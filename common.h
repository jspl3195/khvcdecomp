/*
 * common.h - the types and macros kh_mod.h and swv21brew.h share: Ghidra's type names, and the 64-bit
 * values as two 32-bit words with the macros that work on them. Included by both headers.
 */

#ifndef COMMON_H
#define COMMON_H

#include "brew_types.h"

/* Ghidra type names used by the decompiler output (not BREW types). */
typedef unsigned char  undefined;
typedef unsigned char  undefined1;
typedef unsigned short undefined2;
typedef unsigned int   undefined4;
typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef unsigned char  byte;
typedef unsigned char  bool;    /* Ghidra's boolean: 0 or 1 (C90 has no bool) */
#define true  1                 /* Ghidra's boolean constants (keywords only in C++ and C23) */
#define false 0
#ifndef NULL
#define NULL  ((void *)0)        /* used by the hand-written functions; no standard header is included */
#endif
typedef int            code();  /* Ghidra: function of unknown signature (a call through (code *) is valid C) */

/* C90 has no 64-bit integer type, so a 64-bit value is two 32-bit words: low is the word the ARM code
   holds in r0 (r2) and high the one in r1 (r3); in memory the low word comes first (little-endian), as
   in the structs. uint64 (Ghidra's ulonglong) and int64 (Ghidra's longlong) are two distinct struct
   types, so the compiler tells them apart: assigning one to the other is an error. int64 keeps the sign
   in its high word (int32). The word macros below work on uint64 (unsigned arithmetic, no overflow);
   undefined8 (Ghidra's 8 unknown bytes, in its raw text) is uint64. */
typedef struct uint64 {
  uint32 low;
  uint32 high;
} uint64;
typedef struct int64 {
  uint32 low;
  int32 high;
} int64;
/* What the code does with 64-bit values, as macros on the two words (no calls; the arguments are
   evaluated more than once, and the result is assigned high word first).
   MAKE_WORDS(result, h, l): result = h:l, and the expression's value is result (Ghidra's CONCAT44).
   MULTIPLY_WORDS(result, a, b): result = a * b, a and b 32-bit unsigned, from four 16 x 16 products.
   ADD_WORDS(result, a, b): result = a + b, the carry from the low word into the high (result may be a
   or b). SUBTRACT_WORDS(result, a, b): result = a - b, the same way. SUBTRACT_WORD(result, w): result =
   result - w, w a 32-bit word. SHIFT_LEFT_WORDS(result, a, n): result = a << n, 0 < n < 32 (result may
   be a). */
#define MAKE_WORDS(result,h,l) ((result).high = (h), (result).low = (l), (result))
#define MULTIPLY_WORDS(result,a,b) \
  ((result).high = ((a) >> 16) * ((b) >> 16) + (((a) >> 16) * ((b) & 0xffff) >> 16) + \
                   (((a) & 0xffff) * ((b) >> 16) >> 16) + \
                   ((((a) & 0xffff) * ((b) & 0xffff) >> 16) + (((a) >> 16) * ((b) & 0xffff) & 0xffff) + \
                    (((a) & 0xffff) * ((b) >> 16) & 0xffff) >> 16), \
   (result).low = (a) * (b))
#define ADD_WORDS(result,a,b) \
  ((result).high = (a).high + (b).high + ((a).low + (b).low < (a).low), \
   (result).low = (a).low + (b).low)
#define SUBTRACT_WORDS(result,a,b) \
  ((result).high = (a).high - (b).high - ((a).low < (b).low), \
   (result).low = (a).low - (b).low)
#define SUBTRACT_WORD(result,w) \
  ((result).high = (result).high - ((result).low < (w)), (result).low = (result).low - (w))
#define SHIFT_LEFT_WORDS(result,a,n) \
  ((result).high = (a).high << (n) | (a).low >> (32 - (n)), (result).low = (a).low << (n))
#endif /* COMMON_H */
