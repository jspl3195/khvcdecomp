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
typedef void           code;   /* Ghidra: untyped code pointer target */

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

#endif /* SWV21BREW_H */
