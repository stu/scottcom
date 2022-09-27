/*
 *    ScottCom -- Compiles adventures into the Scott Adams format.
 *    Copyright (C) 1985-1996  Bjorn Gustavsson
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * $Id: font.c,v 1.1 1996/01/12 08:02:14 bjorn Exp $
 *
 */

unsigned char ti99_font[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     /* Char # 0 */
    0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,     /* Char # 1 */
    0xFC, 0x04, 0x05, 0x05, 0x04, 0x06, 0x02, 0x0C,     /* Char # 2 */
    0x00, 0x80, 0x40, 0x40, 0x80, 0x00, 0x0C, 0x12,     /* Char # 3 */
    0xFF, 0x80, 0xC0, 0x40, 0x60, 0x38, 0x1C, 0x0E,     /* Char # 4 */
    0x19, 0x21, 0x21, 0x3D, 0x05, 0x05, 0x05, 0xC4,     /* Char # 5 */
    0xBA, 0x8A, 0x8A, 0xBA, 0xA1, 0xA1, 0xA1, 0x22,     /* Char # 6 */
    0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     /* Char # 7 */
    0xE2, 0x31, 0x10, 0x18, 0x0C, 0x07, 0x03, 0x00,     /* Char # 8 */
    0x4C, 0x90, 0x20, 0x40, 0x40, 0x20, 0xE0, 0x00,     /* Char # 9 */
    0x3C, 0x42, 0x99, 0xA1, 0xA1, 0x99, 0x42, 0x3C,     /* Char # 10 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     /* Char # 11 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     /* Char # 12 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     /* Char # 13 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     /* Char # 14 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     /* Char # 15 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     /* Char # 16 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     /* Char # 17 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     /* Char # 18 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     /* Char # 19 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     /* Char # 20 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     /* Char # 21 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     /* Char # 22 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     /* Char # 23 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     /* Char # 24 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     /* Char # 25 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     /* Char # 26 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     /* Char # 27 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     /* Char # 28 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     /* Char # 29 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     /* Char # 30 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     /* Char # 31 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     /* Char # 32:   */
    0x00, 0x30, 0x30, 0x30, 0x30, 0x00, 0x30, 0x30,     /* Char # 33: ! */
    0x00, 0x28, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00,     /* Char # 34: " */
    0x00, 0x28, 0x28, 0x7C, 0x28, 0x7C, 0x28, 0x28,     /* Char # 35: # */
    0x00, 0x38, 0x54, 0x50, 0x38, 0x14, 0x54, 0x38,     /* Char # 36: $ */
    0x00, 0x60, 0x64, 0x08, 0x10, 0x20, 0x4C, 0x0C,     /* Char # 37: % */
    0x00, 0x20, 0x50, 0x50, 0x20, 0x54, 0x48, 0x34,     /* Char # 38: & */
    0x00, 0x08, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00,     /* Char # 39: ' */
    0x00, 0x04, 0x08, 0x10, 0x10, 0x10, 0x08, 0x04,     /* Char # 40: ( */
    0x00, 0x40, 0x20, 0x10, 0x10, 0x10, 0x20, 0x40,     /* Char # 41: ) */
    0x00, 0x00, 0x28, 0x10, 0x6C, 0x10, 0x28, 0x00,     /* Char # 42: * */
    0x00, 0x00, 0x10, 0x10, 0x7C, 0x10, 0x10, 0x00,     /* Char # 43: + */
    0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x10, 0x20,     /* Char # 44: , */
    0x00, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00,     /* Char # 45: - */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30,     /* Char # 46: . */
    0x00, 0x00, 0x04, 0x08, 0x10, 0x20, 0x40, 0x00,     /* Char # 47: / */
    0x00, 0x18, 0x24, 0x24, 0x24, 0x24, 0x24, 0x18,     /* Char # 48: 0 */
    0x00, 0x10, 0x30, 0x10, 0x10, 0x10, 0x10, 0x38,     /* Char # 49: 1 */
    0x00, 0x38, 0x44, 0x04, 0x38, 0x40, 0x40, 0x7C,     /* Char # 50: 2 */
    0x00, 0x38, 0x44, 0x04, 0x18, 0x04, 0x44, 0x38,     /* Char # 51: 3 */
    0x00, 0x08, 0x18, 0x28, 0x48, 0x7C, 0x08, 0x08,     /* Char # 52: 4 */
    0x00, 0x7C, 0x40, 0x78, 0x04, 0x04, 0x44, 0x38,     /* Char # 53: 5 */
    0x00, 0x18, 0x20, 0x40, 0x78, 0x44, 0x44, 0x38,     /* Char # 54: 6 */
    0x00, 0x7C, 0x04, 0x08, 0x10, 0x20, 0x20, 0x20,     /* Char # 55: 7 */
    0x00, 0x38, 0x44, 0x44, 0x38, 0x44, 0x44, 0x38,     /* Char # 56: 8 */
    0x00, 0x38, 0x44, 0x44, 0x3C, 0x04, 0x08, 0x30,     /* Char # 57: 9 */
    0x00, 0x00, 0x30, 0x30, 0x00, 0x30, 0x30, 0x00,     /* Char # 58: : */
    0x00, 0x30, 0x30, 0x00, 0x30, 0x30, 0x10, 0x20,     /* Char # 59: ; */
    0x00, 0x04, 0x08, 0x10, 0x20, 0x10, 0x08, 0x04,     /* Char # 60: < */
    0x00, 0x00, 0x00, 0x7C, 0x00, 0x7C, 0x00, 0x00,     /* Char # 61: = */
    0x00, 0x40, 0x20, 0x10, 0x08, 0x10, 0x20, 0x40,     /* Char # 62: > */
    0x00, 0x38, 0x44, 0x08, 0x10, 0x10, 0x00, 0x10,     /* Char # 63: ? */
    0x00, 0x38, 0x44, 0x5C, 0x54, 0x5C, 0x40, 0x38,     /* Char # 64: @ */
    0x00, 0x38, 0x44, 0x44, 0x7C, 0x44, 0x44, 0x44,     /* Char # 65: A */
    0x00, 0x78, 0x24, 0x24, 0x38, 0x24, 0x24, 0x78,     /* Char # 66: B */
    0x00, 0x38, 0x44, 0x40, 0x40, 0x40, 0x44, 0x38,     /* Char # 67: C */
    0x00, 0x78, 0x24, 0x24, 0x24, 0x24, 0x24, 0x78,     /* Char # 68: D */
    0x00, 0x7C, 0x40, 0x40, 0x78, 0x40, 0x40, 0x7C,     /* Char # 69: E */
    0x00, 0x7C, 0x40, 0x40, 0x78, 0x40, 0x40, 0x40,     /* Char # 70: F */
    0x00, 0x3C, 0x40, 0x40, 0x5C, 0x44, 0x44, 0x38,     /* Char # 71: G */
    0x00, 0x44, 0x44, 0x44, 0x7C, 0x44, 0x44, 0x44,     /* Char # 72: H */
    0x00, 0x38, 0x10, 0x10, 0x10, 0x10, 0x10, 0x38,     /* Char # 73: I */
    0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x44, 0x38,     /* Char # 74: J */
    0x00, 0x44, 0x48, 0x50, 0x60, 0x50, 0x48, 0x44,     /* Char # 75: K */
    0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7C,     /* Char # 76: L */
    0x00, 0x44, 0x6C, 0x54, 0x54, 0x44, 0x44, 0x44,     /* Char # 77: M */
    0x00, 0x44, 0x64, 0x54, 0x4C, 0x44, 0x44, 0x44,     /* Char # 78: N */
    0x00, 0x7C, 0x44, 0x44, 0x44, 0x44, 0x44, 0x7C,     /* Char # 79: O */
    0x00, 0x78, 0x44, 0x44, 0x78, 0x40, 0x40, 0x40,     /* Char # 80: P */
    0x00, 0x38, 0x44, 0x44, 0x44, 0x54, 0x48, 0x34,     /* Char # 81: Q */
    0x00, 0x78, 0x44, 0x44, 0x78, 0x50, 0x48, 0x44,     /* Char # 82: R */
    0x00, 0x38, 0x44, 0x20, 0x10, 0x08, 0x44, 0x38,     /* Char # 83: S */
    0x00, 0x7C, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,     /* Char # 84: T */
    0x00, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x38,     /* Char # 85: U */
    0x00, 0x44, 0x44, 0x44, 0x28, 0x28, 0x10, 0x10,     /* Char # 86: V */
    0x00, 0x44, 0x44, 0x44, 0x54, 0x54, 0x54, 0x28,     /* Char # 87: W */
    0x00, 0x44, 0x44, 0x28, 0x10, 0x28, 0x44, 0x44,     /* Char # 88: X */
    0x00, 0x44, 0x44, 0x28, 0x10, 0x10, 0x10, 0x10,     /* Char # 89: Y */
    0x00, 0x7C, 0x04, 0x08, 0x10, 0x20, 0x40, 0x7C,     /* Char # 90: Z */
    0x00, 0x1C, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1C,     /* Char # 91: [ */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     /* Char # 92: \ */
    0x00, 0x70, 0x10, 0x10, 0x10, 0x10, 0x10, 0x70,     /* Char # 93: ] */
    0x00, 0x20, 0x50, 0x88, 0x00, 0x00, 0x00, 0x00,     /* Char # 94: ^ */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C,     /* Char # 95: _ */
    0x00, 0x40, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,     /* Char # 96: ` */
    0x00, 0x00, 0x00, 0x30, 0x08, 0x78, 0x48, 0x3C,     /* Char # 97: a */
    0x00, 0x20, 0x20, 0x38, 0x24, 0x24, 0x24, 0x38,     /* Char # 98: b */
    0x00, 0x00, 0x00, 0x18, 0x24, 0x20, 0x24, 0x18,     /* Char # 99: c */
    0x00, 0x04, 0x04, 0x1C, 0x24, 0x24, 0x24, 0x1C,     /* Char # 100: d */
    0x00, 0x00, 0x00, 0x18, 0x24, 0x3C, 0x20, 0x1C,     /* Char # 101: e */
    0x00, 0x08, 0x14, 0x10, 0x38, 0x10, 0x10, 0x10,     /* Char # 102: f */
    0x00, 0x00, 0x00, 0x1C, 0x24, 0x1C, 0x04, 0x38,     /* Char # 103: g */
    0x00, 0x20, 0x20, 0x38, 0x24, 0x24, 0x24, 0x24,     /* Char # 104: h */
    0x00, 0x10, 0x00, 0x30, 0x10, 0x10, 0x10, 0x38,     /* Char # 105: i */
    0x00, 0x08, 0x00, 0x08, 0x08, 0x08, 0x28, 0x10,     /* Char # 106: j */
    0x00, 0x20, 0x20, 0x24, 0x28, 0x30, 0x28, 0x24,     /* Char # 107: k */
    0x00, 0x30, 0x10, 0x10, 0x10, 0x10, 0x10, 0x38,     /* Char # 108: l */
    0x00, 0x00, 0x00, 0x78, 0x54, 0x54, 0x54, 0x54,     /* Char # 109: m */
    0x00, 0x00, 0x00, 0x38, 0x24, 0x24, 0x24, 0x24,     /* Char # 110: n */
    0x00, 0x00, 0x00, 0x18, 0x24, 0x24, 0x24, 0x18,     /* Char # 111: o */
    0x00, 0x00, 0x00, 0x38, 0x24, 0x38, 0x20, 0x20,     /* Char # 112: p */
    0x00, 0x00, 0x00, 0x1C, 0x24, 0x1C, 0x04, 0x04,     /* Char # 113: q */
    0x00, 0x00, 0x00, 0x28, 0x34, 0x20, 0x20, 0x20,     /* Char # 114: r */
    0x00, 0x00, 0x00, 0x1C, 0x20, 0x18, 0x04, 0x38,     /* Char # 115: s */
    0x00, 0x10, 0x10, 0x38, 0x10, 0x10, 0x14, 0x0C,     /* Char # 116: t */
    0x00, 0x00, 0x00, 0x24, 0x24, 0x24, 0x24, 0x1C,     /* Char # 117: u */
    0x00, 0x00, 0x00, 0x44, 0x44, 0x44, 0x28, 0x10,     /* Char # 118: v */
    0x00, 0x00, 0x00, 0x44, 0x54, 0x54, 0x54, 0x28,     /* Char # 119: w */
    0x00, 0x00, 0x00, 0x44, 0x28, 0x10, 0x28, 0x44,     /* Char # 120: x */
    0x00, 0x00, 0x00, 0x44, 0x28, 0x10, 0x10, 0x10,     /* Char # 121: y */
    0x00, 0x00, 0x00, 0x3C, 0x04, 0x08, 0x10, 0x3C,     /* Char # 122: z */
    0x00, 0x0C, 0x10, 0x10, 0x20, 0x10, 0x10, 0x0C,     /* Char # 123: { */
    0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,     /* Char # 124: | */
    0x00, 0x60, 0x10, 0x10, 0x08, 0x10, 0x10, 0x60,     /* Char # 125: } */
    0x00, 0x00, 0x00, 0x24, 0x58, 0x00, 0x00, 0x00,     /* Char # 126: ~ */
    0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,     /* Char # 127 */
};