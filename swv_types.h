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
    SWV_CLASS24             = 24,   /* an Image2D subclass (QI accepts 10 and 24) that is not a
                                       JSR-184 class: JSR-184 1.1 has none between Sprite3D and
                                       Texture2D, where its name would sort (GUESS: what it is) */
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

/* The engine's error codes: what FUN_0102f7e0 (it does not return) is given, the JSR-184 exception each
 * stands for. The listing keeps the INTEGER_MINUS_* literals the code loads; the comments name these.
 * From the methods whose checks the spec lists (JSR-184 1.1): -1301 where it throws
 * IllegalArgumentException (Group.addChild, Texture2D.setImage, ...), -1302 NullPointerException
 * (a null argument), -1300 IllegalStateException (Node.align: a node aligned to its descendant), -1101
 * IndexOutOfBoundsException (Group.getChild, Object3D.getAnimationTrack, ...), -1000
 * ArithmeticException (Node.getTransformTo: a singular transformation), -1202 the Loader's
 * IOException for data not in a valid format (the M3G record readers' range checks). */
typedef enum SwerveError {
    SWVE_ARITHMETIC           = -1000,   /* ArithmeticException */
    SWVE_BAD_FLOAT            = -1001,   /* GUESS: name; a float argument that is a denormal, an infinity
                                            or a NaN (swv_CheckFloat); JSR-184 1.1 has no such check
                                            (GUESS: an ArithmeticException to the application) */
    SWVE_INDEX_OUT_OF_BOUNDS  = -1101,   /* IndexOutOfBoundsException */
    SWVE_READER_STATE         = -1103,   /* GUESS: the M3G reader used out of order (swvM3GReader_End /
                                            _Begin); no spec method maps to it */
    SWVE_END_OF_DATA          = -1200,   /* GUESS: a read past the end of the loader's buffer
                                            (FUN_01019698, FUN_01026d30); an IOException to the
                                            application */
    SWVE_BAD_LENGTH           = -1201,   /* GUESS: name; an M3G section's lengths are not consistent
                                            (swvM3GReader_Feed); an IOException to the application */
    SWVE_BAD_FILE             = -1202,   /* IOException: the M3G data is not valid */
    SWVE_ILLEGAL_STATE        = -1300,   /* IllegalStateException */
    SWVE_ILLEGAL_ARGUMENT     = -1301,   /* IllegalArgumentException */
    SWVE_NULL_POINTER         = -1302    /* NullPointerException */
} SwerveError;

/* JSR-184 AnimationTrack target properties (AnimationTrack +0x24; swvObject3D_AnimateValue, the native
 * Object3D.animate, tests CROP, MORPH_WEIGHTS and SCALE). The values: JSR-184 1.1, AnimationTrack
 * (Constant Field Values, ALPHA 256 .. VISIBILITY 276). */
typedef enum SwerveAnimTarget {
    SWV_ANIM_ALPHA = 0x100,           SWV_ANIM_AMBIENT_COLOR = 0x101,   SWV_ANIM_COLOR = 0x102,
    SWV_ANIM_CROP = 0x103,            SWV_ANIM_DENSITY = 0x104,         SWV_ANIM_DIFFUSE_COLOR = 0x105,
    SWV_ANIM_EMISSIVE_COLOR = 0x106,  SWV_ANIM_FAR_DISTANCE = 0x107,    SWV_ANIM_FIELD_OF_VIEW = 0x108,
    SWV_ANIM_INTENSITY = 0x109,       SWV_ANIM_MORPH_WEIGHTS = 0x10a,   SWV_ANIM_NEAR_DISTANCE = 0x10b,
    SWV_ANIM_ORIENTATION = 0x10c,     SWV_ANIM_PICKABILITY = 0x10d,     SWV_ANIM_SCALE = 0x10e,
    SWV_ANIM_SHININESS = 0x10f,       SWV_ANIM_SPECULAR_COLOR = 0x110,  SWV_ANIM_SPOT_ANGLE = 0x111,
    SWV_ANIM_SPOT_EXPONENT = 0x112,   SWV_ANIM_TRANSLATION = 0x113,     SWV_ANIM_VISIBILITY = 0x114
} SwerveAnimTarget;

/* The properties each class adds to those its base class can animate: its engine vtable +0x20,
 * IsAnimatable(property) (swvObject3D_IsAnimatable gives none; swvMaterial_IsAnimatable ..
 * swvSprite3D_IsAnimatable and swvCamera_IsAnimatable test their mask, then ask their base;
 * FUN_010124ac, a Node subclass's, only asks Node's). A property's bit is
 * 1 << (property - 0xff). The masks are the classes JSR-184 1.1, AnimationTrack's fields name for each
 * property (each mask, its hex value and its base class checked against them). */
#define SWV_ANIM_BIT(property)      ((uint32)1 << ((property) - 0xff))
/* 0x000300c6, Material; base Object3D */
#define SWV_ANIMATED_MATERIAL       (SWV_ANIM_BIT(SWV_ANIM_ALPHA) | \
                                     SWV_ANIM_BIT(SWV_ANIM_AMBIENT_COLOR) | \
                                     SWV_ANIM_BIT(SWV_ANIM_DIFFUSE_COLOR) | \
                                     SWV_ANIM_BIT(SWV_ANIM_EMISSIVE_COLOR) | \
                                     SWV_ANIM_BIT(SWV_ANIM_SHININESS) | \
                                     SWV_ANIM_BIT(SWV_ANIM_SPECULAR_COLOR))
/* 0x08, Texture2D; base Transformable */
#define SWV_ANIMATED_TEXTURE2D      (SWV_ANIM_BIT(SWV_ANIM_COLOR))
/* 0x1a, Background; base Object3D */
#define SWV_ANIMATED_BACKGROUND     (SWV_ANIM_BIT(SWV_ANIM_ALPHA) | SWV_ANIM_BIT(SWV_ANIM_COLOR) | \
                                     SWV_ANIM_BIT(SWV_ANIM_CROP))
/* 0x800, MorphingMesh; base Node */
#define SWV_ANIMATED_MORPHINGMESH   (SWV_ANIM_BIT(SWV_ANIM_MORPH_WEIGHTS))
/* 0x0a, VertexBuffer; base Object3D */
#define SWV_ANIMATED_VERTEXBUFFER   (SWV_ANIM_BIT(SWV_ANIM_ALPHA) | SWV_ANIM_BIT(SWV_ANIM_COLOR))
/* 0x0010a000, Transformable; base Object3D */
#define SWV_ANIMATED_TRANSFORMABLE  (SWV_ANIM_BIT(SWV_ANIM_ORIENTATION) | SWV_ANIM_BIT(SWV_ANIM_SCALE) | \
                                     SWV_ANIM_BIT(SWV_ANIM_TRANSLATION))
/* 0x00001128, Fog; base Object3D */
#define SWV_ANIMATED_FOG            (SWV_ANIM_BIT(SWV_ANIM_COLOR) | SWV_ANIM_BIT(SWV_ANIM_DENSITY) | \
                                     SWV_ANIM_BIT(SWV_ANIM_FAR_DISTANCE) | \
                                     SWV_ANIM_BIT(SWV_ANIM_NEAR_DISTANCE))
/* 0x00204002, Node; base Transformable */
#define SWV_ANIMATED_NODE           (SWV_ANIM_BIT(SWV_ANIM_ALPHA) | SWV_ANIM_BIT(SWV_ANIM_PICKABILITY) | \
                                     SWV_ANIM_BIT(SWV_ANIM_VISIBILITY))
/* 0x000c0408, Light; base Node */
#define SWV_ANIMATED_LIGHT          (SWV_ANIM_BIT(SWV_ANIM_COLOR) | SWV_ANIM_BIT(SWV_ANIM_INTENSITY) | \
                                     SWV_ANIM_BIT(SWV_ANIM_SPOT_ANGLE) | \
                                     SWV_ANIM_BIT(SWV_ANIM_SPOT_EXPONENT))
#define SWV_ANIMATED_SPRITE3D       (SWV_ANIM_BIT(SWV_ANIM_CROP))   /* 0x10, Sprite3D; base Node */
/* 0x00001300, Camera; base Node (swvCamera_IsAnimatable, hand-written: no Ghidra function) */
#define SWV_ANIMATED_CAMERA         (SWV_ANIM_BIT(SWV_ANIM_FAR_DISTANCE) | \
                                     SWV_ANIM_BIT(SWV_ANIM_FIELD_OF_VIEW) | \
                                     SWV_ANIM_BIT(SWV_ANIM_NEAR_DISTANCE))

/* JSR-184 Image2D formats (Image2D +0x40; swvImage2D_BytesPerPixel). The values are JSR-184's. */
typedef enum SwerveImageFormat {
    SWV_IMAGE_ALPHA = 0x60,           SWV_IMAGE_LUMINANCE = 0x61,       SWV_IMAGE_LUMINANCE_ALPHA = 0x62,
    SWV_IMAGE_RGB = 0x63,             SWV_IMAGE_RGBA = 0x64
} SwerveImageFormat;

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
                   /* 0x0102ff38 -> native 0x010202e4. GUESS: name (JSR-184 1.1, Graphics3D.bindTarget,
                      for a raw bitmap: the viewport clamped to 1 .. 1024 instead of -1301, no -1300
                      for a bound target; see swv_Graphics3D_bindTarget); kh.mod passes the screen
                      IDIB's cx, cy, nPitch, pBmp and its view rect */
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
    /* 22 +0x58 */ int (*GetProperty)(IGraphics3D *po, uint32 index, int32 *pValue);
                   /* 0x0102f960 swvGraphics3D_GetProperty. GUESS: name (JSR-184
                      Graphics3D.getProperties, by index): -1301 above 11, else the value of
                      swvGraphics3D_Property: 0 - 3 false, 4 - 5 true, 6 256, 7 - 9 1024, 10 - 11 2
                      (GUESS the property names: 1.1's keys less maxViewportWidth / Height, so 6
                      maxLights, 7 - 9 the largest viewport, texture and sprite crop; kh.mod does not
                      call it) */
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

/* ---- AnimationController, the native object (no struct yet) ------------------------------------
 * Its fields (GUESS: the names; JSR-184 1.1, AnimationController: setActiveInterval
 * swvAnimationController_SetActiveIntervalValue sets +0x1c / +0x20, setPosition
 * swvAnimationController_SetPositionValue +0x24 / +0x28, setSpeed swvAnimationController_SetSpeedValue
 * +0x2c, setWeight swvAnimationController_SetWeightValue +0x30; the BREW slots 18 - 26, kh_types.h
 * SwerveAnimationControllerVtbl):
 *   +0x1c / +0x20     the active interval's start and end (world times): active when they are
 *                     equal, else for start <= t < end (swvAnimationController_IsActive)
 *   +0x24             the reference sequence time (a float)
 *   +0x28             the reference world time
 *   +0x2c             the speed (a float; swvAnimationController_Speed)
 *   +0x30             the weight (a float)
 * The position at a world time is +0x24 + (worldTime - +0x28) * +0x2c (swvAnimationController_Position,
 * the spec's ts = tsref + s (tw - twref)); an AnimationTrack's sample gives its validity as 0x7fffffff
 * (for ever) when the controller is not active (FUN_01010de0). */

/* ---- KeyframeSequence (class 12) --------------------------------------------------------------
 * The fields the keyframe code reads (swvKeyframeSequence_*); the Object3D part before +0x1c is not
 * identified yet. The values: JSR-184 1.1, KeyframeSequence (Constant Field Values): interpolation
 * LINEAR 0xb0 (176), SLERP 0xb1, SPLINE 0xb2,
 * SQUAD 0xb3, STEP 0xb4; repeat mode CONSTANT 0xc0 (192), LOOP 0xc1. A keyframe is
 * swvKeyframeSequence_KeyframeWords words of keyframes: its time (an int), then its components (float
 * bits; for SPLINE and SQUAD each with its two tangents). GUESS: the names of the fields not proven. */
typedef struct SwvKeyframeSequence {
    uint32   field_00[7];    /* +0x00 .. +0x1b not identified */
    int32    interpolation;  /* +0x1c 0xb0 .. 0xb4 */
    int32    repeatMode;     /* +0x20 0xc0 CONSTANT, 0xc1 LOOP */
    uint32   duration;       /* +0x24 the duration as float bits (swv_fflt of +0x28); must be above 0 */
    int32    durationInt;    /* +0x28 the duration, an int: the M3G file's UInt32
                                (swvM3G_ReadKeyframeSequence) and what JSR-184 1.1,
                                KeyframeSequence.getDuration returns (slot 19, 0x01032ac0);
                                swvKeyframeSequence_Sample uses it - 1 */
    int32    validFirst;     /* +0x2c the valid range (setValidRange); first > last: it wraps, and the
                                wrapped keyframes 0 .. last are numbered keyframeCount + i
                                (swvKeyframeSequence_PreviousValid / NextValid) */
    int32    validLast;      /* +0x30 */
    int32    componentCount; /* +0x34 */
    int32    keyframeCount;  /* +0x38 */
    uint32   field_3c;       /* +0x3c not identified */
    int32   *keyframes;      /* +0x40 keyframeCount keyframes of swvKeyframeSequence_KeyframeWords words */
    uint32   field_44[2];    /* +0x44 .. +0x4b not identified */
    int32    prepared;       /* +0x4c set by swvKeyframeSequence_Prepare */
} SwvKeyframeSequence;

/* ---- Object3D, the base of every native object (no struct yet) --------------------------------
 * The fields every class shares (GUESS: the names; swvObject3D_AnimationTrackCount,
 * swvObject3D_AnimationTrack, FUN_01006518):
 *   +0x00             the vtable (engine-relative offsets; +4 getType)
 *   +0x0c             the user id (JSR-184 1.1, Object3D.getUserID / setUserID: swvObject3D_GetUserId and
 *                     swvObject3D_SetUserId, the slots 3 and 4; kept by a duplicate, FUN_01006518)
 *   +0x10             the animation track list, or NULL: a growable array, +4 the items (a word each),
 *                     +8 the count
 *   +0x14             a list of its own, copied when not empty (GUESS: the user parameters)
 * Its engine vtable's +0x20 is IsAnimatable(property) (GUESS: the name; Object3D.addAnimationTrack,
 * swvObject3D_AddAnimationTrackValue, asks it): swvObject3D_IsAnimatable gives 0; each class's own tests
 * the properties it adds (SWV_ANIMATED_*) and then asks its base class's. Its engine vtable's +0x18 is
 * reference(index) (GUESS: the name; swvObject3D_References walks it from 0): an object it refers to, 0
 * for none, -2 when the next index is a list (+4 the items, +8 the count), -1 past the last. The base,
 * swvObject3D_Reference, gives the animation tracks; each class's own gives its references first and then
 * calls its base class's with index less their count (swvGroup_Reference, swvAnimationTrack_Reference,
 * FUN_01011c20 .. FUN_01011f4c). The BREW-facing ISwerveObject slots 3 - 17 they implement: kh_types.h
 * SwerveObject3DVtbl, filled by swv_InitVtbl_Object3D. */

/* ---- Node, the base of the scene-graph objects (no struct yet) ---------------------------------
 * The fields the alignment code reads (GUESS: the names; FUN_0100a02c, the Node alignment, JSR-184
 * 1.1 Node.align):
 *   +0x20             the node's transform (FUN_0102c7a8 reads it)
 *   +0x24             the alignment block, or NULL (no alignment):
 *                       +0x0 the z target (swvNode_AlignmentTargetZ; NONE without a block)
 *                       +0x4 the y target (swvNode_AlignmentTargetY; NONE without a block)
 *                       +0x8 the z reference (swvNode_AlignmentReferenceZ; NULL: the reference
 *                            given to Node.align, JSR-184 1.1 Node.setAlignment)
 *                       +0xc the y reference (swvNode_AlignmentReferenceY; NULL as for z)
 *   +0x30             the parent (NULL for a root; swvNode_Depth walks it, FUN_010048e4 too,
 *                     swvNode_SameSceneGraph to the root, swvNode_HasAncestor / IsAncestorOf for an
 *                     ancestor)
 *   +0x34             the next sibling in its parent's child list (NULL: the last)
 *   +0x38             a Group's first child (swvGroup_ChildCount, swvGroup_NthChild, FUN_01003474)
 *   +0x3c             the depth, a byte (0 for a root; 0xff: not cached or deeper than 254;
 *                     swvNode_Depth, swvNode_SetDepth)
 * The alignment targets (JSR-184 1.1, Node constants): NONE 0x90, ORIGIN 0x91, X_AXIS 0x92, Y_AXIS 0x93,
 * Z_AXIS 0x94; swvNode_SetAlignment (Node.setAlignment) stores them, the range 0x90 - 0x94 is checked by
 * its callers (-1301 in the BREW wrapper FUN_01034b78, -1202 in the M3G Node reader, FUN_010196cc). */

/* ---- VertexBuffer, the native object (no struct yet) -------------------------------------------
 * Its fields (GUESS: the names; the BREW slots, kh_types.h SwerveVertexBufferVtbl, and
 * swvVertexBuffer_Array):
 *   +0x1c             the vertex count: that of its arrays, which must all agree (FUN_01023b3c,
 *                     swvVertexBuffer_HasOnlyArray; -1301), 0 once it has none
 *   +0x20             the default colour (ARGB)
 *   +0x24             the positions (a VertexArray; attribute 0)
 *   +0x28             the normals (attribute 2; corrected, was "the colours":
 *                     swvVertexBuffer_SetNormalsValue enforces JSR-184 1.1 VertexBuffer.setNormals' rule
 *                     on it)
 *   +0x2c             the colours (attribute 1; corrected, was "the normals":
 *                     swvVertexBuffer_SetColorsValue enforces VertexBuffer.setColors' rule)
 *   +0x30 / +0x34     the texture coordinates of units 0 / 1 (attributes 3, 4)
 *   +0x38 .. +0x44    the positions' bias (3 floats) and scale (swvVertexBuffer_SetPositionsValue)
 *   +0x48 .. +0x54    the normals' bias and scale (swvVertexBuffer_SetNormalsValue: to -1 .. 1)
 *   +0x58 .. +0x6c    the texture coordinates' bias, 3 floats a unit; +0x70 / +0x74 their scales
 * Made by FUN_01028898 (0x78 bytes; the default colour 0xffffffff, opaque white, as JSR-184 1.1
 * VertexBuffer(); corrected, was 0xff000000, the value it stores first). */

/* ---- Mesh, the native object (no struct yet) ----------------------------------------------------
 * Its fields (GUESS: the names):
 *   +0x88             its own VertexBuffer (swvMesh_VertexBuffer)
 * Its engine vtable +0x2c gives the VertexBuffer to draw with (GUESS; swvMesh_GetVertexBuffer asks it).
 * A MorphingMesh's (FUN_010104f0, FUN_0100fb34): +0xac set when the morphed buffer must be made again,
 * +0xb0 the morphed VertexBuffer, +0xb4 / +0xb8 the work buffer, +0xc8 / +0xcc the morph targets and
 * their count, +0xd4 their weights: an engine dynamic array (FUN_01023184), +0xd8 the floats (as uint32
 * bits), +0xdc their count (swvMorphingMesh_Weights; FUN_01006918 copies them).
 * A SkinnedMesh's (FUN_01010938): +0xf8 set when the skinned buffer must be made again, +0x100 the
 * skinned VertexBuffer. */

/* ---- VertexArray (class 29), the native object (no struct yet) ------------------------------
 * The fields its readers use (GUESS: the names; swvVertexArray_GetComponent, FUN_010257fc,
 * FUN_010258d0, FUN_01025a50):
 *   +0x1c             the vertex count
 *   +0x20             the components per vertex (the transforms take 2 or 3)
 *   +0x24             the bytes per component: 1 (signed bytes) or 2 (signed 16-bit words)
 *   +0x2c             the values, vertex after vertex */

/* ---- PolygonMode (class 20), the native object (no struct yet) --------------------------------
 * +0x1c, its flags word (GUESS: the names, JSR-184 PolygonMode; swvPolygonMode_SetFlags and the
 * setters):
 *   0x007             culling: 1 CULL_BACK, 2 CULL_FRONT, 4 CULL_NONE (0xa0, 0xa1, 0xa2)
 *   0x018             winding: 8 WINDING_CCW, 0x10 WINDING_CW (0xa8, 0xa9)
 *   0x060             shading: 0x20 SHADE_FLAT, 0x40 SHADE_SMOOTH (0xa4, 0xa5)
 *   0x180             two-sided lighting: 0x80 off, 0x100 on
 *   0x200 / 0x400     local camera lighting / perspective correction (on when set)
 * The names of the last three (GUESS, but firm): the BREW-facing slots 18 - 27 are exactly JSR-184 1.1's
 * twelve PolygonMode methods less the two it adds ("Since M3G 1.1": isLocalCameraLightingEnabled and
 * isPerspectiveCorrectionEnabled), i.e. 1.0's ten (kh_types.h SwervePolygonModeVtbl: only two-sided
 * lighting has a getter, swvPolygonMode_TwoSidedLighting), and the M3G reader swvM3G_ReadPolygonMode reads
 * them in the file format's order (M3G file format 11.20: culling, shading, winding, then the three
 * flags). The values are JSR-184 1.1's (CULL_BACK 160 ... WINDING_CW 169). */

/* ---- Material (class 15), the native object (no struct yet) ------------------------------------
 * Its colours (GUESS: the names, JSR-184 Material; swvMaterial_Color, swvMaterial_SetColorValue), ARGB
 * words, by target (JSR-184 1.1, Material: AMBIENT 0x400, DIFFUSE 0x800, EMISSIVE 0x1000, SPECULAR
 * 0x2000; setColor takes an OR of them, and keeps the alpha of the diffuse colour only):
 *   +0x1c             the ambient colour (stored without its alpha)
 *   +0x20             the diffuse colour (the only one with its alpha)
 *   +0x24             the emissive colour (without its alpha)
 *   +0x28             the specular colour (without its alpha) */

/* ---- Image2D (class 10), the native object (no struct yet) -------------------------------------
 * The fields its accessors read (GUESS: the names; swvImage2D_AlphaStride, _ColourStride,
 * _AlphaPlane, _StorageFormat, _Width, _Height, _Palette, _Indices):
 *   +0x20             the data: the RGB565 pixels, then (at +0x3c) the alpha plane; for a palettised
 *                     image the palette (+0x2c) and the indices (+0x30) instead of the pixels
 *   +0x2c             the palette's offset in the data (RGB565, at most 256 entries), -1 when none; its
 *                     alpha is then the alpha plane, a byte an entry
 *   +0x30             the index plane's offset in the data (a byte a pixel), -1 when none
 *   +0x34             the width (swvImage2D_Width), also the row pitch in pixels (the colour rows are
 *                     twice it in bytes, the alpha rows it)
 *   +0x38             the height (swvImage2D_Height)
 *   +0x3c             the alpha plane's offset in the data, -1 when there is none
 *   +0x40             the JSR-184 format (SwerveImageFormat: ALPHA 0x60, LUMINANCE 0x61, LUMINANCE_ALPHA
 *                     0x62, RGB 0x63, RGBA 0x64; swvImage2D_BytesPerPixel gives the bytes a pixel)
 *   +0x44             mutable (FUN_0102035c, Graphics3D.bindTarget of an Image2D, wants it)
 *   +0x48             a colour buffer FUN_0100800c allocates (width * height words; GUESS: a work copy),
 *                     an engine dynamic array (+0x4c the items); FUN_01007f8c / FUN_01023e44 fill it
 *                     from a second plane after the pixels (two bytes a pixel)
 *   +0x54 / +0x58     the log2 of the width and the height (FUN_01018460 checks the sizes against them)
 * Its vtable (offsets from the table, like every engine vtable): +0x24 / +0x28 the width and height
 * (GUESS: getWidth / getHeight, swvImage2D_GetWidth / GetHeight), +0x30 the pixels (swvImage2D_Pixels
 * calls it; the BREW-facing slot 25, swvImage2D_GetPixels, returns them). A Texture2D's image (its +0x2c;
 * swvTexture2D_SetImage, JSR-184 1.1 Texture2D.setImage, and the loader's swvM3G_ReadTexture2D) must have
 * a width and height that are powers of two (swv_IsPowerOfTwo) up to 1024 (the engine's maximum; the spec
 * leaves it to the implementation); the texture's +0x24 the blend colour, +0x28 the blending, +0x30 /
 * +0x34 the wrapping S / T, +0x38 the level filter, +0x3c the image filter (JSR-184's values). */

/* ---- Background (class 4), the native object (no struct yet) ---------------------------------
 * The fields the Background clear (FUN_01005104, GUESS) reads (GUESS: the names, from JSR-184):
 *   +0x1c             the colour, ARGB (alpha >> 24 into the alpha buffer, the rest as RGB565)
 *   +0x20             the image (an Image2D, or NULL)
 *   +0x24 / +0x28     the x and y image modes: BORDER 0x20, REPEAT 0x21
 *   +0x2c .. +0x38    the crop rectangle: x, y, width, height (floats)
 *   +0x3c / +0x40     the colour clear and the depth clear enables, as the clear uses them (+0x3c
 *                     gates the colour, +0x40 the depth). GUESS, a latent engine bug:
 *                     swvM3G_ReadBackground stores the M3G record's depthClearEnabled at +0x3c and
 *                     colorClearEnabled at +0x40 (M3G file format, Background: depth first), so a
 *                     loaded Background has the two swapped */

/* ---- the M3G reader, the Loader's stream parser (no struct yet) ------------------------------------
 * 0xe8 bytes (swvM3GReader_New / swvM3GReader_Construct); its engine vtables 0x01002410 at +0 and
 * 0x01002438 at +4. Its slots: +0x04 swvM3GReader_Begin, +0x08 swvM3GReader_Feed, +0x0c
 * swvM3GReader_End, +0x10 swvM3GReader_Fail, +0x14 swvM3GReader_State, +0x18 the record reader
 * (FUN_010157e8), +0x24 FUN_0102da68 (+0xd8 above 0). Its fields (GUESS: the names; the file format's
 * parts, M3G file format sections 5 - 7, from swvM3GReader_Feed and FUN_010157e8):
 *   +0x0c             the first error code (-1 while there is none; swvM3GReader_Fail)
 *   +0x10             the current section's reader (swvSection_CreateStored / swvSection_CreateZlib)
 *   +0x14             0 for an M3G file identifier, 1 for Swerve's own ("\xbbSWERVE\xab\r\n\x1a\n")
 *   +0x18             swvM3GReader_Begin's argument (non-zero: Swerve's identifier and the types
 *                     23, 24 allowed)
 *   +0x1c             the header's TotalFileSize (section 10.1; -1 before it)
 *   +0x24             the parser's own state (1 the file identifier, 2 a section's compression byte, ...)
 *   +0x28             the section index (-1 before the first): 0 takes only the header object, 1 the
 *                     external references when the header has them (sections 4, 10.1, 10.2)
 *   +0x2c             the bytes read
 *   +0x30 / +0x34     the section's TotalSectionLength / UncompressedLength (sections 6.2, 6.3)
 *   +0x38 / +0x3c     the section's Checksum read / the Adler-32 computed (section 6.5)
 *   +0x40             the Objects' bytes still to read (TotalSectionLength - 13)
 *   +0x44             the object bytes the record reader took (must equal +0x34)
 *   +0x48 / +0x54     the two file identifiers (section 5; 12 bytes each)
 *   +0x64             the read's state: 0 new, 1 begun, 2 reading, 3 ended, 4 failed
 *   +0x70 .. +0x7c    the record reader's state, ObjectType byte, Length and record buffer (section 7) */

/* ---- the lighting colour ---------------------------------------------------------------------------
 * Three int32, red, green, blue, in 8.8 fixed point (0x100 is 1.0; no struct yet). Made from the RGB
 * bytes of an ARGB word by swv_ColourFromRGB (0xff gives 0x100), worked on by swv_ColourAdd,
 * swv_ColourModulate, swv_ColourScale (by a 16.16 factor) and swv_ColourClamp (to 0 .. 1.0), and
 * packed into an RGB565 pixel by swv_ColourToRGB565. */

/* ---- an integer rectangle ------------------------------------------------------------------
 * The engine's (BREW's AEERect has 16-bit fields): the renderer's target, clip and viewport, cut by
 * swv_RectIntersect. GUESS: the names. */
typedef struct SwvRect {
    int32    x;              /* +0x00 */
    int32    y;              /* +0x04 */
    int32    width;          /* +0x08 */
    int32    height;         /* +0x0c */
} SwvRect;

/* ---- the software rasteriser's context (no struct yet) --------------------------------------
 * The fields the triangle code is known to use (GUESS: the names):
 *   +0x04             the span's y (its parity picks the dither row)
 *   +0x08 / +0x0c     the span's rows of the colour buffer (RGB565) and the z-buffer, 16 bits a pixel
 *   +0x10 / +0xdc     the span's first x and its end
 *   +0x1c / +0x4c     the depth at the first pixel (compared as >> 12) and its step per pixel
 *   +0x38 .. +0x40    the red, green, blue the Gouraud span routines interpolate (16.16, 1.0 = 0x10000)
 *   +0x44             the alpha (0xff00 = opaque; swv_SpanFillGouraudAlpha, swv_SpanFillGeneric)
 *   +0x68 .. +0x74    the steps per pixel of red, green, blue and alpha
 *   +0x148 .. +0x154  4 RGB565 pixels (a word each): the flat colour's 2x2 dither (swv_SetupFlatDither),
 *                     word (x & 1) + (y & 1) * 2 (swv_SpanFillFlatDithered)
 *   +0x158 / +0x18c   the image format of texture unit 0 / 1 (a unit is 0x34 bytes): the JSR-184
 *                     Image2D RGB 99, RGBA 100; 0x5f when the unit is unused (GUESS)
 *   +0x15c / +0x190   the texture blending of unit 0 / 1: the JSR-184 Texture2D FUNC_ADD 0xe0,
 *                     BLEND 0xe1, DECAL 0xe2, MODULATE 0xe3, REPLACE 0xe4
 *   +0x258            the flags: 1 colour write, 2 smooth shading (cleared when the three vertex
 *                     colours are equal), 4 textured, 0x20 depth test, 0x40 depth write, 0x800 alpha
 *                     write (0x200, 0x400 not identified)
 *   +0x25c            the alpha threshold (a pixel is drawn where alpha >> 8 >= it)
 *   +0x260 / +0x264   the 8-bit alpha buffer and its row stride (written with flag 0x800)
 *   +0x268            the blending: the JSR-184 CompositingMode ALPHA 0x40, ALPHA_ADD 0x41, MODULATE
 *                     0x42, MODULATE_X2 0x43, REPLACE 0x44
 *   +0x27c            the colour buffer (RGB565); a span's row (+0x08) is +0x27c + +0x288 * y
 *   +0x280 / +0x284   the target's width and height (swv_FillRect clips to them)
 *   +0x288            the colour buffer's row stride, in bytes
 *   +0x290 .. +0x298  the triangle's three vertices (swv_RasterTriangle); a vertex is 0x3c bytes, its
 *                     +0x0c / +0x10 / +0x14 the red, green, blue in 16.16 (1.0 = 0x10000),
 *                     +0x18 the alpha (a byte)
 *   +0x2b8            the span routine swv_RasterTriangleSetup picked (swv_SpanFillGeneric,
 *                     swv_SpanFillFlatDithered, swv_SpanFillGouraud, swv_SpanFillGouraudAlpha,
 *                     swv_SpanFillTextured, FUN_0100bb68, FUN_0100ac0c, FUN_0100c92c) */

/* ---- the engine's static vtables ---------------------------------------------------------------
 * 65 tables at 0x01001dac - 0x01002890 (the constructors store them; each word an offset from the table
 * to the method, some to this-adjusting thunks, sub r0, r0, #n / b, kept among the tables). All but
 * three are small classes (5 slots or fewer: GUESS the containers, slot +4 FUN_01023420 in most); the
 * scene objects' (Camera, Image2D, Group, ...) are not among them (GUESS: not static), so a virtual call
 * on one is not resolved by these tables.
 * The renderer's (0x01002398; constructor FUN_01028d2c, GUESS JSR-184 Graphics3D's implementation):
 *   +0x00 0x0102ad0c the destructor          +0x1c FUN_01021d50
 *   +0x04 FUN_01005eb8                       +0x20 FUN_0101d01c
 *   +0x08 FUN_01024058                       +0x24 FUN_0101a380 (GUESS: render a node)
 *   +0x0c 0x010266b0                         +0x28 FUN_0101d21c (GUESS: render a World)
 *   +0x10 0x01023c60                         +0x2c swvRenderer_Kind (returns 2)
 *   +0x14 FUN_01005104 (the Background clear) +0x30 FUN_0101a89c
 *   +0x18 FUN_010204ec
 * Its target, clip and viewport fields (GUESS: the names; each rectangle an SwvRect):
 *   +0x0c             the target's rectangle: 0, 0, its width and height (swv_Graphics3D_bindTarget,
 *                     FUN_0102035c)
 *   +0x1c / +0x20     the target's row stride (bytes) and pixels (RGB565)
 *   +0x24             the clip (FUN_01020b64)
 *   +0x34             the target cut to the clip (swv_RectIntersect); +0x44 the address of its first
 *                     pixel, 0 when it is empty
 *   +0x48             the viewport (FUN_01023bc8: its width and height 1 .. 1024, else -1301)
 *   +0x58 / +0x5c     the viewport's x, y less +0x34's; +0x60 / +0x64 its width and height
 *   +0x68             1 when the viewport is cut by the clipped target (+0x6c is not all of it)
 *   +0x6c             the clipped target cut to the viewport (FUN_01026548); +0x80 1 when not empty
 *   +0x7c             1 when +0x6c must be made again (FUN_01020b64, FUN_01023bc8 set it;
 *                     FUN_01026548 clears it)
 *   +0x84             an RGBA image target (FUN_0102035c); +0x88 / +0x8c its alpha plane's stride
 *                     and the plane; +0x90 the image's +0x4c (for the image vtable +0x2c's 0x18)
 * The two other long ones: 0x01002410 (10 slots) and 0x010027d8 (7, thunks and methods Ghidra has no
 * function for). */

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
