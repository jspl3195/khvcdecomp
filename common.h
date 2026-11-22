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
/* A double (IEEE-754 double precision), as its two words: a type of its own, so a double is not taken
   for a 64-bit integer (uint64) or the other way round. The soft-float libraries' double routines
   (kh.mod's, and swv21brew's swv_f2d) take and return it; the word macros work on it too (they only use
   .low and .high). */
typedef struct float64 {
  uint32 low;
  uint32 high;
} float64;
/* What the code does with 64-bit values, as macros on the two words (no calls; the arguments are
   evaluated more than once, and the result is assigned high word first).
   MAKE_WORDS(result, h, l): result = h:l, and the expression's value is result (Ghidra's CONCAT44).
   MULTIPLY_WORDS(result, a, b): result = a * b, a and b 32-bit unsigned, from four 16 x 16 products.
   MULTIPLY_SIGNED_WORDS(result, a, b): result = a * b, a and b 32-bit signed and result an int64 (ARM's
   smull): the high word from the four 16 x 16 products as in MULTIPLY_WORDS, less b when a is negative
   and a when b is.
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
#define MULTIPLY_SIGNED_WORDS(result,a,b) \
  ((result).high = (int32)(((uint32)(a) >> 16) * ((uint32)(b) >> 16) + \
                           ((((uint32)(a) >> 16) * ((uint32)(b) & 0xffff)) >> 16) + \
                           ((((uint32)(a) & 0xffff) * ((uint32)(b) >> 16)) >> 16) + \
                           (((((uint32)(a) & 0xffff) * ((uint32)(b) & 0xffff) >> 16) + \
                             ((((uint32)(a) >> 16) * ((uint32)(b) & 0xffff)) & 0xffff) + \
                             ((((uint32)(a) & 0xffff) * ((uint32)(b) >> 16)) & 0xffff)) >> 16) - \
                           ((int32)(a) < 0 ? (uint32)(b) : 0) - ((int32)(b) < 0 ? (uint32)(a) : 0)), \
   (result).low = (uint32)(a) * (uint32)(b))
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
/* Float compares on the bit patterns (a float is its uint32 bits; no C float), as the integer tests the
   soft-float compares' flag results amount to (swv21brew's swv_fcmp_a / swv_fcmp_b / swv_fcmp_c, kh.mod's
   float_compare_*: Z when a == b, +0 == -0; C with Z clear when a > b; a NaN unordered). A caller writes
   the call, then the test its branch makes, in comma form: `bhi` after swv_fcmp_b is FLOAT_GT, `bls` its
   negation; after swv_fcmp_c (unordered: "greater") `bhi` is !FLOAT_LE and `bhs` !FLOAT_LT; `beq` after
   swv_fcmp_a FLOAT_EQ. The arguments are evaluated more than once.
   FLOAT_IS_NAN(a): a is a NaN. FLOAT_KEY(a): a non-NaN a's order as an unsigned word (+0 and -0 the same,
   0x80000000). FLOAT_LT(a, b), FLOAT_LE, FLOAT_GT, FLOAT_GE, FLOAT_EQ: IEEE a < b, a <= b, a > b, a >= b,
   a == b, each false when a or b is a NaN. */
#define FLOAT_IS_NAN(a) (((uint32)(a) << 1) > 0xff000000)
#define FLOAT_KEY(a) \
  ((uint32)(a) & 0x80000000 ? 0x80000000 - ((uint32)(a) & 0x7fffffff) : 0x80000000 + (uint32)(a))
#define FLOAT_ORDERED(a,b) (!FLOAT_IS_NAN(a) && !FLOAT_IS_NAN(b))
#define FLOAT_LT(a,b) (FLOAT_ORDERED(a,b) && FLOAT_KEY(a) < FLOAT_KEY(b))
#define FLOAT_LE(a,b) (FLOAT_ORDERED(a,b) && FLOAT_KEY(a) <= FLOAT_KEY(b))
#define FLOAT_GT(a,b) FLOAT_LT(b,a)
#define FLOAT_GE(a,b) FLOAT_LE(b,a)
#define FLOAT_EQ(a,b) (FLOAT_ORDERED(a,b) && FLOAT_KEY(a) == FLOAT_KEY(b))
int software_interrupt(int number);      /* Ghidra's name for the `svc` (swi) instruction, not a function:
                                            the trap with the given number, its result as r0 leaves it */

#endif /* COMMON_H */
