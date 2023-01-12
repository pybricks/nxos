# SPDX-License-Identifier: GPL 2.0
# Copyright (c) 2009 The nxos Authors

# SPDX-License-Identifier: MIT
# Copyright (c) 2021 The Pybricks Authors

"""Command line wrapper around pynxt library."""

import argparse
import logging
import sys
import time
import struct

from abc import ABC, abstractmethod
from os import path

import argcomplete
from argcomplete.completers import FilesCompleter

from .. import __name__ as MODULE_NAME, __version__ as MODULE_VERSION


PROG_NAME = (
    f"{path.basename(sys.executable)} -m {MODULE_NAME}"
    if sys.argv[0].endswith("__main__.py")
    else path.basename(sys.argv[0])
)


class Tool(ABC):
    """Common base class for tool implementations."""

    @abstractmethod
    def add_parser(self, subparsers: argparse._SubParsersAction):
        """
        Overriding methods must at least do the following::

            parser = subparsers.add_parser('tool', ...)
            parser.tool = self

        Then additional arguments can be added using the ``parser`` object.
        """
        pass

    @abstractmethod
    def run(self, args: argparse.Namespace):
        """
        Overriding methods should provide an implementation to run the tool.
        """
        pass


class FirmwareInfo(object):
    HEADER_DEF = "<5LB"
    HEADER_SIZE = struct.calcsize(HEADER_DEF)

    def __init__(self, fw_and_header):
        header = fw_and_header[-self.HEADER_SIZE :]
        self.firmware = fw_and_header[: -self.HEADER_SIZE]

        (
            magic,
            self.ramsize,
            self.romsize,
            self.writeaddr,
            self.loadaddr,
            self.samba,
        ) = struct.unpack(self.HEADER_DEF, header)
        self.samba = bool(self.samba)
        if magic != 0xDEADBEEF:
            raise ValueError("Bad magic on header")


class FirmwareExec(Tool):
    def add_parser(self, subparsers: argparse._SubParsersAction):
        parser = subparsers.add_parser(
            "fwexec", help="Load the firmware in RAM and run it."
        )
        parser.tool = self
        parser.add_argument(
            "firmware",
            metavar="<firmware-file>",
            type=argparse.FileType(mode="rb"),
            help="the firmware .bin file",
        ).completer = FilesCompleter(allowednames=(".bin",))

    def run(self, args: argparse.Namespace):

        from ..samba import SambaBrick, SambaOpenError

        fw = args.firmware.read()
        info = FirmwareInfo(fw)
        if not info.samba:
            raise ValueError("Firmware is not suitable for samba mode.")

        if len(fw) > (56 * 1024):
            print("Error: The firmware is too big to fit in RAM.")
            print("Maximum: %d bytes, Actual: %d bytes" % (56 * 1024, len(fw)))
            sys.exit(1)

        s = SambaBrick()

        try:
            print("Looking for the NXT in SAM-BA mode...")
            s.open(timeout=5)
            print("Brick found!")
        except SambaOpenError as e:
            print("Error: %s." % str(e))
            return 1

        print("Uploading firmware...")
        s.write_buffer(info.writeaddr, fw)
        print("Upload complete, jumping to 0x%x..." % info.loadaddr)
        time.sleep(0.25)
        s.jump(info.loadaddr)
        print("Firmware started.")
        s.close()
        return 0


class FirmwareFlash(Tool):
    def add_parser(self, subparsers: argparse._SubParsersAction):
        parser = subparsers.add_parser(
            "fwflash", help="Save the firmware on flash and run it."
        )
        parser.tool = self
        parser.add_argument(
            "firmware",
            metavar="<firmware-file>",
            type=argparse.FileType(mode="rb"),
            help="the firmware .bin file",
        ).completer = FilesCompleter(allowednames=(".bin",))

    def run(self, args: argparse.Namespace):

        from ..samba import SambaBrick, SambaOpenError
        from ..flash import FlashController

        fw = args.firmware.read()
        info = FirmwareInfo(fw)
        if info.samba:
            raise ValueError("Firmware is not suitable for flashing.")

        if len(fw) > (256 * 1024):
            print("Error: The firmware is too big to fit in ROM.")
            print("Maximum: %d bytes, Actual: %d bytes" % (256 * 1024, len(fw)))
            sys.exit(1)

        s = SambaBrick()

        try:
            print("Looking for the NXT in SAM-BA mode...")
            s.open(timeout=5)
            print("Brick found!")
        except SambaOpenError as e:
            print(e)
            sys.exit(1)

        print("Flashing firmware...")
        f = FlashController(s)
        f.flash(fw)
        print("Flashing complete, jumping to 0x100000...")
        time.sleep(0.25)
        s.jump(0x100000)
        print("Firmware started.")
        s.close()
        return 0


def main():
    """Runs ``pynxt`` command line interface."""

    # Provide main description and help.
    parser = argparse.ArgumentParser(
        prog=PROG_NAME,
        description="Utilities for LEGO MINDSTORMS NXT bricks.",
        epilog="Run `%(prog)s <tool> --help` for tool-specific arguments.",
    )

    parser.add_argument(
        "-v", "--version", action="version", version=f"{MODULE_NAME} v{MODULE_VERSION}"
    )
    parser.add_argument(
        "-d", "--debug", action="store_true", help="enable debug logging"
    )

    subparsers = parser.add_subparsers(
        metavar="<tool>",
        dest="tool",
        help="the tool to use",
    )

    for tool in FirmwareExec(), FirmwareFlash():
        tool.add_parser(subparsers)

    argcomplete.autocomplete(parser)
    args = parser.parse_args()

    logging.basicConfig(
        format="%(asctime)s: %(levelname)s: %(name)s: %(message)s",
        level=logging.DEBUG if args.debug else logging.WARNING,
    )

    if not args.tool:
        parser.error(f'Missing name of tool: {"|".join(subparsers.choices.keys())}')

    subparsers.choices[args.tool].tool.run(args)
