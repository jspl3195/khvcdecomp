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
typedef unsigned long long undefined8;
typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef unsigned long long ulonglong;
typedef long long longlong;
typedef void           code;   /* Ghidra: untyped code pointer target */

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
undefined4 FUN_00100028(void);
void FUN_00100104(int param_1);
undefined4 * FUN_00100110(undefined4 *param_1,uint param_2);
undefined8 FUN_00100168(uint *param_1,uint *param_2,uint param_3,uint param_4);
undefined8 FUN_0010021c(byte *param_1,byte *param_2,uint param_3,undefined4 param_4);
ulonglong FUN_00100288(uint param_1,uint param_2);
int FUN_0010035c(uint param_1,uint param_2);
undefined4 FUN_0010041c(int param_1,uint param_2);
undefined4 FUN_001007f4(int param_1,uint param_2);
undefined4 FUN_001008d0(int param_1,uint param_2);
undefined4 FUN_001009b8(uint param_1,uint param_2,undefined4 param_3,undefined4 param_4);
void FUN_00100a38(undefined4 param_1);
undefined4 FUN_00100a58(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4);
uint FUN_00100c2c(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
int FUN_00100d88(undefined4 param_1,uint param_2,undefined8 *param_3);
undefined4 FUN_00101268(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4,int param_5);
undefined8 FUN_001013e0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, uint param_5);
void FUN_00101440(void);
undefined4 FUN_00101458(int param_1,char *param_2);
undefined8 FUN_00101638(void);
undefined4 FUN_00101ad8(int *param_1,int param_2);
void FUN_001051d4(int param_1,int param_2);
void FUN_00105224(int *param_1,int param_2,undefined4 param_3,undefined4 param_4);
int FUN_001052e0(int param_1,undefined4 param_2,int param_3,int param_4,int param_5,int param_6, undefined4 param_7,undefined4 param_8,int param_9);
void FUN_001053a8(undefined4 param_1,undefined4 param_2,int param_3,int param_4,int param_5, int param_6,undefined4 param_7,int param_8,int param_9,int param_10,int param_11, int param_12,int param_13);
int FUN_001054d8(int param_1,int param_2,int param_3);
void FUN_00105538(int param_1,undefined4 param_2,int param_3);
void FUN_001055c4(int param_1,undefined4 param_2,int param_3,undefined4 param_4,int param_5);
void FUN_001056d0(int *param_1,int param_2);
int FUN_001056ec(int param_1,int param_2,int param_3);
void FUN_001056f4(int param_1);
void FUN_00105734(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4);
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
void FUN_00107d24(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_00107e48(undefined4 param_1,int param_2);
int FUN_00107ea4(int *param_1,int param_2,undefined4 param_3,int param_4);
int FUN_00107ec4(int param_1,int param_2);
void * FUN_00107ecc(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
int FUN_00107f88(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
ulonglong FUN_00107fd0(int param_1,int param_2,int param_3);
undefined4 FUN_00107fec(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
int FUN_001080ac(int param_1);
int FUN_001080c8(int *param_1,int param_2);
void FUN_0010810c(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5, undefined4 param_6);
void FUN_001082e0(int param_1,undefined4 param_2,int param_3,undefined4 param_4,undefined4 param_5, undefined4 param_6,undefined4 param_7,int param_8);
undefined4 FUN_001083d8(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
undefined4 FUN_00108414(int param_1,undefined4 param_2,int param_3);
bool FUN_001084e4(undefined4 param_1,undefined4 param_2,int param_3);
undefined4 FUN_00108524(int param_1,undefined4 param_2,int param_3,undefined4 param_4);
int FUN_0010873c(int *param_1,undefined4 param_2,int param_3,undefined4 param_4);
void FUN_00108840(int param_1,short param_2);
void FUN_0010888c(int *param_1,void *param_2,int *param_3,void *param_4,void *param_5);
bool FUN_00108e8c(int param_1);
bool FUN_00108ed8(int param_1);
void FUN_00108f28(int param_1,int param_2);
void FUN_00108fa0(undefined4 param_1);
void FUN_00108fcc(int *param_1,int param_2);
void FUN_001090b8(int param_1,int *param_2,undefined4 param_3,undefined4 param_4);
int FUN_001090fc(int *param_1,int param_2,int param_3);
void FUN_001091fc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_001092c0(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
undefined4 FUN_00109308(int param_1,undefined4 param_2,int param_3);
void FUN_00109368(int param_1);
void FUN_00109380(int *param_1,int param_2);
void thunk_FUN_0011e154(int param_1);
undefined4 FUN_001093f8(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5 );
void FUN_00109534(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5);
void FUN_0010955c(int param_1,int param_2,int param_3);
void FUN_00109750(int param_1,undefined4 param_2);
int FUN_00109780(int *param_1,undefined4 param_2,int param_3,int *param_4);
void FUN_001098d8(int param_1,int param_2,int *param_3,undefined4 param_4);
void FUN_00109940(int param_1,int param_2);
void FUN_00109a10(int param_1,int param_2,int param_3,undefined4 param_4);
void FUN_00109b4c(int param_1,int param_2,int param_3);
void FUN_00109f00(int param_1);
void FUN_00109f48(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_00109ff8(int param_1);
void FUN_0010a03c(int param_1,undefined4 param_2);
void FUN_0010a080(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_0010a0d0(int param_1);
void FUN_0010a124(int param_1);
int FUN_0010a12c(undefined4 param_1,undefined4 param_2,byte *param_3);
undefined8 FUN_0010a214(int param_1,undefined4 param_2);
void FUN_0010a3e8(undefined4 param_1,int *param_2,uint param_3,int param_4);
void FUN_0010a46c(undefined4 param_1,int *param_2,undefined4 param_3,uint param_4);
void FUN_0010a498(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
int * FUN_0010a528(int *param_1,int param_2,int param_3,int param_4);
int * FUN_0010a5d8(int *param_1,undefined4 param_2,int *param_3,int *param_4);
int * FUN_0010aa8c(int *param_1,int *param_2);
int * FUN_0010ac6c(int *param_1,int param_2);
undefined4 * FUN_0010af3c(undefined4 *param_1,undefined4 param_2,undefined4 param_3);
void FUN_0010afc4(undefined4 *param_1);
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
void FUN_0010ba08(undefined4 *param_1,undefined4 param_2);
undefined4 * FUN_0010bb2c(undefined4 *param_1,int param_2,undefined4 param_3);
int * FUN_0010bba0(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,int param_6,int param_7,int param_8,undefined1 param_9);
int * FUN_0010bd7c(int *param_1,int *param_2,undefined1 param_3);
int * FUN_0010be14(int *param_1);
undefined4 * FUN_0010be6c(undefined4 *param_1,int param_2,undefined4 param_3);
undefined8 FUN_0010bec4(int *param_1,int param_2,int param_3,int param_4);
int * FUN_0010c168(int *param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4, undefined2 param_5,int param_6);
undefined4 * FUN_0010c218(undefined4 *param_1,undefined4 *param_2);
void FUN_0010c2a8(int *param_1,int param_2);
void FUN_0010c2c4(int *param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_0010c3f8(int param_1,int param_2);
void FUN_0010c598(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_0010c620(int param_1,int param_2);
void FUN_0010c66c(int param_1,int param_2);
void FUN_0010c6b4(int *param_1,int param_2);
void FUN_0010c720(int *param_1,int param_2);
void FUN_0010c73c(int param_1,int param_2);
void FUN_0010c790(int param_1,int param_2);
void FUN_0010c800(int param_1,int param_2);
void FUN_0010c8b8(int param_1,int param_2);
void FUN_0010c92c(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_0010c9dc(int param_1,int param_2);
void FUN_0010ca1c(int param_1,int param_2);
void FUN_0010cab0(int param_1,int param_2);
void FUN_0010cc9c(int param_1,int param_2);
void FUN_0010cd2c(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_0010cda4(int param_1,int param_2);
void FUN_0010cdd8(int param_1,int param_2);
void FUN_0010ce08(undefined4 *param_1,int param_2);
void FUN_0010cee4(int param_1,int param_2);
void FUN_0010cfc4(int param_1,int param_2);
void FUN_0010d074(int param_1);
void FUN_0010d18c(int param_1,int param_2);
void FUN_0010d1e0(int param_1,int param_2,void *param_3);
undefined4 FUN_0010d2fc(int param_1);
undefined4 FUN_0010d354(int param_1);
void FUN_0010d3a4(int param_1,undefined4 param_2);
undefined4 FUN_0010d4dc(undefined4 param_1,undefined4 param_2);
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
void FUN_0010e9bc(int param_1);
void FUN_0010ea00(int param_1);
void FUN_0010ea64(int param_1);
undefined4 FUN_0010eb74(int param_1,int param_2);
void FUN_0010ecb8(int param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4);
uint FUN_0010ed40(void);
void FUN_0010ed54(int param_1,int param_2,undefined4 param_3);
void FUN_0010edec(int param_1);
int FUN_0010eefc(undefined4 param_1,int param_2,int *param_3,undefined4 param_4);
undefined4 FUN_0010efd4(undefined4 param_1,undefined4 param_2,int param_3,int param_4);
int FUN_0010f058(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_0010f244(int *param_1,undefined4 *param_2);
bool FUN_0010f2cc(int param_1);
undefined8 FUN_0010f2e8(int param_1,uint param_2,undefined4 param_3,uint param_4,undefined4 param_5, undefined4 param_6,uint param_7);
void FUN_0010f4d0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,uint param_6);
void FUN_0010f880(int param_1);
void FUN_0010f8e8(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_0010f9a4(int param_1);
bool FUN_0010fa50(int param_1,int param_2,int param_3);
int FUN_0010faa8(int param_1,undefined4 param_2);
void FUN_0010fb90(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_0010fbf4(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,int param_6,int param_7,undefined4 param_8,uint param_9, undefined4 param_10);
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
bool FUN_00112a98(int param_1,undefined4 param_2,int param_3,undefined4 param_4);
void FUN_00112b4c(int param_1);
int FUN_00112c18(int param_1);
void FUN_00112c44(int *param_1);
undefined4 FUN_00112c9c(int param_1,int param_2);
undefined8 FUN_00112cdc(void);
int FUN_00112cfc(int param_1);
int FUN_00112d28(int param_1);
int FUN_00112d54(int param_1);
undefined4 FUN_00112dbc(int param_1,int param_2);
undefined4 FUN_00112e20(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
undefined8 FUN_00112e84(int param_1,undefined4 param_2);
void FUN_00113030(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5);
void FUN_0011316c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5, undefined4 param_6,undefined4 param_7,undefined4 param_8,int param_9, undefined4 param_10,undefined4 param_11,undefined1 param_12,undefined1 param_13, undefined1 param_14,undefined4 param_15,undefined4 param_16,undefined4 param_17);
void FUN_001132a8(int param_1);
void FUN_00113340(int param_1);
undefined8 FUN_00113374(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5);
void FUN_00113474(void);
void FUN_00113490(undefined4 *param_1,int param_2);
void FUN_00113524(undefined4 *param_1,int param_2);
undefined4 FUN_001135b8(int param_1,int param_2);
void FUN_001135dc(int param_1,undefined4 param_2,undefined4 param_3);
uint FUN_00113654(undefined4 param_1,int param_2);
undefined4 FUN_001136c8(int param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4, undefined4 *param_5,undefined4 param_6);
undefined4 FUN_00113784(int param_1);
int FUN_001137a4(int param_1,int param_2);
uint FUN_001137d4(undefined4 param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4);
uint FUN_00113820(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_0011386c(uint param_1,int param_2);
void FUN_00113cc4(undefined4 *param_1,int param_2);
undefined1 FUN_00113cd4(int param_1,int param_2);
int FUN_00113cfc(undefined4 param_1,int param_2);
int FUN_00113da4(int *param_1,int param_2,int param_3,int param_4,int param_5,undefined4 param_6);
undefined4 FUN_00114120(int param_1,undefined4 param_2,undefined4 *param_3,undefined4 *param_4);
undefined1 FUN_00114198(int param_1,undefined4 param_2);
undefined1 FUN_001141f4(int param_1,int param_2);
int * FUN_0011421c(int *param_1,undefined4 param_2,undefined4 *param_3);
undefined4 FUN_00114240(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 *param_6,int param_7,undefined4 param_8,int param_9);
void FUN_0011442c(undefined4 param_1,undefined4 *param_2);
void FUN_0011448c(undefined4 param_1,int *param_2,undefined4 param_3,undefined4 *param_4);
void FUN_00114520(undefined4 param_1,int *param_2,undefined4 param_3,undefined4 *param_4);
void FUN_001145b4(int param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4);
void FUN_00114610(void);
undefined4 FUN_00114638(int param_1);
int FUN_001146f0(int param_1,undefined4 param_2);
undefined4 FUN_00114750(int param_1);
void FUN_00114774(int *param_1,undefined4 param_2,undefined4 param_3);
void FUN_001147ec(undefined4 *param_1,int param_2,int *param_3);
undefined4 FUN_00114898(int param_1);
undefined4 FUN_001148a0(int param_1);
void FUN_001148a8(int param_1,int param_2);
void FUN_001148c8(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
bool FUN_00114910(int param_1);
void FUN_0011492c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_0011498c(int param_1,uint param_2,undefined4 param_3,undefined4 param_4);
void FUN_00114a1c(int param_1,undefined4 param_2);
undefined8 FUN_00114a94(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5 ,undefined4 param_6,undefined4 param_7);
undefined4 FUN_00114b48(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5 ,undefined4 param_6,undefined4 param_7);
void FUN_00114c00(int param_1,undefined4 param_2,undefined4 param_3,int param_4);
void FUN_001150d0(int param_1,int *param_2);
void FUN_00115118(undefined4 *param_1,undefined4 param_2,undefined4 param_3,int param_4);
void FUN_001174ac(int param_1,undefined4 param_2);
void FUN_00117d30(int param_1,int *param_2,undefined4 param_3,int ****param_4);
void FUN_00117dd8(int param_1);
undefined8 FUN_001180c4(int param_1,undefined4 param_2,int param_3);
void FUN_00118318(int param_1);
void FUN_00118640(int param_1,int *param_2,undefined4 param_3,undefined4 param_4);
void FUN_0011868c(int param_1,undefined4 param_2,undefined4 param_3,int param_4);
void FUN_00118910(int param_1,undefined4 param_2,undefined4 param_3,int param_4);
void FUN_00118ed8(undefined4 *param_1,int *param_2,undefined4 param_3);
void FUN_001195f8(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_00119a28(int param_1,int *param_2);
undefined4 FUN_00119abc(int param_1);
undefined8 FUN_00119b0c(undefined4 param_1,int param_2,undefined4 param_3);
undefined8 FUN_00119c10(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5 ,undefined4 param_6,undefined4 param_7);
undefined8 FUN_00119c60(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
undefined4 FUN_00119ce0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5 ,undefined4 param_6);
bool FUN_00119d58(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6);
void FUN_0011a2f4(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_0011a3ec(int param_1,int param_2,undefined4 param_3);
void FUN_0011a4d8(int param_1,int param_2);
void FUN_0011a7dc(int param_1,int param_2);
void FUN_0011aad0(int param_1,int param_2);
void FUN_0011ab60(int param_1);
undefined8 FUN_0011abc4(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
uint FUN_0011add0(uint param_1,int param_2);
undefined4 FUN_0011ae04(int param_1,undefined4 param_2,int *param_3,int param_4,int param_5);
void FUN_0011b044(int param_1,undefined4 param_2,int param_3,undefined4 param_4,int param_5, undefined4 *param_6);
bool FUN_0011b0cc(int param_1,undefined4 param_2,undefined4 param_3,int *param_4);
undefined4 FUN_0011b178(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
undefined8 FUN_0011b518(int param_1,int param_2,undefined4 param_3,int *param_4);
undefined4 FUN_0011b5f0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_0011b6f0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_0011b890(int param_1,int *param_2,undefined4 param_3,undefined4 param_4);
undefined4 FUN_0011ba0c(int param_1,undefined4 param_2);
void FUN_0011bb00(undefined4 *param_1,int param_2);
void FUN_0011bb58(int param_1,int param_2,int param_3);
int FUN_0011bb9c(int param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4);
undefined8 FUN_0011c330(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_0011c708(int param_1,int param_2,int param_3);
bool FUN_0011c860(int param_1,int param_2,undefined4 param_3);
void FUN_0011ca70(void);
void FUN_0011ca8c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5);
void FUN_0011cb34(undefined4 param_1,undefined4 *param_2);
void FUN_0011cbc4(int param_1,int param_2,int param_3);
void FUN_0011cc14(int param_1,int param_2,int param_3);
undefined4 FUN_0011cc64(int param_1,int param_2,int param_3,undefined4 param_4);
undefined8 FUN_0011ceac(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_0011cfdc(int param_1,undefined4 param_2,int param_3,undefined4 param_4);
void FUN_0011d040(int param_1,undefined4 param_2,void *param_3,int param_4);
void FUN_0011d104(int param_1,int param_2,int param_3);
int FUN_0011d168(int param_1,undefined4 param_2,undefined4 param_3);
void FUN_0011d28c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
undefined8 FUN_0011d3ec(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_0011d6cc(int param_1,int param_2);
int FUN_0011daac(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
uint FUN_0011dc9c(undefined4 param_1,int param_2,int *param_3,undefined4 param_4);
undefined4 FUN_0011dce8(undefined4 param_1,int param_2,int *param_3);
undefined4 FUN_0011dd34(undefined4 param_1,int param_2,int *param_3);
int FUN_0011dd80(undefined4 param_1,int param_2,int *param_3);
void FUN_0011de04(int param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4);
void FUN_0011de64(int param_1);
void FUN_0011de70(int param_1);
void FUN_0011dedc(int param_1);
void FUN_0011df14(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_0011e010(int param_1);
void FUN_0011e07c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_0011e0b4(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_0011e0fc(int param_1);
void FUN_0011e154(int param_1);
undefined4 FUN_0011e250(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
undefined4 FUN_0011e300(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_0011e36c(int param_1);
void FUN_0011e3c0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_0011e530(int param_1,undefined4 param_2,undefined4 param_3);
bool FUN_0011e574(int param_1,undefined4 param_2,undefined4 param_3,int *param_4);
undefined4 FUN_0011e6b8(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
undefined4 FUN_0011ea18(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
undefined4 FUN_0011ead4(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
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
void FUN_0011fc80(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_0011fcc4(int param_1,int param_2,int param_3);
void thunk_FUN_0011fd90(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_0011fd90(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_0011fdbc(int param_1,int param_2,undefined1 param_3);
undefined4 FUN_0011fddc(int param_1,undefined4 param_2,int param_3,undefined4 param_4);
void FUN_0011fed8(int param_1,int param_2,undefined4 param_3);
void FUN_0011fef4(int param_1,undefined4 param_2,int param_3);
void FUN_0011ffc0(undefined4 *param_1,undefined4 param_2,undefined4 param_3);
void FUN_00120024(int param_1,int param_2);
void FUN_001200ac(int param_1,undefined4 param_2);
void FUN_00120120(int param_1,undefined4 param_2,undefined4 param_3);
void FUN_001201cc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void FUN_00120244(int param_1,undefined4 param_2);
void FUN_00120290(int param_1,undefined4 param_2);
void FUN_001202cc(int param_1,undefined4 param_2);
uint FUN_001202f4(void);
uint FUN_00120308(void);
void FUN_0012031c(int *param_1,int param_2,undefined4 param_3,int param_4);
void FUN_00120450(undefined4 *param_1);
void FUN_001204b0(int param_1,int param_2,int param_3);
void FUN_001204f0(undefined4 param_1,undefined4 param_2,int *param_3);
void FUN_0012056c(int param_1,int param_2);
bool FUN_0012059c(int param_1,int param_2,undefined4 param_3,undefined4 param_4);
void FUN_0012070c(int param_1,int param_2);
void FUN_0012088c(int param_1,int *param_2);
void FUN_00120be8(undefined4 *param_1,int *param_2,uint *param_3,uint *param_4,uint param_5);
void FUN_00120f8c(int param_1,int *param_2,int param_3,int *param_4,int param_5);
void FUN_00121134(int param_1,int *param_2,undefined4 param_3);
undefined8 FUN_001213fc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5 ,undefined4 param_6,undefined4 param_7);
void FUN_00121584(int param_1,int *param_2,int *param_3,int param_4);
void FUN_0012164c(int param_1,undefined4 param_2,int param_3);
void FUN_001216c4(int param_1);
void FUN_00121780(int param_1,undefined4 *param_2,undefined4 param_3);
void FUN_00121ab0(int param_1);
void FUN_00121b98(int param_1,undefined4 param_2,undefined4 param_3,uint param_4);
undefined8 FUN_00121c6c(int param_1,undefined4 param_2,int param_3,undefined4 param_4);
void FUN_00122450(int param_1,byte *param_2,int param_3);
void FUN_001226e8(int *param_1,undefined4 param_2,int param_3);
undefined4 FUN_0012289c(int *param_1,undefined4 param_2,int param_3);
void FUN_00122954(int param_1,undefined4 param_2,int param_3,undefined4 param_4);
void FUN_00122b90(int param_1,undefined4 param_2,undefined4 param_3);
void FUN_00122f98(int param_1,undefined4 param_2,int param_3);
void FUN_0012312c(int param_1,int param_2,int param_3,undefined4 param_4);
void FUN_00123588(int param_1,undefined4 param_2,int param_3);
void FUN_00123c24(int param_1,undefined4 param_2,undefined4 param_3,int param_4);
void FUN_00123d7c(int param_1,undefined4 param_2,undefined4 param_3);
void FUN_0012407c(int param_1,undefined4 param_2,undefined4 param_3,int *param_4);
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
uint FUN_00125cd0(uint param_1,uint param_2,uint param_3,uint param_4);
uint FUN_00126248(uint param_1,uint param_2,undefined4 param_3,uint param_4);
uint FUN_001262b0(uint param_1,uint param_2,undefined4 param_3,uint param_4);
uint FUN_001263f8(uint param_1,uint param_2,undefined4 param_3,uint param_4);
uint FUN_0012642c(uint param_1,uint param_2,undefined4 param_3,uint param_4);
uint FUN_00126608(uint param_1,uint param_2,undefined4 param_3,uint param_4);
uint FUN_00126618(uint param_1,uint param_2,undefined4 param_3,uint param_4);
uint FUN_001267f0(uint param_1,uint param_2,undefined4 param_3,uint param_4);
uint FUN_00126858(uint param_1);
uint FUN_001268c8(uint param_1);
uint FUN_001268fc(uint param_1,uint param_2,undefined4 param_3,uint param_4);
uint FUN_00126964(uint param_1,uint param_2,undefined4 param_3,uint param_4);
uint FUN_001269cc(uint param_1,uint param_2,undefined4 param_3,uint param_4);

#endif /* KH_MOD_H */
