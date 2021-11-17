nxos
====

An embedded operating system toolkit for LEGO MINDSTORMS NXT.

This project is forked from [nxos](https://github.com/danderson/nxos/tree/master/nxos),
developed by David Anderson [and others](./nxos/AUTHORS).

This fork updates it to make it work on today's computers.



**Requirements**
- GNU ARM Embedded Toolchain v10-2020-q4 or similar. This repository assumes
  that `arm-none-eabi-gcc` is on your path.
- Python 3.8 or newer.
- Poetry v1.x.
- Pybricksdev [udev rules](https://github.com/pybricks/pybricksdev/blob/master/pybricksdev/resources/99-pybricksdev.rules)
- See [this guide](https://github.com/pybricks/pybricks-micropython/blob/master/CONTRIBUTING.md)
for tips, tricks and useful references.

**Building**
```
poetry install
poetry shell
cd nxos
scons appkernels=examples/sound
```

This builds `sound_samba.bin` which can run from RAM, and `sound_rom.bin` which can be installed on flash.

**Deploying**

First, put the NXT in update (SAMBA) mode:

- Press and hold the small button in the LEGO Technic pin hole under the USB port for 5 seconds.
- Turn the hub on. You will hear a clicking sound.

To run a firmware from RAM and then go back to update mode:

```
pynxt fwexec systems/examples/sound/sound_samba.bin

```
To install it on the brick permanently:

```
pynxt fwflash systems/examples/sound/sound_rom.bin

```
