/** @file _font.h
 *  @brief Embedded font data.
 */

/* Copyright (c) 2008 the NxOS developers
 *
 * See AUTHORS for a full list of the developers.
 *
 * Redistribution of this file is permitted under
 * the terms of the GNU Public License (GPL) version 2.
 */

#ifndef __NXOS_BASE__FONT_H__
#define __NXOS_BASE__FONT_H__

#include "base/types.h"
#include "base/drivers/_lcd.h"

/** @addtogroup kernelinternal */
/*@{*/

/** @defgroup fontinternal Font data
 *
 * A basic font is embedded into the baseplate, for use by the display
 * driver.
 *
 * @note This data is automatically generated from a "font grid" image
 * at compile time. This makes it easy to tweak the looks of the font by
 * editing an image, and have it nicely embedded in the Baseplate.
 */
/*@{*/

/** The ASCII offset of the first character in the font table.
 *
 * All characters before that one are unprintable.
 */
#define NX__FONT_START 0x20

/** The ASCII offset of the last character in the font table.
 *
 * All characters after that one are unprintable.
 */
#define NX__FONT_END 0x80

/** The width of a font character in pixels. */
#define NX__FONT_WIDTH 5
/** The width of a font cell, which includes a 1-pixel spacer. */
#define NX__CELL_WIDTH (NX__FONT_WIDTH + 1)
/** The number of font cells per line. */
#define NX__DISPLAY_WIDTH_CELLS (LCD_WIDTH / NX__CELL_WIDTH)
/** The number of fond lines on the display. */
#define NX__DISPLAY_HEIGHT_CELLS LCD_HEIGHT

/** The font character data.
 *
 * Each entry in the font array is a subarray of length @b
 * FONT_WIDTH. Each element in that array gives the bitmask for one
 * vertical slice of the character in question.
 */
static const U8 nx__font_data[][NX__FONT_WIDTH] = {
  { 0x00, 0x00, 0x00, 0x00, 0x00 },
  { 0x00, 0x00, 0x5F, 0x00, 0x00 },
  { 0x00, 0x07, 0x00, 0x07, 0x00 },
  { 0x14, 0x3E, 0x14, 0x3E, 0x14 },
  { 0x55, 0xAA, 0x55, 0xAA, 0x55 },
  { 0x26, 0x16, 0x08, 0x34, 0x32 },
  { 0xAA, 0x55, 0xAA, 0x55, 0xAA },
  { 0x00, 0x00, 0x07, 0x00, 0x00 },
  { 0x00, 0x1C, 0x22, 0x41, 0x00 },
  { 0x00, 0x41, 0x22, 0x1C, 0x00 },
  { 0x2A, 0x1C, 0x7F, 0x1C, 0x2A },
  { 0x08, 0x08, 0x3E, 0x08, 0x08 },
  { 0x00, 0x50, 0x30, 0x00, 0x00 },
  { 0x08, 0x08, 0x08, 0x08, 0x08 },
  { 0x00, 0x60, 0x60, 0x00, 0x00 },
  { 0x20, 0x10, 0x08, 0x04, 0x02 },
  { 0x3E, 0x51, 0x49, 0x45, 0x3E },
  { 0x00, 0x42, 0x7F, 0x40, 0x00 },
  { 0x42, 0x61, 0x51, 0x49, 0x46 },
  { 0x21, 0x41, 0x45, 0x4B, 0x31 },
  { 0x18, 0x14, 0x12, 0x7F, 0x10 },
  { 0x27, 0x45, 0x45, 0x45, 0x39 },
  { 0x3C, 0x4A, 0x49, 0x49, 0x30 },
  { 0x01, 0x01, 0x79, 0x05, 0x03 },
  { 0x36, 0x49, 0x49, 0x49, 0x36 },
  { 0x06, 0x49, 0x49, 0x29, 0x1E },
  { 0x00, 0x36, 0x36, 0x00, 0x00 },
  { 0x00, 0x56, 0x36, 0x00, 0x00 },
  { 0x08, 0x14, 0x22, 0x41, 0x00 },
  { 0x14, 0x14, 0x14, 0x14, 0x14 },
  { 0x41, 0x22, 0x14, 0x08, 0x00 },
  { 0x02, 0x01, 0x59, 0x05, 0x02 },
  { 0x3E, 0x41, 0x49, 0x55, 0x1E },
  { 0x7E, 0x09, 0x09, 0x09, 0x7E },
  { 0x7F, 0x49, 0x49, 0x49, 0x3E },
  { 0x3E, 0x41, 0x41, 0x41, 0x22 },
  { 0x7F, 0x41, 0x41, 0x22, 0x1C },
  { 0x7F, 0x49, 0x49, 0x49, 0x41 },
  { 0x7F, 0x09, 0x09, 0x09, 0x01 },
  { 0x3E, 0x41, 0x41, 0x49, 0x3A },
  { 0x7F, 0x08, 0x08, 0x08, 0x7F },
  { 0x00, 0x41, 0x7F, 0x41, 0x00 },
  { 0x20, 0x40, 0x41, 0x3F, 0x01 },
  { 0x7F, 0x08, 0x14, 0x22, 0x41 },
  { 0x7F, 0x40, 0x40, 0x40, 0x40 },
  { 0x7F, 0x02, 0x04, 0x02, 0x7F },
  { 0x7F, 0x04, 0x08, 0x10, 0x7F },
  { 0x3E, 0x41, 0x41, 0x41, 0x3E },
  { 0x7F, 0x09, 0x09, 0x09, 0x06 },
  { 0x3E, 0x41, 0x51, 0x21, 0x5E },
  { 0x7F, 0x09, 0x19, 0x29, 0x46 },
  { 0x26, 0x49, 0x49, 0x49, 0x32 },
  { 0x01, 0x01, 0x7F, 0x01, 0x01 },
  { 0x3F, 0x40, 0x40, 0x40, 0x3F },
  { 0x1F, 0x20, 0x40, 0x20, 0x1F },
  { 0x7F, 0x20, 0x18, 0x20, 0x7F },
  { 0x63, 0x14, 0x08, 0x14, 0x63 },
  { 0x03, 0x04, 0x78, 0x04, 0x03 },
  { 0x61, 0x51, 0x49, 0x45, 0x43 },
  { 0x00, 0x7F, 0x41, 0x41, 0x00 },
  { 0x02, 0x04, 0x08, 0x10, 0x20 },
  { 0x00, 0x41, 0x41, 0x7F, 0x00 },
  { 0x04, 0x02, 0x01, 0x02, 0x04 },
  { 0x40, 0x40, 0x40, 0x40, 0x40 },
  { 0x00, 0x01, 0x02, 0x04, 0x00 },
  { 0x20, 0x54, 0x54, 0x54, 0x78 },
  { 0x7F, 0x48, 0x44, 0x44, 0x38 },
  { 0x30, 0x48, 0x48, 0x48, 0x20 },
  { 0x38, 0x44, 0x44, 0x48, 0x7F },
  { 0x38, 0x54, 0x54, 0x54, 0x18 },
  { 0x08, 0x7E, 0x09, 0x09, 0x02 },
  { 0x0C, 0x52, 0x52, 0x52, 0x3E },
  { 0x7F, 0x08, 0x04, 0x04, 0x78 },
  { 0x00, 0x44, 0x7D, 0x40, 0x00 },
  { 0x20, 0x40, 0x40, 0x3D, 0x00 },
  { 0x7F, 0x10, 0x28, 0x44, 0x00 },
  { 0x00, 0x41, 0x7F, 0x40, 0x00 },
  { 0x7C, 0x04, 0x18, 0x04, 0x78 },
  { 0x7C, 0x08, 0x04, 0x04, 0x78 },
  { 0x38, 0x44, 0x44, 0x44, 0x38 },
  { 0xFC, 0x14, 0x14, 0x14, 0x08 },
  { 0x08, 0x14, 0x14, 0x18, 0x7C },
  { 0x7C, 0x08, 0x04, 0x04, 0x08 },
  { 0x48, 0x54, 0x54, 0x54, 0x20 },
  { 0x04, 0x3F, 0x44, 0x40, 0x20 },
  { 0x3C, 0x40, 0x40, 0x20, 0x7C },
  { 0x1C, 0x20, 0x40, 0x20, 0x1C },
  { 0x3C, 0x40, 0x38, 0x40, 0x3C },
  { 0x44, 0x28, 0x10, 0x28, 0x44 },
  { 0x0C, 0x50, 0x50, 0x50, 0x3C },
  { 0x44, 0x64, 0x54, 0x4C, 0x44 },
  { 0x00, 0x08, 0x36, 0x41, 0x00 },
  { 0x00, 0x00, 0x7F, 0x00, 0x00 },
  { 0x00, 0x41, 0x36, 0x08, 0x00 },
  { 0x00, 0x07, 0x00, 0x07, 0x00 },
  { 0x08, 0x1C, 0x2A, 0x08, 0x08 },
};

/*@}*/
/*@}*/

#endif /* __NXOS_BASE__FONT_H__ */
