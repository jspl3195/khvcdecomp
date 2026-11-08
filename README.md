# khvcdecomp

A decompilation of KH V-CAST, the BREW game, into C.

This repository contains no game assets, only C reconstructed from the game's machine code. The code was decompiled with [Ghidra](https://github.com/nationalsecurityagency/ghidra) and AI tools. Function names and types are recovered over time; a `GUESS:` comment marks a name or meaning that is inferred, not certain. The code has not been built against the BREW SDK or recompiled to machine code.

This work was possible thanks to [khvcemu](https://github.com/khrecast/khvcemu).

## Contents

| File | What it is |
|---|---|
| `kh_mod.c`, `kh_mod.h` | kh.mod, the game applet: 455 functions, with globals and prototypes |
| `kh_types.h` | the game's structures (application, characters, enemies, levels, ...) |
| `common.h` | the types and macros both modules' headers share: Ghidra's type names, the 64-bit word types and their macros |
| `swv21brew.c`, `swv21brew.h` | swv21brew.mod, the Swerve 3D engine 2.1 the game loads: 1307 functions |
| `swv_types.h` | Swerve types and class IDs |
| `brew_types.h` | the BREW interfaces both modules use (IShell, IDisplay, the helper table, ...) |

Each function starts with a banner that gives its address in the module and its offset in the file:

```c
/* ==== 0x00124954  (file offset 0x24954)  FUN_00124954 ==== */
```

## Target C version

`kh_mod.c` is written in **strict C90 (ISO/IEC 9899:1990), without compiler extensions**. That is the language of the ARM C compiler the game was built with.

It is checked with:

```sh
gcc -std=c90 -pedantic -fsyntax-only kh_mod.c
```

This must give no errors and no `-Wpedantic`, `-Wlong-long`, `-Woverflow` or shift-width warnings. The warnings that remain come from Ghidra's types, mostly an integer passed where a pointer is expected, and are being fixed function by function.

`swv21brew.c` is still Ghidra's raw output and does not compile yet; it will be brought to the same standard.

## Conventions

- **64-bit values.** C90 has no 64-bit integer type, so a 64-bit value is two 32-bit words, as the ARM code holds it in r0:r1:

  ```c
  typedef struct uint64 { uint32 low; uint32 high; } uint64;   /* Ghidra's ulonglong; undefined8 is uint64 */
  typedef struct int64 { uint32 low; int32 high; } int64;      /* Ghidra's longlong: a distinct type */
  ```

  The 64-bit arithmetic is done with macros in `kh_mod.h`: `MAKE_WORDS`, `MULTIPLY_WORDS`, `ADD_WORDS`, `SUBTRACT_WORDS`, `SUBTRACT_WORD` and `SHIFT_LEFT_WORDS`. The double-precision routines return their result this way.
- **Floating point.** The phones had no FPU, and the game does its float and double arithmetic in its own soft-float routines. Floats are kept as their 32-bit patterns (`uint32`), and doubles as two words.
- **Shifts by a variable count.** The binary uses the count's low byte, and a count of 32 or more gives 0 (or the sign, for an arithmetic shift). C leaves such a shift undefined, so these shifts are written with the macros `SHIFT_LEFT`, `SHIFT_RIGHT` and `SHIFT_RIGHT_SIGNED`. The carry and overflow tests are `ADD_CARRIES`, `ADD_OVERFLOWS` and `SUBTRACT_OVERFLOWS`, and the leading-zero count is `LEADING_ZEROS`. All of these are macros, not calls.
- **Returns.** Where the binary returns through the caller's link register with the result already in r0:r1, the code is a plain `return`.
- **Tail jumps.** Where the binary ends a function by jumping into another function, the code calls that function, even when Ghidra pasted the target's code inline.
- **Stack buffers.** A stack area whose address the code passes on is a typed local, such as an `AEERect`, an `AEEImageInfo` or a `uint32` vector.
- **Data.** The binary reaches its read-only data through offsets from the program counter. In the C, each address the code takes is an object at the end of `kh_mod.h`. Strings are string literals, and other data are arrays of words or bytes reaching to the next such address; the comment gives the address. A function's address is the function itself.
- **Vtables.** The game's own objects use vtables whose entries hold the method's offset from the table (0x00101650–0x00101743). In the C they are arrays of function pointers (`VTABLE_<address>`), and a call through them is `(*(code *)*(int *)(*object + slot))(object)`. Methods and routines that Ghidra has no function for are written from the disassembly and say so in their comment.
- **Compares in the flags.** The soft-float compares leave their result in the CPU flags. The listing writes such a compare as `(float_compare_greater(a,b), *(float *)&a > *(float *)&b)`.
- **Rewritten functions.** Functions that have been cleaned up have named, typed parameters, no `goto`, and the same calls as the binary, with none added or removed.
- **Ghidra names.** Names such as `FUN_<address>`, `uVar3` and `param_1` are Ghidra's and have not been reviewed yet.

## Dependencies

The code shows it was built against these libraries:

| Library | Module | Evidence |
|---|---|---|
| libpng 1.2.0 | swv21brew.mod (the PNG decoder) | the version string `"1.2.0"` (0x0103FAA4) passed to the read struct's constructor (FUN_0103586c, GUESS: `png_create_read_struct`), its "Incompatible libpng version in application and library" check, and routines that match libpng 1.2.0's source (`png_sig_cmp`, `png_warning`) |
| zlib (version not yet identified) | swv21brew.mod (libpng's inflate) | libpng's "zlib version error" / "zlib memory error" messages |

## Known code

Some routines are known code, recognised from their structure. Their comments name the source:

| Routine | Source |
|---|---|
| `collision_shape_turn_direction` (0x00113da4) | Franklin Antonio's segment intersection test, "Faster Line Segment Intersection", *Graphics Gems III* (1992) |
| the double-precision `acos`, `sin`, `cos` and their kernels | fdlibm: `__ieee754_acos`, `__ieee754_rem_pio2`, `__kernel_sin`, `__kernel_cos`, `sin`, `cos` |
| `rt_div0`, the word `memcpy` / `memclr` | the ARM C library: `__rt_div0`, `__rt_memcpy_w`, `__rt_memclr_w` |
| swv21brew's `ll_mul` (0x0100094c) and `ll_mul_int` (0x01000028) | the ARM C library's 64-bit multiply, `_ll_mul` (`__aeabi_lmul` in later ABIs) |
| swv21brew's `swv_memcmp` (0x01000080) | `memcmp` (GUESS: the ARM C library's, from its shape) |
| swv21brew's PNG decoder: `png_sig_cmp` (0x01037e48), `png_warning` (0x01037eb0), ... | libpng 1.2.0 (its version string); its inflate is zlib |

## Status

Many of kh.mod's functions are still Ghidra's output with renamed constants and comments. The rest have been rewritten.

The soft-float routines (single and double precision) have been checked against the original binary under emulation and give the same results on hundreds of thousands of cases each.
