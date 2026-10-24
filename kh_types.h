/*
 * kh_types.h - kh.mod's own data structures.
 *
 * Needs brew_types.h and swv_types.h first (Ghidra: list brew_types.h, swv_types.h, then this file
 * in Parse C Source).
 * No includes or macros, so Ghidra's C parser accepts it.
 *
 * Field names are mine unless they come from the BREW SDK. Every one carries the evidence it
 * rests on: the function that writes it, or the call it is passed to. "GUESS:" marks a meaning
 * that the evidence suggests but does not prove. Unknown fields are named field_<offset>.
 * Addresses are emulator addresses (Ghidra image base 0x00100000).
 */

#ifndef KH_TYPES_H
#define KH_TYPES_H

/* ---- Swerve 3D engine -----------------------------------------------------------------------
 * ISwerve, IGraphics3D, SwerveGlobals and the class-id enum live in swv_types.h (shared with the
 * swv21brew.mod program). ISwerveTarget is the name kh_mod.c uses for the Graphics3D interface
 * that kh_OnAppStart gets from ISwerve::CreateObject(SWV_GRAPHICS3D) and binds to the screen.
 */
typedef struct IGraphics3D ISwerveTarget;   /* struct tag: valid even if swv_types.h is parsed later */

/* Generic interface pointer for objects whose class is not identified yet. */
typedef struct IBaseVtbl { uint32 (*AddRef)(void *po); uint32 (*Release)(void *po); } IBaseVtbl;
typedef struct IBase { const IBaseVtbl *pvt; } IBase;

/* ---- KHApp: the applet object (AEEApplet_New(0xE0, ...) in AEEClsCreateInstance) -----------
 * 0xE0 bytes. Offsets +0x00..+0x1F are AEEApplet. Constructor/destructor pairs named below are
 * the functions that create the object in kh_OnAppStart and destroy it in kh_OnAppStop.
 */
typedef struct KHApp {
    AEEApplet      a;                /* +0x00 BREW applet header (SDK) */
    struct SwerveGlobals *pSwerveGlobals; /* +0x20 owned by swv21brew: swv_NewSwerve (0x01039df4) allocates the
                                        engine's globals and stores them here (GetAppInstance()+0x20) */
    AEEDeviceInfo  devInfo;          /* +0x24 ISHELL_GetDeviceInfo target (kh_OnAppStart) */
    struct ISwerve *pSwerve;         /* +0x64 ISHELL_CreateInstance(AEECLSID_SWERVE); released in kh_OnAppStop */
    ISwerveTarget *pSwerveTarget;    /* +0x68 Graphics3D: pSwerve->CreateObject(SWV_GRAPHICS3D, &...);
                                        released in kh_OnAppStop */
    IBase         *pObj6c;           /* +0x6c GUESS: interface (released via vtbl[1] in kh_OnAppStop);
                                        framebuffer binding is skipped when it is NULL */
    IDIB          *pScreenDIB;       /* +0x70 device bitmap QueryInterface(AEECLSID_DIB) */
    AEERect        rcView;           /* +0x74 {0, 0, devInfo.cxScreen, devInfo.cyScreen} */
    uint32         field_7c;         /* +0x7c */
    uint32         field_80;         /* +0x80 */
    uint32         field_84;         /* +0x84 */
    uint32         field_88;         /* +0x88 */
    int32          field_8c;         /* +0x8c set to 0x1e or a computed value at the end of kh_OnAppStart */
    int32          nErr;             /* +0x90 GUESS: start-up error code; every init step is skipped
                                        once it is non-zero, and key releases are ignored */
    void          *pObj94;           /* +0x94 created by 0x10c218, destroyed by 0x10cee4 */
    void          *pObj98;           /* +0x98 created by 0x10be14, destroyed by 0x10cda4 */
    void          *pObj9c;           /* +0x9c created by 0x10b804, destroyed by 0x10c9dc */
    void          *pObja0;           /* +0xa0 created by 0x10bb2c, destroyed by 0x10cd2c */
    void          *pGame;            /* +0xa4 GUESS: game state; receives key releases (kh_OnKeyRelease);
                                        destroyed by 0x10c2c4 */
    void          *pObja8;           /* +0xa8 created by 0x10b4e4; EVT_APP_MESSAGE handled only while set */
    uint32         field_ac;         /* +0xac */
    uint32         dwStartTimeMS;    /* +0xb0 aee_GetTimeMS() at EVT_APP_START */
    uint32         bStarted;         /* +0xb4 GUESS: set to 1 at EVT_APP_START */
    uint32         bSuspended;       /* +0xb8 GUESS: set to 1 at EVT_APP_SUSPEND */
    uint32         field_bc;         /* +0xbc */
    uint32         field_c0;         /* +0xc0 */
    void          *pBufc4;           /* +0xc4 heap block (helper free in kh_OnAppStop) */
    void          *pBufc8;           /* +0xc8 heap block (helper free in kh_OnAppStop) */
    uint32         field_cc;         /* +0xcc */
    void          *pObjd0;           /* +0xd0 created by 0x10ac6c(0, pMe), destroyed by 0x10c3f8 */
    uint32         field_d4;         /* +0xd4 */
    uint32         fpStatus;         /* +0xd8 GUESS: soft-float status word (what a compiler fplib keeps in a
                                        static). Address returned by kh_GetFpStatusPtr; read by
                                        kh.mod's double->float at 0x12479c (tests bit 0x800). */
    uint32         field_dc;         /* +0xdc address returned by kh_GetAppFieldPtr_dc */
} KHApp;

#endif /* KH_TYPES_H */
