/*
 * kh_mod.h - kh.mod (applet 0x01026191): types, globals and prototypes
 *
 * Source module : dumps/mod/11839/kh.mod (164424 bytes)
 * SHA-256       : 91b28342b14bf8268657f79da7722c5099a496b2c078f90375d93a82ec37fb31
 * Ghidra base   : 0x00100000 (= khvcemu load address); file offset = address - 0x100000
 * Functions     : 450 from Ghidra + hand-written ones Ghidra has no function for
 * Calls into this module from khvcemu: AEEMod_Load, AEEMod_CreateInstance, AEEApplet_HandleEvent
 * (khvcemu/runtime.py:211-242, 398-422). Swerve 3D calls go through ISwerve / ISwerveTarget (kh_types.h).
 */

#ifndef KH_MOD_H
#define KH_MOD_H

#include "brew_types.h"
#include "swv_types.h"
#include "kh_types.h"

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
   for a 64-bit integer (uint64) or the other way round. The soft-float library's double routines take
   and return it; the word macros work on it too (they only use .low and .high). */
typedef struct float64 {
  uint32 low;
  uint32 high;
} float64;
/* Comparisons of two float64 on their words, with no C floating type: the comparison a caller's branch
   makes after double_compare_equal / _greater / _less (which leave the result in the flags), written
   after the comma. +0 == -0; every comparison is false for a NaN, so the negations stand for the
   branches a NaN takes. a > b is DOUBLE_LESS(b,a), a >= b DOUBLE_LESS_EQUAL(b,a). Macros, not calls; the
   arguments are evaluated more than once. */
#define DOUBLE_IS_NAN(a) (((a).high << 1 | ((a).low != 0)) > 0xFFE00000u)
#define DOUBLE_IS_ZERO(a) (((a).high << 1 | (a).low) == 0)
#define DOUBLE_WORDS_LESS(a,b) ((a).high < (b).high || ((a).high == (b).high && (a).low < (b).low))
#define DOUBLE_EQUAL(a,b) \
  (!DOUBLE_IS_NAN(a) && !DOUBLE_IS_NAN(b) && \
   (((a).high == (b).high && (a).low == (b).low) || (DOUBLE_IS_ZERO(a) && DOUBLE_IS_ZERO(b))))
/* both negative: the larger magnitude is the smaller; signs differ: the negative one; else the words */
#define DOUBLE_LESS(a,b) \
  (!DOUBLE_IS_NAN(a) && !DOUBLE_IS_NAN(b) && !(DOUBLE_IS_ZERO(a) && DOUBLE_IS_ZERO(b)) && \
   ((int32)((a).high & (b).high) < 0 ? DOUBLE_WORDS_LESS(b,a) : \
    (int32)((a).high ^ (b).high) < 0 ? (int32)(a).high < 0 : DOUBLE_WORDS_LESS(a,b)))
#define DOUBLE_LESS_EQUAL(a,b) (DOUBLE_LESS(a,b) || DOUBLE_EQUAL(a,b))
typedef uint64 undefined8;
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
/* Shifts by a variable count, as the binary does them: the count is its low byte, and a count of 32
   or more gives 0 (SHIFT_LEFT, SHIFT_RIGHT) or the sign in every bit (SHIFT_RIGHT_SIGNED), where C
   leaves a shift by the width or more undefined. Macros, not calls. */
#define SHIFT_LEFT(x,n) (((n) & 0xff) < 32 ? (uint)(x) << ((n) & 0xff) : 0)
#define SHIFT_RIGHT(x,n) (((n) & 0xff) < 32 ? (uint)(x) >> ((n) & 0xff) : 0)
#define SHIFT_RIGHT_SIGNED(x,n) ((int)(x) >> (((n) & 0xff) < 32 ? ((n) & 0xff) : 31))
/* The carry out of a + b; whether a + b and a - b overflow as signed 32-bit numbers (Ghidra's CARRY4,
   SCARRY4 and SBORROW4). */
#define ADD_CARRIES(a,b) ((uint)(a) + (uint)(b) < (uint)(a))
#define ADD_OVERFLOWS(a,b) \
  ((~((uint)(a) ^ (uint)(b)) & ((uint)(a) ^ ((uint)(a) + (uint)(b)))) >> 31)
#define SUBTRACT_OVERFLOWS(a,b) \
  ((((uint)(a) ^ (uint)(b)) & ((uint)(a) ^ ((uint)(a) - (uint)(b)))) >> 31)
/* The number of leading zero bits of a 32-bit word, 32 for 0 (Ghidra's LZCOUNT), by a lookup per byte. */
#define LEADING_ZEROS(x) \
  ((uint)(x) >> 16 ? ((uint)(x) >> 24 ? leading_zeros_in_byte[(uint)(x) >> 24] \
                                      : 8 + leading_zeros_in_byte[(uint)(x) >> 16]) \
                   : ((uint)(x) >> 8 ? 16 + leading_zeros_in_byte[(uint)(x) >> 8] \
                                     : 24 + leading_zeros_in_byte[(uint)(x) & 0xff]))
static const uint8 leading_zeros_in_byte[256] = {
  8,7,6,6,5,5,5,5,4,4,4,4,4,4,4,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
  2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
#define true  1                 /* Ghidra's boolean constants (keywords only in C++ and C23) */
#define false 0
#ifndef NULL
#define NULL  ((void *)0)        /* used by the hand-written functions; no standard header is included */
#endif
typedef int            code();  /* Ghidra: function of unknown signature (a call through (code *) is valid C) */

/* Literal-pool words given a name (Ghidra's DAT_<address> labels; the value is the word stored at
   that address in kh.mod's read-only image). */
#define ADP_Stopped_ApplicationExit 0x00020026u  /* was DAT_001014d0 (word at 0x001014D0). ARM
                                                    semihosting reason code "application exit",
                                                    passed in r1 with SYS_EXIT (r0 = 0x18) to
                                                    swi 0x123456 on the C library's exit path */
#define PI_DOUBLE_LOW_WORD  0x54442D18u      /* was DAT_001007ac (word at 0x001007AC) */
#define PI_DOUBLE_HIGH_WORD 0x400921FBu      /* was DAT_001007b0 (word at 0x001007B0) */
                                             /* together the IEEE-754 double pi = 0x400921FB54442D18
                                                (3.141592653589793), stored low word first, as the
                                                soft-float code passes doubles in r0:r1 */
#define ONE_DOUBLE_LOW_WORD  0x00000000u     /* was DAT_001007c4 (word at 0x001007C4) and
                                                DAT_00100c0c (word at 0x00100C0C) */
#define ONE_DOUBLE_HIGH_WORD 0x3FF00000u     /* was DAT_001007c8 (word at 0x001007C8) and
                                                DAT_00100c10 (word at 0x00100C10) */
                                             /* together the IEEE-754 double 1.0 = 0x3FF0000000000000,
                                                low word first: the second operand (r2:r3) of the
                                                soft-float calls that pass it. The second copy is in
                                                math_kernel_cos's pool (GUESS: fdlibm kernel_cos), which
                                                returns it for |x| < 2**-27 (fdlibm's `return one`) */
#define HALF_DOUBLE_LOW_WORD  0x00000000u    /* was DAT_001007e4 (word at 0x001007E4),
                                                DAT_00100c1c (word at 0x00100C1C),
                                                DAT_00101194 (word at 0x00101194) and
                                                DAT_001013d8 (word at 0x001013D8) */
#define HALF_DOUBLE_HIGH_WORD 0x3FE00000u    /* was DAT_001007e8 (word at 0x001007E8),
                                                DAT_00100c20 (word at 0x00100C20),
                                                DAT_00101198 (word at 0x00101198) and
                                                DAT_001013dc (word at 0x001013DC) */
                                             /* together the IEEE-754 double 0.5 = 0x3FE0000000000000,
                                                low word first. The second copy is in math_kernel_cos's
                                                pool (GUESS: kernel_cos): the 0.5*z of fdlibm's
                                                1 - (0.5*z - (z*r - x*y)), z = x*x. The third is in
                                                math_rem_pio2's (GUESS: rem_pio2): fdlibm's `half` in the
                                                rounding n = (int)(|x| * invpio2 + half). The fourth is in
                                                math_kernel_sin's (GUESS: kernel_sin): the half*y of
                                                x - ((z*(half*y - v*r) - y) - v*S1) */
#define TWO_DOUBLE_LOW_WORD  0x00000000u     /* was DAT_001007ec (word at 0x001007EC) */
#define TWO_DOUBLE_HIGH_WORD 0x40000000u     /* was DAT_001007f0 (word at 0x001007F0) */
                                             /* together the IEEE-754 double 2.0 = 0x4000000000000000,
                                                low word first */
#define QUARTER_PI_HIGH_WORD 0x3FE921FB      /* was DAT_001008c4 (word at 0x001008C4), DAT_001009ac
                                                (word at 0x001009AC) and DAT_0010115c (word at
                                                0x0010115C): three copies of the high word of pi/4
                                                (0x3FE921FB54442D18 = 0.785398...), one in each of
                                                three literal pools (the third: math_rem_pio2, GUESS:
                                                rem_pio2, "no reduction needed"). fdlibm's range test
                                                |x|_high <= 0x3fe921fb ("|x| <= ~pi/4") before reducing
                                                the argument, in math_cos and math_sin (GUESS:
                                                fdlibm cos and sin - the small-|x| path is kernel_cos
                                                in the first and kernel_sin(x, 0.0, 0) in the second).
                                                Compared as a signed int, so no u suffix */
#define ZERO_DOUBLE_LOW_WORD  0x00000000u    /* word at 0x001008BC (not shown in C),
                                                DAT_001009a4 (word at 0x001009A4),
                                                DAT_00100a18 (word at 0x00100A18) and
                                                DAT_00101154 (word at 0x00101154) */
#define ZERO_DOUBLE_HIGH_WORD 0x00000000u    /* was DAT_001008c0 (word at 0x001008C0),
                                                DAT_001009a8 (word at 0x001009A8),
                                                DAT_00100a1c (word at 0x00100A1C) and
                                                DAT_00101158 (word at 0x00101158) */
                                             /* together the double 0.0, one copy in each of the
                                                literal pools of math_cos and math_sin (GUESS:
                                                fdlibm cos and sin, whose `double z = 0.0` this is).
                                                sin passes it as kernel_sin's tail argument for
                                                |x| <= pi/4 (kh_mod.c math_sin). A third copy is in
                                                math_sqrt's pool (GUESS: sqrt), which compares x with
                                                it (double_compare_less) and sets errno = EDOM and returns NaN
                                                for x < 0. A fourth copy is in math_rem_pio2's pool
                                                (GUESS: rem_pio2), which presets y[1] = 0 with it.
                                                In cos it is
                                                loaded into r2:r3 at entry as kernel_cos's tail argument
                                                for |x| <= pi/4. In the call to math_rem_pio2 (rem_pio2)
                                                the high word is only what r3 still holds - not an
                                                argument rem_pio2 reads. Same value as the ZERO_DOUBLE
                                                object (acos's copy, which the code takes the address of) */
#define NAN_DOUBLE_LOW_WORD  0x00000001u     /* was DAT_001008c8 (word at 0x001008C8),
                                                DAT_001009b0 (word at 0x001009B0) and
                                                DAT_00100a20 (word at 0x00100A20) */
#define NAN_DOUBLE_HIGH_WORD 0x7FF80000u     /* words at 0x001008CC, 0x001009B4 and 0x00100A24
                                                (loaded with them; not shown in C) */
                                             /* together the IEEE-754 quiet NaN 0x7FF80000_00000001:
                                                the same value as NAN_DOUBLE, with one copy in each of
                                                the literal pools of math_cos and math_sin
                                                (GUESS: fdlibm cos and sin), and a third in
                                                math_sqrt's (GUESS: sqrt). cos and sin return it for
                                                x = +-infinity, sqrt for x < 0, each after errno = EDOM
                                                (`adr r1, 0x1008c8; ldmia r1, {r0, r1}`) */
#define SIN_KERNEL_S1_LOW_WORD  0x55555549u  /* was DAT_001013d0 (word at 0x001013D0) */
#define SIN_KERNEL_S1_HIGH_WORD 0xBFC55555u  /* was DAT_001013d4 (word at 0x001013D4) */
                                             /* together -1.66666666666666324348e-01 =
                                                0xBFC5555555555549 (about -1/6), fdlibm k_sin.c's S1:
                                                kernel_sin returns x + v*(S1 + z*r) for iy == 0 and
                                                x - ((z*(half*y - v*r) - y) - v*S1) otherwise
                                                (z = x*x, v = z*x, r = S2 + z*(S3 + ... + z*S6)) */
#define COS_KERNEL_QX_LOW_WORD  0x00000000u  /* was DAT_00100c24 (word at 0x00100C24) */
#define COS_KERNEL_QX_HIGH_WORD 0x3FD20000   /* was DAT_00100c28 (word at 0x00100C28); assigned to an
                                                int, so no u suffix */
                                             /* together the double 0.28125 = 0x3FD2000000000000,
                                                fdlibm k_cos.c's qx for |x| > 0.78125 (ix > 0x3fe90000);
                                                for 0.3 <= |x| <= 0.78125 qx is |x|/4 instead
                                                (INSERT_WORDS(qx, ix - 0x00200000, 0)). kernel_cos
                                                then returns (1 - qx) - ((0.5*z - qx) - (z*r - x*y))
                                                (math_kernel_cos, GUESS: kernel_cos) */
#define THREE_TENTHS_HIGH_WORD 0x3FD33333    /* was DAT_00100c18 (word at 0x00100C18): the high word of
                                                0.3 (0x3FD3333333333333), fdlibm k_cos.c's range test
                                                ix < 0x3FD33333 ("|x| < 0.3"): below it kernel_cos uses
                                                1 - (0.5*z - (z*r - x*y)), above it it subtracts qx
                                                first (math_kernel_cos, GUESS: kernel_cos). Compared as a
                                                signed int, so no u suffix */
#define THREE_QUARTER_PI_HIGH_WORD 0x4002D97C  /* was DAT_00101160 (word at 0x00101160): the high
                                                word of 3*pi/4 (2.356194...), fdlibm e_rem_pio2.c's
                                                test ix < 0x4002d97c ("|x| < 3pi/4": the n = +-1 special
                                                case). Compared as a signed int, so no u suffix */
#define HALF_PI_FIRST_33_BITS_LOW_WORD   0x54400000u  /* was DAT_00101164 (word at 0x00101164) */
#define HALF_PI_FIRST_33_BITS_HIGH_WORD  0x3FF921FBu  /* was DAT_00101168 (word at 0x00101168) */
                                             /* together 1.57079632673412561417e+00 =
                                                0x3FF921FB54400000, fdlibm's pio2_1: the first 33 bits
                                                of pi/2. rem_pio2 computes z = x -+ pio2_1 */
#define HALF_PI_FIRST_33_BITS_TAIL_LOW_WORD  0x1A626331u  /* was DAT_00101178 (word at 0x00101178) */
#define HALF_PI_FIRST_33_BITS_TAIL_HIGH_WORD 0x3DD0B461u  /* was DAT_0010117c (word at 0x0010117C) */
                                             /* together 6.07710050650619224932e-11 =
                                                0x3DD0B4611A626331, fdlibm's pio2_1t: pi/2 - pio2_1, the
                                                tail after the first 33 bits. rem_pio2 loads it with
                                                `adrne r2, 0x101178; ldmiane r2, {r2, r3}` for
                                                n = +-1, and uses it in the medium case as fdlibm's
                                                w = fn * pio2_1t */
#define HALF_PI_SECOND_33_BITS_LOW_WORD  0x1A600000u  /* was DAT_00101180 (word at 0x00101180) */
#define HALF_PI_SECOND_33_BITS_HIGH_WORD 0x3DD0B461u  /* was DAT_00101184 (word at 0x00101184) */
                                             /* together 6.07710050630396597660e-11 =
                                                0x3DD0B4611A600000, fdlibm's pio2_2: the next 33 bits
                                                of pi/2, subtracted as well when x is near pi/2 */
#define HALF_PI_SECOND_33_BITS_TAIL_LOW_WORD  0x2E037073u  /* word at 0x00101170 */
#define HALF_PI_SECOND_33_BITS_TAIL_HIGH_WORD 0x3BA3198Au  /* word at 0x00101174 */
                                             /* together 2.02226624879595063154e-21 =
                                                0x3BA3198A2E037073, fdlibm's pio2_2t: pi/2 - (pio2_1 +
                                                pio2_2), the tail after 66 bits, used when x is near
                                                pi/2. Loaded with `ldmia r10, {r2, r3}`, r10 = 0x101170 */
/* math_rem_pio2 (GUESS: rem_pio2) - limits between its three ways of reducing x */
#define MEDIUM_ARGUMENT_LIMIT_HIGH_WORD 0x413921FB  /* was DAT_00101188 (word at 0x00101188): high word
                                                of ~1647099 (about 2^20 * pi/2), fdlibm e_rem_pio2.c's
                                                medium-size limit (ix <= 0x413921fb). Above it the large-
                                                argument path runs. Compared as a signed int, so no u */
#define LARGE_ARGUMENT_EXPONENT_LIMIT  0x469        /* was DAT_001011a0 (word at 0x001011A0): 1129, a
                                                biased exponent (1129 - 1023 = 106): for |x| >= 2^106 the
                                                large-argument path first scales x by a table entry */
/* The large-argument path (|x| > ~2^20*pi/2) is the ARM library's own, not fdlibm's (fdlibm calls
   __kernel_rem_pio2 there). It splits x (low word & 0xfc000000 and the rest), multiplies both parts
   by a two-part constant C = HIGH_PART + LOW_PART, sums the partial products and reduces modulo the
   period K (double_remainder). Checked from the values: C_hi + C_lo = 0.426041899379994537522 and
   K = 2*pi*C exactly; the pool also holds C itself (0x00101260) and K/4 (0x00101258).
   GUESS: what C stands for, and so the exact meaning of the reduction. */
#define REDUCTION_CONSTANT_HIGH_PART_LOW_WORD  0x40000000u  /* was DAT_001011a8 (0x001011A8) */
#define REDUCTION_CONSTANT_HIGH_PART_HIGH_WORD 0x3FDB4445u  /* was DAT_001011ac (0x001011AC) */
                                             /* C_hi = 4.26041901111602783203e-01 (0x3FDB444540000000:
                                                few mantissa bits, so products with it are exact) */
#define REDUCTION_CONSTANT_LOW_PART_LOW_WORD   0x90000000u  /* was DAT_001011b0 (0x001011B0) */
#define REDUCTION_CONSTANT_LOW_PART_HIGH_WORD  0xBE1DBFB1u  /* was DAT_001011b4 (0x001011B4) */
                                             /* C_lo = -1.73160824568086013642e-09 (0xBE1DBFB190000000),
                                                the correction: C = C_hi + C_lo */
#define REDUCTION_CONSTANT_LOW_WORD  0x3E2404E7u   /* was DAT_00101260 (word at 0x00101260) */
#define REDUCTION_CONSTANT_HIGH_WORD 0x3FDB4445u   /* was DAT_00101264 (word at 0x00101264) */
                                             /* C itself = 4.26041899379994537522e-01
                                                (0x3FDB44453E2404E7) = C_hi + C_lo, used whole to scale
                                                the reduced value into y[0] */
#define REDUCTION_PERIOD_LOW_WORD  0xA740A5A7u      /* was DAT_001011b8 (word at 0x001011B8) */
#define REDUCTION_PERIOD_HIGH_WORD 0x40056A4Au      /* was DAT_001011bc (word at 0x001011BC) */
                                             /* K = 2.67690020242726545163e+00 (0x40056A4AA740A5A7)
                                                = 2*pi*C: the modulus double_remainder reduces by */
#define REDUCTION_QUARTER_PERIOD_LOW_WORD  0xA740A5A7u  /* was DAT_00101258 (word at 0x00101258) */
#define REDUCTION_QUARTER_PERIOD_HIGH_WORD 0x3FE56A4Au  /* was DAT_0010125c (word at 0x0010125C) */
                                             /* K/4 = 6.69225050606816362908e-01 (0x3FE56A4AA740A5A7,
                                                the same mantissa as K): the quarter period, for the
                                                reduction within a quadrant */
#define EIGHT_DOUBLE_LOW_WORD  0x00000000u    /* was DAT_00101248 (word at 0x00101248) */
#define EIGHT_DOUBLE_HIGH_WORD 0x40200000u    /* was DAT_0010124c (word at 0x0010124C) */
                                             /* the double 8.0: the large-argument path multiplies the
                                                reduced value by 8 ... */
#define NINE_DOUBLE_LOW_WORD   0x00000000u    /* was DAT_00101250 (word at 0x00101250) */
#define NINE_DOUBLE_HIGH_WORD  0x40220000u    /* was DAT_00101254 (word at 0x00101254) */
                                             /* ... and adds 9.0, then converts to int (double_to_int)
                                                and halves it: the quadrant. GUESS: why 8 and 9 */
#define TWO_OVER_PI_LOW_WORD   0x6DC9C883u    /* was DAT_0010118c (word at 0x0010118C) */
#define TWO_OVER_PI_HIGH_WORD  0x3FE45F30u    /* was DAT_00101190 (word at 0x00101190) */
                                             /* 2/pi = 6.36619772367581382433e-01 (0x3FE45F306DC9C883),
                                                fdlibm's invpio2: the medium case's
                                                n = (int)(|x| * invpio2 + half) */
#define HALF_PI_DOUBLE_LOW_WORD  0x54442D18u  /* was DAT_001007d4 (word at 0x001007D4) */
#define HALF_PI_DOUBLE_HIGH_WORD 0x3FF921FBu  /* was DAT_001007d8 (word at 0x001007D8) and
                                                 DAT_0010116c (word at 0x0010116C; in math_rem_pio2,
                                                 GUESS: rem_pio2, the "x near pi/2" test
                                                 ix != 0x3ff921fb) */
                                             /* together the IEEE-754 double pi/2 = 1.5707963267948966
                                                = 0x3FF921FB54442D18, fdlibm's pio2_hi (same low word as
                                                pi, which differs only in the exponent) */
#define HALF_PI_CORRECTION_LOW_WORD  0x33145C07u  /* was DAT_001007dc (word at 0x001007DC) */
#define HALF_PI_CORRECTION_HIGH_WORD 0x3C91A626u  /* was DAT_001007e0 (word at 0x001007E0) */
                                             /* together the IEEE-754 double 6.12323399573676603587e-17
                                                = 0x3C91A62633145C07, fdlibm's pio2_lo: the part of pi/2
                                                a double cannot hold (pi/2 = pio2_hi + pio2_lo), added
                                                separately to keep acos's result exact */

#define DOUBLE_EXPONENT_MASK_SHIFTED 0xFFE00000u  /* was DAT_00124e08 (word at 0x00124E08), in the
                                                     soft-float library's literal pool: a double's
                                                     11-bit exponent mask 0x7FF00000 shifted left by 1,
                                                     to match a high word shifted left by 1 (sign bit
                                                     dropped). (MASK & ~(hi << 1)) == 0 means "all
                                                     exponent bits set": the operand is Inf or NaN.
                                                     Used by the add/subtract routines double_add,
                                                     double_reverse_subtract, double_subtract and by
                                                     their copy inlined into math_polynomial */
#define DOUBLE_ADD_NONFINITE_OPERAND_CODE 0x04000011u  /* was DAT_00124e10 (word at 0x00124E10), in
                                                     the soft-float library's literal pool. Not a
                                                     number: a control word handed to the library's
                                                     special-case handler (LAB_00126cb0), chosen when
                                                     an operand of a double add is Inf or NaN (the
                                                     DOUBLE_EXPONENT_MASK_SHIFTED test). Fields:
                                                       bits 0-3  = 1: the operation, add (Swerve's single-
                                                                   precision add/subtract use 0x4000001 /
                                                                   0x4000002: 1 add, 2 subtract)
                                                       bit 4     = double precision (absent in Swerve's
                                                                   single versions; the handler tests
                                                                   & 0x10 to build a 64- or 32-bit result)
                                                       0x04000000 = which special case; the finite path
                                                                   passes DOUBLE_ADD_FINITE_OPERANDS_CODE
                                                     GUESS: the exact IEEE exception class each top bit
                                                     stands for. Used in double_add (double add) and
                                                     in its copy inlined into math_polynomial */
#define DOUBLE_ADD_FINITE_OPERANDS_CODE 0x10000011u  /* was DAT_00124e0c (word at 0x00124E0C), next to
                                                     DOUBLE_ADD_NONFINITE_OPERAND_CODE: the control word
                                                     for the same special-case handler when both
                                                     operands of the double add are finite (chosen
                                                     where the exponents are aligned, LAB_001249ac).
                                                     Same low bits (1 = add, 0x10 = double precision),
                                                     special-case bit 0x10000000 instead of 0x04000000.
                                                     GUESS: which IEEE exception class that bit stands
                                                     for (for finite operands, presumably overflow /
                                                     inexact). Used in double_add (add),
                                                     double_reverse_subtract and double_subtract
                                                     (subtract, through the same add core) and the copy
                                                     inlined into math_polynomial */
#define FLOAT_DEFAULT_NAN            0x7FC00000u  /* was _UNK_00126d40 (word at 0x00126D40) and
                                                     DAT_00126244 (word at 0x00126244) */
#define DOUBLE_DEFAULT_NAN_HIGH_WORD 0x7FF80000u  /* was _UNK_00126d44 (word at 0x00126D44) and
                                                     DAT_00126240 (word at 0x00126240) */
#define DOUBLE_DEFAULT_NAN_LOW_WORD  0x00000000u  /* was DAT_0012623c (word at 0x0012623C); the first
                                                     copy loads the low word as `mov r0, #0` */
                                             /* second copy: the library pool at 0x00126228..0x00126247,
                                                next to the overflow results 0x7FF00000 (double
                                                infinity, high word), 0x7FEFFFFF:FFFFFFFF (largest
                                                double), 0x7F800000 (float infinity) and 0x7F7FFFFF
                                                (largest float). There the NaN keeps the operand's
                                                sign: FLOAT_DEFAULT_NAN | sign, or
                                                DOUBLE_DEFAULT_NAN_HIGH_WORD | sign : LOW_WORD */
                                             /* the IEEE-754 default (quiet) NaN, single precision
                                                0x7FC00000 and the high word of the double
                                                0x7FF80000_00000000 (low word 0): what the soft-float
                                                library returns for an invalid operation. Loaded by the
                                                exit of its special-case handler at 0x00126D30:
                                                  ldreq r0, =0x7FC00000   ; single: r0 = NaN
                                                  ldrne r1, =0x7FF80000   ; double: r1 = high word
                                                  movne r0, #0            ;         r0 = low word
                                                  mov   pc, lr
                                                selected by bit 0x10 of the control word (e.g.
                                                DOUBLE_ADD_NONFINITE_OPERAND_CODE). Ghidra's _UNK_
                                                prefix: the words sit in a code area and were never
                                                defined as data */
/* Literal-pool data the code takes the address of (so: objects, not #defines). */
extern float64 ZERO_DOUBLE;                 /* was DAT_001007b4: the IEEE-754 double 0.0, two zero words
                                               at 0x001007B4..0x001007BB. math_acos (GUESS: acos)
                                               returns it for x == 1: `adr r1, ZERO_DOUBLE;
                                               ldmia r1, {r0, r1}` loads both words as the result */
extern float64 NAN_DOUBLE;                  /* was DAT_001007bc: the IEEE-754 double quiet NaN
                                               0x7FF80000_00000001 (low word 1, high 0x7FF80000) at
                                               0x001007BC..0x001007C3. math_acos (GUESS: acos)
                                               returns it for |x| > 1, after errno = EDOM */


/* AEEHelperFuncs pointer stored by khvcemu (and the real BREW loader) at module base - 4. */
extern AEEHelperFuncs *g_pHelperFuncs;   /* 0x000FFFFC */

/* ---- prototypes, address order ---------------------------------------------------- */

/* Named functions (entry points, SDK glue, helper wrappers, identified game code). */
int AEEMod_Load(IShell *pIShell,AEEHelperFuncs *ph,IModule **ppMod);   /* 0x00100000 */
boolean AEEApplet_New(int16 nIn,AEECLSID clsID,IShell *pIShell,IModule *pIModule,IApplet **ppobj, void *pAppHandleEvent,void *pFreeAppData);   /* 0x00101760 */
uint32 AEEApplet_Release(IApplet *po);   /* 0x00101898 */
int AEEMod_CreateInstance(IModule *po,IShell *pIShell,AEECLSID ClsId,void **ppObj);   /* 0x00101998 */
uint32 AEEMod_Release(IModule *po);   /* 0x001019CC */
int AEEStaticMod_New(int16 nSize,IShell *pIShell,AEEHelperFuncs *ph,IModule **ppMod,void *pfnMC, void *pfnMF);   /* 0x00101A18 */
void helper_free(void *p);   /* 0x0010C290 */
void * helper_malloc(uint32 size);   /* 0x0010CF4C */
void * helper_malloc_2(uint32 size);   /* 0x0010CF64 */
int32 * kh_GetErrnoPtr(void);   /* 0x0010CF7C GUESS: name, see kh_mod.c */
uint32 * kh_GetFpStatusPtr(void);   /* 0x0010CFA0 */
boolean kh_HandleEvent(KHApp *pMe,AEEEvent eCode,uint16 wParam,uint32 dwParam);   /* 0x0010E060 */
void kh_OnAppStop(KHApp *pMe);   /* 0x001127E0 */
void kh_OnAppStart(KHApp *pMe);   /* 0x00119678 */
void kh_OnKey(KHApp *pMe,AEEEvent eCode,uint16 wParam,uint32 dwParam);   /* 0x0011A804 */
void kh_OnKeyRelease(void *pGame,uint16 wParam);   /* 0x0011AA6C */

/* No Ghidra function exists for these; bodies are hand-written in the .c file. */
uint32 AEEApplet_AddRef(IApplet *po);
boolean AEEApplet_HandleEvent(IApplet *po, AEEEvent evt, uint16 wParam, uint32 dwParam);
int32 AEEClsCreateInstance(AEECLSID ClsId, IShell *pIShell, IModule *po, void **ppObj);
uint32 AEEMod_AddRef(IModule *po);
void AEEMod_FreeResources(IModule *po, IHeap *ph, IFileMgr *pfm);

/* Not yet identified (auto-named by Ghidra). */
int32 engine_memory_set_caching(ISwerve *swerve,int32 mode);   /* 0x00100028 GUESS: name, see kh_mod.c */
int32 rt_div0(int32 divisor);   /* 0x00100104 GUESS: name (ARM's __rt_div0), see kh_mod.c */
void * memset(void *destination,uint32 byteCount);   /* 0x00100110 GUESS: name, see kh_mod.c */
uint64 memcpy(void *destination,void *source,uint32 byteCount);   /* 0x00100168 GUESS: name, see kh_mod.c */
uint64 memcpy_word_aligned(void *destination,void *source,uint32 byteCount);   /* 0x0010021C GUESS: name, see kh_mod.c */
uint64 rt_sdiv(int32 divisor,int32 dividend);   /* 0x00100288 GUESS: name (ARM's __rt_sdiv), see kh_mod.c */
uint64 rt_udiv(uint32 divisor,uint32 dividend);   /* 0x0010035C GUESS: name (ARM's __rt_udiv), see kh_mod.c */
float64 math_acos(float64 x);   /* 0x0010041C GUESS: name, see kh_mod.c */
float64 math_cos(float64 x);   /* 0x001007F4 GUESS: name, see kh_mod.c */
float64 math_sin(float64 x);   /* 0x001008D0 GUESS: name, see kh_mod.c */
float64 math_sqrt(float64 x);   /* 0x001009B8 GUESS: name, see kh_mod.c */
/* errno values of ARM's C library that kh.mod sets (set_errno) */
#define ERRNO_EDOM 1   /* an argument outside the function's domain */
int32 * set_errno(int32 value);   /* 0x00100A38 GUESS: name, see kh_mod.c */
int32 rt_div0_raise(void);   /* 0x00100A4C (no Ghidra function) GUESS: name, see kh_mod.c */
float64 math_kernel_cos(float64 x,float64 y);   /* 0x00100A58 GUESS: name, see kh_mod.c */
float64 math_polynomial(const float64 *table,int32 count,float64 x);   /* 0x00100C2C GUESS: name, see kh_mod.c */
int32 math_rem_pio2(float64 x,float64 *y);   /* 0x00100D88 GUESS: name, see kh_mod.c */
float64 math_kernel_sin(float64 x,float64 y,int32 tail);   /* 0x00101268 GUESS: name, see kh_mod.c */
float64 float_raise_exception(uint32 aLow,uint32 aHigh,uint32 bLow,uint32 bHigh,uint32 control);   /* 0x001013E0 GUESS: name, see kh_mod.c */
int32 raise_signal_and_exit(int32 signal,int32 type);   /* 0x00101440 GUESS: name, see kh_mod.c */
int32 raise_signal(int32 signal,int32 type);   /* 0x00101458 GUESS: name, see kh_mod.c */
int32 semihosting_exit(void);   /* 0x001014BC (no Ghidra function) */
int32 default_signal_handler(int32 signal,int32 type);   /* 0x001014D4 (no Ghidra function) */
int32 debug_write_char(char character);   /* 0x00101638 GUESS: name, see kh_mod.c */
int software_interrupt(int number);      /* Ghidra's name for the `svc` (swi) instruction, not a function:
                                            the trap with the given number, its result as r0 leaves it */
undefined4 FUN_00101ad8(int *param_1,int param_2);
void FUN_001051d4(int param_1,int param_2);
int32 ui_element_set_focus(UIElement *element,Screen *screen);   /* 0x00105224 GUESS: name, see kh_mod.c */
int32 hud_show_text(Hud *hud,AECHAR *text,int32 left,int32 top,int32 right,int32 bottom,int32 tailX,int32 tailY,int32 slot);   /* 0x001052E0 GUESS: name, see kh_mod.c */
int32 menu_add_buttons(ScreenStack *stack,Screen *screen,int32 count,const int32 *textIds,const int32 *selectEvents,const int32 *ids,int32 type,int32 x,int32 y,int32 width,int32 height,int32 gap,int32 vertical);   /* 0x001053A8 GUESS: name, see kh_mod.c */
int32 ui_element_add_child(UIElement *parent,UIElement *child,int32 id);   /* 0x001054D8 GUESS: name */
void hud_show_scrolling_text(int param_1,undefined4 param_2,int param_3);   /* 0x00105538 GUESS: name, see kh_mod.c */
void screen_add_heading(ScreenStack *stack,UIElement *screen,uint32 color,int32 titleId,int32 bodyId);   /* 0x001055C4 GUESS: name, see kh_mod.c */
int32 hud_show_loading(Hud *hud,uint32 color);   /* 0x001056D0 GUESS: name, see kh_mod.c */
int32 ui_element_set_key_target(UIElement *element,int32 keyCode,UIElement *target);   /* 0x001056EC GUESS: name, see kh_mod.c */
void key_picker_restore_original(UIElement *picker);   /* 0x001056F4 GUESS: name */
void web_request_parse_reply(WebRequest *caller,WebRequest *request);   /* 0x00105734 GUESS: name, see kh_mod.c */
void FUN_00105c5c(int param_1);
void text_line_destroy(TextLine *line);   /* 0x00105D48 GUESS: name, see kh_mod.c */
void FUN_00105d7c(int param_1);
void FUN_00105dc8(int param_1);
void web_request_read(WebRequest *request);   /* 0x00105E44 GUESS: name, see kh_mod.c */
void web_request_download(WebRequest *request,char *fileName,int32 position,char *userId,int32 time);   /* 0x00106130 GUESS: name, see kh_mod.c */
void web_request_cancel(WebRequest *request,WebRequest *pending);   /* 0x00106354 GUESS: name, see kh_mod.c */
void hud_draw(Hud *hud,IDisplay *display,IGraphics *graphics);   /* 0x00106398 GUESS: name, see kh_mod.c */
void text_box_draw(TextBox *box,IDisplay *display,IGraphics *graphics);   /* 0x0010673C GUESS: name, see kh_mod.c */
void text_line_draw(TextLine *line,IDisplay *display);   /* 0x00106A94 GUESS: name, see kh_mod.c */
void menu_item_draw(UIElement *item,IDisplay *display,IGraphics *graphics);   /* 0x00106BD4 GUESS: name, see kh_mod.c */
void screen_draw(Screen *screen,IDisplay *display,IGraphics *graphics);   /* 0x00106E44 GUESS: name, see kh_mod.c */
void text_box_draw_scroll_bar(TextBox *box,IDisplay *display,IGraphics *graphics);   /* 0x00106FB0 GUESS: name, see kh_mod.c */
void menu_item_draw_over_children(UIElement *item,IDisplay *display,IGraphics *graphics);   /* 0x00107230 GUESS: name, see kh_mod.c */
void hud_draw_gauge(Hud *hud,IGraphics *graphics,int32 side,int32 value,int32 maximum,int32 fullScale, int32 lowThreshold);   /* 0x001077D0 GUESS: name, see kh_mod.c */
void ui_element_draw_box(UIElement *element,int32 mode,IDisplay *display,IGraphics *graphics,AEERect *rect, uint32 lineColour,uint32 fillColour,int16 cut);   /* 0x00107ADC GUESS: name, see kh_mod.c */
int32 ui_element_draw(UIElement *element);   /* 0x00107D24 GUESS: name, see kh_mod.c */
void web_request_free_buffers(WebRequest *caller,WebRequest *request);   /* 0x00107E48 GUESS: name, see kh_mod.c */
int32 list_get_entry(UIList *list,int32 index);   /* 0x00107EA4 GUESS: name, see kh_mod.c */
int32 ui_element_find_child(UIElement *element,int32 id);   /* 0x00107EC4 GUESS: name */
AECHAR * integer_to_wide(int32 owner,int32 value);   /* 0x00107ECC GUESS: name, see kh_mod.c */
int32 text_box_get_content_height(TextBox *box);   /* 0x00107F88 GUESS: name, see kh_mod.c */
uint64 screen_stack_scale(ScreenStack *stack,int32 amount,int32 axis);   /* 0x00107FD0 GUESS: name, see kh_mod.c */
AECHAR * screen_stack_get_text(ScreenStack *stack,int32 textId);   /* 0x00107FEC GUESS: name, see kh_mod.c */
int32 screen_stack_top(ScreenStack *stack);   /* 0x001080AC GUESS: name */
int32 list_find_entry(UIList *list,int32 id);   /* 0x001080C8 GUESS: name */
void web_request_post_rank_ex(WebRequest *request,char *userId,char *levelId,char *score,int32 time, int32 value);   /* 0x0010810C GUESS: name, see kh_mod.c */
void web_request_post_rank(WebRequest *request,int32 state,char *userId,int32 score,char *levelId,int32 time, int32 value,char *text);   /* 0x001082E0 GUESS: name, see kh_mod.c */
int32 screen_stack_handle_key(ScreenStack *stack,int32 eventCode,int32 keyCode,int32 keyParameter);   /* 0x001083D8 GUESS: name, see kh_mod.c */
undefined4 FUN_00108414(int param_1,undefined4 param_2,int param_3);
int32 text_box_handle_key(TextBox *box,int32 eventCode,int32 keyCode);   /* 0x001084E4 GUESS: name, see kh_mod.c */
int32 ui_element_handle_key(UIElement *element,int32 eventCode,int32 keyCode,int32 keyParameter);   /* 0x00108524 GUESS: name */
int32 screen_handle_key(Screen *screen,int32 eventCode,int32 keyCode,int32 keyParameter);   /* 0x0010873C GUESS: name, see kh_mod.c */
void ui_element_move_by(UIElement *element,int16 dy);   /* 0x00108840 GUESS: name, see kh_mod.c */
void FUN_0010888c(int *param_1,void *param_2,int *param_3,void *param_4,void *param_5);
int32 text_box_scroll_down(TextBox *box);   /* 0x00108E8C GUESS: name, see kh_mod.c */
int32 text_box_scroll_up(TextBox *box);   /* 0x00108ED8 GUESS: name, see kh_mod.c */
int32 sound_set_play(SoundSet *set,int32 index);   /* 0x00108F28 GUESS: name, see kh_mod.c */
void screen_stack_close_all(ScreenStack *stack);   /* 0x00108FA0 GUESS: name */
void screen_stack_close_top(ScreenStack *stack,int32 redraw);   /* 0x00108FCC GUESS: name */
void screen_stack_open(ScreenStack *stack,int32 *screen);   /* 0x001090B8 GUESS: name */
int32 list_set_entry(UIList *list,int32 id,int32 entry);   /* 0x001090FC GUESS: name */
void web_request_retry(WebRequest *request);   /* 0x001091FC GUESS: name, see kh_mod.c */
void hud_remove_text(Hud *hud,int32 slot);   /* 0x001092C0 GUESS: name, see kh_mod.c */
int32 ui_element_remove_child(UIElement *element,int32 id,int32 destroy);   /* 0x00109308 GUESS: name */
void hud_hide_loading(Hud *hud);   /* 0x00109368 GUESS: name, see kh_mod.c */
void list_remove_entry(UIList *list,int32 id);   /* 0x00109380 GUESS: name */
void thunk_FUN_0011e154(int param_1);
int32 download_write_file(WebRequest *caller,WebRequest *request,const char *name,uint32 size, const void *data);   /* 0x001093F8 GUESS: name, see kh_mod.c */
void web_request_notify(WebRequest *request,int32 event,int32 value,int32 detail,int32 extra);   /* 0x00109534 GUESS: name, see kh_mod.c */
void text_box_set_tail(TextBox *box,int32 x,int32 y);   /* 0x0010955C GUESS: name, see kh_mod.c */
IImage * ui_element_load_image(UIElement *element,const char *fileName);   /* 0x00109750 GUESS: name, see kh_mod.c */
int32 sound_set_load_file(SoundSet *set,const char *fileName,int32 index);   /* 0x00109780 GUESS: name, see kh_mod.c */
void key_picker_setup(UIElement *picker,KeyOption *options,int32 *setting,int32 index);   /* 0x001098D8 GUESS: name */
void hud_set_cinematic(int param_1,int param_2);   /* 0x00109940 GUESS: name, see kh_mod.c */
void screen_set_soft_key(Screen *screen,int32 slot,int32 textId,int32 selectEvent);   /* 0x00109A10 GUESS: name, see kh_mod.c */
int32 text_box_set_text(TextBox *box,AECHAR *text,int32 narrow);   /* 0x00109B4C GUESS: name, see kh_mod.c */
void text_box_set_text_id(TextBox *box,int32 textId);   /* 0x00109F00 GUESS: name, see kh_mod.c */
void text_line_set_text(TextLine *line,AECHAR *text);   /* 0x00109F48 GUESS: name, see kh_mod.c */
void text_line_set_text_id(TextLine *line,int32 textId);   /* 0x00109FF8 GUESS: name, see kh_mod.c */
int32 sound_set_set_volume(SoundSet *set,int32 volume);   /* 0x0010A03C GUESS: name, see kh_mod.c */
void FUN_0010a080(int param_1);
int32 sound_set_stop(SoundSet *set);   /* 0x0010A0D0 GUESS: name, see kh_mod.c */
void game_pause(KHApp *app);   /* 0x0010A124 GUESS: name, see kh_mod.c */
int32 download_save_files(WebRequest *caller,WebRequest *request,const uint8 *bundle);   /* 0x0010A12C GUESS: name, see kh_mod.c */
TextBox * text_box_layout(TextBox *box);   /* 0x0010A214 GUESS: name, see kh_mod.c */
uint32 graphics_set_color(int32 owner,IGraphics *graphics,uint32 color,int32 which);   /* 0x0010A3E8 GUESS: name, see kh_mod.c */
uint32 display_set_color(int32 owner,IDisplay *display,int32 which,uint32 color);   /* 0x0010A46C GUESS: name, see kh_mod.c */
void FUN_0010a498(int param_1,int param_2);
Hitsphere * hitsphere_create(Hitsphere *hitsphere,int32 entity,BossCombatRegion *owner,int32 secondary);   /* 0x0010A528 GUESS: name */
int * FUN_0010a5d8(int *param_1,undefined4 param_2,int *param_3);
int * FUN_0010aa8c(int *param_1,int *param_2);
ScreenStack * screen_stack_create(ScreenStack *stack,KHApp *app);   /* 0x0010AC6C GUESS: name, see kh_mod.c */
WebRequest * web_request_create(WebRequest *request,int32 context,WebRequestListener listener);   /* 0x0010AF3C GUESS: name, see kh_mod.c */
ScriptCommand * script_command_create(ScriptCommand *command);   /* 0x0010AFC4 GUESS: name, see kh_mod.c */
ItemDrops * item_drops_create(ItemDrops *drops,uint32 munnyPerPickup);   /* 0x0010B014 GUESS: name, see kh_mod.c */
ScriptSequence * script_sequence_create(ScriptSequence *sequence,char *text);   /* 0x0010B080 GUESS: name, see kh_mod.c */
Enemy * enemy_create(Enemy *enemy,int32 number,CombatRegion *region,int32 type);   /* 0x0010B230 GUESS: name */
TextBox * text_box_create(TextBox *box,int32 x,int32 y,int32 width,int32 height,int32 *owner,TextStyle *style);   /* 0x0010B2DC GUESS: name, see kh_mod.c */
Camera * camera_create(Camera *camera,ISwerveObject *node,char *name);   /* 0x0010B3E8 GUESS: name, see kh_mod.c */
CombatRegion * combat_region_create(CombatRegion *region,ISwerveObject *node,char *name);   /* 0x0010B478 GUESS: name */
Progress * progress_create(Progress *progress,int32 skipSetup);   /* 0x0010B4E4 GUESS: name, see kh_mod.c */
MotionEntity * motion_entity_create(MotionEntity *entity,ISwerveObject *node,char *name);   /* 0x0010B5E8 GUESS: name */
TextLine * text_line_create(TextLine *line,int32 x,int32 y,int32 width,int32 height,int32 *owner,int32 textId, uint32 alignment);   /* 0x0010B650 GUESS: name, see kh_mod.c */
Character * character_create(Character *character,ISwerveObject *node,char *name);   /* 0x0010B70C GUESS: name, see kh_mod.c */
Animations * animations_create(Animations *animations);   /* 0x0010B804 GUESS: name */
BossCombatRegion * boss_combat_region_create(BossCombatRegion *region,ISwerveObject *node,char *name);   /* 0x0010B870 GUESS: name */
LevelObject * level_object_create(LevelObject *object,ISwerveObject *node,char *name);   /* 0x0010B8CC GUESS: name */
CollisionShape * collision_shape_create(CollisionShape *shape);   /* 0x0010B9B4 GUESS: name */
TextStyle * text_style_create(TextStyle *style,int32 type);   /* 0x0010BA08 GUESS: name, see kh_mod.c */
Intro * intro_create(Intro *intro,int32 atTitle,int32 *error);   /* 0x0010BB2C GUESS: names */
UIElement * menu_item_create(UIElement *item,int32 x,int32 y,int32 width,int32 height,int32 *owner, int32 type,int32 selectEvent,uint8 enabled);   /* 0x0010BBA0 GUESS: name, see kh_mod.c */
Screen * screen_create(Screen *screen,ScreenStack *stack,uint8 framed);   /* 0x0010BD7C GUESS: name, see kh_mod.c */
TextTable * text_table_create(TextTable *table);   /* 0x0010BE14 GUESS: name, see kh_mod.c */
UIList * list_create(UIList *list,int32 capacity,int32 growBy);   /* 0x0010BE6C GUESS: name, see kh_mod.c */
undefined8 sound_set_create(int *param_1,int param_2,int param_3,int param_4);   /* 0x0010BEC4 GUESS: name: a SoundSet (see kh_types.h) */
UIElement * ui_element_create(UIElement *element,int16 x,int16 y,int16 width,int16 height,int32 *owner);   /* 0x0010C168 GUESS: name, see kh_mod.c */
AppContext * app_context_create(AppContext *context,int32 *error);   /* 0x0010C218 GUESS: name, see kh_mod.c */
void hitsphere_destroy(Hitsphere *hitsphere,int32 freeIt);   /* 0x0010C2A8 GUESS: name, see kh_mod.c */
void FUN_0010c2c4(int *param_1,int param_2);
void screen_stack_destroy(ScreenStack *stack,int32 freeIt);   /* 0x0010C3F8 GUESS: name, see kh_mod.c */
void web_request_destroy(WebRequest *request,int32 freeIt);   /* 0x0010C598 GUESS: name, see kh_mod.c */
void script_command_destroy(ScriptCommand *command,int32 freeIt);   /* 0x0010C620 GUESS: name, see kh_mod.c */
void item_drops_destroy(ItemDrops *drops,int32 freeSelf);   /* 0x0010C66C GUESS: name, see kh_mod.c */
void script_sequence_destroy(ScriptSequence *sequence,int32 freeIt);   /* 0x0010C6B4 GUESS: name, see kh_mod.c */
void enemy_destroy(Enemy *enemy,int32 freeIt);   /* 0x0010C720 GUESS: name, see kh_mod.c */
void camera_destroy(int param_1,int param_2);   /* 0x0010C73C GUESS: name, see kh_mod.c */
void combat_region_destroy(CombatRegion *region,int32 freeIt);   /* 0x0010C790 GUESS: name, see kh_mod.c */
void progress_destroy(Progress *progress,int32 freeSelf);   /* 0x0010C800 GUESS: name, see kh_mod.c */
void motion_entity_destroy(MotionEntity *entity,int32 freeIt);   /* 0x0010C8B8 GUESS: name, see kh_mod.c */
void character_destroy(int param_1,int param_2);   /* 0x0010C92C GUESS: name, see kh_mod.c */
void animations_destroy(Animations *animations,int32 freeIt);   /* 0x0010C9DC GUESS: name, see kh_mod.c */
void boss_combat_region_destroy(BossCombatRegion *region,int32 freeIt);   /* 0x0010CA1C GUESS: name, see kh_mod.c */
void level_object_destroy(int param_1,int param_2);   /* 0x0010CAB0 GUESS: name: a LevelObject's destructor (see kh_types.h) */
void collision_shape_destroy(CollisionShape *shape,int32 freeIt);   /* 0x0010CC9C GUESS: name, see kh_mod.c */
void intro_destroy(Intro *intro,int32 freeIt);   /* 0x0010CD2C GUESS: name, see kh_mod.c */
void text_table_destroy(TextTable *table,int32 freeIt);   /* 0x0010CDA4 GUESS: name, see kh_mod.c */
void list_destroy(UIList *list,int32 freeIt);   /* 0x0010CDD8 GUESS: name, see kh_mod.c */
void screen_resume_nothing(int32 screen);   /* 0x001052DC (no Ghidra function; a virtual method) */
void text_box_destroy(TextBox *box);   /* 0x00105C98 GUESS: name, see kh_mod.c */
void ui_element_destroy(UIElement *element);   /* 0x00105DE4 (no Ghidra function; a virtual method) */
void ui_element_draw_nothing(int32 element,int32 display,int32 graphics);   /* 0x00106FA8 (no Ghidra function; a virtual method) */
void ui_element_update_nothing(int32 element,int32 now,int32 elapsed);   /* 0x00106FAC (no Ghidra function; a virtual method) */
void ui_element_draw_over_children_nothing(int32 element,int32 display,int32 graphics);   /* 0x001077CC (no Ghidra function; a virtual method) */
uint32 ui_element_get_border_color(UIElement *element);   /* 0x00107F58 (no Ghidra function; a virtual method) */
uint32 ui_element_get_secondary_color(UIElement *element);   /* 0x00108048 (no Ghidra function; a virtual method) */
uint32 ui_element_get_primary_color(UIElement *element);   /* 0x0010807C (no Ghidra function; a virtual method) */
int32 screen_handle_key_nothing(int32 screen,int32 eventCode,int32 keyCode);   /* 0x0010872C (no Ghidra function; a virtual method) */
int32 ui_element_handle_key_nothing(int32 element,int32 eventCode,int32 keyCode);   /* 0x00108734 (no Ghidra function; a virtual method) */
uint32 enemy_get_health(Enemy *enemy);   /* 0x001136C0 (no Ghidra function; a virtual method) */
int32 enemy_is_waiting(Enemy *enemy);   /* 0x00119AF4 (no Ghidra function; a virtual method) */
void enemy_enter_mode_3(Enemy *enemy);   /* 0x0011F260 (no Ghidra function; a virtual method) */
void enemy_enter_mode_2(Enemy *enemy);   /* 0x0011F26C (no Ghidra function; a virtual method) */
void enemy_enter_mode_1(Enemy *enemy);   /* 0x0011F624 (no Ghidra function; a virtual method) */
void sound_set_destroy(SoundSet *set,int32 freeIt);   /* 0x0010CE08 GUESS: name, see kh_mod.c */
void app_context_destroy(AppContext *context,int32 freeIt);   /* 0x0010CEE4 GUESS: name, see kh_mod.c */
void progress_add_experience(Progress *progress,int32 amount);   /* 0x0010CFC4 GUESS: name */
void FUN_0010d074(int param_1,undefined4 param_2);
void progress_add_magic_points(Progress *progress,int32 amount);   /* 0x0010D18C GUESS: name */
void progress_add_munny(Progress *progress,int32 amount);   /* 0x0010D1E0 GUESS: name */
int32 combat_region_all_enemies_defeated(CombatRegion *region);   /* 0x0010D2FC GUESS: names */
int32 combat_region_all_enemies_waiting(CombatRegion *region);   /* 0x0010D354 GUESS: name, see kh_mod.c */
void kh_show_error(KHApp *app,int32 error);   /* 0x0010D3A4 GUESS: name, see kh_mod.c */
uint32 string_to_float(int32 context,char *text);   /* 0x0010D4DC GUESS: name, see kh_mod.c */
undefined4 FUN_0010d56c(int param_1,int param_2);
undefined4 FUN_0010d7c4(int param_1,int param_2);
undefined4 FUN_0010d95c(int param_1,int param_2);
void FUN_0010db04(int param_1,undefined4 param_2);
int32 progress_score(Progress *progress);   /* 0x0010E1F8 GUESS: name */
AECHAR * string_to_wide(int32 context,char **text,AECHAR **wide);   /* 0x0010E210 GUESS: name, see kh_mod.c */
void camera_avoid_walls(Camera *camera,uint32 *from,uint32 *to);   /* 0x0010E280 GUESS: names */
undefined4 motion_entity_block_move(int param_1,undefined4 *param_2);   /* 0x0010E448 GUESS: name, see kh_mod.c */
void thunk_animations_add_from_scene(int param_1,int *param_2);
void animations_drop_missing(Animations *animations);   /* 0x0010E94C GUESS: name, see kh_mod.c */
int32 animations_release_controllers(Animations *animations);   /* 0x0010E9BC GUESS: name */
void screen_clear(Screen *screen);   /* 0x0010EA00 GUESS: name, see kh_mod.c */
void FUN_0010ea64(int param_1);
undefined4 FUN_0010eb74(int param_1);
void motion_entity_rotate_by_heading(MotionEntity *entity,uint32 *vector);   /* 0x0010ECB8 GUESS: name, see kh_mod.c */
uint32 float_cos(uint32 angle);   /* 0x0010ED40 GUESS: name, see kh_mod.c */
void FUN_0010ed54(int param_1,int param_2,undefined4 param_3);
void FUN_0010f1fc(int32 character);   /* 0x0010F1FC (no Ghidra function) */
void FUN_0010edec(int param_1);
int32 script_parse_lines(int32 context,char *text,ScriptCommand ***commands,int32 owner);   /* 0x0010EEFC GUESS: name, see kh_mod.c */
int32 string_remove_prefix(int32 context,const char *prefix,char *text,char *out);   /* 0x0010EFD4 GUESS: name, see kh_mod.c */
int FUN_0010f058(int param_1,int param_2);
void item_drops_get_chances(ItemDrops *drops,uint32 *chances);   /* 0x0010F244 GUESS: name, see kh_mod.c */
int32 combat_region_take_one(CombatRegion *region);   /* 0x0010F2CC GUESS: name */
uint32 enemy_take_hit(Enemy *enemy,int32 targetNumber,uint32 damage,uint32 x,uint32 y,uint32 z,int32 playerState);   /* 0x0010F2E8 GUESS: name, see kh_mod.c */
void FUN_0010f4d0(int param_1,uint param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
                 uint param_6);
void progress_reset(Progress *progress);   /* 0x0010F880 GUESS: name */
void progress_set_default_controls(Progress *progress);   /* 0x0010F8E8 GUESS: name, see kh_mod.c */
void progress_new_game(Progress *progress);   /* 0x0010F9A4 GUESS: name, see kh_mod.c */
int32 enemy_wait(Enemy *enemy,int32 now,int32 duration);   /* 0x0010FA50 GUESS: name */
int32 files_remove_by_prefix(AppContext *context,const char *prefix);   /* 0x0010FAA8 GUESS: name, see kh_mod.c */
void FUN_0010fb90(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_0010fbf4(int *param_1,uint param_2,uint param_3,uint param_4,uint param_5,int param_6,
                 int param_7,uint param_8,uint param_9,uint param_10);
uint32 planar_distance_squared(void *object,uint32 x1,uint32 y1,uint32 z1,uint32 x2,uint32 y2);   /* 0x0010FFDC GUESS: name, see kh_mod.c */
uint32 planar_distance_squared_2(void *object,uint32 x1,uint32 y1,uint32 z1,uint32 x2,uint32 y2);   /* 0x00110030 GUESS: name, see kh_mod.c */
int32 string_split(int32 context,char *text,char *separator,char **parts,int32 maxParts);   /* 0x00110084 GUESS: name, see kh_mod.c */
undefined4 FUN_00110190(int param_1,undefined4 *param_2,undefined4 *param_3);
void character_drop(Character *character,int32 notBehind,LevelObject *target);   /* 0x00110564 GUESS: name, see kh_mod.c */
int32 script_run_if_block(int32 context,int32 *index,int32 holds,ScriptCommand **commands);   /* 0x001106A0 GUESS: name, see kh_mod.c */
int32 level_object_run_script(LevelObject *object,int32 which);   /* 0x00110860 GUESS: name, see kh_mod.c */
int32 script_run(int32 context,int32 count,ScriptCommand **commands);   /* 0x001108AC GUESS: name, see kh_mod.c */
int32 script_command_run(ScriptCommand *command);   /* 0x00110924 GUESS: name, see kh_mod.c */
undefined8 FUN_0011295c(undefined4 *param_1,int *param_2,int *param_3,int *param_4,undefined4 param_5);
bool progress_file_exists(int param_1,undefined4 param_2,int param_3);   /* 0x00112A98 GUESS: name, see kh_mod.c */
void intro_find_animations(Intro *intro);   /* 0x00112B4C GUESS: name, see kh_mod.c */
int32 item_drops_find_free_slot(ItemDrops *drops);   /* 0x00112C18 GUESS: name */
void item_drops_find_balls(ItemDrops *drops);   /* 0x00112C44 GUESS: name, see kh_mod.c */
Hitsphere * boss_combat_region_find_hitsphere(BossCombatRegion *region,int32 entity);   /* 0x00112C9C GUESS: name */
undefined8 FUN_00112cdc(int param_1,int *param_2,int param_3);
int32 game_find_free_object_slot(Game *game);   /* 0x00112CFC GUESS: name */
int32 animations_find_free_slot(Animations *animations);   /* 0x00112D28 GUESS: name */
int32 progress_find_free_status(Progress *progress);   /* 0x00112D54 GUESS: name, see kh_mod.c */
LevelObject * game_find_object(Game *game,uint32 nameId);   /* 0x00112DBC GUESS: name, see kh_mod.c */
LevelObject * script_command_find_object(ScriptCommand *command,const char *name);   /* 0x00112E20 GUESS: name, see kh_mod.c */
int32 enemy_fit_walk(Enemy *enemy);   /* 0x00112E84 GUESS: name, see kh_mod.c */
void FUN_00113030(int param_1,undefined4 param_2,uint param_3,uint param_4,undefined4 param_5);
void FUN_0011316c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,int param_9,undefined4 param_10,undefined4 param_11);
void FUN_001132a8(int param_1);
void FUN_00113340(int param_1);
uint32 direction_to(void *context,uint32 x1,uint32 y1,uint32 x2,uint32 y2);   /* 0x00113374 GUESS: names */
void FUN_00113474(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5);
void hitsphere_get_player_point(uint32 *point,Hitsphere *hitsphere);   /* 0x00113490 GUESS: name, see kh_mod.c */
void enemy_get_player_point(uint32 *point,Enemy *enemy);   /* 0x00113524 GUESS: name, see kh_mod.c */
int32 animations_get_duration(Animations *animations,int32 index);   /* 0x001135B8 GUESS: name */
void camera_find_target(Camera *camera);   /* 0x001135DC GUESS: name, see kh_mod.c */
uint32 string_hash(int32 context,const char *text);   /* 0x00113654 GUESS: name, see kh_mod.c */
int32 level_object_get_surface(LevelObject *object,uint32 x,uint32 y,uint32 *bottom,uint32 *top,uint32 radius);   /* 0x001136C8 GUESS: name, see kh_mod.c */
uint32 level_object_get_height(LevelObject *object);   /* 0x00113784 GUESS: name */
int32 animations_find(Animations *animations,int32 userId);   /* 0x001137A4 GUESS: name */
uint32 vector_length(void *context,uint32 *vector);   /* 0x001137D4 GUESS: name, see kh_mod.c */
uint32 vector_length3(void *context,uint32 x,uint32 y,uint32 z);   /* 0x00113820 GUESS: name, see kh_mod.c */
void FUN_0011386c(uint param_1,int param_2);
void level_object_get_position(uint32 *position,LevelObject *object);   /* 0x00113CC4 GUESS: name */
uint8 animations_get_priority(Animations *animations,int32 index);   /* 0x00113CD4 GUESS: name */
uint32 * random_floats(int32 context,int32 count);   /* 0x00113CFC GUESS: name, see kh_mod.c */
int32 collision_shape_turn_direction(CollisionShape *shape,uint32 x1,uint32 y1,uint32 x2,uint32 y2,uint32 heading);   /* 0x00113DA4 GUESS: name, see kh_mod.c */
int32 progress_find_record(Progress *progress,const char *name,int32 *best,int32 *second);   /* 0x00114120 GUESS: name, see kh_mod.c */
uint8 progress_get_status(Progress *progress,const char *name);   /* 0x00114198 GUESS: name, see kh_mod.c */
uint8 animations_get_state(Animations *animations,int32 index);   /* 0x001141F4 GUESS: name */
int32 text_table_get_text(TextTable *table,int32 textId,char **text);   /* 0x0011421C GUESS: name, see kh_mod.c */
undefined4 FUN_00114240(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 *param_6,int param_7,undefined4 param_8,int param_9);
void vector_normalize(void *context,uint32 *vector);   /* 0x0011442C GUESS: name, see kh_mod.c */
int FUN_0011448c(undefined4 param_1,int *param_2,undefined4 param_3,undefined4 *param_4);
void FUN_00114520(undefined4 param_1,int *param_2,undefined4 param_3,undefined4 *param_4);
void FUN_001145b4(int param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4);
void FUN_00114610(int param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4);
int32 boss_combat_region_pick_marker(BossCombatRegion *region);   /* 0x00114638 GUESS: name, see kh_mod.c */
int32 * progress_find_variable(Progress *progress,const char *name);   /* 0x001146F0 GUESS: name, see kh_mod.c */
int32 level_object_is_visible(LevelObject *object);   /* 0x00114750 GUESS: name, see kh_mod.c */
void text_table_get_wide_text(TextTable *table,int32 textId,AECHAR **text);   /* 0x00114774 GUESS: name, see kh_mod.c */
void FUN_001147ec(undefined4 *param_1,int param_2,int *param_3);
uint32 motion_entity_get_pitch(MotionEntity *entity);   /* 0x00114898 GUESS: name */
uint32 motion_entity_get_heading(MotionEntity *entity);   /* 0x001148A0 GUESS: name */
int32 animations_rewind(Animations *animations,int32 index);   /* 0x001148A8 GUESS: name, see kh_mod.c */
int32 animations_finish(Animations *animations,int32 index);   /* 0x001148C8 GUESS: name */
int32 combat_region_take_attack_token(CombatRegion *region);   /* 0x00114910 GUESS: names */
void character_stop_animations(Character *character);   /* 0x0011492C GUESS: name, see kh_mod.c */
void FUN_0011498c(int param_1,uint param_2);
void FUN_00114a1c(int param_1,undefined4 param_2);
int32 combat_region_hit_enemies(CombatRegion *region,int32 targetNumber,uint32 damage,uint32 x,uint32 y,uint32 z,int32 playerState);   /* 0x00114A94 GUESS: names */
int32 boss_combat_region_hit_target(BossCombatRegion *region,int32 targetNumber,uint32 damage,uint32 x,uint32 y,uint32 z,int32 playerState);   /* 0x00114B48 GUESS: name */
void FUN_00114c00(int param_1,undefined4 param_2,undefined4 param_3,int param_4);
void FUN_001150d0(int param_1,int *param_2);
void script_command_parse(ScriptCommand *command,int32 owner,char *text);   /* 0x00115118 GUESS: name, see kh_mod.c */
void enemy_setup_type(int param_1,undefined4 param_2);   /* 0x001174AC GUESS: name, see kh_mod.c */
void FUN_00117d30(int param_1,int *param_2);
void combat_region_setup(CombatRegion *region,int32 context);   /* 0x00117DD8 GUESS: name */
undefined8 motion_entity_setup(int param_1,uint param_2);   /* 0x001180C4 GUESS: name, see kh_mod.c */
void character_setup(Character *character,int32 *error);   /* 0x00118318 GUESS: name */
void FUN_00118640(int param_1,int *param_2);
void boss_combat_region_setup(int param_1,undefined4 param_2);   /* 0x0011868C GUESS: name, see kh_mod.c */
void FUN_00118910(int param_1,undefined4 param_2);
void collision_shape_setup(CollisionShape *shape,ISwerveObject *node,char *text);   /* 0x00118ED8 GUESS: name */
void intro_start(Intro *intro);   /* 0x001195F8 GUESS: name */
void FUN_00119a28(int param_1,int *param_2);
int32 screen_stack_all_keys_bound(ScreenStack *stack);   /* 0x00119ABC GUESS: name, see kh_mod.c */
undefined8 FUN_00119b0c(undefined4 param_1,int param_2,undefined4 param_3);
int32 level_object_allows(LevelObject *object,uint32 x,uint32 y,uint32 z,uint32 radius,uint32 height);   /* 0x00119C10 GUESS: name, see kh_mod.c */
CollisionShape * game_find_blocking_shape(Game *game,uint32 x,uint32 y,uint32 z);   /* 0x00119C60 GUESS: name, see kh_mod.c */
CollisionShape * level_object_find_blocking_shape(LevelObject *object,uint32 x,uint32 y,uint32 z,uint32 radius,uint32 height);   /* 0x00119CE0 GUESS: name, see kh_mod.c */
uint32 collision_shape_allows(CollisionShape *shape,uint32 x,uint32 y,uint32 z,uint32 radius,uint32 height);   /* 0x00119D58 GUESS: name, see kh_mod.c */
void combat_region_update_turns(CombatRegion *region,int32 now);   /* 0x0011A2F4 GUESS: name, see kh_mod.c */
void FUN_0011a3ec(int param_1,int param_2,undefined4 param_3);
void character_on_key(Character *character,int32 key);   /* 0x0011A4D8 GUESS: name */
void intro_on_key(Intro *intro,int32 key);   /* 0x0011A7DC GUESS: name */
void character_on_key_release(Character *character,int32 key);   /* 0x0011AAD0 GUESS: name */
void character_freeze_held_keys(Character *character);   /* 0x0011AB60 GUESS: name */
undefined8 FUN_0011abc4(int param_1,int param_2);
int32 character_lift(Character *character,LevelObject *object);   /* 0x0011ADD0 GUESS: name, see kh_mod.c */
undefined4 FUN_0011ae04(int param_1,undefined4 param_2,int *param_3,int param_4,int param_5);
void FUN_0011b044(int param_1,undefined4 param_2,int param_3,undefined4 param_4,int param_5, undefined4 *param_6);
int32 progress_read_file(Progress *progress,const char *name,void *buffer,uint32 size);   /* 0x0011B0CC GUESS: name, see kh_mod.c */
undefined4 progress_load(int param_1,int param_2);   /* 0x0011B178 GUESS: name, see kh_mod.c */
undefined8 FUN_0011b518(int param_1,int param_2);
undefined4 records_load(int param_1);   /* 0x0011B5F0 GUESS: name, see kh_mod.c */
void settings_load(int param_1,undefined4 param_2);   /* 0x0011B6F0 GUESS: name, see kh_mod.c */
void intro_load_scene(int param_1,int *param_2);   /* 0x0011B890 GUESS: name, see kh_mod.c */
undefined4 FUN_0011ba0c(int param_1,undefined4 param_2);
int32 sound_entry_on_notify(SoundEntry *entry,AEEMediaCmdNotify *notify);   /* 0x0011BB00 GUESS: name, see kh_mod.c */
int32 sound_set_loop(SoundSet *set,int32 index);   /* 0x0011BB58 GUESS: name, see kh_mod.c */
int FUN_0011bb9c(int param_1,undefined4 *param_2);
uint64 enemy_roam(Enemy *enemy,int32 now,uint32 walkRange);   /* 0x0011C330 GUESS: name, see kh_mod.c */
void FUN_0011c708(int param_1,int param_2,int param_3);
bool FUN_0011c860(int param_1,int param_2,undefined4 param_3);
void FUN_0011ca70(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5);
void FUN_0011ca8c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5);
void wrap_angle(int32 context,uint32 *angle);   /* 0x0011CB34 GUESS: name */
void hitsphere_play_animation(Hitsphere *hitsphere,int32 index,int32 loop);   /* 0x0011CBC4 GUESS: name, see kh_mod.c */
void enemy_play_animation(Enemy *enemy,int32 index,int32 loop);   /* 0x0011CC14 GUESS: name, see kh_mod.c */
int32 character_play_animation(Character *character,int32 index,int32 channel,int32 loop);   /* 0x0011CC64 GUESS: names */
undefined8 FUN_0011ceac(int param_1);
undefined4 app_context_play_music(int param_1,undefined4 param_2,int param_3);   /* 0x0011CFDC GUESS: name, see kh_mod.c */
void FUN_0011d040(int param_1,undefined4 param_2,void *param_3);
int32 animations_play(Animations *animations,int32 index,int32 loop);   /* 0x0011D104 GUESS: names */
int32 collision_shape_poly_contains(CollisionShape *shape,uint32 x,uint32 y);   /* 0x0011D168 GUESS: name, see kh_mod.c */
void FUN_0011d28c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
undefined8 FUN_0011d3ec(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_0011d6cc(int param_1,int param_2);
int FUN_0011daac(int param_1,int param_2,undefined4 param_3,uint param_4);
uint32 save_read_byte(Progress *progress,const uint8 *data,int32 *position);   /* 0x0011DC9C GUESS: name, see kh_mod.c */
uint32 save_read_float(Progress *progress,const uint8 *data,int32 *position);   /* 0x0011DCE8 GUESS: name, see kh_mod.c */
int32 save_read_int(Progress *progress,const uint8 *data,int32 *position);   /* 0x0011DD34 GUESS: name, see kh_mod.c */
char * save_read_string(Progress *progress,const uint8 *data,int32 *position);   /* 0x0011DD80 GUESS: name, see kh_mod.c */
void FUN_0011de04(int param_1,undefined4 *param_2);
void combat_region_release_attack_token(CombatRegion *region);   /* 0x0011DE64 GUESS: name */
void enemy_reset_states(Enemy *enemy);   /* 0x0011DE70 GUESS: name */
void FUN_0011dedc(int param_1);
void FUN_0011df14(undefined4 *param_1);
void progress_clear_states(Progress *progress);   /* 0x0011E010 GUESS: name, see kh_mod.c */
void FUN_0011e07c(int param_1);
void FUN_0011e0b4(int param_1);
void animations_reset(Animations *animations);   /* 0x0011E0FC GUESS: name */
void FUN_0011e154(KHApp *app);
undefined4 FUN_0011e250(int param_1,int param_2);
undefined4 FUN_0011e300(int param_1);
void motion_entity_pitch_by(MotionEntity *entity,uint32 angle);   /* 0x0011E36C GUESS: name */
void motion_entity_turn(MotionEntity *entity,uint32 angle);   /* 0x0011E3C0 GUESS: names */
void motion_entity_start_turn(MotionEntity *entity,uint32 angle,uint32 speed);   /* 0x0011E530 GUESS: name */
int32 progress_write_file(Progress *progress,const char *name,const void *data,uint32 size);   /* 0x0011E574 GUESS: name, see kh_mod.c */
undefined4 progress_save(int param_1,int param_2);   /* 0x0011E6B8 GUESS: name, see kh_mod.c */
undefined4 records_save(int param_1);   /* 0x0011EA18 GUESS: name, see kh_mod.c */
undefined4 settings_save(int param_1,undefined4 param_2);   /* 0x0011EAD4 GUESS: name, see kh_mod.c */
undefined4 FUN_0011ec28(int param_1,int param_2);
void text_expand_key_names(AppContext *context,char **text);   /* 0x0011ED3C GUESS: name, see kh_mod.c */
void combat_region_enemies_enter_mode_2(CombatRegion *region);   /* 0x0011F280 GUESS: name, see kh_mod.c */
void FUN_0011f2bc(int param_1,int *param_2,int param_3);
void FUN_0011f394(int param_1,char *param_2,undefined4 param_3,undefined4 param_4,int param_5);
void FUN_0011f540(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5);
void combat_region_enemies_enter_mode_1(CombatRegion *region);   /* 0x0011F630 GUESS: name, see kh_mod.c */
void character_set_control_direction(Character *character,int32 direction);   /* 0x0011F66C GUESS: name */
void camera_move_focus(Camera *camera,uint32 x,uint32 y,uint32 z,int32 elapsed);   /* 0x0011F680 GUESS: name, see kh_mod.c */
void FUN_0011f7d4(int param_1,int param_2);
void FUN_0011f8ac(int param_1);
void FUN_0011f8e0(int param_1,uint param_2);
void FUN_0011fc80(int param_1,undefined4 param_2);
int32 animations_set_position(Animations *animations,int32 index,int32 position);   /* 0x0011FCC4 GUESS: name */
void thunk_FUN_0011fd90(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_0011fd90(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void animations_set_priority(Animations *animations,int32 index,uint8 priority);   /* 0x0011FDBC GUESS: name */
int32 progress_set_record(Progress *progress,const char *name,int32 best,int32 downloaded);   /* 0x0011FDDC GUESS: name, see kh_mod.c */
void animations_set_speed(Animations *animations,int32 index,uint32 speed);   /* 0x0011FED8 GUESS: name */
void progress_set_status(Progress *progress,const char *name,int32 flag);   /* 0x0011FEF4 GUESS: name, see kh_mod.c */
void FUN_0011ffc0(undefined4 *param_1,undefined4 param_2);
void enemy_set_target(Enemy *enemy,int32 how);   /* 0x00120024 GUESS: names */
void progress_set_user_id(Progress *progress,const char *userId);   /* 0x001200AC GUESS: name, see kh_mod.c */
void progress_set_variable(Progress *progress,const char *name,int32 value);   /* 0x00120120 GUESS: name, see kh_mod.c */
void FUN_001201cc(int param_1,undefined4 param_2);
void motion_entity_set_pitch(MotionEntity *entity,uint32 pitch);   /* 0x00120244 GUESS: name */
void motion_entity_set_heading(MotionEntity *entity,uint32 heading);   /* 0x00120290 GUESS: name, see kh_mod.c */
void camera_set_yaw(Camera *camera,uint32 angle);   /* 0x001202CC GUESS: name, see kh_mod.c */
uint32 float_sin(uint32 angle);   /* 0x001202F4 GUESS: name, see kh_mod.c */
uint32 float_sqrt(uint32 value);   /* 0x00120308 GUESS: name, see kh_mod.c */
void app_context_set_music(int *param_1,int param_2);   /* 0x0012031C GUESS: name, see kh_mod.c */
void app_context_stop_music(AppContext *context);   /* 0x00120450 GUESS: name, see kh_mod.c */
void animations_stop(Animations *animations,int32 index,int32 immediately);   /* 0x001204B0 GUESS: name */
char * string_replace(AppContext *context,const char *text,char **slot);   /* 0x001204F0 GUESS: name, see kh_mod.c */
void FUN_0012056c(int param_1,int param_2);
bool FUN_0012059c(int param_1,int param_2);
void FUN_0012070c(int param_1,int param_2);
void animations_add_from_scene(Animations *animations,ISwerveObject *object);   /* 0x0012088C GUESS: name */
void FUN_00120be8(undefined4 *param_1,int *param_2,uint *param_3,uint *param_4,uint param_5);
void FUN_00120f8c(int param_1,int *param_2,int param_3,int *param_4,int param_5);
void game_create_objects(Game *game,ISwerveObject *node,LevelObject *parent);   /* 0x00121134 GUESS: name */
LevelObject * level_object_update_trigger(LevelObject *object,uint32 x,uint32 y,uint32 z,uint32 radius,uint32 height,uint32 heading);   /* 0x001213FC GUESS: name, see kh_mod.c */
void app_context_remove_object(int param_1,int *param_2,int *param_3,int param_4);   /* 0x00121584 GUESS: name, see kh_mod.c */
void FUN_0012164c(int param_1,undefined4 param_2,int param_3);
void progress_add_play_time(Progress *progress);   /* 0x001216C4 GUESS: name, see kh_mod.c */
void FUN_0012171c(int32 object,int32 now,int32 elapsed);   /* 0x0012171C (no Ghidra function) */
void camera_pitch_over_ground(Camera *camera,uint32 *point,int32 elapsed);   /* 0x00121780 GUESS: names */
void FUN_00121ab0(int param_1);
void camera_recenter_yaw(Camera *camera,int32 elapsed);   /* 0x00121B98 GUESS: name, see kh_mod.c */
undefined8 FUN_00121c6c(int param_1,undefined4 param_2,int param_3);
void game_update_objects(int param_1,byte *param_2,int param_3);   /* 0x00122450 GUESS: name, see kh_mod.c */
void FUN_001226e8(ItemDrops *drops,int32 now,int32 elapsed);
int32 script_sequence_update(ScriptSequence *sequence,int32 now,int32 elapsed);   /* 0x0012289C GUESS: name, see kh_mod.c */
void enemy_update(Enemy *enemy,int32 now,int32 elapsed);   /* 0x00122954 GUESS: name */
void camera_update(Camera *camera,int32 now,int32 elapsed);   /* 0x00122B90 GUESS: names, see kh_mod.c */
void combat_region_update(CombatRegion *region,int32 now,int32 elapsed);   /* 0x00122F98 GUESS: name */
void FUN_0012312c(int param_1,int param_2,int param_3);
void FUN_00123588(int param_1,int param_2,int param_3);
void animations_update(Animations *animations,int32 worldTime,int32 elapsed,int32 animate);   /* 0x00123C24 GUESS: names */
void FUN_00123d7c(int param_1,undefined4 param_2,int param_3);
void FUN_0012407c(int param_1,undefined4 param_2,undefined4 param_3);
void intro_update(Intro *intro,int32 worldTime,int32 elapsed,int32 *error);   /* 0x001241A8 GUESS: names */
void FUN_001242b4(int param_1);
void save_write_byte(Progress *progress,uint8 byte,uint8 *data,int32 *position);   /* 0x00124674 GUESS: name, see kh_mod.c */
void save_write_float(Progress *progress,uint32 value,uint8 *data,int32 *position);   /* 0x001246B4 GUESS: name, see kh_mod.c */
void save_write_int(Progress *progress,int32 value,uint8 *data,int32 *position);   /* 0x001246F4 GUESS: name, see kh_mod.c */
int32 save_write_string(Progress *progress,const char *text,uint8 *data,int32 *position);   /* 0x00124734 GUESS: name, see kh_mod.c */
uint32 double_to_float(float64 x);   /* 0x0012479C GUESS: name, see kh_mod.c */
float64 double_add(float64 a,float64 b);   /* 0x00124954 GUESS: name, see kh_mod.c */
float64 double_reverse_subtract(float64 a,float64 b);   /* 0x00124B40 GUESS: name, see kh_mod.c */
float64 double_subtract(float64 a,float64 b);   /* 0x00124B84 GUESS: name, see kh_mod.c */
float64 double_reverse_divide(float64 a,float64 b);   /* 0x00124F24 GUESS: name, see kh_mod.c */
float64 double_divide(float64 a,float64 b);   /* 0x00124F44 GUESS: name, see kh_mod.c */
uint64 double_divide_mantissas(uint32 dividendLow,uint32 dividendHigh,uint32 divisorLow,uint32 divisorHigh);   /* 0x001251EC GUESS: name */
uint32 double_compare_equal(float64 a,float64 b);   /* 0x001254D4 GUESS: name, see kh_mod.c */
int32 double_to_int(float64 x);   /* 0x00125554 GUESS: name, see kh_mod.c */
float64 int_to_double(int32 value);   /* 0x00125604 GUESS: name, see kh_mod.c */
uint32 double_compare_greater(float64 a,float64 b);   /* 0x00125634 GUESS: name, see kh_mod.c */
uint32 double_compare_less(float64 a,float64 b);   /* 0x001256B4 GUESS: name, see kh_mod.c */
float64 double_multiply(float64 a,float64 b);   /* 0x00125734 GUESS: name, see kh_mod.c */
float64 double_remainder(float64 a,float64 b);   /* 0x001259E8 GUESS: name, see kh_mod.c */
float64 double_sqrt(float64 x);   /* 0x00125CD0 GUESS: name, see kh_mod.c */
float64 float_to_double(uint32 a);   /* 0x00126248 GUESS: name, see kh_mod.c */
uint32 float_add(uint32 a,uint32 b);   /* 0x001262B0 GUESS: name; a + b, float bits (__aeabi_fadd) */
uint32 float_reverse_subtract(uint32 a,uint32 b);   /* 0x001263F8 GUESS: name; b - a (__aeabi_frsub) */
uint32 float_subtract(uint32 a,uint32 b);   /* 0x0012642C GUESS: name; a - b (__aeabi_fsub) */
uint32 float_reverse_divide(uint32 a,uint32 b);   /* 0x00126608 GUESS: name, see kh_mod.c */
uint32 float_divide(uint32 a,uint32 b);   /* 0x00126618 GUESS: name, see kh_mod.c */
uint32 float_compare_equal(uint32 a,uint32 b);   /* 0x001267F0 GUESS: name; == / !=, result in the flags (__aeabi_cfcmpeq) */
int32 float_to_int(uint32 a);   /* 0x00126858 GUESS: name, see kh_mod.c */
uint32 int_to_float(int32 value);   /* 0x001268C8 GUESS: name, see kh_mod.c */
uint32 float_compare_greater(uint32 a,uint32 b);   /* 0x001268FC GUESS: name; > / >=, result in the flags (__aeabi_cfcmple) */
uint32 float_compare_less(uint32 a,uint32 b);   /* 0x00126964 GUESS: name; < / <=, result in the flags */
uint32 float_multiply(uint32 a,uint32 b);   /* 0x001269CC GUESS: name, see kh_mod.c */


/* ---- Literal-pool words, named automatically from the module bytes ----------------------------
   Each was a Ghidra DAT_<address> label, named after its value (the PC-relative offsets among them
   are the data objects and function addresses at the end of this file now). The comment gives the old label(s),
   the word's address and how the name was derived. Generated, not reviewed one by one: names say
   what a word IS (its value or target), not necessarily what the code uses it for. */
#define AEECLSID_KH_APPLET_VALUE 0x01026191   /* was DAT_0010197c (word at 0x0010197C); BREW class identifier AEECLSID_KH_APPLET */
#define TEXT_BUY_HEADING 0x2DE9998F   /* was DAT_00102ad0 (word at 0x00102AD0); the text id of
                                         "BUY" (language.m3g) */
#define TEXT_OF 0x1EC39991   /* was DAT_00102ad4 (word at 0x00102AD4); the text id of
                                " of " (language.m3g) */
#define TEXT_SELECT 0x0017A510   /* was DAT_00102ad8 (word at 0x00102AD8); the text id of
                                    "Select" (language.m3g) */
#define TEXT_SAVE 0x1F10FB19   /* was DAT_00102adc (word at 0x00102ADC); the text id of
                                  "Save" (language.m3g) */
#define TEXT_CONTINUE 0x03D18088   /* was DAT_00102ae4 (word at 0x00102AE4); the text id of
                                      "Continue" (language.m3g) */
#define TEXT_REPLAY 0x0252B33F   /* was DAT_00102af4, DAT_0011aa68 (word at 0x00102AF4); the text id of
                                    "Replay" (language.m3g) */
#define TEXT_MENU 0x251509C8   /* was DAT_00102af8, DAT_00108e80 (word at 0x00102AF8); the text id of
                                  "Menu" (language.m3g) */
#define TEXT_SUMMARY 0x310668B6   /* was DAT_00102afc (word at 0x00102AFC); the text id of
                                     "SUMMARY" (language.m3g) */
#define TEXT_SCORE_FORMULA 0x01B449A3   /* was DAT_00102b14 (word at 0x00102B14); the text id of
                                         "Score = Munny + (100 x EXP)" (language.m3g) */
#define TEXT_HIGH_SCORES 0x24017E3E   /* was DAT_00102b18 (word at 0x00102B18); the text id of
                                         "HIGH SCORES" (language.m3g) */
#define TEXT_LEVEL 0x272E6865   /* was DAT_00102b1c (word at 0x00102B1C); the text id of
                                   "Level" (language.m3g) */
#define TEXT_SCORE 0x00C833EC   /* was DAT_00102b20 (word at 0x00102B20); the text id of
                                   "Score" (language.m3g) */
#define TEXT_RANK 0x04D4D70F   /* was DAT_00102b24 (word at 0x00102B24); the text id of
                                  "Rank" (language.m3g) */
/* The music playing (AppContext.music; app_context_set_music, app_context_stop_music; GUESS: names). */
#define MUSIC_TRAINING          0      /* "training.mid": the title and the training level */
#define MUSIC_LEVEL             1      /* the level's own "<level>.mid" */
#define MUSIC_DEATH             2      /* "death.mid" */
#define MUSIC_NONE              3      /* none (app_context_create, app_context_stop_music) */

/* The menu items' types (UIElement.type, menu_item_create; GUESS: names). 1, 4 and 7 have no
   name yet. */
#define MENU_ITEM_SOFT_KEY      2      /* a screen's soft key (screen_set_soft_key) */
#define MENU_ITEM_BUTTON        3      /* a button of a menu's column (menu_add_buttons) */
#define MENU_ITEM_TITLE_BUTTON  5      /* a button of the title menu's column (menu_add_buttons) */
#define MENU_ITEM_ROW           6      /* a list row; its label in text style 0x24 */
#define MENU_ITEM_KEY_PICKER    8      /* the Controls screen's key pickers */
#define MENU_ITEM_TEXT_ENTRY    9      /* a text field: an ITextCtl (class 0x01003009) */
#define MENU_ITEM_NUMBER_ENTRY  10     /* the same, in input mode 5 (GUESS: AEE_TM_NUMBERS) */
#define MENU_ITEM_PROGRESS_BAR  0xb    /* the download progress bar */
#define MENU_ITEM_PICTURE       0xc    /* an image (ui_element_load_image), drawn centred */
#define UI_ELEMENT_FOCUSED      0x2    /* UIElement.flags: it has the focus (ui_element_set_focus) */

#define COLOR_PALE_LILAC 0xFFC9C4DA   /* was DAT_00102b50, DAT_00104c2c, DAT_001077b8, DAT_00108728 (word
                                                 at 0x00102B50); the colour 0xAARRGGBB (201, 196, 218) */
#define TEXT_BACK 0x19408333   /* was DAT_00102b54, DAT_00104c08, DAT_00108e64 (word at 0x00102B54);
                                  the text id of
                                  "Back" (language.m3g) */
#define TEXT_DOWNLOADING 0x0528CA88   /* was DAT_00102b5c, DAT_00104c58 (word at 0x00102B5C);
                                         the text id of
                                         "Downloading....." (language.m3g) */
#define TEXT_CANCEL 0x10FB280A   /* was DAT_00102b70, DAT_00104c50 (word at 0x00102B70); the text id of
                                    "Cancel" (language.m3g) */
#define TEXT_YES 0x03B0A428   /* was DAT_00102b80, DAT_00104c18 (word at 0x00102B80); the text id of
                                 "Yes" (language.m3g) */
#define TEXT_NO 0x30D96C27   /* was DAT_00102b84 (word at 0x00102B84); the text id of
                                "No" (language.m3g) */
#define TEXT_SENDING 0x2E8D6E9D   /* was DAT_00102b88 (word at 0x00102B88); the text id of
                                     "Sending..." (language.m3g) */
#define WORD_HEXADECIMAL_000253E4 0x000253E4   /* was DAT_00102b90 (word at 0x00102B90); value 0x000253E4 (152548) */
#define TEXT_GAME_AUTOSAVED 0x21C1059D   /* was DAT_00102b98 (word at 0x00102B98); the text id of
                                         "(Game autosaved)" (language.m3g) */
#define WORD_HEXADECIMAL_00025038 0x00025038   /* was DAT_00102ba0 (word at 0x00102BA0); value 0x00025038 (151608) */
#define TEXT_STATUS 0x2B21E3F9   /* was DAT_00103b84 (word at 0x00103B84); the text id of
                                         "STATUS" (language.m3g) */
#define TEXT_NEXT 0x225D20E5   /* was DAT_00103b88 (word at 0x00103B88); the text id of
                                  "Next" (language.m3g) */
#define TEXT_ITEMS 0x0DB81F00   /* was DAT_00103bac (word at 0x00103BAC); the text id of
                                         "ITEMS" (language.m3g) */
#define TEXT_OPTIONS 0x2E66608C   /* was DAT_00103bd8 (word at 0x00103BD8); the text id of
                                         "OPTIONS" (language.m3g) */
#define TEXT_SOUND_LOW 0x2F7413EE   /* was DAT_00103be8 (word at 0x00103BE8); the text id of
                                       "Sound Low" (language.m3g) */
#define TEXT_SOUND_MEDIUM 0x31B444EE   /* was DAT_00103bec (word at 0x00103BEC); the text id of
                                          "Sound Medium" (language.m3g) */
#define TEXT_SOUND_HIGH 0x15998E05   /* was DAT_00103bf0 (word at 0x00103BF0); the text id of
                                        "Sound High" (language.m3g) */
#define TEXT_MUSIC_LOW 0x13DD8E16   /* was DAT_00103bf4 (word at 0x00103BF4); the text id of
                                       "Music Low" (language.m3g) */
#define TEXT_MUSIC_MEDIUM 0x0AFA190E   /* was DAT_00103bf8 (word at 0x00103BF8); the text id of
                                          "Music Medium" (language.m3g) */
#define TEXT_MUSIC_HIGH 0x2714CFF7   /* was DAT_00103bfc (word at 0x00103BFC); the text id of
                                        "Music High" (language.m3g) */
#define TEXT_SELECT_AN_ITEM 0x133529B8   /* was DAT_00103c00 (word at 0x00103C00); the text id of
                                         "Select an item for details" (language.m3g) */
#define COLOR_LIGHT_GREY 0xFFEFEFEF   /* was DAT_00103c04, DAT_001051a0, DAT_001052d0, DAT_00108724,
                                                 DAT_0010bb20, DAT_0012465c (word at 0x00103C04); the
                                                 colour 0xAARRGGBB (239, 239, 239) */
#define TEXT_ITEM_HEADING 0x02AAF639   /* was DAT_00104bc4 (word at 0x00104BC4); the text id of
                                          "ITEM" (language.m3g) */
#define TEXT_VALUE_HEADING 0x1A43CB02   /* was DAT_00104bc8 (word at 0x00104BC8); the text id of
                                           "VALUE" (language.m3g) */
#define WORD_HEXADECIMAL_00023F3C 0x00023F3C   /* was DAT_00104bcc (word at 0x00104BCC); value 0x00023F3C (147260) */
#define WORD_HEXADECIMAL_00023F38 0x00023F38   /* was DAT_00104bd0 (word at 0x00104BD0); value 0x00023F38 (147256) */
#define WORD_HEXADECIMAL_00023F34 0x00023F34   /* was DAT_00104bd4 (word at 0x00104BD4); value 0x00023F34 (147252) */
#define INTEGER_57393 0x0000E031   /* was DAT_00104bdc, DAT_001054d0, DAT_0011a4d4, DAT_0011aacc (word at 0x00104BDC); integer 57393 */
#define INTEGER_57394 0x0000E032   /* was DAT_00104be0, DAT_001054d4 (word at 0x00104BE0); integer 57394 */
#define TEXT_MUNNY 0x16A5390B   /* was DAT_00104be4, DAT_0010d2f0 (word at 0x00104BE4); the text id of
                                   "Munny" (language.m3g) */
#define INTEGER_MINUS_16076 0xFFFFC134   /* was DAT_00104be8 (word at 0x00104BE8); integer -16076 */
#define INTEGER_735 0x000002DF   /* was DAT_00104bf0 (word at 0x00104BF0); integer 735 */
#define TEXT_SHOP 0x2A6EBDD0   /* was DAT_00104bf4 (word at 0x00104BF4); the text id of
                                  "Shop" (language.m3g) */
#define TEXT_POTION_HELP 0x2CF7E187   /* was DAT_00104bf8 (word at 0x00104BF8); the text id of
                                         "Potion partially restores your character's health. Co..."
                                         (language.m3g) */
#define TEXT_HI_POTION_HELP 0x0955306E   /* was DAT_00104bfc (word at 0x00104BFC); the text id of
                                            "Hi-Potion fully restores your character's health. Cos..."
                                            (language.m3g) */
#define TEXT_ETHER_HELP 0x2C7A1EE9   /* was DAT_00104c00 (word at 0x00104C00); the text id of
                                        "Ether partially restores your character's magic. Cost..."
                                        (language.m3g) */
#define TEXT_ELIXIR_HELP 0x07A0110B   /* was DAT_00104c04 (word at 0x00104C04); the text id of
                                         "Elixir fully restores your character's magic. Cost 15."
                                         (language.m3g) */
#define TEXT_CONFIRM_END_GAME 0x1650919F   /* was DAT_00104c14 (word at 0x00104C14); the text id of
                                              "Are you sure you want to end the game ?" (language.m3g) */
#define WORD_HEXADECIMAL_3C5A569E 0x3C5A569E   /* was DAT_00104c1c, DAT_0011a498, DAT_0011e240 (word at 0x00104C1C); value 0x3C5A569E (1012553374) */
#define WORD_HEXADECIMAL_21BF9442 0x21BF9442   /* was DAT_00104c20, DAT_00105220, DAT_0010d070, DAT_0010f23c, DAT_0011a49c, DAT_0011e23c, DAT_00123c1c, DAT_00124668 (word at 0x00104C20); value 0x21BF9442 (566203458) */
#define TEXT_CONTROLS 0x111CB9DB   /* was DAT_00104c24 (word at 0x00104C24); the text id of
                                         "CONTROLS" (language.m3g) */
#define TEXT_SOUND_OFF 0x14FB8F11   /* was DAT_00104c38 (word at 0x00104C38); the text id of
                                       "Sound Off" (language.m3g) */
#define TEXT_MUSIC_OFF 0x27B2CEEB   /* was DAT_00104c3c (word at 0x00104C3C); the text id of
                                       "Music Off" (language.m3g) */
#define TEXT_HELP 0x0C211E44   /* was DAT_00104c40 (word at 0x00104C40); the text id of
                                  "HELP" (language.m3g) */
#define TEXT_HELP_BODY 0x2F3E5828   /* was DAT_00104c44 (word at 0x00104C44); the text id of
                                       "Use joypad up or <#UP> to walk forwards, joypad down..."
                                       (language.m3g) */
#define TEXT_ABOUT 0x37E4CCE1   /* was DAT_00104c48 (word at 0x00104C48); the text id of
                                   "ABOUT" (language.m3g) */
#define TEXT_ABOUT_BODY 0x0CB59575   /* was DAT_00104c4c (word at 0x00104C4C); the text id of
                                        "Kingdom Hearts..." (language.m3g) */
#define INTEGER_790 0x00000316   /* was DAT_00104c54 (word at 0x00104C54); integer 790 */
#define TEXT_DOWNLOAD_ERROR 0x27B19885   /* was DAT_001051a4 (word at 0x001051A4); the text id of
                                            "Download Error" (language.m3g) */
#define WORD_HEXADECIMAL_0AE069A1 0x0AE069A1   /* was DAT_001051ac (word at 0x001051AC); value 0x0AE069A1 (182479265) */
#define TEXT_DOWNLOAD 0x1D73D1AE   /* was DAT_001051c4 (word at 0x001051C4); the text id of
                                      "Download" (language.m3g) */
#define TEXT_END 0x14741FD6   /* was DAT_001051c8 (word at 0x001051C8); the text id of
                                 "End" (language.m3g) */
#define WORD_HEXADECIMAL_1FEB4DB8 0x1FEB4DB8   /* was DAT_0010521c, DAT_0011e244 (word at 0x0010521C); value 0x1FEB4DB8 (535514552) */
#define COLOR_DARK_GREY 0xFF606060   /* was DAT_001052cc (word at 0x001052CC); the colour 0xAARRGGBB
                                                 (96, 96, 96): a focused type 5 element's background
                                                 (ui_element_set_focus) */
#define COLOR_PALE_LAVENDER 0xFFEBEBF7   /* was DAT_001052d4, DAT_001077b4, DAT_0010871c, DAT_0010bb28,
                                                 DAT_0010be10 (word at 0x001052D4); the colour
                                                 0xAARRGGBB (235, 235, 247): among others a focused
                                                 element's primary colour (ui_element_set_focus) */
#define COLOR_SLATE_GREY 0xFF7E8194   /* was DAT_001052d8, DAT_00106e40, DAT_001077bc (word at
                                                 0x001052D8); the colour 0xAARRGGBB (126, 129, 148): among
                                                 others a focused element's background
                                                 (ui_element_set_focus) and focus frame (menu_item_draw) */
#define FLOAT_500 0x43FA0000   /* was DAT_001055c0 (word at 0x001055C0); the float 500.0 */
#define INTEGER_MINUS_22348 0xFFFFA8B4   /* was DAT_00105c0c (word at 0x00105C0C); integer -22348 */
#define INTEGER_MINUS_22752 0xFFFFA720   /* was DAT_00105c34 (word at 0x00105C34); integer -22752 */
#define INTEGER_MINUS_23228 0xFFFFA544   /* was DAT_00105c50 (word at 0x00105C50); integer -23228 */
#define AEECLSID_FILEMGR_VALUE 0x01001003   /* was DAT_00106320, DAT_001098d0, DAT_0010fb84, DAT_0011b174, DAT_0011e6b0 (word at 0x00106320); BREW class identifier AEECLSID_FILEMGR */
#define WORD_HEXADECIMAL_00021B34 0x00021B34   /* was DAT_0010634c (word at 0x0010634C); value 0x00021B34 (138036) */
#define WORD_HEXADECIMAL_00010002 0x00010002   /* was DAT_00106350, DAT_001082dc (word at 0x00106350); value 0x00010002 (65538) */
#define COLOR_ROYAL_BLUE 0xFF4757DD   /* was DAT_00106734 (word at 0x00106734); the colour 0xAARRGGBB
                                                 (71, 87, 221) */
#define COLOR_LIGHT_CYAN 0xFF82ECF3   /* was DAT_00106a88 (word at 0x00106A88); the colour 0xAARRGGBB
                                                 (130, 236, 243) */
#define INTEGER_MINUS_19441 0xFFFFB40F   /* was DAT_00106a8c (word at 0x00106A8C); integer -19441 */
#define INTEGER_MINUS_15954 0xFFFFC1AE   /* was DAT_00106a90 (word at 0x00106A90); integer -15954 */
#define COLOR_PURPLE_GREY 0xFF615A6D   /* was DAT_00106fa0 (word at 0x00106FA0); the colour 0xAARRGGBB
                                                 (97, 90, 109) */
#define COLOR_GREY_LILAC 0xFF9795A5   /* was DAT_00106fa4, DAT_001077b0 (word at 0x00106FA4); the colour
                                                 0xAARRGGBB (151, 149, 165) */
#define COLOR_DARK_PURPLE 0xFF2F2533   /* was DAT_001077a8, DAT_00108718 (word at 0x001077A8); the colour
                                                 0xAARRGGBB (47, 37, 51) */
#define WORD_HEXADECIMAL_00FF00FF 0x00FF00FF   /* was DAT_001077ac (word at 0x001077AC); value 0x00FF00FF (16711935) */
#define COLOR_CHARCOAL 0xFF47464C   /* was DAT_001077c0, DAT_00108714 (word at 0x001077C0); the colour
                                                 0xAARRGGBB (71, 70, 76) */
#define COLOR_RED 0xFFFF0000   /* was DAT_001077c4, DAT_00107ad0 (word at 0x001077C4); the colour
                                                 0xAARRGGBB (255, 0, 0) */
#define INTEGER_270 0x0000010E   /* was DAT_00107ac4 (word at 0x00107AC4); integer 270 */
#define COLOR_GREEN 0xFF7FCB61   /* was DAT_00107acc (word at 0x00107ACC); the colour 0xAARRGGBB
                                                 (127, 203, 97) */
#define WORD_HEXADECIMAL_0001FE30 0x0001FE30   /* was DAT_00107d20 (word at 0x00107D20); value 0x0001FE30 (130608) */
#define COLOR_DARK_YELLOW 0xFFC0C000   /* was DAT_00108720 (word at 0x00108720); the colour 0xAARRGGBB
                                                 (192, 192, 0) */
#define INTEGER_57397 0x0000E035   /* was DAT_0010883c (word at 0x0010883C); integer 57397 */
#define TEXT_NETWORK_UNAVAILABLE 0x1AB5DBD0   /* was DAT_00108e58 (word at 0x00108E58); the text id of
                                                 "The network is currently not available, please try ag..."
                                                 (language.m3g) */
#define INTEGER_MINUS_35012 0xFFFF773C   /* was DAT_00108e5c (word at 0x00108E5C); integer -35012 */
#define TEXT_NO_ROOM_TO_DOWNLOAD 0x0FA4E52C   /* was DAT_00108e60 (word at 0x00108E60); the text id of
                                                 "Not enough room on the device to download."
                                                 (language.m3g) */
#define TEXT_SAVING 0x3D569D08   /* was DAT_00108e68 (word at 0x00108E68); the text id of
                                    "Saving...." (language.m3g) */
#define WORD_HEXADECIMAL_0001F14C 0x0001F14C   /* was DAT_00108e6c (word at 0x00108E6C); value 0x0001F14C (127308) */
#define TEXT_RETRY 0x3D198889   /* was DAT_00108e84 (word at 0x00108E84); the text id of
                                   "Retry" (language.m3g) */
#define INTEGER_MINUS_55555 0xFFFF26FD   /* was DAT_001091f8 (word at 0x001091F8); integer -55555 */
#define INTEGER_10000 0x00002710   /* was DAT_00109ef4 (word at 0x00109EF4); integer 10000 */
#define TEXT_DOTS 0x3D1D22E8   /* was DAT_0010a3e4 (word at 0x0010A3E4); the text id of
                                  "....." (language.m3g) */
#define INTEGER_57396 0x0000E034   /* was DAT_0010a524 (word at 0x0010A524); integer 57396 */
#define FLOAT_3 0x40400000   /* was DAT_0010a5cc, DAT_00110554, DAT_00121aac, DAT_00124078 (word at 0x0010A5CC); the float 3.0 */
#define FLOAT_0_POINT_3 0x3E99999A   /* was DAT_0010a5d0, DAT_00117d0c (word at 0x0010A5D0); the float 0.30000001192092896 */
#define INTEGER_MINUS_42416 0xFFFF5A50   /* was DAT_0010a5d4 (word at 0x0010A5D4); integer -42416 */
#define WORD_HEXADECIMAL_1922F406 0x1922F406   /* was DAT_0010aa34 (word at 0x0010AA34); value 0x1922F406 (421721094) */
#define WORD_HEXADECIMAL_038AD7F2 0x038AD7F2   /* was DAT_0010aa40 (word at 0x0010AA40); value 0x038AD7F2 (59430898) */
#define WORD_HEXADECIMAL_334C8936 0x334C8936   /* was DAT_0010aa48 (word at 0x0010AA48); value 0x334C8936 (860653878) */
#define WORD_HEXADECIMAL_0AD65F3D 0x0AD65F3D   /* was DAT_0010aa4c (word at 0x0010AA4C); value 0x0AD65F3D (181821245) */
#define INTEGER_501 0x000001F5   /* was DAT_0010aa54 (word at 0x0010AA54); integer 501 */
#define INTEGER_5001 0x00001389   /* was DAT_0010ac58, DAT_0010faa4 (word at 0x0010AC58); integer 5001 */
#define INTEGER_5002 0x0000138A   /* was DAT_0010ac60, DAT_0010faa0 (word at 0x0010AC60); integer 5002 */
#define TEXT_LOADING 0x254DA109   /* was DAT_0010ac68 (word at 0x0010AC68); the text id of
                                     "Loading....." (language.m3g) */
#define AEECLSID_GRAPHICS_VALUE 0x01002001   /* was DAT_0010aefc (word at 0x0010AEFC); BREW class identifier AEECLSID_GRAPHICS */
#define INTEGER_MINUS_44296 0xFFFF52F8   /* was DAT_0010af00 (word at 0x0010AF00); integer -44296 */
#define WORD_HEXADECIMAL_0001CD1C 0x0001CD1C   /* was DAT_0010af08 (word at 0x0010AF08); value 0x0001CD1C (118044) */
#define INTEGER_5003 0x0000138B   /* was DAT_0010af0c (word at 0x0010AF0C); integer 5003 */
#define INTEGER_5004 0x0000138C   /* was DAT_0010af14 (word at 0x0010AF14); integer 5004 */
#define INTEGER_5005 0x0000138D   /* was DAT_0010af1c (word at 0x0010AF1C); integer 5005 */
#define INTEGER_5006 0x0000138E   /* was DAT_0010af24 (word at 0x0010AF24); integer 5006 */
#define INTEGER_5007 0x0000138F   /* was DAT_0010af2c (word at 0x0010AF2C); integer 5007 */
#define INTEGER_5008 0x00001390   /* was DAT_0010af34 (word at 0x0010AF34); integer 5008 */
#define AEECLSID_WEB_VALUE 0x01005000   /* was DAT_0010afc0 (word at 0x0010AFC0); BREW class identifier AEECLSID_WEB */
#define INTEGER_1001 0x000003E9   /* was DAT_0010b2d4, DAT_00122b84 (word at 0x0010B2D4); integer 1001 */
#define INTEGER_MINUS_45732 0xFFFF4D5C   /* was DAT_0010b2d8 (word at 0x0010B2D8); integer -45732 */
#define INTEGER_5000 0x00001388   /* was DAT_0010b3e4, DAT_0011a800, DAT_0011c324, DAT_0011fc78, DAT_0012243c (word at 0x0010B3E4); integer 5000 */
#define FLOAT_90 0x42B40000   /* was DAT_0010b470, DAT_0010e444, DAT_0011411c, DAT_001169c4, DAT_0011adb4, DAT_001202f0, DAT_00121c5c, DAT_00122f94 (word at 0x0010B470); the float 90.0 */
#define FLOAT_10 0x41200000   /* was DAT_0010b474, DAT_0010db00, DAT_0010df5c, DAT_001118a8, DAT_00122f88 (word at 0x0010B474); the float 10.0 */
#define INTEGER_1836 0x0000072C   /* was DAT_0010b5dc (word at 0x0010B5DC); integer 1836 */
#define INTEGER_1820 0x0000071C   /* was DAT_0010b868 (word at 0x0010B868); integer 1820 */
#define COLOR_PALE_GREEN 0xFFC5FAB9   /* was DAT_0010bafc (word at 0x0010BAFC); the colour 0xAARRGGBB
                                                 (197, 250, 185) */
#define COLOR_DARK_BLUE 0xFF004C78   /* was DAT_0010bb00 (word at 0x0010BB00); the colour 0xAARRGGBB
                                                 (0, 76, 120) */
#define COLOR_BLUE 0xFF0253A8   /* was DAT_0010bb04 (word at 0x0010BB04); the colour 0xAARRGGBB
                                                 (2, 83, 168) */
#define INTEGER_MINUS_28807 0xFFFF8F79   /* was DAT_0010bb08 (word at 0x0010BB08); integer -28807 */
#define COLOR_DARK_PLUM 0xFF2C0621   /* was DAT_0010bb0c (word at 0x0010BB0C); the colour 0xAARRGGBB
                                                 (44, 6, 33) */
#define COLOR_RUST 0xFF8D2B15   /* was DAT_0010bb10 (word at 0x0010BB10); the colour 0xAARRGGBB
                                                 (141, 43, 21) */
#define INTEGER_MINUS_6560 0xFFFFE660   /* was DAT_0010bb14 (word at 0x0010BB14); integer -6560 */
#define COLOR_BROWN 0xFF724307   /* was DAT_0010bb18 (word at 0x0010BB18); the colour 0xAARRGGBB
                                                 (114, 67, 7) */
#define COLOR_OCHRE 0xFF8A4E00   /* was DAT_0010bb1c (word at 0x0010BB1C); the colour 0xAARRGGBB
                                                 (138, 78, 0) */
#define COLOR_CREAM 0xFFEFEFC0   /* was DAT_0010bb24 (word at 0x0010BB24); the colour 0xAARRGGBB
                                                 (239, 239, 192) */
#define CLASS_IDENTIFIER_HEXADECIMAL_01003009 0x01003009   /* was DAT_0010bd74 (word at 0x0010BD74); in the BREW class identifier range */
#define INTEGER_57360 0x0000E010   /* was DAT_0010bd78 (word at 0x0010BD78); integer 57360 */
#define INTEGER_MINUS_48896 0xFFFF4100   /* was DAT_0010c144 (word at 0x0010C144); integer -48896 */
#define INTEGER_MINUS_49004 0xFFFF4094   /* was DAT_0010c148 (word at 0x0010C148); integer -49004 */
#define AEECLSID_MEDIAMP3_VALUE 0x01005502   /* was DAT_0010c150 (word at 0x0010C150); BREW class identifier AEECLSID_MEDIAMP3 */
#define AEECLSID_MEDIAMIDI_VALUE 0x01005501   /* was DAT_0010c158 (word at 0x0010C158); BREW class identifier AEECLSID_MEDIAMIDI */
#define AEECLSID_MEDIAPMD_VALUE 0x01005504   /* was DAT_0010c164 (word at 0x0010C164); BREW class identifier AEECLSID_MEDIAPMD */
#define WORD_HEXADECIMAL_150C956D 0x150C956D   /* was DAT_0010d064 (word at 0x0010D064); value 0x150C956D (353146221) */
#define WORD_HEXADECIMAL_0B96B9C5 0x0B96B9C5   /* was DAT_0010d068 (word at 0x0010D068); value 0x0B96B9C5 (194427333) */
#define WORD_HEXADECIMAL_2CB8343A 0x2CB8343A   /* was DAT_0010d06c (word at 0x0010D06C); value 0x2CB8343A (750269498) */
#define INTEGER_MINUS_53860 0xFFFF2D9C   /* was DAT_0010d2f4 (word at 0x0010D2F4); integer -53860 */
#define INTEGER_MINUS_54208 0xFFFF2C40   /* was DAT_0010d4cc (word at 0x0010D4CC); integer -54208 */
#define FLOAT_0_POINT_7 0x3F333333   /* was DAT_0010d7bc (word at 0x0010D7BC); the float 0.699999988079071 */
#define FLOAT_800 0x44480000   /* was DAT_0010d7c0 (word at 0x0010D7C0); the float 800.0 */
#define FLOAT_180 0x43340000   /* was DAT_0010d958, DAT_0010dafc, DAT_0011ca6c, DAT_0011da98, DAT_0011dc90, DAT_0011ed38, DAT_00122f90, DAT_00123c0c (word at 0x0010D958); the float 180.0 */
#define FLOAT_16 0x41800000   /* was DAT_0010daf8, DAT_0011d3e4 (word at 0x0010DAF8); the float 16.0 */
#define INTEGER_0 0x00000000   /* was DAT_00126224 (word at 0x0010DF60); integer 0 */
#define WORD_HEXADECIMAL_24D6C48B 0x24D6C48B   /* was DAT_0010df70 (word at 0x0010DF70); value 0x24D6C48B (618054795) */
#define WORD_HEXADECIMAL_14A090F6 0x14A090F6   /* was DAT_0010df74 (word at 0x0010DF74); value 0x14A090F6 (346067190) */
#define WORD_HEXADECIMAL_36420037 0x36420037   /* was DAT_0010df78 (word at 0x0010DF78); value 0x36420037 (910295095) */
#define WORD_HEXADECIMAL_387C837A 0x387C837A   /* was DAT_0010df7c (word at 0x0010DF7C); value 0x387C837A (947684218) */
#define WORD_HEXADECIMAL_2DF1CDEC 0x2DF1CDEC   /* was DAT_0010df80 (word at 0x0010DF80); value 0x2DF1CDEC (770821612) */
#define WORD_HEXADECIMAL_254FCFF2 0x254FCFF2   /* was DAT_0010df84 (word at 0x0010DF84); value 0x254FCFF2 (625987570) */
#define FLOAT_100 0x42C80000   /* was DAT_0010df88, DAT_0010ffc0, DAT_0011c6f4 (word at 0x0010DF88); the float 100.0 */
#define WORD_HEXADECIMAL_3361CE32 0x3361CE32   /* was DAT_0010df8c (word at 0x0010DF8C); value 0x3361CE32 (862047794) */
#define INTEGER_750 0x000002EE   /* was DAT_0010e058, DAT_0011c328 (word at 0x0010E058); integer 750 */
#define FLOAT_1_POINT_1 0x3F8CCCCD   /* was DAT_0010e440 (word at 0x0010E440); the float 1.100000023841858 */
#define FLOAT_5 0x40A00000   /* was DAT_0010e834, DAT_0010f8e4, DAT_0010ffc8, DAT_00110560, DAT_00113298, DAT_001180b8, DAT_0011cfd8 (word at 0x0010E834); the float 5.0 */
#define FLOAT_DEGREES_TO_RADIANS 0x3C8EFA39   /* was DAT_0010ed3c, DAT_0011e52c, DAT_00122f8c (word at 0x0010ED3C); the float 0.0174533 (GUESS: name; pi / 180, 4 ULP above it, 0x3C8EFA35), the degrees-to-radians factor */
#define WORD_HEXADECIMAL_0493FC17 0x0493FC17   /* was DAT_0010f240 (word at 0x0010F240); value 0x0493FC17 (76807191) */
#define INTEGER_2004 0x000007D4   /* was DAT_0010f4c8 (word at 0x0010F4C8); integer 2004 */
#define INTEGER_2007 0x000007D7   /* was DAT_0010f4cc, DAT_0011d6bc (word at 0x0010F4CC); integer 2007 */
#define WORD_HEXADECIMAL_397714A4 0x397714A4   /* was DAT_0012244c (word at 0x0010F878); value 0x397714A4 (964105380) */
#define WORD_HEXADECIMAL_0B7E4D24 0x0B7E4D24   /* was DAT_0010f87c (word at 0x0010F87C); value 0x0B7E4D24 (192826660) */
#define INTEGER_57379 0x0000E023   /* was DAT_0010f988 (word at 0x0010F988); integer 57379, AVK_2 (progress_set_default_controls) */
#define INTEGER_57381 0x0000E025   /* was DAT_0010f98c (word at 0x0010F98C); integer 57381, AVK_4 (progress_set_default_controls) */
#define INTEGER_57382 0x0000E026   /* was DAT_0010f990 (word at 0x0010F990); integer 57382, AVK_5 (progress_set_default_controls) */
#define INTEGER_57387 0x0000E02B   /* was DAT_0010f994 (word at 0x0010F994); integer 57387, AVK_STAR (progress_set_default_controls) */
#define WORD_HEXADECIMAL_052F918F 0x052F918F   /* was DAT_0010f998 (word at 0x0010F998); value 0x052F918F (87003535) */
#define INTEGER_57398 0x0000E036   /* was DAT_0010f99c (word at 0x0010F99C); integer 57398, AVK_SOFT1 (progress_set_default_controls) */
#define FLOAT_0_POINT_1 0x3DCCCCCD   /* was DAT_0010fbf0, DAT_00110550, DAT_0011302c, DAT_0011da94 (word at 0x0010FBF0); the float 0.10000000149011612 */
#define FLOAT_5000 0x459C4000   /* was DAT_0010ffc4 (word at 0x0010FFC4); the float 5000.0 */
#define FLOAT_0_POINT_001 0x3A83126F   /* was DAT_0010ffcc, DAT_00110558, DAT_00113028, DAT_0011329c (word at 0x0010FFCC); the float 0.0010000000474974513 */
#define FLOAT_MINUS_1 0xBF800000   /* was DAT_0010ffd0, DAT_0011055c, DAT_00111854, DAT_001132a0, DAT_0011333c, DAT_00113464, DAT_00113cc0, DAT_00117d2c, DAT_00119594, DAT_0011c32c, DAT_0011dc94, DAT_0011f620, DAT_0011fd88, DAT_00122440, DAT_00124074 (word at 0x0010FFD0); the float -1.0 */
#define FLOAT_0_POINT_4 0x3ECCCCCD   /* was DAT_0010ffd4 (word at 0x0010FFD4); the float 0.4000000059604645 */
#define WORD_HEXADECIMAL_FFFEFEE0 0xFFFEFEE0   /* was DAT_00110188 (word at 0x00110188); value 0xFFFEFEE0 (-65824) */
#define FLOAT_MINUS_5 0xC0A00000   /* was DAT_00110698, DAT_001169e4 (word at 0x00110698); the float -5.0 */
#define FLOAT_7_POINT_5 0x40F00000   /* was DAT_0011069c (word at 0x0011069C); the float 7.5 */
#define WORD_HEXADECIMAL_FFFEF6C4 0xFFFEF6C4   /* was DAT_001117b0 (word at 0x001117B0); value 0xFFFEF6C4 (-67900) */
#define TEXT_ACTIVATE 0x2ACA7E67   /* was DAT_001117e4 (word at 0x001117E4); the text id of
                                      "Activate" (language.m3g) */
#define TEXT_ATTACK 0x22837D60   /* was DAT_001117ec (word at 0x001117EC); the text id of
                                    "Attack" (language.m3g) */
#define TEXT_THROW 0x29F2A761   /* was DAT_001117f4 (word at 0x001117F4); the text id of
                                   "Throw" (language.m3g) */
#define TEXT_GRAB 0x0C0AB7A6   /* was DAT_001117fc (word at 0x001117FC); the text id of
                                  "Grab" (language.m3g) */
#define TEXT_LIFT 0x30BF44AD   /* was DAT_00111804 (word at 0x00111804); the text id of
                                  "Lift" (language.m3g) */
#define TEXT_LOCK 0x1B18B1A5   /* was DAT_0011180c (word at 0x0011180C); the text id of
                                  "Lock" (language.m3g) */
#define TEXT_OPEN 0x0B0EC760   /* was DAT_00111814 (word at 0x00111814); the text id of
                                  "Open" (language.m3g) */
#define TEXT_TALK 0x18413CCA   /* was DAT_0011181c (word at 0x0011181C); the text id of
                                  "Talk" (language.m3g) */
#define TEXT_PLACE 0x1BF8C522   /* was DAT_00111824 (word at 0x00111824); the text id of
                                   "Place" (language.m3g) */
#define WORD_HEXADECIMAL_FFFEED2C 0xFFFEED2C   /* was DAT_00111868 (word at 0x00111868); value 0xFFFEED2C (-70356) */
#define WORD_HEXADECIMAL_2E6723BD 0x2E6723BD   /* was DAT_001118a0, DAT_00112e1c (word at 0x001118A0); value 0x2E6723BD (778511293) */
#define WORD_HEXADECIMAL_10C617E4 0x10C617E4   /* was DAT_001118a4, DAT_00112e18 (word at 0x001118A4); value 0x10C617E4 (281417700) */
#define FLOAT_1000 0x447A0000   /* was DAT_001118ac, DAT_00113168, DAT_001132a4, DAT_00113da0, DAT_001146e8, DAT_00118308, DAT_0011860c, DAT_0011c85c, DAT_0011cfcc, DAT_00122434 (word at 0x001118AC); the float 1000.0 */
#define WORD_HEXADECIMAL_00015CF8 0x00015CF8   /* was DAT_001127a4 (word at 0x001127A4); value 0x00015CF8 (89336) */
#define WORD_HEXADECIMAL_2BAC0EE7 0x2BAC0EE7   /* was DAT_00112a94 (word at 0x00112A94); value 0x2BAC0EE7 (732696295) */
#define WORD_HEXADECIMAL_1D28D9CF 0x1D28D9CF   /* was DAT_00112c08 (word at 0x00112C08); value 0x1D28D9CF (489216463) */
#define FLOAT_RADIANS_TO_DEGREES 0x42652F1B   /* was DAT_00113468, DAT_00121a9c (word at 0x00113468);
                                                 the float 57.296 (GUESS: name; 180 / pi rounded, 58 ULP
                                                 above 0x42652EE1), the radians-to-degrees factor */
#define WORD_HEXADECIMAL_00013970 0x00013970   /* was DAT_00113520 (word at 0x00113520); value 0x00013970 (80240) */
#define WORD_HEXADECIMAL_00013B98 0x00013B98   /* was DAT_001135b4 (word at 0x001135B4); value 0x00013B98 (80792) */
#define WORD_HEXADECIMAL_39B9295D 0x39B9295D   /* was DAT_0011364c (word at 0x0011364C); value 0x39B9295D (968436061) */
#define WORD_HEXADECIMAL_3C6EF35F 0x3C6EF35F   /* was DAT_001136b8 (word at 0x001136B8); value 0x3C6EF35F (1013904223) */
#define WORD_HEXADECIMAL_0019660D 0x0019660D   /* was DAT_001136bc (word at 0x001136BC); value 0x0019660D (1664525) */
#define FLOAT_0_POINT_05 0x3D4CCCCD   /* was DAT_00113780 (word at 0x00113780); the float 0.05000000074505806 */
#define WORD_HEXADECIMAL_497423F0 0x497423F0   /* was DAT_00114428 (word at 0x00114428); value 0x497423F0 (1232348144) */
#define WORD_HEXADECIMAL_000136B8 0x000136B8   /* was DAT_00114894 (word at 0x00114894); value 0x000136B8 (79544) */
#define WORD_HEXADECIMAL_2F1AAC89 0x2F1AAC89   /* was DAT_00115048 (word at 0x00115048); value 0x2F1AAC89 (790277257) */
#define WORD_HEXADECIMAL_3D9EB884 0x3D9EB884   /* was DAT_0011504c (word at 0x0011504C); value 0x3D9EB884 (1033812100) */
#define WORD_HEXADECIMAL_3CCB2BC1 0x3CCB2BC1   /* was DAT_00115050 (word at 0x00115050); value 0x3CCB2BC1 (1019947969) */
#define WORD_HEXADECIMAL_2E46DCB0 0x2E46DCB0   /* was DAT_00115054, DAT_001180b4 (word at 0x00115054); value 0x2E46DCB0 (776395952) */
#define WORD_HEXADECIMAL_13ADA166 0x13ADA166   /* was DAT_00115058, DAT_001180bc (word at 0x00115058); value 0x13ADA166 (330146150) */
#define WORD_HEXADECIMAL_3F01176F 0x3F01176F   /* was DAT_0011505c (word at 0x0011505C); value 0x3F01176F (1057036143) */
#define WORD_HEXADECIMAL_3D388F5A 0x3D388F5A   /* was DAT_00115060 (word at 0x00115060); value 0x3D388F5A (1027116890) */
#define WORD_HEXADECIMAL_2345879A 0x2345879A   /* was DAT_00115064 (word at 0x00115064); value 0x2345879A (591759258) */
#define WORD_HEXADECIMAL_01337FE6 0x01337FE6   /* was DAT_00115068 (word at 0x00115068); value 0x01337FE6 (20152294) */
#define FOUR_CHARACTER_TAG_0KRY 0x306B5259   /* was DAT_0011506c (word at 0x0011506C); the four characters '0kRY' (read as a big-endian word) */
#define WORD_HEXADECIMAL_39E539EA 0x39E539EA   /* was DAT_00115070 (word at 0x00115070); value 0x39E539EA (971323882) */
#define WORD_HEXADECIMAL_3975D3E2 0x3975D3E2   /* was DAT_00115074 (word at 0x00115074); value 0x3975D3E2 (964023266) */
#define WORD_HEXADECIMAL_143E4B90 0x143E4B90   /* was DAT_00115078 (word at 0x00115078); value 0x143E4B90 (339626896) */
#define WORD_HEXADECIMAL_1D6B0C6A 0x1D6B0C6A   /* was DAT_0011507c (word at 0x0011507C); value 0x1D6B0C6A (493554794) */
#define WORD_HEXADECIMAL_0AFEF300 0x0AFEF300   /* was DAT_00115080 (word at 0x00115080); value 0x0AFEF300 (184480512) */
#define WORD_HEXADECIMAL_25B1F018 0x25B1F018   /* was DAT_00115088 (word at 0x00115088); value 0x25B1F018 (632418328) */
#define WORD_HEXADECIMAL_0085100C 0x0085100C   /* was DAT_0011508c (word at 0x0011508C); value 0x0085100C (8720396) */
#define WORD_HEXADECIMAL_06110A54 0x06110A54   /* was DAT_00115090 (word at 0x00115090); value 0x06110A54 (101780052) */
#define WORD_HEXADECIMAL_2B8AB074 0x2B8AB074   /* was DAT_00115094 (word at 0x00115094); value 0x2B8AB074 (730509428) */
#define WORD_HEXADECIMAL_22FC52E2 0x22FC52E2   /* was DAT_00115098 (word at 0x00115098); value 0x22FC52E2 (586961634) */
#define WORD_HEXADECIMAL_3F185CDD 0x3F185CDD   /* was DAT_0011509c (word at 0x0011509C); value 0x3F185CDD (1058561245) */
#define WORD_HEXADECIMAL_063765F8 0x063765F8   /* was DAT_001150a0 (word at 0x001150A0); value 0x063765F8 (104293880) */
#define WORD_HEXADECIMAL_27BD4923 0x27BD4923   /* was DAT_001150a4 (word at 0x001150A4); value 0x27BD4923 (666716451) */
#define WORD_HEXADECIMAL_301CA7B2 0x301CA7B2   /* was DAT_001150a8 (word at 0x001150A8); value 0x301CA7B2 (807184306) */
#define WORD_HEXADECIMAL_31C58CC3 0x31C58CC3   /* was DAT_001150ac (word at 0x001150AC); value 0x31C58CC3 (835030211) */
#define WORD_HEXADECIMAL_384A929A 0x384A929A   /* was DAT_001150b0 (word at 0x001150B0); value 0x384A929A (944411290) */
#define WORD_HEXADECIMAL_139B6934 0x139B6934   /* was DAT_001150b4 (word at 0x001150B4); value 0x139B6934 (328952116) */
#define WORD_HEXADECIMAL_FFFEAED0 0xFFFEAED0   /* was DAT_00115e34 (word at 0x00115E34); value 0xFFFEAED0 (-86320) */
#define WORD_HEXADECIMAL_FFFEA960 0xFFFEA960   /* was DAT_00115e70 (word at 0x00115E70); value 0xFFFEA960 (-87712) */
#define WORD_HEXADECIMAL_FFFEA8DC 0xFFFEA8DC   /* was DAT_00115e80 (word at 0x00115E80); value 0xFFFEA8DC (-87844) */
#define WORD_HEXADECIMAL_FFFEA72C 0xFFFEA72C   /* was DAT_00115eb0 (word at 0x00115EB0); value 0xFFFEA72C (-88276) */
#define WORD_HEXADECIMAL_FFFEA60C 0xFFFEA60C   /* was DAT_00115ec4 (word at 0x00115EC4); value 0xFFFEA60C (-88564) */
#define WORD_HEXADECIMAL_FFFEA428 0xFFFEA428   /* was DAT_00115efc (word at 0x00115EFC); value 0xFFFEA428 (-89048) */
#define WORD_HEXADECIMAL_FFFE9FAC 0xFFFE9FAC   /* was DAT_0011699c (word at 0x0011699C); value 0xFFFE9FAC (-90196) */
#define WORD_HEXADECIMAL_FFFE9E00 0xFFFE9E00   /* was DAT_001169bc (word at 0x001169BC); value 0xFFFE9E00 (-90624) */
#define FLOAT_60 0x42700000   /* was DAT_001169cc, DAT_00121aa0, DAT_00121c60 (word at 0x001169CC); the float 60.0 */
#define FLOAT_80 0x42A00000   /* was DAT_001169d4 (word at 0x001169D4); the float 80.0 */
#define FLOAT_25 0x41C80000   /* was DAT_001169dc, DAT_00117884 (word at 0x001169DC); the float 25.0 */
#define WORD_HEXADECIMAL_FFFE9CFC 0xFFFE9CFC   /* was DAT_001169e8 (word at 0x001169E8); value 0xFFFE9CFC (-90884) */
#define WORD_HEXADECIMAL_FFFE9C8C 0xFFFE9C8C   /* was DAT_001169f4 (word at 0x001169F4); value 0xFFFE9C8C (-90996) */
#define WORD_HEXADECIMAL_FFFE977C 0xFFFE977C   /* was DAT_00116a78 (word at 0x00116A78); value 0xFFFE977C (-92292) */
#define WORD_HEXADECIMAL_FFFE94F0 0xFFFE94F0   /* was DAT_001173d8 (word at 0x001173D8); value 0xFFFE94F0 (-92944) */
#define WORD_HEXADECIMAL_FFFE93F0 0xFFFE93F0   /* was DAT_001173ec (word at 0x001173EC); value 0xFFFE93F0 (-93200) */
#define WORD_HEXADECIMAL_FFFE92D8 0xFFFE92D8   /* was DAT_00117414 (word at 0x00117414); value 0xFFFE92D8 (-93480) */
#define WORD_HEXADECIMAL_FFFE8FE0 0xFFFE8FE0   /* was DAT_0011746c (word at 0x0011746C); value 0xFFFE8FE0 (-94240) */
#define WORD_HEXADECIMAL_FFFE8F88 0xFFFE8F88   /* was DAT_00117474 (word at 0x00117474); value 0xFFFE8F88 (-94328) */
#define INTEGER_450 0x000001C2   /* was DAT_0011787c (word at 0x0011787C); integer 450 */
#define FLOAT_0_POINT_004 0x3B83126F   /* was DAT_00117880 (word at 0x00117880); the float 0.004000000189989805 */
#define INTEGER_2500 0x000009C4   /* was DAT_00117888 (word at 0x00117888); integer 2500 */
#define FLOAT_0_POINT_8 0x3F4CCCCD   /* was DAT_0011788c (word at 0x0011788C); the float 0.800000011920929 */
#define WORD_HEXADECIMAL_3C98CA25 0x3C98CA25   /* was DAT_00117890 (word at 0x00117890); value 0x3C98CA25 (1016646181) */
#define WORD_HEXADECIMAL_18C9AD7E 0x18C9AD7E   /* was DAT_00117894 (word at 0x00117894); value 0x18C9AD7E (415870334) */
#define WORD_HEXADECIMAL_2E2C2521 0x2E2C2521   /* was DAT_00117898 (word at 0x00117898); value 0x2E2C2521 (774645025) */
#define WORD_HEXADECIMAL_321D07F5 0x321D07F5   /* was DAT_0011789c (word at 0x0011789C); value 0x321D07F5 (840763381) */
#define WORD_HEXADECIMAL_16069583 0x16069583   /* was DAT_001178a0 (word at 0x001178A0); value 0x16069583 (369530243) */
#define WORD_HEXADECIMAL_30DA3260 0x30DA3260   /* was DAT_001178a4 (word at 0x001178A4); value 0x30DA3260 (819606112) */
#define WORD_HEXADECIMAL_05F2CB9B 0x05F2CB9B   /* was DAT_001178a8 (word at 0x001178A8); value 0x05F2CB9B (99797915) */
#define WORD_HEXADECIMAL_26F0194F 0x26F0194F   /* was DAT_001178ac (word at 0x001178AC); value 0x26F0194F (653269327) */
#define WORD_HEXADECIMAL_1EC99F85 0x1EC99F85   /* was DAT_001178b0 (word at 0x001178B0); value 0x1EC99F85 (516530053) */
#define WORD_HEXADECIMAL_135FFBD8 0x135FFBD8   /* was DAT_001178b4 (word at 0x001178B4); value 0x135FFBD8 (325057496) */
#define WORD_HEXADECIMAL_020A2432 0x020A2432   /* was DAT_001178b8 (word at 0x001178B8); value 0x020A2432 (34219058) */
#define WORD_HEXADECIMAL_3D8F67C0 0x3D8F67C0   /* was DAT_001178bc (word at 0x001178BC); value 0x3D8F67C0 (1032808384) */
#define WORD_HEXADECIMAL_1162331F 0x1162331F   /* was DAT_001178c0 (word at 0x001178C0); value 0x1162331F (291648287) */
#define WORD_HEXADECIMAL_02371D2F 0x02371D2F   /* was DAT_001178c4 (word at 0x001178C4); value 0x02371D2F (37166383) */
#define WORD_HEXADECIMAL_0742CA62 0x0742CA62   /* was DAT_001178c8 (word at 0x001178C8); value 0x0742CA62 (121817698) */
#define WORD_HEXADECIMAL_10BCB1F3 0x10BCB1F3   /* was DAT_001178cc (word at 0x001178CC); value 0x10BCB1F3 (280801779) */
#define WORD_HEXADECIMAL_1A369984 0x1A369984   /* was DAT_001178d0 (word at 0x001178D0); value 0x1A369984 (439785860) */
#define WORD_HEXADECIMAL_23B08115 0x23B08115   /* was DAT_001178d4 (word at 0x001178D4); value 0x23B08115 (598769941) */
#define WORD_HEXADECIMAL_2D2A68A6 0x2D2A68A6   /* was DAT_001178d8 (word at 0x001178D8); value 0x2D2A68A6 (757754022) */
#define WORD_HEXADECIMAL_36A45037 0x36A45037   /* was DAT_001178dc (word at 0x001178DC); value 0x36A45037 (916738103) */
#define WORD_HEXADECIMAL_001E37C8 0x001E37C8   /* was DAT_001178e0 (word at 0x001178E0); value 0x001E37C8 (1980360) */
#define WORD_HEXADECIMAL_09981F59 0x09981F59   /* was DAT_001178e4 (word at 0x001178E4); value 0x09981F59 (160964441) */
#define WORD_HEXADECIMAL_1C67FA2B 0x1C67FA2B   /* was DAT_001178e8 (word at 0x001178E8); value 0x1C67FA2B (476576299) */
#define WORD_HEXADECIMAL_08FE919D 0x08FE919D   /* was DAT_001178ec (word at 0x001178EC); value 0x08FE919D (150901149) */
#define WORD_HEXADECIMAL_1EE299BF 0x1EE299BF   /* was DAT_001178f0 (word at 0x001178F0); value 0x1EE299BF (518166975) */
#define WORD_HEXADECIMAL_1C0CA328 0x1C0CA328   /* was DAT_001178f4 (word at 0x001178F4); value 0x1C0CA328 (470590248) */
#define WORD_HEXADECIMAL_21E5FC16 0x21E5FC16   /* was DAT_001178f8 (word at 0x001178F8); value 0x21E5FC16 (568720406) */
#define WORD_HEXADECIMAL_03EABB3E 0x03EABB3E   /* was DAT_001178fc (word at 0x001178FC); value 0x03EABB3E (65715006) */
#define WORD_HEXADECIMAL_17A9534F 0x17A9534F   /* was DAT_00117910 (word at 0x00117910); value 0x17A9534F (396972879) */
#define WORD_HEXADECIMAL_33F82B3B 0x33F82B3B   /* was DAT_00117914 (word at 0x00117914); value 0x33F82B3B (871902011) */
#define WORD_HEXADECIMAL_2CBD096F 0x2CBD096F   /* was DAT_00117918 (word at 0x00117918); value 0x2CBD096F (750586223) */
#define WORD_HEXADECIMAL_0E72A518 0x0E72A518   /* was DAT_0011791c (word at 0x0011791C); value 0x0E72A518 (242394392) */
#define WORD_HEXADECIMAL_3BBF0731 0x3BBF0731   /* was DAT_00117928 (word at 0x00117928); value 0x3BBF0731 (1002374961) */
#define WORD_HEXADECIMAL_3310565C 0x3310565C   /* was DAT_0011792c (word at 0x0011792C); value 0x3310565C (856708700) */
#define WORD_HEXADECIMAL_2A422940 0x2A422940   /* was DAT_00117930 (word at 0x00117930); value 0x2A422940 (708979008) */
#define WORD_HEXADECIMAL_34F936B3 0x34F936B3   /* was DAT_00117934 (word at 0x00117934); value 0x34F936B3 (888747699) */
#define WORD_HEXADECIMAL_0B006C66 0x0B006C66   /* was DAT_00117938 (word at 0x00117938); value 0x0B006C66 (184577126) */
#define WORD_HEXADECIMAL_1771A3B6 0x1771A3B6   /* was DAT_0011793c (word at 0x0011793C); value 0x1771A3B6 (393323446) */
#define WORD_HEXADECIMAL_058217BC 0x058217BC   /* was DAT_00117940 (word at 0x00117940); value 0x058217BC (92411836) */
#define FLOAT_1_POINT_8 0x3FE66666   /* was DAT_00117944 (word at 0x00117944); the float 1.7999999523162842 */
#define WORD_HEXADECIMAL_330B8247 0x330B8247   /* was DAT_00117948 (word at 0x00117948); value 0x330B8247 (856392263) */
#define WORD_HEXADECIMAL_179CB9BC 0x179CB9BC   /* was DAT_0011794c (word at 0x0011794C); value 0x179CB9BC (396147132) */
#define WORD_HEXADECIMAL_223FF5EF 0x223FF5EF   /* was DAT_00117950 (word at 0x00117950); value 0x223FF5EF (574617071) */
#define WORD_HEXADECIMAL_15BD4DA8 0x15BD4DA8   /* was DAT_00117954 (word at 0x00117954); value 0x15BD4DA8 (364727720) */
#define FLOAT_0_POINT_002 0x3B03126F   /* was DAT_00117958 (word at 0x00117958); the float 0.0020000000949949026 */
#define FLOAT_2_POINT_5 0x40200000   /* was DAT_0011795c (word at 0x0011795C); the float 2.5 */
#define FLOAT_1_POINT_2 0x3F99999A   /* was DAT_00117960 (word at 0x00117960); the float 1.2000000476837158 */
#define WORD_HEXADECIMAL_2E9E50CA 0x2E9E50CA   /* was DAT_00117964 (word at 0x00117964); value 0x2E9E50CA (782127306) */
#define WORD_HEXADECIMAL_005C2F5D 0x005C2F5D   /* was DAT_00117968 (word at 0x00117968); value 0x005C2F5D (6041437) */
#define WORD_HEXADECIMAL_295F33B7 0x295F33B7   /* was DAT_0011796c (word at 0x0011796C); value 0x295F33B7 (694105015) */
#define WORD_HEXADECIMAL_360966DC 0x360966DC   /* was DAT_00117970 (word at 0x00117970); value 0x360966DC (906585820) */
#define WORD_HEXADECIMAL_04B962AA 0x04B962AA   /* was DAT_00117974 (word at 0x00117974); value 0x04B962AA (79258282) */
#define WORD_HEXADECIMAL_23AA2F90 0x23AA2F90   /* was DAT_00117ca0 (word at 0x00117CA0); value 0x23AA2F90 (598355856) */
#define WORD_HEXADECIMAL_017C378A 0x017C378A   /* was DAT_00117ca4 (word at 0x00117CA4); value 0x017C378A (24917898) */
#define WORD_HEXADECIMAL_2CAC1C93 0x2CAC1C93   /* was DAT_00117ca8 (word at 0x00117CA8); value 0x2CAC1C93 (749477011) */
#define WORD_HEXADECIMAL_29D625FC 0x29D625FC   /* was DAT_00117cac (word at 0x00117CAC); value 0x29D625FC (701900284) */
#define WORD_HEXADECIMAL_141C7942 0x141C7942   /* was DAT_00117cb0 (word at 0x00117CB0); value 0x141C7942 (337410370) */
#define WORD_HEXADECIMAL_2D335E68 0x2D335E68   /* was DAT_00117cb4 (word at 0x00117CB4); value 0x2D335E68 (758341224) */
#define WORD_HEXADECIMAL_1C8CAB35 0x1C8CAB35   /* was DAT_00117cb8 (word at 0x00117CB8); value 0x1C8CAB35 (478980917) */
#define FLOAT_6_POINT_6 0x40D33333   /* was DAT_00117cbc (word at 0x00117CBC); the float 6.599999904632568 */
#define INTEGER_3500 0x00000DAC   /* was DAT_00117cc0 (word at 0x00117CC0); integer 3500 */
#define INTEGER_1500 0x000005DC   /* was DAT_00117cc4, DAT_0011d6a8 (word at 0x00117CC4); integer 1500 */
#define WORD_HEXADECIMAL_02411B7F 0x02411B7F   /* was DAT_00117cc8 (word at 0x00117CC8); value 0x02411B7F (37821311) */
#define WORD_HEXADECIMAL_2F6D981B 0x2F6D981B   /* was DAT_00117ccc (word at 0x00117CCC); value 0x2F6D981B (795711515) */
#define WORD_HEXADECIMAL_19A4546C 0x19A4546C   /* was DAT_00117cd0 (word at 0x00117CD0); value 0x19A4546C (430199916) */
#define WORD_HEXADECIMAL_25D8BC39 0x25D8BC39   /* was DAT_00117cd4 (word at 0x00117CD4); value 0x25D8BC39 (634960953) */
#define FLOAT_0_POINT_2 0x3E4CCCCD   /* was DAT_00117cd8 (word at 0x00117CD8); the float 0.20000000298023224 */
#define WORD_HEXADECIMAL_23855817 0x23855817   /* was DAT_00117cdc (word at 0x00117CDC); value 0x23855817 (595941399) */
#define WORD_HEXADECIMAL_3FBCD43A 0x3FBCD43A   /* was DAT_00117ce0 (word at 0x00117CE0); value 0x3FBCD43A (1069339706) */
#define WORD_HEXADECIMAL_29D8CC18 0x29D8CC18   /* was DAT_00117ce4 (word at 0x00117CE4); value 0x29D8CC18 (702073880) */
#define WORD_HEXADECIMAL_2CAEC2AF 0x2CAEC2AF   /* was DAT_00117ce8 (word at 0x00117CE8); value 0x2CAEC2AF (749650607) */
#define WORD_HEXADECIMAL_155E9E13 0x155E9E13   /* was DAT_00117cec (word at 0x00117CEC); value 0x155E9E13 (358522387) */
#define WORD_HEXADECIMAL_3197DD02 0x3197DD02   /* was DAT_00117cf0 (word at 0x00117CF0); value 0x3197DD02 (832036098) */
#define WORD_HEXADECIMAL_0B7AAABB 0x0B7AAABB   /* was DAT_00117cf4 (word at 0x00117CF4); value 0x0B7AAABB (192588475) */
#define WORD_HEXADECIMAL_3361FA4C 0x3361FA4C   /* was DAT_00117cf8 (word at 0x00117CF8); value 0x3361FA4C (862059084) */
#define WORD_HEXADECIMAL_00C562E9 0x00C562E9   /* was DAT_00117cfc (word at 0x00117CFC); value 0x00C562E9 (12935913) */
#define WORD_HEXADECIMAL_265F63F0 0x265F63F0   /* was DAT_00117d00 (word at 0x00117D00); value 0x265F63F0 (643785712) */
#define WORD_HEXADECIMAL_26A2B37F 0x26A2B37F   /* was DAT_00117d04 (word at 0x00117D04); value 0x26A2B37F (648196991) */
#define WORD_HEXADECIMAL_211F0585 0x211F0585   /* was DAT_00117d08 (word at 0x00117D08); value 0x211F0585 (555681157) */
#define WORD_HEXADECIMAL_2850567E 0x2850567E   /* was DAT_00117d10 (word at 0x00117D10); value 0x2850567E (676353662) */
#define WORD_HEXADECIMAL_1A44BF58 0x1A44BF58   /* was DAT_00117d14 (word at 0x00117D14); value 0x1A44BF58 (440713048) */
#define WORD_HEXADECIMAL_31B8F8BC 0x31B8F8BC   /* was DAT_00117d18 (word at 0x00117D18); value 0x31B8F8BC (834205884) */
#define WORD_HEXADECIMAL_3A03126F 0x3A03126F   /* was DAT_00117d1c (word at 0x00117D1C); value 0x3A03126F (973279855) */
#define WORD_HEXADECIMAL_08A18ABF 0x08A18ABF   /* was DAT_00117d20 (word at 0x00117D20); value 0x08A18ABF (144804543) */
#define WORD_HEXADECIMAL_11218F6E 0x11218F6E   /* was DAT_00117d24 (word at 0x00117D24); value 0x11218F6E (287412078) */
#define WORD_HEXADECIMAL_2E48DA58 0x2E48DA58   /* was DAT_00117d28 (word at 0x00117D28); value 0x2E48DA58 (776526424) */
#define WORD_HEXADECIMAL_369F84CA 0x369F84CA   /* was DAT_001180ac (word at 0x001180AC); value 0x369F84CA (916423882) */
#define WORD_HEXADECIMAL_0B63154F 0x0B63154F   /* was DAT_001180b0 (word at 0x001180B0); value 0x0B63154F (191042895) */
#define WORD_HEXADECIMAL_26B58FD6 0x26B58FD6   /* was DAT_001180c0 (word at 0x001180C0); value 0x26B58FD6 (649433046) */
#define WORD_HEXADECIMAL_3488ACED 0x3488ACED   /* was DAT_00118304 (word at 0x00118304); value 0x3488ACED (881372397) */
#define WORD_HEXADECIMAL_1DED5D32 0x1DED5D32   /* was DAT_00118314 (word at 0x00118314); value 0x1DED5D32 (502095154) */
#define WORD_HEXADECIMAL_2073D363 0x2073D363   /* was DAT_00118604 (word at 0x00118604); value 0x2073D363 (544461667) */
#define WORD_HEXADECIMAL_1932DEDD 0x1932DEDD   /* was DAT_00118608 (word at 0x00118608); value 0x1932DEDD (422764253) */
#define WORD_HEXADECIMAL_1218EC09 0x1218EC09   /* was DAT_00118610 (word at 0x00118610); value 0x1218EC09 (303623177) */
#define WORD_HEXADECIMAL_0F846A96 0x0F846A96   /* was DAT_00118620 (word at 0x00118620); value 0x0F846A96 (260336278) */
#define WORD_HEXADECIMAL_0D44B786 0x0D44B786   /* was DAT_00118624 (word at 0x00118624); value 0x0D44B786 (222607238) */
#define WORD_HEXADECIMAL_1DFBEC7F 0x1DFBEC7F   /* was DAT_00118628, DAT_0011ba08 (word at 0x00118628); value 0x1DFBEC7F (503049343) */
#define WORD_HEXADECIMAL_314D49C5 0x314D49C5   /* was DAT_0011862c (word at 0x0011862C); value 0x314D49C5 (827148741) */
#define WORD_HEXADECIMAL_0A893452 0x0A893452   /* was DAT_00118630 (word at 0x00118630); value 0x0A893452 (176763986) */
#define WORD_HEXADECIMAL_2BB0C920 0x2BB0C920   /* was DAT_00118638 (word at 0x00118638); value 0x2BB0C920 (733006112) */
#define WORD_HEXADECIMAL_19DB98DB 0x19DB98DB   /* was DAT_0011863c (word at 0x0011863C); value 0x19DB98DB (433821915) */
#define WORD_HEXADECIMAL_13EB8A28 0x13EB8A28   /* was DAT_001188f8 (word at 0x001188F8); value 0x13EB8A28 (334203432) */
#define WORD_HEXADECIMAL_155EAFB5 0x155EAFB5   /* was DAT_00118904 (word at 0x00118904); value 0x155EAFB5 (358526901) */
#define WORD_HEXADECIMAL_2E583064 0x2E583064   /* was DAT_00118908 (word at 0x00118908); value 0x2E583064 (777531492) */
#define WORD_HEXADECIMAL_275AA16E 0x275AA16E   /* was DAT_0011890c (word at 0x0011890C); value 0x275AA16E (660250990) */
#define WORD_HEXADECIMAL_178BD97D 0x178BD97D   /* was DAT_00118e90 (word at 0x00118E90); value 0x178BD97D (395041149) */
#define WORD_HEXADECIMAL_FFFE768C 0xFFFE768C   /* was DAT_00118e94 (word at 0x00118E94); value 0xFFFE768C (-100724) */
#define WORD_HEXADECIMAL_18FC8335 0x18FC8335   /* was DAT_00118ea4 (word at 0x00118EA4); value 0x18FC8335 (419201845) */
#define WORD_HEXADECIMAL_3310A2A1 0x3310A2A1   /* was DAT_00118ea8 (word at 0x00118EA8); value 0x3310A2A1 (856728225) */
#define WORD_HEXADECIMAL_0B090BAC 0x0B090BAC   /* was DAT_00118eac (word at 0x00118EAC); value 0x0B090BAC (185142188) */
#define WORD_HEXADECIMAL_08E8548D 0x08E8548D   /* was DAT_00118eb0 (word at 0x00118EB0); value 0x08E8548D (149443725) */
#define WORD_HEXADECIMAL_19631267 0x19631267   /* was DAT_00118eb4 (word at 0x00118EB4); value 0x19631267 (425923175) */
#define WORD_HEXADECIMAL_2101870D 0x2101870D   /* was DAT_00118eb8 (word at 0x00118EB8); value 0x2101870D (553748237) */
#define WORD_HEXADECIMAL_32CA0CC6 0x32CA0CC6   /* was DAT_00118ec4 (word at 0x00118EC4); value 0x32CA0CC6 (852102342) */
#define WORD_HEXADECIMAL_FFFE70A8 0xFFFE70A8   /* was DAT_00119598 (word at 0x00119598); value 0xFFFE70A8 (-102232) */
#define WORD_HEXADECIMAL_FFFE6FA8 0xFFFE6FA8   /* was DAT_001195b0 (word at 0x001195B0); value 0xFFFE6FA8 (-102488) */
#define WORD_HEXADECIMAL_FFFE6C24 0xFFFE6C24   /* was DAT_001195d4 (word at 0x001195D4); value 0xFFFE6C24 (-103388) */
#define CLASS_IDENTIFIER_HEXADECIMAL_0100A004 0x0100A004   /* was DAT_001199fc (word at 0x001199FC); in the BREW class identifier range */
#define INTEGER_261 0x00000105   /* was DAT_00119a00 (word at 0x00119A00); integer 261 */
#define AEECLSID_SWERVE_VALUE 0x0102BBFC   /* was DAT_00119a04 (word at 0x00119A04); BREW class identifier AEECLSID_SWERVE */
#define INTEGER_262 0x00000106   /* was DAT_00119a08 (word at 0x00119A08); integer 262 */
#define INTEGER_263 0x00000107   /* was DAT_00119a0c, DAT_0011b9fc, DAT_00124654 (word at 0x00119A0C); integer 263 */
#define AEECLSID_DIB_VALUE 0x01001045   /* was DAT_00119a10 (word at 0x00119A10); BREW class identifier AEECLSID_DIB */
#define INTEGER_265 0x00000109   /* was DAT_00119a14 (word at 0x00119A14); integer 265 */
#define TEXT_30 0x28500339   /* was DAT_00119a18 (word at 0x00119A18); the text id of
                                "30" (language.m3g) */
#define INTEGER_258 0x00000102   /* was DAT_00119a20 (word at 0x00119A20); integer 258 */
#define INTEGER_257 0x00000101   /* was DAT_00119a24 (word at 0x00119A24); integer 257 */
#define WORD_HEXADECIMAL_018B5704 0x018B5704   /* was DAT_00119c00 (word at 0x00119C00); value 0x018B5704 (25908996) */
#define WORD_HEXADECIMAL_FFFE646C 0xFFFE646C   /* was DAT_00119c0c (word at 0x00119C0C); value 0xFFFE646C (-105364) */
#define WORD_HEXADECIMAL_38D1B717 0x38D1B717   /* was DAT_0011a2f0 (word at 0x0011A2F0); value 0x38D1B717 (953267991) */
#define WORD_HEXADECIMAL_FFFE5718 0xFFFE5718   /* was DAT_0011aa64 (word at 0x0011AA64); value 0xFFFE5718 (-108776) */
#define DOUBLE_0_POINT_0175_LOW_WORD  0x1EB851EC   /* was DAT_0011adb8 (word at 0x0011ADB8): the
                                                    low word of the double 0.0175, FUN_0011abc4's
                                                    degrees to radians */
#define DOUBLE_0_POINT_0175_HIGH_WORD 0x3F91EB85   /* was DAT_0011adbc (word at 0x0011ADBC): its high word
                                                    (not a float, though the bits read as 1.14) */
#define WORD_HEXADECIMAL_3E11FC00 0x3E11FC00   /* was DAT_0011ba00 (word at 0x0011BA00); value 0x3E11FC00 (1041366016) */
#define INTEGER_3003 0x00000BBB   /* was DAT_0011c6ec (word at 0x0011C6EC); integer 3003 */
#define INTEGER_7000 0x00001B58   /* was DAT_0011c6f8 (word at 0x0011C6F8); integer 7000 */
#define FLOAT_350 0x43AF0000   /* was DAT_0011c6fc (word at 0x0011C6FC); the float 350.0 */
#define INTEGER_3002 0x00000BBA   /* was DAT_0011c700 (word at 0x0011C700); integer 3002 */
#define FLOAT_0_POINT_000001 0x358637BD   /* was DAT_0011c704 (word at 0x0011C704); the float 0.000001 */
#define INTEGER_42736 0x0000A6F0   /* was DAT_0011c858 (word at 0x0011C858); integer 42736 */
#define INTEGER_4002 0x00000FA2   /* was DAT_0011ca68 (word at 0x0011CA68); integer 4002 */
#define INTEGER_2003 0x000007D3   /* was DAT_0011d3e0, DAT_0011d6a4 (word at 0x0011D3E0); integer 2003 */
#define INTEGER_2010 0x000007DA   /* was DAT_0011d3e8 (word at 0x0011D3E8); integer 2010 */
#define INTEGER_3001 0x00000BB9   /* was DAT_0011d6a0, DAT_0011db30, DAT_0011ded0 (word at 0x0011D6A0); integer 3001 */
#define FLOAT_4 0x40800000   /* was DAT_0011d6ac (word at 0x0011D6AC); the float 4.0 */
#define INTEGER_2002 0x000007D2   /* was DAT_0011d6b0 (word at 0x0011D6B0); integer 2002 */
#define INTEGER_2005 0x000007D5   /* was DAT_0011d6b4 (word at 0x0011D6B4); integer 2005 */
#define INTEGER_2006 0x000007D6   /* was DAT_0011d6b8 (word at 0x0011D6B8); integer 2006 */
#define INTEGER_2008 0x000007D8   /* was DAT_0011d6c0 (word at 0x0011D6C0); integer 2008 */
#define INTEGER_2009 0x000007D9   /* was DAT_0011d6c4 (word at 0x0011D6C4); integer 2009 */
#define INTEGER_2001 0x000007D1   /* was DAT_0011d6c8 (word at 0x0011D6C8); integer 2001 */
#define FLOAT_9 0x41100000   /* was DAT_0011da8c, DAT_0011db2c (word at 0x0011DA8C); the float 9.0 */
#define FLOAT_360 0x43B40000   /* was DAT_0011da90 (word at 0x0011DA90); the float 360.0 */
#define FLOAT_250 0x437A0000   /* was DAT_0011da9c (word at 0x0011DA9C); the float 250.0 */
#define INTEGER_6003 0x00001773   /* was DAT_0011daa0 (word at 0x0011DAA0); integer 6003 */
#define INTEGER_6001 0x00001771   /* was DAT_0011daa4 (word at 0x0011DAA4); integer 6001 */
#define WORD_HEXADECIMAL_267C603F 0x267C603F   /* was DAT_0011daa8 (word at 0x0011DAA8); value 0x267C603F (645685311) */
#define INTEGER_7002 0x00001B5A   /* was DAT_0011dc8c (word at 0x0011DC8C); integer 7002 */
#define INTEGER_7003 0x00001B5B   /* was DAT_0011dc98 (word at 0x0011DC98); integer 7003 */
#define INTEGER_4001 0x00000FA1   /* was DAT_0011ded4 (word at 0x0011DED4); integer 4001 */
#define INTEGER_7001 0x00001B59   /* was DAT_0011ded8 (word at 0x0011DED8); integer 7001 */
#define INTEGER_31544 0x00007B38   /* was DAT_0011f390 (word at 0x0011F390); integer 31544 */
#define FLOAT_0_POINT_85 0x3F59999A   /* was DAT_0011f7d0 (word at 0x0011F7D0); the float 0.8500000238418579 */
#define INTEGER_29864 0x000074A8   /* was DAT_0011fc7c (word at 0x0011FC7C); integer 29864 */
#define WORD_HEXADECIMAL_FFFE01FC 0xFFFE01FC   /* was DAT_0011fed0 (word at 0x0011FED0); value 0xFFFE01FC (-130564) */
#define WORD_HEXADECIMAL_FFFE00F0 0xFFFE00F0   /* was DAT_0011ffbc (word at 0x0011FFBC); value 0xFFFE00F0 (-130832) */
#define WORD_HEXADECIMAL_FFFDFEBC 0xFFFDFEBC   /* was DAT_001201c8 (word at 0x001201C8); value 0xFFFDFEBC (-131396) */
#define WORD_HEXADECIMAL_FFFDFC48 0xFFFDFC48   /* was DAT_00120440 (word at 0x00120440); value 0xFFFDFC48 (-132024) */
#define WORD_HEXADECIMAL_009660B3 0x009660B3   /* was DAT_00121124, DAT_001213e0 (word at 0x00121124); value 0x009660B3 (9855155) */
#define WORD_HEXADECIMAL_019E5BAF 0x019E5BAF   /* was DAT_00121128 (word at 0x00121128); value 0x019E5BAF (27155375) */
#define WORD_HEXADECIMAL_FFFDE350 0xFFFDE350   /* was DAT_00122438 (word at 0x00122438); value 0xFFFDE350 (-138416) */
#define WORD_HEXADECIMAL_1A5C2C12 0x1A5C2C12   /* was DAT_00122448 (word at 0x00122448); value 0x1A5C2C12 (442248210) */
#define INTEGER_1002 0x000003EA   /* was DAT_00122b88 (word at 0x00122B88); integer 1002 */
#define INTEGER_1003 0x000003EB   /* was DAT_00122b8c (word at 0x00122B8C); integer 1003 */
#define WORD_HEXADECIMAL_11E3EE3E 0x11E3EE3E   /* was DAT_00123128 (word at 0x00123128); value 0x11E3EE3E (300150334) */
#define WORD_HEXADECIMAL_3FC90FD8 0x3FC90FD8   /* was DAT_00123568 (word at 0x00123568); value 0x3FC90FD8 (1070141400) */
#define DOUBLE_0_POINT_01_LOW_WORD  0x47AE147B   /* was DAT_0012356c (word at 0x0012356C): the low
                                                  word of the double 0.01, FUN_0012312c's compare */
#define DOUBLE_0_POINT_01_HIGH_WORD 0x3F847AE1   /* was DAT_00123570 (word at 0x00123570): its high
                                                  word (not a float, though the bits read as 1.035) */
#define WORD_HEXADECIMAL_22735D97 0x22735D97   /* was DAT_00123c10 (word at 0x00123C10); value 0x22735D97 (577985943) */
#define WORD_HEXADECIMAL_1812C1C3 0x1812C1C3   /* was DAT_00123c20 (word at 0x00123C20); value 0x1812C1C3 (403882435) */
#define INTEGER_4467 0x00001173   /* was DAT_001242b0 (word at 0x001242B0); integer 4467 */
#define WORD_HEXADECIMAL_FFFDBD34 0xFFFDBD34   /* was DAT_00124650 (word at 0x00124650); value 0xFFFDBD34 (-148172) */
#define WORD_HEXADECIMAL_04000088 0x04000088   /* was DAT_00124950 (word at 0x00124950); value 0x04000088 (67109000) */
#define WORD_HEXADECIMAL_04000012 0x04000012   /* was DAT_00124e14 (word at 0x00124E14); value 0x04000012 (67108882) */
#define WORD_HEXADECIMAL_7FF00000 0x7FF00000   /* was DAT_001254c8, DAT_001259e0 (word at 0x001254C8); value 0x7FF00000 (2146435072) */
#define WORD_HEXADECIMAL_08000014 0x08000014   /* was DAT_001254cc (word at 0x001254CC); value 0x08000014 (134217748) */
#define WORD_HEXADECIMAL_04000014 0x04000014   /* was DAT_001254d0 (word at 0x001254D0); value 0x04000014 (67108884) */
#define WORD_HEXADECIMAL_04120019 0x04120019   /* was DAT_00125550 (word at 0x00125550); value 0x04120019 (68288537) */
#define WORD_HEXADECIMAL_040200C8 0x040200C8   /* was DAT_001255f4 (word at 0x001255F4); value 0x040200C8 (67240136) */
#define WORD_HEXADECIMAL_04130019 0x04130019   /* was DAT_001256b0 (word at 0x001256B0); value 0x04130019 (68354073) */
#define WORD_HEXADECIMAL_04160019 0x04160019   /* was DAT_00125730 (word at 0x00125730); value 0x04160019 (68550681) */
#define WORD_HEXADECIMAL_07FF0000 0x07FF0000u  /* was DAT_001259dc, DAT_00125cc8 (word at 0x001259DC); value 0x07FF0000 (134152192); also
                                                   ram0x001254c4 (word at 0x001254C4), the same value in
                                                   a literal pool Ghidra read as a memory variable */
#define WORD_HEXADECIMAL_04000013 0x04000013   /* was DAT_001259e4 (word at 0x001259E4); value 0x04000013 (67108883) */
#define WORD_HEXADECIMAL_04000015 0x04000015   /* was DAT_00125ccc (word at 0x00125CCC); value 0x04000015 (67108885) */
#define WORD_HEXADECIMAL_04000017 0x04000017   /* was DAT_00125eb0 (word at 0x00125EB0); value 0x04000017 (67108887) */
#define WORD_HEXADECIMAL_7F800000 0x7F800000   /* was DAT_00126234 (word at 0x00126234); value 0x7F800000 (2139095040) */
#define WORD_HEXADECIMAL_04000018 0x04000018   /* was DAT_001262ac (word at 0x001262AC); value 0x04000018 (67108888) */
#define WORD_HEXADECIMAL_04000004 0x04000004   /* was DAT_001267e8 (word at 0x001267E8); value 0x04000004 (67108868) */
#define WORD_HEXADECIMAL_08000004 0x08000004   /* was DAT_001267ec (word at 0x001267EC); value 0x08000004 (134217732) */
#define WORD_HEXADECIMAL_04120009 0x04120009   /* was DAT_00126854 (word at 0x00126854); value 0x04120009 (68288521) */
#define WORD_HEXADECIMAL_04020048 0x04020048   /* was DAT_001268bc (word at 0x001268BC); value 0x04020048 (67240008) */
#define WORD_HEXADECIMAL_04130009 0x04130009   /* was DAT_00126960 (word at 0x00126960); value 0x04130009 (68354057) */
#define WORD_HEXADECIMAL_04160009 0x04160009   /* was DAT_001269c8 (word at 0x001269C8); value 0x04160009 (68550665) */

/* ---- Double-precision literal pairs (low word, high word), named by value ----------------
   The first naming pass missed these pairs and named each word on its own. */
#define TEXT_NEW_HIGH_SCORE 0x2FDE3CD0   /* was DAT_00102b78 (word at 0x00102B78); the text id of
                                         "You have a new high score! Would you like to post it to
                                         the server and get a ranking ?" (language.m3g) */
#define TEXT_HIGH_SCORE 0x3BD468F7   /* was DAT_00102b7c (word at 0x00102B7C); the text id of
                                         "HIGH SCORE" (language.m3g) */
#define DOUBLE_1_POINT_1_LOW_WORD 0x9999999A   /* was DAT_00109a08 (word at 0x00109A08); with the word at 0x00109A0C: the double 1.1 = 0x3FF199999999999A */
#define DOUBLE_1_POINT_1_HIGH_WORD 0x3FF19999   /* was DAT_00109a0c (word at 0x00109A0C); with the word at 0x00109A08: the double 1.1 = 0x3FF199999999999A */
#define DOUBLE_7_POINT_112268678_TIMES_TEN_TO_THE_MINUS_32_LOW_WORD 0x43340000   /* was DAT_0010f874 (word at 0x0010F874); with the word at 0x0010F878: the double 7.112268678270473e-32 = 0x397714A443340000 */
#define DOUBLE_7_POINT_112268678_TIMES_TEN_TO_THE_MINUS_32_HIGH_WORD 0x397714A4   /* was DAT_0010f878 (word at 0x0010F878); with the word at 0x0010F874: the double 7.112268678270473e-32 = 0x397714A443340000 */
#define DOUBLE_MINUS_ONE_LOW_WORD 0x00000000   /* was DAT_0011345c, DAT_001195c8 (word at 0x0011345C); with the word at 0x00113460: the double -1.0 = 0xBFF0000000000000 */
#define DOUBLE_MINUS_ONE_HIGH_WORD 0xBFF00000   /* was DAT_00113460, DAT_001195cc (word at 0x00113460); with the word at 0x0011345C: the double -1.0 = 0xBFF0000000000000 */
#define DOUBLE_1_POINT_640496717_TIMES_TEN_TO_THE_MINUS_22_LOW_WORD 0x41800000   /* was DAT_00117908 (word at 0x00117908); with the word at 0x0011790C: the double 1.640496716623327e-22 = 0x3B68CA5D41800000 */
#define DOUBLE_1_POINT_640496717_TIMES_TEN_TO_THE_MINUS_22_HIGH_WORD 0x3B68CA5D   /* was DAT_0011790c (word at 0x0011790C); with the word at 0x00117908: the double 1.640496716623327e-22 = 0x3B68CA5D41800000 */
#define DOUBLE_7_POINT_317123473_TIMES_TEN_TO_THE_MINUS_9_LOW_WORD 0x28C0F86B   /* was DAT_00117920 (word at 0x00117920); with the word at 0x00117924: the double 7.317123473152145e-09 = 0x3E3F6D4328C0F86B */
#define DOUBLE_7_POINT_317123473_TIMES_TEN_TO_THE_MINUS_9_HIGH_WORD 0x3E3F6D43   /* was DAT_00117924 (word at 0x00117924); with the word at 0x00117920: the double 7.317123473152145e-09 = 0x3E3F6D4328C0F86B */
#define DOUBLE_800_LOW_WORD 0x00000000   /* was DAT_0011adc8 (word at 0x0011ADC8); with the word at 0x0011ADCC: the double 800.0 = 0x4089000000000000 */
#define DOUBLE_800_HIGH_WORD 0x40890000   /* was DAT_0011adcc (word at 0x0011ADCC); with the word at 0x0011ADC8: the double 800.0 = 0x4089000000000000 */
#define DOUBLE_180_LOW_WORD 0x00000000   /* was DAT_0011cbac (word at 0x0011CBAC); with the word at 0x0011CBB0: the double 180.0 = 0x4066800000000000 */
#define DOUBLE_180_HIGH_WORD 0x40668000   /* was DAT_0011cbb0 (word at 0x0011CBB0); with the word at 0x0011CBAC: the double 180.0 = 0x4066800000000000 */
#define DOUBLE_360_LOW_WORD 0x00000000   /* was DAT_0011cbb4 (word at 0x0011CBB4); with the word at 0x0011CBB8: the double 360.0 = 0x4076800000000000 */
#define DOUBLE_360_HIGH_WORD 0x40768000   /* was DAT_0011cbb8 (word at 0x0011CBB8); with the word at 0x0011CBB4: the double 360.0 = 0x4076800000000000 */
#define DOUBLE_MINUS_180_LOW_WORD 0x00000000   /* was DAT_0011cbbc (word at 0x0011CBBC); with the word at 0x0011CBC0: the double -180.0 = 0xC066800000000000 */
#define DOUBLE_MINUS_180_HIGH_WORD 0xC0668000   /* was DAT_0011cbc0 (word at 0x0011CBC0); with the word at 0x0011CBBC: the double -180.0 = 0xC066800000000000 */


/* ---- Literal-pool words, named automatically (second pass) ---------------------------------------
   Each was a Ghidra DAT_<address> label, named after its value (the PC-relative offsets among them
   are the data objects and function addresses at the end of this file now). The comment gives the old label(s),
   the word's address and how the name was derived. Generated, not reviewed one by one: names say
   what a word IS (its value or target), not necessarily what the code uses it for. */
#define TEXT_UPDATE 0x3B4C67C7   /* was DAT_00102b58 (word at 0x00102B58); the text id of
                                    "Update" (language.m3g) */
#define TEXT_BUY 0x0B259095   /* was DAT_00104c0c (word at 0x00104C0C); the text id of
                                 "Buy" (language.m3g) */
#define DOUBLE_4_POINT_5_LOW_WORD 0x00000000   /* was DAT_0010f86c (word at 0x0010F86C); with the word at 0x0010F870: the double 4.5 = 0x4012000000000000 */
#define DOUBLE_4_POINT_5_HIGH_WORD 0x40120000   /* was DAT_0010f870 (word at 0x0010F870); with the word at 0x0010F86C: the double 4.5 = 0x4012000000000000 */
#define TEXT_OPTIONS_ENTRY 0x083D247B   /* was DAT_001117c8 (word at 0x001117C8); the text id of
                                           "Options" (language.m3g) */
#define WORD_HEXADECIMAL_14F1CDC1 0x14F1CDC1   /* was DAT_00114b44 (word at 0x00114B44); value 0x14F1CDC1 (351391169) */
#define WORD_HEXADECIMAL_262A32C2 0x262A32C2   /* was DAT_0011cfd4 (word at 0x0011CFD4); value 0x262A32C2 (640299714) */
#define WORD_HEXADECIMAL_03AD1271 0x03AD1271   /* was DAT_00123564 (word at 0x00123564); value 0x03AD1271 (61674097) */
#define WORD_HEXADECIMAL_14FF65C5 0x14FF65C5   /* was DAT_00123c14 (word at 0x00123C14); value 0x14FF65C5 (352282053) */
#define WORD_HEXADECIMAL_25491361 0x25491361   /* was DAT_00123c18 (word at 0x00123C18); value 0x25491361 (625546081) */
#define WORD_HEXADECIMAL_38618576 0x38618576   /* was DAT_0012466c (word at 0x0012466C); value 0x38618576 (945915254) */
#define WORD_HEXADECIMAL_262EA0D8 0x262EA0D8   /* was DAT_00124670 (word at 0x00124670); value 0x262EA0D8 (640590040) */

/* ---- The read-only data of kh.mod (0x00126DEC - 0x00128247) that the code refers to, one object per
   address the code takes (in kh.mod, an offset from the pc), each reaching to the next such address:
   strings as string literals, the rest as words or bytes. The comment gives the address. */
static const uint32 ITEM_DROP_BALL_HASHES[10] = {   /* 0x00126DEC; string_hash of "ball1" - "ball10" */
  0x05208EC5,0x045958CC,0x0DD3405D,0x174D27EE,0x20C70F7F,0x2A40F710,0x33BADEA1,0x3D34C632,
  0x06AEADC3,0x3544E42E
};
static const uint32 DATA_AT_00126E14[3] = {   /* 0x00126E14 */
  0x12719CCA,0x13001EEA,0x346DBBEC
};
static const uint32 DATA_AT_00126E20[3] = {   /* 0x00126E20 */
  0x00000000,0xC1200000,0x00000000
};
static const char STRING_CARRIAGE_RETURN_NEWLINE_00126E2C[] = "\r\n";   /* 0x00126E2C */
static const uint32 PLAYER_POINT_OFFSET[3] = {   /* 0x00126E30; floats: 0, 0.25, 0 */
  0x00000000,0x3E800000,0x00000000
};
static const char STRING_NOBALLSONHIT[] = "noBallsOnHit";   /* 0x00126E3C */
static const char STRING_NOBALLSONMAGIC[] = "noBallsOnMagic";   /* 0x00126E4C */
static const char STRING_SWITCHTARGETS[] = "switchTargets";   /* 0x00126E5C */
static const char STRING_DOMAGICHITBOSS[] = "doMagicHitBoss";   /* 0x00126E6C */
static const char STRING_DOHITBOSS[] = "doHitBoss";   /* 0x00126E7C */
static const char STRING_ROTTOCHARACTER[] = "rotToCharacter";   /* 0x00126E88 */
static const char STRING_PLAYARRIVEANIM[] = "playArriveAnim";   /* 0x00126E98 */
static const uint32 DATA_AT_00126EA8[29] = {   /* 0x00126EA8 */
  0x3B91C067,0x11C542FF,0x24B276B1,0x22CE1A73,0x2D08E9DC,0x35D28B2C,0x1CD88B65,0x327E81F1,
  0x17CBB3A4,0x290C7A39,0x2EB362EA,0x343FDCDE,0x0151178B,0x24671AD4,0x1366844D,0x31556852,
  0x01995D01,0x36E5852E,0x05A123D5,0x2663AC15,0x05A123D5,0x0C1533CE,0x206BD8C5,0x201DC04E,
  0x22C4793E,0x1F5FB54D,0x0368478C,0x006A8793,0x2450A2A6
};
static const uint32 DATA_AT_00126F1C[16] = {   /* 0x00126F1C */
  0x00000000,0x0000000B,0x0000000C,0x0000000D,0x0000000E,0x0000000F,0x00000010,0x00000011,
  0x00000012,0x00000013,0x00000014,0x00000015,0x00000016,0x00000019,0x0000001A,0x0000001B
};
static const uint32 DATA_AT_00126F5C[16] = {   /* 0x00126F5C */
  0x00000000,0x00000003,0x00000003,0x00000001,0x00000001,0x00000004,0x00000001,0x00000004,
  0x00000001,0x00000004,0x00000001,0x00000004,0x00000004,0x00000004,0x00000004,0x00000004
};
static const uint32 DATA_AT_00126F9C[3] = {   /* 0x00126F9C */
  0x00000000,0x3EB33333,0x00000000
};
static const char STRING_CHARACTER_SHADOW[] = "character_shadow";   /* 0x00126FA8 */
static const char STRING_OUT_OF_MAGIC_00126FBC[] = "OUT_OF_MAGIC";   /* 0x00126FBC */
static const uint32 DATA_AT_00126FCC[1] = {   /* 0x00126FCC */
  0x00000020
};
static const char STRING_USE_VERTS[] = "USE_VERTS";   /* 0x00126FD0 */
static const char STRING_OUTER[] = "Outer";   /* 0x00126FDC */
static const char STRING_INNER[] = "Inner";   /* 0x00126FE4 */
static const char STRING_CIRCLE[] = "Circle";   /* 0x00126FEC */
static const char STRING_CYLINDER[] = "Cylinder";   /* 0x00126FF4 */
static const char STRING_CUBOID[] = "Cuboid";   /* 0x00127000 */
static const char STRING_RECT[] = "Rect";   /* 0x00127008 */
static const char STRING_POLY[] = "Poly";   /* 0x00127010 */
static const char STRING_SPHERE[] = "Sphere";   /* 0x00127018 */
static const char STRING_CLOCKWISE[] = "clockwise";   /* 0x00127020 */
static const char STRING_PERCENT_DTRANSFORM[] = "%dTransform";   /* 0x0012702C */
static const char STRING_SOLDIER[] = "Soldier";   /* 0x00127038 */
static const char STRING_FLYINGSOLDIER[] = "FlyingSoldier";   /* 0x00127040 */
static const char STRING_FLYINGMOOK[] = "FlyingMook";   /* 0x00127050 */
static const char STRING_PURPLECROC[] = "PurpleCroc";   /* 0x0012705C */
static const char STRING_UMBRELLABIRD[] = "UmbrellaBird";   /* 0x00127068 */
static const char STRING_BANDIT[] = "Bandit";   /* 0x00127078 */
static const char STRING_POTSPIDER[] = "Potspider";   /* 0x00127080 */
static const char STRING_MUMMY[] = "Mummy";   /* 0x0012708C */
static const char STRING_DARKBALL[] = "Darkball";   /* 0x00127094 */
static const char STRING_PIGSOLDIER[] = "PigSoldier";   /* 0x001270A0 */
static const uint32 ENEMY_WALK_DIRECTIONS[16] = {   /* 0x001270AC: the eight (x, y) walks enemy_roam
                                                     picks from, floats: (-2, 0), (-2, 2), (0, 2), (2, 2),
                                                     (2, 0), (2, -2), (0, -2), (-2, -2) */
  0xC0000000,0x00000000,0xC0000000,0x40000000,0x00000000,0x40000000,0x40000000,0x40000000,
  0x40000000,0x00000000,0x40000000,0xC0000000,0x00000000,0xC0000000,0xC0000000,0xC0000000
};
static const uint32 ENEMY_PLAYER_POINT_OFFSET[3] = {   /* 0x001270EC; floats: 0, 0.25, 0 */
  0x00000000,0x3E800000,0x00000000
};
static const char STRING_CARRIAGE_RETURN_NEWLINE_001270F8[] = "\r\n";   /* 0x001270F8 */
static const char STRING_ME[] = "ME";   /* 0x001270FC */
static const char STRING_ADDSOFTKEY[] = "addSoftkey";   /* 0x00127100 */
static const uint32 DATA_AT_0012710C[1] = {   /* 0x0012710C */
  0x00000020
};
static const char STRING_ADDUIACTION[] = "addUIAction";   /* 0x00127110 */
static const char STRING_ADDUIINFO[] = "addUIInfo";   /* 0x0012711C */
static const char STRING_ADDUITEXT[] = "addUIText";   /* 0x00127128 */
static const uint32 DATA_AT_00127134[1] = {   /* 0x00127134 */
  0x00000031
};
static const uint32 DATA_AT_00127138[1] = {   /* 0x00127138 */
  0x00000032
};
static const char STRING_ADJUSTVALUE[] = "adjustValue";   /* 0x0012713C */
static const char STRING_BREAK[] = "break";   /* 0x00127148 */
static const char STRING_FADE[] = "fade";   /* 0x00127150 */
static const char STRING_FIREPROJECTILE[] = "fireProjectile";   /* 0x00127158 */
static const char STRING_IF_00127168[] = "if";   /* 0x00127168 */
static const char STRING_IF_0012716C[] = "if ";   /* 0x0012716C */
static const char STRING_IFVAR_00127170[] = "ifVar";   /* 0x00127170 */
static const char STRING_IFVAR_00127178[] = "ifVar ";   /* 0x00127178 */
static const char STRING_ELSE[] = "else";   /* 0x00127180 */
static const char STRING_ENDIF[] = "endif";   /* 0x00127188 */
static const char STRING_LIFT_00127190[] = "lift";   /* 0x00127190 */
static const char STRING_LINK[] = "link";   /* 0x00127198 */
static const char STRING_LOADCLIPART[] = "loadClipart";   /* 0x001271A0 */
static const char STRING_LOADSCENE[] = "loadScene";   /* 0x001271AC */
static const char STRING_LOADSOUNDS_001271B8[] = "loadSounds";   /* 0x001271B8 */
static const char STRING_LOADSOUNDS_001271C4[] = "loadSounds ";   /* 0x001271C4 */
static const char STRING_MATCHPOSITION[] = "matchPosition";   /* 0x001271D0 */
static const char STRING_TERRAIN[] = "TERRAIN";   /* 0x001271E0 */
static const char STRING_PLAYANIM[] = "playAnim";   /* 0x001271E8 */
static const char STRING_LOOP[] = "LOOP";   /* 0x001271F4 */
static const char STRING_PLAYSEQUENCE[] = "playSequence";   /* 0x001271FC */
static const char STRING_PLAYSOUND[] = "playSound";   /* 0x0012720C */
static const char STRING_BAD[] = "BAD";   /* 0x00127218 */
static const char STRING_GOOD[] = "GOOD";   /* 0x0012721C */
static const char STRING_KEYBLADE[] = "KEYBLADE";   /* 0x00127224 */
static const char STRING_EXPLODE[] = "EXPLODE";   /* 0x00127230 */
static const char STRING_WATER[] = "WATER";   /* 0x00127238 */
static const char STRING_JUMP[] = "JUMP";   /* 0x00127240 */
static const char STRING_THUD[] = "THUD";   /* 0x00127248 */
static const char STRING_TRANSITION[] = "TRANSITION";   /* 0x00127250 */
static const char STRING_MAGIC_ALERT[] = "MAGIC_ALERT";   /* 0x0012725C */
static const char STRING_MAGIC_CAST[] = "MAGIC_CAST";   /* 0x00127268 */
static const char STRING_REMOVESOFTKEY[] = "removeSoftkey";   /* 0x00127274 */
static const char STRING_REMOVEUIACTION[] = "removeUIAction";   /* 0x00127284 */
static const char STRING_REMOVEUITEXT[] = "removeUIText";   /* 0x00127294 */
static const char STRING_RESETKEYS[] = "resetKeys";   /* 0x001272A4 */
static const char STRING_SAVEGAME[] = "saveGame";   /* 0x001272B0 */
static const char STRING_TEMP[] = "TEMP";   /* 0x001272BC */
static const char STRING_SETANIMSPEED[] = "setAnimSpeed";   /* 0x001272C4 */
static const char STRING_SETANIMPOSITION[] = "setAnimPosition";   /* 0x001272D4 */
static const char STRING_END[] = "END";   /* 0x001272E4 */
static const char STRING_SETAPPEARANCE[] = "setAppearance";   /* 0x001272E8 */
static const char STRING_SETBACKGROUND[] = "setBackground";   /* 0x001272F8 */
static const char STRING_SETCAMERAFOCUS[] = "setCameraFocus";   /* 0x00127308 */
static const char STRING_STANDARD_VIEW[] = "STANDARD_VIEW";   /* 0x00127318 */
static const char STRING_HIGH_VIEW[] = "HIGH_VIEW";   /* 0x00127328 */
static const char STRING_PLAN_VIEW[] = "PLAN_VIEW";   /* 0x00127334 */
static const char STRING_MED_VIEW[] = "MED_VIEW";   /* 0x00127340 */
static const char STRING_LOW_VIEW[] = "LOW_VIEW";   /* 0x0012734C */
static const char STRING_SETCHARACTERMODE[] = "setCharacterMode";   /* 0x00127358 */
static const char STRING_ATTACK[] = "ATTACK";   /* 0x0012736C */
static const char STRING_SWIM[] = "SWIM";   /* 0x00127374 */
static const char STRING_SWIM_NO_CLIMB[] = "SWIM_NO_CLIMB";   /* 0x0012737C */
static const char STRING_NOSWIM[] = "NOSWIM";   /* 0x0012738C */
static const char STRING_CLIMB_TREE[] = "CLIMB_TREE";   /* 0x00127394 */
static const char STRING_CLIMB_TREE_NO_ROT[] = "CLIMB_TREE_NO_ROT";   /* 0x001273A0 */
static const char STRING_CLIMB_LADDER[] = "CLIMB_LADDER";   /* 0x001273B4 */
static const char STRING_LIFT_001273C4[] = "LIFT";   /* 0x001273C4 */
static const char STRING_DROP[] = "DROP";   /* 0x001273CC */
static const char STRING_BEHIND[] = "BEHIND";   /* 0x001273D4 */
static const char STRING_HANG[] = "HANG";   /* 0x001273DC */
static const char STRING_STATIC_HANG[] = "STATIC_HANG";   /* 0x001273E4 */
static const char STRING_UNHANG[] = "UNHANG";   /* 0x001273F0 */
static const char STRING_HIT[] = "HIT";   /* 0x001273F8 */
static const char STRING_IDLE[] = "IDLE";   /* 0x001273FC */
static const char STRING_RESET[] = "RESET";   /* 0x00127404 */
static const char STRING_SETCOLLECTABLES[] = "setCollectables";   /* 0x0012740C */
static const char STRING_SETCOLLISIONON[] = "setCollisionOn";   /* 0x0012741C */
static const char STRING_SETCOLLISIONOFF[] = "setCollisionOff";   /* 0x0012742C */
static const char STRING_SETCOMBATREGION[] = "setCombatRegion";   /* 0x0012743C */
static const char STRING_SETKEYSON[] = "setKeysOn";   /* 0x0012744C */
static const char STRING_SETKEYSOFF[] = "setKeysOff";   /* 0x00127458 */
static const char STRING_SETLEVELUP[] = "setLevelUp";   /* 0x00127464 */
static const char STRING_SETMIRROR[] = "setMirror";   /* 0x00127470 */
static const char STRING_NULL[] = "NULL";   /* 0x0012747C */
static const char STRING_DASH_X[] = "-X";   /* 0x00127484 */
static const char STRING_DASH_Y[] = "-Y";   /* 0x00127488 */
static const char STRING_DASH_Z[] = "-Z";   /* 0x0012748C */
static const char STRING_DASH_R[] = "-R";   /* 0x00127490 */
static const char STRING_SETMOVINGCAMERA[] = "setMovingCamera";   /* 0x00127494 */
static const char STRING_SETPOSITION[] = "setPosition";   /* 0x001274A4 */
static const char STRING_SETSCREENMODE[] = "setScreenMode";   /* 0x001274B0 */
static const char STRING_CINEMATIC[] = "CINEMATIC";   /* 0x001274C0 */
static const char STRING_SETSCRIPTON[] = "setScriptOn";   /* 0x001274CC */
static const char STRING_SETSCRIPTOFF[] = "setScriptOff";   /* 0x001274D8 */
static const char STRING_SETSHADOWVIS[] = "setShadowVis";   /* 0x001274E8 */
static const char STRING_SETSPELLTYPE[] = "setSpellType";   /* 0x001274F8 */
static const char STRING_FIRE[] = "FIRE";   /* 0x00127508 */
static const char STRING_BLIZZARD[] = "BLIZZARD";   /* 0x00127510 */
static const char STRING_THUNDER[] = "THUNDER";   /* 0x0012751C */
static const char STRING_SETSTATE[] = "setState";   /* 0x00127524 */
static const char STRING_SETVAR[] = "setVar";   /* 0x00127530 */
static const char STRING_INCVAR[] = "incVar";   /* 0x00127538 */
static const char STRING_DECVAR[] = "decVar";   /* 0x00127540 */
static const char STRING_SETSTATICCAMERA[] = "setStaticCamera";   /* 0x00127548 */
static const char STRING_SETTERRAINLEVEL[] = "setTerrainLevel";   /* 0x00127558 */
static const char STRING_SETUPDATEON[] = "setUpdateOn";   /* 0x00127568 */
static const char STRING_SETUPDATEOFF[] = "setUpdateOff";   /* 0x00127574 */
static const char STRING_SETUIVIS_00127584[] = "setUIVis";   /* 0x00127584 */
static const char STRING_SETUIVIS_00127590[] = "setUIVis ";   /* 0x00127590 */
static const char STRING_SETVICTIM[] = "setVictim";   /* 0x0012759C */
static const char STRING_SETVIS[] = "setVis";   /* 0x001275A8 */
static const char STRING_SETXROT[] = "setXRot";   /* 0x001275B0 */
static const char STRING_SETYROT[] = "setYRot";   /* 0x001275B8 */
static const char STRING_STOPANIM[] = "stopAnim";   /* 0x001275C0 */
static const char STRING_NOW[] = "NOW";   /* 0x001275CC */
static const char STRING_SUMMARY[] = "summary";   /* 0x001275D0 */
static const char STRING_UNLINK[] = "unlink";   /* 0x001275D8 */
static const char STRING_UNLOADCLIPART[] = "unloadClipart";   /* 0x001275E0 */
static const char STRING_SETKEYDIR[] = "setKeyDir";   /* 0x001275F0 */
static const char STRING_SETACTIVEROTON[] = "setActiveRotOn";   /* 0x001275FC */
static const char STRING_SETACTIVEROTOFF[] = "setActiveRotOff";   /* 0x0012760C */
static const char STRING_SAVE[] = "SAVE";   /* 0x0012761C */
static const char STRING_SHOP[] = "SHOP";   /* 0x00127624 */
static const char STRING_OPTIONS[] = "OPTIONS";   /* 0x0012762C */
static const char STRING_MAIN_MENU[] = "MAIN_MENU";   /* 0x00127634 */
static const char STRING_RESTART_GAME[] = "RESTART_GAME";   /* 0x00127640 */
static const char STRING_UNPAUSE[] = "UNPAUSE";   /* 0x00127650 */
static const char STRING_ACTIVATE[] = "ACTIVATE";   /* 0x00127658 */
static const char STRING_GRAB[] = "GRAB";   /* 0x00127664 */
static const char STRING_LOCK[] = "LOCK";   /* 0x0012766C */
static const char STRING_OPEN[] = "OPEN";   /* 0x00127674 */
static const char STRING_TALK[] = "TALK";   /* 0x0012767C */
static const char STRING_PLACE[] = "PLACE";   /* 0x00127684 */
static const char STRING_HEALTH[] = "HEALTH";   /* 0x0012768C */
static const char STRING_MAGIC[] = "MAGIC";   /* 0x00127694 */
static const char STRING_MUNNY[] = "MUNNY";   /* 0x0012769C */
static const char STRING_EXP[] = "EXP";   /* 0x001276A4 */
static const char STRING_POTION[] = "POTION";   /* 0x001276A8 */
static const char STRING_HIPOTION[] = "HIPOTION";   /* 0x001276B0 */
static const char STRING_ETHER[] = "ETHER";   /* 0x001276BC */
static const char STRING_ELIXIR[] = "ELIXIR";   /* 0x001276C4 */
static const uint32 DATA_AT_001276CC[1] = {   /* 0x001276CC */
  0x00000021
};
static const char STRING_BAR_BAR[] = "||";   /* 0x001276D0 */
static const char STRING_AND_AND[] = "&&";   /* 0x001276D4 */
static const char STRING_ENGINE_VER[] = "ENGINE_VER";   /* 0x001276D8 */
static const char STRING_EQUALS_EQUALS[] = "==";   /* 0x001276E4 */
static const char STRING_EQUALS_001276E8[] = "!=";   /* 0x001276E8 */
static const uint32 DATA_AT_001276EC[1] = {   /* 0x001276EC */
  0x0000003C
};
static const char STRING_EQUALS_001276F0[] = "<=";   /* 0x001276F0 */
static const uint32 DATA_AT_001276F4[1] = {   /* 0x001276F4 */
  0x0000003E
};
static const char STRING_EQUALS_001276F8[] = ">=";   /* 0x001276F8 */
static const uint32 DATA_AT_001276FC[4] = {   /* 0x001276FC */
  0x65766173,0x656D6167,0x7461642E,0x00000000
};
static const char STRING_DOT_M3G_0012770C[] = ".m3g";   /* 0x0012770C */
static const char STRING_ALL_00127714[] = "ALL";   /* 0x00127714 */
static const char STRING_ENEMY[] = "ENEMY";   /* 0x00127718 */
static const char STRING_SHOW[] = "SHOW";   /* 0x00127720 */
static const char STRING_ALL_00127728[] = "!ALL";   /* 0x00127728 */
static const char STRING_HIDE[] = "HIDE";   /* 0x00127730 */
static const char STRING_LOADING_00127738[] = "LOADING";   /* 0x00127738 */
static const char STRING_LOADING_00127740[] = "!LOADING";   /* 0x00127740 */
static const uint32 DATA_AT_0012774C[1] = {   /* 0x0012774C */
  0x00000020
};
static const uint32 DATA_AT_00127750[1] = {   /* 0x00127750 */
  0x00000031
};
static const char STRING_CARRIAGE_RETURN_NEWLINE_00127754[] = "\r\n";   /* 0x00127754 */
static const char STRING_TERRAINONLY[] = "TerrainOnly";   /* 0x00127758 */
static const char STRING_NONTERRAIN[] = "NonTerrain";   /* 0x00127764 */
static const char STRING_ALIGN[] = "Align";   /* 0x00127770 */
static const char STRING_MOVING[] = "Moving";   /* 0x00127778 */
static const char STRING_CARRIAGE_RETURN_NEWLINE_00127780[] = "\r\n";   /* 0x00127780 */
static const uint32 DATA_AT_00127784[1] = {   /* 0x00127784 */
  0x0000003A
};
static const char STRING_MOTIONENTITY[] = "MotionEntity";   /* 0x00127788 */
static const char STRING_COMBATREGION[] = "CombatRegion";   /* 0x00127798 */
static const char STRING_BOSSCOMBATREGION[] = "BossCombatRegion";   /* 0x001277A8 */
static const char STRING_NOPARENT[] = "NoParent";   /* 0x001277BC */
static const char STRING_DEADEND[] = "DeadEnd";   /* 0x001277C8 */
static const char STRING_BASE_DOT_M3G[] = "base.m3g";   /* 0x001277D0 */
static const char STRING_CHARACTER_GRP_001277DC[] = "character_grp";   /* 0x001277DC */
static const char STRING_GENERAL_SCRIPTS[] = "general_scripts";   /* 0x001277EC */
static const char STRING_CAMERA[] = "Camera";   /* 0x001277FC */
static const char STRING_CHARACTER[] = "Character";   /* 0x00127804 */
static const char STRING_MAGIC_CAST_DOT_QCP[] = "magic_cast.qcp";   /* 0x00127810 */
static const char STRING_MAGIC_ALERT_DOT_MID[] = "magic_alert.mid";   /* 0x00127820 */
static const char STRING_TRANSITION_DOT_QCP[] = "transition.qcp";   /* 0x00127830 */
static const char STRING_THUD_DOT_QCP[] = "thud.qcp";   /* 0x00127840 */
static const char STRING_WATER_DOT_QCP[] = "water.qcp";   /* 0x0012784C */
static const char STRING_EXPLODE_DOT_QCP[] = "explode.qcp";   /* 0x00127858 */
static const char STRING_KEYBLADE_DOT_MID[] = "keyblade.mid";   /* 0x00127864 */
static const char STRING_GOOD_DOT_MID[] = "good.mid";   /* 0x00127874 */
static const char STRING_BAD_DOT_MID[] = "bad.mid";   /* 0x00127880 */
static const char STRING_SORA_SWIPE_DOT_QCP[] = "sora_swipe.qcp";   /* 0x00127888 */
static const char STRING_ENEMY_HIT_DOT_QCP[] = "enemy_hit.qcp";   /* 0x00127898 */
static const char STRING_SORA_HIT_DOT_QCP[] = "sora_hit.qcp";   /* 0x001278A8 */
static const char STRING_SORA_JUMP_DOT_QCP[] = "sora_jump.qcp";   /* 0x001278B8 */
static const char STRING_SCOREDATA_DOT_DAT[] = "scoredata.dat";   /* 0x001278C8 */
static const char STRING_SETTINGS_DOT_DAT_001278D8[] = "settings.dat";   /* 0x001278D8 */
static const char STRING_EMPTY_001278E8[4] = "";   /* 0x001278E8 (4 bytes: "" and its padding) */
static const char STRING_TMP_DOT_DAT[] = "tmp.dat";   /* 0x001278EC */
static const char STRING_OUT_OF_MAGIC_001278F4[] = "OUT_OF_MAGIC";   /* 0x001278F4 */
static const char STRING_PERCENT_S_EQUALS_PERCENT_D[] = "%s = %d";   /* 0x00127904 */
static const char STRING_DOT_M3G_00127910[] = ".m3g";   /* 0x00127910 */
static const uint32 INTRO_ANIMATION_IDS[11] = {   /* 0x00127918 GUESS: name; the intro timeline's
                                                     animations, by user id (intro_find_animations) */
  0x36C5EA1A,0x0368478C,0x343FDCDE,0x0151178B,0x24671AD4,0x1366844D,0x3B91C067,0x2663AC15,
  0x05A123D5,0x3B91C067,0x11C542FF
};
static const uint32 INTRO_ANIMATION_STARTS[11] = {   /* 0x00127944 GUESS: name; when each starts, ms:
                                                        0, 0, 1133, 1133, 1333, 1333, 1800, 3533, 3533,
                                                        4467, 11135 */
  0x00000000,0x00000000,0x0000046D,0x0000046D,0x00000535,0x00000535,0x00000708,0x00000DCD,
  0x00000DCD,0x00001173,0x00002B7F
};
static const uint32 INTRO_ANIMATION_ENDS[11] = {   /* 0x00127970 GUESS: name; when each ends, ms: 7000,
                                                      1133, 1333, 1333, 1800, 1800, 3533, 4467, 4467,
                                                      11135, 13802 */
  0x00001B58,0x0000046D,0x00000535,0x00000535,0x00000708,0x00000708,0x00000DCD,0x00001173,
  0x00001173,0x00002B7F,0x000035EA
};
static const char STRING_DISNEY_DOT_M3G[] = "disney.m3g";   /* 0x0012799C */
static const char STRING_SWERVE_DOT_M3G[] = "swerve.m3g";   /* 0x001279A8 */
static const char STRING_INTRO_DOT_M3G[] = "intro.m3g";   /* 0x001279B4 */
static const char STRING_CHARACTER_GRP_001279C0[] = "character_grp";   /* 0x001279C0 */
static const char STRING_LANGUAGE_DOT_M3G[] = "language.m3g";   /* 0x001279D0 */
static const uint32 DATA_AT_001279E0[5] = {   /* 0x001279E0 */
  0x251509C8,0x19408333,0x10FB280A,0x14741FD6,0x0252B33F
};
static const char STRING_PRESS_ANY_KEY_TO_CONTINUE[] = "Press any key to continue";   /* 0x001279F4 */
static const char STRING_AND_WILL_CLOSE_ERROR_PERCENT_X[] = "and will close (Error %x)";   /* 0x00127A10 */
static const char STRING_THE_APPLICATION_HAS_FAILED[] = "The application has failed";   /* 0x00127A2C */
static const char STRING_SAVEGAME_DOT_DAT[] = "savegame.dat";   /* 0x00127A48 */
static const char STRING_SETTINGS_DOT_DAT_00127A58[] = "settings.dat";   /* 0x00127A58 */
static const uint32 DATA_AT_00127A68[4] = {   /* 0x00127A68 */
  0x00000008,0x00000000,0x00000004,0x00000000
};
static const uint32 DATA_AT_00127A78[2] = {   /* 0x00127A78 */
  0x00000000,0x00000007
};
static const uint8 DATA_AT_00127A7E[8] = {   /* 0x00127A7E */
  0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x00
};
static const uint8 DATA_AT_00127A86[8] = {   /* 0x00127A86 */
  0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x00
};
static const uint8 HUD_MAGIC_ARC[10] = {   /* 0x00127A8E; GUESS: name; the AEEArc hud_draw starts from:
                                             its arcAngle 45 */
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2D,0x00
};
static const char STRING_KH_DOT_BAR_00127A98[] = "kh.bar";   /* 0x00127A98 */
static const uint32 DATA_AT_00127AA0[12] = {   /* 0x00127AA0 */
  0xFFFFFC18,0xFFFFFC17,0xFFFFFC16,0xFFFFFC15,0xFFFFFC14,0xFFFFFC13,0xFFFFFC12,0xFFFFFC11,
  0xFFFFFC10,0xFFFFFC0F,0xFFFFFC0E,0xFFFFFC0D
};
static const uint32 DATA_AT_00127AD0[3] = {   /* 0x00127AD0 */
  0x33323130,0x37363534,0x232A3938
};
static const uint32 DATA_AT_00127ADC[5] = {   /* 0x00127ADC */
  0x39FEE748,0x3D52229B,0x304B17D0,0x17616D9E,0x09B4B3F6
};
static const uint32 DATA_AT_00127AF0[5] = {   /* 0x00127AF0 */
  0x0000003D,0x0000003E,0x00000003,0x00000040,0x00000041
};
static const uint32 DATA_AT_00127B04[6] = {   /* 0x00127B04 */
  0x16A5390B,0x0AF804C1,0x31655ECD,0x2B26AEEE,0x272E6865,0x00C833EC
};
static const uint32 DATA_AT_00127B1C[6] = {   /* 0x00127B1C */
  0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF
};
static const uint32 DATA_AT_00127B34[7] = {   /* 0x00127B34 */
  0x16A5390B,0x0AF804C1,0x31655ECD,0x2B26AEEE,0x272E6865,0x00C833EC,0x04D4D70F
};
static const uint32 DATA_AT_00127B50[7] = {   /* 0x00127B50 */
  0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF
};
static const uint32 DATA_AT_00127B6C[7] = {   /* 0x00127B6C */
  0x1874E38C,0x210035A0,0x0AF804C1,0x31655ECD,0x2B26AEEE,0x08897883,0x272E6865
};
static const uint32 DATA_AT_00127B88[7] = {   /* 0x00127B88 */
  0xFF7FCB61,0xFF4757DD,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF
};
static const uint32 DATA_AT_00127BA4[6] = {   /* 0x00127BA4 */
  0x16A5390B,0x075C231E,0x0F5D9BAD,0x3A8A8292,0x3746DB2E,0x00000000
};
static const uint32 DATA_AT_00127BBC[6] = {   /* 0x00127BBC */
  0xFF000000,0xFF7FCB61,0xFF7FCB61,0xFF4757DD,0xFF4757DD,0xFF000000
};
static const uint32 DATA_AT_00127BD4[5] = {   /* 0x00127BD4 */
  0x2757255D,0x14FB8F11,0x27B2CEEB,0x045E6D5C,0x14A8296B
};
static const uint32 DATA_AT_00127BE8[5] = {   /* 0x00127BE8 */
  0x0000000B,0x0000000C,0x00000011,0x0000000E,0x0000000F
};
static const uint32 DATA_AT_00127BFC[5] = {   /* 0x00127BFC */
  0x00000000,0x000000C8,0x000000C9,0x00000000,0x00000000
};
static const uint32 DATA_AT_00127C10[3] = {   /* 0x00127C10 */
  0x075C231E,0x0F5D9BAD,0x3A8A8292
};
static const uint32 DATA_AT_00127C1C[1] = {   /* 0x00127C1C */
  0x3746DB2E
};
static const uint32 DATA_AT_00127C20[4] = {   /* 0x00127C20 */
  0x0000000A,0x0000000F,0x0000000A,0x0000000F
};
static const uint32 DATA_AT_00127C30[4] = {   /* 0x00127C30 */
  0x00000029,0x0000002A,0x0000002B,0x0000002C
};
static const uint32 DATA_AT_00127C40[7] = {   /* 0x00127C40 */
  0x36637790,0x0198B58B,0x380D74DD,0x108CF3DF,0x2257A2C2,0x0CCFFC1C,0x23C0A51A
};
static const uint32 DATA_AT_00127C5C[13] = {   /* 0x00127C5C */
  0x1484CCBF,0xFFFFFC18,0xFFFFFC17,0xFFFFFC16,0xFFFFFC15,0xFFFFFC14,0xFFFFFC13,0xFFFFFC12,
  0xFFFFFC11,0xFFFFFC10,0xFFFFFC0F,0xFFFFFC0E,0xFFFFFC0D
};
static const uint32 DATA_AT_00127C90[13] = {   /* 0x00127C90 */
  0x0000E010,0x0000E021,0x0000E022,0x0000E023,0x0000E024,0x0000E025,0x0000E026,0x0000E027,
  0x0000E028,0x0000E029,0x0000E02A,0x0000E02B,0x0000E02C
};
static const char STRING_KH_DOT_BAR_00127CC4[] = "kh.bar";   /* 0x00127CC4 */
static const char STRING_PERCENT_D[] = "%d";   /* 0x00127CCC */
static const char STRING_CASTLE[] = "castle";   /* 0x00127CD0 */
static const char STRING_AGRABAH[] = "agrabah";   /* 0x00127CD8 */
static const char STRING_WONDERLAND[] = "wonderland";   /* 0x00127CE0 */
static const char STRING_ISLAND[] = "island";   /* 0x00127CEC */
static const char STRING_SAVEGAME_DOT_DAT_00127CF4[] = "savegame.dat";   /* 0x00127CF4 */
static const char STRING_PERCENT_S_PERCENT_D_SLASH_PERCENT[] = "%s %d/%d";   /* 0x00127D04 */
static const char STRING_TRAINING_00127D10[] = "training";   /* 0x00127D10 */
static const char STRING_REPLAYGAME_DOT_DAT[] = "replaygame.dat";   /* 0x00127D1C */
static const uint32 DATA_AT_00127D2C[1] = {   /* 0x00127D2C */
  0x00000000
};
static const uint32 DATA_AT_00127D30[1] = {   /* 0x00127D30 */
  0x0000002C
};
static const char STRING_COLLECTABLES[] = "COLLECTABLES";   /* 0x00127D34 */
static const char STRING_PERCENT_S_PERCENT_S_PERCENT_S_00127D44[] = "%s%s%s";   /* 0x00127D44 */
static const char STRING_RO[] = "ro_";   /* 0x00127D4C */
static const char STRING_JTEXT_DOT_M3G[] = "_jtext.m3g";   /* 0x00127D50 */
static const char STRING_JIMINY_ICON_DOT_PNG[] = "jiminy_icon.png";   /* 0x00127D5C */
static const char STRING_SPLASH_DOT_PNG[] = "_splash.png";   /* 0x00127D6C */
static const char STRING_OUT_OF_MAGIC_00127D78[] = "OUT_OF_MAGIC";   /* 0x00127D78 */
static const uint32 DATA_AT_00127D88[2] = {   /* 0x00127D88 */
  0x00000000,0x0000000B
};
static const char STRING_EMPTY[4] = "";   /* 0x00127D90 (4 bytes: "" and its padding) */
static const char STRING_SPACE[4] = " ";   /* 0x00127D94 (4 bytes: " " and its padding) */
static const char STRING_INVALIDENTRY[] = "invalidentry";   /* 0x00127D98 */
static const char STRING_STAR_D[] = "*d";   /* 0x00127DA8 */
static const char STRING_STAR_T[] = "*t";   /* 0x00127DAC */
static const char STRING_STAR_R[] = "*r";   /* 0x00127DB0 */
static const char STRING_KH[] = "KH";   /* 0x00127DB4 */
static const char STRING_DOT_DAT[] = ".dat";   /* 0x00127DB8 */
static const char STRING_PERCENT_S_PERCENT_S_PERCENT_S_00127DC0[] = "%s%s%s&uid=%s&aid=%s&t=%d";   /* 0x00127DC0 */
static const char STRING_HTTP_COLON_SLASH_SLASH_SWERVENET_DOT[] = "http://swervenet.superscape.com/";   /* 0x00127DDC */
static const char STRING_DISNEY_SLASH_DOWNLOAD_DOT_PHP_QUESTION[] = "disney/download.php\?f=";   /* 0x00127E00 */
static const char STRING_PERCENT_S_AND_S_EQUALS_PERCENT[] = "%s&s=%d";   /* 0x00127E18 */
static const char STRING_X_METHOD_GET[16] = "X-Method: GET\r\n";   /* 0x00127E20: an HTTP header line, the web
                                                                       requests' GetResponse option 0x00010002 */
static const char STRING_PERCENT_S_PERCENT_S_QUESTION_MARK_00127E30[] = "%s%s\?uid=%s&aid=%s&lid=%s&s=%d&t=%d&u1=%d&u2=%s";   /* 0x00127E30 */
static const char STRING_DISNEY_SLASH_RANK_DOT_PHP[] = "disney/rank.php";   /* 0x00127E60 */
static const char STRING_PERCENT_S_PERCENT_S_QUESTION_MARK_00127E70[] = "%s%s\?uid=%s&aid=%s&lid=%s&s=%s&t=%d&u1=%d";   /* 0x00127E70 */
static const char STRING_DISNEY_SLASH_RANKEX_DOT_PHP[] = "disney/rankex.php";   /* 0x00127E9C */
static const char STRING_MP3[] = "mp3";   /* 0x00127EB0 */
static const char STRING_MID[] = "mid";   /* 0x00127EB4 */
static const char STRING_QCP[] = "qcp";   /* 0x00127EB8 */
static const char STRING_PMD[] = "pmd";   /* 0x00127EBC */
static const uint32 DATA_AT_00127EC4[4] = {   /* 0x00127EC4 */
  0x00000000,0x00000000,0x00000000,0x3F800000
};
static const uint32 KEY_NAME_CODES[8] = {   /* 0x00127ED4; GUESS: name; text_expand_key_names' codes before
                                               the controls fill the first 7 (-1: "#VER") */
  0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0xFFFFFFFF
};
static const char STRING_TRANSFORM[] = "Transform";   /* 0x00127EF4 */
static const char STRING_DOT_M3G_00127F00[] = ".m3g";   /* 0x00127F00 */
static const char STRING_CARRIAGE_RETURN_NEWLINE_00127F08[] = "\r\n";   /* 0x00127F08 */
static const char STRING_HASH_VER[] = "#VER";   /* 0x00127F0C */
static const char STRING_HASH_MAGIC[] = "#MAGIC";   /* 0x00127F14 */
static const char STRING_HASH_INV[] = "#INV";   /* 0x00127F1C */
static const char STRING_HASH_ACTION[] = "#ACTION";   /* 0x00127F24 */
static const char STRING_HASH_RIGHT[] = "#RIGHT";   /* 0x00127F2C */
static const char STRING_HASH_LEFT[] = "#LEFT";   /* 0x00127F34 */
static const char STRING_HASH_DOWN[] = "#DOWN";   /* 0x00127F3C */
static const char STRING_HASH_UP[] = "#UP";   /* 0x00127F44 */
static const char STRING_0_00127F48[] = "0";   /* 0x00127F48 */
static const char STRING_1_00127F4C[] = "1";   /* 0x00127F4C */
static const char STRING_2_00127F50[] = "2";   /* 0x00127F50 */
static const char STRING_3_00127F54[] = "3";   /* 0x00127F54 */
static const char STRING_4_00127F58[] = "4";   /* 0x00127F58 */
static const char STRING_5_00127F5C[] = "5";   /* 0x00127F5C */
static const char STRING_6_00127F60[] = "6";   /* 0x00127F60 */
static const char STRING_7_00127F64[] = "7";   /* 0x00127F64 */
static const char STRING_8_00127F68[] = "8";   /* 0x00127F68 */
static const char STRING_9_00127F6C[] = "9";   /* 0x00127F6C */
static const char STRING_STAR_00127F70[] = "*";   /* 0x00127F70 */
static const char STRING_HASH_00127F74[] = "#";   /* 0x00127F74 */
static const char STRING_EMPTY_00127F78[] = "";   /* 0x00127F78; the root (files_remove_by_prefix) */
static const char STRING_TRAINING_DOT_MID[] = "training.mid";   /* 0x00127F7C */
static const char STRING_TRAINING_00127F8C[] = "training";   /* 0x00127F8C */
static const char STRING_PERCENT_S_PERCENT_S[] = "%s%s";   /* 0x00127F98 */
static const char STRING_DOT_MID[] = ".mid";   /* 0x00127FA0 */
static const char STRING_DEATH_DOT_MID[] = "death.mid";   /* 0x00127FA8 */
static const uint32 ACOS_NUMERATOR_TABLE[12] = {   /* 0x00127FB4 */
  0x55555555,0x3FC55555,0x03EB6F7D,0xBFD4D612,0x0E884455,0x3FC9C155,0xB5688F3B,0xBFA48228,
  0x7501B288,0x3F49EFE0,0x0DFDF709,0x3F023DE1
};
static const uint32 ACOS_DENOMINATOR_TABLE[8] = {   /* 0x00127FE4 */
  0x1C8A2D4B,0xC0033A27,0x9C598AC8,0x40002AE5,0x1B8D0159,0xBFE6066C,0xB12E9282,0x3FB3B8C5
};
static const uint32 COS_KERNEL_TABLE[12] = {   /* 0x00128004 */
  0x5555554C,0x3FA55555,0x16C15177,0xBF56C16C,0x19CB1590,0x3EFA01A0,0x809C52AD,0xBE927E4F,
  0xBDB4B1C4,0x3E21EE9E,0xBE8838D4,0xBDA8FAE9
};
static const uint32 LARGE_ARGUMENT_SCALE_TABLE[36] = {   /* 0x00128034 */
  0x66C0E65C,0x3CA03923,0x486F5BA8,0x3954C2B1,0xCAF7C76B,0xB6254068,0x84BD9AC5,0x32E39207,
  0x1EFD4BE4,0x2FA6702F,0x7AC65E97,0xAC491D0B,0xAA3BC92E,0x2903BD1A,0xC9A22250,0xA5DEF596,
  0x9555FDD5,0x22A2B780,0x046A611E,0x9F638C87,0x916FA3B6,0x1BFEC8DD,0xDC0E352B,0x18D6C252,
  0xB54C4D89,0x958977F8,0x4C55AC6B,0x91CAAFB6,0x593C7F16,0x8EF7690B,0x41E9C6C7,0x0BE571A3,
  0x8851AAAD,0x88A3BDD9,0x94F3DE7D,0x0562D533
};
static const uint32 HALF_PI_PIECES_TABLE[12] = {   /* 0x001280C4 */
  0x54400000,0x3FF921FB,0x1A626331,0x3DD0B461,0x1A600000,0x3DD0B461,0x2E037073,0x3BA3198A,
  0x2E000000,0x3BA3198A,0x252049C1,0x397B839A
};
static const uint32 SIN_KERNEL_TABLE[10] = {   /* 0x001280F4 .. 0x0012811B: the sine kernel's five
                                                 coefficients S2 - S6 (math_kernel_sin's polynomial of 5
                                                 terms). The last three are also SIGNAL_MESSAGE_TABLE's
                                                 first words, the base its messages are indexed from */
  0x1110F8A6,0x3F811111,0x19C161D5,0xBF2A01A0,0x57B1FE7D,0x3EC71DE3,0x8A2B9CEB,0xBE5AE5E6,
  0x5ACFD57C,0x3DE5D93A
};
static const uint32 SIGNAL_MESSAGE_TABLE[81] = {   /* 0x00128104 */
  0x57B1FE7D,0x3EC71DE3,0x8A2B9CEB,0xBE5AE5E6,0x5ACFD57C,0x3DE5D93A,0x6F6E6241,0x6C616D72,
  0x72657420,0x616E696D,0x6E6F6974,0x41000000,0x68746972,0x6974656D,0x78652063,0x74706563,
  0x3A6E6F69,0x6C490020,0x6167656C,0x6E69206C,0x75727473,0x6F697463,0x0000006E,0x746E4900,
  0x75727265,0x72207470,0x69656365,0x00646576,0x00000000,0x656C6C49,0x206C6167,0x72646461,
  0x00737365,0x00000000,0x54000000,0x696D7265,0x6974616E,0x72206E6F,0x65757165,0x00007473,
  0x74530000,0x206B6361,0x7265766F,0x776F6C66,0x00000000,0x00000000,0x64655200,0x63657269,
  0x63203A74,0x74276E61,0x65706F20,0x00203A6E,0x2074754F,0x6820666F,0x20706165,0x6F6D656D,
  0x00007972,0x55000000,0x2D726573,0x69666564,0x2064656E,0x6E676973,0x31206C61,0x73550000,
  0x642D7265,0x6E696665,0x73206465,0x616E6769,0x0032206C,0x72755000,0x69762065,0x61757472,
  0x6E66206C,0x6C616320,0x0064656C,0x202B2B43,0x7262696C,0x20797261,0x65637865,0x6F697470,
  0x0000006E
};

/* ---- The relative vtables (0x00101650 - 0x00101743), as arrays of function pointers. */
static code *const VTABLE_00101650[3] = {   /* 0x00101650; in kh.mod each entry is the method's offset from
                                                the table */
  (code *)FUN_00114c00,
  (code *)FUN_00121c6c,
  (code *)FUN_0010f4d0
};
static code *const VTABLE_0010165C[9] = {   /* 0x0010165C; in kh.mod each entry is the method's offset from
                                                the table */
  (code *)FUN_00105c5c,
  (code *)ui_element_update_nothing,
  (code *)FUN_00108414,
  (code *)ui_element_draw_over_children_nothing,
  (code *)hud_draw,
  (code *)ui_element_get_primary_color,
  (code *)ui_element_get_secondary_color,
  (code *)ui_element_get_border_color,
  (code *)FUN_001051d4
};
static code *const VTABLE_00101680[8] = {   /* 0x00101680; in kh.mod each entry is the method's offset from
                                                the table */
  (code *)enemy_setup_type,
  (code *)enemy_update,
  (code *)enemy_enter_mode_1,
  (code *)enemy_enter_mode_2,
  (code *)enemy_enter_mode_3,
  (code *)enemy_take_hit,
  (code *)enemy_get_health,
  (code *)enemy_is_waiting
};
static code *const VTABLE_001016A0[8] = {   /* 0x001016A0; in kh.mod each entry is the method's offset from
                                                the table */
  (code *)text_box_destroy,
  (code *)ui_element_update_nothing,
  (code *)text_box_handle_key,
  (code *)text_box_draw_scroll_bar,
  (code *)text_box_draw,
  (code *)ui_element_get_primary_color,
  (code *)ui_element_get_secondary_color,
  (code *)ui_element_get_border_color
};
static code *const VTABLE_001016C0[8] = {   /* 0x001016C0; in kh.mod each entry is the method's offset from
                                                the table */
  (code *)text_line_destroy,
  (code *)ui_element_update_nothing,
  (code *)ui_element_handle_key_nothing,
  (code *)ui_element_draw_over_children_nothing,
  (code *)text_line_draw,
  (code *)ui_element_get_primary_color,
  (code *)ui_element_get_secondary_color,
  (code *)ui_element_get_border_color
};
static code *const VTABLE_001016E0[8] = {   /* 0x001016E0; in kh.mod each entry is the method's offset from
                                                the table */
  (code *)FUN_00105d7c,
  (code *)ui_element_update_nothing,
  (code *)ui_element_handle_key,
  (code *)menu_item_draw_over_children,
  (code *)menu_item_draw,
  (code *)ui_element_get_primary_color,
  (code *)ui_element_get_secondary_color,
  (code *)ui_element_get_border_color
};
static code *const VTABLE_00101700[9] = {   /* 0x00101700; in kh.mod each entry is the method's offset from
                                                the table */
  (code *)FUN_00105dc8,
  (code *)ui_element_update_nothing,
  (code *)screen_handle_key_nothing,
  (code *)ui_element_draw_over_children_nothing,
  (code *)screen_draw,
  (code *)ui_element_get_primary_color,
  (code *)ui_element_get_secondary_color,
  (code *)ui_element_get_border_color,
  (code *)screen_resume_nothing
};
static code *const VTABLE_00101724[8] = {   /* 0x00101724; in kh.mod each entry is the method's offset from
                                                the table */
  (code *)ui_element_destroy,
  (code *)ui_element_update_nothing,
  (code *)ui_element_handle_key_nothing,
  (code *)ui_element_draw_over_children_nothing,
  (code *)ui_element_draw_nothing,
  (code *)ui_element_get_primary_color,
  (code *)ui_element_get_secondary_color,
  (code *)ui_element_get_border_color
};

/* The double constants the code passes to the double routines, as float64 (their words are the
   *_LOW_WORD / *_HIGH_WORD literals above). */
static const float64 DOUBLE_180 = { DOUBLE_180_LOW_WORD, DOUBLE_180_HIGH_WORD };
static const float64 DOUBLE_1_POINT_1 = { DOUBLE_1_POINT_1_LOW_WORD, DOUBLE_1_POINT_1_HIGH_WORD };
static const float64 DOUBLE_360 = { DOUBLE_360_LOW_WORD, DOUBLE_360_HIGH_WORD };
static const float64 DOUBLE_4_POINT_5 = { DOUBLE_4_POINT_5_LOW_WORD, DOUBLE_4_POINT_5_HIGH_WORD };
static const float64 DOUBLE_800 = { DOUBLE_800_LOW_WORD, DOUBLE_800_HIGH_WORD };
static const float64 DOUBLE_MINUS_180 = { DOUBLE_MINUS_180_LOW_WORD, DOUBLE_MINUS_180_HIGH_WORD };
static const float64 DOUBLE_MINUS_ONE = { DOUBLE_MINUS_ONE_LOW_WORD, DOUBLE_MINUS_ONE_HIGH_WORD };
static const float64 EIGHT_DOUBLE = { EIGHT_DOUBLE_LOW_WORD, EIGHT_DOUBLE_HIGH_WORD };
static const float64 HALF_DOUBLE = { HALF_DOUBLE_LOW_WORD, HALF_DOUBLE_HIGH_WORD };
static const float64 HALF_PI_CORRECTION = { HALF_PI_CORRECTION_LOW_WORD, HALF_PI_CORRECTION_HIGH_WORD };
static const float64 HALF_PI_FIRST_33_BITS =
  { HALF_PI_FIRST_33_BITS_LOW_WORD, HALF_PI_FIRST_33_BITS_HIGH_WORD };
static const float64 HALF_PI_FIRST_33_BITS_TAIL =
  { HALF_PI_FIRST_33_BITS_TAIL_LOW_WORD, HALF_PI_FIRST_33_BITS_TAIL_HIGH_WORD };
static const float64 HALF_PI_SECOND_33_BITS =
  { HALF_PI_SECOND_33_BITS_LOW_WORD, HALF_PI_SECOND_33_BITS_HIGH_WORD };
static const float64 HALF_PI_SECOND_33_BITS_TAIL =
  { HALF_PI_SECOND_33_BITS_TAIL_LOW_WORD, HALF_PI_SECOND_33_BITS_TAIL_HIGH_WORD };
static const float64 NINE_DOUBLE = { NINE_DOUBLE_LOW_WORD, NINE_DOUBLE_HIGH_WORD };
static const float64 ONE_DOUBLE = { ONE_DOUBLE_LOW_WORD, ONE_DOUBLE_HIGH_WORD };
static const float64 REDUCTION_CONSTANT = { REDUCTION_CONSTANT_LOW_WORD, REDUCTION_CONSTANT_HIGH_WORD };
static const float64 REDUCTION_CONSTANT_HIGH_PART =
  { REDUCTION_CONSTANT_HIGH_PART_LOW_WORD, REDUCTION_CONSTANT_HIGH_PART_HIGH_WORD };
static const float64 REDUCTION_CONSTANT_LOW_PART =
  { REDUCTION_CONSTANT_LOW_PART_LOW_WORD, REDUCTION_CONSTANT_LOW_PART_HIGH_WORD };
static const float64 REDUCTION_PERIOD = { REDUCTION_PERIOD_LOW_WORD, REDUCTION_PERIOD_HIGH_WORD };
static const float64 REDUCTION_QUARTER_PERIOD =
  { REDUCTION_QUARTER_PERIOD_LOW_WORD, REDUCTION_QUARTER_PERIOD_HIGH_WORD };
static const float64 SIN_KERNEL_S1 = { SIN_KERNEL_S1_LOW_WORD, SIN_KERNEL_S1_HIGH_WORD };
static const float64 TWO_DOUBLE = { TWO_DOUBLE_LOW_WORD, TWO_DOUBLE_HIGH_WORD };
static const float64 TWO_OVER_PI = { TWO_OVER_PI_LOW_WORD, TWO_OVER_PI_HIGH_WORD };
static const float64 DOUBLE_0_POINT_01 = { DOUBLE_0_POINT_01_LOW_WORD, DOUBLE_0_POINT_01_HIGH_WORD };
static const float64 DOUBLE_0_POINT_0175 =   /* GUESS: pi / 180 rounded to 0.0175 */
  { DOUBLE_0_POINT_0175_LOW_WORD, DOUBLE_0_POINT_0175_HIGH_WORD };

#endif /* KH_MOD_H */
