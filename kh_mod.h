/*
 * kh_mod.h - kh.mod (applet 0x01026191): types, globals and prototypes
 *
 * Source module : dumps/mod/11839/kh.mod (164424 bytes)
 * SHA-256       : 91b28342b14bf8268657f79da7722c5099a496b2c078f90375d93a82ec37fb31
 * Ghidra base   : 0x00100000 (= khvcemu load address); file offset = address - 0x100000
 * Functions     : 449 from Ghidra (FUN_00100028 removed: always 0 in User mode) + hand-written ones Ghidra has no function for
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
typedef unsigned long long undefined8;
typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef unsigned long long ulonglong;
typedef long long longlong;
typedef unsigned char  byte;
typedef unsigned char  bool;    /* Ghidra's boolean: 0 or 1 (C89 has no bool) */
#define true  1                 /* Ghidra's boolean constants (keywords only in C++ and C23) */
#define false 0
#ifndef NULL
#define NULL  ((void *)0)        /* used by the hand-written functions; no standard header is included */
#endif
typedef int            code();  /* Ghidra: function of unknown signature (a call through (code *) is valid C) */
typedef int            int3;    /* Ghidra: a 3-byte integer (only used in casts; kept in an int) */
#define UndefinedInstruction (*(byte *)0x4)   /* Ghidra's label for address 4 (the ARM undefined-
                                                instruction vector); &UndefinedInstruction = 4 */

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
                                                FUN_00100a58's pool (GUESS: fdlibm kernel_cos), which
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
                                                low word first. The second copy is in FUN_00100a58's
                                                pool (GUESS: kernel_cos): the 0.5*z of fdlibm's
                                                1 - (0.5*z - (z*r - x*y)), z = x*x. The third is in
                                                FUN_00100d88's (GUESS: rem_pio2): fdlibm's `half` in the
                                                rounding n = (int)(|x| * invpio2 + half). The fourth is in
                                                FUN_00101268's (GUESS: kernel_sin): the half*y of
                                                x - ((z*(half*y - v*r) - y) - v*S1) */
#define TWO_DOUBLE_LOW_WORD  0x00000000u     /* was DAT_001007ec (word at 0x001007EC) */
#define TWO_DOUBLE_HIGH_WORD 0x40000000u     /* was DAT_001007f0 (word at 0x001007F0) */
                                             /* together the IEEE-754 double 2.0 = 0x4000000000000000,
                                                low word first */
#define QUARTER_PI_HIGH_WORD 0x3FE921FB      /* was DAT_001008c4 (word at 0x001008C4), DAT_001009ac
                                                (word at 0x001009AC) and DAT_0010115c (word at
                                                0x0010115C): three copies of the high word of pi/4
                                                (0x3FE921FB54442D18 = 0.785398...), one in each of
                                                three literal pools (the third: FUN_00100d88, GUESS:
                                                rem_pio2, "no reduction needed"). fdlibm's range test
                                                |x|_high <= 0x3fe921fb ("|x| <= ~pi/4") before reducing
                                                the argument, in FUN_001007f4 and FUN_001008d0 (GUESS:
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
                                                literal pools of FUN_001007f4 and FUN_001008d0 (GUESS:
                                                fdlibm cos and sin, whose `double z = 0.0` this is).
                                                sin passes it as kernel_sin's tail argument for
                                                |x| <= pi/4 (kh_mod.c FUN_001008d0). A third copy is in
                                                FUN_001009b8's pool (GUESS: sqrt), which compares x with
                                                it (FUN_001256b4) and sets errno = EDOM and returns NaN
                                                for x < 0. A fourth copy is in FUN_00100d88's pool
                                                (GUESS: rem_pio2), which presets y[1] = 0 with it.
                                                In cos it is
                                                loaded into r2:r3 at entry as kernel_cos's tail argument
                                                for |x| <= pi/4. In the call to FUN_00100d88 (rem_pio2)
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
                                                the literal pools of FUN_001007f4 and FUN_001008d0
                                                (GUESS: fdlibm cos and sin), and a third in
                                                FUN_001009b8's (GUESS: sqrt). cos and sin return it for
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
                                                (FUN_00100a58, GUESS: kernel_cos) */
#define THREE_TENTHS_HIGH_WORD 0x3FD33333    /* was DAT_00100c18 (word at 0x00100C18): the high word of
                                                0.3 (0x3FD3333333333333), fdlibm k_cos.c's range test
                                                ix < 0x3FD33333 ("|x| < 0.3"): below it kernel_cos uses
                                                1 - (0.5*z - (z*r - x*y)), above it it subtracts qx
                                                first (FUN_00100a58, GUESS: kernel_cos). Compared as a
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
/* FUN_00100d88 (GUESS: rem_pio2) - limits between its three ways of reducing x */
#define MEDIUM_ARGUMENT_LIMIT_HIGH_WORD 0x413921FB  /* was DAT_00101188 (word at 0x00101188): high word
                                                of ~1647099 (about 2^20 * pi/2), fdlibm e_rem_pio2.c's
                                                medium-size limit (ix <= 0x413921fb). Above it the large-
                                                argument path runs. Compared as a signed int, so no u */
#define LARGE_ARGUMENT_EXPONENT_LIMIT  0x469        /* was DAT_001011a0 (word at 0x001011A0): 1129, a
                                                biased exponent (1129 - 1023 = 106): for |x| >= 2^106 the
                                                large-argument path first scales x by a table entry */
#define LARGE_ARGUMENT_SCALE_TABLE_OFFSET 0x00027000  /* was DAT_001011a4 (word at 0x001011A4): PC-relative
                                                offset; + 0x101034 (the pc) = 0x00128034, a table of
                                                doubles (1.1257e-16, 1.5993e-32, -7.27e-48, 1.49e-63,
                                                ...) indexed by FUN_00100288's result */
/* The large-argument path (|x| > ~2^20*pi/2) is the ARM library's own, not fdlibm's (fdlibm calls
   __kernel_rem_pio2 there). It splits x (low word & 0xfc000000 and the rest), multiplies both parts
   by a two-part constant C = HIGH_PART + LOW_PART, sums the partial products and reduces modulo the
   period K (FUN_001259e8). Checked from the values: C_hi + C_lo = 0.426041899379994537522 and
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
                                                = 2*pi*C: the modulus FUN_001259e8 reduces by */
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
                                             /* ... and adds 9.0, then converts to int (FUN_00125554)
                                                and halves it: the quadrant. GUESS: why 8 and 9 */
#define TWO_OVER_PI_LOW_WORD   0x6DC9C883u    /* was DAT_0010118c (word at 0x0010118C) */
#define TWO_OVER_PI_HIGH_WORD  0x3FE45F30u    /* was DAT_00101190 (word at 0x00101190) */
                                             /* 2/pi = 6.36619772367581382433e-01 (0x3FE45F306DC9C883),
                                                fdlibm's invpio2: the medium case's
                                                n = (int)(|x| * invpio2 + half) */
#define HALF_PI_DOUBLE_LOW_WORD  0x54442D18u  /* was DAT_001007d4 (word at 0x001007D4) */
#define HALF_PI_DOUBLE_HIGH_WORD 0x3FF921FBu  /* was DAT_001007d8 (word at 0x001007D8) and
                                                 DAT_0010116c (word at 0x0010116C; in FUN_00100d88,
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
#define ACOS_DENOMINATOR_TABLE_OFFSET 0x00027B20  /* was DAT_001007cc (word at 0x001007CC): PC-relative
                                                    offset; + 0x1004c4 (the pc) = 0x00127FE4, the 4
                                                    doubles of the acos denominator (fdlibm qS1..qS4) */
#define ACOS_NUMERATOR_TABLE_OFFSET   0x00027AE8  /* was LAB_001007d0 (word at 0x001007D0): PC-relative
                                                    offset; + 0x1004cc (the pc) = 0x00127FB4, the 6
                                                    doubles of the acos numerator (fdlibm pS0..pS5) */
#define HALF_PI_PIECES_TABLE_OFFSET   0x00027184  /* was DAT_0010119c (word at 0x0010119C): PC-relative
                                                    offset; + 0x100f40 (the pc) = 0x001280C4, a table of
                                                    pi/2 in three 33-bit pieces, each with its tail, 16
                                                    bytes per row (fdlibm e_rem_pio2.c):
                                                      row 0: pio2_1 1.5707963267341256,
                                                             pio2_1t 6.0771005065061922e-11
                                                      row 1: pio2_2 6.077100506303966e-11,
                                                             pio2_2t 2.0222662487959506e-21
                                                      row 2: pio2_3 2.0222662487111665e-21,
                                                             pio2_3t 8.4784276603688996e-32
                                                    FUN_00100d88 (GUESS: rem_pio2) loops over rows 1 and
                                                    2 for fdlibm's 2nd and 3rd medium-path refinements,
                                                    when the bits lost to cancellation exceed
                                                    33*k - 17 (16, then 49) */
#define SIGNAL_MESSAGE_TABLE_OFFSET   0x00026C1C  /* was DAT_001015cc (word at 0x001015CC): PC-relative
                                                    offset; + 0x101500 (the pc) = 0x0012811C, the ARM C
                                                    library's signal-message table: 13 entries of 23
                                                    bytes, one per signal (the decompiled
                                                    `signal * 0x17 + OFFSET + 0x1014e9` is that pc minus
                                                    one entry, as signals start at 1):
                                                      1 SIGABRT  "Abnormal termination"
                                                      2 SIGFPE   "Arithmetic exception: " (+ detail)
                                                      3 SIGILL   "Illegal instruction"
                                                      4 SIGINT   "Interrupt received"
                                                      5 SIGSEGV  "Illegal address"
                                                      6 SIGTERM  "Termination request"
                                                      7 SIGSTAK  "Stack overflow"
                                                      8 SIGRTRED "Redirect: can't open: "
                                                      9 SIGRTMEM "Out of heap memory"
                                                     10 SIGUSR1  "User-defined signal 1"
                                                     11 SIGUSR2  "User-defined signal 2"
                                                     12 SIGPVFN  "Pure virtual fn called"
                                                     13 SIGCPPL  "C++ library exception"
                                                    Used by the default signal handler (0x001014d4,
                                                    shown inside FUN_00101458). GUESS: the ARM signal
                                                    names (from ARM's signal.h numbering) */
#define SIN_KERNEL_TABLE_OFFSET       0x00026E04  /* was DAT_001013cc (word at 0x001013CC): PC-relative
                                                    offset; + 0x1012f0 (the pc) = 0x001280F4, the 5
                                                    doubles S2..S6 of the sin kernel polynomial (fdlibm
                                                    k_sin.c, identical to the last digit):
                                                    8.33333333332248946124e-03, -1.98412698298579493134e-04,
                                                    2.75573137070700676789e-06, -2.50507602534068634195e-08,
                                                    1.58969099521155010221e-10. Evaluated by FUN_00100c2c
                                                    in FUN_00101268 (GUESS: kernel_sin). The table follows
                                                    the pi/2 pieces (HALF_PI_PIECES_TABLE_OFFSET) */
#define COS_KERNEL_TABLE_OFFSET       0x00027538  /* was DAT_00100c14 (word at 0x00100C14): PC-relative
                                                    offset; + 0x100acc (the pc) = 0x00128004, the 6
                                                    doubles of the cos kernel polynomial (fdlibm k_cos.c
                                                    C1..C6, identical to the last digit), evaluated by
                                                    FUN_00100c2c in FUN_00100a58 (GUESS: kernel_cos) */

#define DOUBLE_EXPONENT_MASK_SHIFTED 0xFFE00000u  /* was DAT_00124e08 (word at 0x00124E08), in the
                                                     soft-float library's literal pool: a double's
                                                     11-bit exponent mask 0x7FF00000 shifted left by 1,
                                                     to match a high word shifted left by 1 (sign bit
                                                     dropped). (MASK & ~(hi << 1)) == 0 means "all
                                                     exponent bits set": the operand is Inf or NaN.
                                                     Used by the add/subtract routines FUN_00124954,
                                                     FUN_00124b40, FUN_00124b84 and by their copy
                                                     inlined into FUN_00100c2c */
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
                                                     stands for. Used in FUN_00124954 (double add) and
                                                     in its copy inlined into FUN_00100c2c */
#define DOUBLE_ADD_FINITE_OPERANDS_CODE 0x10000011u  /* was DAT_00124e0c (word at 0x00124E0C), next to
                                                     DOUBLE_ADD_NONFINITE_OPERAND_CODE: the control word
                                                     for the same special-case handler when both
                                                     operands of the double add are finite (chosen
                                                     where the exponents are aligned, LAB_001249ac).
                                                     Same low bits (1 = add, 0x10 = double precision),
                                                     special-case bit 0x10000000 instead of 0x04000000.
                                                     GUESS: which IEEE exception class that bit stands
                                                     for (for finite operands, presumably overflow /
                                                     inexact). Used in FUN_00124954 (add), FUN_00124b40
                                                     and FUN_00124b84 (subtract, through the same add
                                                     core) and the copy inlined into FUN_00100c2c */
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
extern undefined4 ZERO_DOUBLE;              /* was DAT_001007b4: the IEEE-754 double 0.0, two zero words
                                               at 0x001007B4..0x001007BB. FUN_0010041c (GUESS: acos)
                                               returns it for x == 1: `adr r1, ZERO_DOUBLE;
                                               ldmia r1, {r0, r1}` loads both words as the result */
extern undefined4 NAN_DOUBLE;               /* was DAT_001007bc: the IEEE-754 double quiet NaN
                                               0x7FF80000_00000001 (low word 1, high 0x7FF80000) at
                                               0x001007BC..0x001007C3. FUN_0010041c (GUESS: acos)
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
void * kh_GetAppFieldPtr_dc(void);   /* 0x0010CF7C */
uint32 * kh_GetFpStatusPtr(void);   /* 0x0010CFA0 */
boolean kh_HandleEvent(KHApp *pMe,AEEEvent eCode,uint16 wParam,uint32 dwParam);   /* 0x0010E060 */
void kh_OnAppStop(KHApp *pMe);   /* 0x001127E0 */
void kh_OnAppStart(KHApp *pMe);   /* 0x00119678 */
void kh_OnKey(KHApp *pMe,AEEEvent eCode,uint16 wParam,uint32 dwParam);   /* 0x0011A804 */
void kh_OnKeyRelease(void *pGame,uint16 wParam);   /* 0x0011AA6C */

/* No Ghidra function exists for these; bodies are hand-written in the .c file. */
uint32 AEEApplet_AddRef(IApplet *po);
boolean AEEApplet_HandleEvent(IApplet *po, AEEEvent evt, uint16 wParam, uint32 dwParam);
int AEEClsCreateInstance(AEECLSID ClsId, IShell *pIShell, IModule *po, void **ppObj);
uint32 AEEMod_AddRef(IModule *po);
void AEEMod_FreeResources(IModule *po, IHeap *ph, IFileMgr *pfm);

/* Not yet identified (auto-named by Ghidra). */
void FUN_00100104(int param_1);
void * memset(void *destination,uint byteCount);   /* 0x00100110 GUESS: name, see kh_mod.c */
void memcpy(void *destination,void *source,uint byteCount);   /* 0x00100168 GUESS: name, see kh_mod.c */
void memcpy_word_aligned(void *destination,void *source,uint byteCount);   /* 0x0010021C GUESS: name, see kh_mod.c */
ulonglong FUN_00100288(uint param_1,uint param_2);
int FUN_0010035c(uint param_1,uint param_2);
undefined4 FUN_0010041c(int param_1,uint param_2);
uint FUN_001007f4(int param_1,uint param_2);
undefined4 FUN_001008d0(int param_1,uint param_2);
undefined4 FUN_001009b8(uint param_1,uint param_2);
void FUN_00100a38(undefined4 param_1);
undefined4 FUN_00100a58(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4);
uint FUN_00100c2c(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
int FUN_00100d88(undefined4 param_1,uint param_2,undefined8 *param_3);
undefined4 FUN_00101268(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4,int param_5);
undefined8 FUN_001013e0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, uint param_5);
void FUN_00101440(undefined4 param_1,undefined4 param_2);
undefined4 FUN_00101458(int param_1,char *param_2);
void debug_write_char(char character);   /* 0x00101638 GUESS: name, see kh_mod.c */
undefined4 FUN_00101ad8(int *param_1,int param_2);
void FUN_001051d4(int param_1,int param_2);
void FUN_00105224(int *param_1,int param_2);
int FUN_001052e0(int param_1,undefined4 param_2,int param_3,int param_4,int param_5,int param_6, undefined4 param_7,undefined4 param_8,int param_9);
void FUN_001053a8(undefined4 param_1,undefined4 param_2,int param_3,int param_4,int param_5, int param_6,undefined4 param_7,int param_8,int param_9,int param_10,int param_11, int param_12,int param_13);
int ui_element_add_child(UIElement *parent,UIElement *child,int id);   /* 0x001054D8 GUESS: name */
void FUN_00105538(int param_1,undefined4 param_2,int param_3);
void FUN_001055c4(int param_1,undefined4 param_2,int param_3,undefined4 param_4,int param_5);
void FUN_001056d0(int *param_1,int param_2);
int FUN_001056ec(int param_1,int param_2,int param_3);
void key_picker_restore_original(UIElement *picker);   /* 0x001056F4 GUESS: name */
void FUN_00105734(undefined4 *param_1,int param_2);
void FUN_00105c5c(int param_1);
void FUN_00105d48(int param_1);
void FUN_00105d7c(int param_1);
void FUN_00105dc8(int param_1);
void FUN_00105e44(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_00106130(int param_1,undefined4 param_2,int param_3,int param_4,undefined4 param_5);
void FUN_00106354(int param_1,int param_2);
void FUN_00106398(int param_1,int *param_2,int *param_3,undefined4 param_4);
void FUN_0010673c(int *param_1,undefined4 param_2,int *param_3,undefined4 param_4);
void FUN_00106a94(int *param_1,int *param_2);
void FUN_00106bd4(int *param_1,int *param_2,int *param_3);
void FUN_00106e44(int param_1,undefined4 param_2,int *param_3);
void FUN_00106fb0(int *param_1,undefined4 param_2,int *param_3);
void FUN_00107230(int *param_1,undefined4 param_2,int *param_3);
void FUN_001077d0(int param_1,int *param_2,int param_3,int param_4,int param_5,undefined4 param_6, int param_7);
void FUN_00107adc(int param_1,int param_2,undefined4 param_3,int *param_4,short *param_5, undefined4 param_6,uint param_7,short param_8);
void FUN_00107d24(int *param_1);
void FUN_00107e48(undefined4 param_1,int param_2);
int list_get_entry(UIList *list,int index);   /* 0x00107EA4 GUESS: name, see kh_mod.c */
int ui_element_find_child(UIElement *element,int id);   /* 0x00107EC4 GUESS: name */
void * FUN_00107ecc(undefined4 param_1,undefined4 param_2);
int FUN_00107f88(int param_1);
ulonglong FUN_00107fd0(int param_1,int param_2,int param_3);
undefined4 FUN_00107fec(int param_1,undefined4 param_2);
int screen_stack_top(ScreenStack *stack);   /* 0x001080AC GUESS: name */
int list_find_entry(UIList *list,int id);   /* 0x001080C8 GUESS: name */
void FUN_0010810c(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5, undefined4 param_6);
void FUN_001082e0(int param_1,undefined4 param_2,int param_3,undefined4 param_4,undefined4 param_5, undefined4 param_6,undefined4 param_7,int param_8);
undefined4 FUN_001083d8(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
undefined4 FUN_00108414(int param_1,undefined4 param_2,int param_3);
bool FUN_001084e4(undefined4 param_1,undefined4 param_2,int param_3);
int ui_element_handle_key(UIElement *element,int eventCode,int keyCode,int keyParameter);   /* 0x00108524 GUESS: name */
int FUN_0010873c(int *param_1,undefined4 param_2,int param_3,undefined4 param_4);
void FUN_00108840(int param_1,short param_2);
void FUN_0010888c(int *param_1,void *param_2,int *param_3,void *param_4,void *param_5);
bool FUN_00108e8c(int param_1);
bool FUN_00108ed8(int param_1);
int FUN_00108f28(int param_1,int param_2);
void screen_stack_close_all(ScreenStack *stack);   /* 0x00108FA0 GUESS: name */
void screen_stack_close_top(ScreenStack *stack,int redraw);   /* 0x00108FCC GUESS: name */
void screen_stack_open(ScreenStack *stack,int *screen);   /* 0x001090B8 GUESS: name */
int list_set_entry(UIList *list,int id,int entry);   /* 0x001090FC GUESS: name */
void FUN_001091fc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_001092c0(int param_1,int param_2);
int ui_element_remove_child(UIElement *element,int id,int destroy);   /* 0x00109308 GUESS: name */
void FUN_00109368(int param_1);
void list_remove_entry(UIList *list,int id);   /* 0x00109380 GUESS: name */
void thunk_FUN_0011e154(int param_1);
undefined4 FUN_001093f8(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5 );
void FUN_00109534(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5);
void FUN_0010955c(int param_1,int param_2,int param_3);
void FUN_00109750(int param_1,undefined4 param_2);
int FUN_00109780(int *param_1,undefined4 param_2,int param_3);
void key_picker_setup(UIElement *picker,KeyOption *options,int *setting,int index);   /* 0x001098D8 GUESS: name */
void FUN_00109940(int param_1,int param_2);
void FUN_00109a10(int param_1,int param_2,int param_3,undefined4 param_4);
void FUN_00109b4c(int param_1,int param_2,int param_3);
void FUN_00109f00(int param_1,undefined4 param_2);
void FUN_00109f48(int param_1,int param_2);
void FUN_00109ff8(int param_1,undefined4 param_2);
void FUN_0010a03c(int param_1,undefined4 param_2);
void FUN_0010a080(int param_1);
void FUN_0010a0d0(int param_1);
void game_pause(KHApp *app);   /* 0x0010A124 GUESS: name, see kh_mod.c */
int FUN_0010a12c(int param_1,undefined4 param_2,byte *param_3);
undefined8 FUN_0010a214(int param_1);
void FUN_0010a3e8(undefined4 param_1,int *param_2,uint param_3,int param_4);
void FUN_0010a46c(undefined4 param_1,int *param_2,undefined4 param_3,uint param_4);
void FUN_0010a498(int param_1,int param_2);
int * FUN_0010a528(int *param_1,int param_2,int param_3,int param_4);
int * FUN_0010a5d8(int *param_1,undefined4 param_2,int *param_3);
int * FUN_0010aa8c(int *param_1,int *param_2);
int * FUN_0010ac6c(int *param_1,int param_2);
undefined4 * FUN_0010af3c(undefined4 *param_1,undefined4 param_2,undefined4 param_3);
undefined4 * FUN_0010afc4(undefined4 *param_1);
undefined4 * FUN_0010b014(undefined4 *param_1,undefined4 param_2);
int * FUN_0010b080(int *param_1,undefined4 param_2);
int * FUN_0010b230(int *param_1,int param_2,int param_3,int param_4);
int * FUN_0010b2dc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5 ,undefined4 param_6,int param_7);
undefined1 * FUN_0010b3e8(undefined1 *param_1,undefined4 param_2,undefined4 param_3);
undefined1 * FUN_0010b478(undefined1 *param_1,undefined4 param_2,undefined4 param_3);
void * FUN_0010b4e4(void *param_1,int param_2);
undefined1 * FUN_0010b5e8(undefined1 *param_1,undefined4 param_2,undefined4 param_3);
undefined8 FUN_0010b650(int *param_1,undefined4 param_2,int param_3,int param_4,undefined4 param_5,int param_6, int param_7,int param_8);
undefined1 * FUN_0010b70c(undefined1 *param_1,undefined4 param_2,undefined4 param_3);
undefined4 * FUN_0010b804(undefined4 *param_1);
undefined1 * FUN_0010b870(undefined1 *param_1,undefined4 param_2,undefined4 param_3);
undefined1 * FUN_0010b8cc(undefined1 *param_1,undefined4 *param_2,undefined4 param_3);
void * FUN_0010b9b4(void *param_1);
undefined4 * FUN_0010ba08(undefined4 *param_1,undefined4 param_2);
undefined4 * FUN_0010bb2c(undefined4 *param_1,int param_2,undefined4 param_3);
int * FUN_0010bba0(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,int param_6,int param_7,int param_8,undefined1 param_9);
int * FUN_0010bd7c(int *param_1,int *param_2,undefined1 param_3);
int * FUN_0010be14(int *param_1);
undefined4 * FUN_0010be6c(undefined4 *param_1,int param_2,undefined4 param_3);
undefined8 FUN_0010bec4(int *param_1,int param_2,int param_3,int param_4);
int * FUN_0010c168(int *param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4, undefined2 param_5,int param_6);
undefined4 * FUN_0010c218(undefined4 *param_1,undefined4 *param_2);
void FUN_0010c2a8(int *param_1,int param_2);
void FUN_0010c2c4(int *param_1,int param_2);
void FUN_0010c3f8(int param_1,int param_2);
void FUN_0010c598(int param_1,int param_2);
void FUN_0010c620(int param_1,int param_2);
void FUN_0010c66c(int param_1,int param_2);
void FUN_0010c6b4(int *param_1,int param_2);
void FUN_0010c720(int *param_1,int param_2);
void FUN_0010c73c(int param_1,int param_2);
void FUN_0010c790(int param_1,int param_2);
void FUN_0010c800(int param_1,int param_2);
void FUN_0010c8b8(int param_1,int param_2);
void FUN_0010c92c(int param_1,int param_2);
void FUN_0010c9dc(int param_1,int param_2);
void FUN_0010ca1c(int param_1,int param_2);
void FUN_0010cab0(int param_1,int param_2);
void FUN_0010cc9c(int param_1,int param_2);
void FUN_0010cd2c(int param_1,int param_2);
void FUN_0010cda4(int param_1,int param_2);
void FUN_0010cdd8(int param_1,int param_2);
void FUN_0010ce08(undefined4 *param_1,int param_2);
void FUN_0010cee4(int param_1,int param_2);
void FUN_0010cfc4(int param_1,int param_2);
void FUN_0010d074(int param_1,undefined4 param_2);
void FUN_0010d18c(int param_1,int param_2);
void FUN_0010d1e0(int param_1,int param_2);
undefined4 FUN_0010d2fc(int param_1);
undefined4 FUN_0010d354(int param_1);
void FUN_0010d3a4(int param_1,undefined4 param_2);
uint FUN_0010d4dc(undefined4 param_1,undefined4 param_2);
undefined4 FUN_0010d56c(int param_1,int param_2);
undefined4 FUN_0010d7c4(int param_1,int param_2);
undefined4 FUN_0010d95c(int param_1,int param_2);
void FUN_0010db04(int param_1,undefined4 param_2);
int FUN_0010e1f8(int param_1);
void FUN_0010e210(undefined4 param_1,undefined4 *param_2,int *param_3);
void FUN_0010e280(int param_1,undefined4 *param_2,undefined4 *param_3);
undefined4 FUN_0010e448(int param_1,undefined4 *param_2);
void thunk_FUN_0012088c(int param_1,int *param_2);
void FUN_0010e94c(int *param_1);
int FUN_0010e9bc(int param_1);
void FUN_0010ea00(int param_1);
void FUN_0010ea64(int param_1);
undefined4 FUN_0010eb74(int param_1);
void FUN_0010ecb8(int param_1,undefined4 *param_2);
uint FUN_0010ed40(uint param_1);
void FUN_0010ed54(int param_1,int param_2,undefined4 param_3);
void FUN_0010edec(int param_1);
int FUN_0010eefc(undefined4 param_1,int param_2,int *param_3,undefined4 param_4);
undefined4 FUN_0010efd4(undefined4 param_1,undefined4 param_2,int param_3,int param_4);
int FUN_0010f058(int param_1,int param_2);
void FUN_0010f244(int *param_1,undefined4 *param_2);
bool FUN_0010f2cc(int param_1);
undefined8 FUN_0010f2e8(int param_1,uint param_2,undefined4 param_3,uint param_4,undefined4 param_5, undefined4 param_6,uint param_7);
void FUN_0010f4d0(int param_1,uint param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
                 uint param_6);
void FUN_0010f880(int param_1);
void FUN_0010f8e8(int param_1);
void FUN_0010f9a4(int param_1);
bool FUN_0010fa50(int param_1,int param_2,int param_3);
int FUN_0010faa8(int param_1,undefined4 param_2);
void FUN_0010fb90(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_0010fbf4(int *param_1,uint param_2,uint param_3,uint param_4,uint param_5,int param_6,
                 int param_7,uint param_8,uint param_9,uint param_10);
uint FUN_0010ffdc(undefined4 param_1,undefined4 param_2,undefined4 param_3,uint param_4, undefined4 param_5,undefined4 param_6);
uint FUN_00110030(undefined4 param_1,undefined4 param_2,undefined4 param_3,uint param_4, undefined4 param_5,undefined4 param_6);
int FUN_00110084(undefined4 param_1,int param_2,undefined4 param_3,int param_4,int param_5);
undefined4 FUN_00110190(int param_1,undefined4 *param_2,undefined4 *param_3);
void FUN_00110564(int param_1,int param_2,int param_3);
undefined4 FUN_001106a0(undefined4 param_1,int *param_2,int param_3,int param_4);
void FUN_00110860(int param_1,int param_2);
void FUN_001108ac(undefined4 param_1,int param_2,int param_3);
uint FUN_00110924(int *param_1);
undefined8 FUN_0011295c(undefined4 *param_1,int *param_2,int *param_3,int *param_4,undefined4 param_5);
bool FUN_00112a98(int param_1,undefined4 param_2,int param_3);
void FUN_00112b4c(int param_1);
int FUN_00112c18(int param_1);
void FUN_00112c44(int *param_1);
undefined4 FUN_00112c9c(int param_1,int param_2);
undefined8 FUN_00112cdc(int param_1,int *param_2,int param_3);
int FUN_00112cfc(int param_1);
int FUN_00112d28(int param_1);
int FUN_00112d54(int param_1);
undefined4 FUN_00112dbc(int param_1,int param_2);
undefined4 FUN_00112e20(int param_1,undefined4 param_2);
undefined8 FUN_00112e84(int param_1);
void FUN_00113030(int param_1,undefined4 param_2,uint param_3,uint param_4,undefined4 param_5);
void FUN_0011316c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,int param_9,undefined4 param_10,undefined4 param_11);
void FUN_001132a8(int param_1);
void FUN_00113340(int param_1);
undefined8 FUN_00113374(undefined4 param_1,uint param_2,uint param_3,uint param_4,uint param_5);
void FUN_00113474(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5);
void FUN_00113490(undefined4 *param_1,int param_2);
void FUN_00113524(undefined4 *param_1,int param_2);
undefined4 FUN_001135b8(int param_1,int param_2);
void FUN_001135dc(int param_1);
uint FUN_00113654(undefined4 param_1,int param_2);
undefined4 FUN_001136c8(int param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4, undefined4 *param_5,undefined4 param_6);
undefined4 FUN_00113784(int param_1);
int FUN_001137a4(int param_1,int param_2);
uint FUN_001137d4(undefined4 param_1,undefined4 *param_2);
uint FUN_00113820(undefined4 param_1,uint param_2,uint param_3,uint param_4);
void FUN_0011386c(uint param_1,int param_2);
void FUN_00113cc4(undefined4 *param_1,int param_2);
undefined1 FUN_00113cd4(int param_1,int param_2);
int FUN_00113cfc(undefined4 param_1,int param_2);
int FUN_00113da4(int *param_1,int param_2,int param_3,int param_4,int param_5,uint param_6);
undefined4 FUN_00114120(int param_1,undefined4 param_2,undefined4 *param_3,undefined4 *param_4);
undefined1 FUN_00114198(int param_1,undefined4 param_2);
undefined1 FUN_001141f4(int param_1,int param_2);
int * FUN_0011421c(int *param_1,undefined4 param_2,undefined4 *param_3);
undefined4 FUN_00114240(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 *param_6,int param_7,undefined4 param_8,int param_9);
void FUN_0011442c(undefined4 param_1,undefined4 *param_2);
void FUN_0011448c(undefined4 param_1,int *param_2,undefined4 param_3,undefined4 *param_4);
void FUN_00114520(undefined4 param_1,int *param_2,undefined4 param_3,undefined4 *param_4);
void FUN_001145b4(int param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4);
void FUN_00114610(int param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4);
undefined4 FUN_00114638(int param_1);
int FUN_001146f0(int param_1,undefined4 param_2);
undefined4 FUN_00114750(int param_1);
void FUN_00114774(int *param_1,undefined4 param_2,undefined4 param_3);
void FUN_001147ec(undefined4 *param_1,int param_2,int *param_3);
undefined4 FUN_00114898(int param_1);
undefined4 FUN_001148a0(int param_1);
void FUN_001148a8(int param_1,int param_2);
int FUN_001148c8(int param_1,int param_2);
bool FUN_00114910(int param_1);
void FUN_0011492c(int param_1);
void FUN_0011498c(int param_1,uint param_2);
void FUN_00114a1c(int param_1,undefined4 param_2);
undefined8 FUN_00114a94(int param_1,undefined4 param_2,void *param_3,undefined4 param_4,undefined4 param_5,
                        undefined4 param_6,undefined4 param_7);
undefined4 FUN_00114b48(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5 ,undefined4 param_6,undefined4 param_7);
void FUN_00114c00(int param_1,undefined4 param_2,undefined4 param_3,int param_4);
void FUN_001150d0(int param_1,int *param_2);
void FUN_00115118(undefined4 *param_1,undefined4 param_2,uint param_3);
void FUN_001174ac(int param_1,undefined4 param_2);
void FUN_00117d30(int param_1,int *param_2);
void FUN_00117dd8(int param_1,undefined4 param_2);
undefined8 FUN_001180c4(int param_1,uint param_2);
void FUN_00118318(int param_1,int *param_2);
void FUN_00118640(int param_1,int *param_2);
void FUN_0011868c(int param_1,undefined4 param_2);
void FUN_00118910(int param_1,undefined4 param_2);
void FUN_00118ed8(undefined4 *param_1,int *param_2,int param_3);
void FUN_001195f8(undefined4 *param_1);
void FUN_00119a28(int param_1,int *param_2);
undefined4 FUN_00119abc(int param_1);
undefined8 FUN_00119b0c(undefined4 param_1,int param_2,undefined4 param_3);
undefined8 FUN_00119c10(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5 ,undefined4 param_6,undefined4 param_7);
undefined8 FUN_00119c60(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
undefined4 FUN_00119ce0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5 ,undefined4 param_6);
bool FUN_00119d58(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6);
void FUN_0011a2f4(int param_1,int param_2);
void FUN_0011a3ec(int param_1,int param_2,undefined4 param_3);
void FUN_0011a4d8(int param_1,int param_2);
void FUN_0011a7dc(int param_1,int param_2);
void FUN_0011aad0(int param_1,int param_2);
void FUN_0011ab60(int param_1);
undefined8 FUN_0011abc4(int param_1,int param_2,uint param_3);
uint FUN_0011add0(uint param_1,int param_2);
undefined4 FUN_0011ae04(int param_1,undefined4 param_2,int *param_3,int param_4,int param_5);
void FUN_0011b044(int param_1,undefined4 param_2,int param_3,undefined4 param_4,int param_5, undefined4 *param_6);
bool FUN_0011b0cc(int param_1,undefined4 param_2,undefined4 param_3,int *param_4);
undefined4 FUN_0011b178(int param_1,int param_2);
undefined8 FUN_0011b518(int param_1,int param_2);
undefined4 FUN_0011b5f0(int param_1);
void FUN_0011b6f0(int param_1,undefined4 param_2);
void FUN_0011b890(int param_1,int *param_2);
undefined4 FUN_0011ba0c(int param_1,undefined4 param_2);
void FUN_0011bb00(undefined4 *param_1,int param_2);
void FUN_0011bb58(int param_1,int param_2);
int FUN_0011bb9c(int param_1,undefined4 *param_2);
undefined8 FUN_0011c330(int param_1,int param_2,uint param_3,uint param_4);
void FUN_0011c708(int param_1,int param_2,int param_3);
bool FUN_0011c860(int param_1,int param_2,undefined4 param_3);
void FUN_0011ca70(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5);
void FUN_0011ca8c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5);
void FUN_0011cb34(undefined4 param_1,undefined4 *param_2);
void FUN_0011cbc4(int param_1,int param_2,int param_3);
void FUN_0011cc14(int param_1,int param_2,int param_3);
undefined4 FUN_0011cc64(int param_1,int param_2,int param_3,undefined4 param_4);
undefined8 FUN_0011ceac(int param_1);
undefined4 FUN_0011cfdc(int param_1,undefined4 param_2,int param_3);
void FUN_0011d040(int param_1,undefined4 param_2,void *param_3);
int FUN_0011d104(int param_1,int param_2,int param_3);
int FUN_0011d168(int param_1,undefined4 param_2,undefined4 param_3);
void FUN_0011d28c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
undefined8 FUN_0011d3ec(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_0011d6cc(int param_1,int param_2);
int FUN_0011daac(int param_1,int param_2,undefined4 param_3,uint param_4);
uint FUN_0011dc9c(undefined4 param_1,int param_2,int *param_3);
undefined4 FUN_0011dce8(undefined4 param_1,int param_2,int *param_3);
undefined4 FUN_0011dd34(undefined4 param_1,int param_2,int *param_3);
int FUN_0011dd80(undefined4 param_1,int param_2,int *param_3);
void FUN_0011de04(int param_1,undefined4 *param_2);
void FUN_0011de64(int param_1);
void FUN_0011de70(int param_1);
void FUN_0011dedc(int param_1);
void FUN_0011df14(undefined4 *param_1);
void FUN_0011e010(int param_1);
void FUN_0011e07c(int param_1);
void FUN_0011e0b4(int param_1);
void FUN_0011e0fc(int param_1);
void FUN_0011e154(int param_1);
undefined4 FUN_0011e250(int param_1);
undefined4 FUN_0011e300(int param_1);
void FUN_0011e36c(int param_1,undefined4 param_2);
void FUN_0011e3c0(int param_1,uint param_2);
void FUN_0011e530(int param_1,undefined4 param_2,undefined4 param_3);
bool FUN_0011e574(int param_1,undefined4 param_2,undefined4 param_3,int *param_4);
undefined4 FUN_0011e6b8(int param_1,int param_2);
undefined4 FUN_0011ea18(int param_1);
undefined4 FUN_0011ead4(int param_1,undefined4 param_2);
undefined4 FUN_0011ec28(int param_1,int param_2);
void FUN_0011ed3c(int param_1,undefined4 *param_2);
void FUN_0011f280(int param_1);
void FUN_0011f2bc(int param_1,int *param_2,int param_3);
void FUN_0011f394(int param_1,char *param_2,undefined4 param_3,undefined4 param_4,int param_5);
void FUN_0011f540(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5);
void FUN_0011f630(int param_1);
void FUN_0011f66c(int param_1,int param_2);
void FUN_0011f680(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5);
void FUN_0011f7d4(int param_1,int param_2);
void FUN_0011f8ac(int param_1);
void FUN_0011f8e0(int param_1,uint param_2);
void FUN_0011fc80(int param_1,undefined4 param_2);
void FUN_0011fcc4(int param_1,int param_2,int param_3);
void thunk_FUN_0011fd90(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_0011fd90(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_0011fdbc(int param_1,int param_2,undefined1 param_3);
undefined4 FUN_0011fddc(int param_1,undefined4 param_2,int param_3,undefined4 param_4);
void FUN_0011fed8(int param_1,int param_2,undefined4 param_3);
void FUN_0011fef4(int param_1,undefined4 param_2,int param_3);
void FUN_0011ffc0(undefined4 *param_1,undefined4 param_2);
void FUN_00120024(int param_1,int param_2);
void FUN_001200ac(int param_1,undefined4 param_2);
void FUN_00120120(int param_1,undefined4 param_2,undefined4 param_3);
void FUN_001201cc(int param_1,undefined4 param_2);
void FUN_00120244(int param_1,undefined4 param_2);
void FUN_00120290(int param_1,undefined4 param_2);
void FUN_001202cc(int param_1,undefined4 param_2);
uint FUN_001202f4(uint param_1);
uint FUN_00120308(void);
void FUN_0012031c(int *param_1,int param_2);
void FUN_00120450(undefined4 *param_1);
void FUN_001204b0(int param_1,int param_2,int param_3);
void FUN_001204f0(undefined4 param_1,undefined4 param_2,int *param_3);
void FUN_0012056c(int param_1,int param_2);
bool FUN_0012059c(int param_1,int param_2);
void FUN_0012070c(int param_1,int param_2);
void FUN_0012088c(int param_1,int *param_2);
void FUN_00120be8(undefined4 *param_1,int *param_2,uint *param_3,uint *param_4,uint param_5);
void FUN_00120f8c(int param_1,int *param_2,int param_3,int *param_4,int param_5);
void FUN_00121134(int param_1,int *param_2,undefined4 param_3);
undefined8 FUN_001213fc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5 ,undefined4 param_6,undefined4 param_7);
void FUN_00121584(int param_1,int *param_2,int *param_3,int param_4);
void FUN_0012164c(int param_1,undefined4 param_2,int param_3);
void FUN_001216c4(int param_1);
void FUN_00121780(int param_1,undefined4 *param_2);
void FUN_00121ab0(int param_1);
void FUN_00121b98(int param_1,undefined4 param_2);
undefined8 FUN_00121c6c(int param_1,undefined4 param_2,int param_3,uint param_4);
void FUN_00122450(int param_1,byte *param_2,int param_3);
void FUN_001226e8(int *param_1,undefined4 param_2,int param_3);
undefined4 FUN_0012289c(int *param_1,undefined4 param_2,int param_3);
void FUN_00122954(int param_1,undefined4 param_2,int param_3,undefined4 param_4);
void FUN_00122b90(int param_1,int param_2,uint param_3,undefined4 param_4);
void FUN_00122f98(int param_1,int param_2,int param_3);
void FUN_0012312c(int param_1,int param_2,int param_3,undefined4 param_4);
void FUN_00123588(int param_1,int param_2,int param_3,undefined4 param_4);
void FUN_00123c24(int param_1,undefined4 param_2,undefined4 param_3,int param_4);
void FUN_00123d7c(int param_1,undefined4 param_2,int param_3);
void FUN_0012407c(int param_1,undefined4 param_2,undefined4 param_3);
void FUN_001241a8(int *param_1,undefined4 param_2,int param_3,undefined4 param_4);
void FUN_001242b4(int param_1);
undefined8 FUN_00124674(undefined4 param_1,undefined4 param_2,int param_3,int *param_4);
undefined8 FUN_001246b4(undefined4 param_1,undefined4 param_2,int param_3,int *param_4);
undefined8 FUN_001246f4(undefined4 param_1,undefined4 param_2,int param_3,int *param_4);
void FUN_00124734(undefined4 param_1,int param_2,int param_3,int *param_4);
uint FUN_0012479c(uint param_1,uint param_2);
uint FUN_00124954(uint param_1,uint param_2,uint param_3,uint param_4);
uint FUN_00124b40(uint param_1,uint param_2,uint param_3,uint param_4);
uint FUN_00124b84(uint param_1,uint param_2,uint param_3,uint param_4);
uint FUN_00124f24(uint param_1,uint param_2,uint param_3,uint param_4);
uint FUN_00124f44(uint param_1,uint param_2,uint param_3,uint param_4);
undefined8 FUN_001251ec(uint param_1,uint param_2,uint param_3,uint param_4);
uint FUN_001254d4(uint param_1,uint param_2,uint param_3,uint param_4);
uint FUN_00125554(uint param_1,uint param_2);
undefined8 FUN_00125604(uint param_1);
uint FUN_00125634(uint param_1,uint param_2,uint param_3,uint param_4);
uint FUN_001256b4(uint param_1,uint param_2,uint param_3,uint param_4);
uint FUN_00125734(uint param_1,uint param_2,uint param_3,uint param_4);
uint FUN_001259e8(uint param_1,uint param_2,uint param_3,uint param_4);
uint FUN_00125cd0(uint param_1,uint param_2);
uint FUN_00126248(uint param_1);
uint FUN_001262b0(uint param_1,uint param_2);
uint FUN_001263f8(uint param_1,uint param_2);
uint FUN_0012642c(uint param_1,uint param_2);
uint FUN_00126608(uint param_1,uint param_2);
uint FUN_00126618(uint param_1,uint param_2);
uint FUN_001267f0(uint param_1,uint param_2);
uint FUN_00126858(uint param_1);
uint FUN_001268c8(uint param_1);
uint FUN_001268fc(uint param_1,uint param_2);
uint FUN_00126964(uint param_1,uint param_2);
uint FUN_001269cc(uint param_1,uint param_2);


/* ---- Literal-pool words, named automatically from the module bytes ----------------------------
   Each was a Ghidra DAT_<address> label. PC-relative offsets (used as NAME + pc) are named after
   what they point to; other words are named after their value. The comment gives the old label(s),
   the word's address and how the name was derived. Generated, not reviewed one by one: names say
   what a word IS (its value or target), not necessarily what the code uses it for. */
#define AEECLSID_KH_APPLET_VALUE 0x01026191   /* was DAT_0010197c (word at 0x0010197C); BREW class identifier AEECLSID_KH_APPLET */
#define ADDRESS_OF_kh_HandleEvent_OFFSET 0x0000C70C   /* was DAT_00101980 (word at 0x00101980); PC-relative offset: + 0x101954 (the pc) = 0x0010E060 */
#define ADDRESS_OF_AEEMod_AddRef_OFFSET 0xFFFFFEFC   /* was DAT_00101ac8 (word at 0x00101AC8); PC-relative offset: + 0x101a88 (the pc) = 0x00101984 */
#define ADDRESS_OF_AEEMod_Release_OFFSET 0xFFFFFF38   /* was DAT_00101acc (word at 0x00101ACC); PC-relative offset: + 0x101a94 (the pc) = 0x001019CC */
#define ADDRESS_OF_AEEMod_CreateInstance_OFFSET 0xFFFFFEF8   /* was DAT_00101ad0 (word at 0x00101AD0); PC-relative offset: + 0x101aa0 (the pc) = 0x00101998 */
#define ADDRESS_OF_AEEMod_FreeResources_OFFSET 0xFFFFFF1C   /* was DAT_00101ad4 (word at 0x00101AD4); PC-relative offset: + 0x101aac (the pc) = 0x001019C8 */
extern undefined4 CODE_AT_00100FD0_SELF_RELATIVE_OFFSET;   /* was DAT_00102acc (word at 0x00102ACC = 0xFFFFE504); word relative to its own address: 0x00102ACC + 0xFFFFE504 = 0x00100FD0 */
#define WORD_HEXADECIMAL_2DE9998F 0x2DE9998F   /* was DAT_00102ad0 (word at 0x00102AD0); value 0x2DE9998F (770283919) */
#define WORD_HEXADECIMAL_1EC39991 0x1EC39991   /* was DAT_00102ad4 (word at 0x00102AD4); value 0x1EC39991 (516135313) */
#define WORD_HEXADECIMAL_0017A510 0x0017A510   /* was DAT_00102ad8 (word at 0x00102AD8); value 0x0017A510 (1549584) */
#define WORD_HEXADECIMAL_1F10FB19 0x1F10FB19   /* was DAT_00102adc (word at 0x00102ADC); value 0x1F10FB19 (521206553) */
#define STRING_TRAINING_OFFSET 0x000260D4   /* was DAT_00102ae0 (word at 0x00102AE0); PC-relative offset: + 0x101c3c (the pc) = 0x00127D10 */
#define WORD_HEXADECIMAL_03D18088 0x03D18088   /* was DAT_00102ae4 (word at 0x00102AE4); value 0x03D18088 (64061576) */
#define STRING_JTEXT_DOT_M3G_OFFSET 0x0002608C   /* was DAT_00102ae8 (word at 0x00102AE8); PC-relative offset: + 0x101cc4 (the pc) = 0x00127D50 */
#define STRING_RO_OFFSET 0x00026070   /* was DAT_00102aec (word at 0x00102AEC); PC-relative offset: + 0x101cdc (the pc) = 0x00127D4C */
#define STRING_PERCENT_S_PERCENT_S_PERCENT_S_OFFSET 0x00026060   /* was DAT_00102af0 (word at 0x00102AF0); PC-relative offset: + 0x101ce4 (the pc) = 0x00127D44 */
#define WORD_HEXADECIMAL_0252B33F 0x0252B33F   /* was DAT_00102af4, DAT_0011aa68 (word at 0x00102AF4); value 0x0252B33F (38974271) */
#define WORD_HEXADECIMAL_251509C8 0x251509C8   /* was DAT_00102af8, DAT_00108e80 (word at 0x00102AF8); value 0x251509C8 (622135752) */
#define WORD_HEXADECIMAL_310668B6 0x310668B6   /* was DAT_00102afc (word at 0x00102AFC); value 0x310668B6 (822503606) */
#define DATA_AT_00127ADC_OFFSET 0x00025CF0   /* was DAT_00102b00 (word at 0x00102B00); PC-relative offset: + 0x101dec (the pc) = 0x00127ADC */
#define DATA_AT_00127AF0_OFFSET 0x00025CEC   /* was DAT_00102b04 (word at 0x00102B04); PC-relative offset: + 0x101e04 (the pc) = 0x00127AF0 */
#define STRING_SAVEGAME_DOT_DAT_OFFSET 0x00025E28   /* was DAT_00102b08 (word at 0x00102B08); PC-relative offset: + 0x101ecc (the pc) = 0x00127CF4 */
#define STRING_TRAINING_OFFSET_2 0x00025E24   /* was DAT_00102b0c (word at 0x00102B0C); PC-relative offset: + 0x101eec (the pc) = 0x00127D10 */
#define STRING_REPLAYGAME_DOT_DAT_OFFSET 0x00025D78   /* was DAT_00102b10 (word at 0x00102B10); PC-relative offset: + 0x101fa4 (the pc) = 0x00127D1C */
#define WORD_HEXADECIMAL_01B449A3 0x01B449A3   /* was DAT_00102b14 (word at 0x00102B14); value 0x01B449A3 (28592547) */
#define WORD_HEXADECIMAL_24017E3E 0x24017E3E   /* was DAT_00102b18 (word at 0x00102B18); value 0x24017E3E (604077630) */
#define WORD_HEXADECIMAL_272E6865 0x272E6865   /* was DAT_00102b1c (word at 0x00102B1C); value 0x272E6865 (657352805) */
#define WORD_HEXADECIMAL_00C833EC 0x00C833EC   /* was DAT_00102b20 (word at 0x00102B20); value 0x00C833EC (13120492) */
#define WORD_HEXADECIMAL_04D4D70F 0x04D4D70F   /* was DAT_00102b24 (word at 0x00102B24); value 0x04D4D70F (81057551) */
#define DATA_AT_00127D2C_OFFSET 0x00025BFC   /* was DAT_00102b2c (word at 0x00102B2C); PC-relative offset: + 0x102130 (the pc) = 0x00127D2C */
#define STRING_PERCENT_D_OFFSET 0x000259EC   /* was DAT_00102b3c (word at 0x00102B3C); PC-relative offset: + 0x1022e0 (the pc) = 0x00127CCC */
#define STRING_PERCENT_D_OFFSET_2 0x00025904   /* was DAT_00102b48 (word at 0x00102B48); PC-relative offset: + 0x1023c8 (the pc) = 0x00127CCC */
#define WORD_HEXADECIMAL_FFC9C4DA 0xFFC9C4DA   /* was DAT_00102b50, DAT_00104c2c, DAT_001077b8, DAT_00108728 (word at 0x00102B50); value 0xFFC9C4DA (-3554086) */
#define WORD_HEXADECIMAL_19408333 0x19408333   /* was DAT_00102b54, DAT_00104c08, DAT_00108e64 (word at 0x00102B54); value 0x19408333 (423658291) */
#define WORD_HEXADECIMAL_0528CA88 0x0528CA88   /* was DAT_00102b5c, DAT_00104c58 (word at 0x00102B5C); value 0x0528CA88 (86559368) */
#define DATA_AT_00127D2C_OFFSET_2 0x000257A0   /* was DAT_00102b60 (word at 0x00102B60); PC-relative offset: + 0x10258c (the pc) = 0x00127D2C */
#define DATA_AT_00127D30_OFFSET 0x00025784   /* was DAT_00102b64 (word at 0x00102B64); PC-relative offset: + 0x1025ac (the pc) = 0x00127D30 */
#define DATA_AT_00127D30_OFFSET_2 0x0002576C   /* was DAT_00102b68 (word at 0x00102B68); PC-relative offset: + 0x1025c4 (the pc) = 0x00127D30 */
#define STRING_PERCENT_D_OFFSET_3 0x00025698   /* was DAT_00102b6c (word at 0x00102B6C); PC-relative offset: + 0x102634 (the pc) = 0x00127CCC */
#define WORD_HEXADECIMAL_10FB280A 0x10FB280A   /* was DAT_00102b70, DAT_00104c50 (word at 0x00102B70); value 0x10FB280A (284895242) */
#define ADDRESS_OF_FUNCTION_0010888c_OFFSET 0x000061E0   /* was DAT_00102b74 (word at 0x00102B74); PC-relative offset: + 0x1026ac (the pc) = 0x0010888C */
#define WORD_HEXADECIMAL_03B0A428 0x03B0A428   /* was DAT_00102b80, DAT_00104c18 (word at 0x00102B80); value 0x03B0A428 (61908008) */
#define WORD_HEXADECIMAL_30D96C27 0x30D96C27   /* was DAT_00102b84 (word at 0x00102B84); value 0x30D96C27 (819555367) */
#define WORD_HEXADECIMAL_2E8D6E9D 0x2E8D6E9D   /* was DAT_00102b88 (word at 0x00102B88); value 0x2E8D6E9D (781020829) */
#define ADDRESS_OF_FUNCTION_0010888c_OFFSET_2 0x00006088   /* was DAT_00102b8c (word at 0x00102B8C); PC-relative offset: + 0x102804 (the pc) = 0x0010888C */
#define WORD_HEXADECIMAL_000253E4 0x000253E4   /* was DAT_00102b90 (word at 0x00102B90); value 0x000253E4 (152548) */
#define STRING_SAVEGAME_DOT_DAT_OFFSET_2 0x0002539C   /* was DAT_00102b94 (word at 0x00102B94); PC-relative offset: + 0x102958 (the pc) = 0x00127CF4 */
#define WORD_HEXADECIMAL_21C1059D 0x21C1059D   /* was DAT_00102b98 (word at 0x00102B98); value 0x21C1059D (566298013) */
#define STRING_SAVEGAME_DOT_DAT_OFFSET_3 0x00025310   /* was DAT_00102b9c (word at 0x00102B9C); PC-relative offset: + 0x1029e4 (the pc) = 0x00127CF4 */
#define WORD_HEXADECIMAL_00025038 0x00025038   /* was DAT_00102ba0 (word at 0x00102BA0); value 0x00025038 (151608) */
#define DATA_AT_00127B1C_OFFSET 0x00024F60   /* was DAT_00103b5c (word at 0x00103B5C); PC-relative offset: + 0x102bbc (the pc) = 0x00127B1C */
#define STRING_TRAINING_OFFSET_3 0x00024F98   /* was DAT_00103b6c (word at 0x00103B6C); PC-relative offset: + 0x102d78 (the pc) = 0x00127D10 */
#define STRING_SAVEGAME_DOT_DAT_OFFSET_4 0x00024EA4   /* was DAT_00103b70 (word at 0x00103B70); PC-relative offset: + 0x102e50 (the pc) = 0x00127CF4 */
#define DATA_AT_00127B34_OFFSET 0x00024BE0   /* was DAT_00103b74 (word at 0x00103B74); PC-relative offset: + 0x102f54 (the pc) = 0x00127B34 */
#define DATA_AT_00127B50_OFFSET 0x00024BE8   /* was DAT_00103b78 (word at 0x00103B78); PC-relative offset: + 0x102f68 (the pc) = 0x00127B50 */
#define WORD_HEXADECIMAL_2B21E3F9 0x2B21E3F9   /* was DAT_00103b84 (word at 0x00103B84); value 0x2B21E3F9 (723641337) */
#define WORD_HEXADECIMAL_225D20E5 0x225D20E5   /* was DAT_00103b88 (word at 0x00103B88); value 0x225D20E5 (576528613) */
#define DATA_AT_00127B6C_OFFSET 0x0002493C   /* was DAT_00103b8c (word at 0x00103B8C); PC-relative offset: + 0x103230 (the pc) = 0x00127B6C */
#define DATA_AT_00127B88_OFFSET 0x00024944   /* was DAT_00103b90 (word at 0x00103B90); PC-relative offset: + 0x103244 (the pc) = 0x00127B88 */
#define WORD_HEXADECIMAL_0DB81F00 0x0DB81F00   /* was DAT_00103bac (word at 0x00103BAC); value 0x0DB81F00 (230170368) */
#define DATA_AT_00127BA4_OFFSET 0x000246D4   /* was DAT_00103bb0 (word at 0x00103BB0); PC-relative offset: + 0x1034d0 (the pc) = 0x00127BA4 */
#define STRING_COLLECTABLES_OFFSET 0x0002484C   /* was DAT_00103bb4 (word at 0x00103BB4); PC-relative offset: + 0x1034e8 (the pc) = 0x00127D34 */
#define DATA_AT_00127BBC_OFFSET 0x00024664   /* was DAT_00103bb8 (word at 0x00103BB8); PC-relative offset: + 0x103558 (the pc) = 0x00127BBC */
#define WORD_HEXADECIMAL_2E66608C 0x2E66608C   /* was DAT_00103bd8 (word at 0x00103BD8); value 0x2E66608C (778461324) */
#define DATA_AT_00127BD4_OFFSET 0x000242D0   /* was DAT_00103bdc (word at 0x00103BDC); PC-relative offset: + 0x103904 (the pc) = 0x00127BD4 */
#define DATA_AT_00127BE8_OFFSET 0x000242D0   /* was DAT_00103be0 (word at 0x00103BE0); PC-relative offset: + 0x103918 (the pc) = 0x00127BE8 */
#define DATA_AT_00127BFC_OFFSET 0x000242D0   /* was DAT_00103be4 (word at 0x00103BE4); PC-relative offset: + 0x10392c (the pc) = 0x00127BFC */
#define WORD_HEXADECIMAL_2F7413EE 0x2F7413EE   /* was DAT_00103be8 (word at 0x00103BE8); value 0x2F7413EE (796136430) */
#define WORD_HEXADECIMAL_31B444EE 0x31B444EE   /* was DAT_00103bec (word at 0x00103BEC); value 0x31B444EE (833897710) */
#define WORD_HEXADECIMAL_15998E05 0x15998E05   /* was DAT_00103bf0 (word at 0x00103BF0); value 0x15998E05 (362384901) */
#define WORD_HEXADECIMAL_13DD8E16 0x13DD8E16   /* was DAT_00103bf4 (word at 0x00103BF4); value 0x13DD8E16 (333286934) */
#define WORD_HEXADECIMAL_0AFA190E 0x0AFA190E   /* was DAT_00103bf8 (word at 0x00103BF8); value 0x0AFA190E (184162574) */
#define WORD_HEXADECIMAL_2714CFF7 0x2714CFF7   /* was DAT_00103bfc (word at 0x00103BFC); value 0x2714CFF7 (655675383) */
#define WORD_HEXADECIMAL_133529B8 0x133529B8   /* was DAT_00103c00 (word at 0x00103C00); value 0x133529B8 (322251192) */
#define WORD_HEXADECIMAL_FFEFEFEF 0xFFEFEFEF   /* was DAT_00103c04, DAT_001051a0, DAT_001052d0, DAT_00108724, DAT_0010bb20, DAT_0012465c (word at 0x00103C04); value 0xFFEFEFEF (-1052689) */
#define WORD_HEXADECIMAL_02AAF639 0x02AAF639   /* was DAT_00104bc4 (word at 0x00104BC4); value 0x02AAF639 (44758585) */
#define WORD_HEXADECIMAL_1A43CB02 0x1A43CB02   /* was DAT_00104bc8 (word at 0x00104BC8); value 0x1A43CB02 (440650498) */
#define WORD_HEXADECIMAL_00023F3C 0x00023F3C   /* was DAT_00104bcc (word at 0x00104BCC); value 0x00023F3C (147260) */
#define WORD_HEXADECIMAL_00023F38 0x00023F38   /* was DAT_00104bd0 (word at 0x00104BD0); value 0x00023F38 (147256) */
#define WORD_HEXADECIMAL_00023F34 0x00023F34   /* was DAT_00104bd4 (word at 0x00104BD4); value 0x00023F34 (147252) */
#define INTEGER_57393 0x0000E031   /* was DAT_00104bdc, DAT_001054d0, DAT_0011a4d4, DAT_0011aacc (word at 0x00104BDC); integer 57393 */
#define INTEGER_57394 0x0000E032   /* was DAT_00104be0, DAT_001054d4 (word at 0x00104BE0); integer 57394 */
#define WORD_HEXADECIMAL_16A5390B 0x16A5390B   /* was DAT_00104be4, DAT_0010d2f0 (word at 0x00104BE4); value 0x16A5390B (379926795) */
#define INTEGER_MINUS_16076 0xFFFFC134   /* was DAT_00104be8 (word at 0x00104BE8); integer -16076 */
#define STRING_PERCENT_D_OFFSET_4 0x00023DEC   /* was DAT_00104bec (word at 0x00104BEC); PC-relative offset: + 0x103ee0 (the pc) = 0x00127CCC */
#define INTEGER_735 0x000002DF   /* was DAT_00104bf0 (word at 0x00104BF0); integer 735 */
#define WORD_HEXADECIMAL_2A6EBDD0 0x2A6EBDD0   /* was DAT_00104bf4 (word at 0x00104BF4); value 0x2A6EBDD0 (711900624) */
#define WORD_HEXADECIMAL_2CF7E187 0x2CF7E187   /* was DAT_00104bf8 (word at 0x00104BF8); value 0x2CF7E187 (754442631) */
#define WORD_HEXADECIMAL_0955306E 0x0955306E   /* was DAT_00104bfc (word at 0x00104BFC); value 0x0955306E (156577902) */
#define WORD_HEXADECIMAL_2C7A1EE9 0x2C7A1EE9   /* was DAT_00104c00 (word at 0x00104C00); value 0x2C7A1EE9 (746200809) */
#define WORD_HEXADECIMAL_07A0110B 0x07A0110B   /* was DAT_00104c04 (word at 0x00104C04); value 0x07A0110B (127930635) */
#define STRING_PERCENT_D_OFFSET_5 0x00023B40   /* was DAT_00104c10 (word at 0x00104C10); PC-relative offset: + 0x10418c (the pc) = 0x00127CCC */
#define WORD_HEXADECIMAL_1650919F 0x1650919F   /* was DAT_00104c14 (word at 0x00104C14); value 0x1650919F (374378911) */
#define WORD_HEXADECIMAL_3C5A569E 0x3C5A569E   /* was DAT_00104c1c, DAT_0011a498, DAT_0011e240 (word at 0x00104C1C); value 0x3C5A569E (1012553374) */
#define WORD_HEXADECIMAL_21BF9442 0x21BF9442   /* was DAT_00104c20, DAT_00105220, DAT_0010d070, DAT_0010f23c, DAT_0011a49c, DAT_0011e23c, DAT_00123c1c, DAT_00124668 (word at 0x00104C20); value 0x21BF9442 (566203458) */
#define WORD_HEXADECIMAL_111CB9DB 0x111CB9DB   /* was DAT_00104c24 (word at 0x00104C24); value 0x111CB9DB (287095259) */
#define DATA_AT_00127C40_OFFSET 0x0002380C   /* was DAT_00104c28 (word at 0x00104C28); PC-relative offset: + 0x104434 (the pc) = 0x00127C40 */
#define DATA_AT_00127C5C_OFFSET 0x0002369C   /* was DAT_00104c30 (word at 0x00104C30); PC-relative offset: + 0x1045c0 (the pc) = 0x00127C5C */
#define DATA_AT_00127C90_OFFSET 0x000236B8   /* was DAT_00104c34 (word at 0x00104C34); PC-relative offset: + 0x1045d8 (the pc) = 0x00127C90 */
#define WORD_HEXADECIMAL_14FB8F11 0x14FB8F11   /* was DAT_00104c38 (word at 0x00104C38); value 0x14FB8F11 (352030481) */
#define WORD_HEXADECIMAL_27B2CEEB 0x27B2CEEB   /* was DAT_00104c3c (word at 0x00104C3C); value 0x27B2CEEB (666029803) */
#define WORD_HEXADECIMAL_0C211E44 0x0C211E44   /* was DAT_00104c40 (word at 0x00104C40); value 0x0C211E44 (203497028) */
#define WORD_HEXADECIMAL_2F3E5828 0x2F3E5828   /* was DAT_00104c44 (word at 0x00104C44); value 0x2F3E5828 (792614952) */
#define WORD_HEXADECIMAL_37E4CCE1 0x37E4CCE1   /* was DAT_00104c48 (word at 0x00104C48); value 0x37E4CCE1 (937741537) */
#define WORD_HEXADECIMAL_0CB59575 0x0CB59575   /* was DAT_00104c4c (word at 0x00104C4C); value 0x0CB59575 (213226869) */
#define INTEGER_790 0x00000316   /* was DAT_00104c54 (word at 0x00104C54); integer 790 */
#define ADDRESS_OF_FUNCTION_0010888c_OFFSET_3 0x00003C0C   /* was DAT_0010519c (word at 0x0010519C); PC-relative offset: + 0x104c80 (the pc) = 0x0010888C */
#define WORD_HEXADECIMAL_27B19885 0x27B19885   /* was DAT_001051a4 (word at 0x001051A4); value 0x27B19885 (665950341) */
#define STRING_JIMINY_ICON_DOT_PNG_OFFSET 0x00022ED0   /* was DAT_001051a8 (word at 0x001051A8); PC-relative offset: + 0x104e8c (the pc) = 0x00127D5C */
#define WORD_HEXADECIMAL_0AE069A1 0x0AE069A1   /* was DAT_001051ac (word at 0x001051AC); value 0x0AE069A1 (182479265) */
#define STRING_SPLASH_DOT_PNG_OFFSET 0x00022D5C   /* was DAT_001051b0 (word at 0x001051B0); PC-relative offset: + 0x105010 (the pc) = 0x00127D6C */
#define STRING_RO_OFFSET_2 0x00022D1C   /* was DAT_001051b4 (word at 0x001051B4); PC-relative offset: + 0x105030 (the pc) = 0x00127D4C */
#define STRING_PERCENT_S_PERCENT_S_PERCENT_S_OFFSET_2 0x00022D0C   /* was DAT_001051b8 (word at 0x001051B8); PC-relative offset: + 0x105038 (the pc) = 0x00127D44 */
#define STRING_RO_OFFSET_3 0x00022CF4   /* was DAT_001051bc (word at 0x001051BC); PC-relative offset: + 0x105058 (the pc) = 0x00127D4C */
#define STRING_PERCENT_S_PERCENT_S_PERCENT_S_OFFSET_3 0x00022CE4   /* was DAT_001051c0 (word at 0x001051C0); PC-relative offset: + 0x105060 (the pc) = 0x00127D44 */
#define WORD_HEXADECIMAL_1D73D1AE 0x1D73D1AE   /* was DAT_001051c4 (word at 0x001051C4); value 0x1D73D1AE (494129582) */
#define WORD_HEXADECIMAL_14741FD6 0x14741FD6   /* was DAT_001051c8 (word at 0x001051C8); value 0x14741FD6 (343154646) */
#define STRING_OUT_OF_MAGIC_OFFSET 0x00022C08   /* was DAT_001051cc (word at 0x001051CC); PC-relative offset: + 0x105170 (the pc) = 0x00127D78 */
#define STRING_REPLAYGAME_DOT_DAT_OFFSET_2 0x00022B98   /* was DAT_001051d0 (word at 0x001051D0); PC-relative offset: + 0x105184 (the pc) = 0x00127D1C */
#define WORD_HEXADECIMAL_1FEB4DB8 0x1FEB4DB8   /* was DAT_0010521c, DAT_0011e244 (word at 0x0010521C); value 0x1FEB4DB8 (535514552) */
#define WORD_HEXADECIMAL_FF606060 0xFF606060   /* was DAT_001052cc (word at 0x001052CC); value 0xFF606060 (-10461088) */
#define WORD_HEXADECIMAL_FFEBEBF7 0xFFEBEBF7   /* was DAT_001052d4, DAT_001077b4, DAT_0010871c, DAT_0010bb28, DAT_0010be10 (word at 0x001052D4); value 0xFFEBEBF7 (-1315849) */
#define WORD_HEXADECIMAL_FF7E8194 0xFF7E8194   /* was DAT_001052d8, DAT_00106e40, DAT_001077bc (word at 0x001052D8); value 0xFF7E8194 (-8486508) */
#define FLOAT_500 0x43FA0000   /* was DAT_001055c0 (word at 0x001055C0); the float 500.0 */
#define INTEGER_MINUS_22348 0xFFFFA8B4   /* was DAT_00105c0c (word at 0x00105C0C); integer -22348 */
#define DATA_AT_00127D94_OFFSET 0x00022608   /* was DAT_00105c10 (word at 0x00105C10); PC-relative offset: + 0x10578c (the pc) = 0x00127D94 */
#define STRING_INVALIDENTRY_OFFSET 0x0002257C   /* was DAT_00105c24 (word at 0x00105C24); PC-relative offset: + 0x10581c (the pc) = 0x00127D98 */
#define STRING_STAR_D_OFFSET 0x00022518   /* was DAT_00105c30 (word at 0x00105C30); PC-relative offset: + 0x105890 (the pc) = 0x00127DA8 */
#define INTEGER_MINUS_22752 0xFFFFA720   /* was DAT_00105c34 (word at 0x00105C34); integer -22752 */
#define STRING_STAR_T_OFFSET 0x000224C0   /* was DAT_00105c38 (word at 0x00105C38); PC-relative offset: + 0x1058ec (the pc) = 0x00127DAC */
#define DATA_AT_00127D94_OFFSET_2 0x00022380   /* was DAT_00105c40 (word at 0x00105C40); PC-relative offset: + 0x105a14 (the pc) = 0x00127D94 */
#define INTEGER_MINUS_23228 0xFFFFA544   /* was DAT_00105c50 (word at 0x00105C50); integer -23228 */
#define STRING_STAR_R_OFFSET 0x000222E0   /* was DAT_00105c54 (word at 0x00105C54); PC-relative offset: + 0x105ad0 (the pc) = 0x00127DB0 */
#define STRING_INVALIDENTRY_OFFSET_2 0x000222A8   /* was DAT_00105c58 (word at 0x00105C58); PC-relative offset: + 0x105af0 (the pc) = 0x00127D98 */
#define ADDRESS_OF_FUNCTION_001091fc_OFFSET 0x000031F4   /* was DAT_00106128 (word at 0x00106128); PC-relative offset: + 0x106008 (the pc) = 0x001091FC */
#define ADDRESS_OF_FUNCTION_001091fc_OFFSET_2 0x000030F8   /* was DAT_0010612c (word at 0x0010612C); PC-relative offset: + 0x106104 (the pc) = 0x001091FC */
#define AEECLSID_FILEMGR_VALUE 0x01001003   /* was DAT_00106320, DAT_001098d0, DAT_0010fb84, DAT_0011b174, DAT_0011e6b0 (word at 0x00106320); BREW class identifier AEECLSID_FILEMGR */
#define STRING_DOT_DAT_OFFSET 0x00021BB8   /* was DAT_00106328 (word at 0x00106328); PC-relative offset: + 0x106200 (the pc) = 0x00127DB8 */
#define STRING_KH_OFFSET 0x00021B9C   /* was DAT_0010632c (word at 0x0010632C); PC-relative offset: + 0x106218 (the pc) = 0x00127DB4 */
#define DATA_AT_00127D90_OFFSET 0x00021B6C   /* was DAT_00106330 (word at 0x00106330); PC-relative offset: + 0x106224 (the pc) = 0x00127D90 */
#define STRING_DISNEY_SLASH_DOWNLOAD_DOT_PHP_QUESTION_OFFSET 0x00021BC0   /* was DAT_00106334 (word at 0x00106334); PC-relative offset: + 0x106240 (the pc) = 0x00127E00 */
#define STRING_HTTP_COLON_SLASH_SLASH_SWERVENET_DOT_OFFSET 0x00021B94   /* was DAT_00106338 (word at 0x00106338); PC-relative offset: + 0x106248 (the pc) = 0x00127DDC */
#define STRING_PERCENT_S_PERCENT_S_PERCENT_S_OFFSET_4 0x00021B6C   /* was DAT_0010633c (word at 0x0010633C); PC-relative offset: + 0x106254 (the pc) = 0x00127DC0 */
#define STRING_PERCENT_S_AND_S_EQUALS_PERCENT_OFFSET 0x00021B7C   /* was DAT_00106340 (word at 0x00106340); PC-relative offset: + 0x10629c (the pc) = 0x00127E18 */
#define ADDRESS_OF_FUNCTION_001091fc_OFFSET_3 0x00002F44   /* was DAT_00106344 (word at 0x00106344); PC-relative offset: + 0x1062b8 (the pc) = 0x001091FC */
#define ADDRESS_OF_FUNCTION_00105e44_OFFSET 0xFFFFFB6C   /* was DAT_00106348 (word at 0x00106348); PC-relative offset: + 0x1062d8 (the pc) = 0x00105E44 */
#define WORD_HEXADECIMAL_00021B34 0x00021B34   /* was DAT_0010634c (word at 0x0010634C); value 0x00021B34 (138036) */
#define WORD_HEXADECIMAL_00010002 0x00010002   /* was DAT_00106350, DAT_001082dc (word at 0x00106350); value 0x00010002 (65538) */
#define WORD_HEXADECIMAL_FF4757DD 0xFF4757DD   /* was DAT_00106734 (word at 0x00106734); value 0xFF4757DD (-12101667) */
#define DATA_AT_00127A8E_OFFSET 0x00021616   /* was DAT_00106738 (word at 0x00106738); PC-relative offset: + 0x106478 (the pc) = 0x00127A8E */
#define WORD_HEXADECIMAL_FF82ECF3 0xFF82ECF3   /* was DAT_00106a88 (word at 0x00106A88); value 0xFF82ECF3 (-8196877) */
#define INTEGER_MINUS_19441 0xFFFFB40F   /* was DAT_00106a8c (word at 0x00106A8C); integer -19441 */
#define INTEGER_MINUS_15954 0xFFFFC1AE   /* was DAT_00106a90 (word at 0x00106A90); integer -15954 */
#define WORD_HEXADECIMAL_FF615A6D 0xFF615A6D   /* was DAT_00106fa0 (word at 0x00106FA0); value 0xFF615A6D (-10397075) */
#define WORD_HEXADECIMAL_FF9795A5 0xFF9795A5   /* was DAT_00106fa4, DAT_001077b0 (word at 0x00106FA4); value 0xFF9795A5 (-6842971) */
#define DATA_AT_00127D88_OFFSET 0x00020D40   /* was DAT_0010722c (word at 0x0010722C); PC-relative offset: + 0x107048 (the pc) = 0x00127D88 */
#define WORD_HEXADECIMAL_FF2F2533 0xFF2F2533   /* was DAT_001077a8, DAT_00108718 (word at 0x001077A8); value 0xFF2F2533 (-13687501) */
#define WORD_HEXADECIMAL_00FF00FF 0x00FF00FF   /* was DAT_001077ac (word at 0x001077AC); value 0x00FF00FF (16711935) */
#define WORD_HEXADECIMAL_FF47464C 0xFF47464C   /* was DAT_001077c0, DAT_00108714 (word at 0x001077C0); value 0xFF47464C (-12106164) */
#define WORD_HEXADECIMAL_FFFF0000 0xFFFF0000   /* was DAT_001077c4, DAT_00107ad0 (word at 0x001077C4); value 0xFFFF0000 (-65536) */
#define INTEGER_270 0x0000010E   /* was DAT_00107ac4 (word at 0x00107AC4); integer 270 */
#define DATA_AT_00127A7E_OFFSET 0x0002016E   /* was DAT_00107ac8 (word at 0x00107AC8); PC-relative offset: + 0x107910 (the pc) = 0x00127A7E */
#define WORD_HEXADECIMAL_FF7FCB61 0xFF7FCB61   /* was DAT_00107acc (word at 0x00107ACC); value 0xFF7FCB61 (-8402079) */
#define DATA_AT_00127A86_OFFSET 0x0002009E   /* was DAT_00107ad4 (word at 0x00107AD4); PC-relative offset: + 0x1079e8 (the pc) = 0x00127A86 */
#define DATA_AT_00127A7C_OFFSET 0x00020010   /* was DAT_00107ad8 (word at 0x00107AD8); PC-relative offset: + 0x107a6c (the pc) = 0x00127A7C */
#define WORD_HEXADECIMAL_0001FE30 0x0001FE30   /* was DAT_00107d20 (word at 0x00107D20); value 0x0001FE30 (130608) */
#define STRING_PERCENT_D_OFFSET_6 0x0001FDD0   /* was DAT_00107f54 (word at 0x00107F54); PC-relative offset: + 0x107efc (the pc) = 0x00127CCC */
#define STRING_KH_OFFSET_2 0x0001FC34   /* was DAT_001081e0 (word at 0x001081E0); PC-relative offset: + 0x108180 (the pc) = 0x00127DB4 */
#define DATA_AT_00127D90_OFFSET_2 0x0001FBF4   /* was DAT_001081e4 (word at 0x001081E4); PC-relative offset: + 0x10819c (the pc) = 0x00127D90 */
#define STRING_DISNEY_SLASH_RANKEX_DOT_PHP_OFFSET 0x0001FCEC   /* was DAT_001081e8 (word at 0x001081E8); PC-relative offset: + 0x1081b0 (the pc) = 0x00127E9C */
#define STRING_HTTP_COLON_SLASH_SLASH_SWERVENET_DOT_OFFSET_2 0x0001FC24   /* was DAT_001081ec (word at 0x001081EC); PC-relative offset: + 0x1081b8 (the pc) = 0x00127DDC */
#define STRING_PERCENT_S_PERCENT_S_QUESTION_MARK_OFFSET 0x0001FCB0   /* was DAT_001081f0 (word at 0x001081F0); PC-relative offset: + 0x1081c0 (the pc) = 0x00127E70 */
#define ADDRESS_OF_FUNCTION_001091fc_OFFSET_4 0x00000FB4   /* was DAT_001082d0 (word at 0x001082D0); PC-relative offset: + 0x108248 (the pc) = 0x001091FC */
#define ADDRESS_OF_FUNCTION_00105e44_OFFSET_2 0xFFFFDBDC   /* was DAT_001082d4 (word at 0x001082D4); PC-relative offset: + 0x108268 (the pc) = 0x00105E44 */
#define STRING_X_DASH_METHOD_COLON_GET_CARRIAGE_OFFSET 0x0001FB80   /* was DAT_001082d8 (word at 0x001082D8); PC-relative offset: + 0x1082a0 (the pc) = 0x00127E20 */
#define DATA_AT_00127D90_OFFSET_3 0x0001FA40   /* was DAT_001083c4 (word at 0x001083C4); PC-relative offset: + 0x108350 (the pc) = 0x00127D90 */
#define STRING_KH_OFFSET_3 0x0001FA48   /* was DAT_001083c8 (word at 0x001083C8); PC-relative offset: + 0x10836c (the pc) = 0x00127DB4 */
#define STRING_DISNEY_SLASH_RANK_DOT_PHP_OFFSET 0x0001FACC   /* was DAT_001083cc (word at 0x001083CC); PC-relative offset: + 0x108394 (the pc) = 0x00127E60 */
#define STRING_HTTP_COLON_SLASH_SLASH_SWERVENET_DOT_OFFSET_3 0x0001FA40   /* was DAT_001083d0 (word at 0x001083D0); PC-relative offset: + 0x10839c (the pc) = 0x00127DDC */
#define STRING_PERCENT_S_PERCENT_S_QUESTION_MARK_OFFSET_2 0x0001FA8C   /* was DAT_001083d4 (word at 0x001083D4); PC-relative offset: + 0x1083a4 (the pc) = 0x00127E30 */
#define WORD_HEXADECIMAL_FFC0C000 0xFFC0C000   /* was DAT_00108720 (word at 0x00108720); value 0xFFC0C000 (-4145152) */
#define INTEGER_57397 0x0000E035   /* was DAT_0010883c (word at 0x0010883C); integer 57397 */
#define WORD_HEXADECIMAL_1AB5DBD0 0x1AB5DBD0   /* was DAT_00108e58 (word at 0x00108E58); value 0x1AB5DBD0 (448125904) */
#define INTEGER_MINUS_35012 0xFFFF773C   /* was DAT_00108e5c (word at 0x00108E5C); integer -35012 */
#define WORD_HEXADECIMAL_0FA4E52C 0x0FA4E52C   /* was DAT_00108e60 (word at 0x00108E60); value 0x0FA4E52C (262464812) */
#define WORD_HEXADECIMAL_3D569D08 0x3D569D08   /* was DAT_00108e68 (word at 0x00108E68); value 0x3D569D08 (1029086472) */
#define WORD_HEXADECIMAL_0001F14C 0x0001F14C   /* was DAT_00108e6c (word at 0x00108E6C); value 0x0001F14C (127308) */
#define STRING_ISLAND_OFFSET 0x0001F130   /* was DAT_00108e70 (word at 0x00108E70); PC-relative offset: + 0x108bbc (the pc) = 0x00127CEC */
#define STRING_WONDERLAND_OFFSET 0x0001F110   /* was DAT_00108e74 (word at 0x00108E74); PC-relative offset: + 0x108bd0 (the pc) = 0x00127CE0 */
#define STRING_AGRABAH_OFFSET 0x0001F0F4   /* was DAT_00108e78 (word at 0x00108E78); PC-relative offset: + 0x108be4 (the pc) = 0x00127CD8 */
#define STRING_CASTLE_OFFSET 0x0001F0D8   /* was DAT_00108e7c (word at 0x00108E7C); PC-relative offset: + 0x108bf8 (the pc) = 0x00127CD0 */
#define WORD_HEXADECIMAL_3D198889 0x3D198889   /* was DAT_00108e84 (word at 0x00108E84); value 0x3D198889 (1025083529) */
#define STRING_PERCENT_S_PERCENT_D_SLASH_PERCENT_OFFSET 0x0001EF54   /* was DAT_00108e88 (word at 0x00108E88); PC-relative offset: + 0x108db0 (the pc) = 0x00127D04 */
#define INTEGER_MINUS_55555 0xFFFF26FD   /* was DAT_001091f8 (word at 0x001091F8); integer -55555 */
#define DATA_AT_00127D90_OFFSET_4 0x0001E964   /* was DAT_0010952c (word at 0x0010952C); PC-relative offset: + 0x10942c (the pc) = 0x00127D90 */
#define DATA_AT_00127D90_OFFSET_5 0x0001E928   /* was DAT_00109530 (word at 0x00109530); PC-relative offset: + 0x109468 (the pc) = 0x00127D90 */
#define INTEGER_10000 0x00002710   /* was DAT_00109ef4 (word at 0x00109EF4); integer 10000 */
#define ADDRESS_OF_FUNCTION_001242b4_OFFSET 0x0001A214   /* was DAT_0010a0cc (word at 0x0010A0CC); PC-relative offset: + 0x10a0a0 (the pc) = 0x001242B4 */
#define WORD_HEXADECIMAL_3D1D22E8 0x3D1D22E8   /* was DAT_0010a3e4 (word at 0x0010A3E4); value 0x3D1D22E8 (1025319656) */
#define INTEGER_57396 0x0000E034   /* was DAT_0010a524 (word at 0x0010A524); integer 57396 */
#define DATA_AT_00101650_OFFSET 0xFFFF70F4   /* was DAT_0010a5c8 (word at 0x0010A5C8); PC-relative offset: + 0x10a55c (the pc) = 0x00101650 */
#define FLOAT_3 0x40400000   /* was DAT_0010a5cc, DAT_00110554, DAT_00121aac, DAT_00124078 (word at 0x0010A5CC); the float 3.0 */
#define FLOAT_0_POINT_3 0x3E99999A   /* was DAT_0010a5d0, DAT_00117d0c (word at 0x0010A5D0); the float 0.30000001192092896 */
#define INTEGER_MINUS_42416 0xFFFF5A50   /* was DAT_0010a5d4 (word at 0x0010A5D4); integer -42416 */
#define STRING_BASE_DOT_M3G_OFFSET 0x0001D144   /* was DAT_0010aa30 (word at 0x0010AA30); PC-relative offset: + 0x10a68c (the pc) = 0x001277D0 */
#define WORD_HEXADECIMAL_1922F406 0x1922F406   /* was DAT_0010aa34 (word at 0x0010AA34); value 0x1922F406 (421721094) */
#define STRING_CHARACTER_GRP_OFFSET 0x0001D0F0   /* was DAT_0010aa38 (word at 0x0010AA38); PC-relative offset: + 0x10a6ec (the pc) = 0x001277DC */
#define STRING_GENERAL_SCRIPTS_OFFSET 0x0001D0D4   /* was DAT_0010aa3c (word at 0x0010AA3C); PC-relative offset: + 0x10a718 (the pc) = 0x001277EC */
#define WORD_HEXADECIMAL_038AD7F2 0x038AD7F2   /* was DAT_0010aa40 (word at 0x0010AA40); value 0x038AD7F2 (59430898) */
#define STRING_CAMERA_OFFSET 0x0001D0A0   /* was DAT_0010aa44 (word at 0x0010AA44); PC-relative offset: + 0x10a75c (the pc) = 0x001277FC */
#define WORD_HEXADECIMAL_334C8936 0x334C8936   /* was DAT_0010aa48 (word at 0x0010AA48); value 0x334C8936 (860653878) */
#define WORD_HEXADECIMAL_0AD65F3D 0x0AD65F3D   /* was DAT_0010aa4c (word at 0x0010AA4C); value 0x0AD65F3D (181821245) */
#define STRING_CHARACTER_OFFSET 0x0001D008   /* was DAT_0010aa50 (word at 0x0010AA50); PC-relative offset: + 0x10a7fc (the pc) = 0x00127804 */
#define INTEGER_501 0x000001F5   /* was DAT_0010aa54 (word at 0x0010AA54); integer 501 */
#define STRING_SORA_JUMP_DOT_QCP_OFFSET 0x0001D000   /* was DAT_0010aa58 (word at 0x0010AA58); PC-relative offset: + 0x10a8b8 (the pc) = 0x001278B8 */
#define STRING_SORA_HIT_DOT_QCP_OFFSET 0x0001CFD8   /* was DAT_0010aa5c (word at 0x0010AA5C); PC-relative offset: + 0x10a8d0 (the pc) = 0x001278A8 */
#define STRING_ENEMY_HIT_DOT_QCP_OFFSET 0x0001CFB0   /* was DAT_0010aa60 (word at 0x0010AA60); PC-relative offset: + 0x10a8e8 (the pc) = 0x00127898 */
#define STRING_SORA_SWIPE_DOT_QCP_OFFSET 0x0001CF88   /* was DAT_0010aa64 (word at 0x0010AA64); PC-relative offset: + 0x10a900 (the pc) = 0x00127888 */
#define STRING_BAD_DOT_MID_OFFSET 0x0001CF68   /* was DAT_0010aa68 (word at 0x0010AA68); PC-relative offset: + 0x10a918 (the pc) = 0x00127880 */
#define STRING_GOOD_DOT_MID_OFFSET 0x0001CF44   /* was DAT_0010aa6c (word at 0x0010AA6C); PC-relative offset: + 0x10a930 (the pc) = 0x00127874 */
#define STRING_KEYBLADE_DOT_MID_OFFSET 0x0001CF1C   /* was DAT_0010aa70 (word at 0x0010AA70); PC-relative offset: + 0x10a948 (the pc) = 0x00127864 */
#define STRING_EXPLODE_DOT_QCP_OFFSET 0x0001CEF8   /* was DAT_0010aa74 (word at 0x0010AA74); PC-relative offset: + 0x10a960 (the pc) = 0x00127858 */
#define STRING_WATER_DOT_QCP_OFFSET 0x0001CED4   /* was DAT_0010aa78 (word at 0x0010AA78); PC-relative offset: + 0x10a978 (the pc) = 0x0012784C */
#define STRING_THUD_DOT_QCP_OFFSET 0x0001CEB0   /* was DAT_0010aa7c (word at 0x0010AA7C); PC-relative offset: + 0x10a990 (the pc) = 0x00127840 */
#define STRING_TRANSITION_DOT_QCP_OFFSET 0x0001CE88   /* was DAT_0010aa80 (word at 0x0010AA80); PC-relative offset: + 0x10a9a8 (the pc) = 0x00127830 */
#define STRING_MAGIC_ALERT_DOT_MID_OFFSET 0x0001CE60   /* was DAT_0010aa84 (word at 0x0010AA84); PC-relative offset: + 0x10a9c0 (the pc) = 0x00127820 */
#define STRING_MAGIC_CAST_DOT_QCP_OFFSET 0x0001CE38   /* was DAT_0010aa88 (word at 0x0010AA88); PC-relative offset: + 0x10a9d8 (the pc) = 0x00127810 */
#define DATA_AT_0010165C_OFFSET 0xFFFF6B84   /* was DAT_0010ac50 (word at 0x0010AC50); PC-relative offset: + 0x10aad8 (the pc) = 0x0010165C */
#define INTEGER_5001 0x00001389   /* was DAT_0010ac58, DAT_0010faa4 (word at 0x0010AC58); integer 5001 */
#define STRING_KH_DOT_BAR_OFFSET 0x0001CF24   /* was DAT_0010ac5c (word at 0x0010AC5C); PC-relative offset: + 0x10ab74 (the pc) = 0x00127A98 */
#define INTEGER_5002 0x0000138A   /* was DAT_0010ac60, DAT_0010faa0 (word at 0x0010AC60); integer 5002 */
#define STRING_KH_DOT_BAR_OFFSET_2 0x0001CEFC   /* was DAT_0010ac64 (word at 0x0010AC64); PC-relative offset: + 0x10ab9c (the pc) = 0x00127A98 */
#define WORD_HEXADECIMAL_254DA109 0x254DA109   /* was DAT_0010ac68 (word at 0x0010AC68); value 0x254DA109 (625844489) */
#define AEECLSID_GRAPHICS_VALUE 0x01002001   /* was DAT_0010aefc (word at 0x0010AEFC); BREW class identifier AEECLSID_GRAPHICS */
#define INTEGER_MINUS_44296 0xFFFF52F8   /* was DAT_0010af00 (word at 0x0010AF00); integer -44296 */
#define DATA_AT_00127AA0_OFFSET 0x0001CD00   /* was DAT_0010af04 (word at 0x0010AF04); PC-relative offset: + 0x10ada0 (the pc) = 0x00127AA0 */
#define WORD_HEXADECIMAL_0001CD1C 0x0001CD1C   /* was DAT_0010af08 (word at 0x0010AF08); value 0x0001CD1C (118044) */
#define INTEGER_5003 0x0000138B   /* was DAT_0010af0c (word at 0x0010AF0C); integer 5003 */
#define STRING_KH_DOT_BAR_OFFSET_3 0x0001CE9C   /* was DAT_0010af10 (word at 0x0010AF10); PC-relative offset: + 0x10ae28 (the pc) = 0x00127CC4 */
#define INTEGER_5004 0x0000138C   /* was DAT_0010af14 (word at 0x0010AF14); integer 5004 */
#define STRING_KH_DOT_BAR_OFFSET_4 0x0001CE74   /* was DAT_0010af18 (word at 0x0010AF18); PC-relative offset: + 0x10ae50 (the pc) = 0x00127CC4 */
#define INTEGER_5005 0x0000138D   /* was DAT_0010af1c (word at 0x0010AF1C); integer 5005 */
#define STRING_KH_DOT_BAR_OFFSET_5 0x0001CE4C   /* was DAT_0010af20 (word at 0x0010AF20); PC-relative offset: + 0x10ae78 (the pc) = 0x00127CC4 */
#define INTEGER_5006 0x0000138E   /* was DAT_0010af24 (word at 0x0010AF24); integer 5006 */
#define STRING_KH_DOT_BAR_OFFSET_6 0x0001CE24   /* was DAT_0010af28 (word at 0x0010AF28); PC-relative offset: + 0x10aea0 (the pc) = 0x00127CC4 */
#define INTEGER_5007 0x0000138F   /* was DAT_0010af2c (word at 0x0010AF2C); integer 5007 */
#define STRING_KH_DOT_BAR_OFFSET_7 0x0001CDFC   /* was DAT_0010af30 (word at 0x0010AF30); PC-relative offset: + 0x10aec8 (the pc) = 0x00127CC4 */
#define INTEGER_5008 0x00001390   /* was DAT_0010af34 (word at 0x0010AF34); integer 5008 */
#define STRING_KH_DOT_BAR_OFFSET_8 0x0001CDD4   /* was DAT_0010af38 (word at 0x0010AF38); PC-relative offset: + 0x10aef0 (the pc) = 0x00127CC4 */
#define AEECLSID_WEB_VALUE 0x01005000   /* was DAT_0010afc0 (word at 0x0010AFC0); BREW class identifier AEECLSID_WEB */
#define STRING_CARRIAGE_RETURN_NEWLINE_OFFSET 0x0001C694   /* was DAT_0010b224 (word at 0x0010B224); PC-relative offset: + 0x10b0ec (the pc) = 0x00127780 */
#define STRING_CARRIAGE_RETURN_NEWLINE_OFFSET_2 0x0001C65C   /* was DAT_0010b228 (word at 0x0010B228); PC-relative offset: + 0x10b124 (the pc) = 0x00127780 */
#define DATA_AT_00127784_OFFSET 0x0001C62C   /* was DAT_0010b22c (word at 0x0010B22C); PC-relative offset: + 0x10b158 (the pc) = 0x00127784 */
#define DATA_AT_00101680_OFFSET 0xFFFF641C   /* was DAT_0010b2d0 (word at 0x0010B2D0); PC-relative offset: + 0x10b264 (the pc) = 0x00101680 */
#define INTEGER_1001 0x000003E9   /* was DAT_0010b2d4, DAT_00122b84 (word at 0x0010B2D4); integer 1001 */
#define INTEGER_MINUS_45732 0xFFFF4D5C   /* was DAT_0010b2d8 (word at 0x0010B2D8); integer -45732 */
#define DATA_AT_001016A0_OFFSET 0xFFFF6364   /* was DAT_0010b3e0 (word at 0x0010B3E0); PC-relative offset: + 0x10b33c (the pc) = 0x001016A0 */
#define INTEGER_5000 0x00001388   /* was DAT_0010b3e4, DAT_0011a800, DAT_0011c324, DAT_0011fc78, DAT_0012243c (word at 0x0010B3E4); integer 5000 */
#define FLOAT_90 0x42B40000   /* was DAT_0010b470, DAT_0010e444, DAT_0011411c, DAT_001169c4, DAT_0011adb4, DAT_001202f0, DAT_00121c5c, DAT_00122f94 (word at 0x0010B470); the float 90.0 */
#define FLOAT_10 0x41200000   /* was DAT_0010b474, DAT_0010db00, DAT_0010df5c, DAT_001118a8, DAT_00122f88 (word at 0x0010B474); the float 10.0 */
#define INTEGER_1836 0x0000072C   /* was DAT_0010b5dc (word at 0x0010B5DC); integer 1836 */
#define STRING_SETTINGS_DOT_DAT_OFFSET 0x0001C310   /* was DAT_0010b5e4 (word at 0x0010B5E4); PC-relative offset: + 0x10b5c8 (the pc) = 0x001278D8 */
#define DATA_AT_001016C0_OFFSET 0xFFFF6014   /* was DAT_0010b708 (word at 0x0010B708); PC-relative offset: + 0x10b6ac (the pc) = 0x001016C0 */
#define INTEGER_1820 0x0000071C   /* was DAT_0010b868 (word at 0x0010B868); integer 1820 */
#define WORD_HEXADECIMAL_FFC5FAB9 0xFFC5FAB9   /* was DAT_0010bafc (word at 0x0010BAFC); value 0xFFC5FAB9 (-3802439) */
#define WORD_HEXADECIMAL_FF004C78 0xFF004C78   /* was DAT_0010bb00 (word at 0x0010BB00); value 0xFF004C78 (-16757640) */
#define WORD_HEXADECIMAL_FF0253A8 0xFF0253A8   /* was DAT_0010bb04 (word at 0x0010BB04); value 0xFF0253A8 (-16624728) */
#define INTEGER_MINUS_28807 0xFFFF8F79   /* was DAT_0010bb08 (word at 0x0010BB08); integer -28807 */
#define WORD_HEXADECIMAL_FF2C0621 0xFF2C0621   /* was DAT_0010bb0c (word at 0x0010BB0C); value 0xFF2C0621 (-13892063) */
#define WORD_HEXADECIMAL_FF8D2B15 0xFF8D2B15   /* was DAT_0010bb10 (word at 0x0010BB10); value 0xFF8D2B15 (-7525611) */
#define INTEGER_MINUS_6560 0xFFFFE660   /* was DAT_0010bb14 (word at 0x0010BB14); integer -6560 */
#define WORD_HEXADECIMAL_FF724307 0xFF724307   /* was DAT_0010bb18 (word at 0x0010BB18); value 0xFF724307 (-9288953) */
#define WORD_HEXADECIMAL_FF8A4E00 0xFF8A4E00   /* was DAT_0010bb1c (word at 0x0010BB1C); value 0xFF8A4E00 (-7713280) */
#define WORD_HEXADECIMAL_FFEFEFC0 0xFFEFEFC0   /* was DAT_0010bb24 (word at 0x0010BB24); value 0xFFEFEFC0 (-1052736) */
#define DATA_AT_001016E0_OFFSET 0xFFFF5AD0   /* was DAT_0010bd70 (word at 0x0010BD70); PC-relative offset: + 0x10bc10 (the pc) = 0x001016E0 */
#define CLASS_IDENTIFIER_HEXADECIMAL_01003009 0x01003009   /* was DAT_0010bd74 (word at 0x0010BD74); in the BREW class identifier range */
#define INTEGER_57360 0x0000E010   /* was DAT_0010bd78 (word at 0x0010BD78); integer 57360 */
#define DATA_AT_00101700_OFFSET 0xFFFF5934   /* was DAT_0010be0c (word at 0x0010BE0C); PC-relative offset: + 0x10bdcc (the pc) = 0x00101700 */
#define STRING_LANGUAGE_DOT_M3G_OFFSET 0x0001BB78   /* was DAT_0010be68 (word at 0x0010BE68); PC-relative offset: + 0x10be58 (the pc) = 0x001279D0 */
#define INTEGER_MINUS_48896 0xFFFF4100   /* was DAT_0010c144 (word at 0x0010C144); integer -48896 */
#define INTEGER_MINUS_49004 0xFFFF4094   /* was DAT_0010c148 (word at 0x0010C148); integer -49004 */
#define STRING_MP3_OFFSET 0x0001BF18   /* was DAT_0010c14c (word at 0x0010C14C); PC-relative offset: + 0x10bf98 (the pc) = 0x00127EB0 */
#define AEECLSID_MEDIAMP3_VALUE 0x01005502   /* was DAT_0010c150 (word at 0x0010C150); BREW class identifier AEECLSID_MEDIAMP3 */
#define STRING_MID_OFFSET 0x0001BEF8   /* was DAT_0010c154 (word at 0x0010C154); PC-relative offset: + 0x10bfbc (the pc) = 0x00127EB4 */
#define AEECLSID_MEDIAMIDI_VALUE 0x01005501   /* was DAT_0010c158 (word at 0x0010C158); BREW class identifier AEECLSID_MEDIAMIDI */
#define STRING_QCP_OFFSET 0x0001BED8   /* was DAT_0010c15c (word at 0x0010C15C); PC-relative offset: + 0x10bfe0 (the pc) = 0x00127EB8 */
#define STRING_PMD_OFFSET 0x0001BE80   /* was DAT_0010c160 (word at 0x0010C160); PC-relative offset: + 0x10c03c (the pc) = 0x00127EBC */
#define AEECLSID_MEDIAPMD_VALUE 0x01005504   /* was DAT_0010c164 (word at 0x0010C164); BREW class identifier AEECLSID_MEDIAPMD */
#define DATA_AT_00101724_OFFSET 0xFFFF5580   /* was DAT_0010c214 (word at 0x0010C214); PC-relative offset: + 0x10c1a4 (the pc) = 0x00101724 */
#define DATA_AT_00101650_OFFSET_2 0xFFFF539C   /* was DAT_0010c2c0 (word at 0x0010C2C0); PC-relative offset: + 0x10c2b4 (the pc) = 0x00101650 */
#define ADDRESS_OF_FUNCTION_001091fc_OFFSET_5 0xFFFFCC28   /* was DAT_0010c61c (word at 0x0010C61C); PC-relative offset: + 0x10c5d4 (the pc) = 0x001091FC */
#define DATA_AT_00101680_OFFSET_2 0xFFFF4F54   /* was DAT_0010c738 (word at 0x0010C738); PC-relative offset: + 0x10c72c (the pc) = 0x00101680 */
#define WORD_HEXADECIMAL_150C956D 0x150C956D   /* was DAT_0010d064 (word at 0x0010D064); value 0x150C956D (353146221) */
#define WORD_HEXADECIMAL_0B96B9C5 0x0B96B9C5   /* was DAT_0010d068 (word at 0x0010D068); value 0x0B96B9C5 (194427333) */
#define WORD_HEXADECIMAL_2CB8343A 0x2CB8343A   /* was DAT_0010d06c (word at 0x0010D06C); value 0x2CB8343A (750269498) */
extern undefined4 STRING_OUT_OF_MAGIC_SELF_RELATIVE_OFFSET;   /* was DAT_0010d1dc (word at 0x0010D1DC = 0x0001A718); word relative to its own address: 0x0010D1DC + 0x0001A718 = 0x001278F4 */
#define INTEGER_MINUS_53860 0xFFFF2D9C   /* was DAT_0010d2f4 (word at 0x0010D2F4); integer -53860 */
#define STRING_PERCENT_S_EQUALS_PERCENT_D_OFFSET 0x0001A68C   /* was DAT_0010d2f8 (word at 0x0010D2F8); PC-relative offset: + 0x10d278 (the pc) = 0x00127904 */
#define INTEGER_MINUS_54208 0xFFFF2C40   /* was DAT_0010d4cc (word at 0x0010D4CC); integer -54208 */
#define STRING_THE_APPLICATION_HAS_FAILED_OFFSET 0x0001A660   /* was DAT_0010d4d0 (word at 0x0010D4D0); PC-relative offset: + 0x10d3cc (the pc) = 0x00127A2C */
#define STRING_AND_WILL_CLOSE_ERROR_PERCENT_X_OFFSET 0x0001A628   /* was DAT_0010d4d4 (word at 0x0010D4D4); PC-relative offset: + 0x10d3e8 (the pc) = 0x00127A10 */
#define STRING_PRESS_ANY_KEY_TO_CONTINUE_OFFSET 0x0001A5F4   /* was DAT_0010d4d8 (word at 0x0010D4D8); PC-relative offset: + 0x10d400 (the pc) = 0x001279F4 */
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
#define STRING_OUT_OF_MAGIC_OFFSET_2 0x00018FC8   /* was DAT_0010e05c (word at 0x0010E05C); PC-relative offset: + 0x10dff4 (the pc) = 0x00126FBC */
#define FLOAT_1_POINT_1 0x3F8CCCCD   /* was DAT_0010e440 (word at 0x0010E440); the float 1.100000023841858 */
#define FLOAT_5 0x40A00000   /* was DAT_0010e834, DAT_0010f8e4, DAT_0010ffc8, DAT_00110560, DAT_00113298, DAT_001180b8, DAT_0011cfd8 (word at 0x0010E834); the float 5.0 */
#define WORD_HEXADECIMAL_3C8EFA39 0x3C8EFA39   /* was DAT_0010ed3c, DAT_0011e52c, DAT_00122f8c (word at 0x0010ED3C); value 0x3C8EFA39 (1016003129) */
#define STRING_CARRIAGE_RETURN_NEWLINE_OFFSET_3 0x00018FE0   /* was DAT_0010efcc (word at 0x0010EFCC); PC-relative offset: + 0x10ef28 (the pc) = 0x00127F08 */
#define STRING_CARRIAGE_RETURN_NEWLINE_OFFSET_4 0x00018FB0   /* was DAT_0010efd0 (word at 0x0010EFD0); PC-relative offset: + 0x10ef58 (the pc) = 0x00127F08 */
#define WORD_HEXADECIMAL_0493FC17 0x0493FC17   /* was DAT_0010f240 (word at 0x0010F240); value 0x0493FC17 (76807191) */
#define INTEGER_2004 0x000007D4   /* was DAT_0010f4c8 (word at 0x0010F4C8); integer 2004 */
#define INTEGER_2007 0x000007D7   /* was DAT_0010f4cc, DAT_0011d6bc (word at 0x0010F4CC); integer 2007 */
#define WORD_HEXADECIMAL_397714A4 0x397714A4   /* was DAT_0012244c (word at 0x0010F878); value 0x397714A4 (964105380) */
#define WORD_HEXADECIMAL_0B7E4D24 0x0B7E4D24   /* was DAT_0010f87c (word at 0x0010F87C); value 0x0B7E4D24 (192826660) */
#define INTEGER_57379 0x0000E023   /* was DAT_0010f988 (word at 0x0010F988); integer 57379 */
#define INTEGER_57381 0x0000E025   /* was DAT_0010f98c (word at 0x0010F98C); integer 57381 */
#define INTEGER_57382 0x0000E026   /* was DAT_0010f990 (word at 0x0010F990); integer 57382 */
#define INTEGER_57387 0x0000E02B   /* was DAT_0010f994 (word at 0x0010F994); integer 57387 */
#define WORD_HEXADECIMAL_052F918F 0x052F918F   /* was DAT_0010f998 (word at 0x0010F998); value 0x052F918F (87003535) */
#define INTEGER_57398 0x0000E036   /* was DAT_0010f99c (word at 0x0010F99C); integer 57398 */
#define DATA_AT_00127F78_OFFSET 0x00018484   /* was DAT_0010fb88 (word at 0x0010FB88); PC-relative offset: + 0x10faf4 (the pc) = 0x00127F78 */
#define FLOAT_0_POINT_1 0x3DCCCCCD   /* was DAT_0010fbf0, DAT_00110550, DAT_0011302c, DAT_0011da94 (word at 0x0010FBF0); the float 0.10000000149011612 */
#define FLOAT_5000 0x459C4000   /* was DAT_0010ffc4 (word at 0x0010FFC4); the float 5000.0 */
#define FLOAT_0_POINT_001 0x3A83126F   /* was DAT_0010ffcc, DAT_00110558, DAT_00113028, DAT_0011329c (word at 0x0010FFCC); the float 0.0010000000474974513 */
#define FLOAT_MINUS_1 0xBF800000   /* was DAT_0010ffd0, DAT_0011055c, DAT_00111854, DAT_001132a0, DAT_0011333c, DAT_00113464, DAT_00113cc0, DAT_00117d2c, DAT_00119594, DAT_0011c32c, DAT_0011dc94, DAT_0011f620, DAT_0011fd88, DAT_00122440, DAT_00124074 (word at 0x0010FFD0); the float -1.0 */
#define FLOAT_0_POINT_4 0x3ECCCCCD   /* was DAT_0010ffd4 (word at 0x0010FFD4); the float 0.4000000059604645 */
#define WORD_HEXADECIMAL_FFFEFEE0 0xFFFEFEE0   /* was DAT_00110188 (word at 0x00110188); value 0xFFFEFEE0 (-65824) */
#define FLOAT_MINUS_5 0xC0A00000   /* was DAT_00110698, DAT_001169e4 (word at 0x00110698); the float -5.0 */
#define FLOAT_7_POINT_5 0x40F00000   /* was DAT_0011069c (word at 0x0011069C); the float 7.5 */
#define WORD_HEXADECIMAL_FFFEF6C4 0xFFFEF6C4   /* was DAT_001117b0 (word at 0x001117B0); value 0xFFFEF6C4 (-67900) */
#define STRING_SAVE_OFFSET 0x00016B38   /* was DAT_001117b4 (word at 0x001117B4); PC-relative offset: + 0x110ae4 (the pc) = 0x0012761C */
#define STRING_SHOP_OFFSET 0x00016B18   /* was DAT_001117bc (word at 0x001117BC); PC-relative offset: + 0x110b0c (the pc) = 0x00127624 */
#define STRING_OPTIONS_OFFSET 0x00016AF8   /* was DAT_001117c4 (word at 0x001117C4); PC-relative offset: + 0x110b34 (the pc) = 0x0012762C */
#define STRING_MAIN_MENU_OFFSET 0x00016AD4   /* was DAT_001117cc (word at 0x001117CC); PC-relative offset: + 0x110b60 (the pc) = 0x00127634 */
#define STRING_RESTART_GAME_OFFSET 0x00016AB8   /* was DAT_001117d4 (word at 0x001117D4); PC-relative offset: + 0x110b88 (the pc) = 0x00127640 */
#define STRING_UNPAUSE_OFFSET 0x00016A9C   /* was DAT_001117dc (word at 0x001117DC); PC-relative offset: + 0x110bb4 (the pc) = 0x00127650 */
#define STRING_ACTIVATE_OFFSET 0x00016A5C   /* was DAT_001117e0 (word at 0x001117E0); PC-relative offset: + 0x110bfc (the pc) = 0x00127658 */
#define WORD_HEXADECIMAL_2ACA7E67 0x2ACA7E67   /* was DAT_001117e4 (word at 0x001117E4); value 0x2ACA7E67 (717913703) */
#define STRING_ATTACK_OFFSET 0x0001674C   /* was DAT_001117e8 (word at 0x001117E8); PC-relative offset: + 0x110c20 (the pc) = 0x0012736C */
#define WORD_HEXADECIMAL_22837D60 0x22837D60   /* was DAT_001117ec (word at 0x001117EC); value 0x22837D60 (579042656) */
#define STRING_DROP_OFFSET 0x00016788   /* was DAT_001117f0 (word at 0x001117F0); PC-relative offset: + 0x110c44 (the pc) = 0x001273CC */
#define WORD_HEXADECIMAL_29F2A761 0x29F2A761   /* was DAT_001117f4 (word at 0x001117F4); value 0x29F2A761 (703768417) */
#define STRING_GRAB_OFFSET 0x000169FC   /* was DAT_001117f8 (word at 0x001117F8); PC-relative offset: + 0x110c68 (the pc) = 0x00127664 */
#define WORD_HEXADECIMAL_0C0AB7A6 0x0C0AB7A6   /* was DAT_001117fc (word at 0x001117FC); value 0x0C0AB7A6 (202028966) */
#define STRING_LIFT_OFFSET 0x00016738   /* was DAT_00111800 (word at 0x00111800); PC-relative offset: + 0x110c8c (the pc) = 0x001273C4 */
#define WORD_HEXADECIMAL_30BF44AD 0x30BF44AD   /* was DAT_00111804 (word at 0x00111804); value 0x30BF44AD (817841325) */
#define STRING_LOCK_OFFSET 0x000169BC   /* was DAT_00111808 (word at 0x00111808); PC-relative offset: + 0x110cb0 (the pc) = 0x0012766C */
#define WORD_HEXADECIMAL_1B18B1A5 0x1B18B1A5   /* was DAT_0011180c (word at 0x0011180C); value 0x1B18B1A5 (454603173) */
#define STRING_OPEN_OFFSET 0x000169A0   /* was DAT_00111810 (word at 0x00111810); PC-relative offset: + 0x110cd4 (the pc) = 0x00127674 */
#define WORD_HEXADECIMAL_0B0EC760 0x0B0EC760   /* was DAT_00111814 (word at 0x00111814); value 0x0B0EC760 (185517920) */
#define STRING_TALK_OFFSET 0x00016984   /* was DAT_00111818 (word at 0x00111818); PC-relative offset: + 0x110cf8 (the pc) = 0x0012767C */
#define WORD_HEXADECIMAL_18413CCA 0x18413CCA   /* was DAT_0011181c (word at 0x0011181C); value 0x18413CCA (406928586) */
#define STRING_PLACE_OFFSET 0x00016968   /* was DAT_00111820 (word at 0x00111820); PC-relative offset: + 0x110d1c (the pc) = 0x00127684 */
#define WORD_HEXADECIMAL_1BF8C522 0x1BF8C522   /* was DAT_00111824 (word at 0x00111824); value 0x1BF8C522 (469288226) */
#define STRING_HEALTH_OFFSET 0x000167E8   /* was DAT_00111828 (word at 0x00111828); PC-relative offset: + 0x110ea4 (the pc) = 0x0012768C */
#define STRING_MAGIC_OFFSET 0x000167C0   /* was DAT_0011182c (word at 0x0011182C); PC-relative offset: + 0x110ed4 (the pc) = 0x00127694 */
#define STRING_MUNNY_OFFSET 0x00016798   /* was DAT_00111830 (word at 0x00111830); PC-relative offset: + 0x110f04 (the pc) = 0x0012769C */
#define STRING_EXP_OFFSET 0x00016770   /* was DAT_00111834 (word at 0x00111834); PC-relative offset: + 0x110f34 (the pc) = 0x001276A4 */
#define STRING_POTION_OFFSET 0x00016744   /* was DAT_00111838 (word at 0x00111838); PC-relative offset: + 0x110f64 (the pc) = 0x001276A8 */
#define STRING_HIPOTION_OFFSET 0x00016704   /* was DAT_0011183c (word at 0x0011183C); PC-relative offset: + 0x110fac (the pc) = 0x001276B0 */
#define STRING_ETHER_OFFSET 0x000166C8   /* was DAT_00111840 (word at 0x00111840); PC-relative offset: + 0x110ff4 (the pc) = 0x001276BC */
#define STRING_ELIXIR_OFFSET 0x00016688   /* was DAT_00111844 (word at 0x00111844); PC-relative offset: + 0x11103c (the pc) = 0x001276C4 */
#define STRING_FIRE_OFFSET 0x00016484   /* was DAT_00111848 (word at 0x00111848); PC-relative offset: + 0x111084 (the pc) = 0x00127508 */
#define STRING_BLIZZARD_OFFSET 0x00016454   /* was DAT_0011184c (word at 0x0011184C); PC-relative offset: + 0x1110bc (the pc) = 0x00127510 */
#define STRING_THUNDER_OFFSET 0x00016428   /* was DAT_00111850 (word at 0x00111850); PC-relative offset: + 0x1110f4 (the pc) = 0x0012751C */
#define DATA_AT_0012710C_OFFSET 0x00015F00   /* was DAT_00111858 (word at 0x00111858); PC-relative offset: + 0x11120c (the pc) = 0x0012710C */
#define DATA_AT_0012710C_OFFSET_2 0x00015ED4   /* was DAT_0011185c (word at 0x0011185C); PC-relative offset: + 0x111238 (the pc) = 0x0012710C */
#define DATA_AT_001276CC_OFFSET 0x0001647C   /* was DAT_00111860 (word at 0x00111860); PC-relative offset: + 0x111250 (the pc) = 0x001276CC */
#define DATA_AT_001276CC_OFFSET_2 0x00016428   /* was DAT_00111864 (word at 0x00111864); PC-relative offset: + 0x1112a4 (the pc) = 0x001276CC */
#define WORD_HEXADECIMAL_FFFEED2C 0xFFFEED2C   /* was DAT_00111868 (word at 0x00111868); value 0xFFFEED2C (-70356) */
#define STRING_BAR_BAR_OFFSET 0x000163E8   /* was DAT_0011186c (word at 0x0011186C); PC-relative offset: + 0x1112e8 (the pc) = 0x001276D0 */
#define STRING_AND_AND_OFFSET 0x000163CC   /* was DAT_00111870 (word at 0x00111870); PC-relative offset: + 0x111308 (the pc) = 0x001276D4 */
#define DATA_AT_0012710C_OFFSET_3 0x00015DA0   /* was DAT_00111874 (word at 0x00111874); PC-relative offset: + 0x11136c (the pc) = 0x0012710C */
#define DATA_AT_0012710C_OFFSET_4 0x00015D74   /* was DAT_00111878 (word at 0x00111878); PC-relative offset: + 0x111398 (the pc) = 0x0012710C */
#define STRING_ENGINE_VER_OFFSET 0x00016324   /* was DAT_0011187c (word at 0x0011187C); PC-relative offset: + 0x1113b4 (the pc) = 0x001276D8 */
#define STRING_EQUALS_EQUALS_OFFSET 0x000162B4   /* was DAT_00111880 (word at 0x00111880); PC-relative offset: + 0x111430 (the pc) = 0x001276E4 */
#define STRING_EQUALS_OFFSET 0x0001628C   /* was DAT_00111884 (word at 0x00111884); PC-relative offset: + 0x11145c (the pc) = 0x001276E8 */
#define DATA_AT_001276EC_OFFSET 0x00016264   /* was DAT_00111888 (word at 0x00111888); PC-relative offset: + 0x111488 (the pc) = 0x001276EC */
#define STRING_EQUALS_OFFSET_2 0x0001623C   /* was DAT_0011188c (word at 0x0011188C); PC-relative offset: + 0x1114b4 (the pc) = 0x001276F0 */
#define DATA_AT_001276F4_OFFSET 0x00016214   /* was DAT_00111890 (word at 0x00111890); PC-relative offset: + 0x1114e0 (the pc) = 0x001276F4 */
#define STRING_EQUALS_OFFSET_3 0x000161EC   /* was DAT_00111894 (word at 0x00111894); PC-relative offset: + 0x11150c (the pc) = 0x001276F8 */
#define DATA_AT_0012710C_OFFSET_5 0x00015AC0   /* was DAT_00111898 (word at 0x00111898); PC-relative offset: + 0x11164c (the pc) = 0x0012710C */
#define DATA_AT_0012710C_OFFSET_6 0x00015A94   /* was DAT_0011189c (word at 0x0011189C); PC-relative offset: + 0x111678 (the pc) = 0x0012710C */
#define WORD_HEXADECIMAL_2E6723BD 0x2E6723BD   /* was DAT_001118a0, DAT_00112e1c (word at 0x001118A0); value 0x2E6723BD (778511293) */
#define WORD_HEXADECIMAL_10C617E4 0x10C617E4   /* was DAT_001118a4, DAT_00112e18 (word at 0x001118A4); value 0x10C617E4 (281417700) */
#define FLOAT_1000 0x447A0000   /* was DAT_001118ac, DAT_00113168, DAT_001132a4, DAT_00113da0, DAT_001146e8, DAT_00118308, DAT_0011860c, DAT_0011c85c, DAT_0011cfcc, DAT_00122434 (word at 0x001118AC); the float 1000.0 */
#define WORD_HEXADECIMAL_00015CF8 0x00015CF8   /* was DAT_001127a4 (word at 0x001127A4); value 0x00015CF8 (89336) */
#define STRING_DOT_M3G_OFFSET 0x00015AE8   /* was DAT_001127a8 (word at 0x001127A8); PC-relative offset: + 0x111c24 (the pc) = 0x0012770C */
#define STRING_ALL_OFFSET 0x000154A0   /* was DAT_001127ac (word at 0x001127AC); PC-relative offset: + 0x112274 (the pc) = 0x00127714 */
#define DATA_AT_0012710C_OFFSET_7 0x00014D50   /* was DAT_001127b0 (word at 0x001127B0); PC-relative offset: + 0x1123bc (the pc) = 0x0012710C */
#define DATA_AT_0012710C_OFFSET_8 0x00014D24   /* was DAT_001127b4 (word at 0x001127B4); PC-relative offset: + 0x1123e8 (the pc) = 0x0012710C */
#define STRING_LOADING_OFFSET 0x0001531C   /* was DAT_001127b8 (word at 0x001127B8); PC-relative offset: + 0x112424 (the pc) = 0x00127740 */
#define STRING_HEALTH_OFFSET_2 0x00015250   /* was DAT_001127bc (word at 0x001127BC); PC-relative offset: + 0x11243c (the pc) = 0x0012768C */
#define STRING_MAGIC_OFFSET_2 0x00015234   /* was DAT_001127c0 (word at 0x001127C0); PC-relative offset: + 0x112460 (the pc) = 0x00127694 */
#define STRING_ENEMY_OFFSET 0x00015294   /* was DAT_001127c4 (word at 0x001127C4); PC-relative offset: + 0x112484 (the pc) = 0x00127718 */
#define DATA_AT_001276CC_OFFSET_3 0x00015224   /* was DAT_001127c8 (word at 0x001127C8); PC-relative offset: + 0x1124a8 (the pc) = 0x001276CC */
#define STRING_ALL_OFFSET_2 0x00015240   /* was DAT_001127cc (word at 0x001127CC); PC-relative offset: + 0x1124d4 (the pc) = 0x00127714 */
#define STRING_SHOW_OFFSET 0x0001522C   /* was DAT_001127d0 (word at 0x001127D0); PC-relative offset: + 0x1124f4 (the pc) = 0x00127720 */
#define STRING_ALL_OFFSET_3 0x00015200   /* was DAT_001127d4 (word at 0x001127D4); PC-relative offset: + 0x112528 (the pc) = 0x00127728 */
#define STRING_HIDE_OFFSET 0x000151E8   /* was DAT_001127d8 (word at 0x001127D8); PC-relative offset: + 0x112548 (the pc) = 0x00127730 */
#define STRING_LOADING_OFFSET_2 0x000151BC   /* was DAT_001127dc (word at 0x001127DC); PC-relative offset: + 0x11257c (the pc) = 0x00127738 */
#define STRING_SETTINGS_DOT_DAT_OFFSET_2 0x00015174   /* was DAT_00112958 (word at 0x00112958); PC-relative offset: + 0x1128e4 (the pc) = 0x00127A58 */
#define WORD_HEXADECIMAL_2BAC0EE7 0x2BAC0EE7   /* was DAT_00112a94 (word at 0x00112A94); value 0x2BAC0EE7 (732696295) */
#define STRING_DOT_M3G_OFFSET_2 0x00014E10   /* was DAT_00112b48 (word at 0x00112B48); PC-relative offset: + 0x112b00 (the pc) = 0x00127910 */
#define WORD_HEXADECIMAL_1D28D9CF 0x1D28D9CF   /* was DAT_00112c08 (word at 0x00112C08); value 0x1D28D9CF (489216463) */
#define DATA_AT_00127918_OFFSET 0x00014D80   /* was DAT_00112c0c (word at 0x00112C0C); PC-relative offset: + 0x112b98 (the pc) = 0x00127918 */
#define DATA_AT_00127944_OFFSET 0x00014D98   /* was DAT_00112c10 (word at 0x00112C10); PC-relative offset: + 0x112bac (the pc) = 0x00127944 */
#define DATA_AT_00127970_OFFSET 0x00014DB0   /* was DAT_00112c14 (word at 0x00112C14); PC-relative offset: + 0x112bc0 (the pc) = 0x00127970 */
#define DATA_AT_00126DEC_OFFSET 0x0001418C   /* was DAT_00112c98 (word at 0x00112C98); PC-relative offset: + 0x112c60 (the pc) = 0x00126DEC */
#define DATA_AT_001278E8_OFFSET 0x00014B7C   /* was DAT_00112db4 (word at 0x00112DB4); PC-relative offset: + 0x112d6c (the pc) = 0x001278E8 */
#define STRING_ME_OFFSET 0x000142B8   /* was DAT_00112e80 (word at 0x00112E80); PC-relative offset: + 0x112e44 (the pc) = 0x001270FC */
#define WORD_HEXADECIMAL_42652F1B 0x42652F1B   /* was DAT_00113468, DAT_00121a9c (word at 0x00113468); value 0x42652F1B (1113927451) */
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
#define STRING_ROTTOCHARACTER_OFFSET 0x00011F20   /* was DAT_001150b8 (word at 0x001150B8); PC-relative offset: + 0x114f68 (the pc) = 0x00126E88 */
#define STRING_DOHITBOSS_OFFSET 0x00011EF4   /* was DAT_001150bc (word at 0x001150BC); PC-relative offset: + 0x114f88 (the pc) = 0x00126E7C */
#define STRING_DOMAGICHITBOSS_OFFSET 0x00011EC4   /* was DAT_001150c0 (word at 0x001150C0); PC-relative offset: + 0x114fa8 (the pc) = 0x00126E6C */
#define STRING_SWITCHTARGETS_OFFSET 0x00011E94   /* was DAT_001150c4 (word at 0x001150C4); PC-relative offset: + 0x114fc8 (the pc) = 0x00126E5C */
#define STRING_NOBALLSONMAGIC_OFFSET 0x00011E64   /* was DAT_001150c8 (word at 0x001150C8); PC-relative offset: + 0x114fe8 (the pc) = 0x00126E4C */
#define STRING_NOBALLSONHIT_OFFSET 0x00011E34   /* was DAT_001150cc (word at 0x001150CC); PC-relative offset: + 0x115008 (the pc) = 0x00126E3C */
#define WORD_HEXADECIMAL_FFFEAED0 0xFFFEAED0   /* was DAT_00115e34 (word at 0x00115E34); value 0xFFFEAED0 (-86320) */
#define DATA_AT_0012710C_OFFSET_9 0x00011FB4   /* was DAT_00115e38 (word at 0x00115E38); PC-relative offset: + 0x115158 (the pc) = 0x0012710C */
#define DATA_AT_0012710C_OFFSET_10 0x00011F84   /* was DAT_00115e3c (word at 0x00115E3C); PC-relative offset: + 0x115188 (the pc) = 0x0012710C */
#define STRING_ADDSOFTKEY_OFFSET 0x00011F5C   /* was DAT_00115e40 (word at 0x00115E40); PC-relative offset: + 0x1151a4 (the pc) = 0x00127100 */
#define STRING_ADDUIACTION_OFFSET 0x00011EFC   /* was DAT_00115e44 (word at 0x00115E44); PC-relative offset: + 0x115214 (the pc) = 0x00127110 */
#define STRING_ADDUIINFO_OFFSET 0x00011EC0   /* was DAT_00115e48 (word at 0x00115E48); PC-relative offset: + 0x11525c (the pc) = 0x0012711C */
#define STRING_ADDUITEXT_OFFSET 0x00011E6C   /* was DAT_00115e4c (word at 0x00115E4C); PC-relative offset: + 0x1152bc (the pc) = 0x00127128 */
#define DATA_AT_00127134_OFFSET 0x00011E6C   /* was DAT_00115e50 (word at 0x00115E50); PC-relative offset: + 0x1152c8 (the pc) = 0x00127134 */
#define DATA_AT_00127138_OFFSET 0x00011D34   /* was DAT_00115e54 (word at 0x00115E54); PC-relative offset: + 0x115404 (the pc) = 0x00127138 */
#define STRING_ADJUSTVALUE_OFFSET 0x00011CC8   /* was DAT_00115e58 (word at 0x00115E58); PC-relative offset: + 0x115474 (the pc) = 0x0012713C */
#define STRING_BREAK_OFFSET 0x00011C78   /* was DAT_00115e5c (word at 0x00115E5C); PC-relative offset: + 0x1154d0 (the pc) = 0x00127148 */
#define STRING_FADE_OFFSET 0x00011C5C   /* was DAT_00115e60 (word at 0x00115E60); PC-relative offset: + 0x1154f4 (the pc) = 0x00127150 */
#define STRING_FIREPROJECTILE_OFFSET 0x00011BB0   /* was DAT_00115e64 (word at 0x00115E64); PC-relative offset: + 0x1155a8 (the pc) = 0x00127158 */
#define STRING_IF_OFFSET 0x00011AF0   /* was DAT_00115e6c (word at 0x00115E6C); PC-relative offset: + 0x115678 (the pc) = 0x00127168 */
#define WORD_HEXADECIMAL_FFFEA960 0xFFFEA960   /* was DAT_00115e70 (word at 0x00115E70); value 0xFFFEA960 (-87712) */
#define STRING_IF_OFFSET_2 0x00011A8C   /* was DAT_00115e74 (word at 0x00115E74); PC-relative offset: + 0x1156e0 (the pc) = 0x0012716C */
#define STRING_IFVAR_OFFSET 0x00011A70   /* was DAT_00115e7c (word at 0x00115E7C); PC-relative offset: + 0x115700 (the pc) = 0x00127170 */
#define WORD_HEXADECIMAL_FFFEA8DC 0xFFFEA8DC   /* was DAT_00115e80 (word at 0x00115E80); value 0xFFFEA8DC (-87844) */
#define STRING_IFVAR_OFFSET_2 0x00011A14   /* was DAT_00115e84 (word at 0x00115E84); PC-relative offset: + 0x115764 (the pc) = 0x00127178 */
#define STRING_ELSE_OFFSET 0x000119FC   /* was DAT_00115e8c (word at 0x00115E8C); PC-relative offset: + 0x115784 (the pc) = 0x00127180 */
#define STRING_ENDIF_OFFSET 0x000119D8   /* was DAT_00115e94 (word at 0x00115E94); PC-relative offset: + 0x1157b0 (the pc) = 0x00127188 */
#define STRING_LIFT_OFFSET_2 0x000119B4   /* was DAT_00115e9c (word at 0x00115E9C); PC-relative offset: + 0x1157dc (the pc) = 0x00127190 */
#define STRING_LINK_OFFSET 0x00011968   /* was DAT_00115ea4 (word at 0x00115EA4); PC-relative offset: + 0x115830 (the pc) = 0x00127198 */
#define STRING_LOADCLIPART_OFFSET 0x00011914   /* was DAT_00115eac (word at 0x00115EAC); PC-relative offset: + 0x11588c (the pc) = 0x001271A0 */
#define WORD_HEXADECIMAL_FFFEA72C 0xFFFEA72C   /* was DAT_00115eb0 (word at 0x00115EB0); value 0xFFFEA72C (-88276) */
#define STRING_LOADSCENE_OFFSET 0x0001181C   /* was DAT_00115eb8 (word at 0x00115EB8); PC-relative offset: + 0x115990 (the pc) = 0x001271AC */
#define STRING_LOADSOUNDS_OFFSET 0x000117EC   /* was DAT_00115ec0 (word at 0x00115EC0); PC-relative offset: + 0x1159cc (the pc) = 0x001271B8 */
#define WORD_HEXADECIMAL_FFFEA60C 0xFFFEA60C   /* was DAT_00115ec4 (word at 0x00115EC4); value 0xFFFEA60C (-88564) */
#define STRING_LOADSOUNDS_OFFSET_2 0x00011790   /* was DAT_00115ec8 (word at 0x00115EC8); PC-relative offset: + 0x115a34 (the pc) = 0x001271C4 */
#define STRING_MATCHPOSITION_OFFSET 0x00011778   /* was DAT_00115ed0 (word at 0x00115ED0); PC-relative offset: + 0x115a58 (the pc) = 0x001271D0 */
#define STRING_TERRAIN_OFFSET 0x00011728   /* was DAT_00115ed8 (word at 0x00115ED8); PC-relative offset: + 0x115ab8 (the pc) = 0x001271E0 */
#define STRING_PLAYANIM_OFFSET 0x00011704   /* was DAT_00115ee0 (word at 0x00115EE0); PC-relative offset: + 0x115ae4 (the pc) = 0x001271E8 */
#define STRING_LOOP_OFFSET 0x000116BC   /* was DAT_00115ee8 (word at 0x00115EE8); PC-relative offset: + 0x115b38 (the pc) = 0x001271F4 */
#define STRING_PLAYSEQUENCE_OFFSET 0x00011698   /* was DAT_00115ef0 (word at 0x00115EF0); PC-relative offset: + 0x115b64 (the pc) = 0x001271FC */
#define STRING_PLAYSOUND_OFFSET 0x00011658   /* was DAT_00115ef8 (word at 0x00115EF8); PC-relative offset: + 0x115bb4 (the pc) = 0x0012720C */
#define WORD_HEXADECIMAL_FFFEA428 0xFFFEA428   /* was DAT_00115efc (word at 0x00115EFC); value 0xFFFEA428 (-89048) */
#define STRING_BAD_OFFSET 0x0001162C   /* was DAT_00115f00 (word at 0x00115F00); PC-relative offset: + 0x115bec (the pc) = 0x00127218 */
#define STRING_GOOD_OFFSET 0x00011608   /* was DAT_00115f04 (word at 0x00115F04); PC-relative offset: + 0x115c14 (the pc) = 0x0012721C */
#define STRING_KEYBLADE_OFFSET 0x000115E8   /* was DAT_00115f08 (word at 0x00115F08); PC-relative offset: + 0x115c3c (the pc) = 0x00127224 */
#define STRING_EXPLODE_OFFSET 0x000115CC   /* was DAT_00115f0c (word at 0x00115F0C); PC-relative offset: + 0x115c64 (the pc) = 0x00127230 */
#define STRING_WATER_OFFSET 0x000115AC   /* was DAT_00115f10 (word at 0x00115F10); PC-relative offset: + 0x115c8c (the pc) = 0x00127238 */
#define STRING_JUMP_OFFSET 0x00011590   /* was DAT_00115f14 (word at 0x00115F14); PC-relative offset: + 0x115cb0 (the pc) = 0x00127240 */
#define STRING_THUD_OFFSET 0x00011574   /* was DAT_00115f18 (word at 0x00115F18); PC-relative offset: + 0x115cd4 (the pc) = 0x00127248 */
#define STRING_TRANSITION_OFFSET 0x00011554   /* was DAT_00115f1c (word at 0x00115F1C); PC-relative offset: + 0x115cfc (the pc) = 0x00127250 */
#define STRING_MAGIC_ALERT_OFFSET 0x00011538   /* was DAT_00115f20 (word at 0x00115F20); PC-relative offset: + 0x115d24 (the pc) = 0x0012725C */
#define STRING_MAGIC_CAST_OFFSET 0x0001151C   /* was DAT_00115f24 (word at 0x00115F24); PC-relative offset: + 0x115d4c (the pc) = 0x00127268 */
#define STRING_REMOVESOFTKEY_OFFSET 0x000114F0   /* was DAT_00115f2c (word at 0x00115F2C); PC-relative offset: + 0x115d84 (the pc) = 0x00127274 */
#define STRING_REMOVEUIACTION_OFFSET 0x000114C4   /* was DAT_00115f34 (word at 0x00115F34); PC-relative offset: + 0x115dc0 (the pc) = 0x00127284 */
#define STRING_REMOVEUITEXT_OFFSET 0x000114A8   /* was DAT_00115f3c (word at 0x00115F3C); PC-relative offset: + 0x115dec (the pc) = 0x00127294 */
#define STRING_RESETKEYS_OFFSET 0x0001148C   /* was DAT_00115f44 (word at 0x00115F44); PC-relative offset: + 0x115e18 (the pc) = 0x001272A4 */
#define STRING_SAVEGAME_OFFSET 0x00011348   /* was DAT_00116980 (word at 0x00116980); PC-relative offset: + 0x115f68 (the pc) = 0x001272B0 */
#define STRING_TEMP_OFFSET 0x0001131C   /* was DAT_00116988 (word at 0x00116988); PC-relative offset: + 0x115fa0 (the pc) = 0x001272BC */
#define STRING_SETANIMSPEED_OFFSET 0x000112F8   /* was DAT_00116990 (word at 0x00116990); PC-relative offset: + 0x115fcc (the pc) = 0x001272C4 */
#define STRING_SETANIMPOSITION_OFFSET 0x000112B8   /* was DAT_00116998 (word at 0x00116998); PC-relative offset: + 0x11601c (the pc) = 0x001272D4 */
#define WORD_HEXADECIMAL_FFFE9FAC 0xFFFE9FAC   /* was DAT_0011699c (word at 0x0011699C); value 0xFFFE9FAC (-90196) */
#define STRING_END_OFFSET 0x0001127C   /* was DAT_001169a0 (word at 0x001169A0); PC-relative offset: + 0x116068 (the pc) = 0x001272E4 */
#define STRING_SETAPPEARANCE_OFFSET 0x00011214   /* was DAT_001169a8 (word at 0x001169A8); PC-relative offset: + 0x1160d4 (the pc) = 0x001272E8 */
#define STRING_SETBACKGROUND_OFFSET 0x000111B4   /* was DAT_001169b0 (word at 0x001169B0); PC-relative offset: + 0x116144 (the pc) = 0x001272F8 */
#define STRING_SETCAMERAFOCUS_OFFSET 0x00011130   /* was DAT_001169b8 (word at 0x001169B8); PC-relative offset: + 0x1161d8 (the pc) = 0x00127308 */
#define WORD_HEXADECIMAL_FFFE9E00 0xFFFE9E00   /* was DAT_001169bc (word at 0x001169BC); value 0xFFFE9E00 (-90624) */
#define STRING_STANDARD_VIEW_OFFSET 0x00011104   /* was DAT_001169c0 (word at 0x001169C0); PC-relative offset: + 0x116214 (the pc) = 0x00127318 */
#define STRING_HIGH_VIEW_OFFSET 0x000110E4   /* was DAT_001169c8 (word at 0x001169C8); PC-relative offset: + 0x116244 (the pc) = 0x00127328 */
#define FLOAT_60 0x42700000   /* was DAT_001169cc, DAT_00121aa0, DAT_00121c60 (word at 0x001169CC); the float 60.0 */
#define STRING_PLAN_VIEW_OFFSET 0x000110C4   /* was DAT_001169d0 (word at 0x001169D0); PC-relative offset: + 0x116270 (the pc) = 0x00127334 */
#define FLOAT_80 0x42A00000   /* was DAT_001169d4 (word at 0x001169D4); the float 80.0 */
#define STRING_MED_VIEW_OFFSET 0x000110A0   /* was DAT_001169d8 (word at 0x001169D8); PC-relative offset: + 0x1162a0 (the pc) = 0x00127340 */
#define FLOAT_25 0x41C80000   /* was DAT_001169dc, DAT_00117884 (word at 0x001169DC); the float 25.0 */
#define STRING_LOW_VIEW_OFFSET 0x00011084   /* was DAT_001169e0 (word at 0x001169E0); PC-relative offset: + 0x1162c8 (the pc) = 0x0012734C */
#define WORD_HEXADECIMAL_FFFE9CFC 0xFFFE9CFC   /* was DAT_001169e8 (word at 0x001169E8); value 0xFFFE9CFC (-90884) */
#define STRING_SETCHARACTERMODE_OFFSET 0x00011008   /* was DAT_001169f0 (word at 0x001169F0); PC-relative offset: + 0x116350 (the pc) = 0x00127358 */
#define WORD_HEXADECIMAL_FFFE9C8C 0xFFFE9C8C   /* was DAT_001169f4 (word at 0x001169F4); value 0xFFFE9C8C (-90996) */
#define STRING_ATTACK_OFFSET_2 0x00010FE4   /* was DAT_001169f8 (word at 0x001169F8); PC-relative offset: + 0x116388 (the pc) = 0x0012736C */
#define STRING_SWIM_OFFSET 0x00010FC8   /* was DAT_001169fc (word at 0x001169FC); PC-relative offset: + 0x1163ac (the pc) = 0x00127374 */
#define STRING_SWIM_NO_CLIMB_OFFSET 0x00010FAC   /* was DAT_00116a00 (word at 0x00116A00); PC-relative offset: + 0x1163d0 (the pc) = 0x0012737C */
#define STRING_NOSWIM_OFFSET 0x00010F90   /* was DAT_00116a04 (word at 0x00116A04); PC-relative offset: + 0x1163fc (the pc) = 0x0012738C */
#define STRING_CLIMB_TREE_OFFSET 0x00010F74   /* was DAT_00116a08 (word at 0x00116A08); PC-relative offset: + 0x116420 (the pc) = 0x00127394 */
#define STRING_CLIMB_TREE_NO_ROT_OFFSET 0x00010F5C   /* was DAT_00116a0c (word at 0x00116A0C); PC-relative offset: + 0x116444 (the pc) = 0x001273A0 */
#define STRING_CLIMB_LADDER_OFFSET 0x00010F4C   /* was DAT_00116a10 (word at 0x00116A10); PC-relative offset: + 0x116468 (the pc) = 0x001273B4 */
#define STRING_LIFT_OFFSET_3 0x00010F38   /* was DAT_00116a14 (word at 0x00116A14); PC-relative offset: + 0x11648c (the pc) = 0x001273C4 */
#define STRING_DROP_OFFSET_2 0x00010F1C   /* was DAT_00116a18 (word at 0x00116A18); PC-relative offset: + 0x1164b0 (the pc) = 0x001273CC */
#define STRING_BEHIND_OFFSET 0x00010EF0   /* was DAT_00116a1c (word at 0x00116A1C); PC-relative offset: + 0x1164e4 (the pc) = 0x001273D4 */
#define STRING_HANG_OFFSET 0x00010ED4   /* was DAT_00116a20 (word at 0x00116A20); PC-relative offset: + 0x116508 (the pc) = 0x001273DC */
#define STRING_STATIC_HANG_OFFSET 0x00010E98   /* was DAT_00116a24 (word at 0x00116A24); PC-relative offset: + 0x11654c (the pc) = 0x001273E4 */
#define STRING_UNHANG_OFFSET 0x00010E80   /* was DAT_00116a28 (word at 0x00116A28); PC-relative offset: + 0x116570 (the pc) = 0x001273F0 */
#define STRING_HIT_OFFSET 0x00010E64   /* was DAT_00116a2c (word at 0x00116A2C); PC-relative offset: + 0x116594 (the pc) = 0x001273F8 */
#define STRING_IDLE_OFFSET 0x00010E20   /* was DAT_00116a30 (word at 0x00116A30); PC-relative offset: + 0x1165dc (the pc) = 0x001273FC */
#define STRING_RESET_OFFSET 0x00010E04   /* was DAT_00116a34 (word at 0x00116A34); PC-relative offset: + 0x116600 (the pc) = 0x00127404 */
#define STRING_SETCOLLECTABLES_OFFSET 0x00010DD0   /* was DAT_00116a3c (word at 0x00116A3C); PC-relative offset: + 0x11663c (the pc) = 0x0012740C */
#define STRING_SETCOLLISIONON_OFFSET 0x00010D54   /* was DAT_00116a44 (word at 0x00116A44); PC-relative offset: + 0x1166c8 (the pc) = 0x0012741C */
#define STRING_SETCOLLISIONOFF_OFFSET 0x00010D28   /* was DAT_00116a4c (word at 0x00116A4C); PC-relative offset: + 0x116704 (the pc) = 0x0012742C */
#define STRING_SETCOMBATREGION_OFFSET 0x00010CFC   /* was DAT_00116a54 (word at 0x00116A54); PC-relative offset: + 0x116740 (the pc) = 0x0012743C */
#define STRING_SETKEYSON_OFFSET 0x00010CD0   /* was DAT_00116a5c (word at 0x00116A5C); PC-relative offset: + 0x11677c (the pc) = 0x0012744C */
#define STRING_SETKEYSOFF_OFFSET 0x00010CA0   /* was DAT_00116a64 (word at 0x00116A64); PC-relative offset: + 0x1167b8 (the pc) = 0x00127458 */
#define STRING_SETLEVELUP_OFFSET 0x00010C70   /* was DAT_00116a6c (word at 0x00116A6C); PC-relative offset: + 0x1167f4 (the pc) = 0x00127464 */
#define STRING_SETMIRROR_OFFSET 0x00010C10   /* was DAT_00116a74 (word at 0x00116A74); PC-relative offset: + 0x116860 (the pc) = 0x00127470 */
#define WORD_HEXADECIMAL_FFFE977C 0xFFFE977C   /* was DAT_00116a78 (word at 0x00116A78); value 0xFFFE977C (-92292) */
#define STRING_NULL_OFFSET 0x00010BE4   /* was DAT_00116a7c (word at 0x00116A7C); PC-relative offset: + 0x116898 (the pc) = 0x0012747C */
#define STRING_DASH_X_OFFSET 0x00010BB4   /* was DAT_00116a80 (word at 0x00116A80); PC-relative offset: + 0x1168d0 (the pc) = 0x00127484 */
#define STRING_DASH_Y_OFFSET 0x00010B98   /* was DAT_00116a84 (word at 0x00116A84); PC-relative offset: + 0x1168f0 (the pc) = 0x00127488 */
#define STRING_DASH_Z_OFFSET 0x00010B7C   /* was DAT_00116a88 (word at 0x00116A88); PC-relative offset: + 0x116910 (the pc) = 0x0012748C */
#define STRING_DASH_R_OFFSET 0x00010B60   /* was DAT_00116a8c (word at 0x00116A8C); PC-relative offset: + 0x116930 (the pc) = 0x00127490 */
#define STRING_SETMOVINGCAMERA_OFFSET 0x000109E4   /* was DAT_001173cc (word at 0x001173CC); PC-relative offset: + 0x116ab0 (the pc) = 0x00127494 */
#define STRING_SETPOSITION_OFFSET 0x000109C8   /* was DAT_001173d4 (word at 0x001173D4); PC-relative offset: + 0x116adc (the pc) = 0x001274A4 */
#define WORD_HEXADECIMAL_FFFE94F0 0xFFFE94F0   /* was DAT_001173d8 (word at 0x001173D8); value 0xFFFE94F0 (-92944) */
#define STRING_NULL_OFFSET_2 0x0001095C   /* was DAT_001173dc (word at 0x001173DC); PC-relative offset: + 0x116b20 (the pc) = 0x0012747C */
#define STRING_TERRAIN_OFFSET_2 0x00010630   /* was DAT_001173e0 (word at 0x001173E0); PC-relative offset: + 0x116bb0 (the pc) = 0x001271E0 */
#define STRING_SETSCREENMODE_OFFSET 0x000108BC   /* was DAT_001173e8 (word at 0x001173E8); PC-relative offset: + 0x116bf4 (the pc) = 0x001274B0 */
#define WORD_HEXADECIMAL_FFFE93F0 0xFFFE93F0   /* was DAT_001173ec (word at 0x001173EC); value 0xFFFE93F0 (-93200) */
#define STRING_CINEMATIC_OFFSET 0x0001089C   /* was DAT_001173f0 (word at 0x001173F0); PC-relative offset: + 0x116c24 (the pc) = 0x001274C0 */
#define STRING_SETSCRIPTON_OFFSET 0x0001087C   /* was DAT_001173f8 (word at 0x001173F8); PC-relative offset: + 0x116c50 (the pc) = 0x001274CC */
#define STRING_SETSCRIPTOFF_OFFSET 0x0001084C   /* was DAT_00117400 (word at 0x00117400); PC-relative offset: + 0x116c8c (the pc) = 0x001274D8 */
#define STRING_SETSHADOWVIS_OFFSET 0x00010820   /* was DAT_00117408 (word at 0x00117408); PC-relative offset: + 0x116cc8 (the pc) = 0x001274E8 */
#define STRING_SETSPELLTYPE_OFFSET 0x000107F4   /* was DAT_00117410 (word at 0x00117410); PC-relative offset: + 0x116d04 (the pc) = 0x001274F8 */
#define WORD_HEXADECIMAL_FFFE92D8 0xFFFE92D8   /* was DAT_00117414 (word at 0x00117414); value 0xFFFE92D8 (-93480) */
#define STRING_FIRE_OFFSET_2 0x000107CC   /* was DAT_00117418 (word at 0x00117418); PC-relative offset: + 0x116d3c (the pc) = 0x00127508 */
#define STRING_BLIZZARD_OFFSET_2 0x000107AC   /* was DAT_0011741c (word at 0x0011741C); PC-relative offset: + 0x116d64 (the pc) = 0x00127510 */
#define STRING_THUNDER_OFFSET_2 0x00010798   /* was DAT_00117420 (word at 0x00117420); PC-relative offset: + 0x116d84 (the pc) = 0x0012751C */
#define STRING_SETSTATE_OFFSET 0x0001076C   /* was DAT_00117428 (word at 0x00117428); PC-relative offset: + 0x116db8 (the pc) = 0x00127524 */
#define STRING_SETVAR_OFFSET 0x0001073C   /* was DAT_00117430 (word at 0x00117430); PC-relative offset: + 0x116df4 (the pc) = 0x00127530 */
#define STRING_INCVAR_OFFSET 0x00010708   /* was DAT_00117438 (word at 0x00117438); PC-relative offset: + 0x116e30 (the pc) = 0x00127538 */
#define STRING_DECVAR_OFFSET 0x000106A4   /* was DAT_00117440 (word at 0x00117440); PC-relative offset: + 0x116e9c (the pc) = 0x00127540 */
#define STRING_SETSTATICCAMERA_OFFSET 0x00010650   /* was DAT_00117448 (word at 0x00117448); PC-relative offset: + 0x116ef8 (the pc) = 0x00127548 */
#define STRING_SETTERRAINLEVEL_OFFSET 0x00010610   /* was DAT_00117450 (word at 0x00117450); PC-relative offset: + 0x116f48 (the pc) = 0x00127558 */
#define STRING_SETUPDATEON_OFFSET 0x000105E4   /* was DAT_00117458 (word at 0x00117458); PC-relative offset: + 0x116f84 (the pc) = 0x00127568 */
#define STRING_SETUPDATEOFF_OFFSET 0x000105B4   /* was DAT_00117460 (word at 0x00117460); PC-relative offset: + 0x116fc0 (the pc) = 0x00127574 */
#define STRING_SETUIVIS_OFFSET 0x00010588   /* was DAT_00117468 (word at 0x00117468); PC-relative offset: + 0x116ffc (the pc) = 0x00127584 */
#define WORD_HEXADECIMAL_FFFE8FE0 0xFFFE8FE0   /* was DAT_0011746c (word at 0x0011746C); value 0xFFFE8FE0 (-94240) */
#define STRING_SETUIVIS_OFFSET_2 0x00010530   /* was DAT_00117470 (word at 0x00117470); PC-relative offset: + 0x117060 (the pc) = 0x00127590 */
#define WORD_HEXADECIMAL_FFFE8F88 0xFFFE8F88   /* was DAT_00117474 (word at 0x00117474); value 0xFFFE8F88 (-94328) */
#define STRING_SETVICTIM_OFFSET 0x00010510   /* was DAT_00117478 (word at 0x00117478); PC-relative offset: + 0x11708c (the pc) = 0x0012759C */
#define STRING_NULL_OFFSET_3 0x000103C0   /* was DAT_0011747c (word at 0x0011747C); PC-relative offset: + 0x1170bc (the pc) = 0x0012747C */
#define STRING_SETVIS_OFFSET 0x000104C8   /* was DAT_00117480 (word at 0x00117480); PC-relative offset: + 0x1170e0 (the pc) = 0x001275A8 */
#define STRING_SETXROT_OFFSET 0x00010470   /* was DAT_00117484 (word at 0x00117484); PC-relative offset: + 0x117140 (the pc) = 0x001275B0 */
#define STRING_SETYROT_OFFSET 0x00010444   /* was DAT_00117488 (word at 0x00117488); PC-relative offset: + 0x117174 (the pc) = 0x001275B8 */
#define STRING_STOPANIM_OFFSET 0x000103F4   /* was DAT_0011748c (word at 0x0011748C); PC-relative offset: + 0x1171cc (the pc) = 0x001275C0 */
#define STRING_NOW_OFFSET 0x000103B4   /* was DAT_00117490 (word at 0x00117490); PC-relative offset: + 0x117218 (the pc) = 0x001275CC */
#define STRING_SUMMARY_OFFSET 0x00010390   /* was DAT_00117494 (word at 0x00117494); PC-relative offset: + 0x117240 (the pc) = 0x001275D0 */
#define STRING_UNLINK_OFFSET 0x00010350   /* was DAT_00117498 (word at 0x00117498); PC-relative offset: + 0x117288 (the pc) = 0x001275D8 */
#define STRING_UNLOADCLIPART_OFFSET 0x00010324   /* was DAT_0011749c (word at 0x0011749C); PC-relative offset: + 0x1172bc (the pc) = 0x001275E0 */
#define STRING_SETKEYDIR_OFFSET 0x000102B8   /* was DAT_001174a0 (word at 0x001174A0); PC-relative offset: + 0x117338 (the pc) = 0x001275F0 */
#define STRING_SETACTIVEROTON_OFFSET 0x00010290   /* was DAT_001174a4 (word at 0x001174A4); PC-relative offset: + 0x11736c (the pc) = 0x001275FC */
#define STRING_SETACTIVEROTOFF_OFFSET 0x0001027C   /* was DAT_001174a8 (word at 0x001174A8); PC-relative offset: + 0x117390 (the pc) = 0x0012760C */
#define ADDRESS_OF_FUNCTION_0011daac_OFFSET 0x000065C8   /* was DAT_00117874 (word at 0x00117874); PC-relative offset: + 0x1174e4 (the pc) = 0x0011DAAC */
#define ADDRESS_OF_FUNCTION_0011d3ec_OFFSET 0x00005EFC   /* was DAT_00117878 (word at 0x00117878); PC-relative offset: + 0x1174f0 (the pc) = 0x0011D3EC */
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
#define ADDRESS_OF_FUNCTION_0011d6cc_OFFSET 0x00005FE0   /* was DAT_00117900 (word at 0x00117900); PC-relative offset: + 0x1176ec (the pc) = 0x0011D6CC */
#define ADDRESS_OF_FUNCTION_0011d28c_OFFSET 0x00005B94   /* was DAT_00117904 (word at 0x00117904); PC-relative offset: + 0x1176f8 (the pc) = 0x0011D28C */
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
#define STRING_SOLDIER_OFFSET 0x0000F23C   /* was DAT_00118084 (word at 0x00118084); PC-relative offset: + 0x117dfc (the pc) = 0x00127038 */
#define STRING_FLYINGSOLDIER_OFFSET 0x0000F21C   /* was DAT_00118088 (word at 0x00118088); PC-relative offset: + 0x117e24 (the pc) = 0x00127040 */
#define STRING_FLYINGMOOK_OFFSET 0x0000F208   /* was DAT_0011808c (word at 0x0011808C); PC-relative offset: + 0x117e48 (the pc) = 0x00127050 */
#define STRING_PURPLECROC_OFFSET 0x0000F1F0   /* was DAT_00118090 (word at 0x00118090); PC-relative offset: + 0x117e6c (the pc) = 0x0012705C */
#define STRING_UMBRELLABIRD_OFFSET 0x0000F1D8   /* was DAT_00118094 (word at 0x00118094); PC-relative offset: + 0x117e90 (the pc) = 0x00127068 */
#define STRING_BANDIT_OFFSET 0x0000F1C4   /* was DAT_00118098 (word at 0x00118098); PC-relative offset: + 0x117eb4 (the pc) = 0x00127078 */
#define STRING_POTSPIDER_OFFSET 0x0000F1A8   /* was DAT_0011809c (word at 0x0011809C); PC-relative offset: + 0x117ed8 (the pc) = 0x00127080 */
#define STRING_MUMMY_OFFSET 0x0000F190   /* was DAT_001180a0 (word at 0x001180A0); PC-relative offset: + 0x117efc (the pc) = 0x0012708C */
#define STRING_DARKBALL_OFFSET 0x0000F174   /* was DAT_001180a4 (word at 0x001180A4); PC-relative offset: + 0x117f20 (the pc) = 0x00127094 */
#define STRING_PIGSOLDIER_OFFSET 0x0000F15C   /* was DAT_001180a8 (word at 0x001180A8); PC-relative offset: + 0x117f44 (the pc) = 0x001270A0 */
#define WORD_HEXADECIMAL_369F84CA 0x369F84CA   /* was DAT_001180ac (word at 0x001180AC); value 0x369F84CA (916423882) */
#define WORD_HEXADECIMAL_0B63154F 0x0B63154F   /* was DAT_001180b0 (word at 0x001180B0); value 0x0B63154F (191042895) */
#define WORD_HEXADECIMAL_26B58FD6 0x26B58FD6   /* was DAT_001180c0 (word at 0x001180C0); value 0x26B58FD6 (649433046) */
#define WORD_HEXADECIMAL_3488ACED 0x3488ACED   /* was DAT_00118304 (word at 0x00118304); value 0x3488ACED (881372397) */
#define STRING_CARRIAGE_RETURN_NEWLINE_OFFSET_5 0x0000EF14   /* was DAT_0011830c (word at 0x0011830C); PC-relative offset: + 0x1181e4 (the pc) = 0x001270F8 */
#define WORD_HEXADECIMAL_1DED5D32 0x1DED5D32   /* was DAT_00118314 (word at 0x00118314); value 0x1DED5D32 (502095154) */
#define WORD_HEXADECIMAL_2073D363 0x2073D363   /* was DAT_00118604 (word at 0x00118604); value 0x2073D363 (544461667) */
#define WORD_HEXADECIMAL_1932DEDD 0x1932DEDD   /* was DAT_00118608 (word at 0x00118608); value 0x1932DEDD (422764253) */
#define WORD_HEXADECIMAL_1218EC09 0x1218EC09   /* was DAT_00118610 (word at 0x00118610); value 0x1218EC09 (303623177) */
#define DATA_AT_00126EA8_OFFSET 0x0000EB18   /* was DAT_00118614 (word at 0x00118614); PC-relative offset: + 0x118390 (the pc) = 0x00126EA8 */
#define DATA_AT_00126F1C_OFFSET 0x0000EB4C   /* was DAT_00118618 (word at 0x00118618); PC-relative offset: + 0x1183d0 (the pc) = 0x00126F1C */
#define DATA_AT_00126F5C_OFFSET 0x0000EB78   /* was DAT_0011861c (word at 0x0011861C); PC-relative offset: + 0x1183e4 (the pc) = 0x00126F5C */
#define WORD_HEXADECIMAL_0F846A96 0x0F846A96   /* was DAT_00118620 (word at 0x00118620); value 0x0F846A96 (260336278) */
#define WORD_HEXADECIMAL_0D44B786 0x0D44B786   /* was DAT_00118624 (word at 0x00118624); value 0x0D44B786 (222607238) */
#define WORD_HEXADECIMAL_1DFBEC7F 0x1DFBEC7F   /* was DAT_00118628, DAT_0011ba08 (word at 0x00118628); value 0x1DFBEC7F (503049343) */
#define WORD_HEXADECIMAL_314D49C5 0x314D49C5   /* was DAT_0011862c (word at 0x0011862C); value 0x314D49C5 (827148741) */
#define WORD_HEXADECIMAL_0A893452 0x0A893452   /* was DAT_00118630 (word at 0x00118630); value 0x0A893452 (176763986) */
#define STRING_CHARACTER_SHADOW_OFFSET 0x0000EA08   /* was DAT_00118634 (word at 0x00118634); PC-relative offset: + 0x1185a0 (the pc) = 0x00126FA8 */
#define WORD_HEXADECIMAL_2BB0C920 0x2BB0C920   /* was DAT_00118638 (word at 0x00118638); value 0x2BB0C920 (733006112) */
#define WORD_HEXADECIMAL_19DB98DB 0x19DB98DB   /* was DAT_0011863c (word at 0x0011863C); value 0x19DB98DB (433821915) */
#define WORD_HEXADECIMAL_13EB8A28 0x13EB8A28   /* was DAT_001188f8 (word at 0x001188F8); value 0x13EB8A28 (334203432) */
#define STRING_CARRIAGE_RETURN_NEWLINE_OFFSET_6 0x0000E768   /* was DAT_001188fc (word at 0x001188FC); PC-relative offset: + 0x1186c4 (the pc) = 0x00126E2C */
#define WORD_HEXADECIMAL_155EAFB5 0x155EAFB5   /* was DAT_00118904 (word at 0x00118904); value 0x155EAFB5 (358526901) */
#define WORD_HEXADECIMAL_2E583064 0x2E583064   /* was DAT_00118908 (word at 0x00118908); value 0x2E583064 (777531492) */
#define WORD_HEXADECIMAL_275AA16E 0x275AA16E   /* was DAT_0011890c (word at 0x0011890C); value 0x275AA16E (660250990) */
#define WORD_HEXADECIMAL_178BD97D 0x178BD97D   /* was DAT_00118e90 (word at 0x00118E90); value 0x178BD97D (395041149) */
#define WORD_HEXADECIMAL_FFFE768C 0xFFFE768C   /* was DAT_00118e94 (word at 0x00118E94); value 0xFFFE768C (-100724) */
#define DATA_AT_0012774C_OFFSET 0x0000EDB0   /* was DAT_00118e98 (word at 0x00118E98); PC-relative offset: + 0x11899c (the pc) = 0x0012774C */
#define DATA_AT_0012774C_OFFSET_2 0x0000ED84   /* was DAT_00118e9c (word at 0x00118E9C); PC-relative offset: + 0x1189c8 (the pc) = 0x0012774C */
#define DATA_AT_00127750_OFFSET 0x0000ED64   /* was DAT_00118ea0 (word at 0x00118EA0); PC-relative offset: + 0x1189ec (the pc) = 0x00127750 */
#define WORD_HEXADECIMAL_18FC8335 0x18FC8335   /* was DAT_00118ea4 (word at 0x00118EA4); value 0x18FC8335 (419201845) */
#define WORD_HEXADECIMAL_3310A2A1 0x3310A2A1   /* was DAT_00118ea8 (word at 0x00118EA8); value 0x3310A2A1 (856728225) */
#define WORD_HEXADECIMAL_0B090BAC 0x0B090BAC   /* was DAT_00118eac (word at 0x00118EAC); value 0x0B090BAC (185142188) */
#define WORD_HEXADECIMAL_08E8548D 0x08E8548D   /* was DAT_00118eb0 (word at 0x00118EB0); value 0x08E8548D (149443725) */
#define WORD_HEXADECIMAL_19631267 0x19631267   /* was DAT_00118eb4 (word at 0x00118EB4); value 0x19631267 (425923175) */
#define WORD_HEXADECIMAL_2101870D 0x2101870D   /* was DAT_00118eb8 (word at 0x00118EB8); value 0x2101870D (553748237) */
#define STRING_CARRIAGE_RETURN_NEWLINE_OFFSET_7 0x0000EA94   /* was DAT_00118ebc (word at 0x00118EBC); PC-relative offset: + 0x118cc0 (the pc) = 0x00127754 */
#define STRING_CARRIAGE_RETURN_NEWLINE_OFFSET_8 0x0000EA64   /* was DAT_00118ec0 (word at 0x00118EC0); PC-relative offset: + 0x118cf0 (the pc) = 0x00127754 */
#define WORD_HEXADECIMAL_32CA0CC6 0x32CA0CC6   /* was DAT_00118ec4 (word at 0x00118EC4); value 0x32CA0CC6 (852102342) */
#define STRING_MOVING_OFFSET 0x0000E964   /* was DAT_00118ec8 (word at 0x00118EC8); PC-relative offset: + 0x118e14 (the pc) = 0x00127778 */
#define STRING_ALIGN_OFFSET 0x0000E940   /* was DAT_00118ecc (word at 0x00118ECC); PC-relative offset: + 0x118e30 (the pc) = 0x00127770 */
#define STRING_NONTERRAIN_OFFSET 0x0000E918   /* was DAT_00118ed0 (word at 0x00118ED0); PC-relative offset: + 0x118e4c (the pc) = 0x00127764 */
#define STRING_TERRAINONLY_OFFSET 0x0000E8F0   /* was DAT_00118ed4 (word at 0x00118ED4); PC-relative offset: + 0x118e68 (the pc) = 0x00127758 */
#define DATA_AT_00126FCC_OFFSET 0x0000E0C4   /* was DAT_0011958c (word at 0x0011958C); PC-relative offset: + 0x118f08 (the pc) = 0x00126FCC */
#define DATA_AT_00126FCC_OFFSET_2 0x0000E094   /* was DAT_00119590 (word at 0x00119590); PC-relative offset: + 0x118f38 (the pc) = 0x00126FCC */
#define WORD_HEXADECIMAL_FFFE70A8 0xFFFE70A8   /* was DAT_00119598 (word at 0x00119598); value 0xFFFE70A8 (-102232) */
#define STRING_USE_VERTS_OFFSET 0x0000E058   /* was DAT_0011959c (word at 0x0011959C); PC-relative offset: + 0x118f78 (the pc) = 0x00126FD0 */
#define STRING_OUTER_OFFSET 0x0000DFF0   /* was DAT_001195a0 (word at 0x001195A0); PC-relative offset: + 0x118fec (the pc) = 0x00126FDC */
#define STRING_INNER_OFFSET 0x0000DFD4   /* was DAT_001195a4 (word at 0x001195A4); PC-relative offset: + 0x119010 (the pc) = 0x00126FE4 */
#define STRING_CIRCLE_OFFSET 0x0000DFAC   /* was DAT_001195ac (word at 0x001195AC); PC-relative offset: + 0x119040 (the pc) = 0x00126FEC */
#define WORD_HEXADECIMAL_FFFE6FA8 0xFFFE6FA8   /* was DAT_001195b0 (word at 0x001195B0); value 0xFFFE6FA8 (-102488) */
#define STRING_CYLINDER_OFFSET 0x0000DF88   /* was DAT_001195b4 (word at 0x001195B4); PC-relative offset: + 0x11906c (the pc) = 0x00126FF4 */
#define STRING_CUBOID_OFFSET 0x0000DF70   /* was DAT_001195b8 (word at 0x001195B8); PC-relative offset: + 0x119090 (the pc) = 0x00127000 */
#define STRING_RECT_OFFSET 0x0000DF54   /* was DAT_001195bc (word at 0x001195BC); PC-relative offset: + 0x1190b4 (the pc) = 0x00127008 */
#define STRING_POLY_OFFSET 0x0000DF38   /* was DAT_001195c0 (word at 0x001195C0); PC-relative offset: + 0x1190d8 (the pc) = 0x00127010 */
#define STRING_SPHERE_OFFSET 0x0000DF1C   /* was DAT_001195c4 (word at 0x001195C4); PC-relative offset: + 0x1190fc (the pc) = 0x00127018 */
#define STRING_CLOCKWISE_OFFSET 0x0000DC68   /* was DAT_001195d0 (word at 0x001195D0); PC-relative offset: + 0x1193b8 (the pc) = 0x00127020 */
#define WORD_HEXADECIMAL_FFFE6C24 0xFFFE6C24   /* was DAT_001195d4 (word at 0x001195D4); value 0xFFFE6C24 (-103388) */
#define STRING_PERCENT_DTRANSFORM_OFFSET 0x0000DC48   /* was DAT_001195d8 (word at 0x001195D8); PC-relative offset: + 0x1193e4 (the pc) = 0x0012702C */
#define CLASS_IDENTIFIER_HEXADECIMAL_0100A004 0x0100A004   /* was DAT_001199fc (word at 0x001199FC); in the BREW class identifier range */
#define INTEGER_261 0x00000105   /* was DAT_00119a00 (word at 0x00119A00); integer 261 */
#define AEECLSID_SWERVE_VALUE 0x0102BBFC   /* was DAT_00119a04 (word at 0x00119A04); BREW class identifier AEECLSID_SWERVE */
#define INTEGER_262 0x00000106   /* was DAT_00119a08 (word at 0x00119A08); integer 262 */
#define INTEGER_263 0x00000107   /* was DAT_00119a0c, DAT_0011b9fc, DAT_00124654 (word at 0x00119A0C); integer 263 */
#define AEECLSID_DIB_VALUE 0x01001045   /* was DAT_00119a10 (word at 0x00119A10); BREW class identifier AEECLSID_DIB */
#define INTEGER_265 0x00000109   /* was DAT_00119a14 (word at 0x00119A14); integer 265 */
#define WORD_HEXADECIMAL_28500339 0x28500339   /* was DAT_00119a18 (word at 0x00119A18); value 0x28500339 (676332345) */
#define INTEGER_258 0x00000102   /* was DAT_00119a20 (word at 0x00119A20); integer 258 */
#define INTEGER_257 0x00000101   /* was DAT_00119a24 (word at 0x00119A24); integer 257 */
#define WORD_HEXADECIMAL_018B5704 0x018B5704   /* was DAT_00119c00 (word at 0x00119C00); value 0x018B5704 (25908996) */
#define STRING_CARRIAGE_RETURN_NEWLINE_OFFSET_9 0x0000E3B8   /* was DAT_00119c04 (word at 0x00119C04); PC-relative offset: + 0x119b50 (the pc) = 0x00127F08 */
#define STRING_CARRIAGE_RETURN_NEWLINE_OFFSET_10 0x0000E390   /* was DAT_00119c08 (word at 0x00119C08); PC-relative offset: + 0x119b78 (the pc) = 0x00127F08 */
#define WORD_HEXADECIMAL_FFFE646C 0xFFFE646C   /* was DAT_00119c0c (word at 0x00119C0C); value 0xFFFE646C (-105364) */
#define WORD_HEXADECIMAL_38D1B717 0x38D1B717   /* was DAT_0011a2f0 (word at 0x0011A2F0); value 0x38D1B717 (953267991) */
#define STRING_OUT_OF_MAGIC_OFFSET_3 0x0000C8EC   /* was DAT_0011a7d8 (word at 0x0011A7D8); PC-relative offset: + 0x11a6d0 (the pc) = 0x00126FBC */
#define DATA_AT_001279E0_OFFSET 0x0000D10C   /* was DAT_0011aa60 (word at 0x0011AA60); PC-relative offset: + 0x11a8d4 (the pc) = 0x001279E0 */
#define WORD_HEXADECIMAL_FFFE5718 0xFFFE5718   /* was DAT_0011aa64 (word at 0x0011AA64); value 0xFFFE5718 (-108776) */
#define WORD_HEXADECIMAL_1EB851EC 0x1EB851EC   /* was DAT_0011adb8 (word at 0x0011ADB8); value 0x1EB851EC (515396076) */
#define FLOAT_1_POINT_14 0x3F91EB85   /* was DAT_0011adbc (word at 0x0011ADBC); the float 1.1399999856948853 */
#define STRING_TRANSFORM_OFFSET 0x0000D070   /* was DAT_0011b03c (word at 0x0011B03C); PC-relative offset: + 0x11ae84 (the pc) = 0x00127EF4 */
#define STRING_DOT_M3G_OFFSET_3 0x0000CFD8   /* was DAT_0011b040 (word at 0x0011B040); PC-relative offset: + 0x11af28 (the pc) = 0x00127F00 */
#define STRING_SCOREDATA_DOT_DAT_OFFSET 0x0000C2A0   /* was DAT_0011b6ec (word at 0x0011B6EC); PC-relative offset: + 0x11b628 (the pc) = 0x001278C8 */
#define STRING_DISNEY_DOT_M3G_OFFSET 0x0000C0AC   /* was DAT_0011b9f0 (word at 0x0011B9F0); PC-relative offset: + 0x11b8f0 (the pc) = 0x0012799C */
#define STRING_SWERVE_DOT_M3G_OFFSET 0x0000C09C   /* was DAT_0011b9f4 (word at 0x0011B9F4); PC-relative offset: + 0x11b90c (the pc) = 0x001279A8 */
#define STRING_INTRO_DOT_M3G_OFFSET 0x0000C090   /* was DAT_0011b9f8 (word at 0x0011B9F8); PC-relative offset: + 0x11b924 (the pc) = 0x001279B4 */
#define WORD_HEXADECIMAL_3E11FC00 0x3E11FC00   /* was DAT_0011ba00 (word at 0x0011BA00); value 0x3E11FC00 (1041366016) */
#define STRING_CHARACTER_GRP_OFFSET_2 0x0000C048   /* was DAT_0011ba04 (word at 0x0011BA04); PC-relative offset: + 0x11b978 (the pc) = 0x001279C0 */
extern undefined4 ADDRESS_OF_FUNCTION_0011bb00_SELF_RELATIVE_OFFSET;   /* was DAT_0011bb98 (word at 0x0011BB98 = 0xFFFFFF68); word relative to its own address: 0x0011BB98 + 0xFFFFFF68 = 0x0011BB00 */
#define INTEGER_3003 0x00000BBB   /* was DAT_0011c6ec (word at 0x0011C6EC); integer 3003 */
#define DATA_AT_001270AC_OFFSET 0x0000AC38   /* was DAT_0011c6f0 (word at 0x0011C6F0); PC-relative offset: + 0x11c474 (the pc) = 0x001270AC */
#define INTEGER_7000 0x00001B58   /* was DAT_0011c6f8 (word at 0x0011C6F8); integer 7000 */
#define FLOAT_350 0x43AF0000   /* was DAT_0011c6fc (word at 0x0011C6FC); the float 350.0 */
#define INTEGER_3002 0x00000BBA   /* was DAT_0011c700 (word at 0x0011C700); integer 3002 */
#define WORD_HEXADECIMAL_358637BD 0x358637BD   /* was DAT_0011c704 (word at 0x0011C704); value 0x358637BD (897988541) */
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
#define ADDRESS_OF_FUNCTION_001242b4_OFFSET_2 0x000060A4   /* was DAT_0011e24c (word at 0x0011E24C); PC-relative offset: + 0x11e210 (the pc) = 0x001242B4 */
#define STRING_TMP_DOT_DAT_OFFSET 0x00009324   /* was DAT_0011e6b4 (word at 0x0011E6B4); PC-relative offset: + 0x11e5c8 (the pc) = 0x001278EC */
#define STRING_SCOREDATA_DOT_DAT_OFFSET_2 0x00008E20   /* was DAT_0011ead0 (word at 0x0011EAD0); PC-relative offset: + 0x11eaa8 (the pc) = 0x001278C8 */
#define STRING_HASH_UP_OFFSET 0x000091E0   /* was DAT_0011f20c (word at 0x0011F20C); PC-relative offset: + 0x11ed64 (the pc) = 0x00127F44 */
#define STRING_HASH_DOWN_OFFSET 0x000091C0   /* was DAT_0011f210 (word at 0x0011F210); PC-relative offset: + 0x11ed7c (the pc) = 0x00127F3C */
#define STRING_HASH_LEFT_OFFSET 0x000091A0   /* was DAT_0011f214 (word at 0x0011F214); PC-relative offset: + 0x11ed94 (the pc) = 0x00127F34 */
#define STRING_HASH_RIGHT_OFFSET 0x00009180   /* was DAT_0011f218 (word at 0x0011F218); PC-relative offset: + 0x11edac (the pc) = 0x00127F2C */
#define STRING_HASH_ACTION_OFFSET 0x00009160   /* was DAT_0011f21c (word at 0x0011F21C); PC-relative offset: + 0x11edc4 (the pc) = 0x00127F24 */
#define STRING_HASH_INV_OFFSET 0x00009140   /* was DAT_0011f220 (word at 0x0011F220); PC-relative offset: + 0x11eddc (the pc) = 0x00127F1C */
#define STRING_HASH_MAGIC_OFFSET 0x00009120   /* was DAT_0011f224 (word at 0x0011F224); PC-relative offset: + 0x11edf4 (the pc) = 0x00127F14 */
#define STRING_HASH_VER_OFFSET 0x00009100   /* was DAT_0011f228 (word at 0x0011F228); PC-relative offset: + 0x11ee0c (the pc) = 0x00127F0C */
#define DATA_AT_00127ED4_OFFSET 0x000090B0   /* was DAT_0011f22c (word at 0x0011F22C); PC-relative offset: + 0x11ee24 (the pc) = 0x00127ED4 */
#define DATA_AT_00127F4C_OFFSET 0x0000903C   /* was DAT_0011f230 (word at 0x0011F230); PC-relative offset: + 0x11ef10 (the pc) = 0x00127F4C */
#define DATA_AT_00127F58_OFFSET 0x00009018   /* was DAT_0011f234 (word at 0x0011F234); PC-relative offset: + 0x11ef40 (the pc) = 0x00127F58 */
#define DATA_AT_00127F48_OFFSET 0x00008FC0   /* was DAT_0011f238 (word at 0x0011F238); PC-relative offset: + 0x11ef88 (the pc) = 0x00127F48 */
#define DATA_AT_00127F50_OFFSET 0x00008FAC   /* was DAT_0011f23c (word at 0x0011F23C); PC-relative offset: + 0x11efa4 (the pc) = 0x00127F50 */
#define DATA_AT_00127F54_OFFSET 0x00008F94   /* was DAT_0011f240 (word at 0x0011F240); PC-relative offset: + 0x11efc0 (the pc) = 0x00127F54 */
#define DATA_AT_00127F5C_OFFSET 0x00008F80   /* was DAT_0011f244 (word at 0x0011F244); PC-relative offset: + 0x11efdc (the pc) = 0x00127F5C */
#define DATA_AT_00127F60_OFFSET 0x00008F68   /* was DAT_0011f248 (word at 0x0011F248); PC-relative offset: + 0x11eff8 (the pc) = 0x00127F60 */
#define DATA_AT_00127F64_OFFSET 0x00008F50   /* was DAT_0011f24c (word at 0x0011F24C); PC-relative offset: + 0x11f014 (the pc) = 0x00127F64 */
#define DATA_AT_00127F68_OFFSET 0x00008F38   /* was DAT_0011f250 (word at 0x0011F250); PC-relative offset: + 0x11f030 (the pc) = 0x00127F68 */
#define DATA_AT_00127F6C_OFFSET 0x00008F20   /* was DAT_0011f254 (word at 0x0011F254); PC-relative offset: + 0x11f04c (the pc) = 0x00127F6C */
#define DATA_AT_00127F70_OFFSET 0x00008F08   /* was DAT_0011f258 (word at 0x0011F258); PC-relative offset: + 0x11f068 (the pc) = 0x00127F70 */
#define DATA_AT_00127F74_OFFSET 0x00008EF0   /* was DAT_0011f25c (word at 0x0011F25C); PC-relative offset: + 0x11f084 (the pc) = 0x00127F74 */
#define INTEGER_31544 0x00007B38   /* was DAT_0011f390 (word at 0x0011F390); integer 31544 */
#define FLOAT_0_POINT_85 0x3F59999A   /* was DAT_0011f7d0 (word at 0x0011F7D0); the float 0.8500000238418579 */
#define INTEGER_29864 0x000074A8   /* was DAT_0011fc7c (word at 0x0011FC7C); integer 29864 */
#define WORD_HEXADECIMAL_FFFE01FC 0xFFFE01FC   /* was DAT_0011fed0 (word at 0x0011FED0); value 0xFFFE01FC (-130564) */
#define DATA_AT_001278E8_OFFSET_2 0x00007AC4   /* was DAT_0011fed4 (word at 0x0011FED4); PC-relative offset: + 0x11fe24 (the pc) = 0x001278E8 */
#define WORD_HEXADECIMAL_FFFE00F0 0xFFFE00F0   /* was DAT_0011ffbc (word at 0x0011FFBC); value 0xFFFE00F0 (-130832) */
#define DATA_AT_001278E8_OFFSET_3 0x00007808   /* was DAT_0012011c (word at 0x0012011C); PC-relative offset: + 0x1200e0 (the pc) = 0x001278E8 */
#define WORD_HEXADECIMAL_FFFDFEBC 0xFFFDFEBC   /* was DAT_001201c8 (word at 0x001201C8); value 0xFFFDFEBC (-131396) */
#define STRING_DEATH_DOT_MID_OFFSET 0x00007C64   /* was DAT_00120438 (word at 0x00120438); PC-relative offset: + 0x120344 (the pc) = 0x00127FA8 */
#define STRING_TRAINING_DOT_MID_OFFSET 0x00007C14   /* was DAT_0012043c (word at 0x0012043C); PC-relative offset: + 0x120368 (the pc) = 0x00127F7C */
#define WORD_HEXADECIMAL_FFFDFC48 0xFFFDFC48   /* was DAT_00120440 (word at 0x00120440); value 0xFFFDFC48 (-132024) */
#define STRING_TRAINING_OFFSET_4 0x00007BB0   /* was DAT_00120444 (word at 0x00120444); PC-relative offset: + 0x1203dc (the pc) = 0x00127F8C */
#define STRING_DOT_MID_OFFSET 0x00007B98   /* was DAT_00120448 (word at 0x00120448); PC-relative offset: + 0x120408 (the pc) = 0x00127FA0 */
#define STRING_PERCENT_S_PERCENT_S_OFFSET 0x00007B88   /* was DAT_0012044c (word at 0x0012044C); PC-relative offset: + 0x120410 (the pc) = 0x00127F98 */
#define ADDRESS_OF_FUNCTION_001242b4_OFFSET_3 0x00003D20   /* was DAT_00120598 (word at 0x00120598); PC-relative offset: + 0x120594 (the pc) = 0x001242B4 */
#define STRING_DEADEND_OFFSET 0x00006BB4   /* was DAT_00120f88 (word at 0x00120F88); PC-relative offset: + 0x120c14 (the pc) = 0x001277C8 */
#define WORD_HEXADECIMAL_009660B3 0x009660B3   /* was DAT_00121124, DAT_001213e0 (word at 0x00121124); value 0x009660B3 (9855155) */
#define WORD_HEXADECIMAL_019E5BAF 0x019E5BAF   /* was DAT_00121128 (word at 0x00121128); value 0x019E5BAF (27155375) */
#define STRING_DEADEND_OFFSET_2 0x00006760   /* was DAT_00121130 (word at 0x00121130); PC-relative offset: + 0x121068 (the pc) = 0x001277C8 */
#define STRING_MOTIONENTITY_OFFSET 0x000065EC   /* was DAT_001213e4 (word at 0x001213E4); PC-relative offset: + 0x12119c (the pc) = 0x00127788 */
#define STRING_COMBATREGION_OFFSET 0x000065C8   /* was DAT_001213e8 (word at 0x001213E8); PC-relative offset: + 0x1211d0 (the pc) = 0x00127798 */
#define STRING_BOSSCOMBATREGION_OFFSET 0x000065A4   /* was DAT_001213ec (word at 0x001213EC); PC-relative offset: + 0x121204 (the pc) = 0x001277A8 */
#define STRING_NOPARENT_OFFSET 0x00006578   /* was DAT_001213f0 (word at 0x001213F0); PC-relative offset: + 0x121244 (the pc) = 0x001277BC */
#define STRING_DEADEND_OFFSET_3 0x00006534   /* was DAT_001213f8 (word at 0x001213F8); PC-relative offset: + 0x121294 (the pc) = 0x001277C8 */
#define WORD_HEXADECIMAL_FFFDE350 0xFFFDE350   /* was DAT_00122438 (word at 0x00122438); value 0xFFFDE350 (-138416) */
#define STRING_PLAYARRIVEANIM_OFFSET 0x00004C44   /* was DAT_00122444 (word at 0x00122444); PC-relative offset: + 0x122254 (the pc) = 0x00126E98 */
#define WORD_HEXADECIMAL_1A5C2C12 0x1A5C2C12   /* was DAT_00122448 (word at 0x00122448); value 0x1A5C2C12 (442248210) */
#define INTEGER_1002 0x000003EA   /* was DAT_00122b88 (word at 0x00122B88); integer 1002 */
#define INTEGER_1003 0x000003EB   /* was DAT_00122b8c (word at 0x00122B8C); integer 1003 */
#define WORD_HEXADECIMAL_11E3EE3E 0x11E3EE3E   /* was DAT_00123128 (word at 0x00123128); value 0x11E3EE3E (300150334) */
#define WORD_HEXADECIMAL_3FC90FD8 0x3FC90FD8   /* was DAT_00123568 (word at 0x00123568); value 0x3FC90FD8 (1070141400) */
#define WORD_HEXADECIMAL_47AE147B 0x47AE147B   /* was DAT_0012356c (word at 0x0012356C); value 0x47AE147B (1202590843) */
#define FLOAT_1_POINT_035 0x3F847AE1   /* was DAT_00123570 (word at 0x00123570); the float 1.034999966621399 */
#define WORD_HEXADECIMAL_22735D97 0x22735D97   /* was DAT_00123c10 (word at 0x00123C10); value 0x22735D97 (577985943) */
#define WORD_HEXADECIMAL_1812C1C3 0x1812C1C3   /* was DAT_00123c20 (word at 0x00123C20); value 0x1812C1C3 (403882435) */
#define INTEGER_4467 0x00001173   /* was DAT_001242b0 (word at 0x001242B0); integer 4467 */
#define WORD_HEXADECIMAL_FFFDBD34 0xFFFDBD34   /* was DAT_00124650 (word at 0x00124650); value 0xFFFDBD34 (-148172) */
#define ADDRESS_OF_FUNCTION_001242b4_OFFSET_4 0xFFFFFCCC   /* was DAT_00124660 (word at 0x00124660); PC-relative offset: + 0x1245e8 (the pc) = 0x001242B4 */
#define STRING_SAVEGAME_DOT_DAT_OFFSET_5 0x00003438   /* was DAT_00124664 (word at 0x00124664); PC-relative offset: + 0x124610 (the pc) = 0x00127A48 */
#define DATA_AT_001278E8_OFFSET_4 0x00003198   /* was DAT_00124794 (word at 0x00124794); PC-relative offset: + 0x124750 (the pc) = 0x001278E8 */
#define WORD_HEXADECIMAL_04000088 0x04000088   /* was DAT_00124950 (word at 0x00124950); value 0x04000088 (67109000) */
#define WORD_HEXADECIMAL_04000012 0x04000012   /* was DAT_00124e14 (word at 0x00124E14); value 0x04000012 (67108882) */
#define WORD_HEXADECIMAL_7FF00000 0x7FF00000   /* was DAT_001254c8, DAT_001259e0 (word at 0x001254C8); value 0x7FF00000 (2146435072) */
#define WORD_HEXADECIMAL_08000014 0x08000014   /* was DAT_001254cc (word at 0x001254CC); value 0x08000014 (134217748) */
#define WORD_HEXADECIMAL_04000014 0x04000014   /* was DAT_001254d0 (word at 0x001254D0); value 0x04000014 (67108884) */
#define WORD_HEXADECIMAL_04120019 0x04120019   /* was DAT_00125550 (word at 0x00125550); value 0x04120019 (68288537) */
#define WORD_HEXADECIMAL_040200C8 0x040200C8   /* was DAT_001255f4 (word at 0x001255F4); value 0x040200C8 (67240136) */
#define WORD_HEXADECIMAL_04130019 0x04130019   /* was DAT_001256b0 (word at 0x001256B0); value 0x04130019 (68354073) */
#define WORD_HEXADECIMAL_04160019 0x04160019   /* was DAT_00125730 (word at 0x00125730); value 0x04160019 (68550681) */
#define WORD_HEXADECIMAL_07FF0000 0x07FF0000   /* was DAT_001259dc, DAT_00125cc8 (word at 0x001259DC); value 0x07FF0000 (134152192); also
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
#define DOUBLE_1_POINT_72879609_TIMES_TEN_TO_THE_MINUS_20_LOW_WORD 0x2FDE3CD0   /* was DAT_00102b78 (word at 0x00102B78); with the word at 0x00102B7C: the double 1.728796089680687e-20 = 0x3BD468F72FDE3CD0 */
#define DOUBLE_1_POINT_72879609_TIMES_TEN_TO_THE_MINUS_20_HIGH_WORD 0x3BD468F7   /* was DAT_00102b7c (word at 0x00102B7C); with the word at 0x00102B78: the double 1.728796089680687e-20 = 0x3BD468F72FDE3CD0 */
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
   Each was a Ghidra DAT_<address> label. PC-relative offsets (used as NAME + pc) are named after
   what they point to; other words are named after their value. The comment gives the old label(s),
   the word's address and how the name was derived. Generated, not reviewed one by one: names say
   what a word IS (its value or target), not necessarily what the code uses it for. */
#define WORD_HEXADECIMAL_3B4C67C7 0x3B4C67C7   /* was DAT_00102b58 (word at 0x00102B58); value 0x3B4C67C7 (994863047); r2 of FUN_00109a10 at LAB_001024bc in FUN_00101ad8 */
#define WORD_HEXADECIMAL_0B259095 0x0B259095   /* was DAT_00104c0c (word at 0x00104C0C); value 0x0B259095 (187011221); r2 of FUN_00109a10 in FUN_00101ad8 cases 0x29..0x2c */
#define DOUBLE_4_POINT_5_LOW_WORD 0x00000000   /* was DAT_0010f86c (word at 0x0010F86C); with the word at 0x0010F870: the double 4.5 = 0x4012000000000000 */
#define DOUBLE_4_POINT_5_HIGH_WORD 0x40120000   /* was DAT_0010f870 (word at 0x0010F870); with the word at 0x0010F86C: the double 4.5 = 0x4012000000000000 */
#define WORD_HEXADECIMAL_083D247B 0x083D247B   /* was DAT_001117c8 (word at 0x001117C8); value 0x083D247B (138224763) */
#define WORD_HEXADECIMAL_14F1CDC1 0x14F1CDC1   /* was DAT_00114b44 (word at 0x00114B44); value 0x14F1CDC1 (351391169) */
#define WORD_HEXADECIMAL_262A32C2 0x262A32C2   /* was DAT_0011cfd4 (word at 0x0011CFD4); value 0x262A32C2 (640299714) */
#define WORD_HEXADECIMAL_03AD1271 0x03AD1271   /* was DAT_00123564 (word at 0x00123564); value 0x03AD1271 (61674097) */
#define WORD_HEXADECIMAL_14FF65C5 0x14FF65C5   /* was DAT_00123c14 (word at 0x00123C14); value 0x14FF65C5 (352282053) */
#define WORD_HEXADECIMAL_25491361 0x25491361   /* was DAT_00123c18 (word at 0x00123C18); value 0x25491361 (625546081) */
#define WORD_HEXADECIMAL_38618576 0x38618576   /* was DAT_0012466c (word at 0x0012466C); value 0x38618576 (945915254) */
#define WORD_HEXADECIMAL_262EA0D8 0x262EA0D8   /* was DAT_00124670 (word at 0x00124670); value 0x262EA0D8 (640590040) */

#endif /* KH_MOD_H */
