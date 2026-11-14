/*
 * swv_types.h - public types of the Swerve 3D engine (swv21brew.mod, Superscape, v2.1.0.364),
 * as seen from kh.mod and from the engine's own BREW glue.
 *
 * Needs brew_types.h first (Ghidra: list brew_types.h before this file in Parse C Source).
 * No includes or macros, so Ghidra's C parser accepts it. Used by both programs.
 *
 * Swerve implements JSR-184 (Mobile 3D Graphics). Evidence for every name is given inline;
 * "GUESS:" marks a meaning the evidence suggests but does not prove.
 * Addresses are emulator addresses (Ghidra image base 0x01000000).
 */

#ifndef SWV_TYPES_H
#define SWV_TYPES_H

/* ---- class ids for ISwerve::CreateObject (and QueryInterface) -----------------------------
 * The JSR-184 classes numbered in alphabetical order from 1, with one extra class at 24.
 * Evidence: swvObj_QueryInterface (0x01011fc4) accepts, for each object type, its own id plus
 * every base-class id, and that table reproduces the JSR-184 hierarchy exactly with these
 * numbers (e.g. Mesh 16 <- MorphingMesh 17 / SkinnedMesh 22; Group 9 <- World 31; IndexBuffer
 * 11 <- TriangleStripArray 28; every node also accepts Node 18 and Transformable 27; every
 * object accepts Object3D 19). ISwerve_CreateObject (0x0102479c) refuses exactly the abstract
 * classes 11, 18, 19, 27 (and 0). kh.mod's uses agree: id 8 is bound to the screen
 * (Graphics3D.bindTarget), id 21 is passed to a pick-style call, id 26 transforms vertex data.
 */
typedef enum SwerveClassId {
    SWV_ANIMATIONCONTROLLER = 1,
    SWV_ANIMATIONTRACK      = 2,
    SWV_APPEARANCE          = 3,
    SWV_BACKGROUND          = 4,
    SWV_CAMERA              = 5,
    SWV_COMPOSITINGMODE     = 6,
    SWV_FOG                 = 7,
    SWV_GRAPHICS3D          = 8,
    SWV_GROUP               = 9,
    SWV_IMAGE2D             = 10,
    SWV_INDEXBUFFER         = 11,   /* abstract: CreateObject refuses it */
    SWV_KEYFRAMESEQUENCE    = 12,
    SWV_LIGHT               = 13,
    SWV_LOADER              = 14,
    SWV_MATERIAL            = 15,
    SWV_MESH                = 16,
    SWV_MORPHINGMESH        = 17,
    SWV_NODE                = 18,   /* abstract */
    SWV_OBJECT3D            = 19,   /* abstract; every object accepts it in QueryInterface */
    SWV_POLYGONMODE         = 20,
    SWV_RAYINTERSECTION     = 21,
    SWV_SKINNEDMESH         = 22,
    SWV_SPRITE3D            = 23,
    SWV_CLASS24             = 24,   /* GUESS: an Image2D subclass that is not a JSR-184 class (QI accepts
                                       10 and 24); its name would sort between Sprite3D and Texture2D */
    SWV_TEXTURE2D           = 25,
    SWV_TRANSFORM           = 26,
    SWV_TRANSFORMABLE       = 27,   /* abstract */
    SWV_TRIANGLESTRIPARRAY  = 28,
    SWV_VERTEXARRAY         = 29,
    SWV_VERTEXBUFFER        = 30,
    SWV_WORLD               = 31,
    SWV_EXT100              = 100,  /* Swerve extension classes (not JSR-184): a SWVARC archive */
    SWV_EXT101              = 101   /* and one entry's stream (SwvExtObject; 0x0102d8ac / 0x0102d990) */
} SwerveClassId;

/* Internal object type, returned by a native object's virtual getType (vtable +4). Values 1-22
 * are the M3G file-format object types; 25-28 are Swerve's own. Used by swv_WrapObject
 * (0x01039fb4) to pick the BREW vtable, and by swvObj_QueryInterface. */
typedef enum SwerveObjectType {
    SWVT_ANIMATIONCONTROLLER = 1,  SWVT_ANIMATIONTRACK = 2,  SWVT_APPEARANCE = 3,
    SWVT_BACKGROUND = 4,           SWVT_CAMERA = 5,          SWVT_COMPOSITINGMODE = 6,
    SWVT_FOG = 7,                  SWVT_POLYGONMODE = 8,     SWVT_GROUP = 9,
    SWVT_IMAGE2D = 10,             SWVT_TRIANGLESTRIPARRAY = 11, SWVT_LIGHT = 12,
    SWVT_MATERIAL = 13,            SWVT_MESH = 14,           SWVT_MORPHINGMESH = 15,
    SWVT_SKINNEDMESH = 16,         SWVT_TEXTURE2D = 17,      SWVT_SPRITE3D = 18,
    SWVT_KEYFRAMESEQUENCE = 19,    SWVT_VERTEXARRAY = 20,    SWVT_VERTEXBUFFER = 21,
    SWVT_WORLD = 22,
    SWVT_UNUSED23 = 23,            /* refused by QueryInterface; shares type 24's vtable */
    SWVT_CLASS24 = 24,             SWVT_GRAPHICS3D = 25,     SWVT_RAYINTERSECTION = 26,
    SWVT_TRANSFORM = 27,           SWVT_LOADER = 28
} SwerveObjectType;

/* ISwerve::GetVersion output. 0x01024a68 writes {2, 1, 0, 0x16c, 1} = 2.1.0.364, the version in
   swv21brew's MIF (dumps/mif_dump/14957.txt). GUESS: meaning of the last word. */
typedef struct SwerveVersion {
    uint32 major;      /* 2 */
    uint32 minor;      /* 1 */
    uint32 micro;      /* 0 */
    uint32 build;      /* 364 */
    uint32 field_10;   /* 1 */
} SwerveVersion;

/* ISwerve::GetPixelFormat output: what 0x01024a1c writes - an RGB565 descriptor. */
typedef struct SwervePixelFormat {
    uint32 nBitsPerPixel;  /* 16 */
    uint32 maskR;          /* 0xF800 */
    uint32 maskG;          /* 0x07E0 */
    uint32 maskB;          /* 0x001F */
    uint32 shiftR;         /* 11 */
    uint32 shiftG;         /* 5 */
    uint32 shiftB;         /* 0 */
    uint32 bitsR;          /* 5 */
    uint32 bitsG;          /* 6 */
    uint32 bitsB;          /* 5 */
} SwervePixelFormat;

/* ---- ISwerve: the object returned for AEECLSID_SWERVE ------------------------------------ */
typedef struct ISwerve ISwerve;
typedef struct ISwerveVtbl {
    /* 0 +0x00 */ uint32 (*AddRef)(ISwerve *po);                                        /* 0x01024788 */
    /* 1 +0x04 */ uint32 (*Release)(ISwerve *po);                                       /* 0x01024978 */
    /* 2 +0x08 */ void   (*GetVersion)(ISwerve *po, SwerveVersion *pVer);               /* 0x01024a68 */
    /* 3 +0x0c */ void   (*GetPixelFormat)(ISwerve *po, SwervePixelFormat *pFmt);       /* 0x01024a1c */
    /* 4 +0x10 */ int    (*CreateObject)(ISwerve *po, SwerveClassId cls, void **ppObj); /* 0x0102479c:
                         NULL ppObj -> EBADPARM (14); unknown/abstract class -> *ppObj = 0 */
} ISwerveVtbl;
struct ISwerve {
    const ISwerveVtbl *pvt;  /* +0x00 */
    uint32   m_nRefs;        /* +0x04 */
    IShell  *m_pIShell;      /* +0x08 AddRef'd by swv_NewSwerve */
    IModule *m_pIModule;     /* +0x0c AddRef'd by swv_NewSwerve */
};

/* ---- generic Swerve object interface (every CreateObject result) --------------------------
 * The BREW-facing object is a small wrapper {vtbl, native object, refs} built by swv_WrapObject
 * (0x01039fb4). Slots 0-2 are shared by all classes; slots from 3 on are per class, filled at
 * run time by a per-type vtable builder (swv_InitVtbl_<Class>) and cached in the globals. */
typedef struct ISwerveObject ISwerveObject;
typedef struct ISwerveObjectVtbl {
    /* 0 +0x00 */ uint32 (*AddRef)(ISwerveObject *po);                                   /* 0x01011f8c */
    /* 1 +0x04 */ uint32 (*Release)(ISwerveObject *po);                                  /* 0x01012294 */
    /* 2 +0x08 */ int    (*QueryInterface)(ISwerveObject *po, SwerveClassId cls, void **ppo); /* 0x01011fc4:
                         3 if the object is not of class cls or a subclass of it */
} ISwerveObjectVtbl;
struct ISwerveObject {
    const ISwerveObjectVtbl *pvt;  /* +0x00 */
    void   *pNative;               /* +0x04 engine-side object (C++-style, vtable with getType at +4) */
    uint32  m_nRefs;               /* +0x08 */
};

/* Graphics3D interface (class 8). 23 slots (0x5c bytes, swv_InitVtbl_Graphics3D 0x0102fa30).
 * Only BindTarget is identified; other slots are generic until analysed. */
typedef struct IGraphics3D IGraphics3D;
typedef struct IGraphics3DVtbl {
    /*  0 +0x00 */ uint32 (*AddRef)(IGraphics3D *po);
    /*  1 +0x04 */ uint32 (*Release)(IGraphics3D *po);
    /*  2 +0x08 */ int (*QueryInterface)(IGraphics3D *po, SwerveClassId cls, void **ppo);
    /*  3 +0x0c */ int (*slot3)(IGraphics3D *po, ...);
    /*  4 +0x10 */ int (*slot4)(IGraphics3D *po, ...);
    /*  5 +0x14 */ int (*slot5)(IGraphics3D *po, ...);
    /*  6 +0x18 */ int (*slot6)(IGraphics3D *po, ...);
    /*  7 +0x1c */ int (*slot7)(IGraphics3D *po, ...);
    /*  8 +0x20 */ int (*BindTarget)(IGraphics3D *po, uint16 cx, uint16 cy, int nPitch, void *pBits,
                                     int x, int y, int dx, int dy);
                   /* 0x0102ff38 -> native 0x010202e4. GUESS: name (JSR-184 Graphics3D.bindTarget);
                      kh.mod passes the screen IDIB's cx, cy, nPitch, pBmp and its view rect */
    /*  9 +0x24 */ int (*slot9)(IGraphics3D *po, ...);
    /* 10 +0x28 */ int (*slot10)(IGraphics3D *po, ...);
    /* 11 +0x2c */ int (*slot11)(IGraphics3D *po, ...);
    /* 12 +0x30 */ int (*slot12)(IGraphics3D *po, ...);
    /* 13 +0x34 */ int (*slot13)(IGraphics3D *po, ...);
    /* 14 +0x38 */ int (*slot14)(IGraphics3D *po, ...);
    /* 15 +0x3c */ int (*slot15)(IGraphics3D *po, ...);
    /* 16 +0x40 */ int (*slot16)(IGraphics3D *po, ...);
    /* 17 +0x44 */ int (*Render)(IGraphics3D *po, ...);
    /* 18 +0x48 */ int (*slot18)(IGraphics3D *po, ...);
    /* 19 +0x4c */ int (*slot19)(IGraphics3D *po, ...);
    /* 20 +0x50 */ int (*slot20)(IGraphics3D *po, ...);
    /* 21 +0x54 */ int (*slot21)(IGraphics3D *po, ...);
    /* 22 +0x58 */ int (*slot22)(IGraphics3D *po, ...);
} IGraphics3DVtbl;
struct IGraphics3D { const IGraphics3DVtbl *pvt; void *pNative; uint32 m_nRefs; };

/* ---- extension objects, classes 100 and 101 ------------------------------------------------
 * The objects swv_Create_Ext100 (0x0102d8ac, 0x18 bytes) and swv_Create_Ext101 (0x0102d990, 0x1c
 * bytes) build: BREW-style {vtable, refs, ...}, the vtables cached in pVtblCache[0x1b] (Ext100Vtbl,
 * 6 slots) and [0x1c] (Ext101Vtbl, 3 slots); slots 0 and 1 are the shared swvExt_AddRef (0x010041ec)
 * and swvExt_Release (0x01004200). Ext100 is a SWVARC archive (swvArchive_Open: the magic
 * "\xabSWVARC\xbb\r\n\x1a\n", a 0x21-byte header with an adler32, a directory of named entries) with
 * swvArchive_EnumInit / EnumNext / OpenEntry; Ext101 is one entry's stream (swvArchiveEntry_Read), a
 * region of the archive's IFile. No file of the game's data is such an archive. */
typedef struct SwvExtObject {
    const void *pvt;        /* +0x00 Ext100Vtbl / Ext101Vtbl (arrays of function addresses) */
    uint32   m_nRefs;       /* +0x04 1 after the constructor */
    IFile   *pFile;         /* +0x08 the archive file (an entry shares it); released by swvExt_Release */
    void    *pBuffer;       /* +0x0c archive: its directory; freed by swvExt_Release */
    uint32   field_10;      /* +0x10 archive: the data's start; entry: the region's start */
    uint32   field_14;      /* +0x14 archive: the listing's index; entry: the region's size */
    uint32   field_18;      /* +0x18 entry only (the archive ends at +0x18): the read position */
} SwvExtObject;

/* ---- SkinnedMesh skinning data ------------------------------------------------------------
 * Built once by swvSkin_BuildBoneSets (0x0101790c). A SkinnedMesh keeps its bone table at +0xc4
 * (count +0xc8: SwvSkinBone, one per M3G addTransform(bone, weight, firstVertex, numVertices)); at
 * +0xd0 a list (array +0xd4, count +0xd8) of SwvSkinBoneSet, the distinct sets of the (at most 2)
 * heaviest bones of its vertices, index 0 the no-bone template; and at +0xe0 a list (array +0xe4,
 * count +0xe8) of uint16, each vertex's bone-set index. +0xf0 / +0xf4 / +0xf8 become 1 once built.
 * GUESS: the field names. */
typedef struct SwvSkinBone {
    int32    weight;        /* +0x00 swvSkin_VertexBones keeps the heaviest */
    uint16   firstVertex;   /* +0x04 the first vertex it moves */
    uint16   vertexCount;   /* +0x06 how many (0 is an error) */
    uint16   bone;          /* +0x08 GUESS: the bone node's index */
    uint16   pad_0a;        /* +0x0a */
} SwvSkinBone;

typedef struct SwvSkinBoneSet {
    uint16   bones[2];      /* +0x00 indices into the bone table; 0xffff: none */
    uint32   transform[17]; /* +0x04 16 float bits and a flags word (swv_Matrix4SetIdentity) */
    uint32   weightScale;   /* +0x48 float bits: 1 / the sum of the bones' weights */
} SwvSkinBoneSet;

/* ---- the software rasteriser's context (no struct yet) --------------------------------------
 * The fields the triangle code is known to use (GUESS: the names):
 *   +0x148 .. +0x154  4 RGB565 pixels (a word each): the flat colour's 2x2 dither (swv_SetupFlatDither),
 *                     word (x & 1) + (y & 1) * 2 (swv_SpanFillFlatDithered)
 *   +0x290 .. +0x298  the triangle's three vertices (swv_RasterTriangle); a vertex is 0x3c bytes, its
 *                     +0x0c / +0x10 / +0x14 the red, green, blue in 16.16 (1.0 = 0x10000)
 *   +0x2b8            the span routine swv_RasterTriangleSetup picked (swv_SpanFillFlat,
 *                     swv_SpanFillFlatDithered, swv_SpanFillTextured, swv_SpanFillGeneric, ...) */

/* ---- engine globals ------------------------------------------------------------------------
 * Swerve has no writable statics either: swv_NewSwerve allocates this 0x24-byte block and
 * stores it in the *host applet* at GetAppInstance()+0x20 (KHApp.pSwerveGlobals). It also
 * replaces the applet's pFreeAppData (+0x1c) with its own clean-up, keeping the old value here
 * and restoring it in ISwerve_Release. */
typedef struct SwerveGlobals {
    uint32   field_00;        /* +0x00 read/written by swv_GetGlobal00 / swv_SetGlobal00 (0x01039910 /
                                 0x0103af88); meaning not identified */
    ISwerve *pSwerve;         /* +0x04 the ISwerve object (swv_GetSwerveObject 0x01039938) */
    void   **pVtblCache;      /* +0x08 0x74-byte array (29 entries): BREW vtables built per object type
                                 (swv_GetVtblCache 0x0103999c); freed in ISwerve_Release */
    void    *pfnSavedFreeAppData; /* +0x0c the applet's previous pFreeAppData */
    uint32   field_10[5];     /* +0x10 .. +0x23 */
} SwerveGlobals;

#endif /* SWV_TYPES_H */
