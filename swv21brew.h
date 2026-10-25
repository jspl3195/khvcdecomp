/*
 * swv21brew.h - swv21brew.mod (Swerve 3D engine 2.1.0.364, class 0x0102bbfc): types, globals and prototypes
 *
 * Source module : dumps/mod/14957/swv21brew.mod (273188 bytes)
 * SHA-256       : 1e76412e158bc3948bf6ad173b181368e0f0d554d6b0e1488a29402d96b0cdab
 * Ghidra base   : 0x01000000 (= khvcemu load address); file offset = address - 0x1000000
 * Functions     : 1305 from Ghidra + hand-written ones Ghidra has no function for
 * Loaded by khvcemu on kh.mod's first ISHELL_CreateInstance(0x0102bbfc) (khvcemu/runtime.py:267-288).
 * Calls into it: AEEMod_Load, AEEMod_CreateInstance, then the ISwerve / engine-object vtables from kh.mod.
 * This is the original code: khvcemu's speed patches (khvcemu/swerve_patch.py) are not applied or referenced.
 * 112 vtable methods were turned into functions by ghidra_scripts/CreateFunctionsFromList.java.
 * Class names: see SwerveClassId in swv_types.h; per-class vtable slots beyond the shared 3 are not named yet.
 */

#ifndef SWV21BREW_H
#define SWV21BREW_H

#include "brew_types.h"
#include "swv_types.h"

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

/* AEEHelperFuncs pointer stored by khvcemu (and the real BREW loader) at module base - 4. */
extern AEEHelperFuncs *g_pHelperFuncs;   /* 0x00FFFFFC */

/* ---- prototypes, address order ---------------------------------------------------- */

/* Named functions (entry points, SDK glue, helper wrappers, identified game code). */
int AEEMod_Load(IShell *pIShell,AEEHelperFuncs *ph,IModule **ppMod);   /* 0x01000000 */
undefined4 swv_memset(undefined4 param_1,uint param_2,undefined4 param_3);   /* 0x0100010C */
undefined4 * swv_memzero(undefined4 *param_1,uint param_2);   /* 0x01000130 */
longlong swv_setjmp(undefined4 *param_1);   /* 0x01000500 */
uint32 AEEMod_AddRef(IModule *po);   /* 0x010028C8 */
int AEEMod_CreateInstance(IModule *po,IShell *pIShell,AEECLSID ClsId,void **ppObj);   /* 0x010028DC */
uint32 AEEMod_Release(IModule *po);   /* 0x01002910 */
int AEEStaticMod_New(int16 nSize,IShell *pIShell,AEEHelperFuncs *ph,IModule **ppMod,void *pfnMC, void *pfnMF);   /* 0x0100297C */
void swv_TryArm(int param_1);   /* 0x0100500C */
int swv_Graphics3D_New(void);   /* 0x010098A4 */
void swv_SpanFillGeneric(int param_1);   /* 0x0100A8B4 */
void swv_SpanFillFlat(int param_1);   /* 0x0100B18C */
void swv_SpanFillTextured(int param_1);   /* 0x0100DFEC */
uint32 swvObj_AddRef(ISwerveObject *po);   /* 0x01011F8C */
int swvObj_QueryInterface(ISwerveObject *po,SwerveClassId cls,void **ppo);   /* 0x01011FC4 */
uint32 swvObj_Release(ISwerveObject *po);   /* 0x01012294 */
undefined4 swv_Matrix4Invert(int param_1);   /* 0x0101376C */
void swv_NativeRelease(int *param_1);   /* 0x01019F28 */
void swv_Graphics3D_bindTarget (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8, undefined4 param_9);   /* 0x010202E4 */
uint32 ISwerve_AddRef(ISwerve *po);   /* 0x01024788 */
int ISwerve_CreateObject(ISwerve *po,SwerveClassId cls,void **ppObj);   /* 0x0102479C */
uint32 ISwerve_Release(ISwerve *po);   /* 0x01024978 */
void ISwerve_GetPixelFormat(ISwerve *po,SwervePixelFormat *pFmt);   /* 0x01024A1C */
void ISwerve_GetVersion(ISwerve *po,SwerveVersion *pVer);   /* 0x01024A68 */
int swv_TryPush(int param_1);   /* 0x01025E98 */
void swv_TryPop(void);   /* 0x01026298 */
void helper_free(void *p);   /* 0x01029908 */
void helper_free(void *p);   /* 0x01029910 */
void * helper_malloc(uint32 size);   /* 0x0102CBF8 */
void * helper_malloc(uint32 size);   /* 0x0102CBFC */
void * swv_New(uint32 param_1);   /* 0x0102CC00 */
int swv_GetFpStatusPtr(void);   /* 0x0102CC70 */
int swv_Create_AnimationController(void **ppObj);   /* 0x0102CDFC */
void swv_InitVtbl_AnimationController(void **pVtbl);   /* 0x0102CEE4 */
int swv_Create_AnimationTrack(void **ppObj);   /* 0x0102D160 */
void swv_InitVtbl_AnimationTrack(void **pVtbl);   /* 0x0102D2B0 */
int swv_Create_Appearance(void **ppObj);   /* 0x0102D3CC */
void swv_InitVtbl_Appearance(void **pVtbl);   /* 0x0102D678 */
int swv_Create_Ext100(void **ppObj);   /* 0x0102D8AC */
int swv_Create_Ext101(void **ppObj);   /* 0x0102D990 */
int swv_Create_Background(void **ppObj);   /* 0x0102DA7C */
void swv_InitVtbl_Background(void **pVtbl);   /* 0x0102DC40 */
int swv_Create_Camera(void **ppObj);   /* 0x0102E00C */
void swv_InitVtbl_Camera(void **pVtbl);   /* 0x0102E150 */
int swv_Create_CompositingMode(void **ppObj);   /* 0x0102E44C */
void swv_InitVtbl_CompositingMode(void **pVtbl);   /* 0x0102E50C */
int swv_Create_Fog(void **ppObj);   /* 0x0102E9E0 */
void swv_InitVtbl_Fog(void **pVtbl);   /* 0x0102EABC */
void swv_SetGlobal00(uint32 value);   /* 0x0102ECE8 */
uint32 swv_GetGlobal00(void);   /* 0x0102F464 */
int swv_Create_Graphics3D(void **ppObj);   /* 0x0102F904 */
void swv_InitVtbl_Graphics3D(void **pVtbl);   /* 0x0102FA30 */
int IGraphics3D_BindTarget (IGraphics3D *po,uint16 cx,uint16 cy,int nPitch,void *pBits,int x,int y,int dx,int dy);   /* 0x0102FF38 */
int swv_Create_Group(void **ppObj);   /* 0x0103028C */
void swv_InitVtbl_Group(void **pVtbl);   /* 0x01030380 */
int swv_Create_Image2D(void **ppObj);   /* 0x01030A4C */
void swv_InitVtbl_Image2D(void **pVtbl);   /* 0x01030B84 */
int swv_Create_KeyframeSequence(void **ppObj);   /* 0x01032A60 */
void swv_InitVtbl_KeyframeSequence(void **pVtbl);   /* 0x01032AF0 */
int swv_Create_Light(void **ppObj);   /* 0x01032DF8 */
void swv_InitVtbl_Light(void **pVtbl);   /* 0x01032F1C */
int swv_Create_Loader(void **ppObj);   /* 0x01033634 */
void swv_InitVtbl_Loader(void **pVtbl);   /* 0x01033764 */
int swv_Create_Material(void **ppObj);   /* 0x010339C4 */
void swv_InitVtbl_Material(void **pVtbl);   /* 0x01033AC4 */
int swv_Create_Mesh(void **ppObj);   /* 0x01033C6C */
void swv_InitVtbl_Mesh(void **pVtbl);   /* 0x01033E44 */
int swv_Create_MorphingMesh(void **ppObj);   /* 0x01034200 */
void swv_InitVtbl_MorphingMesh(void **pVtbl);   /* 0x01034384 */
int swv_Create_PolygonMode(void **ppObj);   /* 0x01037F40 */
void swv_InitVtbl_PolygonMode(void **pVtbl);   /* 0x01038000 */
int swv_Create_RayIntersection(void **ppObj);   /* 0x010382E0 */
void swv_InitVtbl_RayIntersection(void **pVtbl);   /* 0x01038590 */
int swv_Create_SkinnedMesh(void **ppObj);   /* 0x01038818 */
void swv_InitVtbl_SkinnedMesh(void **pVtbl);   /* 0x010388E4 */
int swv_Create_Sprite3D(void **ppObj);   /* 0x01038C2C */
void swv_InitVtbl_Sprite3D(void **pVtbl);   /* 0x01038DC4 */
int swv_Create_Class24(void **ppObj);   /* 0x0103927C */
void swv_InitVtbl_Class24(void **pVtbl);   /* 0x0103930C */
void * helper_malloc(uint32 size);   /* 0x01039598 */
undefined4 swv_ErrorToResult(int param_1);   /* 0x0103976C */
void helper_free(void *p);   /* 0x010398D0 */
uint32 swv_GetGlobal00(void);   /* 0x01039910 */
ISwerve * swv_GetSwerveObject(void);   /* 0x01039938 */
void * helper_GetAppInstance(void);   /* 0x01039960 */
SwerveGlobals * swv_GetGlobals(void);   /* 0x01039978 */
void ** swv_GetVtblCache(void);   /* 0x0103999C */
undefined4 swv_memset(undefined4 param_1,uint param_2,undefined4 param_3);   /* 0x01039DF0 */
int swv_NewSwerve(int16 nSize,IShell *pIShell,IModule *pIModule,ISwerve **ppObj);   /* 0x01039DF4 */
int swv_WrapObject(void *pNative,ISwerveObject **ppOut);   /* 0x01039FB4 */
void swv_SetGlobal00(uint32 value);   /* 0x0103AF88 */
int swv_Create_Texture2D(void **ppObj);   /* 0x0103B200 */
void swv_InitVtbl_Texture2D(void **pVtbl);   /* 0x0103B32C */
int swv_Create_Transform(void **ppObj);   /* 0x0103B68C */
void swv_InitVtbl_Transform(void **pVtbl);   /* 0x0103B768 */
int swv_Create_TriangleStripArray(void **ppObj);   /* 0x0103C81C */
void swv_InitVtbl_TriangleStripArray(void **pVtbl);   /* 0x0103C87C */
int swv_Create_VertexArray(void **ppObj);   /* 0x0103C9C4 */
void swv_InitVtbl_VertexArray(void **pVtbl);   /* 0x0103CA24 */
int swv_Create_VertexBuffer(void **ppObj);   /* 0x0103CC48 */
void swv_InitVtbl_VertexBuffer(void **pVtbl);   /* 0x0103CEB0 */
int swv_Create_World(void **ppObj);   /* 0x0103D18C */
void swv_InitVtbl_World(void **pVtbl);   /* 0x0103D2C4 */
uint swv_f2d(uint param_1,uint param_2,undefined4 param_3,uint param_4);   /* 0x0103EE80 */
uint swv_fadd(uint param_1,uint param_2,undefined4 param_3,uint param_4);   /* 0x0103EEE8 */
uint swv_frsb(uint param_1,uint param_2,undefined4 param_3,uint param_4);   /* 0x0103F030 */
uint swv_fsub(uint param_1,uint param_2,undefined4 param_3,uint param_4);   /* 0x0103F064 */
uint swv_frdiv(uint param_1,uint param_2,undefined4 param_3,uint param_4);   /* 0x0103F240 */
uint swv_fdiv(uint param_1,uint param_2,undefined4 param_3,uint param_4);   /* 0x0103F250 */
uint swv_fcmp_a(uint param_1,uint param_2,undefined4 param_3,uint param_4);   /* 0x0103F428 */
uint swv_ffix(uint param_1);   /* 0x0103F490 */
uint swv_ffltu(int param_1);   /* 0x0103F4F8 */
uint swv_fflt(uint param_1);   /* 0x0103F500 */
uint swv_fcmp_b(uint param_1,uint param_2,undefined4 param_3,uint param_4);   /* 0x0103F534 */
uint swv_fcmp_c(uint param_1,uint param_2,undefined4 param_3,uint param_4);   /* 0x0103F59C */
uint swv_fmul(uint param_1,uint param_2,undefined4 param_3,uint param_4);   /* 0x0103F604 */
void swv_fp_status(uint param_1,uint param_2);   /* 0x0103F8E8 */

/* No Ghidra function exists for these; bodies are hand-written in the .c file. */
int AEEClsCreateInstance(AEECLSID ClsId, IShell *pIShell, IModule *po, void **ppObj);
void AEEMod_FreeResources(IModule *po, IHeap *ph, IFileMgr *pfm);

/* Not yet identified (auto-named by Ghidra). */
undefined8 FUN_01000028(uint param_1,int param_2,uint param_3);
int FUN_01000080(byte *param_1,byte *param_2,uint param_3);
undefined4 FUN_01000100(undefined4 param_1);
undefined8 FUN_01000188(byte *param_1,byte *param_2,uint param_3,undefined4 param_4);
ulonglong FUN_010001f4(uint param_1,uint param_2);
int FUN_010002c8(uint param_1,uint param_2);
void FUN_01000388(int param_1,int param_2,int param_3,uint param_4);
void FUN_010003cc(int param_1,int param_2,int param_3,uint param_4);
int * FUN_01000414(int *param_1,int param_2,int param_3,int param_4,uint param_5);
longlong FUN_01000474(int param_1,uint param_2,uint param_3,uint param_4);
void FUN_01000524(int param_1,int param_2);
undefined4 FUN_01000550(int param_1,uint param_2);
undefined4 FUN_0100062c(undefined4 param_1,undefined4 param_2,undefined4 param_3,uint param_4);
undefined4 FUN_01000728(int param_1,uint param_2);
undefined4 FUN_01000810(uint param_1,uint param_2,undefined4 param_3,undefined4 param_4);
undefined4 FUN_01000880(int param_1,uint param_2);
void FUN_01000938(undefined4 param_1);
ulonglong FUN_01000964(uint param_1,uint param_2,uint param_3,uint param_4);
void FUN_01000c24(void);
undefined4 FUN_01000c30(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
undefined4 * FUN_01000c54(undefined4 *param_1,uint param_2,undefined4 param_3);
undefined8 FUN_01000c94(uint *param_1,uint *param_2,uint param_3,uint param_4);
undefined4 FUN_01000d48(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4);
void FUN_01000f1c(int param_1,uint param_2,int *param_3);
int FUN_01000f94(undefined4 param_1,uint param_2,undefined8 *param_3);
undefined4 FUN_01001474(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4,int param_5);
uint FUN_010015ec(uint param_1,uint param_2,undefined4 param_3,uint param_4,int param_5);
undefined8 FUN_010019e0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, uint param_5);
void FUN_01001a40(void);
uint FUN_01001a58(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
undefined4 FUN_01001bb4(int param_1,char *param_2);
undefined8 FUN_01001d94(void);
void FUN_01002a58(int *param_1,int param_2,undefined4 param_3,undefined4 param_4);
int FUN_01002c70(int param_1,int param_2);
void FUN_01002d60(int param_1,int param_2);
undefined4 FUN_01002dfc(undefined1 *param_1,int param_2,int param_3);
void FUN_01002ef8(int param_1,int param_2,int param_3,undefined4 param_4,int param_5,int param_6);
void FUN_0100300c(int param_1,uint param_2,uint param_3,int param_4,int param_5,int *param_6);
void FUN_010031a0(int param_1,int param_2);
undefined8 FUN_01003234(int param_1,int param_2,int param_3,int param_4,int param_5);
int FUN_010033a4(int param_1,undefined4 param_2);
int FUN_01003408(int param_1);
void FUN_01003474(int param_1,undefined4 param_2);
void FUN_010034cc(int param_1,int param_2);
void FUN_0100350c(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_01003604(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_01003758(undefined4 param_1,int param_2);
void FUN_010037a0(undefined4 param_1,int param_2);
void FUN_010037f0(undefined4 param_1,int param_2);
void FUN_0100385c(undefined4 param_1,int param_2);
void FUN_010038c8(undefined4 param_1,int param_2);
int FUN_01003b00(int param_1,undefined4 param_2,int param_3,undefined4 param_4);
int FUN_01003be8(int param_1,undefined4 param_2,int param_3,undefined4 param_4);
undefined4 FUN_01003c38(int *param_1,undefined4 param_2,int param_3);
void FUN_0100400c(int *param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4);
void FUN_0100406c(int *param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4);
void FUN_010040cc(int *param_1,undefined1 *param_2,undefined4 param_3,undefined4 param_4);
void FUN_0100412c(int *param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4);
undefined4 * FUN_0100418c(int *param_1,undefined4 *param_2);
void FUN_010041ec(int param_1);
int FUN_01004200(void *param_1);
void FUN_01004250(int param_1,undefined4 param_2,uint param_3,undefined4 param_4);
void FUN_010042bc(int param_1);
undefined4 FUN_010042d0(int param_1,undefined4 *param_2,int *param_3);
int FUN_01004380(int param_1,undefined4 param_2);
int FUN_01004638(int param_1,undefined4 param_2,undefined4 *param_3,void **param_4);
int FUN_010047b0(int param_1,int param_2,int param_3);
int FUN_01004848(int param_1,int param_2);
int FUN_0100486c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
int FUN_010048e4(int param_1,int param_2,undefined4 param_3);
void FUN_01004a68(int param_1,int *param_2,int *param_3,int *param_4,int *param_5);
void FUN_01004b54(int param_1);
int FUN_01004c0c(int param_1);
int FUN_01004c30(int param_1);
void FUN_01004c4c(int param_1,int param_2);
void FUN_01004fb8(int *param_1);
void FUN_01005028(int param_1);
void FUN_010050ac(int param_1);
undefined4 FUN_01005104(int param_1,int param_2,int param_3);
void FUN_01005eb8(int param_1);
void FUN_01005f0c(int param_1);
void FUN_01005f28(int param_1,int param_2,int param_3,int param_4,int param_5);
void FUN_01005f88(int param_1,int param_2);
void FUN_01006020(int param_1);
void FUN_01006078(int param_1);
int FUN_01006240(int param_1,int param_2,uint param_3);
int FUN_01006438(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
int FUN_010064c4(int param_1,int param_2);
int FUN_01006518(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
int FUN_01006650(int param_1,int param_2);
int FUN_01006750(int param_1,int param_2);
int FUN_01006810(int param_1,int param_2);
int FUN_01006918(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
int FUN_01006a10(int param_1,int param_2);
int FUN_01006b38(int param_1,int param_2);
int FUN_01006c1c(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
undefined8 FUN_01006da4(int param_1,int param_2,int param_3,int param_4);
int FUN_01006efc(int param_1,int param_2);
int FUN_01006f8c(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
int FUN_01006fec(int param_1);
int FUN_01007064(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
int FUN_010070c4(int param_1);
int FUN_01007164(int param_1);
int FUN_01007210(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
int FUN_01007270(int param_1);
undefined8 FUN_0100732c(undefined4 param_1,undefined4 param_2,int param_3,int param_4);
int FUN_010073c8(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
int FUN_01007430(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
int FUN_0100748c(int param_1);
int FUN_01007554(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
int FUN_010075c4(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
int FUN_01007624(int param_1);
int FUN_010076e0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
int FUN_01007780(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
int FUN_01007864(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
int FUN_010078f4(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
int FUN_01007984(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
int FUN_01007a0c(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
int FUN_01007a7c(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
int FUN_01007aec(int param_1);
int FUN_01007b94(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
int FUN_01007c50(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
int FUN_01007d04(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_01007d70(int param_1,undefined4 param_2,uint param_3,uint param_4,int param_5,int param_6);
void FUN_01007e30(int param_1,undefined4 param_2,uint param_3,uint param_4,int param_5, undefined4 param_6,int param_7,int param_8);
void FUN_01007f40(int param_1,undefined4 param_2,uint param_3,uint param_4,int param_5);
undefined4 FUN_01007f8c(int param_1,int param_2,int param_3,int param_4,int param_5);
undefined4 FUN_0100800c(int param_1,undefined4 param_2,undefined4 param_3);
void thunk_FUN_01021abc(int param_1,int param_2);
void thunk_FUN_01023f30(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_0100806c(int param_1,undefined4 param_2);
void FUN_01008074(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_010080e4(int param_1);
void FUN_01008104(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6,int *param_7);
void FUN_01008144(int param_1,int param_2,int param_3,int param_4);
void FUN_01008184(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, int param_5,int param_6);
void FUN_010081ec(int param_1,undefined4 param_2,int param_3,int param_4,undefined4 param_5, undefined4 param_6,undefined4 param_7,undefined4 param_8);
void FUN_010082f0(int param_1,int param_2,undefined4 param_3);
uint FUN_0100835c(int param_1,undefined4 param_2);
void FUN_01008398(int param_1,int param_2,int param_3,int param_4);
void FUN_0100844c(int param_1,int param_2,int param_3,int param_4,int param_5);
void FUN_01008540(int param_1,int param_2,int param_3,int param_4);
void FUN_010085e8(void);
void FUN_01008624(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6);
void FUN_01008744(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
uint FUN_01008c54(undefined4 param_1,uint param_2,uint param_3,int param_4);
int FUN_01009638(int param_1,int param_2);
void FUN_0100973c(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6, int param_7,int param_8,int param_9,int param_10,int param_11,int param_12);
void FUN_01009860(int param_1);
int * FUN_010098fc(void);
int FUN_01009944(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
int FUN_010099a4(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_01009a04(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
int FUN_01009ad0(void);
int FUN_01009b80(void);
undefined4 FUN_01009bb8(int param_1,undefined4 param_2,undefined4 param_3);
void FUN_01009c20(void);
void FUN_01009c48(void);
void FUN_01009cb0(void);
void FUN_01009e54(int param_1);
uint * FUN_01009eac(int param_1,int param_2,int *param_3);
void FUN_0100a02c(int param_1,int param_2);
uint FUN_0100a470(int param_1,undefined4 param_2,undefined4 param_3);
void FUN_0100a624(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_0100a820(int param_1);
void FUN_0100ac0c(int param_1);
undefined4 FUN_0100b280(int param_1,int param_2);
void FUN_0100bae0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6);
void FUN_0100bb68(int param_1);
void FUN_0100c7a0(int param_1);
void FUN_0100c92c(int param_1);
void FUN_0100cef4(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_0100cf00(int param_1);
int FUN_0100e490(int param_1,int param_2,int param_3);
void FUN_0100e4e8(undefined4 *param_1);
int FUN_0100e5b0(void);
int * FUN_0100e5d4(void);
int * FUN_0100e63c(void);
int FUN_0100e6b8(void);
int FUN_0100e6dc(void);
int FUN_0100e700(void);
int * FUN_0100e724(void);
int FUN_0100e798(void);
int FUN_0100e7ec(void);
int * FUN_0100e810(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
int FUN_0100e900(void);
int FUN_0100e924(void);
int FUN_0100e948(void);
int FUN_0100e96c(void);
int FUN_0100e990(void);
void FUN_0100e9b4(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
int FUN_0100ea80(void);
int FUN_0100eaa4(void);
int FUN_0100eac8(void);
int FUN_0100eaec(void);
int FUN_0100eb10(void);
int FUN_0100eb34(void);
int FUN_0100eb58(void);
int * FUN_0100eb7c(void);
int FUN_0100ebf8(void);
int FUN_0100ec1c(void);
int * FUN_0100ec40(void);
void FUN_0100eca0(int param_1,int param_2,int param_3,int param_4,int param_5,undefined2 param_6, undefined1 param_7);
void FUN_0100ed84(int param_1,int param_2,int param_3);
uint FUN_0100edd4(int param_1,uint param_2,int param_3);
int * FUN_0100eef0(int *param_1,int param_2);
void FUN_0100efe4(int *param_1,int param_2);
void FUN_0100f030(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
int FUN_0100f154(int param_1);
undefined4 FUN_0100f170(int param_1);
undefined4 FUN_0100f184(int param_1,int param_2);
undefined4 FUN_0100f1c8(int param_1,int param_2);
void FUN_0100f1fc(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3,undefined4 param_4);
void FUN_0100f350(undefined4 *param_1,undefined4 param_2,undefined4 *param_3,undefined4 param_4);
void FUN_0100f3cc(undefined4 param_1,int param_2,undefined4 param_3,undefined4 *param_4);
void FUN_0100f450(undefined4 param_1,int param_2,undefined4 param_3,undefined4 *param_4);
undefined4 * FUN_0100f4dc(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
undefined4 FUN_0100f530(undefined4 param_1);
int FUN_0100f594(int param_1);
void FUN_0100f5b4(int param_1,int *param_2,int param_3);
undefined8 FUN_0100f5dc(undefined4 param_1,int param_2);
undefined4 FUN_0100f620(int param_1,int param_2);
void FUN_0100f654(int param_1,int param_2);
undefined4 FUN_0100f6d8(int param_1);
int FUN_0100f6f8(int param_1);
undefined4 FUN_0100f714(int param_1);
undefined4 FUN_0100f71c(int param_1);
undefined4 FUN_0100f734(int param_1,int param_2);
undefined4 FUN_0100f768(void);
undefined4 FUN_0100f780(void);
undefined4 FUN_0100f798(void);
undefined4 FUN_0100f7b0(void);
undefined4 FUN_0100f7d0(void);
undefined4 FUN_0100f7e0(void);
undefined4 FUN_0100f810(void);
undefined4 FUN_0100f8e8(void);
int FUN_0100f8f8(int param_1);
int FUN_0100f910(int param_1);
int FUN_0100f950(int param_1);
int FUN_0100f9e4(int param_1);
undefined4 FUN_0100f9f8(int param_1);
undefined4 FUN_0100fac0(int param_1);
int FUN_0100fb34(int param_1,int param_2);
int FUN_0100fdec(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
int FUN_0100fe8c(int param_1,int param_2);
int FUN_0100ffe4(int param_1);
int FUN_0100fffc(int param_1);
uint FUN_01010008(int *param_1);
void FUN_01010084(int *param_1);
uint FUN_01010094(int param_1,int param_2,undefined4 param_3,uint param_4);
undefined4 FUN_010100f0(int param_1,int param_2,undefined4 *param_3);
undefined8 FUN_01010148(int param_1,uint param_2);
undefined4 FUN_010102c8(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
undefined4 FUN_01010320(int param_1,int param_2,undefined4 *param_3);
void FUN_01010384(int param_1,int param_2,undefined4 *param_3);
int FUN_010103d4(int *param_1,int param_2,int *param_3);
undefined4 FUN_010104f0(int param_1);
undefined4 FUN_010106f8(int param_1);
void FUN_0101070c(int param_1,int param_2,int *param_3,undefined4 *param_4,undefined4 *param_5);
undefined4 FUN_01010818(int param_1);
undefined4 FUN_01010828(int param_1,uint param_2,int param_3,undefined4 *param_4);
bool FUN_010108d4(undefined4 param_1,undefined4 param_2,int param_3);
int FUN_01010924(int param_1,int param_2);
undefined4 FUN_01010938(int param_1);
uint FUN_01010cc8(int param_1);
int FUN_01010cf4(int param_1,int param_2,undefined4 param_3,int param_4);
int FUN_01010d40(int param_1,int param_2,undefined4 param_3,int param_4);
undefined4 FUN_01010dac(undefined4 param_1,int param_2);
undefined4 FUN_01010de0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5 );
void FUN_01010e84(int param_1,int param_2,int *param_3,undefined4 *param_4);
undefined4 FUN_01010f60(int param_1,int param_2);
undefined4 FUN_01010f90(int param_1);
undefined4 FUN_01010f98(int param_1,undefined4 param_2,int param_3,undefined4 *param_4,undefined4 param_5);
void FUN_01011900(int param_1,undefined4 *param_2,undefined4 *param_3);
void FUN_0101191c(int param_1,int param_2,undefined4 *param_3);
undefined4 FUN_01011960(int param_1);
undefined4 FUN_01011968(int param_1);
undefined4 FUN_01011980(int param_1);
undefined4 FUN_01011994(int param_1);
int FUN_010119a8(int param_1,int param_2,int param_3);
undefined4 FUN_010119d8(int param_1);
undefined4 FUN_010119e8(int param_1);
undefined4 FUN_010119fc(int param_1);
undefined4 FUN_01011a0c(int param_1);
void FUN_01011a20(int param_1,int param_2,undefined4 *param_3);
int FUN_01011a84(int param_1);
uint FUN_01011aa8(int param_1);
undefined4 FUN_01011ab8(int param_1);
int FUN_01011ae0(int param_1,int param_2);
int FUN_01011b4c(int param_1,int param_2);
int FUN_01011bb4(int param_1);
int FUN_01011be4(int param_1);
undefined4 FUN_01011bfc(int param_1,int param_2,int param_3);
void FUN_01011c20(undefined4 param_1,int param_2);
undefined4 FUN_01011c4c(int param_1,int param_2);
void FUN_01011cbc(undefined4 param_1,int param_2);
int FUN_01011ce8(int param_1,int param_2);
int FUN_01011d54(int param_1,int param_2);
undefined4 FUN_01011de0(int param_1,int param_2);
void FUN_01011e44(undefined4 *param_1,int param_2);
int FUN_01011e84(int param_1,int param_2);
void FUN_01011ee4(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void FUN_01011f0c(undefined4 *param_1,int param_2);
void FUN_01011f4c(undefined4 *param_1,int param_2);
undefined4 FUN_010122f0(undefined4 param_1,int param_2);
undefined4 FUN_01012324(void);
undefined4 FUN_0101232c(undefined4 param_1,int param_2);
undefined4 FUN_01012358(undefined4 param_1,int param_2);
undefined4 FUN_01012384(undefined4 param_1,int param_2);
undefined4 FUN_010123b0(undefined4 param_1,int param_2);
undefined4 FUN_010123dc(undefined4 param_1,int param_2);
undefined4 FUN_01012410(undefined4 param_1,int param_2);
undefined4 FUN_01012444(undefined4 param_1,int param_2);
undefined4 FUN_01012478(undefined4 param_1,int param_2);
undefined4 FUN_010124dc(undefined4 param_1,int param_2);
undefined4 FUN_01012508(int param_1,int param_2);
void FUN_01012568(undefined4 *param_1);
void FUN_010125e4(int param_1,uint param_2,undefined4 param_3,undefined4 param_4,undefined4 *param_5 );
void FUN_010126d0(void);
void FUN_01012758(void);
void * FUN_010127a4(void);
void FUN_010127fc(int param_1,uint param_2,undefined4 param_3,undefined4 param_4,undefined4 *param_5 ,undefined4 *param_6);
int FUN_01012908(int *param_1,int param_2,int param_3);
void FUN_0101303c(void);
undefined4 FUN_010130ac(void);
void FUN_01013214(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5);
void FUN_01013290(int *param_1,int param_2,undefined4 *param_3);
void FUN_01013368(int *param_1,int param_2,undefined4 *param_3);
undefined4 FUN_01013440(int *param_1,int *param_2);
undefined4 FUN_010134ec(undefined4 *param_1);
void FUN_01013744(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
undefined4 FUN_01013a80(int param_1,int param_2);
undefined4 FUN_01013ab0(int param_1,int param_2);
undefined4 FUN_01013ac8(int param_1,int param_2);
undefined4 FUN_01013af8(uint param_1);
undefined4 FUN_01013b34(int param_1,int param_2);
int FUN_01013bb4(int param_1);
void FUN_01013bcc(int param_1,undefined4 param_2);
void FUN_01013c58(int param_1,int param_2,int *param_3,int param_4);
void FUN_01013e88(int param_1,int param_2);
void FUN_0101411c(int param_1,int param_2);
void FUN_0101420c(int param_1,int param_2);
void FUN_010144f8(undefined4 *param_1,undefined4 param_2,undefined4 param_3);
void FUN_01014510(int param_1,int param_2);
void FUN_0101456c(int param_1,int param_2);
uint FUN_010146c8(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_0101471c(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 *param_6);
void FUN_010148c8(undefined4 *param_1,undefined4 *param_2);
void FUN_01014b3c(undefined4 param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4, int param_5);
void FUN_01014d10(undefined4 param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4);
void FUN_01014f98(undefined4 param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4);
void FUN_01015128(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_010151f0(int param_1,int param_2);
undefined4 FUN_01015220(int *param_1);
undefined4 FUN_010152d8(int param_1,undefined4 param_2);
void FUN_010159e4(int param_1,undefined4 param_2,int param_3);
undefined4 FUN_01015a40(undefined4 param_1,int param_2,undefined4 *param_3,undefined4 *param_4);
void FUN_01015ce8(undefined4 param_1,int param_2,int *param_3);
void FUN_010166a4(undefined4 param_1,int param_2,int param_3);
bool FUN_01016d8c(int param_1,undefined4 param_2,undefined4 *param_3,uint *param_4,int param_5);
bool FUN_01016ecc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,int param_6);
void FUN_01017120(undefined4 param_1,int param_2);
void FUN_0101715c(int param_1);
void FUN_01017174(int param_1);
void FUN_01017190(int param_1);
void FUN_010171a0(void);
undefined4 * FUN_010171ec(int param_1,int param_2);
void FUN_010171f8(int param_1,undefined4 *param_2);
void FUN_01017254(int *param_1,undefined4 param_2);
void FUN_010172a8(int param_1,undefined4 *param_2);
void FUN_010172d4(int param_1);
void FUN_010172fc(undefined4 *param_1,uint *param_2);
undefined4 * FUN_0101749c(undefined4 *param_1,undefined4 *param_2);
void FUN_01017840(int *param_1,undefined4 param_2);
void FUN_01017894(uint *param_1);
void FUN_0101790c(int param_1,undefined4 param_2,int param_3);
bool FUN_01017b00(int param_1);
int FUN_01017bc4(int param_1);
bool FUN_01017ccc(int param_1);
void FUN_01017dc4(int param_1,int *param_2,int *param_3);
void FUN_01017eb8(int param_1,int *param_2,int *param_3,int param_4);
int FUN_01018018(undefined4 param_1,int param_2);
void FUN_0101807c(int param_1,undefined4 param_2);
void FUN_01018094(int param_1);
void FUN_01018170(int param_1,undefined4 param_2);
uint FUN_010181b4(int param_1);
void FUN_010181e4(int param_1,int param_2);
void FUN_010183b0(int param_1);
void FUN_01018460(int param_1);
void FUN_0101956c(uint *param_1);
bool FUN_01019618(void);
undefined1 FUN_01019640(void);
void FUN_01019650(undefined4 param_1,undefined1 *param_2,int param_3);
int FUN_01019698(int param_1,int param_2);
uint FUN_010196cc(undefined4 param_1,uint param_2,uint param_3);
void FUN_01019704(undefined4 param_1,int param_2,int param_3,undefined4 param_4);
int FUN_01019764(void);
uint thunk_FUN_01019abc(undefined4 param_1);
void FUN_0101977c(undefined4 param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4);
int FUN_010197c4(undefined4 param_1,int param_2);
int FUN_0101981c(undefined4 param_1,int param_2);
int FUN_01019888(undefined4 param_1,int param_2);
undefined4 FUN_010198c8(int param_1);
void FUN_01019920(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_010199ac(undefined4 param_1,int param_2,int param_3,undefined4 param_4);
uint FUN_01019a0c(undefined4 param_1,undefined4 param_2,undefined4 param_3,uint param_4);
uint FUN_01019a98(undefined4 param_1);
uint FUN_01019abc(undefined4 param_1);
void FUN_01019afc(undefined4 param_1,undefined4 param_2,uint param_3,uint param_4);
void FUN_01019ba4(undefined4 param_1,undefined4 *param_2);
undefined1 FUN_01019bd4(int param_1);
void FUN_01019c10(uint param_1,int param_2,undefined4 param_3);
void FUN_01019cc0(int param_1,int param_2);
void FUN_01019ebc(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_01019f00(undefined4 param_1,int param_2,undefined4 param_3);
void FUN_01019f54(undefined4 param_1);
void FUN_0101a010(int param_1,int param_2);
void FUN_0101a104(int param_1,int param_2);
void FUN_0101a154(int param_1,int param_2);
void FUN_0101a1b0(int param_1);
void FUN_0101a230(int param_1);
void FUN_0101a2a4(int param_1,int param_2);
void FUN_0101a2c0(int param_1,int param_2,undefined4 param_3);
void FUN_0101a380(int param_1,int param_2,int param_3);
void FUN_0101a478(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6);
void FUN_0101a514(int param_1,int *param_2);
void FUN_0101a830(int param_1,int *param_2);
void FUN_0101a89c(int param_1,int param_2);
int FUN_0101bb58(int *param_1);
void FUN_0101bd48(int param_1,int param_2,int param_3,int param_4,undefined4 param_5);
void FUN_0101d01c(int param_1,int param_2,int param_3,int param_4,int param_5);
void FUN_0101d17c(int param_1,int param_2);
int FUN_0101d21c(int *param_1,int param_2);
void FUN_0101d37c(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_0101d554(int *param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_0101d598(int param_1);
void FUN_0101d620(int param_1);
void FUN_0101d674(undefined4 *param_1);
void FUN_0101d864(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_0101d8c8(int param_1);
void FUN_0101d974(int *param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4);
void FUN_0101da48(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_0101da90(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
uint FUN_0101dbcc(undefined4 param_1,int param_2);
void FUN_0101dbf8(int param_1,undefined4 param_2,undefined4 param_3,undefined2 *param_4);
void FUN_0101de2c(int param_1,undefined4 param_2);
void FUN_0101ded0(int param_1,undefined4 param_2);
void FUN_0101df64(int param_1,undefined4 param_2);
undefined4 FUN_0101e0b0(int param_1,undefined4 param_2);
void FUN_0101e144(int param_1,undefined4 param_2);
void FUN_0101e288(int param_1,undefined4 param_2);
void FUN_0101e3f4(int param_1,undefined4 param_2);
void thunk_FUN_0101df64(int param_1,undefined4 param_2);
void FUN_0101e534(int param_1,undefined4 param_2);
void FUN_0101e778(int param_1,undefined4 param_2);
void FUN_0101e824(int param_1,undefined4 param_2);
void FUN_0101e8ec(int param_1,undefined4 param_2);
void FUN_0101ea94(int param_1,undefined4 param_2,uint param_3,uint param_4);
void FUN_0101ee08(int *param_1,undefined4 param_2);
void FUN_0101ef44(int param_1,undefined4 param_2);
void FUN_0101f0b4(int param_1,undefined4 param_2);
void FUN_0101f3e4(int param_1,undefined4 param_2);
void FUN_0101f760(int param_1,undefined4 param_2);
void FUN_0101f8ac(int param_1,undefined4 param_2);
void FUN_0101f9a8(undefined4 param_1,undefined4 param_2);
void FUN_0101f9f8(int param_1,undefined4 param_2);
void FUN_0101fb28(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_0101fba8(int param_1,undefined4 param_2);
void FUN_0101fccc(int param_1,undefined4 param_2);
void FUN_0101fdc4(int param_1,int param_2,int param_3,int param_4,undefined4 param_5);
void FUN_0101fe5c(int param_1,int param_2,int param_3,undefined4 param_4,int param_5,int param_6);
void FUN_0101fefc(int param_1,int param_2,int param_3,int param_4,undefined4 param_5);
void FUN_0101ff90(int param_1,int param_2,int param_3);
void FUN_0101ffbc(int param_1,undefined4 param_2,int param_3,undefined4 param_4);
void FUN_01020104(int param_1,int param_2,int param_3,int param_4,int param_5);
void FUN_010201dc(int param_1,int param_2,int param_3);
void FUN_0102023c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_01020290(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5);
undefined8 FUN_0102035c(int param_1,int *param_2);
void FUN_01020480(int param_1,int param_2,int param_3,undefined4 param_4);
undefined4 * FUN_010204ec(undefined4 *param_1,int param_2,int param_3);
void FUN_0102060c(int *param_1,int *param_2,int *param_3,int param_4);
void FUN_01020948(int param_1,uint param_2,uint param_3);
void FUN_010209ac(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_01020a28(int param_1,int param_2);
undefined8 FUN_01020b64(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5 );
void FUN_01020bcc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5);
void FUN_01020c1c(int param_1,int param_2);
void FUN_01020c44(int param_1,undefined4 param_2);
void FUN_01020c60(int param_1,int param_2,int param_3,undefined2 param_4);
void FUN_01020c90(int param_1,int param_2);
void FUN_01020cc0(int param_1,int param_2,undefined4 param_3,int param_4);
void FUN_01020d0c(int *param_1,int param_2);
void FUN_01020da0(int param_1,int param_2);
void FUN_01020dec(int param_1);
void FUN_01021a78(int param_1,undefined4 param_2,int param_3);
void FUN_01021abc(int param_1,int param_2);
void FUN_01021b6c(int param_1,undefined4 param_2);
void FUN_01021b7c(int param_1,int param_2);
void FUN_01021bac(int param_1,int param_2,undefined4 param_3,int param_4,int param_5);
int FUN_01021c7c(int param_1,int param_2,int param_3,int param_4);
void FUN_01021d10(int param_1);
void FUN_01021d50(int param_1,int param_2,undefined4 param_3,int param_4);
void FUN_01021e58(int param_1,undefined4 param_2,undefined4 param_3);
void FUN_01021e64(int param_1,int param_2);
void FUN_01021ec8(int param_1,undefined4 param_2);
void FUN_01021f28(int param_1);
void FUN_010220b0(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_01022140(int *param_1,undefined4 param_2);
void FUN_010221a0(int *param_1,uint param_2);
void FUN_010221dc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5);
void FUN_01022204(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5);
void FUN_01022234(int *param_1,int param_2);
void FUN_01022278(int param_1,int param_2);
void FUN_010222a8(undefined4 *param_1,int *param_2,int param_3,int param_4);
void FUN_01022340(int param_1,undefined4 param_2,undefined4 param_3);
void FUN_0102234c(int param_1,int param_2,undefined4 param_3,int param_4,undefined4 *param_5);
void FUN_010223f0(int param_1,uint param_2,uint param_3,uint *param_4);
void FUN_010224fc(void);
int FUN_01022600(int param_1,uint param_2,undefined4 param_3,undefined4 *param_4);
void FUN_010226fc(int param_1,uint param_2,undefined4 param_3,undefined4 *param_4);
void FUN_0102277c(int *param_1,uint param_2,undefined4 param_3,int *param_4);
void FUN_0102282c(int *param_1,uint param_2,undefined4 param_3,int *param_4);
void FUN_01022a6c(int *param_1,int param_2,int param_3,int param_4);
void FUN_01022a94(int param_1,undefined4 param_2,undefined4 *param_3);
void FUN_01022acc(undefined1 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_01022bb8(int *param_1,int param_2);
void FUN_01022bfc(int *param_1,undefined4 param_2);
undefined4 FUN_01022c5c(int param_1,int param_2,undefined4 param_3,int param_4,int param_5);
void FUN_01023108(int param_1,int param_2);
void FUN_01023124(int *param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_01023174(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_01023184(int *param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_010231c4(int param_1,int *param_2);
void FUN_01023244(int param_1,undefined4 param_2,int param_3);
void FUN_0102327c(int param_1,undefined4 param_2);
void FUN_0102328c(int param_1,undefined4 param_2);
void FUN_0102329c(int param_1,int *param_2);
void FUN_01023420(int *param_1,int param_2,int param_3,undefined4 param_4);
undefined4 FUN_010234bc(int param_1,int param_2,undefined4 param_3,uint param_4,int param_5);
void FUN_0102358c(int param_1,uint param_2,int param_3,undefined4 param_4,int param_5, undefined4 *param_6);
void FUN_01023678(int param_1,uint param_2,int param_3);
void FUN_010236c4(int param_1,int param_2,int param_3,int param_4);
void FUN_01023944(int *param_1,int param_2);
void FUN_010239a4(int *param_1,undefined4 param_2);
void FUN_010239fc(int param_1,int param_2,int param_3,int param_4);
void FUN_01023af0(int param_1,int param_2,int param_3);
void FUN_01023b3c(int param_1,int *param_2,int param_3);
undefined8 FUN_01023bc8(int param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5);
void FUN_01023c88(int param_1,undefined4 param_2);
void FUN_01023c90(int param_1,int param_2,int param_3);
void FUN_01023ce4(int param_1,int param_2);
void FUN_01023d00(int param_1);
void FUN_01023d30(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6, int param_7);
undefined8 FUN_01023e44(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7);
void FUN_01023f30(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_01023f50(int param_1,int param_2,undefined4 *param_3);
void FUN_01023fb4(int param_1,int param_2);
void FUN_01023fc4(int param_1,int param_2);
void FUN_01023ff4(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_01024058(int param_1,int param_2);
void FUN_010240fc(int param_1,int param_2);
void FUN_0102412c(int param_1,int *param_2);
void FUN_010241f4(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_01024274(int param_1,undefined4 param_2,undefined4 param_3);
void FUN_01024280(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6,undefined4 param_7);
void FUN_010242a4(int param_1);
void FUN_01024338(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3,uint param_4, int param_5);
void FUN_010246a0(uint *param_1,uint *param_2,undefined4 param_3);
void FUN_010246f4(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6);
void FUN_01024a8c(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6, int param_7,int param_8,int param_9);
void FUN_01024d84(int *param_1,char *param_2,int *param_3,int *param_4);
void FUN_01024e18(int *param_1,short *param_2,int *param_3,int *param_4);
void FUN_01024eac(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4);
void FUN_0102501c(int *param_1,char *param_2,int *param_3,int *param_4,int param_5);
void FUN_01025104(int *param_1,short *param_2,int *param_3,int *param_4,int param_5);
void FUN_010251ec(int *param_1,char *param_2,int *param_3);
void FUN_01025270(int *param_1,short *param_2,int *param_3);
void FUN_010252f4(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3,undefined4 param_4);
void FUN_010254f0(int param_1);
void FUN_010255dc(int param_1,undefined4 param_2);
undefined8 FUN_010257a8(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_010257fc(int param_1,int param_2,int *param_3,int *param_4,int *param_5);
void FUN_010258d0(int param_1,int param_2,int param_3,undefined4 param_4,int param_5,int param_6);
void FUN_01025a50(int param_1,int param_2,int param_3,int param_4,int param_5);
void FUN_01025b30(int param_1,uint param_2,undefined4 *param_3);
void FUN_01025bc4(byte *param_1,undefined4 param_2,ushort *param_3,byte *param_4);
void FUN_01025c8c(int *param_1,uint *param_2);
void FUN_01025d30(undefined4 *param_1,uint *param_2);
void FUN_01025d38(undefined4 *param_1,uint param_2,uint param_3,uint param_4);
void FUN_01025e3c(int param_1);
undefined4 FUN_01025ec8(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,uint param_6,undefined4 *param_7,undefined4 *param_8, undefined4 *param_9);
void FUN_010261f0(int param_1);
void FUN_010262b0(void);
void FUN_010262e8(void);
void FUN_01026310(void);
void FUN_01026348(void);
void FUN_01026380(void);
void FUN_010263e8(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_01026468(uint *param_1);
undefined8 FUN_01026548(int param_1,int param_2);
void FUN_010265fc(int param_1);
void FUN_01026614(int param_1,int param_2);
void FUN_010266c0(int param_1);
int FUN_010268b4(void);
undefined8 FUN_010268d4(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_01026d30(int param_1,undefined4 param_2,int param_3);
int FUN_01026d84(int *param_1,int param_2);
undefined4 * FUN_0102727c(undefined4 *param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4);
void FUN_010272c0(int *param_1,int *param_2);
uint * FUN_010272f4(uint *param_1,undefined4 *param_2);
undefined4 * FUN_0102748c(undefined4 *param_1,undefined4 param_2);
undefined8 FUN_010274dc(uint *param_1,int param_2);
void FUN_01027538(int *param_1,int *param_2);
int * FUN_01027578(int *param_1,uint param_2,undefined4 param_3,undefined4 param_4);
undefined4 * FUN_010275fc(undefined4 *param_1,undefined4 *param_2);
void FUN_0102793c(int *param_1,int *param_2);
int FUN_01027970(int param_1,int param_2);
void FUN_010279d0(undefined4 *param_1,undefined4 *param_2);
int * FUN_010279ec(int *param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_01027a30(undefined4 *param_1,undefined4 *param_2);
int FUN_01027a54(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
undefined4 FUN_01027acc(undefined4 param_1,undefined4 param_2);
int FUN_01027ae4(int param_1,int param_2);
undefined4 * FUN_01027b08(undefined4 *param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4);
int * FUN_01027b6c(int *param_1);
void FUN_01027bf4(int *param_1);
void FUN_01027c34(int *param_1);
void FUN_01027c84(undefined4 *param_1);
void FUN_01027cb4(int *param_1);
void FUN_01027cd8(int *param_1);
void FUN_01027cfc(int param_1);
int * FUN_01027d0c(int *param_1);
int * FUN_01027d68(int *param_1);
void FUN_01027dbc(undefined4 *param_1);
int * FUN_01027e10(int *param_1);
void FUN_01027e6c(int *param_1);
void FUN_01027e90(undefined4 *param_1);
void FUN_01027ec0(int *param_1);
void FUN_01027ed4(int *param_1,int param_2,int param_3);
int * FUN_01027eec(int *param_1);
undefined4 * FUN_01028030(undefined4 *param_1,undefined4 *param_2);
undefined4 * FUN_01028344(undefined4 *param_1,undefined4 param_2,undefined4 *param_3);
int * FUN_01028430(int *param_1);
undefined8 FUN_01028464(int *param_1,int param_2,int param_3,int param_4);
int * FUN_010285fc(int *param_1);
int * FUN_01028630(int *param_1);
int * FUN_010286dc(int *param_1);
void FUN_01028758(int *param_1);
int * FUN_010287cc(int *param_1);
void FUN_0102885c(int *param_1);
int * FUN_01028898(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
int * FUN_01028948(int *param_1);
int * FUN_0102897c(int *param_1);
undefined4 * FUN_010289b0(undefined4 *param_1,undefined4 *param_2);
void FUN_01028a3c(undefined4 *param_1);
void FUN_01028a6c(int param_1);
int * FUN_01028a7c(int *param_1);
int * FUN_01028abc(int *param_1);
int * FUN_01028afc(int *param_1);
int * FUN_01028b28(int *param_1);
int * FUN_01028b58(int *param_1);
void FUN_01028bb0(int *param_1);
int * FUN_01028cc8(int *param_1);
int * FUN_01028d2c(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
int * FUN_01028f54(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
int * FUN_01029010(int *param_1);
int * FUN_010290c4(int *param_1);
void FUN_01029110(undefined4 *param_1);
int * FUN_010291bc(int *param_1);
void FUN_01029208(int *param_1);
void FUN_01029268(int *param_1);
int * FUN_010292b8(int *param_1);
int * FUN_01029304(int *param_1);
int * FUN_01029370(int *param_1);
void FUN_010293d4(int param_1);
void FUN_010293e4(int *param_1);
int * FUN_01029450(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_010294dc(undefined4 *param_1);
int * FUN_0102950c(int *param_1);
int * FUN_01029540(int *param_1);
int * FUN_010295ac(int *param_1);
void * FUN_01029620(void *param_1);
void * FUN_01029650(void *param_1,uint *param_2);
void * FUN_010296e8(void *param_1,undefined4 param_2);
undefined4 * FUN_01029724(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_010297d4(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8, undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12, undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16, undefined4 param_17);
void FUN_01029850(void *param_1);
void FUN_01029878(undefined4 *param_1);
void FUN_010298b4(void *param_1);
void FUN_010298e0(void *param_1);
void FUN_01029914(int *param_1,int param_2);
void FUN_01029994(undefined4 param_1,int param_2);
void FUN_010299a0(int *param_1,int param_2);
void FUN_01029a10(int *param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_01029a54(int *param_1,int param_2);
void FUN_01029ac0(int *param_1,int param_2);
void FUN_01029bf4(undefined4 param_1,int param_2);
void FUN_01029c00(int *param_1);
void FUN_01029c14(int *param_1,int param_2);
void FUN_01029d1c(int *param_1,int param_2);
void FUN_01029d74(int *param_1,int param_2);
void FUN_01029e10(int *param_1,int param_2);
void FUN_01029eb8(int *param_1,int param_2);
void FUN_01029fdc(int *param_1,int param_2);
void FUN_0102a7c8(int *param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_0102a898(int *param_1,int param_2);
void FUN_0102a910(int *param_1,int param_2);
void FUN_0102b194(int *param_1,int param_2);
void FUN_0102b38c(int *param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_0102b3d0(int *param_1,int param_2);
void FUN_0102b4c4(int *param_1,int param_2);
void FUN_0102b524(int *param_1,int param_2);
void FUN_0102b5fc(int *param_1,int param_2);
void FUN_0102b654(int *param_1,int param_2);
void FUN_0102b6d4(int *param_1,int param_2);
void FUN_0102b72c(int *param_1,int param_2);
void FUN_0102b784(int *param_1,int param_2);
void FUN_0102b7e0(int *param_1,int param_2);
void FUN_0102b83c(int *param_1,int param_2);
void FUN_0102b8ac(int *param_1,int param_2);
void FUN_0102b90c(int *param_1,int param_2);
void FUN_0102b964(int *param_1,int param_2);
void FUN_0102ba94(int *param_1,int param_2);
void FUN_0102baf0(int *param_1,int param_2);
void FUN_0102bb44(int *param_1,int param_2);
void FUN_0102bba0(int *param_1,int param_2);
void FUN_0102bbf8(int *param_1,int param_2);
void FUN_0102bef4(int *param_1,int param_2);
void FUN_0102bf50(int *param_1,int param_2);
void FUN_0102bfc8(int *param_1,int param_2);
void FUN_0102c1dc(int *param_1,int param_2);
void FUN_0102c254(int *param_1,int param_2);
void FUN_0102c2f4(int *param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_0102c338(int *param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_0102c46c(int *param_1,int param_2);
void FUN_0102c4d0(int *param_1,int param_2);
void FUN_0102c584(undefined4 param_1,int param_2);
void FUN_0102c590(undefined4 param_1,int param_2);
void FUN_0102c5a8(int *param_1,int param_2);
undefined4 FUN_0102c620(undefined4 *param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4);
undefined4 FUN_0102c670(int *param_1,int *param_2);
void FUN_0102c6b4(undefined4 *param_1,uint *param_2,undefined4 *param_3,undefined4 param_4);
void FUN_0102c760(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3);
void FUN_0102c7a8(uint *param_1,uint *param_2);
uint FUN_0102c7d4(undefined4 *param_1,undefined4 *param_2,undefined4 param_3,uint param_4);
void FUN_0102c820(undefined4 *param_1,undefined4 *param_2,undefined4 param_3);
undefined8 FUN_0102c868(int *param_1,int *param_2);
void FUN_0102c8bc(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3,undefined4 param_4);
void * FUN_0102cb54(uint32 param_1);
undefined4 FUN_0102cb6c(undefined4 *param_1,undefined4 *param_2);
void * FUN_0102cbe0(uint32 param_1);
void FUN_0102cc18(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3);
int FUN_0102cc60(void);
int FUN_0102cc80(int param_1,int param_2);
uint FUN_0102cc94(uint param_1,byte *param_2,uint param_3);
void FUN_0102ce5c(int param_1,undefined4 *param_2);
void FUN_0102ce74(int param_1,undefined4 *param_2);
void FUN_0102ce8c(int param_1,undefined4 param_2,undefined4 *param_3);
void FUN_0102ceac(int param_1,undefined4 *param_2);
void FUN_0102cecc(int param_1,undefined4 *param_2);
undefined4 FUN_0102cf84(int param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0102cfec(int param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0102d060(int param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0102d0d4(int param_1,undefined4 param_2);
int FUN_0102d1c0(int param_1,ISwerveObject **param_2);
int FUN_0102d22c(int param_1,ISwerveObject **param_2);
void FUN_0102d298(int param_1,undefined4 *param_2);
undefined4 FUN_0102d310(int param_1,int param_2,int param_3);
void FUN_0102d3ac(int param_1,int param_2);
int FUN_0102d42c(int param_1,ISwerveObject **param_2);
int FUN_0102d498(int param_1,ISwerveObject **param_2);
void FUN_0102d504(int param_1,undefined4 *param_2);
int FUN_0102d51c(int param_1,ISwerveObject **param_2);
int FUN_0102d588(int param_1,ISwerveObject **param_2);
int FUN_0102d5f4(int param_1,uint param_2,ISwerveObject **param_3);
void FUN_0102d748(int param_1,int param_2);
void FUN_0102d768(int param_1,int param_2);
undefined4 FUN_0102d788(int param_1,int param_2);
void FUN_0102d7f8(int param_1,int param_2);
void FUN_0102d818(int param_1,int param_2);
undefined4 FUN_0102d838(int param_1,undefined4 param_2,int param_3);
void FUN_0102da44(int param_1);
void FUN_0102dadc(int param_1,undefined4 *param_2);
void FUN_0102daf4(int param_1,undefined4 *param_2);
void FUN_0102db20(int param_1,undefined4 *param_2);
void FUN_0102db4c(int param_1,undefined4 *param_2);
void FUN_0102db78(int param_1,undefined4 *param_2);
int FUN_0102dba4(int param_1,ISwerveObject **param_2);
void FUN_0102dc10(int param_1,undefined4 *param_2);
void FUN_0102dc28(int param_1,undefined4 *param_2);
void FUN_0102dd50(int param_1,undefined1 *param_2);
void FUN_0102dd68(int param_1,undefined1 *param_2);
void FUN_0102dd80(int param_1,undefined4 param_2);
void FUN_0102dd94(int param_1,int param_2);
undefined4 FUN_0102ddb0(int param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5);
void FUN_0102de64(int param_1,int param_2);
undefined4 FUN_0102de80(int param_1,int param_2);
undefined4 FUN_0102deec(int param_1,int param_2,int param_3);
int FUN_0102df78(int param_1,int param_2);
undefined4 FUN_0102e06c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4);
undefined4 FUN_0102e0dc(int param_1,int param_2,undefined4 *param_3);
undefined4 FUN_0102e1b0(int param_1,int param_2);
undefined4 FUN_0102e234(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5 );
undefined4 FUN_0102e318(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5 );
void FUN_0102e4ac(int param_1,undefined4 *param_2);
void FUN_0102e4c4(int param_1,undefined4 *param_2);
void FUN_0102e4dc(int param_1,undefined4 *param_2);
void FUN_0102e4f4(int param_1,undefined4 *param_2);
void FUN_0102e60c(int param_1,undefined1 *param_2);
void FUN_0102e624(int param_1,undefined1 *param_2);
void FUN_0102e63c(int param_1,undefined1 *param_2);
void FUN_0102e654(int param_1,undefined1 *param_2);
undefined4 FUN_0102e66c(int param_1,undefined4 param_2);
void FUN_0102e708(int param_1,int param_2);
undefined4 FUN_0102e724(int param_1,int param_2);
void FUN_0102e794(int param_1,int param_2);
undefined4 FUN_0102e7b0(int param_1,undefined4 param_2,undefined4 param_3);
void FUN_0102e828(int param_1,int param_2);
void FUN_0102e844(int param_1,int param_2);
uint FUN_0102e860(uint param_1,byte *param_2,uint param_3);
bool FUN_0102e968(int *param_1,undefined4 param_2,undefined4 param_3);
void FUN_0102ea40(int param_1,uint *param_2);
void FUN_0102ea5c(int param_1,undefined4 *param_2);
void FUN_0102ea74(int param_1,undefined4 *param_2);
void FUN_0102ea8c(int param_1,undefined4 *param_2);
void FUN_0102eaa4(int param_1,undefined4 *param_2);
void FUN_0102eb5c(int param_1,uint param_2);
undefined4 FUN_0102eb74(int param_1,undefined4 param_2);
undefined4 FUN_0102ebf8(int param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0102ec78(int param_1,int param_2);
uint32 FUN_0102ecec(void);
uint FUN_0102ed04(uint param_1);
ulonglong FUN_0102ed3c(uint param_1,uint param_2);
undefined8 FUN_0102ed54(int param_1,int param_2,int param_3,uint param_4);
int FUN_0102edb4(int param_1);
int FUN_0102edc0(uint param_1,uint param_2,undefined4 param_3,undefined4 param_4);
int FUN_0102ee88(uint param_1);
int FUN_0102f080(int param_1);
ulonglong FUN_0102f088(uint param_1);
longlong FUN_0102f240(int param_1);
uint FUN_0102f264(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
uint FUN_0102f3e4(int param_1,undefined4 param_2,undefined4 param_3,uint param_4);
int FUN_0102f468(int param_1,int param_2);
int thunk_FUN_01009ad0(void);
void FUN_0102f514(undefined4 param_1);
void FUN_0102f774(undefined4 param_1);
void FUN_0102f7e0(undefined4 param_1);
undefined4 FUN_0102f7f8(int param_1,int param_2,int param_3,undefined4 *param_4);
undefined4 FUN_0102f898(int param_1,int param_2);
undefined4 FUN_0102f960(undefined4 param_1,uint param_2,undefined4 *param_3);
void FUN_0102f9d0(int param_1,undefined4 *param_2);
void FUN_0102f9e8(int param_1,undefined4 *param_2);
void FUN_0102fa00(int param_1,undefined4 *param_2);
void FUN_0102fa18(int param_1,undefined4 *param_2);
undefined4 FUN_0102fb74(int param_1,int param_2,int param_3);
undefined4 FUN_0102fc0c(int param_1,int param_2,int param_3,int param_4,int param_5,undefined4 param_6);
undefined4 FUN_0102fcf8(int param_1,int param_2);
undefined4 FUN_0102fd7c(int param_1);
undefined4 FUN_0102fdd4(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5 );
undefined4 FUN_0102fe4c(int param_1,int param_2);
undefined4 FUN_0102feb8(int param_1,int param_2,int param_3);
undefined4 FUN_0102ffb8(int param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_010300a4(int param_1,int param_2,undefined4 param_3);
undefined4 FUN_01030110(int param_1,undefined4 param_2,int param_3,int param_4);
undefined4 FUN_01030198(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5 );
void FUN_01030210(int param_1,int param_2);
undefined4 FUN_01030220(int param_1,int param_2);
int FUN_010302ec(int param_1,undefined4 param_2,ISwerveObject **param_3);
void FUN_01030360(int param_1,undefined4 *param_2);
undefined4 FUN_010303f0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5, int param_6,undefined1 *param_7);
undefined4 FUN_010304c0(int param_1,undefined4 param_2,undefined4 *param_3,undefined4 *param_4,int param_5, undefined1 *param_6);
undefined4 FUN_010305b8(int param_1,int param_2);
undefined4 FUN_01030624(int *param_1,uint param_2,uint param_3,int param_4,int param_5,uint *param_6, uint *param_7,int param_8,int *param_9,uint *param_10);
void FUN_01030aac(int param_1,undefined4 *param_2);
void FUN_01030acc(int param_1,undefined4 *param_2);
void FUN_01030ae4(int param_1,undefined4 *param_2);
void FUN_01030b10(int param_1,int *param_2);
void FUN_01030b38(int param_1,undefined4 *param_2);
void FUN_01030b58(int param_1,undefined4 *param_2);
undefined4 FUN_01030c54(int param_1,int param_2,int param_3,int param_4,undefined4 param_5,int param_6);
undefined4 FUN_01030d14(int param_1,int param_2,int param_3,int param_4);
undefined4 FUN_01030dbc(int param_1,int param_2,int param_3,int param_4,undefined4 param_5,int param_6, undefined4 param_7,int param_8);
undefined4 FUN_01030e98(int param_1,int param_2,int param_3,int param_4,int param_5);
void FUN_01030f48(int param_1,undefined1 *param_2);
undefined4 FUN_01030f60(int param_1,int param_2,int param_3,int param_4,int param_5,undefined4 param_6, int param_7);
void thunk_FUN_0103517c(int param_1);
void FUN_01031034(int param_1,int param_2);
undefined4 FUN_010311c4(int param_1,char *param_2,int param_3);
undefined4 FUN_010311d4(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_01031224(undefined4 *param_1,int *param_2,int param_3);
undefined4 FUN_01031ae4(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
undefined4 * FUN_01031b30(int param_1,undefined4 param_2,int param_3,undefined4 param_4);
void FUN_01031c04(int *param_1,int param_2,int *param_3,undefined4 param_4);
int FUN_01031c90(int param_1,int *param_2,int param_3,undefined4 param_4);
void FUN_0103224c(undefined4 param_1,int param_2);
void FUN_01032260(undefined1 param_1,undefined1 param_2,undefined4 param_3,undefined4 param_4, int param_5);
undefined4 FUN_010322ac(int param_1,int param_2,int param_3,int param_4,int param_5,int *param_6);
int FUN_01032658(int param_1,int param_2,int param_3,undefined4 param_4);
int FUN_0103278c(undefined4 param_1,int *param_2,undefined4 param_3,undefined4 param_4,int param_5);
int FUN_01032858(uint param_1,undefined4 param_2,int param_3,int *param_4,int *param_5, undefined4 param_6,undefined4 param_7,undefined4 param_8,int param_9);
undefined4 FUN_01032a28(undefined4 *param_1,undefined4 *param_2,int *param_3,int *param_4);
void FUN_01032ac0(int param_1,undefined4 *param_2);
void FUN_01032ad8(int param_1,undefined4 *param_2);
undefined4 FUN_01032b70(int param_1,int param_2,int param_3,int param_4);
undefined4 FUN_01032c10(int param_1,int param_2);
undefined4 FUN_01032c84(int param_1,undefined4 param_2,int param_3,undefined4 param_4,int param_5);
undefined4 FUN_01032d20(int param_1,int param_2);
undefined4 FUN_01032d90(int param_1,undefined4 param_2,undefined4 param_3);
void FUN_01032e58(int param_1,uint *param_2);
void FUN_01032e74(int param_1,undefined4 *param_2);
void FUN_01032e8c(int param_1,undefined4 *param_2);
void FUN_01032ea4(int param_1,undefined4 *param_2);
void FUN_01032ebc(int param_1,undefined4 *param_2);
void FUN_01032ed4(int param_1,undefined4 *param_2);
void FUN_01032eec(int param_1,undefined4 *param_2);
void FUN_01032f04(int param_1,undefined4 *param_2);
undefined4 FUN_0103300c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_010330f8(int param_1,uint param_2);
undefined4 FUN_01033108(int param_1,undefined4 param_2);
undefined4 FUN_01033174(int param_1,int param_2);
undefined4 FUN_010331ec(int param_1,undefined4 param_2);
undefined4 FUN_01033294(int param_1,undefined4 param_2);
undefined8 FUN_01033338(int param_1,uint param_2,uint param_3,int param_4);
int FUN_01033474(int param_1,undefined1 param_2,undefined4 param_3);
int FUN_01033690(int param_1,int param_2,ISwerveObject **param_3);
void FUN_0103372c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4);
void FUN_0103374c(int param_1,undefined4 *param_2);
undefined4 FUN_010337a8(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5 ,undefined4 *param_6);
undefined4 FUN_01033834(int param_1,undefined4 *param_2);
undefined4 FUN_010338a0(int param_1,int param_2,undefined4 *param_3);
undefined4 FUN_01033918(int param_1,undefined4 param_2);
void FUN_01033984(int param_1,int param_2);
int FUN_010339a4(int param_1);
undefined4 FUN_01033a24(int param_1,int param_2,undefined4 *param_3);
void FUN_01033aac(int param_1,undefined4 *param_2);
void FUN_01033b34(int param_1,undefined1 *param_2);
undefined4 FUN_01033b4c(int param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_01033bb4(int param_1,undefined4 param_2);
void FUN_01033c50(int param_1,int param_2);
int FUN_01033ccc(int param_1,undefined4 param_2,ISwerveObject **param_3);
int FUN_01033d40(int param_1,undefined4 param_2,ISwerveObject **param_3);
void FUN_01033db4(int param_1,undefined4 *param_2);
int FUN_01033dcc(int param_1,ISwerveObject **param_2);
undefined4 FUN_01033ec4(int param_1,int param_2,uint param_3,int param_4,uint param_5,int param_6);
undefined4 FUN_010340d0(int param_1,int param_2,int param_3,int param_4);
undefined4 FUN_0103418c(int param_1,undefined4 param_2,int param_3);
int FUN_01034260(int param_1,int param_2,ISwerveObject **param_3);
void FUN_010342f0(int param_1,undefined4 *param_2);
undefined4 FUN_01034308(int param_1,undefined4 param_2,int param_3);
undefined4 FUN_010343f4(int param_1,int param_2,uint param_3,int param_4,uint param_5,int param_6,uint param_7, int param_8);
undefined4 FUN_010346bc(int param_1,int param_2,uint param_3,int param_4,int param_5,int param_6);
undefined4 FUN_01034834(int param_1,undefined4 param_2,int param_3);
undefined4 FUN_010348b0(int param_1,int param_2);
void FUN_0103491c(int param_1,undefined4 *param_2);
int FUN_01034934(int param_1,ISwerveObject **param_2);
void FUN_010349a0(int param_1,undefined4 *param_2);
undefined4 FUN_010349b8(int param_1,int param_2,int param_3,undefined1 *param_4);
void FUN_01034a6c(int param_1);
void FUN_01034b3c(int param_1,byte *param_2);
void FUN_01034b5c(int param_1,byte *param_2);
undefined4 FUN_01034b78(int param_1,int param_2,int param_3,int param_4,int param_5);
undefined4 FUN_01034c3c(int param_1,undefined4 param_2);
void FUN_01034cd8(int param_1,int param_2);
void FUN_01034cf0(int param_1,int param_2);
void FUN_01034d08(int param_1);
undefined4 FUN_01034d24(int param_1,int param_2);
undefined4 FUN_01034da8(int param_1,undefined4 param_2,undefined4 *param_3);
int FUN_01034e14(int param_1,ISwerveObject **param_2);
int FUN_01034e8c(int param_1,undefined4 param_2,ISwerveObject **param_3);
int FUN_01034f00(int param_1,undefined4 param_2,ISwerveObject **param_3);
void FUN_01034f74(int param_1,undefined4 *param_2);
int FUN_01034f94(int param_1,uint param_2,int param_3,uint *param_4);
void FUN_010350fc(int param_1,undefined4 *param_2);
void FUN_01035114(int param_1);
void FUN_01035134(int param_1,int param_2,undefined4 *param_3);
void FUN_0103515c(int param_1);
void FUN_0103517c(int param_1);
undefined4 FUN_01035270(int param_1,int param_2);
void FUN_010352f4(int param_1);
void FUN_01035304(int param_1,undefined4 param_2);
undefined4 FUN_01035318(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
int FUN_01035388(int param_1);
void FUN_01035404(undefined4 param_1,byte *param_2);
void FUN_01035488(undefined4 param_1,undefined4 param_2);
void FUN_010354b4(undefined4 param_1,undefined4 param_2);
byte * FUN_010354e0(int param_1,byte *param_2,uint param_3);
undefined4 FUN_01035704(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
undefined4 FUN_01035774(int param_1,uint param_2);
void FUN_01035814(int param_1,undefined4 param_2,undefined4 param_3);
int FUN_0103583c(int param_1,undefined4 param_2,undefined4 param_3,int param_4);
int FUN_0103586c(char *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void * FUN_01035a40(int param_1);
void FUN_01035a84(int *param_1,int *param_2,int *param_3);
void FUN_01035b08(int param_1);
void FUN_01035b14(int *param_1,undefined1 *param_2);
void FUN_01035b70(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_01035e84(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_01035f30(uint *param_1,int param_2);
void FUN_01036088(int param_1);
void FUN_010360b0(int param_1,int param_2,int param_3);
void FUN_01036188(int param_1,int param_2);
void FUN_0103619c(int param_1,uint param_2,uint param_3,int param_4);
uint * FUN_010362a0(int param_1,uint *param_2,uint *param_3,uint *param_4,uint *param_5, uint *param_6,uint *param_7,uint *param_8,uint *param_9);
undefined4 FUN_01036370(uint param_1,int param_2,undefined4 *param_3,uint *param_4);
undefined4 FUN_010363a8(uint param_1,int param_2,undefined4 *param_3,uint *param_4,int *param_5);
int FUN_01036424(byte *param_1);
int FUN_01036438(byte *param_1);
uint FUN_0103645c(int param_1,int param_2,uint param_3);
undefined4 FUN_01036474(int param_1,int param_2,uint param_3,undefined4 param_4);
void FUN_010364d4(int param_1,undefined4 param_2,int param_3);
void FUN_01036610(int param_1,int param_2,uint param_3);
void FUN_01036838(int param_1,int param_2,uint param_3);
undefined4 FUN_010369f4(int param_1,undefined4 param_2,uint param_3,undefined4 param_4);
void FUN_01036a70(undefined4 param_1,undefined4 param_2);
undefined4 FUN_01036a98(undefined4 *param_1,uint param_2);
void FUN_01036acc(void);
void * FUN_01036ad0(int param_1,uint32 param_2);
undefined4 FUN_01036b0c(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
undefined4 FUN_01036b1c(undefined4 param_1,undefined4 param_2,uint param_3,undefined4 param_4);
void FUN_01036b2c(int param_1);
void FUN_01036b48(int param_1,int param_2,int param_3);
void FUN_01036c24(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_01036db4(undefined4 param_1,int param_2,byte *param_3,byte *param_4,undefined4 param_5);
void FUN_01036f6c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_01037248(int param_1,undefined4 *param_2);
void FUN_010372a8(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_010374dc(int param_1,int param_2,int param_3,uint param_4);
void FUN_01037904(int param_1);
void FUN_01037a70(int param_1);
void FUN_01037a90(int param_1,uint *param_2,uint param_3,uint param_4,uint param_5,uint param_6, int param_7,int param_8,int param_9);
void FUN_01037c78(int param_1,int param_2,undefined4 param_3,int param_4);
void FUN_01037cf8(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
undefined4 FUN_01037d08(int param_1);
void FUN_01037d28(int param_1);
void FUN_01037d48(int param_1,undefined4 param_2,undefined4 param_3);
void FUN_01037d98(int param_1);
void FUN_01037da8(int param_1,int param_2,int param_3,int param_4,int param_5);
undefined8 FUN_01037e48(int param_1,uint param_2,uint param_3);
void FUN_01037eb0(int param_1,char *param_2);
int FUN_01037eec(undefined4 param_1,int param_2,int param_3,undefined4 param_4);
void thunk_FUN_01036188(int param_1,int param_2);
void FUN_01037fa0(int param_1,undefined4 *param_2);
void FUN_01037fc0(int param_1,undefined4 *param_2);
void FUN_01037fe0(int param_1,undefined4 *param_2);
void FUN_010380b0(int param_1,undefined1 *param_2);
undefined4 FUN_010380d0(int param_1,int param_2);
void FUN_01038148(int param_1,int param_2);
void FUN_01038160(int param_1,int param_2);
undefined4 FUN_01038178(int param_1,int param_2);
void FUN_010381f0(int param_1,int param_2);
undefined4 FUN_01038208(int param_1,int param_2);
void FUN_01038280(int param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4);
void FUN_01038340(int param_1,undefined4 *param_2);
int FUN_01038358(int param_1,ISwerveObject **param_2);
void FUN_010383c4(int param_1,undefined4 *param_2);
void FUN_010383dc(int param_1,undefined4 *param_2);
void FUN_010383f4(int param_1,undefined4 *param_2);
undefined4 FUN_0103840c(int param_1,undefined4 param_2,int param_3);
void FUN_01038488(int param_1,undefined4 *param_2);
undefined4 FUN_010384a0(int param_1,uint param_2,undefined4 *param_3);
undefined4 FUN_01038518(int param_1,uint param_2,undefined4 *param_3);
int FUN_01038624(byte *param_1);
int FUN_01038644(uint param_1,int param_2,int param_3,undefined4 param_4);
int FUN_010386cc(int *param_1);
int FUN_010386fc(int *param_1);
int FUN_01038730(int *param_1);
int FUN_01038760(int *param_1);
undefined4 FUN_01038794(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5);
int FUN_01038878(int param_1,ISwerveObject **param_2);
undefined4 FUN_01038934(int param_1,int param_2,uint param_3,int param_4,uint param_5,int param_6,int param_7);
undefined4 FUN_01038b54(int param_1,int param_2,int param_3,int param_4,int param_5);
int FUN_01038c8c(int param_1,ISwerveObject **param_2);
void FUN_01038cf8(int param_1,undefined4 *param_2);
void FUN_01038d10(int param_1,undefined4 *param_2);
void FUN_01038d28(int param_1,undefined4 *param_2);
void FUN_01038d40(int param_1,undefined4 *param_2);
int FUN_01038d58(int param_1,ISwerveObject **param_2);
undefined4 FUN_01038e84(int param_1,int param_2,int param_3,int param_4);
void FUN_01038f38(int param_1,undefined1 *param_2);
void FUN_01038f50(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
undefined4 FUN_01038f70(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5 );
undefined4 FUN_01038fe8(int param_1,int param_2);
int FUN_0103906c(int param_1);
uint FUN_010390ac(int param_1,int param_2);
int FUN_01039270(int param_1);
void FUN_010392dc(int param_1,undefined4 *param_2);
void FUN_010392f4(int param_1,undefined4 *param_2);
undefined4 FUN_0103937c(int param_1,int param_2,int param_3,undefined4 param_4,int param_5);
undefined4 FUN_01039424(int param_1,int param_2,int param_3);
undefined4 FUN_010394ac(int param_1,undefined4 param_2);
undefined4 FUN_01039510(int param_1,undefined4 param_2);
uint thunk_FUN_0102cc94(uint param_1,byte *param_2,uint param_3);
bool thunk_FUN_01039670(undefined4 *param_1);
undefined4 FUN_010395b4(undefined4 param_1,undefined4 param_2,int *param_3);
bool FUN_01039670(undefined4 *param_1);
undefined4 FUN_010396cc(int param_1,int param_2,undefined4 *param_3);
void FUN_010398e8(int param_1);
undefined4 FUN_010399c4(int param_1,undefined4 param_2,undefined4 *param_3);
void FUN_01039a10(int param_1,undefined4 *param_2);
int FUN_01039a28(int param_1,undefined4 param_2,undefined4 param_3,int *param_4);
int FUN_01039aac(int param_1,undefined4 param_2,undefined4 param_3,int *param_4);
int FUN_01039c24(int param_1,int param_2);
undefined4 thunk_FUN_01000100(undefined4 param_1);
int FUN_0103a77c(int param_1,int param_2,void **param_3);
int FUN_0103ad28(int param_1,undefined4 param_2,undefined4 *param_3);
void FUN_0103ae48(void);
undefined4 FUN_0103aed8(undefined4 param_1);
undefined4 FUN_0103afb4(char *param_1);
int FUN_0103aff8(int param_1,int param_2,undefined4 param_3,int param_4,undefined4 *param_5);
int FUN_0103b0a4(int param_1,int param_2,undefined4 param_3,int param_4,undefined4 *param_5);
int FUN_0103b154(int param_1,undefined4 param_2,int param_3);
void FUN_0103b260(int param_1,undefined4 *param_2);
void FUN_0103b278(int param_1,undefined4 *param_2);
int FUN_0103b290(int param_1,ISwerveObject **param_2);
void FUN_0103b2fc(int param_1,undefined4 *param_2);
void FUN_0103b314(int param_1,undefined4 *param_2);
undefined4 FUN_0103b3ec(int param_1,int param_2);
void FUN_0103b46c(int param_1,undefined4 param_2);
undefined4 FUN_0103b480(int param_1,int param_2);
undefined4 FUN_0103b4f0(int param_1,int param_2,int param_3);
undefined4 FUN_0103b57c(int param_1,int param_2);
undefined4 FUN_0103b600(int param_1,int param_2,int param_3);
undefined4 FUN_0103b6ec(int param_1,undefined4 param_2,int param_3);
undefined4 FUN_0103b84c(int param_1,int param_2);
undefined4 FUN_0103b8cc(int param_1);
undefined4 FUN_0103b924(int param_1,int param_2);
undefined4 FUN_0103b9a8(int param_1,undefined4 *param_2);
undefined4 FUN_0103baa8(int param_1,undefined4 *param_2);
undefined4 FUN_0103bba8(int param_1,undefined4 *param_2);
undefined4 FUN_0103bc40(int param_1,undefined4 *param_2);
void FUN_0103bcd8(int param_1);
undefined4 FUN_0103bce8(int param_1,undefined4 param_2,int param_3);
undefined4 FUN_0103bd64(int param_1,int param_2);
undefined4 FUN_0103bde8(int param_1,int param_2,undefined4 param_3,int param_4,int param_5);
undefined4 FUN_0103be9c(int param_1,undefined4 param_2,int param_3);
void FUN_0103bf18(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
undefined4 FUN_0103bf28(int param_1,int param_2);
void FUN_0103bfac(int param_1,undefined4 *param_2);
void FUN_0103c03c(int param_1,undefined4 *param_2);
undefined4 FUN_0103c094(int param_1,int param_2);
void FUN_0103c118(int param_1,undefined4 *param_2);
void FUN_0103c170(int param_1);
undefined4 FUN_0103c250(int param_1,undefined4 *param_2);
undefined4 FUN_0103c350(int param_1,undefined4 *param_2);
undefined4 FUN_0103c450(int param_1,undefined4 *param_2);
undefined4 FUN_0103c4e8(int param_1,undefined4 *param_2);
undefined4 FUN_0103c5e8(int param_1,undefined4 *param_2);
undefined4 FUN_0103c680(int param_1,int param_2);
undefined4 FUN_0103c6ec(int param_1,undefined4 *param_2);
undefined4 FUN_0103c784(int param_1,undefined4 *param_2);
undefined4 FUN_0103c8ac(int param_1,undefined4 param_2,int param_3,undefined4 param_4,int param_5);
undefined4 FUN_0103c944(int param_1,undefined4 param_2,undefined4 param_3,int param_4);
undefined4 FUN_0103ca64(int param_1,int param_2,int param_3,int param_4);
undefined4 FUN_0103cb10(int param_1,undefined4 param_2,int param_3,undefined4 param_4,int param_5);
undefined4 FUN_0103cbac(int param_1,undefined4 param_2,int param_3,undefined4 param_4,int param_5);
int FUN_0103cca8(int param_1,ISwerveObject **param_2);
void FUN_0103cd14(int param_1,undefined4 *param_2);
int FUN_0103cd2c(int param_1,ISwerveObject **param_2);
int FUN_0103cd98(int param_1,undefined4 param_2,undefined4 param_3,ISwerveObject **param_4);
int FUN_0103ce14(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, ISwerveObject **param_5);
void FUN_0103ce98(int param_1,undefined4 *param_2);
undefined4 FUN_0103cf70(int param_1,int param_2);
void FUN_0103cfdc(int param_1,undefined4 param_2);
undefined4 FUN_0103cff0(int param_1,int param_2);
undefined4 FUN_0103d05c(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5);
undefined4 FUN_0103d0f0(int param_1,undefined4 param_2,int param_3,undefined4 param_4,undefined4 param_5, undefined4 param_6);
int FUN_0103d1ec(int param_1,ISwerveObject **param_2);
int FUN_0103d258(int param_1,ISwerveObject **param_2);
undefined4 FUN_0103d314(int param_1,int param_2);
void FUN_0103d398(int param_1,int param_2);
void FUN_0103d3b8(undefined4 param_1,int param_2,int param_3);
void FUN_0103d3c0(undefined4 param_1,undefined4 param_2);
uint FUN_0103d3d4(uint param_1,uint param_2);
uint FUN_0103d58c(uint param_1,uint param_2,uint param_3,uint param_4);
uint FUN_0103d778(uint param_1,uint param_2,uint param_3,uint param_4);
uint FUN_0103d7bc(uint param_1,uint param_2,uint param_3,uint param_4);
uint FUN_0103db5c(uint param_1,uint param_2,uint param_3,uint param_4);
uint FUN_0103db7c(uint param_1,uint param_2,uint param_3,uint param_4);
undefined8 FUN_0103de24(uint param_1,uint param_2,uint param_3,uint param_4);
uint FUN_0103e10c(uint param_1,uint param_2,uint param_3,uint param_4);
uint FUN_0103e18c(uint param_1,uint param_2);
undefined8 FUN_0103e23c(uint param_1);
uint FUN_0103e26c(uint param_1,uint param_2,uint param_3,uint param_4);
uint FUN_0103e2ec(uint param_1,uint param_2,uint param_3,uint param_4);
uint FUN_0103e36c(uint param_1,uint param_2,uint param_3,uint param_4);
uint FUN_0103e620(uint param_1,uint param_2,uint param_3,uint param_4);
uint FUN_0103e908(uint param_1,uint param_2,uint param_3,uint param_4);


/* ---- Literal-pool words, named automatically from the module bytes ----------------------------
   Each was a Ghidra DAT_<address> label. PC-relative offsets (used as NAME + pc) are named after
   what they point to; other words are named after their value. The comment gives the old label(s),
   the word's address and how the name was derived. Generated, not reviewed one by one: names say
   what a word IS (its value or target), not necessarily what the code uses it for. */
#define INTEGER_0 0x00000000   /* was DAT_0100061c, DAT_01004b50, DAT_01018aec, DAT_01018af4, DAT_01019294, DAT_0101929c, DAT_010192a4, DAT_010192ac, DAT_010192b4, DAT_0102f070, DAT_0103ee5c (word at 0x0100061C); integer 0 */
#define HIGH_WORD_OF_DOUBLE_0_POINT_7853980064 0x3FE921FB   /* was DAT_01000620, DAT_01000804, DAT_0100091c (word at 0x01000620); high word of the double 0.785398006439209, in a function that tests high words */
#define INTEGER_1 0x00000001   /* was DAT_01000624, DAT_01000808, DAT_01000878, DAT_01000920 (word at 0x01000624); integer 1 */
#define INTEGER_2056 0x00000808   /* was DAT_010006fc (word at 0x010006FC); integer 2056 */
#define WORD_HEXADECIMAL_FF800000 0xFF800000   /* was DAT_01000700, DAT_01017eb4 (word at 0x01000700); value 0xFF800000 (-8388608) */
#define WORD_HEXADECIMAL_7F800000 0x7F800000   /* was DAT_01000704, DAT_0102ed38, DAT_0102f3e0, DAT_0103ee6c (word at 0x01000704); value 0x7F800000 (2139095040) */
#define DATA_AT_01042864_OFFSET 0x00041AA8   /* was DAT_01000f04 (word at 0x01000F04); PC-relative offset: + 0x1000dbc (the pc) = 0x01042864 */
#define HIGH_WORD_OF_DOUBLE_0_POINT_2999999523 0x3FD33333   /* was DAT_01000f08 (word at 0x01000F08); high word of the double 0.2999999523162842, in a function that tests high words */
#define HIGH_WORD_OF_DOUBLE_1_POINT_570796013 0x3FF921FB   /* was DAT_01001378 (word at 0x01001374); high word of the double 1.570796012878418, in a function that tests high words */
#define HIGH_WORD_OF_DOUBLE_1647099 0x413921FB   /* was DAT_01001394 (word at 0x01001394); high word of the double 1647099.0, in a function that tests high words */
#define DATA_AT_01042924_OFFSET 0x000417D8   /* was DAT_010013a8 (word at 0x010013A8); PC-relative offset: + 0x100114c (the pc) = 0x01042924 */
#define INTEGER_1129 0x00000469   /* was DAT_010013ac (word at 0x010013AC); integer 1129 */
#define DATA_AT_01042894_OFFSET 0x00041654   /* was DAT_010013b0 (word at 0x010013B0); PC-relative offset: + 0x1001240 (the pc) = 0x01042894 */
#define DATA_AT_01042954_OFFSET 0x00041458   /* was DAT_010015d8 (word at 0x010015D8); PC-relative offset: + 0x10014fc (the pc) = 0x01042954 */
#define HIGH_WORD_OF_DOUBLE_0_POINT_6743354797 0x3FE59428   /* was DAT_010019ac (word at 0x010019AC); high word of the double 0.6743354797363281, in a function that tests high words */
#define DATA_AT_0104297C_OFFSET 0x00041224   /* was DAT_010019c8 (word at 0x010019C8); PC-relative offset: + 0x1001758 (the pc) = 0x0104297C */
#define DATA_AT_010429AC_OFFSET 0x0004123C   /* was DAT_010019cc (word at 0x010019CC); PC-relative offset: + 0x1001770 (the pc) = 0x010429AC */
#define WORD_HEXADECIMAL_00020026 0x00020026   /* was DAT_01001c2c (word at 0x01001C2C); value 0x00020026 (131110) */
#define DATA_AT_010429C5_OFFSET 0x00040D80   /* was DAT_01001d28 (word at 0x01001D28); PC-relative offset: + 0x1001c45 (the pc) = 0x010429C5 */
#define AEECLSID_SWERVE_VALUE 0x0102BBFC   /* was DAT_010028c4 (word at 0x010028C4); BREW class identifier AEECLSID_SWERVE */
#define ADDRESS_OF_AEEMod_AddRef_OFFSET 0xFFFFFED0   /* was DAT_01002a48 (word at 0x01002A48); PC-relative offset: + 0x10029f8 (the pc) = 0x010028C8 */
#define ADDRESS_OF_AEEMod_Release_OFFSET 0xFFFFFF0C   /* was DAT_01002a4c (word at 0x01002A4C); PC-relative offset: + 0x1002a04 (the pc) = 0x01002910 */
#define ADDRESS_OF_AEEMod_CreateInstance_OFFSET 0xFFFFFECC   /* was DAT_01002a50 (word at 0x01002A50); PC-relative offset: + 0x1002a10 (the pc) = 0x010028DC */
#define DATA_AT_0100290C_OFFSET 0xFFFFFEF0   /* was DAT_01002a54 (word at 0x01002A54); PC-relative offset: + 0x1002a1c (the pc) = 0x0100290C */
#define INTEGER_MINUS_1301 0xFFFFFAEB   /* was DAT_01002af4, DAT_01002c6c, DAT_01002df8, DAT_0100339c, DAT_01003508, DAT_0100601c, DAT_01007e2c, DAT_01007f3c, DAT_01008008, DAT_010082c4, DAT_01008358, DAT_01008440, DAT_01008538, DAT_010085e4, DAT_0100873c, DAT_01010144, DAT_01010380, DAT_010103d0, DAT_010108d0, DAT_0101195c, DAT_01011a80, DAT_01016ec4, DAT_0101a150, DAT_0101a37c, DAT_0101ef40, DAT_0101ffb8, DAT_010201d8, DAT_0102028c, DAT_0102047c, DAT_01020994, DAT_010209f4, DAT_01020c18, DAT_01020de8, DAT_01021b68, DAT_01021c78, DAT_01022134, DAT_010223ec, DAT_01023240, DAT_01023674, DAT_010239a0, DAT_01023bc4, DAT_01023c5c, DAT_01023ce0, DAT_01023e3c, DAT_01023f2c, DAT_01023fb0, DAT_010241f0, DAT_01025b2c, DAT_01025bc0, DAT_0102d15c, DAT_0102d3a8, DAT_0102de60, DAT_0102df74, DAT_0102e314, DAT_0102e444, DAT_0102e704, DAT_0102e790, DAT_0102ebf4, DAT_0102ece4, DAT_0102f9cc, DAT_010300a0, DAT_01030d0c, DAT_01030db8, DAT_01030e90, DAT_01030f44, DAT_01031028, DAT_01032c0c, DAT_01032c80, DAT_01032d18, DAT_01032d8c, DAT_010330f4, DAT_010331e8, DAT_01033290, DAT_01033334, DAT_01033aa8, DAT_01033c4c, DAT_01034c38, DAT_01034cd4, DAT_010350f8, DAT_01038144, DAT_010381ec, DAT_0103827c, DAT_0103941c, DAT_010394a8, DAT_01039590, DAT_0103b4ec, DAT_0103b578, DAT_0103b688, DAT_0103baa4, DAT_0103bba4, DAT_0103c34c, DAT_0103c44c, DAT_0103c5e4, DAT_0103cb0c, DAT_0103cba4, DAT_0103cc40 (word at 0x01002AF4); integer -1301 */
#define DATA_AT_010025AC_OFFSET 0xFFFFFAE4   /* was DAT_01002af8 (word at 0x01002AF8); PC-relative offset: + 0x1002ac8 (the pc) = 0x010025AC */
#define DATA_AT_01001EE8_OFFSET 0xFFFFF408   /* was DAT_01002afc (word at 0x01002AFC); PC-relative offset: + 0x1002ae0 (the pc) = 0x01001EE8 */
#define INTEGER_MINUS_1302 0xFFFFFAEA   /* was DAT_01002df4, DAT_01003398, DAT_010082c8, DAT_01008740, DAT_0102323c, DAT_0102d3a4, DAT_0102e230, DAT_0102f894, DAT_0102fc08, DAT_0102fcf4, DAT_0102fd78, DAT_010304bc, DAT_01030d10, DAT_01030e94, DAT_0103102c, DAT_01032d1c, DAT_010340c4, DAT_01034188, DAT_01034380, DAT_010346ac, DAT_0103482c, DAT_010348ac, DAT_01034a68, DAT_01034da4, DAT_010352f0, DAT_01038484, DAT_01038b48, DAT_01038c28, DAT_01038f34, DAT_01039068, DAT_01039420, DAT_0103a768, DAT_0103b468, DAT_0103b5fc, DAT_0103b764, DAT_0103b8c8, DAT_0103b9a4, DAT_0103bd60, DAT_0103bde4, DAT_0103be98, DAT_0103bf14, DAT_0103bfa8, DAT_0103c114, DAT_0103c940, DAT_0103c9c0, DAT_0103cba8, DAT_0103cc44, DAT_0103d394 (word at 0x01002DF4); integer -1302 */
#define INTEGER_MINUS_1101 0xFFFFFBB3   /* was DAT_010033a0, DAT_0100853c, DAT_010085e0, DAT_0100f1c4, DAT_0100f1f8, DAT_0100f61c, DAT_0100f764, DAT_010108cc, DAT_0101668c, DAT_0101963c, DAT_01019ba0, DAT_0101a82c, DAT_0101cd5c, DAT_0101f63c, DAT_0101fe58, DAT_0101ff8c, DAT_01020238, DAT_01021c74, DAT_01021d0c, DAT_010236c0, DAT_01023b38, DAT_0102d674, DAT_0102d7f4, DAT_010342ec, DAT_01038514, DAT_0103858c (word at 0x010033A0); integer -1101 */
#define ADDRESS_OF_FUNCTION_01027c84_OFFSET 0x00024500   /* was DAT_0100379c (word at 0x0100379C); PC-relative offset: + 0x1003784 (the pc) = 0x01027C84 */
#define ADDRESS_OF_FUNCTION_01027cfc_OFFSET 0x00024534   /* was DAT_010037e0 (word at 0x010037E0); PC-relative offset: + 0x10037c8 (the pc) = 0x01027CFC */
#define ADDRESS_OF_FUNCTION_01027e90_OFFSET 0x00024674   /* was DAT_01003834 (word at 0x01003834); PC-relative offset: + 0x100381c (the pc) = 0x01027E90 */
#define ADDRESS_OF_FUNCTION_01028a3c_OFFSET 0x000251B4   /* was DAT_010038a0 (word at 0x010038A0); PC-relative offset: + 0x1003888 (the pc) = 0x01028A3C */
#define ADDRESS_OF_FUNCTION_01029110_OFFSET 0x0002581C   /* was DAT_0100390c (word at 0x0100390C); PC-relative offset: + 0x10038f4 (the pc) = 0x01029110 */
#define AEECLSID_FILEMGR_VALUE 0x01001003   /* was DAT_01004624, DAT_01039aa4, DAT_01039c1c (word at 0x01004624); BREW class identifier AEECLSID_FILEMGR */
#define WORD_HEXADECIMAL_0001000B 0x0001000B   /* was DAT_01004628, DAT_0103986c (word at 0x01004628); value 0x0001000B (65547) */
#define DATA_AT_0103FAAC_OFFSET 0x0003B660   /* was DAT_01004630 (word at 0x01004630); PC-relative offset: + 0x100444c (the pc) = 0x0103FAAC */
#define INTEGER_MINUS_18052 0xFFFFB97C   /* was DAT_01004798 (word at 0x01004798); integer -18052 */
#define WORD_HEXADECIMAL_3C6EF35F 0x3C6EF35F   /* was DAT_010047a0 (word at 0x010047A0); value 0x3C6EF35F (1013904223) */
#define WORD_HEXADECIMAL_0019660D 0x0019660D   /* was DAT_010047a4 (word at 0x010047A4); value 0x0019660D (1664525) */
#define INTEGER_257 0x00000101   /* was DAT_010047ac, DAT_01032a08 (word at 0x010047AC); integer 257 */
#define DATA_AT_01040138_OFFSET 0x0003B864   /* was DAT_010048e0 (word at 0x010048E0); PC-relative offset: + 0x10048d4 (the pc) = 0x01040138 */
#define INTEGER_MINUS_1000 0xFFFFFC18   /* was DAT_01004a64, DAT_0100f94c, DAT_0101031c, DAT_010167fc, DAT_010204e8 (word at 0x01004A64); integer -1000 */
#define WORD_HEXADECIMAL_00010000 0x00010000   /* was DAT_01004b4c (word at 0x01004B4C); value 0x00010000 (65536) */
#define WORD_HEXADECIMAL_47800000 0x47800000   /* was DAT_01005eac, DAT_0100a620, DAT_0100f348, DAT_0101302c, DAT_0101328c, DAT_01016d84, DAT_0101b808, DAT_0101bd3c, DAT_0101cd74, DAT_0101d174, DAT_0101d550, DAT_0101e774, DAT_01020b30, DAT_01023588, DAT_01028a38, DAT_010294d8 (word at 0x01005EAC); value 0x47800000 (1199570944) */
#define WORD_HEXADECIMAL_46FFFE00 0x46FFFE00   /* was DAT_01010cc4, DAT_01013038 (word at 0x01005EB0); value 0x46FFFE00 (1191181824) */
#define DATA_AT_01002628_OFFSET 0xFFFFC05C   /* was DAT_0100664c (word at 0x0100664C); PC-relative offset: + 0x10065cc (the pc) = 0x01002628 */
#define FOUR_CHARACTER_TAG_ZLIB 0x5A4C4942   /* was DAT_01008394, DAT_0103966c, DAT_010396c8, DAT_01039760 (word at 0x01008394); the four characters 'ZLIB' (read as a big-endian word) */
#define DATA_AT_0100203C_OFFSET 0xFFFF8718   /* was DAT_0100993c (word at 0x0100993C); PC-relative offset: + 0x1009924 (the pc) = 0x0100203C */
#define DATA_AT_01002268_OFFSET 0xFFFF8938   /* was DAT_01009940 (word at 0x01009940); PC-relative offset: + 0x1009930 (the pc) = 0x01002268 */
#define DATA_AT_0100203C_OFFSET_2 0xFFFF8614   /* was DAT_01009ac0 (word at 0x01009AC0); PC-relative offset: + 0x1009a28 (the pc) = 0x0100203C */
#define DATA_AT_01001E5C_OFFSET 0xFFFF842C   /* was DAT_01009ac4 (word at 0x01009AC4); PC-relative offset: + 0x1009a30 (the pc) = 0x01001E5C */
#define INTEGER_MINUS_30712 0xFFFF8808   /* was DAT_01009ac8 (word at 0x01009AC8); integer -30712 */
#define INTEGER_MINUS_30512 0xFFFF88D0   /* was DAT_01009acc (word at 0x01009ACC); integer -30512 */
#define INTEGER_2788 0x00000AE4   /* was DAT_01009b7c (word at 0x01009B7C); integer 2788 */
#define INTEGER_MINUS_1300 0xFFFFFAEC   /* was DAT_0100a46c, DAT_0100eeec, DAT_0100fdb4, DAT_010106cc, DAT_01010cc0, DAT_010118f0, DAT_01016684, DAT_01016d80, DAT_0101711c, DAT_01017afc, DAT_0101a378, DAT_0101a510, DAT_0101bd44, DAT_0101cd60, DAT_0101d170, DAT_0101d218, DAT_0101d378, DAT_0101fe50, DAT_0101ff84, DAT_01023e40, DAT_010268b0 (word at 0x0100A46C); integer -1300 */
#define INTEGER_65535 0x0000FFFF   /* was DAT_0100b188, DAT_0100c798, DAT_0100cef0, DAT_0100dfe8, DAT_01017af8, DAT_0101f3e0, DAT_01021a6c (word at 0x0100B188); integer 65535 */
#define WORD_HEXADECIMAL_00036CA8 0x00036CA8   /* was DAT_0100c790 (word at 0x0100C790); value 0x00036CA8 (224424) */
#define WORD_HEXADECIMAL_00036CAC 0x00036CAC   /* was DAT_0100c794 (word at 0x0100C794); value 0x00036CAC (224428) */
#define INTEGER_8191 0x00001FFF   /* was DAT_0100c79c (word at 0x0100C79C); integer 8191 */
#define ADDRESS_OF_FUNCTION_0100bb68_OFFSET 0xFFFFE93C   /* was DAT_0100dfc4 (word at 0x0100DFC4); PC-relative offset: + 0x100d22c (the pc) = 0x0100BB68 */
#define ADDRESS_OF_swv_SpanFillTextured_OFFSET 0x00000D40   /* was DAT_0100dfc8 (word at 0x0100DFC8); PC-relative offset: + 0x100d2ac (the pc) = 0x0100DFEC */
#define ADDRESS_OF_FUNCTION_0100ac0c_OFFSET 0xFFFFD938   /* was DAT_0100dfcc (word at 0x0100DFCC); PC-relative offset: + 0x100d2d4 (the pc) = 0x0100AC0C */
#define ADDRESS_OF_FUNCTION_0100c92c_OFFSET 0xFFFFF630   /* was DAT_0100dfd0 (word at 0x0100DFD0); PC-relative offset: + 0x100d2fc (the pc) = 0x0100C92C */
#define ADDRESS_OF_swv_SpanFillGeneric_OFFSET 0xFFFFD5A4   /* was DAT_0100dfd4 (word at 0x0100DFD4); PC-relative offset: + 0x100d310 (the pc) = 0x0100A8B4 */
#define ADDRESS_OF_FUNCTION_0100a820_OFFSET 0xFFFFD4C4   /* was DAT_0100dfd8 (word at 0x0100DFD8); PC-relative offset: + 0x100d35c (the pc) = 0x0100A820 */
#define ADDRESS_OF_swv_SpanFillFlat_OFFSET 0xFFFFDE28   /* was DAT_0100dfdc (word at 0x0100DFDC); PC-relative offset: + 0x100d364 (the pc) = 0x0100B18C */
#define ADDRESS_OF_FUNCTION_0100c7a0_OFFSET 0xFFFFF420   /* was DAT_0100dfe0 (word at 0x0100DFE0); PC-relative offset: + 0x100d380 (the pc) = 0x0100C7A0 */
#define INTEGER_4095 0x00000FFF   /* was DAT_0100dfe4 (word at 0x0100DFE4); integer 4095 */
#define WORD_HEXADECIMAL_377BA882 0x377BA882   /* was DAT_0100e5ac, DAT_0100f34c, DAT_0100f948, DAT_010100ec, DAT_01010318, DAT_010126cc, DAT_01012904, DAT_01013740, DAT_01015ce4, DAT_01016ec0, DAT_0101cd6c, DAT_0101d860, DAT_0101da44, DAT_0101da8c, DAT_0101dbc8, DAT_0101fcc8, DAT_01025d2c, DAT_01025e1c, DAT_010260f8, DAT_01028340, DAT_010296e4, DAT_010297d0, DAT_0102cbdc (word at 0x0100E5AC); value 0x377BA882 (930850946) */
#define INTEGER_MINUS_51212 0xFFFF37F4   /* was DAT_0100e634 (word at 0x0100E634); integer -51212 */
#define WORD_HEXADECIMAL_00333333 0x00333333   /* was DAT_0100e638 (word at 0x0100E638); value 0x00333333 (3355443) */
#define DATA_AT_01001E64_OFFSET 0xFFFF37FC   /* was DAT_0100e6ac (word at 0x0100E6AC); PC-relative offset: + 0x100e668 (the pc) = 0x01001E64 */
#define DATA_AT_01001E6C_OFFSET 0xFFFF37F8   /* was DAT_0100e6b0 (word at 0x0100E6B0); PC-relative offset: + 0x100e674 (the pc) = 0x01001E6C */
#define INTEGER_MINUS_50892 0xFFFF3934   /* was DAT_0100e6b4 (word at 0x0100E6B4); integer -50892 */
#define INTEGER_MINUS_51068 0xFFFF3884   /* was DAT_0100e794 (word at 0x0100E794); integer -51068 */
#define INTEGER_MINUS_50960 0xFFFF38F0   /* was DAT_0100e8e8 (word at 0x0100E8E8); integer -50960 */
#define DATA_AT_01002614_OFFSET 0xFFFF3DB0   /* was DAT_0100e8ec (word at 0x0100E8EC); PC-relative offset: + 0x100e864 (the pc) = 0x01002614 */
#define DATA_AT_01002600_OFFSET 0xFFFF3D84   /* was DAT_0100e8f0 (word at 0x0100E8F0); PC-relative offset: + 0x100e87c (the pc) = 0x01002600 */
#define DATA_AT_0100263C_OFFSET 0xFFFF3DA8   /* was DAT_0100e8f4 (word at 0x0100E8F4); PC-relative offset: + 0x100e894 (the pc) = 0x0100263C */
#define DATA_AT_01001FC0_OFFSET 0xFFFF3714   /* was DAT_0100e8f8 (word at 0x0100E8F8); PC-relative offset: + 0x100e8ac (the pc) = 0x01001FC0 */
#define DATA_AT_010024DC_OFFSET 0xFFFF3BFC   /* was DAT_0100e8fc (word at 0x0100E8FC); PC-relative offset: + 0x100e8e0 (the pc) = 0x010024DC */
#define DATA_AT_0100203C_OFFSET_3 0xFFFF3664   /* was DAT_0100ea70 (word at 0x0100EA70); PC-relative offset: + 0x100e9d8 (the pc) = 0x0100203C */
#define DATA_AT_01001E5C_OFFSET_2 0xFFFF347C   /* was DAT_0100ea74 (word at 0x0100EA74); PC-relative offset: + 0x100e9e0 (the pc) = 0x01001E5C */
#define INTEGER_MINUS_51112 0xFFFF3858   /* was DAT_0100ea78 (word at 0x0100EA78); integer -51112 */
#define INTEGER_MINUS_50912 0xFFFF3920   /* was DAT_0100ea7c (word at 0x0100EA7C); integer -50912 */
#define INTEGER_MINUS_50200 0xFFFF3BE8   /* was DAT_0100ebf4 (word at 0x0100EBF4); integer -50200 */
#define INTEGER_MINUS_50204 0xFFFF3BE4   /* was DAT_0100ec9c (word at 0x0100EC9C); integer -50204 */
#define WORD_HEXADECIMAL_FFFC0000 0xFFFC0000   /* was DAT_0100f02c (word at 0x0100F02C); value 0xFFFC0000 (-262144) */
#define DATA_AT_0100203C_OFFSET_4 0xFFFF27F8   /* was DAT_0100f8dc (word at 0x0100F8DC); PC-relative offset: + 0x100f844 (the pc) = 0x0100203C */
#define DATA_AT_010023E0_OFFSET 0xFFFF2B90   /* was DAT_0100f8e0 (word at 0x0100F8E0); PC-relative offset: + 0x100f850 (the pc) = 0x010023E0 */
#define DATA_AT_01002664_OFFSET 0xFFFF2DFC   /* was DAT_0100f8e4 (word at 0x0100F8E4); PC-relative offset: + 0x100f868 (the pc) = 0x01002664 */
#define INTEGER_MINUS_65535 0xFFFF0001   /* was DAT_0100fabc (word at 0x0100FABC); integer -65535 */
#define DATA_AT_0104013C_OFFSET 0x0002F374   /* was DAT_01010ddc (word at 0x01010DDC); PC-relative offset: + 0x1010dc8 (the pc) = 0x0104013C */
#define WORD_HEXADECIMAL_7F7FFFFF 0x7F7FFFFF   /* was DAT_01010e80, DAT_010118f8, DAT_01016ec8 (word at 0x01010E80); value 0x7F7FFFFF (2139095039) */
#define FLOAT_MINUS_1 0xBF800000   /* was DAT_010118f4, DAT_01014b38, DAT_0101845c, DAT_01019eb8 (word at 0x010118F4); the float -1.0 */
#define FLOAT_3 0x40400000   /* was DAT_010118fc, DAT_0102469c, DAT_0102f460 (word at 0x010118FC); the float 3.0 */
#define DATA_AT_01042B10_OFFSET 0x00030DFC   /* was DAT_01011d50 (word at 0x01011D50); PC-relative offset: + 0x1011d14 (the pc) = 0x01042B10 */
#define DATA_AT_01042B08_OFFSET 0x00030D9C   /* was DAT_01011dd8 (word at 0x01011DD8); PC-relative offset: + 0x1011d6c (the pc) = 0x01042B08 */
#define DATA_AT_01042B10_OFFSET_2 0x00030D74   /* was DAT_01011ddc (word at 0x01011DDC); PC-relative offset: + 0x1011d9c (the pc) = 0x01042B10 */
#define DATA_AT_01042B10_OFFSET_3 0x00030C6C   /* was DAT_01011ee0 (word at 0x01011EE0); PC-relative offset: + 0x1011ea4 (the pc) = 0x01042B10 */
#define WORD_HEXADECIMAL_000300C6 0x000300C6   /* was DAT_01012320 (word at 0x01012320); value 0x000300C6 (196806) */
#define WORD_HEXADECIMAL_0010A000 0x0010A000   /* was DAT_0101240c (word at 0x0101240C); value 0x0010A000 (1089536) */
#define INTEGER_4392 0x00001128   /* was DAT_01012440 (word at 0x01012440); integer 4392 */
#define WORD_HEXADECIMAL_00204002 0x00204002   /* was DAT_01012474 (word at 0x01012474); value 0x00204002 (2113538) */
#define WORD_HEXADECIMAL_000C0408 0x000C0408   /* was DAT_010124a8 (word at 0x010124A8); value 0x000C0408 (787464) */
#define DATA_AT_0100203C_OFFSET_5 0xFFFEF948   /* was DAT_01012744 (word at 0x01012744); PC-relative offset: + 0x10126f4 (the pc) = 0x0100203C */
#define DATA_AT_01001E58_OFFSET 0xFFFEF758   /* was DAT_01012748 (word at 0x01012748); PC-relative offset: + 0x1012700 (the pc) = 0x01001E58 */
#define DATA_AT_010025FC_OFFSET 0xFFFEFEF4   /* was DAT_0101274c (word at 0x0101274C); PC-relative offset: + 0x1012708 (the pc) = 0x010025FC */
#define DATA_AT_01001EAC_OFFSET 0xFFFEF798   /* was DAT_01012750 (word at 0x01012750); PC-relative offset: + 0x1012714 (the pc) = 0x01001EAC */
#define DATA_AT_010025E8_OFFSET 0xFFFEFEB8   /* was DAT_01012754 (word at 0x01012754); PC-relative offset: + 0x1012730 (the pc) = 0x010025E8 */
#define ADDRESS_OF_FUNCTION_0101411c_OFFSET 0x000015E8   /* was DAT_01013020 (word at 0x01013020); PC-relative offset: + 0x1012b34 (the pc) = 0x0101411C */
#define HIGH_WORD_OF_DOUBLE_5_POINT_277655813_TIMES_TEN_TO_THE_14 0x42FE0000   /* was DAT_01013024 (word at 0x01013024); high word of the double 527765581332480.0, in a function that tests high words */
#define HIGH_WORD_OF_DOUBLE_5_POINT_373717307_TIMES_TEN_TO_THE_MINUS_17 0x3C8EFA35   /* was DAT_01013028 (word at 0x01013028); high word of the double 5.3737173072131703e-17, in a function that tests high words */
#define ADDRESS_OF_FUNCTION_0101420c_OFFSET 0x000014FC   /* was DAT_01013030 (word at 0x01013030); PC-relative offset: + 0x1012d10 (the pc) = 0x0101420C */
#define ADDRESS_OF_FUNCTION_01013e88_OFFSET 0x00000F9C   /* was DAT_01013034 (word at 0x01013034); PC-relative offset: + 0x1012eec (the pc) = 0x01013E88 */
#define DATA_AT_010024D8_OFFSET 0xFFFEF468   /* was DAT_010130a0 (word at 0x010130A0); PC-relative offset: + 0x1013070 (the pc) = 0x010024D8 */
#define DATA_AT_01001EAC_OFFSET_2 0xFFFEEE34   /* was DAT_010130a4 (word at 0x010130A4); PC-relative offset: + 0x1013078 (the pc) = 0x01001EAC */
#define WORD_HEXADECIMAL_FFFEF544 0xFFFEF544   /* was DAT_010130a8 (word at 0x010130A8); value 0xFFFEF544 (-68284) */
#define WORD_HEXADECIMAL_FFFF0000 0xFFFF0000   /* was DAT_01013e84 (word at 0x01013E84); value 0xFFFF0000 (-65536) */
#define INTEGER_MINUS_1103 0xFFFFFBB1   /* was DAT_010152d4, DAT_01015344 (word at 0x010152D4); integer -1103 */
#define STRING_READ_ERROR_OFFSET 0x0002A07C   /* was DAT_01015a3c (word at 0x01015A3C); PC-relative offset: + 0x1015a1c (the pc) = 0x0103FA98 */
#define ADDRESS_OF_FUNCTION_01027c84_OFFSET_2 0x00011CB0   /* was DAT_01016688 (word at 0x01016688); PC-relative offset: + 0x1015fd4 (the pc) = 0x01027C84 */
#define ADDRESS_OF_FUNCTION_01027c84_OFFSET_3 0x000119D8   /* was DAT_01016690 (word at 0x01016690); PC-relative offset: + 0x10162ac (the pc) = 0x01027C84 */
#define ADDRESS_OF_FUNCTION_01029bf4_OFFSET 0x000137B0   /* was DAT_01016694 (word at 0x01016694); PC-relative offset: + 0x1016444 (the pc) = 0x01029BF4 */
#define ADDRESS_OF_FUNCTION_01027c84_OFFSET_4 0x000117F8   /* was DAT_01016698 (word at 0x01016698); PC-relative offset: + 0x101648c (the pc) = 0x01027C84 */
#define ADDRESS_OF_FUNCTION_01029bf4_OFFSET_2 0x0001365C   /* was DAT_0101669c (word at 0x0101669C); PC-relative offset: + 0x1016598 (the pc) = 0x01029BF4 */
#define ADDRESS_OF_FUNCTION_01029bf4_OFFSET_3 0x000135C8   /* was DAT_010166a0 (word at 0x010166A0); PC-relative offset: + 0x101662c (the pc) = 0x01029BF4 */
#define FLOAT_255 0x437F0000   /* was DAT_01016d88, DAT_0101b80c, DAT_0101f994, DAT_010224f8, DAT_01022690, DAT_01022bb4 (word at 0x01016D88); the float 255.0 */
#define DATA_AT_01040134_OFFSET 0x000285AC   /* was DAT_01017bc0 (word at 0x01017BC0); PC-relative offset: + 0x1017b88 (the pc) = 0x01040134 */
#define DATA_AT_01040138_OFFSET_2 0x000284A8   /* was DAT_01017cc8 (word at 0x01017CC8); PC-relative offset: + 0x1017c90 (the pc) = 0x01040138 */
#define DATA_AT_01040138_OFFSET_3 0x000283C8   /* was DAT_01017dc0 (word at 0x01017DC0); PC-relative offset: + 0x1017d70 (the pc) = 0x01040138 */
#define DATA_AT_0100203C_OFFSET_6 0xFFFE9B74   /* was DAT_01018adc (word at 0x01018ADC); PC-relative offset: + 0x10184c8 (the pc) = 0x0100203C */
#define DATA_AT_01001EAC_OFFSET_3 0xFFFE99D8   /* was DAT_01018ae0 (word at 0x01018AE0); PC-relative offset: + 0x10184d4 (the pc) = 0x01001EAC */
#define WORD_HEXADECIMAL_FFFE9A14 0xFFFE9A14   /* was DAT_01018ae4 (word at 0x01018AE4); value 0xFFFE9A14 (-91628) */
#define INTEGER_21845 0x00005555   /* was DAT_01018ae8 (word at 0x01018AE8); integer 21845 */
#define WORD_HEXADECIMAL_7D710000 0x7D710000   /* was DAT_01018af0 (word at 0x01018AF0); value 0x7D710000 (2104557568) */
#define INTEGER_20416 0x00004FC0   /* was DAT_0101928c (word at 0x0101928C); integer 20416 */
#define INTEGER_3449 0x00000D79   /* was DAT_01019290 (word at 0x01019290); integer 3449 */
#define INTEGER_5958 0x00001746   /* was DAT_01019298 (word at 0x01019298); integer 5958 */
#define WORD_HEXADECIMAL_0002D3F8 0x0002D3F8   /* was DAT_010192a0 (word at 0x010192A0); value 0x0002D3F8 (185336) */
#define INTEGER_46341 0x0000B505   /* was DAT_010192a8 (word at 0x010192A8); integer 46341 */
#define INTEGER_10430 0x000028BE   /* was DAT_010192b0 (word at 0x010192B0); integer 10430 */
#define INTEGER_MINUS_1200 0xFFFFFB50   /* was DAT_010196c8, DAT_01019c0c, DAT_01026d80 (word at 0x010196C8); integer -1200 */
#define INTEGER_MINUS_1202 0xFFFFFB4E   /* was DAT_01019700, DAT_01019818, DAT_01019884, DAT_010198c4, DAT_0101991c, DAT_01019a94, DAT_0101de28, DAT_0101df60, DAT_0101e280, DAT_0101e3f0, DAT_0101e52c, DAT_0101e770, DAT_0101ea90, DAT_0101eaf8, DAT_0101f020, DAT_0101f3d4, DAT_0101f638, DAT_0101f8a8, DAT_0101f990, DAT_0101fb20, DAT_0101fcc0, DAT_0101fdc0 (word at 0x01019700); integer -1202 */
#define WORD_HEXADECIMAL_3C8EFA35 0x3C8EFA35   /* was DAT_01019eb4, DAT_0101ef3c, DAT_0103baa0, DAT_0103c348, DAT_0103c448, DAT_0103c5e0 (word at 0x01019EB4); value 0x3C8EFA35 (1016003125) */
#define WORD_HEXADECIMAL_4D7FF000 0x4D7FF000   /* was DAT_0101bd40, DAT_0101d178 (word at 0x0101BD40); value 0x4D7FF000 (1300230144) */
#define HIGH_WORD_OF_DOUBLE_1_POINT_396115884_TIMES_TEN_TO_THE_17 0x437F0000   /* was DAT_0101cd58 (word at 0x0101CD58); high word of the double 1.3961158844848538e+17, in a function that tests high words */
#define HIGH_WORD_OF_DOUBLE_5_POINT_277655813_TIMES_TEN_TO_THE_13 0x42C80000   /* was DAT_0101cd64 (word at 0x0101CD64); high word of the double 52776558133248.0, in a function that tests high words */
#define HIGH_WORD_OF_DOUBLE_MINUS_5_POINT_277655813_TIMES_TEN_TO_THE_13 0xC2C80000   /* was DAT_0101cd68 (word at 0x0101CD68); high word of the double -52776558133248.0, in a function that tests high words */
#define WORD_HEXADECIMAL_000262B0 0x000262B0   /* was DAT_0101cd70 (word at 0x0101CD70); value 0x000262B0 (156336) */
#define FLOAT_4095 0x457FF000   /* was DAT_0101d54c (word at 0x0101D54C); the float 4095.0 */
#define DATA_AT_01002628_OFFSET_2 0xFFFE4634   /* was DAT_0101e0ac (word at 0x0101E0AC); PC-relative offset: + 0x101dff4 (the pc) = 0x01002628 */
#define FLOAT_90 0x42B40000   /* was DAT_0101fb24, DAT_010228fc, DAT_0103328c (word at 0x0101FB24); the float 90.0 */
#define HIGH_WORD_OF_DOUBLE_5_POINT_629499534_TIMES_TEN_TO_THE_15 0x43340000   /* was DAT_0101fcc4 (word at 0x0101FCC4); high word of the double 5629499534213120.0, in a function that tests high words */
#define DATA_AT_0100203C_OFFSET_7 0xFFFE2000   /* was DAT_010200f8 (word at 0x010200F8); PC-relative offset: + 0x102003c (the pc) = 0x0100203C */
#define DATA_AT_01002890_OFFSET 0xFFFE2848   /* was DAT_010200fc (word at 0x010200FC); PC-relative offset: + 0x1020048 (the pc) = 0x01002890 */
#define DATA_AT_010023CC_OFFSET 0xFFFE236C   /* was DAT_01020100 (word at 0x01020100); PC-relative offset: + 0x1020060 (the pc) = 0x010023CC */
#define ADDRESS_OF_FUNCTION_0100a820_OFFSET_2 0xFFFE9624   /* was DAT_01021a70 (word at 0x01021A70); PC-relative offset: + 0x10211fc (the pc) = 0x0100A820 */
#define ADDRESS_OF_swv_SpanFillTextured_OFFSET_2 0xFFFECDE0   /* was DAT_01021a74 (word at 0x01021A74); PC-relative offset: + 0x102120c (the pc) = 0x0100DFEC */
#define WORD_HEXADECIMAL_46FFFF00 0x46FFFF00   /* was DAT_01022138 (word at 0x01022138); value 0x46FFFF00 (1191182080) */
#define FLOAT_127_POINT_5 0x42FF0000   /* was DAT_0102213c (word at 0x0102213C); the float 127.5 */
#define WORD_HEXADECIMAL_4E800000 0x4E800000   /* was DAT_010230ec (word at 0x010230EC); value 0x4E800000 (1317011456) */
#define DATA_AT_01002628_OFFSET_3 0xFFFDEBE0   /* was DAT_01023aec (word at 0x01023AEC); PC-relative offset: + 0x1023a48 (the pc) = 0x01002628 */
#define INTEGER_1023 0x000003FF   /* was DAT_01023c58 (word at 0x01023C58); integer 1023 */
#define HIGH_WORD_OF_DOUBLE_0_POINT_007806248963 0x3F7FF972   /* was DAT_01024690 (word at 0x01024690); high word of the double 0.007806248962879181, in a function that tests high words */
#define HIGH_WORD_OF_DOUBLE_0_POINT_007813438773 0x3F80007E   /* was DAT_010260fc (word at 0x010260FC); high word of the double 0.007813438773155212, in a function that tests high words */
#define STRING_UNKNOWN_COMPRESSION_METHOD_OFFSET 0x000191F8   /* was DAT_01027268 (word at 0x01027268); PC-relative offset: + 0x1026e5c (the pc) = 0x01040054 */
#define STRING_INVALID_WINDOW_SIZE_OFFSET 0x000191F8   /* was DAT_0102726c (word at 0x0102726C); PC-relative offset: + 0x1026e78 (the pc) = 0x01040070 */
#define STRING_INCORRECT_HEADER_CHECK_OFFSET 0x000191AC   /* was DAT_01027270 (word at 0x01027270); PC-relative offset: + 0x1026ed8 (the pc) = 0x01040084 */
#define STRING_NEED_DICTIONARY_OFFSET 0x00019044   /* was DAT_01027274 (word at 0x01027274); PC-relative offset: + 0x1027058 (the pc) = 0x0104009C */
#define STRING_INCORRECT_DATA_CHECK_OFFSET 0x00018E70   /* was DAT_01027278 (word at 0x01027278); PC-relative offset: + 0x102723c (the pc) = 0x010400AC */
#define FLOAT_1024 0x44800000   /* was DAT_010275f4 (word at 0x010275F4); the float 1024.0 */
#define FLOAT_256 0x43800000   /* was DAT_010275f8 (word at 0x010275F8); the float 256.0 */
#define DATA_AT_01001DAC_OFFSET 0xFFFDA228   /* was DAT_01027be4 (word at 0x01027BE4); PC-relative offset: + 0x1027b84 (the pc) = 0x01001DAC */
#define DATA_AT_01001DB4_OFFSET 0xFFFDA224   /* was DAT_01027be8 (word at 0x01027BE8); PC-relative offset: + 0x1027b90 (the pc) = 0x01001DB4 */
#define DATA_AT_01001EAC_OFFSET_4 0xFFFDA314   /* was DAT_01027bec (word at 0x01027BEC); PC-relative offset: + 0x1027b98 (the pc) = 0x01001EAC */
#define WORD_HEXADECIMAL_FFFDA3F8 0xFFFDA3F8   /* was DAT_01027bf0 (word at 0x01027BF0); value 0xFFFDA3F8 (-154632) */
#define DATA_AT_01001DF0_OFFSET 0xFFFDA1F0   /* was DAT_01027c28 (word at 0x01027C28); PC-relative offset: + 0x1027c00 (the pc) = 0x01001DF0 */
#define DATA_AT_01001EAC_OFFSET_5 0xFFFDA2A0   /* was DAT_01027c2c (word at 0x01027C2C); PC-relative offset: + 0x1027c0c (the pc) = 0x01001EAC */
#define DATA_AT_01002348_OFFSET 0xFFFDA724   /* was DAT_01027c30 (word at 0x01027C30); PC-relative offset: + 0x1027c24 (the pc) = 0x01002348 */
#define DATA_AT_0100203C_OFFSET_8 0xFFFDA3FC   /* was DAT_01027c78 (word at 0x01027C78); PC-relative offset: + 0x1027c40 (the pc) = 0x0100203C */
#define DATA_AT_01001E5C_OFFSET_3 0xFFFDA214   /* was DAT_01027c7c (word at 0x01027C7C); PC-relative offset: + 0x1027c48 (the pc) = 0x01001E5C */
#define WORD_HEXADECIMAL_FFFDA1D4 0xFFFDA1D4   /* was DAT_01027c80 (word at 0x01027C80); value 0xFFFDA1D4 (-155180) */
#define DATA_AT_01001EAC_OFFSET_6 0xFFFDA1EC   /* was DAT_01027cd4 (word at 0x01027CD4); PC-relative offset: + 0x1027cc0 (the pc) = 0x01001EAC */
#define DATA_AT_01001ED4_OFFSET 0xFFFDA1E0   /* was DAT_01027cf8 (word at 0x01027CF8); PC-relative offset: + 0x1027cf4 (the pc) = 0x01001ED4 */
#define WORD_HEXADECIMAL_FFFDA1EC 0xFFFDA1EC   /* was DAT_01027d64 (word at 0x01027D64); value 0xFFFDA1EC (-155156) */
#define DATA_AT_0100203C_OFFSET_9 0xFFFDA2C0   /* was DAT_01027db0 (word at 0x01027DB0); PC-relative offset: + 0x1027d7c (the pc) = 0x0100203C */
#define DATA_AT_01001E5C_OFFSET_4 0xFFFDA0D8   /* was DAT_01027db4 (word at 0x01027DB4); PC-relative offset: + 0x1027d84 (the pc) = 0x01001E5C */
#define WORD_HEXADECIMAL_FFFDA1BC 0xFFFDA1BC   /* was DAT_01027db8 (word at 0x01027DB8); value 0xFFFDA1BC (-155204) */
#define WORD_HEXADECIMAL_FFFDA14C 0xFFFDA14C   /* was DAT_01027e68 (word at 0x01027E68); value 0xFFFDA14C (-155316) */
#define DATA_AT_01001FC0_OFFSET_2 0xFFFDA138   /* was DAT_01027e8c (word at 0x01027E8C); PC-relative offset: + 0x1027e88 (the pc) = 0x01001FC0 */
#define DATA_AT_0100200C_OFFSET 0xFFFDA140   /* was DAT_01027ed0 (word at 0x01027ED0); PC-relative offset: + 0x1027ecc (the pc) = 0x0100200C */
#define DATA_AT_01002018_OFFSET 0xFFFDA138   /* was DAT_01027ee8 (word at 0x01027EE8); PC-relative offset: + 0x1027ee0 (the pc) = 0x01002018 */
#define DATA_AT_0100203C_OFFSET_10 0xFFFDA13C   /* was DAT_01028018 (word at 0x01028018); PC-relative offset: + 0x1027f00 (the pc) = 0x0100203C */
#define DATA_AT_01001E5C_OFFSET_5 0xFFFD9F50   /* was DAT_0102801c (word at 0x0102801C); PC-relative offset: + 0x1027f0c (the pc) = 0x01001E5C */
#define DATA_AT_0100201C_OFFSET 0xFFFDA100   /* was DAT_01028020 (word at 0x01028020); PC-relative offset: + 0x1027f1c (the pc) = 0x0100201C */
#define DATA_AT_01002024_OFFSET 0xFFFDA0FC   /* was DAT_01028024 (word at 0x01028024); PC-relative offset: + 0x1027f28 (the pc) = 0x01002024 */
#define DATA_AT_010023F8_OFFSET 0xFFFDA400   /* was DAT_01028028 (word at 0x01028028); PC-relative offset: + 0x1027ff8 (the pc) = 0x010023F8 */
#define DATA_AT_010023E4_OFFSET 0xFFFDA3D4   /* was DAT_0102802c (word at 0x0102802C); PC-relative offset: + 0x1028010 (the pc) = 0x010023E4 */
#define WORD_HEXADECIMAL_FFFD9BF8 0xFFFD9BF8   /* was DAT_01028460 (word at 0x01028460); value 0xFFFD9BF8 (-156680) */
#define WORD_HEXADECIMAL_FFFD9BE8 0xFFFD9BE8   /* was DAT_010285e4 (word at 0x010285E4); value 0xFFFD9BE8 (-156696) */
#define ADDRESS_OF_FUNCTION_010294dc_OFFSET 0x00000FE0   /* was DAT_010285e8 (word at 0x010285E8); PC-relative offset: + 0x10284fc (the pc) = 0x010294DC */
#define WORD_HEXADECIMAL_31417926 0x31417926   /* was DAT_010285ec (word at 0x010285EC); value 0x31417926 (826374438) */
#define FLOAT_0_POINT_698 0x3F32B021   /* was DAT_010285f0 (word at 0x010285F0); the float 0.6980000138282776 */
#define FLOAT_0_POINT_3 0x3E99999A   /* was DAT_010285f4 (word at 0x010285F4); the float 0.30000001192092896 */
#define FLOAT_0_POINT_8 0x3F4CCCCD   /* was DAT_010285f8 (word at 0x010285F8); the float 0.800000011920929 */
#define WORD_HEXADECIMAL_FFFD9AA8 0xFFFD9AA8   /* was DAT_0102862c (word at 0x0102862C); value 0xFFFD9AA8 (-157016) */
#define DATA_AT_0100203C_OFFSET_11 0xFFFD99F8   /* was DAT_010286d0 (word at 0x010286D0); PC-relative offset: + 0x1028644 (the pc) = 0x0100203C */
#define DATA_AT_01001E5C_OFFSET_6 0xFFFD9810   /* was DAT_010286d4 (word at 0x010286D4); PC-relative offset: + 0x102864c (the pc) = 0x01001E5C */
#define WORD_HEXADECIMAL_FFFD9A98 0xFFFD9A98   /* was DAT_010286d8 (word at 0x010286D8); value 0xFFFD9A98 (-157032) */
#define DATA_AT_01002174_OFFSET 0xFFFD9A80   /* was DAT_01028748 (word at 0x01028748); PC-relative offset: + 0x10286f4 (the pc) = 0x01002174 */
#define DATA_AT_0100217C_OFFSET 0xFFFD9A7C   /* was DAT_0102874c (word at 0x0102874C); PC-relative offset: + 0x1028700 (the pc) = 0x0100217C */
#define WORD_HEXADECIMAL_FFFD9794 0xFFFD9794   /* was DAT_01028750 (word at 0x01028750); value 0xFFFD9794 (-157804) */
#define WORD_HEXADECIMAL_FFFD987C 0xFFFD987C   /* was DAT_01028754 (word at 0x01028754); value 0xFFFD987C (-157572) */
#define DATA_AT_0100203C_OFFSET_12 0xFFFD98D8   /* was DAT_010287b8 (word at 0x010287B8); PC-relative offset: + 0x1028764 (the pc) = 0x0100203C */
#define DATA_AT_01001E5C_OFFSET_7 0xFFFD96F0   /* was DAT_010287bc (word at 0x010287BC); PC-relative offset: + 0x102876c (the pc) = 0x01001E5C */
#define WORD_HEXADECIMAL_FFFD9A30 0xFFFD9A30   /* was DAT_010287c0 (word at 0x010287C0); value 0xFFFD9A30 (-157136) */
#define WORD_HEXADECIMAL_FFFD9714 0xFFFD9714   /* was DAT_010287c4 (word at 0x010287C4); value 0xFFFD9714 (-157932) */
#define DATA_AT_01001FAC_OFFSET 0xFFFD97F8   /* was DAT_010287c8 (word at 0x010287C8); PC-relative offset: + 0x10287b4 (the pc) = 0x01001FAC */
#define WORD_HEXADECIMAL_FFFD99E0 0xFFFD99E0   /* was DAT_0102884c (word at 0x0102884C); value 0xFFFD99E0 (-157216) */
#define DATA_AT_01001EE8_OFFSET_2 0xFFFD96D4   /* was DAT_01028850 (word at 0x01028850); PC-relative offset: + 0x1028814 (the pc) = 0x01001EE8 */
#define DATA_AT_01002584_OFFSET 0xFFFD9D58   /* was DAT_01028854 (word at 0x01028854); PC-relative offset: + 0x102882c (the pc) = 0x01002584 */
#define DATA_AT_01001ED4_OFFSET_2 0xFFFD9690   /* was DAT_01028858 (word at 0x01028858); PC-relative offset: + 0x1028844 (the pc) = 0x01001ED4 */
#define DATA_AT_0100220C_OFFSET 0xFFFD9988   /* was DAT_01028894 (word at 0x01028894); PC-relative offset: + 0x1028884 (the pc) = 0x0100220C */
#define WORD_HEXADECIMAL_FFFD9960 0xFFFD9960   /* was DAT_01028940 (word at 0x01028940); value 0xFFFD9960 (-157344) */
#define INTEGER_MINUS_3168 0xFFFFF3A0   /* was DAT_01028944 (word at 0x01028944); integer -3168 */
#define DATA_AT_010427A8_OFFSET 0x00019E48   /* was DAT_01028974 (word at 0x01028974); PC-relative offset: + 0x1028960 (the pc) = 0x010427A8 */
#define DATA_AT_01002260_OFFSET 0xFFFD98F4   /* was DAT_01028978 (word at 0x01028978); PC-relative offset: + 0x102896c (the pc) = 0x01002260 */
#define DATA_AT_0104279C_OFFSET 0x00019E08   /* was DAT_010289a8 (word at 0x010289A8); PC-relative offset: + 0x1028994 (the pc) = 0x0104279C */
#define DATA_AT_01002264_OFFSET 0xFFFD98C4   /* was DAT_010289ac (word at 0x010289AC); PC-relative offset: + 0x10289a0 (the pc) = 0x01002264 */
#define WORD_HEXADECIMAL_FFFD97D8 0xFFFD97D8   /* was DAT_01028ab8 (word at 0x01028AB8); value 0xFFFD97D8 (-157736) */
#define WORD_HEXADECIMAL_FFFD97C8 0xFFFD97C8   /* was DAT_01028af8 (word at 0x01028AF8); value 0xFFFD97C8 (-157752) */
#define DATA_AT_010022D4_OFFSET 0xFFFD97C0   /* was DAT_01028b24 (word at 0x01028B24); PC-relative offset: + 0x1028b14 (the pc) = 0x010022D4 */
#define DATA_AT_010022E0_OFFSET 0xFFFD97A0   /* was DAT_01028b54 (word at 0x01028B54); PC-relative offset: + 0x1028b40 (the pc) = 0x010022E0 */
#define WORD_HEXADECIMAL_FFFD977C 0xFFFD977C   /* was DAT_01028bac (word at 0x01028BAC); value 0xFFFD977C (-157828) */
#define DATA_AT_0100235C_OFFSET 0xFFFD9784   /* was DAT_01028cb0 (word at 0x01028CB0); PC-relative offset: + 0x1028bd8 (the pc) = 0x0100235C */
#define DATA_AT_01001EAC_OFFSET_7 0xFFFD92B4   /* was DAT_01028cb4 (word at 0x01028CB4); PC-relative offset: + 0x1028bf8 (the pc) = 0x01001EAC */
#define WORD_HEXADECIMAL_FFFD9964 0xFFFD9964   /* was DAT_01028cb8 (word at 0x01028CB8); value 0xFFFD9964 (-157340) */
#define WORD_HEXADECIMAL_FFFD92C0 0xFFFD92C0   /* was DAT_01028cbc (word at 0x01028CBC); value 0xFFFD92C0 (-159040) */
#define WORD_HEXADECIMAL_FFFD9340 0xFFFD9340   /* was DAT_01028cc0 (word at 0x01028CC0); value 0xFFFD9340 (-158912) */
#define WORD_HEXADECIMAL_FFFD9868 0xFFFD9868   /* was DAT_01028cc4 (word at 0x01028CC4); value 0xFFFD9868 (-157592) */
#define WORD_HEXADECIMAL_FFFD9680 0xFFFD9680   /* was DAT_01028d28 (word at 0x01028D28); value 0xFFFD9680 (-158080) */
#define DATA_AT_01002398_OFFSET 0xFFFD9658   /* was DAT_01028f2c (word at 0x01028F2C); PC-relative offset: + 0x1028d40 (the pc) = 0x01002398 */
#define DATA_AT_01001EAC_OFFSET_8 0xFFFD915C   /* was DAT_01028f30 (word at 0x01028F30); PC-relative offset: + 0x1028d50 (the pc) = 0x01001EAC */
#define WORD_HEXADECIMAL_FFFD98E8 0xFFFD98E8   /* was DAT_01028f34 (word at 0x01028F34); value 0xFFFD98E8 (-157464) */
#define WORD_HEXADECIMAL_FFFD9764 0xFFFD9764   /* was DAT_01028f38 (word at 0x01028F38); value 0xFFFD9764 (-157852) */
#define ADDRESS_OF_FUNCTION_01028bb0_OFFSET 0xFFFFFD88   /* was DAT_01028f3c (word at 0x01028F3C); PC-relative offset: + 0x1028e28 (the pc) = 0x01028BB0 */
#define WORD_HEXADECIMAL_FFFD9154 0xFFFD9154   /* was DAT_01028f40 (word at 0x01028F40); value 0xFFFD9154 (-159404) */
#define WORD_HEXADECIMAL_FFFD9668 0xFFFD9668   /* was DAT_01028f44 (word at 0x01028F44); value 0xFFFD9668 (-158104) */
#define WORD_HEXADECIMAL_FFFD9730 0xFFFD9730   /* was DAT_01028f48 (word at 0x01028F48); value 0xFFFD9730 (-157904) */
#define WORD_HEXADECIMAL_FFFD9100 0xFFFD9100   /* was DAT_01028f4c (word at 0x01028F4C); value 0xFFFD9100 (-159488) */
#define INTEGER_MINUS_4376 0xFFFFEEE8   /* was DAT_01028f50 (word at 0x01028F50); integer -4376 */
#define DATA_AT_0100240C_OFFSET 0xFFFD94A4   /* was DAT_0102900c (word at 0x0102900C); PC-relative offset: + 0x1028f68 (the pc) = 0x0100240C */
#define DATA_AT_01002410_OFFSET 0xFFFD93E8   /* was DAT_010290b0 (word at 0x010290B0); PC-relative offset: + 0x1029028 (the pc) = 0x01002410 */
#define DATA_AT_01002438_OFFSET 0xFFFD9404   /* was DAT_010290b4 (word at 0x010290B4); PC-relative offset: + 0x1029034 (the pc) = 0x01002438 */
#define DATA_AT_01002598_OFFSET 0xFFFD9534   /* was DAT_010290b8 (word at 0x010290B8); PC-relative offset: + 0x1029064 (the pc) = 0x01002598 */
#define DATA_AT_01001EC0_OFFSET 0xFFFD8E44   /* was DAT_010290bc (word at 0x010290BC); PC-relative offset: + 0x102907c (the pc) = 0x01001EC0 */
#define DATA_AT_01001EE8_OFFSET_3 0xFFFD8E54   /* was DAT_010290c0 (word at 0x010290C0); PC-relative offset: + 0x1029094 (the pc) = 0x01001EE8 */
#define WORD_HEXADECIMAL_FFFD9378 0xFFFD9378   /* was DAT_0102910c (word at 0x0102910C); value 0xFFFD9378 (-158856) */
#define WORD_HEXADECIMAL_FFFD92B8 0xFFFD92B8   /* was DAT_01029204 (word at 0x01029204); value 0xFFFD92B8 (-159048) */
#define DATA_AT_01002558_OFFSET 0xFFFD9328   /* was DAT_0102925c (word at 0x0102925C); PC-relative offset: + 0x1029230 (the pc) = 0x01002558 */
#define DATA_AT_01001EAC_OFFSET_9 0xFFFD8C74   /* was DAT_01029260 (word at 0x01029260); PC-relative offset: + 0x1029238 (the pc) = 0x01001EAC */
#define WORD_HEXADECIMAL_FFFD92F0 0xFFFD92F0   /* was DAT_01029264 (word at 0x01029264); value 0xFFFD92F0 (-158992) */
#define DATA_AT_01002554_OFFSET 0xFFFD92E0   /* was DAT_010292ac (word at 0x010292AC); PC-relative offset: + 0x1029274 (the pc) = 0x01002554 */
#define DATA_AT_01001EAC_OFFSET_10 0xFFFD8C30   /* was DAT_010292b0 (word at 0x010292B0); PC-relative offset: + 0x102927c (the pc) = 0x01001EAC */
#define WORD_HEXADECIMAL_FFFD8D18 0xFFFD8D18   /* was DAT_010292b4 (word at 0x010292B4); value 0xFFFD8D18 (-160488) */
#define WORD_HEXADECIMAL_FFFD93A8 0xFFFD93A8   /* was DAT_01029300 (word at 0x01029300); value 0xFFFD93A8 (-158808) */
#define WORD_HEXADECIMAL_FFFD9394 0xFFFD9394   /* was DAT_01029364 (word at 0x01029364); value 0xFFFD9394 (-158828) */
#define DATA_AT_0100255C_OFFSET 0xFFFD9218   /* was DAT_01029368 (word at 0x01029368); PC-relative offset: + 0x1029344 (the pc) = 0x0100255C */
#define DATA_AT_0100252C_OFFSET 0xFFFD91D0   /* was DAT_0102936c (word at 0x0102936C); PC-relative offset: + 0x102935c (the pc) = 0x0100252C */
#define WORD_HEXADECIMAL_FFFD9370 0xFFFD9370   /* was DAT_010293d0 (word at 0x010293D0); value 0xFFFD9370 (-158864) */
#define DATA_AT_0100203C_OFFSET_13 0xFFFD8C4C   /* was DAT_0102943c (word at 0x0102943C); PC-relative offset: + 0x10293f0 (the pc) = 0x0100203C */
#define DATA_AT_01001E5C_OFFSET_8 0xFFFD8A64   /* was DAT_01029440 (word at 0x01029440); PC-relative offset: + 0x10293f8 (the pc) = 0x01001E5C */
#define WORD_HEXADECIMAL_FFFD9324 0xFFFD9324   /* was DAT_01029444 (word at 0x01029444); value 0xFFFD9324 (-158940) */
#define WORD_HEXADECIMAL_FFFD8A94 0xFFFD8A94   /* was DAT_01029448 (word at 0x01029448); value 0xFFFD8A94 (-161132) */
#define WORD_HEXADECIMAL_FFFD8B80 0xFFFD8B80   /* was DAT_0102944c (word at 0x0102944C); value 0xFFFD8B80 (-160896) */
#define WORD_HEXADECIMAL_FFFD9224 0xFFFD9224   /* was DAT_0102953c (word at 0x0102953C); value 0xFFFD9224 (-159196) */
#define DATA_AT_010027D0_OFFSET 0xFFFD9278   /* was DAT_0102959c (word at 0x0102959C); PC-relative offset: + 0x1029558 (the pc) = 0x010027D0 */
#define DATA_AT_010027D8_OFFSET 0xFFFD9274   /* was DAT_010295a0 (word at 0x010295A0); PC-relative offset: + 0x1029564 (the pc) = 0x010027D8 */
#define WORD_HEXADECIMAL_FFFD8934 0xFFFD8934   /* was DAT_010295a4 (word at 0x010295A4); value 0xFFFD8934 (-161484) */
#define DATA_AT_010024C4_OFFSET 0xFFFD8F30   /* was DAT_010295a8 (word at 0x010295A8); PC-relative offset: + 0x1029594 (the pc) = 0x010024C4 */
#define WORD_HEXADECIMAL_FFFD924C 0xFFFD924C   /* was DAT_01029618 (word at 0x01029618); value 0xFFFD924C (-159156) */
#define WORD_HEXADECIMAL_42652EE1 0x42652EE1   /* was DAT_0102961c (word at 0x0102961C); value 0x42652EE1 (1113927393) */
#define WORD_HEXADECIMAL_FFFD8480 0xFFFD8480   /* was DAT_01029988 (word at 0x01029988); value 0xFFFD8480 (-162688) */
#define DATA_AT_01001FAC_OFFSET_2 0xFFFD8668   /* was DAT_0102998c (word at 0x0102998C); PC-relative offset: + 0x1029944 (the pc) = 0x01001FAC */
#define DATA_AT_0100203C_OFFSET_14 0xFFFD86D4   /* was DAT_01029990 (word at 0x01029990); PC-relative offset: + 0x1029968 (the pc) = 0x0100203C */
#define DATA_AT_01001DF0_OFFSET_2 0xFFFD8438   /* was DAT_01029a04 (word at 0x01029A04); PC-relative offset: + 0x10299b8 (the pc) = 0x01001DF0 */
#define DATA_AT_01002348_OFFSET_2 0xFFFD8980   /* was DAT_01029a08 (word at 0x01029A08); PC-relative offset: + 0x10299c8 (the pc) = 0x01002348 */
#define DATA_AT_0100203C_OFFSET_15 0xFFFD8650   /* was DAT_01029a0c (word at 0x01029A0C); PC-relative offset: + 0x10299ec (the pc) = 0x0100203C */
#define WORD_HEXADECIMAL_FFFD83CC 0xFFFD83CC   /* was DAT_01029a50 (word at 0x01029A50); value 0xFFFD83CC (-162868) */
#define WORD_HEXADECIMAL_FFFD83C0 0xFFFD83C0   /* was DAT_01029ab4 (word at 0x01029AB4); value 0xFFFD83C0 (-162880) */
#define DATA_AT_01001E5C_OFFSET_9 0xFFFD83C4   /* was DAT_01029ab8 (word at 0x01029AB8); PC-relative offset: + 0x1029a98 (the pc) = 0x01001E5C */
#define DATA_AT_0100203C_OFFSET_16 0xFFFD859C   /* was DAT_01029abc (word at 0x01029ABC); PC-relative offset: + 0x1029aa0 (the pc) = 0x0100203C */
#define DATA_AT_010025E8_OFFSET_2 0xFFFD8AFC   /* was DAT_01029b4c (word at 0x01029B4C); PC-relative offset: + 0x1029aec (the pc) = 0x010025E8 */
#define INTEGER_10888 0x00002A88   /* was DAT_01029b50 (word at 0x01029B50); integer 10888 */
#define DATA_AT_0100203C_OFFSET_17 0xFFFD850C   /* was DAT_01029b54 (word at 0x01029B54); PC-relative offset: + 0x1029b30 (the pc) = 0x0100203C */
#define DATA_AT_0100203C_OFFSET_18 0xFFFD8430   /* was DAT_01029c10 (word at 0x01029C10); PC-relative offset: + 0x1029c0c (the pc) = 0x0100203C */
#define DATA_AT_01001EC0_OFFSET_2 0xFFFD8294   /* was DAT_01029c64 (word at 0x01029C64); PC-relative offset: + 0x1029c2c (the pc) = 0x01001EC0 */
#define DATA_AT_0100203C_OFFSET_19 0xFFFD83EC   /* was DAT_01029c68 (word at 0x01029C68); PC-relative offset: + 0x1029c50 (the pc) = 0x0100203C */
#define DATA_AT_01001EFC_OFFSET 0xFFFD81C8   /* was DAT_01029d6c (word at 0x01029D6C); PC-relative offset: + 0x1029d34 (the pc) = 0x01001EFC */
#define DATA_AT_0100203C_OFFSET_20 0xFFFD82E4   /* was DAT_01029d70 (word at 0x01029D70); PC-relative offset: + 0x1029d58 (the pc) = 0x0100203C */
#define WORD_HEXADECIMAL_FFFD8184 0xFFFD8184   /* was DAT_01029dc4 (word at 0x01029DC4); value 0xFFFD8184 (-163452) */
#define WORD_HEXADECIMAL_FFFD814C 0xFFFD814C   /* was DAT_01029eb4 (word at 0x01029EB4); value 0xFFFD814C (-163508) */
#define DATA_AT_01001FAC_OFFSET_3 0xFFFD80DC   /* was DAT_01029f08 (word at 0x01029F08); PC-relative offset: + 0x1029ed0 (the pc) = 0x01001FAC */
#define DATA_AT_0100203C_OFFSET_21 0xFFFD8148   /* was DAT_01029f0c (word at 0x01029F0C); PC-relative offset: + 0x1029ef4 (the pc) = 0x0100203C */
#define DATA_AT_0100203C_OFFSET_22 0xFFFD8054   /* was DAT_01029ff4 (word at 0x01029FF4); PC-relative offset: + 0x1029fe8 (the pc) = 0x0100203C */
#define DATA_AT_01002260_OFFSET_2 0xFFFD7A80   /* was DAT_0102a800 (word at 0x0102A800); PC-relative offset: + 0x102a7e0 (the pc) = 0x01002260 */
#define WORD_HEXADECIMAL_FFFD79BC 0xFFFD79BC   /* was DAT_0102a90c (word at 0x0102A90C); value 0xFFFD79BC (-165444) */
#define WORD_HEXADECIMAL_FFFD7974 0xFFFD7974   /* was DAT_0102a970 (word at 0x0102A970); value 0xFFFD7974 (-165516) */
#define WORD_HEXADECIMAL_FFFD70E8 0xFFFD70E8   /* was DAT_0102b3cc (word at 0x0102B3CC); value 0xFFFD70E8 (-167704) */
#define DATA_AT_010024C4_OFFSET_2 0xFFFD70DC   /* was DAT_0102b420 (word at 0x0102B420); PC-relative offset: + 0x102b3e8 (the pc) = 0x010024C4 */
#define DATA_AT_0100203C_OFFSET_23 0xFFFD6C30   /* was DAT_0102b424 (word at 0x0102B424); PC-relative offset: + 0x102b40c (the pc) = 0x0100203C */
#define DATA_AT_01002540_OFFSET 0xFFFD7060   /* was DAT_0102b51c (word at 0x0102B51C); PC-relative offset: + 0x102b4e0 (the pc) = 0x01002540 */
#define DATA_AT_0100203C_OFFSET_24 0xFFFD6B38   /* was DAT_0102b520 (word at 0x0102B520); PC-relative offset: + 0x102b504 (the pc) = 0x0100203C */
#define DATA_AT_010024DC_OFFSET_2 0xFFFD6FA0   /* was DAT_0102b598 (word at 0x0102B598); PC-relative offset: + 0x102b53c (the pc) = 0x010024DC */
#define INTEGER_MINUS_6488 0xFFFFE6A8   /* was DAT_0102b59c (word at 0x0102B59C); integer -6488 */
#define DATA_AT_0100203C_OFFSET_25 0xFFFD6AB8   /* was DAT_0102b5a0 (word at 0x0102B5A0); PC-relative offset: + 0x102b584 (the pc) = 0x0100203C */
#define DATA_AT_01002504_OFFSET 0xFFFD6EF0   /* was DAT_0102b64c (word at 0x0102B64C); PC-relative offset: + 0x102b614 (the pc) = 0x01002504 */
#define DATA_AT_0100203C_OFFSET_26 0xFFFD6A04   /* was DAT_0102b650 (word at 0x0102B650); PC-relative offset: + 0x102b638 (the pc) = 0x0100203C */
#define DATA_AT_01002518_OFFSET 0xFFFD6EAC   /* was DAT_0102b6c8 (word at 0x0102B6C8); PC-relative offset: + 0x102b66c (the pc) = 0x01002518 */
#define INTEGER_MINUS_5824 0xFFFFE940   /* was DAT_0102b6cc (word at 0x0102B6CC); integer -5824 */
#define DATA_AT_0100203C_OFFSET_27 0xFFFD6988   /* was DAT_0102b6d0 (word at 0x0102B6D0); PC-relative offset: + 0x102b6b4 (the pc) = 0x0100203C */
#define DATA_AT_0100252C_OFFSET_2 0xFFFD6E40   /* was DAT_0102b724 (word at 0x0102B724); PC-relative offset: + 0x102b6ec (the pc) = 0x0100252C */
#define DATA_AT_0100203C_OFFSET_28 0xFFFD692C   /* was DAT_0102b728 (word at 0x0102B728); PC-relative offset: + 0x102b710 (the pc) = 0x0100203C */
#define DATA_AT_01002540_OFFSET_2 0xFFFD6DFC   /* was DAT_0102b77c (word at 0x0102B77C); PC-relative offset: + 0x102b744 (the pc) = 0x01002540 */
#define DATA_AT_0100203C_OFFSET_29 0xFFFD68D4   /* was DAT_0102b780 (word at 0x0102B780); PC-relative offset: + 0x102b768 (the pc) = 0x0100203C */
#define DATA_AT_01002554_OFFSET_2 0xFFFD6D00   /* was DAT_0102b8a0 (word at 0x0102B8A0); PC-relative offset: + 0x102b854 (the pc) = 0x01002554 */
#define DATA_AT_01001FAC_OFFSET_4 0xFFFD6748   /* was DAT_0102b8a4 (word at 0x0102B8A4); PC-relative offset: + 0x102b864 (the pc) = 0x01001FAC */
#define DATA_AT_0100203C_OFFSET_30 0xFFFD67B4   /* was DAT_0102b8a8 (word at 0x0102B8A8); PC-relative offset: + 0x102b888 (the pc) = 0x0100203C */
#define DATA_AT_01002540_OFFSET_3 0xFFFD6C78   /* was DAT_0102b904 (word at 0x0102B904); PC-relative offset: + 0x102b8c8 (the pc) = 0x01002540 */
#define DATA_AT_0100203C_OFFSET_31 0xFFFD6750   /* was DAT_0102b908 (word at 0x0102B908); PC-relative offset: + 0x102b8ec (the pc) = 0x0100203C */
#define DATA_AT_0100255C_OFFSET_2 0xFFFD6C38   /* was DAT_0102b95c (word at 0x0102B95C); PC-relative offset: + 0x102b924 (the pc) = 0x0100255C */
#define DATA_AT_0100203C_OFFSET_32 0xFFFD66F4   /* was DAT_0102b960 (word at 0x0102B960); PC-relative offset: + 0x102b948 (the pc) = 0x0100203C */
#define DATA_AT_01002570_OFFSET 0xFFFD6BF4   /* was DAT_0102b9d8 (word at 0x0102B9D8); PC-relative offset: + 0x102b97c (the pc) = 0x01002570 */
#define INTEGER_MINUS_4428 0xFFFFEEB4   /* was DAT_0102b9dc (word at 0x0102B9DC); integer -4428 */
#define DATA_AT_0100203C_OFFSET_33 0xFFFD6678   /* was DAT_0102b9e0 (word at 0x0102B9E0); PC-relative offset: + 0x102b9c4 (the pc) = 0x0100203C */
#define DATA_AT_010025AC_OFFSET_2 0xFFFD69F4   /* was DAT_0102bbf0 (word at 0x0102BBF0); PC-relative offset: + 0x102bbb8 (the pc) = 0x010025AC */
#define DATA_AT_0100203C_OFFSET_34 0xFFFD6460   /* was DAT_0102bbf4 (word at 0x0102BBF4); PC-relative offset: + 0x102bbdc (the pc) = 0x0100203C */
#define DATA_AT_010025C0_OFFSET 0xFFFD69B0   /* was DAT_0102bc6c (word at 0x0102BC6C); PC-relative offset: + 0x102bc10 (the pc) = 0x010025C0 */
#define INTEGER_MINUS_2208 0xFFFFF760   /* was DAT_0102bc70 (word at 0x0102BC70); integer -2208 */
#define DATA_AT_0100203C_OFFSET_35 0xFFFD63E4   /* was DAT_0102bc74 (word at 0x0102BC74); PC-relative offset: + 0x102bc58 (the pc) = 0x0100203C */
#define DATA_AT_0100263C_OFFSET_2 0xFFFD66D4   /* was DAT_0102bfc0 (word at 0x0102BFC0); PC-relative offset: + 0x102bf68 (the pc) = 0x0100263C */
#define INTEGER_1572 0x00000624   /* was DAT_0102bfc4 (word at 0x0102BFC4); integer 1572 */
#define DATA_AT_01002650_OFFSET 0xFFFD6670   /* was DAT_0102c018 (word at 0x0102C018); PC-relative offset: + 0x102bfe0 (the pc) = 0x01002650 */
#define DATA_AT_0100203C_OFFSET_36 0xFFFD6038   /* was DAT_0102c01c (word at 0x0102C01C); PC-relative offset: + 0x102c004 (the pc) = 0x0100203C */
#define WORD_HEXADECIMAL_FFFD6504 0xFFFD6504   /* was DAT_0102c250 (word at 0x0102C250); value 0xFFFD6504 (-170748) */
#define WORD_HEXADECIMAL_FFFD64C0 0xFFFD64C0   /* was DAT_0102c2d8 (word at 0x0102C2D8); value 0xFFFD64C0 (-170816) */
#define DATA_AT_01001FAC_OFFSET_5 0xFFFD5D18   /* was DAT_0102c2dc (word at 0x0102C2DC); PC-relative offset: + 0x102c294 (the pc) = 0x01001FAC */
#define DATA_AT_0100203C_OFFSET_37 0xFFFD5D84   /* was DAT_0102c2e0 (word at 0x0102C2E0); PC-relative offset: + 0x102c2b8 (the pc) = 0x0100203C */
#define DATA_AT_01001E5C_OFFSET_10 0xFFFD5B9C   /* was DAT_0102c2e4 (word at 0x0102C2E4); PC-relative offset: + 0x102c2c0 (the pc) = 0x01001E5C */
#define WORD_HEXADECIMAL_FFFD6444 0xFFFD6444   /* was DAT_0102c334 (word at 0x0102C334); value 0xFFFD6444 (-170940) */
#define WORD_HEXADECIMAL_FFFD6440 0xFFFD6440   /* was DAT_0102c378 (word at 0x0102C378); value 0xFFFD6440 (-170944) */
#define WORD_HEXADECIMAL_FFFD63CC 0xFFFD63CC   /* was DAT_0102c4cc (word at 0x0102C4CC); value 0xFFFD63CC (-171060) */
#define DATA_AT_01001EE8_OFFSET_4 0xFFFD59D0   /* was DAT_0102c578 (word at 0x0102C578); PC-relative offset: + 0x102c518 (the pc) = 0x01001EE8 */
#define DATA_AT_0100203C_OFFSET_38 0xFFFD5B00   /* was DAT_0102c57c (word at 0x0102C57C); PC-relative offset: + 0x102c53c (the pc) = 0x0100203C */
#define DATA_AT_010025AC_OFFSET_3 0xFFFD6068   /* was DAT_0102c580 (word at 0x0102C580); PC-relative offset: + 0x102c544 (the pc) = 0x010025AC */
#define DATA_AT_01002890_OFFSET_2 0xFFFD62D0   /* was DAT_0102c614 (word at 0x0102C614); PC-relative offset: + 0x102c5c0 (the pc) = 0x01002890 */
#define DATA_AT_010023CC_OFFSET_2 0xFFFD5DF4   /* was DAT_0102c618 (word at 0x0102C618); PC-relative offset: + 0x102c5d8 (the pc) = 0x010023CC */
#define DATA_AT_0100203C_OFFSET_39 0xFFFD5A40   /* was DAT_0102c61c (word at 0x0102C61C); PC-relative offset: + 0x102c5fc (the pc) = 0x0100203C */
#define INTEGER_5552 0x000015B0   /* was DAT_0102cdf4 (word at 0x0102CDF4); integer 5552 */
#define INTEGER_65521 0x0000FFF1   /* was DAT_0102cdf8 (word at 0x0102CDF8); integer 65521 */
#define ADDRESS_OF_FUNCTION_0102cecc_OFFSET 0xFFFFFFD0   /* was DAT_0102cf60 (word at 0x0102CF60); PC-relative offset: + 0x102cefc (the pc) = 0x0102CECC */
#define ADDRESS_OF_FUNCTION_0102d0d4_OFFSET 0x000001CC   /* was DAT_0102cf64 (word at 0x0102CF64); PC-relative offset: + 0x102cf08 (the pc) = 0x0102D0D4 */
#define ADDRESS_OF_FUNCTION_0102ce74_OFFSET 0xFFFFFF60   /* was DAT_0102cf68 (word at 0x0102CF68); PC-relative offset: + 0x102cf14 (the pc) = 0x0102CE74 */
#define ADDRESS_OF_FUNCTION_0102ce5c_OFFSET 0xFFFFFF3C   /* was DAT_0102cf6c (word at 0x0102CF6C); PC-relative offset: + 0x102cf20 (the pc) = 0x0102CE5C */
#define ADDRESS_OF_FUNCTION_0102ceac_OFFSET 0xFFFFFF80   /* was DAT_0102cf70 (word at 0x0102CF70); PC-relative offset: + 0x102cf2c (the pc) = 0x0102CEAC */
#define ADDRESS_OF_FUNCTION_0102cf84_OFFSET 0x0000004C   /* was DAT_0102cf74 (word at 0x0102CF74); PC-relative offset: + 0x102cf38 (the pc) = 0x0102CF84 */
#define ADDRESS_OF_FUNCTION_0102ce8c_OFFSET 0xFFFFFF48   /* was DAT_0102cf78 (word at 0x0102CF78); PC-relative offset: + 0x102cf44 (the pc) = 0x0102CE8C */
#define ADDRESS_OF_FUNCTION_0102cfec_OFFSET 0x0000009C   /* was DAT_0102cf7c (word at 0x0102CF7C); PC-relative offset: + 0x102cf50 (the pc) = 0x0102CFEC */
#define ADDRESS_OF_FUNCTION_0102d060_OFFSET 0x00000104   /* was DAT_0102cf80 (word at 0x0102CF80); PC-relative offset: + 0x102cf5c (the pc) = 0x0102D060 */
#define ADDRESS_OF_FUNCTION_0102d310_OFFSET 0x00000048   /* was DAT_0102d2fc (word at 0x0102D2FC); PC-relative offset: + 0x102d2c8 (the pc) = 0x0102D310 */
#define ADDRESS_OF_FUNCTION_0102d1c0_OFFSET 0xFFFFFEEC   /* was DAT_0102d300 (word at 0x0102D300); PC-relative offset: + 0x102d2d4 (the pc) = 0x0102D1C0 */
#define ADDRESS_OF_FUNCTION_0102d3ac_OFFSET 0x000000CC   /* was DAT_0102d304 (word at 0x0102D304); PC-relative offset: + 0x102d2e0 (the pc) = 0x0102D3AC */
#define ADDRESS_OF_FUNCTION_0102d22c_OFFSET 0xFFFFFF40   /* was DAT_0102d308 (word at 0x0102D308); PC-relative offset: + 0x102d2ec (the pc) = 0x0102D22C */
#define ADDRESS_OF_FUNCTION_0102d298_OFFSET 0xFFFFFFA0   /* was DAT_0102d30c (word at 0x0102D30C); PC-relative offset: + 0x102d2f8 (the pc) = 0x0102D298 */
#define ADDRESS_OF_FUNCTION_0102d504_OFFSET 0xFFFFFE74   /* was DAT_0102d718 (word at 0x0102D718); PC-relative offset: + 0x102d690 (the pc) = 0x0102D504 */
#define ADDRESS_OF_FUNCTION_0102d788_OFFSET 0x000000EC   /* was DAT_0102d71c (word at 0x0102D71C); PC-relative offset: + 0x102d69c (the pc) = 0x0102D788 */
#define ADDRESS_OF_FUNCTION_0102d51c_OFFSET 0xFFFFFE74   /* was DAT_0102d720 (word at 0x0102D720); PC-relative offset: + 0x102d6a8 (the pc) = 0x0102D51C */
#define ADDRESS_OF_FUNCTION_0102d7f8_OFFSET 0x00000144   /* was DAT_0102d724 (word at 0x0102D724); PC-relative offset: + 0x102d6b4 (the pc) = 0x0102D7F8 */
#define ADDRESS_OF_FUNCTION_0102d498_OFFSET 0xFFFFFDD8   /* was DAT_0102d728 (word at 0x0102D728); PC-relative offset: + 0x102d6c0 (the pc) = 0x0102D498 */
#define ADDRESS_OF_FUNCTION_0102d768_OFFSET 0x0000009C   /* was DAT_0102d72c (word at 0x0102D72C); PC-relative offset: + 0x102d6cc (the pc) = 0x0102D768 */
#define ADDRESS_OF_FUNCTION_0102d42c_OFFSET 0xFFFFFD54   /* was DAT_0102d730 (word at 0x0102D730); PC-relative offset: + 0x102d6d8 (the pc) = 0x0102D42C */
#define ADDRESS_OF_FUNCTION_0102d748_OFFSET 0x00000064   /* was DAT_0102d734 (word at 0x0102D734); PC-relative offset: + 0x102d6e4 (the pc) = 0x0102D748 */
#define ADDRESS_OF_FUNCTION_0102d588_OFFSET 0xFFFFFE98   /* was DAT_0102d738 (word at 0x0102D738); PC-relative offset: + 0x102d6f0 (the pc) = 0x0102D588 */
#define ADDRESS_OF_FUNCTION_0102d818_OFFSET 0x0000011C   /* was DAT_0102d73c (word at 0x0102D73C); PC-relative offset: + 0x102d6fc (the pc) = 0x0102D818 */
#define ADDRESS_OF_FUNCTION_0102d5f4_OFFSET 0xFFFFFEEC   /* was DAT_0102d740 (word at 0x0102D740); PC-relative offset: + 0x102d708 (the pc) = 0x0102D5F4 */
#define ADDRESS_OF_FUNCTION_0102d838_OFFSET 0x00000124   /* was DAT_0102d744 (word at 0x0102D744); PC-relative offset: + 0x102d714 (the pc) = 0x0102D838 */
#define ADDRESS_OF_FUNCTION_010041ec_OFFSET 0xFFFD6900   /* was DAT_0102d978 (word at 0x0102D978); PC-relative offset: + 0x102d8ec (the pc) = 0x010041EC */
#define ADDRESS_OF_FUNCTION_01004200_OFFSET 0xFFFD6908   /* was DAT_0102d97c (word at 0x0102D97C); PC-relative offset: + 0x102d8f8 (the pc) = 0x01004200 */
#define ADDRESS_OF_FUNCTION_010042bc_OFFSET 0xFFFD69B8   /* was DAT_0102d980 (word at 0x0102D980); PC-relative offset: + 0x102d904 (the pc) = 0x010042BC */
#define ADDRESS_OF_FUNCTION_010042d0_OFFSET 0xFFFD69C0   /* was DAT_0102d984 (word at 0x0102D984); PC-relative offset: + 0x102d910 (the pc) = 0x010042D0 */
#define ADDRESS_OF_FUNCTION_01004380_OFFSET 0xFFFD6A64   /* was DAT_0102d988 (word at 0x0102D988); PC-relative offset: + 0x102d91c (the pc) = 0x01004380 */
#define ADDRESS_OF_FUNCTION_01004638_OFFSET 0xFFFD6D10   /* was DAT_0102d98c (word at 0x0102D98C); PC-relative offset: + 0x102d928 (the pc) = 0x01004638 */
#define ADDRESS_OF_FUNCTION_010041ec_OFFSET_2 0xFFFD681C   /* was DAT_0102da38 (word at 0x0102DA38); PC-relative offset: + 0x102d9d0 (the pc) = 0x010041EC */
#define ADDRESS_OF_FUNCTION_01004200_OFFSET_2 0xFFFD6824   /* was DAT_0102da3c (word at 0x0102DA3C); PC-relative offset: + 0x102d9dc (the pc) = 0x01004200 */
#define ADDRESS_OF_FUNCTION_01004250_OFFSET 0xFFFD6868   /* was DAT_0102da40 (word at 0x0102DA40); PC-relative offset: + 0x102d9e8 (the pc) = 0x01004250 */
#define ADDRESS_OF_FUNCTION_0102dadc_OFFSET 0xFFFFFE84   /* was DAT_0102dd10 (word at 0x0102DD10); PC-relative offset: + 0x102dc58 (the pc) = 0x0102DADC */
#define ADDRESS_OF_FUNCTION_0102dd80_OFFSET 0x0000011C   /* was DAT_0102dd14 (word at 0x0102DD14); PC-relative offset: + 0x102dc64 (the pc) = 0x0102DD80 */
#define ADDRESS_OF_FUNCTION_0102dba4_OFFSET 0xFFFFFF34   /* was DAT_0102dd18 (word at 0x0102DD18); PC-relative offset: + 0x102dc70 (the pc) = 0x0102DBA4 */
#define ADDRESS_OF_FUNCTION_0102de80_OFFSET 0x00000204   /* was DAT_0102dd1c (word at 0x0102DD1C); PC-relative offset: + 0x102dc7c (the pc) = 0x0102DE80 */
#define ADDRESS_OF_FUNCTION_0102dc10_OFFSET 0xFFFFFF88   /* was DAT_0102dd20 (word at 0x0102DD20); PC-relative offset: + 0x102dc88 (the pc) = 0x0102DC10 */
#define ADDRESS_OF_FUNCTION_0102dc28_OFFSET 0xFFFFFF94   /* was DAT_0102dd24 (word at 0x0102DD24); PC-relative offset: + 0x102dc94 (the pc) = 0x0102DC28 */
#define ADDRESS_OF_FUNCTION_0102db4c_OFFSET 0xFFFFFEAC   /* was DAT_0102dd28 (word at 0x0102DD28); PC-relative offset: + 0x102dca0 (the pc) = 0x0102DB4C */
#define ADDRESS_OF_FUNCTION_0102db78_OFFSET 0xFFFFFECC   /* was DAT_0102dd2c (word at 0x0102DD2C); PC-relative offset: + 0x102dcac (the pc) = 0x0102DB78 */
#define ADDRESS_OF_FUNCTION_0102db20_OFFSET 0xFFFFFE68   /* was DAT_0102dd30 (word at 0x0102DD30); PC-relative offset: + 0x102dcb8 (the pc) = 0x0102DB20 */
#define ADDRESS_OF_FUNCTION_0102daf4_OFFSET 0xFFFFFE30   /* was DAT_0102dd34 (word at 0x0102DD34); PC-relative offset: + 0x102dcc4 (the pc) = 0x0102DAF4 */
#define ADDRESS_OF_FUNCTION_0102dd50_OFFSET 0x00000080   /* was DAT_0102dd38 (word at 0x0102DD38); PC-relative offset: + 0x102dcd0 (the pc) = 0x0102DD50 */
#define ADDRESS_OF_FUNCTION_0102dd94_OFFSET 0x000000B8   /* was DAT_0102dd3c (word at 0x0102DD3C); PC-relative offset: + 0x102dcdc (the pc) = 0x0102DD94 */
#define ADDRESS_OF_FUNCTION_0102dd68_OFFSET 0x00000080   /* was DAT_0102dd40 (word at 0x0102DD40); PC-relative offset: + 0x102dce8 (the pc) = 0x0102DD68 */
#define ADDRESS_OF_FUNCTION_0102de64_OFFSET 0x00000170   /* was DAT_0102dd44 (word at 0x0102DD44); PC-relative offset: + 0x102dcf4 (the pc) = 0x0102DE64 */
#define ADDRESS_OF_FUNCTION_0102deec_OFFSET 0x000001EC   /* was DAT_0102dd48 (word at 0x0102DD48); PC-relative offset: + 0x102dd00 (the pc) = 0x0102DEEC */
#define ADDRESS_OF_FUNCTION_0102ddb0_OFFSET 0x000000A4   /* was DAT_0102dd4c (word at 0x0102DD4C); PC-relative offset: + 0x102dd0c (the pc) = 0x0102DDB0 */
#define ADDRESS_OF_FUNCTION_0102e06c_OFFSET 0xFFFFFF04   /* was DAT_0102e19c (word at 0x0102E19C); PC-relative offset: + 0x102e168 (the pc) = 0x0102E06C */
#define ADDRESS_OF_FUNCTION_0102e0dc_OFFSET 0xFFFFFF68   /* was DAT_0102e1a0 (word at 0x0102E1A0); PC-relative offset: + 0x102e174 (the pc) = 0x0102E0DC */
#define ADDRESS_OF_FUNCTION_0102e1b0_OFFSET 0x00000030   /* was DAT_0102e1a4 (word at 0x0102E1A4); PC-relative offset: + 0x102e180 (the pc) = 0x0102E1B0 */
#define ADDRESS_OF_FUNCTION_0102e234_OFFSET 0x000000A8   /* was DAT_0102e1a8 (word at 0x0102E1A8); PC-relative offset: + 0x102e18c (the pc) = 0x0102E234 */
#define ADDRESS_OF_FUNCTION_0102e318_OFFSET 0x00000180   /* was DAT_0102e1ac (word at 0x0102E1AC); PC-relative offset: + 0x102e198 (the pc) = 0x0102E318 */
#define FLOAT_180 0x43340000   /* was DAT_0102e448 (word at 0x0102E448); the float 180.0 */
#define ADDRESS_OF_FUNCTION_0102e4ac_OFFSET 0xFFFFFF88   /* was DAT_0102e5d0 (word at 0x0102E5D0); PC-relative offset: + 0x102e524 (the pc) = 0x0102E4AC */
#define ADDRESS_OF_FUNCTION_0102e66c_OFFSET 0x0000013C   /* was DAT_0102e5d4 (word at 0x0102E5D4); PC-relative offset: + 0x102e530 (the pc) = 0x0102E66C */
#define ADDRESS_OF_FUNCTION_0102e4c4_OFFSET 0xFFFFFF88   /* was DAT_0102e5d8 (word at 0x0102E5D8); PC-relative offset: + 0x102e53c (the pc) = 0x0102E4C4 */
#define ADDRESS_OF_FUNCTION_0102e724_OFFSET 0x000001DC   /* was DAT_0102e5dc (word at 0x0102E5DC); PC-relative offset: + 0x102e548 (the pc) = 0x0102E724 */
#define ADDRESS_OF_FUNCTION_0102e624_OFFSET 0x000000D0   /* was DAT_0102e5e0 (word at 0x0102E5E0); PC-relative offset: + 0x102e554 (the pc) = 0x0102E624 */
#define ADDRESS_OF_FUNCTION_0102e794_OFFSET 0x00000234   /* was DAT_0102e5e4 (word at 0x0102E5E4); PC-relative offset: + 0x102e560 (the pc) = 0x0102E794 */
#define ADDRESS_OF_FUNCTION_0102e60c_OFFSET 0x000000A0   /* was DAT_0102e5e8 (word at 0x0102E5E8); PC-relative offset: + 0x102e56c (the pc) = 0x0102E60C */
#define ADDRESS_OF_FUNCTION_0102e708_OFFSET 0x00000190   /* was DAT_0102e5ec (word at 0x0102E5EC); PC-relative offset: + 0x102e578 (the pc) = 0x0102E708 */
#define ADDRESS_OF_FUNCTION_0102e654_OFFSET 0x000000D0   /* was DAT_0102e5f0 (word at 0x0102E5F0); PC-relative offset: + 0x102e584 (the pc) = 0x0102E654 */
#define ADDRESS_OF_FUNCTION_0102e844_OFFSET 0x000002B4   /* was DAT_0102e5f4 (word at 0x0102E5F4); PC-relative offset: + 0x102e590 (the pc) = 0x0102E844 */
#define ADDRESS_OF_FUNCTION_0102e63c_OFFSET 0x000000A0   /* was DAT_0102e5f8 (word at 0x0102E5F8); PC-relative offset: + 0x102e59c (the pc) = 0x0102E63C */
#define ADDRESS_OF_FUNCTION_0102e828_OFFSET 0x00000280   /* was DAT_0102e5fc (word at 0x0102E5FC); PC-relative offset: + 0x102e5a8 (the pc) = 0x0102E828 */
#define ADDRESS_OF_FUNCTION_0102e4dc_OFFSET 0xFFFFFF28   /* was DAT_0102e600 (word at 0x0102E600); PC-relative offset: + 0x102e5b4 (the pc) = 0x0102E4DC */
#define ADDRESS_OF_FUNCTION_0102e4f4_OFFSET 0xFFFFFF34   /* was DAT_0102e604 (word at 0x0102E604); PC-relative offset: + 0x102e5c0 (the pc) = 0x0102E4F4 */
#define ADDRESS_OF_FUNCTION_0102e7b0_OFFSET 0x000001E4   /* was DAT_0102e608 (word at 0x0102E608); PC-relative offset: + 0x102e5cc (the pc) = 0x0102E7B0 */
#define DATA_AT_01040A04_OFFSET 0x00012184   /* was DAT_0102e964 (word at 0x0102E964); PC-relative offset: + 0x102e880 (the pc) = 0x01040A04 */
#define ADDRESS_OF_FUNCTION_0102ea40_OFFSET 0xFFFFFF6C   /* was DAT_0102eb38 (word at 0x0102EB38); PC-relative offset: + 0x102ead4 (the pc) = 0x0102EA40 */
#define ADDRESS_OF_FUNCTION_0102eb5c_OFFSET 0x0000007C   /* was DAT_0102eb3c (word at 0x0102EB3C); PC-relative offset: + 0x102eae0 (the pc) = 0x0102EB5C */
#define ADDRESS_OF_FUNCTION_0102ea5c_OFFSET 0xFFFFFF70   /* was DAT_0102eb40 (word at 0x0102EB40); PC-relative offset: + 0x102eaec (the pc) = 0x0102EA5C */
#define ADDRESS_OF_FUNCTION_0102eb74_OFFSET 0x0000007C   /* was DAT_0102eb44 (word at 0x0102EB44); PC-relative offset: + 0x102eaf8 (the pc) = 0x0102EB74 */
#define ADDRESS_OF_FUNCTION_0102ea8c_OFFSET 0xFFFFFF88   /* was DAT_0102eb48 (word at 0x0102EB48); PC-relative offset: + 0x102eb04 (the pc) = 0x0102EA8C */
#define ADDRESS_OF_FUNCTION_0102ec78_OFFSET 0x00000168   /* was DAT_0102eb4c (word at 0x0102EB4C); PC-relative offset: + 0x102eb10 (the pc) = 0x0102EC78 */
#define ADDRESS_OF_FUNCTION_0102eaa4_OFFSET 0xFFFFFF88   /* was DAT_0102eb50 (word at 0x0102EB50); PC-relative offset: + 0x102eb1c (the pc) = 0x0102EAA4 */
#define ADDRESS_OF_FUNCTION_0102ea74_OFFSET 0xFFFFFF4C   /* was DAT_0102eb54 (word at 0x0102EB54); PC-relative offset: + 0x102eb28 (the pc) = 0x0102EA74 */
#define ADDRESS_OF_FUNCTION_0102ebf8_OFFSET 0x000000C4   /* was DAT_0102eb58 (word at 0x0102EB58); PC-relative offset: + 0x102eb34 (the pc) = 0x0102EBF8 */
#define INTEGER_MINUS_1 0xFFFFFFFF   /* was DAT_0102edac (word at 0x0102EDAC); integer -1 */
#define WORD_HEXADECIMAL_7FFFFFFF 0x7FFFFFFF   /* was DAT_0102edb0 (word at 0x0102EDB0); value 0x7FFFFFFF (2147483647) */
#define WORD_HEXADECIMAL_0001921F 0x0001921F   /* was DAT_0102ee80 (word at 0x0102EE80); value 0x0001921F (102943) */
#define WORD_HEXADECIMAL_FFFE6DE1 0xFFFE6DE1   /* was DAT_0102ee84 (word at 0x0102EE84); value 0xFFFE6DE1 (-102943) */
#define INTEGER_47976 0x0000BB68   /* was DAT_0102f06c (word at 0x0102F06C); integer 47976 */
#define WORD_HEXADECIMAL_00011A9C 0x00011A9C   /* was DAT_0102f074 (word at 0x0102F074); value 0x00011A9C (72348) */
#define WORD_HEXADECIMAL_00011A18 0x00011A18   /* was DAT_0102f078 (word at 0x0102F078); value 0x00011A18 (72216) */
#define DATA_AT_010409F4_OFFSET 0x00011998   /* was DAT_0102f07c (word at 0x0102F07C); PC-relative offset: + 0x102f05c (the pc) = 0x010409F4 */
#define WORD_HEXADECIMAL_00B504F3 0x00B504F3   /* was DAT_0102f23c (word at 0x0102F23C); value 0x00B504F3 (11863283) */
#define FLOAT_88 0x42B00000   /* was DAT_0102f3b4 (word at 0x0102F3B4); the float 88.0 */
#define FLOAT_MINUS_88 0xC2B00000   /* was DAT_0102f3b8 (word at 0x0102F3B8); the float -88.0 */
#define WORD_HEXADECIMAL_4272759C 0x4272759C   /* was DAT_0102f3c4 (word at 0x0102F3C4); value 0x4272759C (1114797468) */
#define WORD_HEXADECIMAL_4AB73041 0x4AB73041   /* was DAT_0102f3c8 (word at 0x0102F3C8); value 0x4AB73041 (1253519425) */
#define WORD_HEXADECIMAL_46EC9DF2 0x46EC9DF2   /* was DAT_0102f3d4 (word at 0x0102F3D4); value 0x46EC9DF2 (1189912050) */
#define WORD_HEXADECIMAL_49FDF403 0x49FDF403   /* was DAT_0102f3d8 (word at 0x0102F3D8); value 0x49FDF403 (1241379843) */
#define WORD_HEXADECIMAL_3FB504F3 0x3FB504F3   /* was DAT_0102f3dc (word at 0x0102F3DC); value 0x3FB504F3 (1068827891) */
#define WORD_HEXADECIMAL_5F374800 0x5F374800   /* was DAT_0102f45c (word at 0x0102F45C); value 0x5F374800 (1597458432) */
#define DATA_AT_01040194_OFFSET 0x00010D0C   /* was DAT_0102f50c (word at 0x0102F50C); PC-relative offset: + 0x102f488 (the pc) = 0x01040194 */
#define ADDRESS_OF_FUNCTION_0100eac8_OFFSET 0xFFFDF5A0   /* was DAT_0102f710 (word at 0x0102F710); PC-relative offset: + 0x102f528 (the pc) = 0x0100EAC8 */
#define ADDRESS_OF_FUNCTION_0100e96c_OFFSET 0xFFFDF434   /* was DAT_0102f714 (word at 0x0102F714); PC-relative offset: + 0x102f538 (the pc) = 0x0100E96C */
#define ADDRESS_OF_FUNCTION_0100e700_OFFSET 0xFFFDF1B4   /* was DAT_0102f718 (word at 0x0102F718); PC-relative offset: + 0x102f54c (the pc) = 0x0100E700 */
#define ADDRESS_OF_FUNCTION_0100e724_OFFSET 0xFFFDF1C4   /* was DAT_0102f71c (word at 0x0102F71C); PC-relative offset: + 0x102f560 (the pc) = 0x0100E724 */
#define ADDRESS_OF_FUNCTION_0100ec1c_OFFSET 0xFFFDF6A8   /* was DAT_0102f720 (word at 0x0102F720); PC-relative offset: + 0x102f574 (the pc) = 0x0100EC1C */
#define ADDRESS_OF_FUNCTION_0100e990_OFFSET 0xFFFDF408   /* was DAT_0102f724 (word at 0x0102F724); PC-relative offset: + 0x102f588 (the pc) = 0x0100E990 */
#define ADDRESS_OF_FUNCTION_0100eaec_OFFSET 0xFFFDF550   /* was DAT_0102f728 (word at 0x0102F728); PC-relative offset: + 0x102f59c (the pc) = 0x0100EAEC */
#define ADDRESS_OF_FUNCTION_0100eb58_OFFSET 0xFFFDF5A8   /* was DAT_0102f72c (word at 0x0102F72C); PC-relative offset: + 0x102f5b0 (the pc) = 0x0100EB58 */
#define ADDRESS_OF_FUNCTION_0100e7ec_OFFSET 0xFFFDF228   /* was DAT_0102f730 (word at 0x0102F730); PC-relative offset: + 0x102f5c4 (the pc) = 0x0100E7EC */
#define ADDRESS_OF_FUNCTION_0100e5b0_OFFSET 0xFFFDEFD8   /* was DAT_0102f734 (word at 0x0102F734); PC-relative offset: + 0x102f5d8 (the pc) = 0x0100E5B0 */
#define ADDRESS_OF_FUNCTION_0100ea80_OFFSET 0xFFFDF494   /* was DAT_0102f738 (word at 0x0102F738); PC-relative offset: + 0x102f5ec (the pc) = 0x0100EA80 */
#define ADDRESS_OF_FUNCTION_0100eb7c_OFFSET 0xFFFDF57C   /* was DAT_0102f73c (word at 0x0102F73C); PC-relative offset: + 0x102f600 (the pc) = 0x0100EB7C */
#define ADDRESS_OF_FUNCTION_0100e5d4_OFFSET 0xFFFDEFC0   /* was DAT_0102f740 (word at 0x0102F740); PC-relative offset: + 0x102f614 (the pc) = 0x0100E5D4 */
#define ADDRESS_OF_FUNCTION_0100eb10_OFFSET 0xFFFDF4E8   /* was DAT_0102f744 (word at 0x0102F744); PC-relative offset: + 0x102f628 (the pc) = 0x0100EB10 */
#define ADDRESS_OF_FUNCTION_0100e924_OFFSET 0xFFFDF2E8   /* was DAT_0102f748 (word at 0x0102F748); PC-relative offset: + 0x102f63c (the pc) = 0x0100E924 */
#define ADDRESS_OF_FUNCTION_0100e9b4_OFFSET 0xFFFDF364   /* was DAT_0102f74c (word at 0x0102F74C); PC-relative offset: + 0x102f650 (the pc) = 0x0100E9B4 */
#define ADDRESS_OF_FUNCTION_0100e810_OFFSET 0xFFFDF1AC   /* was DAT_0102f750 (word at 0x0102F750); PC-relative offset: + 0x102f664 (the pc) = 0x0100E810 */
#define ADDRESS_OF_FUNCTION_0100ec40_OFFSET 0xFFFDF5C8   /* was DAT_0102f754 (word at 0x0102F754); PC-relative offset: + 0x102f678 (the pc) = 0x0100EC40 */
#define ADDRESS_OF_FUNCTION_0100e6b8_OFFSET 0xFFFDF02C   /* was DAT_0102f758 (word at 0x0102F758); PC-relative offset: + 0x102f68c (the pc) = 0x0100E6B8 */
#define ADDRESS_OF_FUNCTION_0100e6dc_OFFSET 0xFFFDF03C   /* was DAT_0102f75c (word at 0x0102F75C); PC-relative offset: + 0x102f6a0 (the pc) = 0x0100E6DC */
#define ADDRESS_OF_FUNCTION_0100eaa4_OFFSET 0xFFFDF3F0   /* was DAT_0102f760 (word at 0x0102F760); PC-relative offset: + 0x102f6b4 (the pc) = 0x0100EAA4 */
#define ADDRESS_OF_FUNCTION_0100e900_OFFSET 0xFFFDF238   /* was DAT_0102f764 (word at 0x0102F764); PC-relative offset: + 0x102f6c8 (the pc) = 0x0100E900 */
#define ADDRESS_OF_FUNCTION_0100e948_OFFSET 0xFFFDF26C   /* was DAT_0102f768 (word at 0x0102F768); PC-relative offset: + 0x102f6dc (the pc) = 0x0100E948 */
#define ADDRESS_OF_FUNCTION_0100ebf8_OFFSET 0xFFFDF508   /* was DAT_0102f76c (word at 0x0102F76C); PC-relative offset: + 0x102f6f0 (the pc) = 0x0100EBF8 */
#define ADDRESS_OF_FUNCTION_0100eb34_OFFSET 0xFFFDF430   /* was DAT_0102f770 (word at 0x0102F770); PC-relative offset: + 0x102f704 (the pc) = 0x0100EB34 */
#define ADDRESS_OF_FUNCTION_0100e798_OFFSET 0xFFFDF010   /* was DAT_0102f7a4 (word at 0x0102F7A4); PC-relative offset: + 0x102f788 (the pc) = 0x0100E798 */
#define ADDRESS_OF_FUNCTION_0100e63c_OFFSET 0xFFFDEEA4   /* was DAT_0102f7a8 (word at 0x0102F7A8); PC-relative offset: + 0x102f798 (the pc) = 0x0100E63C */
#define ADDRESS_OF_FUNCTION_0102fa18_OFFSET 0xFFFFFFDC   /* was DAT_0102fb24 (word at 0x0102FB24); PC-relative offset: + 0x102fa3c (the pc) = 0x0102FA18 */
#define ADDRESS_OF_FUNCTION_0102f9d0_OFFSET 0xFFFFFF88   /* was DAT_0102fb28 (word at 0x0102FB28); PC-relative offset: + 0x102fa48 (the pc) = 0x0102F9D0 */
#define ADDRESS_OF_FUNCTION_0102f9e8_OFFSET 0xFFFFFF94   /* was DAT_0102fb2c (word at 0x0102FB2C); PC-relative offset: + 0x102fa54 (the pc) = 0x0102F9E8 */
#define ADDRESS_OF_FUNCTION_0102fa00_OFFSET 0xFFFFFFA0   /* was DAT_0102fb30 (word at 0x0102FB30); PC-relative offset: + 0x102fa60 (the pc) = 0x0102FA00 */
#define ADDRESS_OF_FUNCTION_0102fdd4_OFFSET 0x00000368   /* was DAT_0102fb34 (word at 0x0102FB34); PC-relative offset: + 0x102fa6c (the pc) = 0x0102FDD4 */
#define ADDRESS_OF_IGraphics3D_BindTarget_OFFSET 0x000004C0   /* was DAT_0102fb38 (word at 0x0102FB38); PC-relative offset: + 0x102fa78 (the pc) = 0x0102FF38 */
#define ADDRESS_OF_FUNCTION_0102fe4c_OFFSET 0x000003C8   /* was DAT_0102fb3c (word at 0x0102FB3C); PC-relative offset: + 0x102fa84 (the pc) = 0x0102FE4C */
#define ADDRESS_OF_FUNCTION_01030210_OFFSET 0x00000780   /* was DAT_0102fb40 (word at 0x0102FB40); PC-relative offset: + 0x102fa90 (the pc) = 0x01030210 */
#define ADDRESS_OF_FUNCTION_010300a4_OFFSET 0x00000608   /* was DAT_0102fb44 (word at 0x0102FB44); PC-relative offset: + 0x102fa9c (the pc) = 0x010300A4 */
#define ADDRESS_OF_FUNCTION_01030198_OFFSET 0x000006F0   /* was DAT_0102fb48 (word at 0x0102FB48); PC-relative offset: + 0x102faa8 (the pc) = 0x01030198 */
#define ADDRESS_OF_FUNCTION_0102ffb8_OFFSET 0x00000504   /* was DAT_0102fb4c (word at 0x0102FB4C); PC-relative offset: + 0x102fab4 (the pc) = 0x0102FFB8 */
#define ADDRESS_OF_FUNCTION_0102f898_OFFSET 0xFFFFFDD8   /* was DAT_0102fb50 (word at 0x0102FB50); PC-relative offset: + 0x102fac0 (the pc) = 0x0102F898 */
#define ADDRESS_OF_FUNCTION_0102fc0c_OFFSET 0x00000140   /* was DAT_0102fb54 (word at 0x0102FB54); PC-relative offset: + 0x102facc (the pc) = 0x0102FC0C */
#define ADDRESS_OF_FUNCTION_0102fb74_OFFSET 0x0000009C   /* was DAT_0102fb58 (word at 0x0102FB58); PC-relative offset: + 0x102fad8 (the pc) = 0x0102FB74 */
#define ADDRESS_OF_FUNCTION_0102fcf8_OFFSET 0x00000214   /* was DAT_0102fb5c (word at 0x0102FB5C); PC-relative offset: + 0x102fae4 (the pc) = 0x0102FCF8 */
#define ADDRESS_OF_FUNCTION_0102feb8_OFFSET 0x000003C8   /* was DAT_0102fb60 (word at 0x0102FB60); PC-relative offset: + 0x102faf0 (the pc) = 0x0102FEB8 */
#define ADDRESS_OF_FUNCTION_01030110_OFFSET 0x00000614   /* was DAT_0102fb64 (word at 0x0102FB64); PC-relative offset: + 0x102fafc (the pc) = 0x01030110 */
#define ADDRESS_OF_FUNCTION_0102f7f8_OFFSET 0xFFFFFCF0   /* was DAT_0102fb68 (word at 0x0102FB68); PC-relative offset: + 0x102fb08 (the pc) = 0x0102F7F8 */
#define ADDRESS_OF_FUNCTION_0102fd7c_OFFSET 0x00000268   /* was DAT_0102fb6c (word at 0x0102FB6C); PC-relative offset: + 0x102fb14 (the pc) = 0x0102FD7C */
#define ADDRESS_OF_FUNCTION_0102f960_OFFSET 0xFFFFFE40   /* was DAT_0102fb70 (word at 0x0102FB70); PC-relative offset: + 0x102fb20 (the pc) = 0x0102F960 */
#define ADDRESS_OF_FUNCTION_01030360_OFFSET 0xFFFFFFC8   /* was DAT_010303d8 (word at 0x010303D8); PC-relative offset: + 0x1030398 (the pc) = 0x01030360 */
#define ADDRESS_OF_FUNCTION_010302ec_OFFSET 0xFFFFFF48   /* was DAT_010303dc (word at 0x010303DC); PC-relative offset: + 0x10303a4 (the pc) = 0x010302EC */
#define ADDRESS_OF_FUNCTION_01030220_OFFSET 0xFFFFFE70   /* was DAT_010303e0 (word at 0x010303E0); PC-relative offset: + 0x10303b0 (the pc) = 0x01030220 */
#define ADDRESS_OF_FUNCTION_010305b8_OFFSET 0x000001FC   /* was DAT_010303e4 (word at 0x010303E4); PC-relative offset: + 0x10303bc (the pc) = 0x010305B8 */
#define ADDRESS_OF_FUNCTION_010304c0_OFFSET 0x000000F8   /* was DAT_010303e8 (word at 0x010303E8); PC-relative offset: + 0x10303c8 (the pc) = 0x010304C0 */
#define ADDRESS_OF_FUNCTION_010303f0_OFFSET 0x0000001C   /* was DAT_010303ec (word at 0x010303EC); PC-relative offset: + 0x10303d4 (the pc) = 0x010303F0 */
#define ADDRESS_OF_FUNCTION_01030c54_OFFSET 0x000000B8   /* was DAT_01030c24 (word at 0x01030C24); PC-relative offset: + 0x1030b9c (the pc) = 0x01030C54 */
#define ADDRESS_OF_FUNCTION_01030dbc_OFFSET 0x00000214   /* was DAT_01030c28 (word at 0x01030C28); PC-relative offset: + 0x1030ba8 (the pc) = 0x01030DBC */
#define ADDRESS_OF_FUNCTION_01030d14_OFFSET 0x00000160   /* was DAT_01030c2c (word at 0x01030C2C); PC-relative offset: + 0x1030bb4 (the pc) = 0x01030D14 */
#define ADDRESS_OF_FUNCTION_01030e98_OFFSET 0x000002D8   /* was DAT_01030c30 (word at 0x01030C30); PC-relative offset: + 0x1030bc0 (the pc) = 0x01030E98 */
#define ADDRESS_OF_FUNCTION_01030acc_OFFSET 0xFFFFFF00   /* was DAT_01030c34 (word at 0x01030C34); PC-relative offset: + 0x1030bcc (the pc) = 0x01030ACC */
#define ADDRESS_OF_FUNCTION_01030b58_OFFSET 0xFFFFFF80   /* was DAT_01030c38 (word at 0x01030C38); PC-relative offset: + 0x1030bd8 (the pc) = 0x01030B58 */
#define ADDRESS_OF_FUNCTION_01030ae4_OFFSET 0xFFFFFF00   /* was DAT_01030c3c (word at 0x01030C3C); PC-relative offset: + 0x1030be4 (the pc) = 0x01030AE4 */
#define ADDRESS_OF_FUNCTION_01030b38_OFFSET 0xFFFFFF48   /* was DAT_01030c40 (word at 0x01030C40); PC-relative offset: + 0x1030bf0 (the pc) = 0x01030B38 */
#define ADDRESS_OF_FUNCTION_01030b10_OFFSET 0xFFFFFF14   /* was DAT_01030c44 (word at 0x01030C44); PC-relative offset: + 0x1030bfc (the pc) = 0x01030B10 */
#define ADDRESS_OF_FUNCTION_01030aac_OFFSET 0xFFFFFEA4   /* was DAT_01030c48 (word at 0x01030C48); PC-relative offset: + 0x1030c08 (the pc) = 0x01030AAC */
#define ADDRESS_OF_FUNCTION_01030f48_OFFSET 0x00000334   /* was DAT_01030c4c (word at 0x01030C4C); PC-relative offset: + 0x1030c14 (the pc) = 0x01030F48 */
#define ADDRESS_OF_FUNCTION_01030f60_OFFSET 0x00000340   /* was DAT_01030c50 (word at 0x01030C50); PC-relative offset: + 0x1030c20 (the pc) = 0x01030F60 */
#define STRING_1_DOT_1_DOT_4_OFFSET 0x0000EFA8   /* was DAT_010311b4 (word at 0x010311B4); PC-relative offset: + 0x10310a4 (the pc) = 0x0104004C */
#define ADDRESS_OF_FUNCTION_0103d3b8_OFFSET 0x0000C2D4   /* was DAT_010311b8 (word at 0x010311B8); PC-relative offset: + 0x10310e4 (the pc) = 0x0103D3B8 */
#define ADDRESS_OF_FUNCTION_0103d3c0_OFFSET 0x0000C2C4   /* was DAT_010311bc (word at 0x010311BC); PC-relative offset: + 0x10310fc (the pc) = 0x0103D3C0 */
#define ADDRESS_OF_FUNCTION_0102cc94_OFFSET 0xFFFFBB10   /* was DAT_010311c0 (word at 0x010311C0); PC-relative offset: + 0x1031184 (the pc) = 0x0102CC94 */
#define STRING_INVALID_BLOCK_TYPE_OFFSET 0x0000FB14   /* was DAT_01031ac8 (word at 0x01031AC8); PC-relative offset: + 0x103133c (the pc) = 0x01040E50 */
#define STRING_INVALID_STORED_BLOCK_LENGTHS_OFFSET 0x0000FA50   /* was DAT_01031acc (word at 0x01031ACC); PC-relative offset: + 0x1031414 (the pc) = 0x01040E64 */
#define STRING_TOO_MANY_LENGTH_OR_DISTANCE_SYMBOLS_OFFSET 0x0000F8A8   /* was DAT_01031ad0 (word at 0x01031AD0); PC-relative offset: + 0x10315dc (the pc) = 0x01040E84 */
#define DATA_AT_01040E04_OFFSET 0x0000F7D0   /* was DAT_01031ad4 (word at 0x01031AD4); PC-relative offset: + 0x1031634 (the pc) = 0x01040E04 */
#define DATA_AT_010425CC_OFFSET 0x00010E80   /* was DAT_01031ad8 (word at 0x01031AD8); PC-relative offset: + 0x103174c (the pc) = 0x010425CC */
#define DATA_AT_010425CC_OFFSET_2 0x00010DF4   /* was DAT_01031adc (word at 0x01031ADC); PC-relative offset: + 0x10317d8 (the pc) = 0x010425CC */
#define STRING_INVALID_BIT_LENGTH_REPEAT_OFFSET 0x0000F674   /* was DAT_01031ae0 (word at 0x01031AE0); PC-relative offset: + 0x1031834 (the pc) = 0x01040EA8 */
#define DATA_AT_010425CC_OFFSET_3 0x000107DC   /* was DAT_01032234 (word at 0x01032234); PC-relative offset: + 0x1031df0 (the pc) = 0x010425CC */
#define STRING_INVALID_LITERAL_SLASH_LENGTH_CODE_OFFSET 0x00010908   /* was DAT_01032238 (word at 0x01032238); PC-relative offset: + 0x1031e60 (the pc) = 0x01042768 */
#define DATA_AT_010425CC_OFFSET_4 0x00010704   /* was DAT_0103223c (word at 0x0103223C); PC-relative offset: + 0x1031ec8 (the pc) = 0x010425CC */
#define DATA_AT_010425CC_OFFSET_5 0x0001069C   /* was DAT_01032240 (word at 0x01032240); PC-relative offset: + 0x1031f30 (the pc) = 0x010425CC */
#define STRING_INVALID_DISTANCE_CODE_OFFSET 0x000107EC   /* was DAT_01032244 (word at 0x01032244); PC-relative offset: + 0x1031f98 (the pc) = 0x01042784 */
#define DATA_AT_010425CC_OFFSET_6 0x000105F4   /* was DAT_01032248 (word at 0x01032248); PC-relative offset: + 0x1031fd8 (the pc) = 0x010425CC */
#define DATA_AT_010425CC_OFFSET_7 0x000102D8   /* was DAT_01032648 (word at 0x01032648); PC-relative offset: + 0x10322f4 (the pc) = 0x010425CC */
#define DATA_AT_010425CC_OFFSET_8 0x00010290   /* was DAT_0103264c (word at 0x0103264C); PC-relative offset: + 0x103233c (the pc) = 0x010425CC */
#define STRING_INVALID_DISTANCE_CODE_OFFSET_2 0x000102FC   /* was DAT_01032650 (word at 0x01032650); PC-relative offset: + 0x10324b8 (the pc) = 0x010427B4 */
#define STRING_INVALID_LITERAL_SLASH_LENGTH_CODE_OFFSET_2 0x000101D0   /* was DAT_01032654 (word at 0x01032654); PC-relative offset: + 0x10325fc (the pc) = 0x010427CC */
#define STRING_OVERSUBSCRIBED_DYNAMIC_BIT_LENGTHS_TREE_OFFSET 0x0000FCC8   /* was DAT_01032850 (word at 0x01032850); PC-relative offset: + 0x1032814 (the pc) = 0x010424DC */
#define STRING_INCOMPLETE_DYNAMIC_BIT_LENGTHS_TREE_OFFSET 0x0000FCD4   /* was DAT_01032854 (word at 0x01032854); PC-relative offset: + 0x1032830 (the pc) = 0x01042504 */
#define DATA_AT_01041270_OFFSET 0x0000E9B4   /* was DAT_01032a00 (word at 0x01032A00); PC-relative offset: + 0x10328bc (the pc) = 0x01041270 */
#define DATA_AT_010411F4_OFFSET 0x0000E930   /* was DAT_01032a04 (word at 0x01032A04); PC-relative offset: + 0x10328c4 (the pc) = 0x010411F4 */
#define STRING_OVERSUBSCRIBED_LITERAL_SLASH_LENGTH_TREE_OFFSET 0x0000FC28   /* was DAT_01032a0c (word at 0x01032A0C); PC-relative offset: + 0x1032900 (the pc) = 0x01042528 */
#define STRING_INCOMPLETE_LITERAL_SLASH_LENGTH_TREE_OFFSET 0x0000FC34   /* was DAT_01032a10 (word at 0x01032A10); PC-relative offset: + 0x1032918 (the pc) = 0x0104254C */
#define DATA_AT_01041364_OFFSET 0x0000EA14   /* was DAT_01032a14 (word at 0x01032A14); PC-relative offset: + 0x1032950 (the pc) = 0x01041364 */
#define DATA_AT_010412EC_OFFSET 0x0000E988   /* was DAT_01032a18 (word at 0x01032A18); PC-relative offset: + 0x1032964 (the pc) = 0x010412EC */
#define STRING_OVERSUBSCRIBED_DISTANCE_TREE_OFFSET 0x0000FBCC   /* was DAT_01032a1c (word at 0x01032A1C); PC-relative offset: + 0x10329a0 (the pc) = 0x0104256C */
#define STRING_INCOMPLETE_DISTANCE_TREE_OFFSET 0x0000FBD8   /* was DAT_01032a20 (word at 0x01032A20); PC-relative offset: + 0x10329b4 (the pc) = 0x0104258C */
#define STRING_EMPTY_DISTANCE_TREE_WITH_LENGTHS_OFFSET 0x0000FBE0   /* was DAT_01032a24 (word at 0x01032A24); PC-relative offset: + 0x10329c8 (the pc) = 0x010425A8 */
#define DATA_AT_010413DC_OFFSET 0x0000E998   /* was DAT_01032a58 (word at 0x01032A58); PC-relative offset: + 0x1032a44 (the pc) = 0x010413DC */
#define DATA_AT_010423DC_OFFSET 0x0000F98C   /* was DAT_01032a5c (word at 0x01032A5C); PC-relative offset: + 0x1032a50 (the pc) = 0x010423DC */
#define ADDRESS_OF_FUNCTION_01032b70_OFFSET 0x00000068   /* was DAT_01032b54 (word at 0x01032B54); PC-relative offset: + 0x1032b08 (the pc) = 0x01032B70 */
#define ADDRESS_OF_FUNCTION_01032ac0_OFFSET 0xFFFFFFAC   /* was DAT_01032b58 (word at 0x01032B58); PC-relative offset: + 0x1032b14 (the pc) = 0x01032AC0 */
#define ADDRESS_OF_FUNCTION_01032c10_OFFSET 0x000000F0   /* was DAT_01032b5c (word at 0x01032B5C); PC-relative offset: + 0x1032b20 (the pc) = 0x01032C10 */
#define ADDRESS_OF_FUNCTION_01032ad8_OFFSET 0xFFFFFFAC   /* was DAT_01032b60 (word at 0x01032B60); PC-relative offset: + 0x1032b2c (the pc) = 0x01032AD8 */
#define ADDRESS_OF_FUNCTION_01032d20_OFFSET 0x000001E8   /* was DAT_01032b64 (word at 0x01032B64); PC-relative offset: + 0x1032b38 (the pc) = 0x01032D20 */
#define ADDRESS_OF_FUNCTION_01032c84_OFFSET 0x00000140   /* was DAT_01032b68 (word at 0x01032B68); PC-relative offset: + 0x1032b44 (the pc) = 0x01032C84 */
#define ADDRESS_OF_FUNCTION_01032d90_OFFSET 0x00000240   /* was DAT_01032b6c (word at 0x01032B6C); PC-relative offset: + 0x1032b50 (the pc) = 0x01032D90 */
#define ADDRESS_OF_FUNCTION_01032ebc_OFFSET 0xFFFFFF88   /* was DAT_01032fd4 (word at 0x01032FD4); PC-relative offset: + 0x1032f34 (the pc) = 0x01032EBC */
#define ADDRESS_OF_FUNCTION_01033174_OFFSET 0x00000234   /* was DAT_01032fd8 (word at 0x01032FD8); PC-relative offset: + 0x1032f40 (the pc) = 0x01033174 */
#define ADDRESS_OF_FUNCTION_01032e58_OFFSET 0xFFFFFF0C   /* was DAT_01032fdc (word at 0x01032FDC); PC-relative offset: + 0x1032f4c (the pc) = 0x01032E58 */
#define ADDRESS_OF_FUNCTION_010330f8_OFFSET 0x000001A0   /* was DAT_01032fe0 (word at 0x01032FE0); PC-relative offset: + 0x1032f58 (the pc) = 0x010330F8 */
#define ADDRESS_OF_FUNCTION_01032e8c_OFFSET 0xFFFFFF28   /* was DAT_01032fe4 (word at 0x01032FE4); PC-relative offset: + 0x1032f64 (the pc) = 0x01032E8C */
#define ADDRESS_OF_FUNCTION_01033108_OFFSET 0x00000198   /* was DAT_01032fe8 (word at 0x01032FE8); PC-relative offset: + 0x1032f70 (the pc) = 0x01033108 */
#define ADDRESS_OF_FUNCTION_01032eec_OFFSET 0xFFFFFF70   /* was DAT_01032fec (word at 0x01032FEC); PC-relative offset: + 0x1032f7c (the pc) = 0x01032EEC */
#define ADDRESS_OF_FUNCTION_010331ec_OFFSET 0x00000264   /* was DAT_01032ff0 (word at 0x01032FF0); PC-relative offset: + 0x1032f88 (the pc) = 0x010331EC */
#define ADDRESS_OF_FUNCTION_01032f04_OFFSET 0xFFFFFF70   /* was DAT_01032ff4 (word at 0x01032FF4); PC-relative offset: + 0x1032f94 (the pc) = 0x01032F04 */
#define ADDRESS_OF_FUNCTION_01033294_OFFSET 0x000002F4   /* was DAT_01032ff8 (word at 0x01032FF8); PC-relative offset: + 0x1032fa0 (the pc) = 0x01033294 */
#define ADDRESS_OF_FUNCTION_01032e74_OFFSET 0xFFFFFEC8   /* was DAT_01032ffc (word at 0x01032FFC); PC-relative offset: + 0x1032fac (the pc) = 0x01032E74 */
#define ADDRESS_OF_FUNCTION_01032ea4_OFFSET 0xFFFFFEEC   /* was DAT_01033000 (word at 0x01033000); PC-relative offset: + 0x1032fb8 (the pc) = 0x01032EA4 */
#define ADDRESS_OF_FUNCTION_01032ed4_OFFSET 0xFFFFFF10   /* was DAT_01033004 (word at 0x01033004); PC-relative offset: + 0x1032fc4 (the pc) = 0x01032ED4 */
#define ADDRESS_OF_FUNCTION_0103300c_OFFSET 0x0000003C   /* was DAT_01033008 (word at 0x01033008); PC-relative offset: + 0x1032fd0 (the pc) = 0x0103300C */
#define ADDRESS_OF_FUNCTION_01039a28_OFFSET 0x000062B8   /* was DAT_01033798 (word at 0x01033798); PC-relative offset: + 0x1033770 (the pc) = 0x01039A28 */
#define ADDRESS_OF_FUNCTION_01039aac_OFFSET 0x00006330   /* was DAT_0103379c (word at 0x0103379C); PC-relative offset: + 0x103377c (the pc) = 0x01039AAC */
#define ADDRESS_OF_FUNCTION_01039a10_OFFSET 0x00006288   /* was DAT_010337a0 (word at 0x010337A0); PC-relative offset: + 0x1033788 (the pc) = 0x01039A10 */
#define ADDRESS_OF_FUNCTION_010399c4_OFFSET 0x00006230   /* was DAT_010337a4 (word at 0x010337A4); PC-relative offset: + 0x1033794 (the pc) = 0x010399C4 */
#define ADDRESS_OF_FUNCTION_01033aac_OFFSET 0xFFFFFFD0   /* was DAT_01033b1c (word at 0x01033B1C); PC-relative offset: + 0x1033adc (the pc) = 0x01033AAC */
#define ADDRESS_OF_FUNCTION_01033bb4_OFFSET 0x000000CC   /* was DAT_01033b20 (word at 0x01033B20); PC-relative offset: + 0x1033ae8 (the pc) = 0x01033BB4 */
#define ADDRESS_OF_FUNCTION_01033b34_OFFSET 0x00000040   /* was DAT_01033b24 (word at 0x01033B24); PC-relative offset: + 0x1033af4 (the pc) = 0x01033B34 */
#define ADDRESS_OF_FUNCTION_01033c50_OFFSET 0x00000150   /* was DAT_01033b28 (word at 0x01033B28); PC-relative offset: + 0x1033b00 (the pc) = 0x01033C50 */
#define ADDRESS_OF_FUNCTION_01033a24_OFFSET 0xFFFFFF18   /* was DAT_01033b2c (word at 0x01033B2C); PC-relative offset: + 0x1033b0c (the pc) = 0x01033A24 */
#define ADDRESS_OF_FUNCTION_01033b4c_OFFSET 0x00000034   /* was DAT_01033b30 (word at 0x01033B30); PC-relative offset: + 0x1033b18 (the pc) = 0x01033B4C */
#define ADDRESS_OF_FUNCTION_01033ec4_OFFSET 0x00000068   /* was DAT_01033ea8 (word at 0x01033EA8); PC-relative offset: + 0x1033e5c (the pc) = 0x01033EC4 */
#define ADDRESS_OF_FUNCTION_010340d0_OFFSET 0x00000268   /* was DAT_01033eac (word at 0x01033EAC); PC-relative offset: + 0x1033e68 (the pc) = 0x010340D0 */
#define ADDRESS_OF_FUNCTION_01033db4_OFFSET 0xFFFFFF40   /* was DAT_01033eb0 (word at 0x01033EB0); PC-relative offset: + 0x1033e74 (the pc) = 0x01033DB4 */
#define ADDRESS_OF_FUNCTION_01033dcc_OFFSET 0xFFFFFF4C   /* was DAT_01033eb4 (word at 0x01033EB4); PC-relative offset: + 0x1033e80 (the pc) = 0x01033DCC */
#define ADDRESS_OF_FUNCTION_01033d40_OFFSET 0xFFFFFEB4   /* was DAT_01033eb8 (word at 0x01033EB8); PC-relative offset: + 0x1033e8c (the pc) = 0x01033D40 */
#define ADDRESS_OF_FUNCTION_01033ccc_OFFSET 0xFFFFFE34   /* was DAT_01033ebc (word at 0x01033EBC); PC-relative offset: + 0x1033e98 (the pc) = 0x01033CCC */
#define ADDRESS_OF_FUNCTION_0103418c_OFFSET 0x000002E8   /* was DAT_01033ec0 (word at 0x01033EC0); PC-relative offset: + 0x1033ea4 (the pc) = 0x0103418C */
#define DATA_AT_0100255C_OFFSET_3 0xFFFCE618   /* was DAT_010340c8 (word at 0x010340C8); PC-relative offset: + 0x1033f44 (the pc) = 0x0100255C */
#define DATA_AT_0100252C_OFFSET_3 0xFFFCE55C   /* was DAT_010340cc (word at 0x010340CC); PC-relative offset: + 0x1033fd0 (the pc) = 0x0100252C */
#define ADDRESS_OF_FUNCTION_010343f4_OFFSET 0x00000058   /* was DAT_010343dc (word at 0x010343DC); PC-relative offset: + 0x103439c (the pc) = 0x010343F4 */
#define ADDRESS_OF_FUNCTION_010346bc_OFFSET 0x00000314   /* was DAT_010343e0 (word at 0x010343E0); PC-relative offset: + 0x10343a8 (the pc) = 0x010346BC */
#define ADDRESS_OF_FUNCTION_010342f0_OFFSET 0xFFFFFF3C   /* was DAT_010343e4 (word at 0x010343E4); PC-relative offset: + 0x10343b4 (the pc) = 0x010342F0 */
#define ADDRESS_OF_FUNCTION_01034260_OFFSET 0xFFFFFEA0   /* was DAT_010343e8 (word at 0x010343E8); PC-relative offset: + 0x10343c0 (the pc) = 0x01034260 */
#define ADDRESS_OF_FUNCTION_01034308_OFFSET 0xFFFFFF3C   /* was DAT_010343ec (word at 0x010343EC); PC-relative offset: + 0x10343cc (the pc) = 0x01034308 */
#define ADDRESS_OF_FUNCTION_01034834_OFFSET 0x0000045C   /* was DAT_010343f0 (word at 0x010343F0); PC-relative offset: + 0x10343d8 (the pc) = 0x01034834 */
#define DATA_AT_01002584_OFFSET_2 0xFFFCE108   /* was DAT_010346b0 (word at 0x010346B0); PC-relative offset: + 0x103447c (the pc) = 0x01002584 */
#define DATA_AT_0100255C_OFFSET_4 0xFFFCE048   /* was DAT_010346b4 (word at 0x010346B4); PC-relative offset: + 0x1034514 (the pc) = 0x0100255C */
#define DATA_AT_0100252C_OFFSET_4 0xFFFCDF8C   /* was DAT_010346b8 (word at 0x010346B8); PC-relative offset: + 0x10345a0 (the pc) = 0x0100252C */
#define DATA_AT_01002584_OFFSET_3 0xFFFCDE44   /* was DAT_01034830 (word at 0x01034830); PC-relative offset: + 0x1034740 (the pc) = 0x01002584 */
#define ADDRESS_OF_FUNCTION_01034934_OFFSET 0xFFFFFEB0   /* was DAT_01034b0c (word at 0x01034B0C); PC-relative offset: + 0x1034a84 (the pc) = 0x01034934 */
#define ADDRESS_OF_FUNCTION_0103491c_OFFSET 0xFFFFFE8C   /* was DAT_01034b10 (word at 0x01034B10); PC-relative offset: + 0x1034a90 (the pc) = 0x0103491C */
#define ADDRESS_OF_FUNCTION_01034c3c_OFFSET 0x000001A0   /* was DAT_01034b14 (word at 0x01034B14); PC-relative offset: + 0x1034a9c (the pc) = 0x01034C3C */
#define ADDRESS_OF_FUNCTION_01034b5c_OFFSET 0x000000B4   /* was DAT_01034b18 (word at 0x01034B18); PC-relative offset: + 0x1034aa8 (the pc) = 0x01034B5C */
#define ADDRESS_OF_FUNCTION_01034cf0_OFFSET 0x0000023C   /* was DAT_01034b1c (word at 0x01034B1C); PC-relative offset: + 0x1034ab4 (the pc) = 0x01034CF0 */
#define ADDRESS_OF_FUNCTION_01034b3c_OFFSET 0x0000007C   /* was DAT_01034b20 (word at 0x01034B20); PC-relative offset: + 0x1034ac0 (the pc) = 0x01034B3C */
#define ADDRESS_OF_FUNCTION_01034cd8_OFFSET 0x0000020C   /* was DAT_01034b24 (word at 0x01034B24); PC-relative offset: + 0x1034acc (the pc) = 0x01034CD8 */
#define ADDRESS_OF_FUNCTION_010349a0_OFFSET 0xFFFFFEC8   /* was DAT_01034b28 (word at 0x01034B28); PC-relative offset: + 0x1034ad8 (the pc) = 0x010349A0 */
#define ADDRESS_OF_FUNCTION_01034d08_OFFSET 0x00000224   /* was DAT_01034b2c (word at 0x01034B2C); PC-relative offset: + 0x1034ae4 (the pc) = 0x01034D08 */
#define ADDRESS_OF_FUNCTION_010349b8_OFFSET 0xFFFFFEC8   /* was DAT_01034b30 (word at 0x01034B30); PC-relative offset: + 0x1034af0 (the pc) = 0x010349B8 */
#define ADDRESS_OF_FUNCTION_01034b78_OFFSET 0x0000007C   /* was DAT_01034b34 (word at 0x01034B34); PC-relative offset: + 0x1034afc (the pc) = 0x01034B78 */
#define ADDRESS_OF_FUNCTION_010348b0_OFFSET 0xFFFFFDA8   /* was DAT_01034b38 (word at 0x01034B38); PC-relative offset: + 0x1034b08 (the pc) = 0x010348B0 */
#define DATA_AT_0100203C_OFFSET_40 0xFFFCD040   /* was DAT_010350ec (word at 0x010350EC); PC-relative offset: + 0x1034ffc (the pc) = 0x0100203C */
#define DATA_AT_01001EAC_OFFSET_11 0xFFFCCEA4   /* was DAT_010350f0 (word at 0x010350F0); PC-relative offset: + 0x1035008 (the pc) = 0x01001EAC */
#define WORD_HEXADECIMAL_FFFCD4EC 0xFFFCD4EC   /* was DAT_010350f4 (word at 0x010350F4); value 0xFFFCD4EC (-207636) */
#define ADDRESS_OF_FUNCTION_010350fc_OFFSET 0xFFFFFF74   /* was DAT_01035234 (word at 0x01035234); PC-relative offset: + 0x1035188 (the pc) = 0x010350FC */
#define ADDRESS_OF_FUNCTION_01035304_OFFSET 0x00000170   /* was DAT_01035238 (word at 0x01035238); PC-relative offset: + 0x1035194 (the pc) = 0x01035304 */
#define ADDRESS_OF_FUNCTION_01034f74_OFFSET 0xFFFFFDD4   /* was DAT_0103523c (word at 0x0103523C); PC-relative offset: + 0x10351a0 (the pc) = 0x01034F74 */
#define ADDRESS_OF_FUNCTION_01034f00_OFFSET 0xFFFFFD54   /* was DAT_01035240 (word at 0x01035240); PC-relative offset: + 0x10351ac (the pc) = 0x01034F00 */
#define ADDRESS_OF_FUNCTION_01034d24_OFFSET 0xFFFFFB6C   /* was DAT_01035244 (word at 0x01035244); PC-relative offset: + 0x10351b8 (the pc) = 0x01034D24 */
#define ADDRESS_OF_FUNCTION_01035270_OFFSET 0x000000AC   /* was DAT_01035248 (word at 0x01035248); PC-relative offset: + 0x10351c4 (the pc) = 0x01035270 */
#define ADDRESS_OF_FUNCTION_01034da8_OFFSET 0xFFFFFBD8   /* was DAT_0103524c (word at 0x0103524C); PC-relative offset: + 0x10351d0 (the pc) = 0x01034DA8 */
#define ADDRESS_OF_FUNCTION_01034e8c_OFFSET 0xFFFFFCB0   /* was DAT_01035250 (word at 0x01035250); PC-relative offset: + 0x10351dc (the pc) = 0x01034E8C */
#define ADDRESS_OF_FUNCTION_01034f94_OFFSET 0xFFFFFDAC   /* was DAT_01035254 (word at 0x01035254); PC-relative offset: + 0x10351e8 (the pc) = 0x01034F94 */
#define ADDRESS_OF_FUNCTION_01035114_OFFSET 0xFFFFFF20   /* was DAT_01035258 (word at 0x01035258); PC-relative offset: + 0x10351f4 (the pc) = 0x01035114 */
#define ADDRESS_OF_FUNCTION_01035318_OFFSET 0x00000118   /* was DAT_0103525c (word at 0x0103525C); PC-relative offset: + 0x1035200 (the pc) = 0x01035318 */
#define ADDRESS_OF_FUNCTION_010352f4_OFFSET 0x000000E8   /* was DAT_01035260 (word at 0x01035260); PC-relative offset: + 0x103520c (the pc) = 0x010352F4 */
#define ADDRESS_OF_FUNCTION_01035134_OFFSET 0xFFFFFF1C   /* was DAT_01035264 (word at 0x01035264); PC-relative offset: + 0x1035218 (the pc) = 0x01035134 */
#define ADDRESS_OF_FUNCTION_0103515c_OFFSET 0xFFFFFF38   /* was DAT_01035268 (word at 0x01035268); PC-relative offset: + 0x1035224 (the pc) = 0x0103515C */
#define ADDRESS_OF_FUNCTION_01034e14_OFFSET 0xFFFFFBE4   /* was DAT_0103526c (word at 0x0103526C); PC-relative offset: + 0x1035230 (the pc) = 0x01034E14 */
extern undefined4 STRING_INVALID_CHUNK_TYPE_SELF_RELATIVE_OFFSET;   /* was DAT_01035484 (word at 0x01035484 = 0x0000BC4C); word relative to its own address: 0x01035484 + 0x0000BC4C = 0x010410D0 */
#define INTEGER_3855 0x00000F0F   /* was DAT_010356fc, DAT_01035e78 (word at 0x010356FC); integer 3855 */
#define INTEGER_16191 0x00003F3F   /* was DAT_01035700, DAT_01035e80 (word at 0x01035700); integer 16191 */
#define STRING_CRC_ERROR_OFFSET 0x0000B6E8   /* was DAT_01035810 (word at 0x01035810); PC-relative offset: + 0x10357dc (the pc) = 0x01040EC4 */
#define INTEGER_42468 0x0000A5E4   /* was DAT_01035a20 (word at 0x01035A20); integer 42468 */
#define STRING_INCOMPATIBLE_LIBPNG_VERSION_IN_APPLICATION_AND_OFFSET 0x0000A144   /* was DAT_01035a24 (word at 0x01035A24); PC-relative offset: + 0x1035974 (the pc) = 0x0103FAB8 */
#define ADDRESS_OF_FUNCTION_01037eec_OFFSET 0x00002554   /* was DAT_01035a28 (word at 0x01035A28); PC-relative offset: + 0x1035998 (the pc) = 0x01037EEC */
#define DATA_AT_01037F3C_OFFSET 0x00002598   /* was DAT_01035a2c (word at 0x01035A2C); PC-relative offset: + 0x10359a4 (the pc) = 0x01037F3C */
#define INTEGER_41272 0x0000A138   /* was DAT_01035a30 (word at 0x01035A30); integer 41272 */
#define STRING_ZLIB_VERSION_ERROR_OFFSET 0x0000A140   /* was DAT_01035a34 (word at 0x01035A34); PC-relative offset: + 0x10359cc (the pc) = 0x0103FB0C */
#define STRING_ZLIB_MEMORY_ERROR_OFFSET 0x0000A118   /* was DAT_01035a38 (word at 0x01035A38); PC-relative offset: + 0x10359e0 (the pc) = 0x0103FAF8 */
#define STRING_UNKNOWN_ZLIB_ERROR_OFFSET 0x0000A12C   /* was DAT_01035a3c (word at 0x01035A3C); PC-relative offset: + 0x10359f4 (the pc) = 0x0103FB20 */
#define DATA_AT_0103FF18_OFFSET 0x0000A380   /* was DAT_01035e74 (word at 0x01035E74); PC-relative offset: + 0x1035b98 (the pc) = 0x0103FF18 */
#define INTEGER_32639 0x00007F7F   /* was DAT_01035e7c (word at 0x01035E7C); integer 32639 */
#define STRING_NULL_ROW_BUFFER_OFFSET 0x0000A250   /* was DAT_01035f2c (word at 0x01035F2C); PC-relative offset: + 0x1035ea0 (the pc) = 0x010400F0 */
#define STRING_0123456789ABCDEF_OFFSET 0x00009F68   /* was DAT_01036184 (word at 0x01036184); PC-relative offset: + 0x10360d0 (the pc) = 0x01040038 */
#define STRING_WIDTH_TOO_LARGE_FOR_LIBPNG_TO_OFFSET 0x00009DA0   /* was DAT_0103636c (word at 0x0103636C); PC-relative offset: + 0x1036360 (the pc) = 0x01040100 */
#define STRING_NO_IMAGE_IN_FILE_OFFSET 0x0000AB40   /* was DAT_010364cc (word at 0x010364CC); PC-relative offset: + 0x1036498 (the pc) = 0x01040FD8 */
#define INTEGER_43828 0x0000AB34   /* was DAT_010364d0 (word at 0x010364D0); integer 43828 */
#define STRING_OUT_OF_PLACE_IHDR_OFFSET 0x0000A9D4   /* was DAT_01036608 (word at 0x01036608); PC-relative offset: + 0x10364fc (the pc) = 0x01040ED0 */
#define STRING_INVALID_IHDR_CHUNK_OFFSET 0x0000A9D4   /* was DAT_0103660c (word at 0x0103660C); PC-relative offset: + 0x1036510 (the pc) = 0x01040EE4 */
#define STRING_MISSING_IHDR_BEFORE_PLTE_OFFSET 0x0000A8C0   /* was DAT_01036818 (word at 0x01036818); PC-relative offset: + 0x1036638 (the pc) = 0x01040EF8 */
#define STRING_INVALID_PLTE_AFTER_IDAT_OFFSET 0x0000A8CC   /* was DAT_0103681c (word at 0x0103681C); PC-relative offset: + 0x1036648 (the pc) = 0x01040F14 */
#define STRING_DUPLICATE_PLTE_CHUNK_OFFSET 0x0000A8D0   /* was DAT_01036820 (word at 0x01036820); PC-relative offset: + 0x103665c (the pc) = 0x01040F2C */
#define STRING_IGNORING_PLTE_CHUNK_IN_GRAYSCALE_PNG_OFFSET 0x0000A8C0   /* was DAT_01036824 (word at 0x01036824); PC-relative offset: + 0x1036684 (the pc) = 0x01040F44 */
#define STRING_INVALID_PALETTE_CHUNK_OFFSET 0x0000A89C   /* was DAT_01036828 (word at 0x01036828); PC-relative offset: + 0x10366d0 (the pc) = 0x01040F6C */
#define STRING_CRC_ERROR_OFFSET_2 0x0000A75C   /* was DAT_0103682c (word at 0x0103682C); PC-relative offset: + 0x1036768 (the pc) = 0x01040EC4 */
#define STRING_TRUNCATING_INCORRECT_TRNS_CHUNK_LENGTH_OFFSET 0x0000A798   /* was DAT_01036830 (word at 0x01036830); PC-relative offset: + 0x10367ec (the pc) = 0x01040F84 */
#define STRING_TRUNCATING_INCORRECT_INFO_TRNS_CHUNK_LENGTH_OFFSET 0x0000A7A0   /* was DAT_01036834 (word at 0x01036834); PC-relative offset: + 0x103680c (the pc) = 0x01040FAC */
#define STRING_MISSING_IHDR_BEFORE_TRNS_OFFSET 0x0000A7A4   /* was DAT_010369d8 (word at 0x010369D8); PC-relative offset: + 0x1036864 (the pc) = 0x01041008 */
#define STRING_INVALID_TRNS_AFTER_IDAT_OFFSET 0x0000A7A8   /* was DAT_010369dc (word at 0x010369DC); PC-relative offset: + 0x103687c (the pc) = 0x01041024 */
#define STRING_DUPLICATE_TRNS_CHUNK_OFFSET 0x0000A7A8   /* was DAT_010369e0 (word at 0x010369E0); PC-relative offset: + 0x1036894 (the pc) = 0x0104103C */
#define STRING_INCORRECT_TRNS_CHUNK_LENGTH_OFFSET 0x0000A7CC   /* was DAT_010369e4 (word at 0x010369E4); PC-relative offset: + 0x10368a4 (the pc) = 0x01041070 */
#define STRING_MISSING_PLTE_BEFORE_TRNS_OFFSET 0x0000A790   /* was DAT_010369e8 (word at 0x010369E8); PC-relative offset: + 0x10368c4 (the pc) = 0x01041054 */
#define STRING_ZERO_LENGTH_TRNS_CHUNK_OFFSET 0x0000A7A4   /* was DAT_010369ec (word at 0x010369EC); PC-relative offset: + 0x10368e8 (the pc) = 0x0104108C */
#define STRING_TRNS_CHUNK_NOT_ALLOWED_WITH_ALPHA_OFFSET 0x0000A744   /* was DAT_010369f0 (word at 0x010369F0); PC-relative offset: + 0x1036960 (the pc) = 0x010410A4 */
#define STRING_IDAT_OFFSET 0x000094C7   /* was DAT_01036a68 (word at 0x01036A68); PC-relative offset: + 0x1036a20 (the pc) = 0x0103FEE7 */
#define STRING_UNKNOWN_CRITICAL_CHUNK_OFFSET 0x0000A690   /* was DAT_01036a6c (word at 0x01036A6C); PC-relative offset: + 0x1036a54 (the pc) = 0x010410E4 */
#define STRING_OUT_OF_MEMORY_OFFSET 0x0000A6A8   /* was DAT_01036b08 (word at 0x01036B08); PC-relative offset: + 0x1036afc (the pc) = 0x010411A4 */
#define STRING_IDAT_OFFSET_2 0x000092A3   /* was DAT_01036d9c (word at 0x01036D9C); PC-relative offset: + 0x1036c44 (the pc) = 0x0103FEE7 */
#define STRING_TOO_MANY_IDAT_S_FOUND_OFFSET 0x0000910C   /* was DAT_01036da0 (word at 0x01036DA0); PC-relative offset: + 0x1036c4c (the pc) = 0x0103FD58 */
#define STRING_PLTE_OFFSET 0x0000929D   /* was DAT_01036da4 (word at 0x01036DA4); PC-relative offset: + 0x1036c54 (the pc) = 0x0103FEF1 */
#define STRING_TRNS_OFFSET 0x0000929A   /* was DAT_01036da8 (word at 0x01036DA8); PC-relative offset: + 0x1036c5c (the pc) = 0x0103FEF6 */
#define STRING_IHDR_OFFSET 0x00009242   /* was DAT_01036dac (word at 0x01036DAC); PC-relative offset: + 0x1036ca0 (the pc) = 0x0103FEE2 */
#define STRING_IEND_OFFSET 0x0000921C   /* was DAT_01036db0 (word at 0x01036DB0); PC-relative offset: + 0x1036cd0 (the pc) = 0x0103FEEC */
#define STRING_IGNORING_BAD_ADAPTIVE_FILTER_TYPE_OFFSET 0x0000A1A0   /* was DAT_01036f68 (word at 0x01036F68); PC-relative offset: + 0x1036f5c (the pc) = 0x010410FC */
#define DATA_AT_0103FEFC_OFFSET 0x00008F34   /* was DAT_01037224 (word at 0x01037224); PC-relative offset: + 0x1036fc8 (the pc) = 0x0103FEFC */
#define DATA_AT_0103FF18_OFFSET_2 0x00008F48   /* was DAT_01037228 (word at 0x01037228); PC-relative offset: + 0x1036fd0 (the pc) = 0x0103FF18 */
#define DATA_AT_0103FF34_OFFSET 0x00008F5C   /* was DAT_0103722c (word at 0x0103722C); PC-relative offset: + 0x1036fd8 (the pc) = 0x0103FF34 */
#define DATA_AT_0103FF50_OFFSET 0x00008F70   /* was DAT_01037230 (word at 0x01037230); PC-relative offset: + 0x1036fe0 (the pc) = 0x0103FF50 */
#define STRING_IDAT_OFFSET_3 0x00008E5B   /* was DAT_01037234 (word at 0x01037234); PC-relative offset: + 0x103708c (the pc) = 0x0103FEE7 */
#define STRING_NOT_ENOUGH_IMAGE_DATA_OFFSET 0x0000A08C   /* was DAT_01037238 (word at 0x01037238); PC-relative offset: + 0x1037094 (the pc) = 0x01041120 */
#define STRING_DECOMPRESSION_ERROR_OFFSET 0x0000A0B4   /* was DAT_0103723c (word at 0x0103723C); PC-relative offset: + 0x103709c (the pc) = 0x01041150 */
#define STRING_EXTRA_COMPRESSED_DATA_OFFSET 0x0000A094   /* was DAT_01037240 (word at 0x01037240); PC-relative offset: + 0x10370a4 (the pc) = 0x01041138 */
#define STRING_EXTRA_COMPRESSION_DATA_OFFSET 0x00009F90   /* was DAT_01037244 (word at 0x01037244); PC-relative offset: + 0x10371d4 (the pc) = 0x01041164 */
#define STRING_NOT_A_PNG_FILE_OFFSET 0x00008914   /* was DAT_010374b8 (word at 0x010374B8); PC-relative offset: + 0x1037324 (the pc) = 0x0103FC38 */
#define STRING_PNG_FILE_CORRUPTED_BY_ASCII_CONVERSION_OFFSET 0x00008918   /* was DAT_010374bc (word at 0x010374BC); PC-relative offset: + 0x1037330 (the pc) = 0x0103FC48 */
#define STRING_IEND_OFFSET_2 0x00008B9C   /* was DAT_010374c0 (word at 0x010374C0); PC-relative offset: + 0x1037350 (the pc) = 0x0103FEEC */
#define STRING_PLTE_OFFSET_2 0x00008B99   /* was DAT_010374c4 (word at 0x010374C4); PC-relative offset: + 0x1037358 (the pc) = 0x0103FEF1 */
#define STRING_IDAT_OFFSET_4 0x00008B87   /* was DAT_010374c8 (word at 0x010374C8); PC-relative offset: + 0x1037360 (the pc) = 0x0103FEE7 */
#define STRING_TRNS_OFFSET_2 0x00008B8E   /* was DAT_010374cc (word at 0x010374CC); PC-relative offset: + 0x1037368 (the pc) = 0x0103FEF6 */
#define STRING_IHDR_OFFSET_2 0x00008B36   /* was DAT_010374d0 (word at 0x010374D0); PC-relative offset: + 0x10373ac (the pc) = 0x0103FEE2 */
#define STRING_MISSING_IHDR_BEFORE_IDAT_OFFSET 0x00008820   /* was DAT_010374d4 (word at 0x010374D4); PC-relative offset: + 0x1037450 (the pc) = 0x0103FC70 */
#define STRING_MISSING_PLTE_BEFORE_IDAT_OFFSET 0x00008820   /* was DAT_010374d8 (word at 0x010374D8); PC-relative offset: + 0x103746c (the pc) = 0x0103FC8C */
#define STRING_INVALID_ATTEMPT_TO_READ_ROW_DATA_OFFSET 0x000086B0   /* was DAT_010378ec (word at 0x010378EC); PC-relative offset: + 0x1037640 (the pc) = 0x0103FCF0 */
#define INTEGER_34955 0x0000888B   /* was DAT_010378f0 (word at 0x010378F0); integer 34955 */
#define STRING_NOT_ENOUGH_IMAGE_DATA_OFFSET_2 0x000086B0   /* was DAT_010378f4 (word at 0x010378F4); PC-relative offset: + 0x1037664 (the pc) = 0x0103FD14 */
#define STRING_EXTRA_COMPRESSED_DATA_OFFSET_2 0x000085D4   /* was DAT_010378f8 (word at 0x010378F8); PC-relative offset: + 0x1037758 (the pc) = 0x0103FD2C */
#define STRING_DECOMPRESSION_ERROR_OFFSET_2 0x000085B0   /* was DAT_010378fc (word at 0x010378FC); PC-relative offset: + 0x1037794 (the pc) = 0x0103FD44 */
#define DATA_AT_0103FF50_OFFSET_2 0x000085F4   /* was DAT_01037a60 (word at 0x01037A60); PC-relative offset: + 0x103795c (the pc) = 0x0103FF50 */
#define DATA_AT_0103FF34_OFFSET_2 0x000085C0   /* was DAT_01037a64 (word at 0x01037A64); PC-relative offset: + 0x1037974 (the pc) = 0x0103FF34 */
#define DATA_AT_0103FF18_OFFSET_3 0x00008580   /* was DAT_01037a68 (word at 0x01037A68); PC-relative offset: + 0x1037998 (the pc) = 0x0103FF18 */
#define DATA_AT_0103FEFC_OFFSET_2 0x00008550   /* was DAT_01037a6c (word at 0x01037A6C); PC-relative offset: + 0x10379ac (the pc) = 0x0103FEFC */
#define STRING_IMAGE_WIDTH_OR_HEIGHT_IS_ZERO_OFFSET 0x0000AB40   /* was DAT_01037c54 (word at 0x01037C54); PC-relative offset: + 0x1037ad0 (the pc) = 0x01042610 */
#define STRING_INVALID_IMAGE_SIZE_IN_IHDR_OFFSET 0x0000AB50   /* was DAT_01037c58 (word at 0x01037C58); PC-relative offset: + 0x1037ae8 (the pc) = 0x01042638 */
#define STRING_INVALID_BIT_DEPTH_IN_IHDR_OFFSET 0x0000AB48   /* was DAT_01037c5c (word at 0x01037C5C); PC-relative offset: + 0x1037b0c (the pc) = 0x01042654 */
#define STRING_INVALID_COLOR_TYPE_IN_IHDR_OFFSET 0x0000AB38   /* was DAT_01037c60 (word at 0x01037C60); PC-relative offset: + 0x1037b38 (the pc) = 0x01042670 */
#define STRING_INVALID_COLOR_TYPE_SLASH_BIT_DEPTH_OFFSET 0x0000AB18   /* was DAT_01037c64 (word at 0x01037C64); PC-relative offset: + 0x1037b74 (the pc) = 0x0104268C */
#define STRING_UNKNOWN_INTERLACE_METHOD_IN_IHDR_OFFSET 0x0000AB34   /* was DAT_01037c68 (word at 0x01037C68); PC-relative offset: + 0x1037b8c (the pc) = 0x010426C0 */
#define STRING_UNKNOWN_COMPRESSION_METHOD_IN_IHDR_OFFSET 0x0000AB44   /* was DAT_01037c6c (word at 0x01037C6C); PC-relative offset: + 0x1037ba0 (the pc) = 0x010426E4 */
#define STRING_UNKNOWN_FILTER_METHOD_IN_IHDR_OFFSET 0x0000AB54   /* was DAT_01037c70 (word at 0x01037C70); PC-relative offset: + 0x1037bb4 (the pc) = 0x01042708 */
#define STRING_WIDTH_TOO_LARGE_TO_PROCESS_IMAGE_OFFSET 0x0000AAE4   /* was DAT_01037c74 (word at 0x01037C74); PC-relative offset: + 0x1037c44 (the pc) = 0x01042728 */
#define STRING_IT_S_AN_ERROR_TO_SET_OFFSET 0x00008280   /* was DAT_01037d90 (word at 0x01037D90); PC-relative offset: + 0x1037d74 (the pc) = 0x0103FFF4 */
#define STRING_SAME_STRUCTURE_DOT_RESETTING_WRITE_DATA_OFFSET 0x00008238   /* was DAT_01037d94 (word at 0x01037D94); PC-relative offset: + 0x1037d88 (the pc) = 0x0103FFC0 */
#define INTEGER_32536 0x00007F18   /* was DAT_01037eac (word at 0x01037EAC); integer 32536 */
#define ADDRESS_OF_FUNCTION_01037fa0_OFFSET 0xFFFFFF88   /* was DAT_01038088 (word at 0x01038088); PC-relative offset: + 0x1038018 (the pc) = 0x01037FA0 */
#define ADDRESS_OF_FUNCTION_010380d0_OFFSET 0x000000AC   /* was DAT_0103808c (word at 0x0103808C); PC-relative offset: + 0x1038024 (the pc) = 0x010380D0 */
#define ADDRESS_OF_FUNCTION_01037fc0_OFFSET 0xFFFFFF90   /* was DAT_01038090 (word at 0x01038090); PC-relative offset: + 0x1038030 (the pc) = 0x01037FC0 */
#define ADDRESS_OF_FUNCTION_01038178_OFFSET 0x0000013C   /* was DAT_01038094 (word at 0x01038094); PC-relative offset: + 0x103803c (the pc) = 0x01038178 */
#define ADDRESS_OF_FUNCTION_01037fe0_OFFSET 0xFFFFFF98   /* was DAT_01038098 (word at 0x01038098); PC-relative offset: + 0x1038048 (the pc) = 0x01037FE0 */
#define ADDRESS_OF_FUNCTION_01038208_OFFSET 0x000001B4   /* was DAT_0103809c (word at 0x0103809C); PC-relative offset: + 0x1038054 (the pc) = 0x01038208 */
#define ADDRESS_OF_FUNCTION_01038148_OFFSET 0x000000E8   /* was DAT_010380a0 (word at 0x010380A0); PC-relative offset: + 0x1038060 (the pc) = 0x01038148 */
#define ADDRESS_OF_FUNCTION_01038160_OFFSET 0x000000F4   /* was DAT_010380a4 (word at 0x010380A4); PC-relative offset: + 0x103806c (the pc) = 0x01038160 */
#define ADDRESS_OF_FUNCTION_010380b0_OFFSET 0x00000038   /* was DAT_010380a8 (word at 0x010380A8); PC-relative offset: + 0x1038078 (the pc) = 0x010380B0 */
#define ADDRESS_OF_FUNCTION_010381f0_OFFSET 0x0000016C   /* was DAT_010380ac (word at 0x010380AC); PC-relative offset: + 0x1038084 (the pc) = 0x010381F0 */
#define ADDRESS_OF_FUNCTION_01038340_OFFSET 0xFFFFFDA4   /* was DAT_01038600 (word at 0x01038600); PC-relative offset: + 0x103859c (the pc) = 0x01038340 */
#define ADDRESS_OF_FUNCTION_01038358_OFFSET 0xFFFFFDB0   /* was DAT_01038604 (word at 0x01038604); PC-relative offset: + 0x10385a8 (the pc) = 0x01038358 */
#define ADDRESS_OF_FUNCTION_01038488_OFFSET 0xFFFFFED4   /* was DAT_01038608 (word at 0x01038608); PC-relative offset: + 0x10385b4 (the pc) = 0x01038488 */
#define ADDRESS_OF_FUNCTION_010383c4_OFFSET 0xFFFFFE04   /* was DAT_0103860c (word at 0x0103860C); PC-relative offset: + 0x10385c0 (the pc) = 0x010383C4 */
#define ADDRESS_OF_FUNCTION_010383dc_OFFSET 0xFFFFFE10   /* was DAT_01038610 (word at 0x01038610); PC-relative offset: + 0x10385cc (the pc) = 0x010383DC */
#define ADDRESS_OF_FUNCTION_010383f4_OFFSET 0xFFFFFE1C   /* was DAT_01038614 (word at 0x01038614); PC-relative offset: + 0x10385d8 (the pc) = 0x010383F4 */
#define ADDRESS_OF_FUNCTION_010384a0_OFFSET 0xFFFFFEBC   /* was DAT_01038618 (word at 0x01038618); PC-relative offset: + 0x10385e4 (the pc) = 0x010384A0 */
#define ADDRESS_OF_FUNCTION_01038518_OFFSET 0xFFFFFF28   /* was DAT_0103861c (word at 0x0103861C); PC-relative offset: + 0x10385f0 (the pc) = 0x01038518 */
#define ADDRESS_OF_FUNCTION_0103840c_OFFSET 0xFFFFFE10   /* was DAT_01038620 (word at 0x01038620); PC-relative offset: + 0x10385fc (the pc) = 0x0103840C */
#define ADDRESS_OF_FUNCTION_01038934_OFFSET 0x00000038   /* was DAT_01038924 (word at 0x01038924); PC-relative offset: + 0x10388fc (the pc) = 0x01038934 */
#define ADDRESS_OF_FUNCTION_01038b54_OFFSET 0x0000024C   /* was DAT_01038928 (word at 0x01038928); PC-relative offset: + 0x1038908 (the pc) = 0x01038B54 */
#define ADDRESS_OF_FUNCTION_01038878_OFFSET 0xFFFFFF64   /* was DAT_0103892c (word at 0x0103892C); PC-relative offset: + 0x1038914 (the pc) = 0x01038878 */
#define ADDRESS_OF_FUNCTION_01038794_OFFSET 0xFFFFFE74   /* was DAT_01038930 (word at 0x01038930); PC-relative offset: + 0x1038920 (the pc) = 0x01038794 */
#define DATA_AT_0100255C_OFFSET_5 0xFFFC9BA8   /* was DAT_01038b4c (word at 0x01038B4C); PC-relative offset: + 0x10389b4 (the pc) = 0x0100255C */
#define DATA_AT_0100252C_OFFSET_5 0xFFFC9AEC   /* was DAT_01038b50 (word at 0x01038B50); PC-relative offset: + 0x1038a40 (the pc) = 0x0100252C */
#define ADDRESS_OF_FUNCTION_01038e84_OFFSET 0x000000A8   /* was DAT_01038e58 (word at 0x01038E58); PC-relative offset: + 0x1038ddc (the pc) = 0x01038E84 */
#define ADDRESS_OF_FUNCTION_01038c8c_OFFSET 0xFFFFFEA4   /* was DAT_01038e5c (word at 0x01038E5C); PC-relative offset: + 0x1038de8 (the pc) = 0x01038C8C */
#define ADDRESS_OF_FUNCTION_01038f50_OFFSET 0x0000015C   /* was DAT_01038e60 (word at 0x01038E60); PC-relative offset: + 0x1038df4 (the pc) = 0x01038F50 */
#define ADDRESS_OF_FUNCTION_01038d58_OFFSET 0xFFFFFF58   /* was DAT_01038e64 (word at 0x01038E64); PC-relative offset: + 0x1038e00 (the pc) = 0x01038D58 */
#define ADDRESS_OF_FUNCTION_01038fe8_OFFSET 0x000001DC   /* was DAT_01038e68 (word at 0x01038E68); PC-relative offset: + 0x1038e0c (the pc) = 0x01038FE8 */
#define ADDRESS_OF_FUNCTION_01038cf8_OFFSET 0xFFFFFEE0   /* was DAT_01038e6c (word at 0x01038E6C); PC-relative offset: + 0x1038e18 (the pc) = 0x01038CF8 */
#define ADDRESS_OF_FUNCTION_01038d10_OFFSET 0xFFFFFEEC   /* was DAT_01038e70 (word at 0x01038E70); PC-relative offset: + 0x1038e24 (the pc) = 0x01038D10 */
#define ADDRESS_OF_FUNCTION_01038d28_OFFSET 0xFFFFFEF8   /* was DAT_01038e74 (word at 0x01038E74); PC-relative offset: + 0x1038e30 (the pc) = 0x01038D28 */
#define ADDRESS_OF_FUNCTION_01038d40_OFFSET 0xFFFFFF04   /* was DAT_01038e78 (word at 0x01038E78); PC-relative offset: + 0x1038e3c (the pc) = 0x01038D40 */
#define ADDRESS_OF_FUNCTION_01038f38_OFFSET 0x000000F0   /* was DAT_01038e7c (word at 0x01038E7C); PC-relative offset: + 0x1038e48 (the pc) = 0x01038F38 */
#define ADDRESS_OF_FUNCTION_01038f70_OFFSET 0x0000011C   /* was DAT_01038e80 (word at 0x01038E80); PC-relative offset: + 0x1038e54 (the pc) = 0x01038F70 */
#define DATA_AT_010427E8_OFFSET 0x00009748   /* was DAT_010390a8 (word at 0x010390A8); PC-relative offset: + 0x10390a0 (the pc) = 0x010427E8 */
#define ADDRESS_OF_FUNCTION_0103937c_OFFSET 0x00000058   /* was DAT_01039364 (word at 0x01039364); PC-relative offset: + 0x1039324 (the pc) = 0x0103937C */
#define ADDRESS_OF_FUNCTION_01039424_OFFSET 0x000000F4   /* was DAT_01039368 (word at 0x01039368); PC-relative offset: + 0x1039330 (the pc) = 0x01039424 */
#define ADDRESS_OF_FUNCTION_010392f4_OFFSET 0xFFFFFFB8   /* was DAT_0103936c (word at 0x0103936C); PC-relative offset: + 0x103933c (the pc) = 0x010392F4 */
#define ADDRESS_OF_FUNCTION_01039510_OFFSET 0x000001C8   /* was DAT_01039370 (word at 0x01039370); PC-relative offset: + 0x1039348 (the pc) = 0x01039510 */
#define ADDRESS_OF_FUNCTION_010392dc_OFFSET 0xFFFFFF88   /* was DAT_01039374 (word at 0x01039374); PC-relative offset: + 0x1039354 (the pc) = 0x010392DC */
#define ADDRESS_OF_FUNCTION_010394ac_OFFSET 0x0000014C   /* was DAT_01039378 (word at 0x01039378); PC-relative offset: + 0x1039360 (the pc) = 0x010394AC */
#define INTEGER_1036 0x0000040C   /* was DAT_01039764 (word at 0x01039764); integer 1036 */
#define INTEGER_25364 0x00006314   /* was DAT_01039768 (word at 0x01039768); integer 25364 */
#define WORD_HEXADECIMAL_0001000F 0x0001000F   /* was DAT_01039870 (word at 0x01039870); value 0x0001000F (65551) */
#define WORD_HEXADECIMAL_0001000E 0x0001000E   /* was DAT_01039874, DAT_01039de8 (word at 0x01039874); value 0x0001000E (65550) */
#define WORD_HEXADECIMAL_0001000D 0x0001000D   /* was DAT_01039878, DAT_0103a76c (word at 0x01039878); value 0x0001000D (65549) */
#define WORD_HEXADECIMAL_0001000C 0x0001000C   /* was DAT_0103987c (word at 0x0103987C); value 0x0001000C (65548) */
#define WORD_HEXADECIMAL_0001000A 0x0001000A   /* was DAT_01039880 (word at 0x01039880); value 0x0001000A (65546) */
#define WORD_HEXADECIMAL_00010009 0x00010009   /* was DAT_01039884 (word at 0x01039884); value 0x00010009 (65545) */
#define WORD_HEXADECIMAL_00010008 0x00010008   /* was DAT_01039888 (word at 0x01039888); value 0x00010008 (65544) */
#define WORD_HEXADECIMAL_00010002 0x00010002   /* was DAT_0103988c (word at 0x0103988C); value 0x00010002 (65538) */
#define WORD_HEXADECIMAL_00010006 0x00010006   /* was DAT_01039890 (word at 0x01039890); value 0x00010006 (65542) */
#define WORD_HEXADECIMAL_00010005 0x00010005   /* was DAT_01039894 (word at 0x01039894); value 0x00010005 (65541) */
#define WORD_HEXADECIMAL_00010004 0x00010004   /* was DAT_01039898 (word at 0x01039898); value 0x00010004 (65540) */
#define WORD_HEXADECIMAL_00010003 0x00010003   /* was DAT_0103989c (word at 0x0103989C); value 0x00010003 (65539) */
#define WORD_HEXADECIMAL_00010001 0x00010001   /* was DAT_010398a0, DAT_0103ae44 (word at 0x010398A0); value 0x00010001 (65537) */
#define ADDRESS_OF_FUNCTION_0103b0a4_OFFSET 0x00001630   /* was DAT_01039aa8 (word at 0x01039AA8); PC-relative offset: + 0x1039a74 (the pc) = 0x0103B0A4 */
#define STRING_SWVARC_COLON_OFFSET 0x00005F8C   /* was DAT_01039c0c (word at 0x01039C0C); PC-relative offset: + 0x1039adc (the pc) = 0x0103FA68 */
#define DATA_AT_0103FA70_OFFSET 0x00005F5C   /* was DAT_01039c10 (word at 0x01039C10); PC-relative offset: + 0x1039b14 (the pc) = 0x0103FA70 */
#define INTEGER_259 0x00000103   /* was DAT_01039c14 (word at 0x01039C14); integer 259 */
#define ADDRESS_OF_FUNCTION_0103aff8_OFFSET 0x0000148C   /* was DAT_01039c18 (word at 0x01039C18); PC-relative offset: + 0x1039b6c (the pc) = 0x0103AFF8 */
#define ADDRESS_OF_FUNCTION_0103b0a4_OFFSET_2 0x000014C8   /* was DAT_01039c20 (word at 0x01039C20); PC-relative offset: + 0x1039bdc (the pc) = 0x0103B0A4 */
#define ADDRESS_OF_ISwerve_AddRef_OFFSET 0xFFFEA910   /* was DAT_01039f9c (word at 0x01039F9C); PC-relative offset: + 0x1039e78 (the pc) = 0x01024788 */
#define ADDRESS_OF_ISwerve_Release_OFFSET 0xFFFEAAF4   /* was DAT_01039fa0 (word at 0x01039FA0); PC-relative offset: + 0x1039e84 (the pc) = 0x01024978 */
#define ADDRESS_OF_ISwerve_GetVersion_OFFSET 0xFFFEABD8   /* was DAT_01039fa4 (word at 0x01039FA4); PC-relative offset: + 0x1039e90 (the pc) = 0x01024A68 */
#define ADDRESS_OF_ISwerve_GetPixelFormat_OFFSET 0xFFFEAB80   /* was DAT_01039fa8 (word at 0x01039FA8); PC-relative offset: + 0x1039e9c (the pc) = 0x01024A1C */
#define ADDRESS_OF_ISwerve_CreateObject_OFFSET 0xFFFEA8F4   /* was DAT_01039fac (word at 0x01039FAC); PC-relative offset: + 0x1039ea8 (the pc) = 0x0102479C */
#define ADDRESS_OF_FUNCTION_010398e8_OFFSET 0xFFFFF974   /* was DAT_01039fb0 (word at 0x01039FB0); PC-relative offset: + 0x1039f74 (the pc) = 0x010398E8 */
#define ADDRESS_OF_swvObj_AddRef_OFFSET 0xFFFD78F8   /* was DAT_0103a770 (word at 0x0103A770); PC-relative offset: + 0x103a694 (the pc) = 0x01011F8C */
#define ADDRESS_OF_swvObj_Release_OFFSET 0xFFFD7BF4   /* was DAT_0103a774 (word at 0x0103A774); PC-relative offset: + 0x103a6a0 (the pc) = 0x01012294 */
#define ADDRESS_OF_swvObj_QueryInterface_OFFSET 0xFFFD7918   /* was DAT_0103a778 (word at 0x0103A778); PC-relative offset: + 0x103a6ac (the pc) = 0x01011FC4 */
#define STRING_1_DOT_2_DOT_0_OFFSET 0x000052D0   /* was DAT_0103ad1c (word at 0x0103AD1C); PC-relative offset: + 0x103a7d4 (the pc) = 0x0103FAA4 */
#define DATA_AT_0103FA74_OFFSET 0x00005264   /* was DAT_0103ad20 (word at 0x0103AD20); PC-relative offset: + 0x103a810 (the pc) = 0x0103FA74 */
#define ADDRESS_OF_FUNCTION_010159e4_OFFSET 0xFFFDB188   /* was DAT_0103ad24 (word at 0x0103AD24); PC-relative offset: + 0x103a85c (the pc) = 0x010159E4 */
#define ADDRESS_OF_FUNCTION_0103b3ec_OFFSET 0x000000A8   /* was DAT_0103b3c0 (word at 0x0103B3C0); PC-relative offset: + 0x103b344 (the pc) = 0x0103B3EC */
#define ADDRESS_OF_FUNCTION_0103b290_OFFSET 0xFFFFFF40   /* was DAT_0103b3c4 (word at 0x0103B3C4); PC-relative offset: + 0x103b350 (the pc) = 0x0103B290 */
#define ADDRESS_OF_FUNCTION_0103b57c_OFFSET 0x00000220   /* was DAT_0103b3c8 (word at 0x0103B3C8); PC-relative offset: + 0x103b35c (the pc) = 0x0103B57C */
#define ADDRESS_OF_FUNCTION_0103b278_OFFSET 0xFFFFFF10   /* was DAT_0103b3cc (word at 0x0103B3CC); PC-relative offset: + 0x103b368 (the pc) = 0x0103B278 */
#define ADDRESS_OF_FUNCTION_0103b480_OFFSET 0x0000010C   /* was DAT_0103b3d0 (word at 0x0103B3D0); PC-relative offset: + 0x103b374 (the pc) = 0x0103B480 */
#define ADDRESS_OF_FUNCTION_0103b260_OFFSET 0xFFFFFEE0   /* was DAT_0103b3d4 (word at 0x0103B3D4); PC-relative offset: + 0x103b380 (the pc) = 0x0103B260 */
#define ADDRESS_OF_FUNCTION_0103b46c_OFFSET 0x000000E0   /* was DAT_0103b3d8 (word at 0x0103B3D8); PC-relative offset: + 0x103b38c (the pc) = 0x0103B46C */
#define ADDRESS_OF_FUNCTION_0103b2fc_OFFSET 0xFFFFFF64   /* was DAT_0103b3dc (word at 0x0103B3DC); PC-relative offset: + 0x103b398 (the pc) = 0x0103B2FC */
#define ADDRESS_OF_FUNCTION_0103b314_OFFSET 0xFFFFFF70   /* was DAT_0103b3e0 (word at 0x0103B3E0); PC-relative offset: + 0x103b3a4 (the pc) = 0x0103B314 */
#define ADDRESS_OF_FUNCTION_0103b600_OFFSET 0x00000250   /* was DAT_0103b3e4 (word at 0x0103B3E4); PC-relative offset: + 0x103b3b0 (the pc) = 0x0103B600 */
#define ADDRESS_OF_FUNCTION_0103b4f0_OFFSET 0x00000134   /* was DAT_0103b3e8 (word at 0x0103B3E8); PC-relative offset: + 0x103b3bc (the pc) = 0x0103B4F0 */
#define ADDRESS_OF_FUNCTION_0103b84c_OFFSET 0x000000D8   /* was DAT_0103b814 (word at 0x0103B814); PC-relative offset: + 0x103b774 (the pc) = 0x0103B84C */
#define ADDRESS_OF_FUNCTION_0103b6ec_OFFSET 0xFFFFFF6C   /* was DAT_0103b818 (word at 0x0103B818); PC-relative offset: + 0x103b780 (the pc) = 0x0103B6EC */
#define ADDRESS_OF_FUNCTION_0103bce8_OFFSET 0x0000055C   /* was DAT_0103b81c (word at 0x0103B81C); PC-relative offset: + 0x103b78c (the pc) = 0x0103BCE8 */
#define ADDRESS_OF_FUNCTION_0103bd64_OFFSET 0x000005CC   /* was DAT_0103b820 (word at 0x0103B820); PC-relative offset: + 0x103b798 (the pc) = 0x0103BD64 */
#define ADDRESS_OF_FUNCTION_0103bcd8_OFFSET 0x00000534   /* was DAT_0103b824 (word at 0x0103B824); PC-relative offset: + 0x103b7a4 (the pc) = 0x0103BCD8 */
#define ADDRESS_OF_FUNCTION_0103b8cc_OFFSET 0x0000011C   /* was DAT_0103b828 (word at 0x0103B828); PC-relative offset: + 0x103b7b0 (the pc) = 0x0103B8CC */
#define ADDRESS_OF_FUNCTION_0103b924_OFFSET 0x00000168   /* was DAT_0103b82c (word at 0x0103B82C); PC-relative offset: + 0x103b7bc (the pc) = 0x0103B924 */
#define ADDRESS_OF_FUNCTION_0103b9a8_OFFSET 0x000001E0   /* was DAT_0103b830 (word at 0x0103B830); PC-relative offset: + 0x103b7c8 (the pc) = 0x0103B9A8 */
#define ADDRESS_OF_FUNCTION_0103baa8_OFFSET 0x000002D4   /* was DAT_0103b834 (word at 0x0103B834); PC-relative offset: + 0x103b7d4 (the pc) = 0x0103BAA8 */
#define ADDRESS_OF_FUNCTION_0103bba8_OFFSET 0x000003C8   /* was DAT_0103b838 (word at 0x0103B838); PC-relative offset: + 0x103b7e0 (the pc) = 0x0103BBA8 */
#define ADDRESS_OF_FUNCTION_0103bc40_OFFSET 0x00000454   /* was DAT_0103b83c (word at 0x0103B83C); PC-relative offset: + 0x103b7ec (the pc) = 0x0103BC40 */
#define ADDRESS_OF_FUNCTION_0103bde8_OFFSET 0x000005F0   /* was DAT_0103b840 (word at 0x0103B840); PC-relative offset: + 0x103b7f8 (the pc) = 0x0103BDE8 */
#define ADDRESS_OF_FUNCTION_0103be9c_OFFSET 0x00000698   /* was DAT_0103b844 (word at 0x0103B844); PC-relative offset: + 0x103b804 (the pc) = 0x0103BE9C */
#define ADDRESS_OF_FUNCTION_0103bf18_OFFSET 0x00000708   /* was DAT_0103b848 (word at 0x0103B848); PC-relative offset: + 0x103b810 (the pc) = 0x0103BF18 */
#define WORD_HEXADECIMAL_42652EE0 0x42652EE0   /* was DAT_0103c038 (word at 0x0103C038); value 0x42652EE0 (1113927392) */
#define ADDRESS_OF_FUNCTION_0103c118_OFFSET 0xFFFFFF90   /* was DAT_0103c21c (word at 0x0103C21C); PC-relative offset: + 0x103c188 (the pc) = 0x0103C118 */
#define ADDRESS_OF_FUNCTION_0103c6ec_OFFSET 0x00000558   /* was DAT_0103c220 (word at 0x0103C220); PC-relative offset: + 0x103c194 (the pc) = 0x0103C6EC */
#define ADDRESS_OF_FUNCTION_0103c03c_OFFSET 0xFFFFFE9C   /* was DAT_0103c224 (word at 0x0103C224); PC-relative offset: + 0x103c1a0 (the pc) = 0x0103C03C */
#define ADDRESS_OF_FUNCTION_0103c5e8_OFFSET 0x0000043C   /* was DAT_0103c228 (word at 0x0103C228); PC-relative offset: + 0x103c1ac (the pc) = 0x0103C5E8 */
#define ADDRESS_OF_FUNCTION_0103bfac_OFFSET 0xFFFFFDF4   /* was DAT_0103c22c (word at 0x0103C22C); PC-relative offset: + 0x103c1b8 (the pc) = 0x0103BFAC */
#define ADDRESS_OF_FUNCTION_0103c4e8_OFFSET 0x00000324   /* was DAT_0103c230 (word at 0x0103C230); PC-relative offset: + 0x103c1c4 (the pc) = 0x0103C4E8 */
#define ADDRESS_OF_FUNCTION_0103c784_OFFSET 0x000005B4   /* was DAT_0103c234 (word at 0x0103C234); PC-relative offset: + 0x103c1d0 (the pc) = 0x0103C784 */
#define ADDRESS_OF_FUNCTION_0103c450_OFFSET 0x00000274   /* was DAT_0103c238 (word at 0x0103C238); PC-relative offset: + 0x103c1dc (the pc) = 0x0103C450 */
#define ADDRESS_OF_FUNCTION_0103c350_OFFSET 0x00000168   /* was DAT_0103c23c (word at 0x0103C23C); PC-relative offset: + 0x103c1e8 (the pc) = 0x0103C350 */
#define ADDRESS_OF_FUNCTION_0103c250_OFFSET 0x0000005C   /* was DAT_0103c240 (word at 0x0103C240); PC-relative offset: + 0x103c1f4 (the pc) = 0x0103C250 */
#define ADDRESS_OF_FUNCTION_0103c094_OFFSET 0xFFFFFE94   /* was DAT_0103c244 (word at 0x0103C244); PC-relative offset: + 0x103c200 (the pc) = 0x0103C094 */
#define ADDRESS_OF_FUNCTION_0103bf28_OFFSET 0xFFFFFD1C   /* was DAT_0103c248 (word at 0x0103C248); PC-relative offset: + 0x103c20c (the pc) = 0x0103BF28 */
#define ADDRESS_OF_FUNCTION_0103c680_OFFSET 0x00000468   /* was DAT_0103c24c (word at 0x0103C24C); PC-relative offset: + 0x103c218 (the pc) = 0x0103C680 */
#define ADDRESS_OF_FUNCTION_0103c944_OFFSET 0x000000B0   /* was DAT_0103c8a4 (word at 0x0103C8A4); PC-relative offset: + 0x103c894 (the pc) = 0x0103C944 */
#define ADDRESS_OF_FUNCTION_0103c8ac_OFFSET 0x0000000C   /* was DAT_0103c8a8 (word at 0x0103C8A8); PC-relative offset: + 0x103c8a0 (the pc) = 0x0103C8AC */
#define ADDRESS_OF_FUNCTION_0103ca64_OFFSET 0x00000028   /* was DAT_0103ca58 (word at 0x0103CA58); PC-relative offset: + 0x103ca3c (the pc) = 0x0103CA64 */
#define ADDRESS_OF_FUNCTION_0103cb10_OFFSET 0x000000C8   /* was DAT_0103ca5c (word at 0x0103CA5C); PC-relative offset: + 0x103ca48 (the pc) = 0x0103CB10 */
#define ADDRESS_OF_FUNCTION_0103cbac_OFFSET 0x00000158   /* was DAT_0103ca60 (word at 0x0103CA60); PC-relative offset: + 0x103ca54 (the pc) = 0x0103CBAC */
#define ADDRESS_OF_FUNCTION_0103cd2c_OFFSET 0xFFFFFE64   /* was DAT_0103cf44 (word at 0x0103CF44); PC-relative offset: + 0x103cec8 (the pc) = 0x0103CD2C */
#define ADDRESS_OF_FUNCTION_0103cff0_OFFSET 0x0000011C   /* was DAT_0103cf48 (word at 0x0103CF48); PC-relative offset: + 0x103ced4 (the pc) = 0x0103CFF0 */
#define ADDRESS_OF_FUNCTION_0103cca8_OFFSET 0xFFFFFDC8   /* was DAT_0103cf4c (word at 0x0103CF4C); PC-relative offset: + 0x103cee0 (the pc) = 0x0103CCA8 */
#define ADDRESS_OF_FUNCTION_0103cf70_OFFSET 0x00000084   /* was DAT_0103cf50 (word at 0x0103CF50); PC-relative offset: + 0x103ceec (the pc) = 0x0103CF70 */
#define ADDRESS_OF_FUNCTION_0103cd14_OFFSET 0xFFFFFE1C   /* was DAT_0103cf54 (word at 0x0103CF54); PC-relative offset: + 0x103cef8 (the pc) = 0x0103CD14 */
#define ADDRESS_OF_FUNCTION_0103cfdc_OFFSET 0x000000D8   /* was DAT_0103cf58 (word at 0x0103CF58); PC-relative offset: + 0x103cf04 (the pc) = 0x0103CFDC */
#define ADDRESS_OF_FUNCTION_0103ce98_OFFSET 0xFFFFFF88   /* was DAT_0103cf5c (word at 0x0103CF5C); PC-relative offset: + 0x103cf10 (the pc) = 0x0103CE98 */
#define ADDRESS_OF_FUNCTION_0103cd98_OFFSET 0xFFFFFE7C   /* was DAT_0103cf60 (word at 0x0103CF60); PC-relative offset: + 0x103cf1c (the pc) = 0x0103CD98 */
#define ADDRESS_OF_FUNCTION_0103d05c_OFFSET 0x00000134   /* was DAT_0103cf64 (word at 0x0103CF64); PC-relative offset: + 0x103cf28 (the pc) = 0x0103D05C */
#define ADDRESS_OF_FUNCTION_0103ce14_OFFSET 0xFFFFFEE0   /* was DAT_0103cf68 (word at 0x0103CF68); PC-relative offset: + 0x103cf34 (the pc) = 0x0103CE14 */
#define ADDRESS_OF_FUNCTION_0103d0f0_OFFSET 0x000001B0   /* was DAT_0103cf6c (word at 0x0103CF6C); PC-relative offset: + 0x103cf40 (the pc) = 0x0103D0F0 */
#define ADDRESS_OF_FUNCTION_0103d1ec_OFFSET 0xFFFFFF10   /* was DAT_0103d304 (word at 0x0103D304); PC-relative offset: + 0x103d2dc (the pc) = 0x0103D1EC */
#define ADDRESS_OF_FUNCTION_0103d314_OFFSET 0x0000002C   /* was DAT_0103d308 (word at 0x0103D308); PC-relative offset: + 0x103d2e8 (the pc) = 0x0103D314 */
#define ADDRESS_OF_FUNCTION_0103d258_OFFSET 0xFFFFFF64   /* was DAT_0103d30c (word at 0x0103D30C); PC-relative offset: + 0x103d2f4 (the pc) = 0x0103D258 */
#define ADDRESS_OF_FUNCTION_0103d398_OFFSET 0x00000098   /* was DAT_0103d310 (word at 0x0103D310); PC-relative offset: + 0x103d300 (the pc) = 0x0103D398 */
#define WORD_HEXADECIMAL_04000088 0x04000088   /* was DAT_0103d588 (word at 0x0103D588); value 0x04000088 (67109000) */
#define WORD_HEXADECIMAL_FFE00000 0xFFE00000   /* was DAT_0103da40 (word at 0x0103DA40); value 0xFFE00000 (-2097152) */
#define WORD_HEXADECIMAL_10000011 0x10000011   /* was DAT_0103da44 (word at 0x0103DA44); value 0x10000011 (268435473) */
#define WORD_HEXADECIMAL_04000011 0x04000011   /* was DAT_0103da48 (word at 0x0103DA48); value 0x04000011 (67108881) */
#define WORD_HEXADECIMAL_04000012 0x04000012   /* was DAT_0103da4c (word at 0x0103DA4C); value 0x04000012 (67108882) */
#define WORD_HEXADECIMAL_7FF00000 0x7FF00000   /* was DAT_0103e100, DAT_0103e618 (word at 0x0103E100); value 0x7FF00000 (2146435072) */
#define WORD_HEXADECIMAL_08000014 0x08000014   /* was DAT_0103e104 (word at 0x0103E104); value 0x08000014 (134217748) */
#define WORD_HEXADECIMAL_04000014 0x04000014   /* was DAT_0103e108 (word at 0x0103E108); value 0x04000014 (67108884) */
#define WORD_HEXADECIMAL_04120019 0x04120019   /* was DAT_0103e188 (word at 0x0103E188); value 0x04120019 (68288537) */
#define WORD_HEXADECIMAL_040200C8 0x040200C8   /* was DAT_0103e22c (word at 0x0103E22C); value 0x040200C8 (67240136) */
#define WORD_HEXADECIMAL_04130019 0x04130019   /* was DAT_0103e2e8 (word at 0x0103E2E8); value 0x04130019 (68354073) */
#define WORD_HEXADECIMAL_04160019 0x04160019   /* was DAT_0103e368 (word at 0x0103E368); value 0x04160019 (68550681) */
#define WORD_HEXADECIMAL_07FF0000 0x07FF0000   /* was DAT_0103e614, DAT_0103e900 (word at 0x0103E614); value 0x07FF0000 (134152192) */
#define WORD_HEXADECIMAL_04000013 0x04000013   /* was DAT_0103e61c (word at 0x0103E61C); value 0x04000013 (67108883) */
#define WORD_HEXADECIMAL_04000015 0x04000015   /* was DAT_0103e904 (word at 0x0103E904); value 0x04000015 (67108885) */
#define WORD_HEXADECIMAL_04000017 0x04000017   /* was DAT_0103eae8 (word at 0x0103EAE8); value 0x04000017 (67108887) */
#define WORD_HEXADECIMAL_7FC00000 0x7FC00000   /* was DAT_0103ee7c (word at 0x0103EE7C); value 0x7FC00000 (2143289344) */
#define WORD_HEXADECIMAL_04000018 0x04000018   /* was DAT_0103eee4 (word at 0x0103EEE4); value 0x04000018 (67108888) */
#define WORD_HEXADECIMAL_04000004 0x04000004   /* was DAT_0103f420 (word at 0x0103F420); value 0x04000004 (67108868) */
#define WORD_HEXADECIMAL_08000004 0x08000004   /* was DAT_0103f424 (word at 0x0103F424); value 0x08000004 (134217732) */
#define WORD_HEXADECIMAL_04120009 0x04120009   /* was DAT_0103f48c (word at 0x0103F48C); value 0x04120009 (68288521) */
#define WORD_HEXADECIMAL_04020048 0x04020048   /* was DAT_0103f4f4 (word at 0x0103F4F4); value 0x04020048 (67240008) */
#define WORD_HEXADECIMAL_04130009 0x04130009   /* was DAT_0103f598 (word at 0x0103F598); value 0x04130009 (68354057) */
#define WORD_HEXADECIMAL_04160009 0x04160009   /* was DAT_0103f600 (word at 0x0103F600); value 0x04160009 (68550665) */
#define WORD_HEXADECIMAL_FE3FE0E0 0xFE3FE0E0   /* was DAT_0103f920 (word at 0x0103F920); value 0xFE3FE0E0 (-29368096) */

#define BAD_PARAMETER_ERROR_AS_POINTER ((void *)14)   /* was &DAT_0000000e: not an object, Ghidra's view of
                                                        the constant 14 (EBADPARM) loaded into a register
                                                        that is also used as a pointer; returned when the
                                                        output pointer argument is NULL */
#define SIX_AS_BYTE_POINTER ((byte *)6)               /* was &DAT_00000006: not an object, the constant 6
                                                        (the starting bit shift of a 2-bit pixel unpacking
                                                        loop) in a register Ghidra typed as byte * */

/* ---- Double-precision literal pairs (low word, high word), named by value ----------------
   The first naming pass missed these pairs and named each word on its own. */
#define ZERO_DOUBLE_LOW_WORD 0x00000000   /* was DAT_010006f4, DAT_010007fc, DAT_01000870, DAT_01000914, DAT_01001360, DAT_010019c0, DAT_01008444, DAT_0101f3d8, DAT_0102eda4 (word at 0x010006F4); with the word at 0x010006F8: the double 0.0 = 0x0000000000000000 */
#define ZERO_DOUBLE_HIGH_WORD 0x00000000   /* was DAT_010006f8, DAT_01000800, DAT_01000874, DAT_01000918, DAT_01001364, DAT_010019c4, DAT_01008448, DAT_0101f3dc, DAT_0102eda8 (word at 0x010006F8); with the word at 0x010006F4: the double 0.0 = 0x0000000000000000 */
#define ONE_DOUBLE_LOW_WORD 0x00000000   /* was DAT_01000efc, DAT_0100199c (word at 0x01000EFC); with the word at 0x01000F00: the double 1.0 = 0x3FF0000000000000 */
#define ONE_DOUBLE_HIGH_WORD 0x3FF00000   /* was DAT_01000f00, DAT_010019a0 (word at 0x01000F00); with the word at 0x01000EFC: the double 1.0 = 0x3FF0000000000000 */
#define HALF_DOUBLE_LOW_WORD 0x00000000   /* was DAT_01000f0c, DAT_010013a0, DAT_010015e4 (word at 0x01000F0C); with the word at 0x01000F10: the double 0.5 = 0x3FE0000000000000 */
#define HALF_DOUBLE_HIGH_WORD 0x3FE00000   /* was DAT_01000f10, DAT_010013a4, DAT_010015e8 (word at 0x01000F10); with the word at 0x01000F0C: the double 0.5 = 0x3FE0000000000000 */
#define DOUBLE_0_POINT_28125_LOW_WORD 0x00000000   /* was DAT_01000f14 (word at 0x01000F14); with the word at 0x01000F18: the double 0.28125 = 0x3FD2000000000000 */
#define DOUBLE_0_POINT_28125_HIGH_WORD 0x3FD20000   /* was DAT_01000f18 (word at 0x01000F18); with the word at 0x01000F14: the double 0.28125 = 0x3FD2000000000000 */
#define DOUBLE_1_POINT_801439851_TIMES_TEN_TO_THE_16_LOW_WORD 0x00000000   /* was DAT_01000f8c (word at 0x01000F8C); with the word at 0x01000F90: the double 1.8014398509481984e+16 = 0x4350000000000000 */
#define DOUBLE_1_POINT_801439851_TIMES_TEN_TO_THE_16_HIGH_WORD 0x43500000   /* was DAT_01000f90 (word at 0x01000F90); with the word at 0x01000F8C: the double 1.8014398509481984e+16 = 0x4350000000000000 */
#define DOUBLE_2_POINT_356194019_LOW_WORD 0x3FE921FB   /* was DAT_01001368 (word at 0x01001368); with the word at 0x0100136C: the double 2.356194018652102 = 0x4002D97C3FE921FB */
#define DOUBLE_2_POINT_356194019_HIGH_WORD 0x4002D97C   /* was DAT_0100136c (word at 0x0100136C); with the word at 0x01001368: the double 2.356194018652102 = 0x4002D97C3FE921FB */
#define DOUBLE_1_POINT_570796327_LOW_WORD 0x54400000   /* was DAT_01001370 (word at 0x01001370); with the word at 0x01001374: the double 1.5707963267341256 = 0x3FF921FB54400000 */
#define DOUBLE_1_POINT_570796327_HIGH_WORD 0x3FF921FB   /* was DAT_01001374 (word at 0x01001374); with the word at 0x01001370: the double 1.5707963267341256 = 0x3FF921FB54400000 */
#define DOUBLE_6_POINT_077100507_TIMES_TEN_TO_THE_MINUS_11_LOW_WORD 0x1A626331   /* was DAT_01001384 (word at 0x01001384); with the word at 0x01001388: the double 6.077100506506192e-11 = 0x3DD0B4611A626331 */
#define DOUBLE_6_POINT_077100507_TIMES_TEN_TO_THE_MINUS_11_HIGH_WORD 0x3DD0B461   /* was DAT_01001388 (word at 0x01001388); with the word at 0x01001384: the double 6.077100506506192e-11 = 0x3DD0B4611A626331 */
#define DOUBLE_6_POINT_077100506_TIMES_TEN_TO_THE_MINUS_11_LOW_WORD 0x1A600000   /* was DAT_0100138c (word at 0x0100138C); with the word at 0x01001390: the double 6.077100506303966e-11 = 0x3DD0B4611A600000 */
#define DOUBLE_6_POINT_077100506_TIMES_TEN_TO_THE_MINUS_11_HIGH_WORD 0x3DD0B461   /* was DAT_01001390 (word at 0x01001390); with the word at 0x0100138C: the double 6.077100506303966e-11 = 0x3DD0B4611A600000 */
#define TWO_OVER_PI_DOUBLE_LOW_WORD 0x6DC9C883   /* was DAT_01001398 (word at 0x01001398); with the word at 0x0100139C: the double 0.6366197723675814 = 0x3FE45F306DC9C883 */
#define TWO_OVER_PI_DOUBLE_HIGH_WORD 0x3FE45F30   /* was DAT_0100139c (word at 0x0100139C); with the word at 0x01001398: the double 0.6366197723675814 = 0x3FE45F306DC9C883 */
#define DOUBLE_0_POINT_4260419011_LOW_WORD 0x40000000   /* was DAT_010013b4 (word at 0x010013B4); with the word at 0x010013B8: the double 0.4260419011116028 = 0x3FDB444540000000 */
#define DOUBLE_0_POINT_4260419011_HIGH_WORD 0x3FDB4445   /* was DAT_010013b8 (word at 0x010013B8); with the word at 0x010013B4: the double 0.4260419011116028 = 0x3FDB444540000000 */
#define DOUBLE_MINUS_1_POINT_731608246_TIMES_TEN_TO_THE_MINUS_9_LOW_WORD 0x90000000   /* was DAT_010013bc (word at 0x010013BC); with the word at 0x010013C0: the double -1.7316082456808601e-09 = 0xBE1DBFB190000000 */
#define DOUBLE_MINUS_1_POINT_731608246_TIMES_TEN_TO_THE_MINUS_9_HIGH_WORD 0xBE1DBFB1   /* was DAT_010013c0 (word at 0x010013C0); with the word at 0x010013BC: the double -1.7316082456808601e-09 = 0xBE1DBFB190000000 */
#define DOUBLE_2_POINT_676900202_LOW_WORD 0xA740A5A7   /* was DAT_010013c4 (word at 0x010013C4); with the word at 0x010013C8: the double 2.6769002024272655 = 0x40056A4AA740A5A7 */
#define DOUBLE_2_POINT_676900202_HIGH_WORD 0x40056A4A   /* was DAT_010013c8 (word at 0x010013C8); with the word at 0x010013C4: the double 2.6769002024272655 = 0x40056A4AA740A5A7 */
#define EIGHT_DOUBLE_LOW_WORD 0x00000000   /* was DAT_01001454 (word at 0x01001454); with the word at 0x01001458: the double 8.0 = 0x4020000000000000 */
#define EIGHT_DOUBLE_HIGH_WORD 0x40200000   /* was DAT_01001458 (word at 0x01001458); with the word at 0x01001454: the double 8.0 = 0x4020000000000000 */
#define NINE_DOUBLE_LOW_WORD 0x00000000   /* was DAT_0100145c (word at 0x0100145C); with the word at 0x01001460: the double 9.0 = 0x4022000000000000 */
#define NINE_DOUBLE_HIGH_WORD 0x40220000   /* was DAT_01001460 (word at 0x01001460); with the word at 0x0100145C: the double 9.0 = 0x4022000000000000 */
#define DOUBLE_0_POINT_6692250506_LOW_WORD 0xA740A5A7   /* was DAT_01001464 (word at 0x01001464); with the word at 0x01001468: the double 0.6692250506068164 = 0x3FE56A4AA740A5A7 */
#define DOUBLE_0_POINT_6692250506_HIGH_WORD 0x3FE56A4A   /* was DAT_01001468 (word at 0x01001468); with the word at 0x01001464: the double 0.6692250506068164 = 0x3FE56A4AA740A5A7 */
#define DOUBLE_0_POINT_4260418994_LOW_WORD 0x3E2404E7   /* was DAT_0100146c (word at 0x0100146C); with the word at 0x01001470: the double 0.42604189937999454 = 0x3FDB44453E2404E7 */
#define DOUBLE_0_POINT_4260418994_HIGH_WORD 0x3FDB4445   /* was DAT_01001470 (word at 0x01001470); with the word at 0x0100146C: the double 0.42604189937999454 = 0x3FDB44453E2404E7 */
#define DOUBLE_MINUS_0_POINT_1666666667_LOW_WORD 0x55555549   /* was DAT_010015dc (word at 0x010015DC); with the word at 0x010015E0: the double -0.16666666666666632 = 0xBFC5555555555549 */
#define DOUBLE_MINUS_0_POINT_1666666667_HIGH_WORD 0xBFC55555   /* was DAT_010015e0 (word at 0x010015E0); with the word at 0x010015DC: the double -0.16666666666666632 = 0xBFC5555555555549 */
#define DOUBLE_MINUS_ONE_LOW_WORD 0x00000000   /* was DAT_010019a4 (word at 0x010019A4); with the word at 0x010019A8: the double -1.0 = 0xBFF0000000000000 */
#define DOUBLE_MINUS_ONE_HIGH_WORD 0xBFF00000   /* was DAT_010019a8 (word at 0x010019A8); with the word at 0x010019A4: the double -1.0 = 0xBFF0000000000000 */
#define QUARTER_PI_DOUBLE_LOW_WORD 0x54442D18   /* was DAT_010019b0 (word at 0x010019B0); with the word at 0x010019B4: the double 0.7853981633974483 = 0x3FE921FB54442D18 */
#define QUARTER_PI_DOUBLE_HIGH_WORD 0x3FE921FB   /* was DAT_010019b4 (word at 0x010019B4); with the word at 0x010019B0: the double 0.7853981633974483 = 0x3FE921FB54442D18 */
#define DOUBLE_3_POINT_061616998_TIMES_TEN_TO_THE_MINUS_17_LOW_WORD 0x33145C07   /* was DAT_010019b8 (word at 0x010019B8); with the word at 0x010019BC: the double 3.061616997868383e-17 = 0x3C81A62633145C07 */
#define DOUBLE_3_POINT_061616998_TIMES_TEN_TO_THE_MINUS_17_HIGH_WORD 0x3C81A626   /* was DAT_010019bc (word at 0x010019BC); with the word at 0x010019B8: the double 3.061616997868383e-17 = 0x3C81A62633145C07 */
#define DOUBLE_0_POINT_3333333333_LOW_WORD 0x55555563   /* was DAT_010019d0 (word at 0x010019D0); with the word at 0x010019D4: the double 0.3333333333333341 = 0x3FD5555555555563 */
#define DOUBLE_0_POINT_3333333333_HIGH_WORD 0x3FD55555   /* was DAT_010019d4 (word at 0x010019D4); with the word at 0x010019D0: the double 0.3333333333333341 = 0x3FD5555555555563 */
#define TWO_DOUBLE_LOW_WORD 0x00000000   /* was DAT_010019d8 (word at 0x010019D8); with the word at 0x010019DC: the double 2.0 = 0x4000000000000000 */
#define TWO_DOUBLE_HIGH_WORD 0x40000000   /* was DAT_010019dc (word at 0x010019DC); with the word at 0x010019D8: the double 2.0 = 0x4000000000000000 */
#define DOUBLE_MINUS_1_POINT_038205979_TIMES_TEN_TO_THE_34_LOW_WORD 0x46FFFE00   /* was DAT_01005eb0 (word at 0x01005EB0); with the word at 0x01005EB4: the double -1.038205978920834e+34 = 0xC6FFFE0046FFFE00 */
#define DOUBLE_MINUS_1_POINT_038205979_TIMES_TEN_TO_THE_34_HIGH_WORD 0xC6FFFE00   /* was DAT_01005eb4 (word at 0x01005EB4); with the word at 0x01005EB0: the double -1.038205978920834e+34 = 0xC6FFFE0046FFFE00 */
#define DOUBLE_2_POINT_658456541_TIMES_TEN_TO_THE_36_LOW_WORD 0x377BA882   /* was DAT_010146c0 (word at 0x010146C0); with the word at 0x010146C4: the double 2.658456541047245e+36 = 0x47800000377BA882 */
#define DOUBLE_2_POINT_658456541_TIMES_TEN_TO_THE_36_HIGH_WORD 0x47800000   /* was DAT_010146c4 (word at 0x010146C4); with the word at 0x010146C0: the double 2.658456541047245e+36 = 0x47800000377BA882 */
#define DOUBLE_1_POINT_342271274_TIMES_TEN_TO_THE_MINUS_17_LOW_WORD 0x0019660D   /* was DAT_010181d8, DAT_0101dbf0 (word at 0x010181D8); with the word at 0x010181DC: the double 1.342271274202179e-17 = 0x3C6EF35F0019660D */
#define DOUBLE_1_POINT_342271274_TIMES_TEN_TO_THE_MINUS_17_HIGH_WORD 0x3C6EF35F   /* was DAT_010181dc, DAT_0101dbf4 (word at 0x010181DC); with the word at 0x010181D8: the double 1.342271274202179e-17 = 0x3C6EF35F0019660D */
#define DOUBLE_1_POINT_03820598_TIMES_TEN_TO_THE_34_LOW_WORD 0x47800000   /* was DAT_010183a8 (word at 0x010183A8); with the word at 0x010183AC: the double 1.0382059798880336e+34 = 0x46FFFE0047800000 */
#define DOUBLE_1_POINT_03820598_TIMES_TEN_TO_THE_34_HIGH_WORD 0x46FFFE00   /* was DAT_010183ac (word at 0x010183AC); with the word at 0x010183A8: the double 1.0382059798880336e+34 = 0x46FFFE0047800000 */
#define DOUBLE_2_POINT_658456546_TIMES_TEN_TO_THE_36_LOW_WORD 0x37FBA882   /* was DAT_01024694 (word at 0x01024694); with the word at 0x01024698: the double 2.6584565459990054e+36 = 0x4780000037FBA882 */
#define DOUBLE_2_POINT_658456546_TIMES_TEN_TO_THE_36_HIGH_WORD 0x47800000   /* was DAT_01024698 (word at 0x01024698); with the word at 0x01024694: the double 2.6584565459990054e+36 = 0x4780000037FBA882 */
#define DOUBLE_0_POINT_0963475405_LOW_WORD 0x7F7FFFFF   /* was DAT_0102f3bc (word at 0x0102F3BC); with the word at 0x0102F3C0: the double 0.0963475405005738 = 0x3FB8AA3B7F7FFFFF */
#define DOUBLE_0_POINT_0963475405_HIGH_WORD 0x3FB8AA3B   /* was DAT_0102f3c0 (word at 0x0102F3C0); with the word at 0x0102F3BC: the double 0.0963475405005738 = 0x3FB8AA3B7F7FFFFF */
#define DOUBLE_5_POINT_036114712_TIMES_TEN_TO_THE_23_LOW_WORD 0x48A005A5   /* was DAT_0102f3cc (word at 0x0102F3CC); with the word at 0x0102F3D0: the double 5.036114711907845e+23 = 0x44DAA93548A005A5 */
#define DOUBLE_5_POINT_036114712_TIMES_TEN_TO_THE_23_HIGH_WORD 0x44DAA935   /* was DAT_0102f3d0 (word at 0x0102F3D0); with the word at 0x0102F3CC: the double 5.036114711907845e+23 = 0x44DAA93548A005A5 */
#define DOUBLE_NOT_A_NUMBER_LOW_WORD 0x00000000   /* was DAT_0103ee74 (word at 0x0103EE74); with the word at 0x0103EE78: the double nan = 0x7FF8000000000000 */
#define DOUBLE_NOT_A_NUMBER_HIGH_WORD 0x7FF80000   /* was DAT_0103ee78 (word at 0x0103EE78); with the word at 0x0103EE74: the double nan = 0x7FF8000000000000 */

#endif /* SWV21BREW_H */
