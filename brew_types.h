/*
 * brew_types.h - BREW SDK types as used by kh.mod and swv21brew.mod.
 *
 * Generated from khvcemu's own tables (khvcemu/helpers.py HELPER_SLOTS and each interface
 * class's SLOTS tuple), so vtable order matches the emulator exactly. Signatures follow
 * research_notes/brew_hle_reference.md. A slot whose signature is not known is declared as
 * `int (*Name)(IFoo *po, ...)` and marked "signature unknown".
 *
 * Written to be accepted by Ghidra's File > Parse C Source: no includes, no macros.
 * ARM AAPCS, little-endian, 32-bit pointers.
 *
 * GUESS markers: any name not taken from the BREW SDK (or not confirmed by how the game uses
 * it) carries a "GUESS:" comment with the evidence.
 */

#ifndef BREW_TYPES_H
#define BREW_TYPES_H

/* ---- scalar types (AEEStdDef.h) -------------------------------------------------------- */
typedef unsigned char      uint8;
typedef signed char        int8;
typedef unsigned short     uint16;
typedef short              int16;
typedef unsigned long      uint32;
typedef long               int32;
typedef unsigned char      boolean;
typedef unsigned short     AECHAR;        /* UTF-16LE, zero-terminated */
typedef unsigned long      AEECLSID;
typedef unsigned short     AEEEvent;      /* event codes, see AEEEventCode below */
typedef unsigned long      RGBVAL;        /* 0xBBGGRR00 */
typedef unsigned long      NativeColor;   /* RGB565 in the low 16 bits on this target */
typedef int                AEEFont;       /* 0x8000 normal, 0x8001 bold, 0x8002 large */
typedef int                AEERasterOp;   /* see AEERasterOpValue */
typedef int                OpenFileMode;  /* 1 READ, 2 READWRITE, 4 CREATE, 8 APPEND */
typedef int                FileSeekType;  /* 0 START, 1 END, 2 CURRENT */
typedef int                AEEMediaSeek;
typedef char *             AEEVaList;      /* pointer to the arguments in memory */

/* ---- enums for readability ------------------------------------------------------------- */
typedef enum AEEEventCode {
    EVT_APP_START        = 0x0,
    EVT_APP_STOP         = 0x1,
    EVT_APP_SUSPEND      = 0x2,
    EVT_APP_RESUME       = 0x3,
    EVT_APP_CONFIG       = 0x4,
    EVT_APP_HIDDEN_CONFIG= 0x5,
    EVT_APP_BROWSE_URL   = 0x6,
    EVT_APP_BROWSE_FILE  = 0x7,
    EVT_APP_MESSAGE      = 0x8,
    EVT_KEY              = 0x100,
    EVT_KEY_PRESS        = 0x101,
    EVT_KEY_RELEASE      = 0x102,
    EVT_FLIP             = 0x405,   /* GUESS: BREW EVT_FLIP; kh_HandleEvent just returns TRUE for it */
    EVT_NOTIFY           = 0x500    /* GUESS: BREW EVT_NOTIFY range; kh_HandleEvent checks GetAEEVersion
                                       there and calls a display method - meaning not confirmed */
} AEEEventCode;

typedef enum AEEErrorCode {
    SUCCESS = 0, EFAILED = 1, ENOMEMORY = 2, ECLASSNOTSUPPORT = 3, EBADPARM = 14,
    EUNSUPPORTED = 20, EITEMBUSY = 32, EFILEEXISTS = 0x101, EFILENOEXISTS = 0x102,
    EBADFILENAME = 0x104
} AEEErrorCode;

/* Operation code for AEEHelperFuncs::f_op (slot 37). GUESS: numbering, see the f_op comment. */
typedef enum FloatOperationType {
    FO_ADD = 0, FO_SUB = 1, FO_MUL = 2, FO_DIV = 3
} FloatOperationType;

typedef enum AEERasterOpValue {
    AEE_RO_OR = 0, AEE_RO_XOR = 1, AEE_RO_COPY = 2, AEE_RO_NOT = 3, AEE_RO_MERGENOT = 4,
    AEE_RO_ANDNOT = 5, AEE_RO_TRANSPARENT = 6, AEE_RO_MASK = 7
} AEERasterOpValue;

typedef enum AVKType {
    AVK_0 = 0xE021, AVK_1 = 0xE022, AVK_2 = 0xE023, AVK_3 = 0xE024, AVK_4 = 0xE025,
    AVK_5 = 0xE026, AVK_6 = 0xE027, AVK_7 = 0xE028, AVK_8 = 0xE029, AVK_9 = 0xE02A,
    AVK_STAR = 0xE02B, AVK_POUND = 0xE02C, AVK_POWER = 0xE02D, AVK_END = 0xE02E,
    AVK_SEND = 0xE02F, AVK_CLR = 0xE030, AVK_UP = 0xE031, AVK_DOWN = 0xE032,
    AVK_LEFT = 0xE033, AVK_RIGHT = 0xE034, AVK_SELECT = 0xE035, AVK_SOFT1 = 0xE036,
    AVK_SOFT2 = 0xE037
} AVKType;

typedef enum AEEClassId {
    AEECLSID_DISPLAY    = 0x01001001,
    AEECLSID_FILEMGR    = 0x01001003,
    AEECLSID_DIB        = 0x01001045,
    AEECLSID_GRAPHICS   = 0x01002001,
    AEECLSID_WEB        = 0x01005000,
    AEECLSID_MEDIA      = 0x01005500,
    AEECLSID_MEDIAMIDI  = 0x01005501,
    AEECLSID_MEDIAMP3   = 0x01005502,
    AEECLSID_MEDIAQCP   = 0x01005503,
    AEECLSID_MEDIAPMD   = 0x01005504,
    AEECLSID_MEDIAADPCM = 0x0100550A,
    AEECLSID_MEDIAPCM   = 0x01005511,
    AEECLSID_FONT_GUESS = 0x0100a004,   /* GUESS: a font class; kh.mod asks for it at start-up and
                                           copes when CreateInstance fails (README.md:510) */
    AEECLSID_KH_APPLET  = 0x01026191,   /* kh.mod's applet (dumps/mif/11839.mif) */
    AEECLSID_SWERVE     = 0x0102bbfc    /* swv21brew.mod's exported class (dumps/mif/14957.mif) */
} AEEClassId;

/* ---- forward declarations ---------------------------------------------------------------- */

typedef struct IShell IShell;
typedef struct IDisplay IDisplay;
typedef struct IBitmap IBitmap;
typedef struct IGraphics IGraphics;
typedef struct IImage IImage;
typedef struct IFileMgr IFileMgr;
typedef struct IFile IFile;
typedef struct IMedia IMedia;
typedef struct IWeb IWeb;
typedef struct IWebResp IWebResp;
typedef struct ISource ISource;
typedef struct IModule IModule;
typedef struct IApplet IApplet;
typedef struct IHeap IHeap;
typedef struct IBitmap IDIB;   /* IDIB extends IBitmap; same vtable, same object layout */

/* ---- plain data structures ----------------------------------------------------------------- */
typedef struct AEERect  { int16 x; int16 y; int16 dx; int16 dy; } AEERect;
typedef struct AEEPoint { int16 x; int16 y; } AEEPoint;

/* IGraphics shape records. GUESS: field layouts inferred from kh.mod's call sites
   (graphics.py / brew_hle_reference.md section 6), not from the SDK headers. */
typedef struct AEELine     { int16 sx; int16 sy; int16 ex; int16 ey; } AEELine;
typedef struct AEECircle   { int16 cx; int16 cy; int16 r; } AEECircle;
typedef struct AEEArc      { int16 cx; int16 cy; int16 r; int16 startAngle; int16 arcAngle; } AEEArc;
typedef struct AEEEllipse  { int16 cx; int16 cy; int16 wx; int16 wy; } AEEEllipse;
typedef struct AEETriangle { AEEPoint p0; AEEPoint p1; AEEPoint p2; } AEETriangle;
typedef struct AEEPolygon  { int16 len; int16 pad; AEEPoint *points; } AEEPolygon;
typedef struct AEEPolygon  AEEPolyline;

typedef void (*PFNNOTIFY)(void *pData);
typedef int  (*PFNQSORTCMP)(const void *a, const void *b);
typedef void (*PFNIMAGEINFO)(void *pUser, IImage *pImage, void *pii, int nErr);

typedef struct AEECallback AEECallback;
struct AEECallback {
    AEECallback *pNext;        /* +0  */
    void        *pmc;          /* +4  */
    PFNNOTIFY    pfnCancel;    /* +8  written by ISHELL_Resume */
    void        *pCancelData;  /* +12 */
    PFNNOTIFY    pfnNotify;    /* +16 */
    void        *pNotifyData;  /* +20 */
    void        *pReserved;    /* +24 */
};

/* dwParam of EVT_APP_START */
typedef struct AEEAppStart {
    int32     error;           /* +0  */
    AEECLSID  clsApp;          /* +4  */
    IDisplay *pDisplay;        /* +8  */
    AEERect   rc;              /* +12 */
    const char *pszArgs;       /* +20 */
} AEEAppStart;

/* ISHELL_GetDeviceInfo. Only the fields khvcemu fills are named; the rest is padding. */
typedef struct AEEDeviceInfo {
    uint16 cxScreen;           /* +0  */
    uint16 cyScreen;           /* +2  */
    uint16 cxAltScreen;        /* +4  */
    uint16 cyAltScreen;        /* +6  */
    uint16 cxScrollBar;        /* +8  */
    uint16 wEncoding;          /* +10 */
    uint16 wMenuTextScroll;    /* +12 */
    uint16 nColorDepth;        /* +14 */
    uint32 wMenuImageDelay;    /* +16 */
    uint32 dwRAMLegacy;        /* +20 */
    uint32 dwRAM;              /* +24 */
    uint32 reserved28;         /* +28 */
    uint32 reserved32;         /* +32 */
    uint32 dwLang;             /* +36 */
    uint32 reserved40;         /* +40 */
    uint16 wStructSize;        /* +44 requested size on input */
    uint16 reserved46;
    uint32 reserved48[4];      /* +48 .. +63 */
} AEEDeviceInfo;

typedef struct AEEBitmapInfo { uint32 cx; uint32 cy; uint32 nDepth; } AEEBitmapInfo;

typedef struct AEEImageInfo {
    uint16 cx;                 /* +0 */
    uint16 cy;                 /* +2 */
    uint16 nColors;            /* +4 */
    boolean bAnimated;         /* +6 */
    uint8  pad7;
    uint16 cxFrame;            /* +8 */
} AEEImageInfo;

typedef struct FileInfo {
    uint8  attrib;             /* +0  0x10 = folder */
    uint8  pad1[3];
    uint32 dwCreationDate;     /* +4  */
    uint32 dwSize;             /* +8  */
    char   szName[64];         /* +12 */
} FileInfo;

typedef struct AEEMediaData { uint32 clsData; void *pData; uint32 dwSize; } AEEMediaData;

typedef struct AEEMediaCmdNotify {
    AEECLSID clsMedia;         /* +0  */
    IMedia  *pIMedia;          /* +4  */
    int      nCmd;             /* +8  4 = PLAY */
    int      nSubCmd;          /* +12 */
    int      nStatus;          /* +16 1 START, 2 DONE, 3 ABORT */
    void    *pCmdData;         /* +20 */
    uint32   dwSize;           /* +24 */
} AEEMediaCmdNotify;
typedef void (*PFNMEDIANOTIFY)(void *pUser, AEEMediaCmdNotify *pCmdNotify);

typedef struct WebOpt { int32 nId; void *pVal; } WebOpt;
typedef struct WebRespInfo {
    int      nCode;            /* +0 */
    ISource *pisMessage;       /* +4 */
    int32    lContentLength;   /* +8 */
    uint32   reserved[5];
} WebRespInfo;

/* ---- AEEHelperFuncs: the table passed to AEEMod_Load in r1 and kept at module base - 4 ---- */
typedef struct AEEHelperFuncs {
    /*   0 +0x000 */ void * (*memmove)(void *dst, const void *src, uint32 n);
    /*   1 +0x004 */ void * (*memset)(void *dst, int c, uint32 n);
    /*   2 +0x008 */ char * (*strcpy)(char *dst, const char *src);
    /*   3 +0x00c */ char * (*strcat)(char *dst, const char *src);
    /*   4 +0x010 */ int (*strcmp)(const char *a, const char *b);
    /*   5 +0x014 */ uint32 (*strlen)(const char *s);
    /*   6 +0x018 */ char * (*strchr)(const char *s, int ch);
    /*   7 +0x01c */ char * (*strrchr)(const char *s, int ch);
    /*   8 +0x020 */ int (*sprintf)(char *dst, const char *fmt, ...);
    /*   9 +0x024 */ AECHAR * (*wstrcpy)(AECHAR *dst, const AECHAR *src);
    /*  10 +0x028 */ AECHAR * (*wstrcat)(AECHAR *dst, const AECHAR *src);
    /*  11 +0x02c */ int (*wstrcmp)(const AECHAR *a, const AECHAR *b);
    /*  12 +0x030 */ int (*wstrlen)(const AECHAR *s);
    /*  13 +0x034 */ AECHAR * (*wstrchr)(const AECHAR *s, AECHAR ch);
    /*  14 +0x038 */ AECHAR * (*wstrrchr)(const AECHAR *s, AECHAR ch);
    /*  15 +0x03c */ int (*wsprintf)(AECHAR *dst, int nDstBytes, const AECHAR *fmt, ...);
    /*  16 +0x040 */ AECHAR * (*strtowstr)(const char *src, AECHAR *dst, int nDstBytes);
    /*  17 +0x044 */ char * (*wstrtostr)(const AECHAR *src, char *dst, int nDstBytes);
    /*  18 +0x048 */ double (*wstrtofloat)(const AECHAR *s);
    /*  19 +0x04c */ int (*floattowstr)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /*  20 +0x050 */ int (*utf8towstr)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /*  21 +0x054 */ int (*wstrtoutf8)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /*  22 +0x058 */ AECHAR * (*wstrlower)(AECHAR *s);
    /*  23 +0x05c */ AECHAR * (*wstrupper)(AECHAR *s);
    /*  24 +0x060 */ int (*chartype)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /*  25 +0x064 */ int (*SetupNativeImage)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /*  26 +0x068 */ void * (*malloc)(uint32 size);
    /*  27 +0x06c */ void (*free)(void *p);
    /*  28 +0x070 */ AECHAR * (*wstrdup)(const AECHAR *s);
    /*  29 +0x074 */ void * (*realloc)(void *p, uint32 size);
    /*  30 +0x078 */ int (*wwritelongex)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /*  31 +0x07c */ int (*wstrsize)(const AECHAR *s);
    /*  32 +0x080 */ AECHAR * (*wstrncopyn)(AECHAR *dst, int nDstChars, const AECHAR *src, int nCount);
    /*  33 +0x084 */ int (*OEMStrLen)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /*  34 +0x088 */ int (*OEMStrSize)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /*  35 +0x08c */ uint32 (*GetAEEVersion)(char *buf, int n);
    /*  36 +0x090 */ int (*atoi)(const char *s);
    /*
     * f_op - BREW floating-point arithmetic helper (AEEHelperFuncs slot 37, byte offset +0x94)
     * =====================================================================================
     *
     * Why it exists
     *   BREW handsets of this era are ARM cores without an FPU, so every float/double operation is
     *   done in software. A compiler's soft-float library normally keeps a writable status word
     *   (rounding mode, sticky exception flags) in static data, and BREW modules are built
     *   position-independent with no writable statics. The SDK therefore offers the arithmetic as
     *   helpers implemented by the OS, reached through AEEStdLib.h macros of the form
     *       FADD(a, b) / FSUB(a, b) / FMUL(a, b) / FDIV(a, b)  ->  GET_HELPER()->f_op(a, b, <op>)
     *   (macro names from the SDK convention; the exact enum spelling is not confirmed here).
     *   Related slots of the same family: 38 f_cmp, 96 f_calc, 88 f_assignstr, 89 f_assignint,
     *   107 f_toint, 108 f_get. GUESS (from the names only): f_cmp compares two doubles with a
     *   comparison code and returns a boolean; f_calc applies a unary function (floor, ceil,
     *   sqrt, ...) to one double; f_assignstr / f_assignint convert a string / an int to double;
     *   f_toint converts a double to int. khvcemu implements none of them: each logs
     *   "[unimpl] helper ..." and returns 0. kh.mod calls none of them except f_op.
     *
     *   kh.mod mostly avoids these helpers: it links its own soft-float routines and keeps their
     *   status word in the applet instead of a static (KHApp+0xd8, reached through
     *   kh_GetAppFieldPtr_d8 = GetAppInstance()+0xd8; the double->float routine at 0x12479c tests
     *   bit 0x800 of it). f_op is called exactly once (below).
     *
     * Calling convention (ARM AAPCS, soft-float, little-endian)
     *   r0:r1   double v1     r0 = low 32 bits of the IEEE-754 binary64 value, r1 = high 32 bits
     *                         (sign, 11-bit exponent, top 20 mantissa bits). Word order confirmed
     *                         from kh.mod's own int->double at 0x125604, which returns the
     *                         sign/exponent word in r1; it also matches khvcemu's strtod/
     *                         wstrtofloat results (helpers.py), which return low:high in r0:r1.
     *   r2:r3   double v2     same layout.
     *   [sp]    nType         FloatOperationType, a 32-bit word on the stack (the 5th argument word,
     *                         because the two doubles fill r0-r3).
     *   result  double        in r0:r1 (low:high). No error channel: the helper cannot fail.
     *
     * Operation codes (FloatOperationType)
     *   0 FO_ADD   v1 + v2
     *   1 FO_SUB   v1 - v2
     *   2 FO_MUL   v1 * v2
     *   3 FO_DIV   v1 / v2
     *   GUESS: the numbering follows the conventional add/sub/mul/div order of the SDK's
     *   FADD/FSUB/FMUL/FDIV macros; it is not confirmed from an SDK header. Evidence for 3 = divide
     *   is the only call site (see below), where a ratio is the only meaningful result.
     *
     * What an implementation should do
     *   1. v1 = bits_to_double(r0 | r1 << 32), v2 = bits_to_double(r2 | r3 << 32), nType = [sp].
     *   2. Compute in IEEE-754 binary64, round-to-nearest-even (what both the handset OS's
     *      soft-float and a host CPU produce for + - * /, so results are bit-exact).
     *   3. Division by zero must not trap: x/0 -> +-infinity with the sign of x XOR the sign of 0,
     *      0/0 and inf/inf -> NaN. (A host language such as Python raises on float division by
     *      zero; handle it explicitly.) NaN inputs propagate as NaN. What the original handset
     *      returned for these edge cases is not known; IEEE behaviour is the safe reading.
     *   4. Unknown nType: no defined result. Log it and return +0.0 (r0 = r1 = 0).
     *   5. Return the result bits low word in r0, high word in r1. Do not touch r2/r3 meaningfully
     *      (caller-saved) and do not write memory.
     *
     * The call in kh.mod (FUN_00107230, case 0xb of a UI/widget draw switch, call at 0x00107718)
     *       a = (double)(int)obj->+0x54;            // 0x125604 int->double
     *       b = (double)(int)obj->+0x58;            // 0x125604 int->double
     *       r = f_op(a, b, 3);                      // a / b
     *       f = (float)r;                           // 0x12479c double->float
     *       w = (float)(int16)obj->rect->dx;        // 0x1268c8 int->float, rect = obj->+0x08 (AEERect)
     *       ... 0x1269cc(w, f) ...                  // GUESS: float multiply -> filled width
     *   GUESS: obj+0x54 / obj+0x58 are a value and its maximum, and the code scales the widget
     *   width by their ratio (a progress or gauge bar). Under khvcemu f_op returns 0, so this
     *   element is drawn as if the ratio were 0 (empty).
     */
    /*  37 +0x094 */ double (*f_op)(double v1, double v2, FloatOperationType nType);
    /*  38 +0x098 */ int (*f_cmp)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /*  39 +0x09c */ void (*dbgprintf)(const char *fmt, ...);
    /*  40 +0x0a0 */ int (*wstrcompress)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /*  41 +0x0a4 */ int32 (*aee_LocalTimeOffset)(boolean *pbDaylight);
    /*  42 +0x0a8 */ void (*aee_GetRand)(uint8 *buf, int n);
    /*  43 +0x0ac */ uint32 (*aee_GetTimeMS)(void);
    /*  44 +0x0b0 */ uint32 (*aee_GetUpTimeMS)(void);
    /*  45 +0x0b4 */ uint32 (*aee_GetSeconds)(void);
    /*  46 +0x0b8 */ int (*aee_GetJulianDate)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /*  47 +0x0bc */ void (*sysfree)(void *p);
    /*  48 +0x0c0 */ void * (*GetAppInstance)(void);
    /*  49 +0x0c4 */ uint32 (*strtoul)(const char *s, char **end, int base);
    /*  50 +0x0c8 */ char * (*strncpy)(char *dst, const char *src, uint32 n);
    /*  51 +0x0cc */ int (*strncmp)(const char *a, const char *b, uint32 n);
    /*  52 +0x0d0 */ int (*stricmp)(const char *a, const char *b);
    /*  53 +0x0d4 */ int (*strnicmp)(const char *a, const char *b, uint32 n);
    /*  54 +0x0d8 */ char * (*strstr)(const char *haystack, const char *needle);
    /*  55 +0x0dc */ int (*memcmp)(const void *a, const void *b, uint32 n);
    /*  56 +0x0e0 */ void * (*memchr)(const void *p, int c, uint32 n);
    /*  57 +0x0e4 */ int (*strexpand)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /*  58 +0x0e8 */ char * (*stristr)(const char *haystack, const char *needle);
    /*  59 +0x0ec */ int (*memstr)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /*  60 +0x0f0 */ int (*wstrncmp)(const AECHAR *a, const AECHAR *b, uint32 n);
    /*  61 +0x0f4 */ char * (*strdup)(const char *s);
    /*  62 +0x0f8 */ boolean (*strbegins)(const char *prefix, const char *s);
    /*  63 +0x0fc */ boolean (*strends)(const char *suffix, const char *s);
    /*  64 +0x100 */ char * (*strchrend)(const char *s, int ch);
    /*  65 +0x104 */ int (*strchrsend)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /*  66 +0x108 */ int (*memrchr)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /*  67 +0x10c */ int (*memchrend)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /*  68 +0x110 */ int (*memrchrbegin)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /*  69 +0x114 */ char * (*strlower)(char *s);
    /*  70 +0x118 */ char * (*strupper)(char *s);
    /*  71 +0x11c */ int (*wstricmp)(const AECHAR *a, const AECHAR *b);
    /*  72 +0x120 */ int (*wstrnicmp)(const AECHAR *a, const AECHAR *b, uint32 n);
    /*  73 +0x124 */ int (*inet_aton)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /*  74 +0x128 */ int (*inet_ntoa)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /*  75 +0x12c */ uint32 (*swapl)(uint32 v);
    /*  76 +0x130 */ uint16 (*swaps)(uint16 v);
    /*  77 +0x134 */ uint32 (*GetFSFree)(uint32 *pdwTotal);
    /*  78 +0x138 */ uint32 (*GetRAMFree)(uint32 *pdwTotal);
    /*  79 +0x13c */ int (*vsprintf)(char *dst, const char *fmt, AEEVaList args);
    /*  80 +0x140 */ int (*vsnprintf)(char *dst, uint32 n, const char *fmt, AEEVaList args);
    /*  81 +0x144 */ int (*snprintf)(char *dst, uint32 n, const char *fmt, ...);
    /*  82 +0x148 */ int (*aee_JulianToSeconds)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /*  83 +0x14c */ uint32 (*strlcpy)(char *dst, const char *src, uint32 n);
    /*  84 +0x150 */ uint32 (*strlcat)(char *dst, const char *src, uint32 n);
    /*  85 +0x154 */ uint32 (*wstrlcpy)(AECHAR *dst, const AECHAR *src, uint32 nChars);
    /*  86 +0x158 */ uint32 (*wstrlcat)(AECHAR *dst, const AECHAR *src, uint32 nChars);
    /*  87 +0x15c */ int (*setstaticptr)(void);
    /*  88 +0x160 */ int (*f_assignstr)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /*  89 +0x164 */ int (*f_assignint)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /*  90 +0x168 */ int (*wwritelong)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /*  91 +0x16c */ int (*dbgheapmark)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /*  92 +0x170 */ void * (*lockmem)(void *p);
    /*  93 +0x174 */ int (*unlockmem)(void *p);
    /*  94 +0x178 */ int (*dumpheap)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /*  95 +0x17c */ double (*strtod)(const char *s, char **end);
    /*  96 +0x180 */ int (*f_calc)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /*  97 +0x184 */ int (*sleep)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /*  98 +0x188 */ int (*getlasterror)(void);
    /*  99 +0x18c */ int (*wgs84_to_degrees)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /* 100 +0x190 */ int (*dbgevent)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /* 101 +0x194 */ boolean (*aee_IsBadPtr)(void *p, uint32 n);
    /* 102 +0x198 */ int (*aee_basename)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /* 103 +0x19c */ int (*aee_makepath)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /* 104 +0x1a0 */ int (*aee_splitpath)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /* 105 +0x1a4 */ boolean (*aee_stribegins)(const char *prefix, const char *s);
    /* 106 +0x1a8 */ uint32 (*aee_GetUTCSeconds)(void);
    /* 107 +0x1ac */ int (*f_toint)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /* 108 +0x1b0 */ int (*f_get)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /* 109 +0x1b4 */ void (*qsort)(void *base, uint32 count, uint32 size, PFNQSORTCMP cmp);
    /* 110 +0x1b8 */ int (*trunc)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /* 111 +0x1bc */ int (*utrunc)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /* 112 +0x1c0 */ int (*err_realloc)(uint32 size, void **pp);
    /* 113 +0x1c4 */ int (*err_strdup)(const char *s, char **pp);
    /* 114 +0x1c8 */ int (*inet_pton)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /* 115 +0x1cc */ int (*inet_ntop)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
    /* 116 +0x1d0 */ int (*GetALSContext)(void *a, ...);   /* signature unknown (not implemented by khvcemu) */
} AEEHelperFuncs;

/* ---- interfaces: struct { vtbl *pvt; } + vtable in khvcemu SLOTS order --------------- */

/* IShell: 52 slots, order from khvcemu/shell.py class Shell. */
typedef struct IShellVtbl {
    /*  0 +0x00 */ uint32 (*AddRef)(IShell *po);
    /*  1 +0x04 */ uint32 (*Release)(IShell *po);
    /*  2 +0x08 */ int (*CreateInstance)(IShell *po, AEECLSID cls, void **ppobj);
    /*  3 +0x0c */ boolean (*QueryClass)(IShell *po, AEECLSID cls, AEECLSID *pOut);
    /*  4 +0x10 */ void (*GetDeviceInfo)(IShell *po, AEEDeviceInfo *pi);
    /*  5 +0x14 */ int (*StartApplet)(IShell *po, AEECLSID cls);
    /*  6 +0x18 */ int (*CloseApplet)(IShell *po, boolean bReturnToIdle);
    /*  7 +0x1c */ boolean (*CanStartApplet)(IShell *po, AEECLSID cls);
    /*  8 +0x20 */ AEECLSID (*ActiveApplet)(IShell *po);
    /*  9 +0x24 */ int (*EnumAppletInit)(IShell *po, ...);   /* signature unknown */
    /* 10 +0x28 */ int (*EnumNextApplet)(IShell *po, ...);   /* signature unknown */
    /* 11 +0x2c */ int (*SetTimer)(IShell *po, int32 dwMSecs, PFNNOTIFY pfn, void *pUser);
    /* 12 +0x30 */ int (*CancelTimer)(IShell *po, PFNNOTIFY pfn, void *pUser);
    /* 13 +0x34 */ uint32 (*GetTimerExpiration)(IShell *po, PFNNOTIFY pfn, void *pUser);
    /* 14 +0x38 */ int (*CreateDialog)(IShell *po, ...);   /* signature unknown */
    /* 15 +0x3c */ int (*GetActiveDialog)(IShell *po, ...);   /* signature unknown */
    /* 16 +0x40 */ int (*EndDialog)(IShell *po, ...);   /* signature unknown */
    /* 17 +0x44 */ int (*LoadResString)(IShell *po, const char *pszResFile, uint16 nResID, AECHAR *pBuff, int nSize);
    /* 18 +0x48 */ void * (*LoadResData)(IShell *po, const char *pszResFile, uint16 nResID, uint16 nType);
    /* 19 +0x4c */ void * (*LoadResObject)(IShell *po, const char *pszResFile, uint16 nResID, AEECLSID cls);
    /* 20 +0x50 */ void (*FreeResData)(IShell *po, void *pData);
    /* 21 +0x54 */ boolean (*SendEvent)(IShell *po, uint32 dwFlags, AEECLSID cls, AEEEvent evt, uint16 wp, uint32 dwp);
    /* 22 +0x58 */ boolean (*Beep)(IShell *po, int nBeep, boolean bLoud);
    /* 23 +0x5c */ int (*GetPrefs)(IShell *po, AEECLSID cls, uint16 wVer, void *pCfg, uint16 nSize);
    /* 24 +0x60 */ int (*SetPrefs)(IShell *po, AEECLSID cls, uint16 wVer, void *pCfg, uint16 nSize);
    /* 25 +0x64 */ int (*GetItemStyle)(IShell *po, ...);   /* signature unknown */
    /* 26 +0x68 */ int (*Prompt)(IShell *po, ...);   /* signature unknown */
    /* 27 +0x6c */ int (*MessageBox)(IShell *po, ...);   /* signature unknown */
    /* 28 +0x70 */ int (*MessageBoxText)(IShell *po, ...);   /* signature unknown */
    /* 29 +0x74 */ int (*SetAlarm)(IShell *po, ...);   /* signature unknown */
    /* 30 +0x78 */ int (*CancelAlarm)(IShell *po, ...);   /* signature unknown */
    /* 31 +0x7c */ int (*AlarmsActive)(IShell *po, ...);   /* signature unknown */
    /* 32 +0x80 */ AEECLSID (*GetHandler)(IShell *po, AEECLSID clsBase, const char *pszMime);
    /* 33 +0x84 */ int (*RegisterHandler)(IShell *po, ...);   /* signature unknown */
    /* 34 +0x88 */ int (*RegisterNotify)(IShell *po, ...);   /* signature unknown */
    /* 35 +0x8c */ int (*Notify)(IShell *po, ...);   /* signature unknown */
    /* 36 +0x90 */ int (*Resume)(IShell *po, AEECallback *pcb);
    /* 37 +0x94 */ int (*ForceExit)(IShell *po, ...);   /* signature unknown */
    /* 38 +0x98 */ int (*GetPosition)(IShell *po, ...);   /* signature unknown */
    /* 39 +0x9c */ int (*CheckPrivLevel)(IShell *po, ...);   /* signature unknown */
    /* 40 +0xa0 */ boolean (*IsValidResource)(IShell *po, const char *pszResFile);
    /* 41 +0xa4 */ void * (*LoadResDataEx)(IShell *po, const char *pszResFile, uint16 nResID, uint16 nType, void *pBuf, uint32 *pnSize);
    /* 42 +0xa8 */ int (*RegisterSystemCallback)(IShell *po, ...);   /* signature unknown */
    /* 43 +0xac */ int (*DetectType)(IShell *po, const void *pBuf, uint32 *pnBufSize, const char *pszName, const char **ppszMime);
    /* 44 +0xb0 */ int (*GetDeviceInfoEx)(IShell *po, ...);   /* signature unknown */
    /* 45 +0xb4 */ int (*GetClassItemID)(IShell *po, ...);   /* signature unknown */
    /* 46 +0xb8 */ int (*Obsolete)(IShell *po, ...);   /* signature unknown */
    /* 47 +0xbc */ int (*GetProperty)(IShell *po, ...);   /* signature unknown */
    /* 48 +0xc0 */ int (*SetProperty)(IShell *po, ...);   /* signature unknown */
    /* 49 +0xc4 */ int (*RegisterEvent)(IShell *po, ...);   /* signature unknown */
    /* 50 +0xc8 */ int (*Reset)(IShell *po, ...);   /* signature unknown */
    /* 51 +0xcc */ int (*AppIsInGroup)(IShell *po, ...);   /* signature unknown */
} IShellVtbl;
struct IShell { const IShellVtbl *pvt; };

/* IDisplay: 26 slots, order from khvcemu/display.py class Display. */
typedef struct IDisplayVtbl {
    /*  0 +0x00 */ uint32 (*AddRef)(IDisplay *po);
    /*  1 +0x04 */ uint32 (*Release)(IDisplay *po);
    /*  2 +0x08 */ int (*GetFontMetrics)(IDisplay *po, AEEFont nFont, int *pnAscent, int *pnDescent);
    /*  3 +0x0c */ int (*MeasureTextEx)(IDisplay *po, AEEFont nFont, const AECHAR *pcText, int nChars, int nMaxWidth, int *pnFits);
    /*  4 +0x10 */ int (*DrawText)(IDisplay *po, AEEFont nFont, const AECHAR *pcText, int nChars, int x, int y, const AEERect *prcBackground, uint32 dwFlags);
    /*  5 +0x14 */ int (*DrawRect)(IDisplay *po, const AEERect *prc, RGBVAL clrFrame, RGBVAL clrFill, uint32 dwFlags);
    /*  6 +0x18 */ int (*BitBlt)(IDisplay *po, int xDest, int yDest, int cxDest, int cyDest, IBitmap *pSrc, int xSrc, int ySrc, AEERasterOp rop);
    /*  7 +0x1c */ void (*Update)(IDisplay *po);
    /*  8 +0x20 */ int (*SetAnnunciators)(IDisplay *po, ...);   /* signature unknown */
    /*  9 +0x24 */ int (*Backlight)(IDisplay *po, ...);   /* signature unknown */
    /* 10 +0x28 */ RGBVAL (*SetColor)(IDisplay *po, int clrItem, RGBVAL clr);
    /* 11 +0x2c */ int (*GetSymbol)(IDisplay *po, ...);   /* signature unknown */
    /* 12 +0x30 */ int (*DrawFrame)(IDisplay *po, ...);   /* signature unknown */
    /* 13 +0x34 */ int (*CreateDIBitmap)(IDisplay *po, IDIB **ppIDIB, uint8 colorDepth, uint16 w, uint16 h);
    /* 14 +0x38 */ IBitmap * (*SetDestination)(IDisplay *po, IBitmap *pDst);
    /* 15 +0x3c */ IBitmap * (*GetDestination)(IDisplay *po);
    /* 16 +0x40 */ int (*GetDeviceBitmap)(IDisplay *po, IBitmap **ppIBitmap);
    /* 17 +0x44 */ void * (*SetFont)(IDisplay *po, AEEFont nFont, void *piFont);
    /* 18 +0x48 */ void (*SetClipRect)(IDisplay *po, const AEERect *prc);
    /* 19 +0x4c */ void (*GetClipRect)(IDisplay *po, AEERect *prc);
    /* 20 +0x50 */ int (*Clone)(IDisplay *po, IDisplay **ppIDisplayNew);
    /* 21 +0x54 */ int (*MakeDefault)(IDisplay *po);
    /* 22 +0x58 */ boolean (*IsEnabled)(IDisplay *po);
    /* 23 +0x5c */ int (*NotifyEnable)(IDisplay *po, ...);   /* signature unknown */
    /* 24 +0x60 */ int (*CreateDIBitmapEx)(IDisplay *po, IDIB **ppIDIB, uint8 colorDepth, uint16 h, uint16 w);
    /* 25 +0x64 */ int (*SetPrefs)(IDisplay *po, ...);   /* signature unknown */
} IDisplayVtbl;
struct IDisplay { const IDisplayVtbl *pvt; };

/* IBitmap: 16 slots, order from khvcemu/display.py class Dib. */
typedef struct IBitmapVtbl {
    /*  0 +0x00 */ uint32 (*AddRef)(IBitmap *po);
    /*  1 +0x04 */ uint32 (*Release)(IBitmap *po);
    /*  2 +0x08 */ int (*QueryInterface)(IBitmap *po, AEECLSID id, void **ppo);
    /*  3 +0x0c */ NativeColor (*RGBToNative)(IBitmap *po, RGBVAL rgb);
    /*  4 +0x10 */ RGBVAL (*NativeToRGB)(IBitmap *po, NativeColor clr);
    /*  5 +0x14 */ int (*DrawPixel)(IBitmap *po, unsigned int x, unsigned int y, NativeColor clr, AEERasterOp rop);
    /*  6 +0x18 */ int (*GetPixel)(IBitmap *po, unsigned int x, unsigned int y, NativeColor *pclr);
    /*  7 +0x1c */ int (*SetPixels)(IBitmap *po, unsigned int cnt, AEEPoint *pPoint, NativeColor clr, AEERasterOp rop);
    /*  8 +0x20 */ int (*DrawHScanline)(IBitmap *po, unsigned int y, unsigned int xMin, unsigned int xMax, NativeColor clr, AEERasterOp rop);
    /*  9 +0x24 */ int (*FillRect)(IBitmap *po, const AEERect *prc, NativeColor clr, AEERasterOp rop);
    /* 10 +0x28 */ int (*BltIn)(IBitmap *po, int xDst, int yDst, int dx, int dy, IBitmap *pSrc, int xSrc, int ySrc, AEERasterOp rop);
    /* 11 +0x2c */ int (*BltOut)(IBitmap *po, int xDst, int yDst, int dx, int dy, IBitmap *pDst, int xSrc, int ySrc, AEERasterOp rop);
    /* 12 +0x30 */ int (*GetInfo)(IBitmap *po, AEEBitmapInfo *pinfo, int nSize);
    /* 13 +0x34 */ int (*CreateCompatibleBitmap)(IBitmap *po, IBitmap **ppIBitmap, uint16 w, uint16 h);
    /* 14 +0x38 */ int (*SetTransparencyColor)(IBitmap *po, NativeColor clr);
    /* 15 +0x3c */ int (*GetTransparencyColor)(IBitmap *po, NativeColor *pclr);
} IBitmapVtbl;
struct IBitmap {                 /* 48-byte object; kh.mod and Swerve read these fields directly */
    const IBitmapVtbl *pvt;      /* +0  */
    void   *pPaletteMap;         /* +4  */
    uint8  *pBmp;                /* +8  pixel buffer */
    uint32 *pRGB;                /* +12 */
    NativeColor ncTransparent;   /* +16 */
    uint16  cx;                  /* +20 */
    uint16  cy;                  /* +22 */
    int16   nPitch;              /* +24 bytes per row */
    uint16  cntRGB;              /* +26 */
    uint8   nDepth;              /* +28 16 */
    uint8   nColorScheme;        /* +29 16 = RGB565 */
    uint8   reserved[18];        /* +30 .. +47 */
};

/* IGraphics: 56 slots, order from khvcemu/graphics.py class Graphics. GUESS: slot names inferred from
   kh.mod's call sites, not from the SDK (graphics.py:1-7). */
typedef struct IGraphicsVtbl {
    /*  0 +0x00 */ uint32 (*AddRef)(IGraphics *po);
    /*  1 +0x04 */ uint32 (*Release)(IGraphics *po);
    /*  2 +0x08 */ RGBVAL (*SetBackground)(IGraphics *po, uint8 r, uint8 g, uint8 b);
    /*  3 +0x0c */ int (*GetBackground)(IGraphics *po, ...);   /* signature unknown */
    /*  4 +0x10 */ RGBVAL (*SetColor)(IGraphics *po, uint8 r, uint8 g, uint8 b, uint8 alpha);
    /*  5 +0x14 */ int (*GetColor)(IGraphics *po, ...);   /* signature unknown */
    /*  6 +0x18 */ boolean (*SetFillMode)(IGraphics *po, boolean bFill);
    /*  7 +0x1c */ boolean (*GetFillMode)(IGraphics *po);
    /*  8 +0x20 */ RGBVAL (*SetFillColor)(IGraphics *po, uint8 r, uint8 g, uint8 b, uint8 alpha);
    /*  9 +0x24 */ int (*GetFillColor)(IGraphics *po, ...);   /* signature unknown */
    /* 10 +0x28 */ uint8 (*SetPointSize)(IGraphics *po, uint8 size);
    /* 11 +0x2c */ int (*GetPointSize)(IGraphics *po, ...);   /* signature unknown */
    /* 12 +0x30 */ int (*SetStrokeStyle)(IGraphics *po, ...);   /* signature unknown */
    /* 13 +0x34 */ int (*GetStrokeStyle)(IGraphics *po, ...);   /* signature unknown */
    /* 14 +0x38 */ int (*SetPaintMode)(IGraphics *po, ...);   /* signature unknown */
    /* 15 +0x3c */ int (*GetPaintMode)(IGraphics *po, ...);   /* signature unknown */
    /* 16 +0x40 */ boolean (*SetViewport)(IGraphics *po, const AEERect *prc, uint32 flags);
    /* 17 +0x44 */ void (*GetViewport)(IGraphics *po, AEERect *prc, uint32 *pflags);
    /* 18 +0x48 */ int (*ClearViewport)(IGraphics *po);
    /* 19 +0x4c */ int (*ClearRect)(IGraphics *po, const AEERect *prc);
    /* 20 +0x50 */ int (*DrawPoint)(IGraphics *po, const AEEPoint *ppt);
    /* 21 +0x54 */ int (*DrawLine)(IGraphics *po, const AEELine *pLine);
    /* 22 +0x58 */ int (*DrawRect)(IGraphics *po, const AEERect *prc);
    /* 23 +0x5c */ int (*DrawCircle)(IGraphics *po, const AEECircle *pCircle);
    /* 24 +0x60 */ int (*DrawArc)(IGraphics *po, const AEEArc *pArc);
    /* 25 +0x64 */ int (*DrawPie)(IGraphics *po, ...);   /* signature unknown */
    /* 26 +0x68 */ int (*DrawEllipse)(IGraphics *po, const AEEEllipse *pEllipse);
    /* 27 +0x6c */ int (*DrawTriangle)(IGraphics *po, const AEETriangle *pTri);
    /* 28 +0x70 */ int (*DrawPolygon)(IGraphics *po, const AEEPolygon *pPoly);
    /* 29 +0x74 */ int (*DrawPolyline)(IGraphics *po, const AEEPolyline *pPoly);
    /* 30 +0x78 */ int (*ClearRectBg)(IGraphics *po, const AEERect *prc);
    /* 31 +0x7c */ int (*slot31)(IGraphics *po, ...);   /* unknown slot */
    /* 32 +0x80 */ int (*Flush)(IGraphics *po);
    /* 33 +0x84 */ int (*slot33)(IGraphics *po, ...);   /* unknown slot */
    /* 34 +0x88 */ int (*slot34)(IGraphics *po, ...);   /* unknown slot */
    /* 35 +0x8c */ int (*slot35)(IGraphics *po, ...);   /* unknown slot */
    /* 36 +0x90 */ int (*slot36)(IGraphics *po, ...);   /* unknown slot */
    /* 37 +0x94 */ int (*slot37)(IGraphics *po, ...);   /* unknown slot */
    /* 38 +0x98 */ int (*slot38)(IGraphics *po, ...);   /* unknown slot */
    /* 39 +0x9c */ int (*slot39)(IGraphics *po, ...);   /* unknown slot */
    /* 40 +0xa0 */ int (*slot40)(IGraphics *po, ...);   /* unknown slot */
    /* 41 +0xa4 */ int (*slot41)(IGraphics *po, ...);   /* unknown slot */
    /* 42 +0xa8 */ int (*slot42)(IGraphics *po, ...);   /* unknown slot */
    /* 43 +0xac */ int (*DrawRoundRect)(IGraphics *po, const AEERect *prc, int16 arcWidth, int16 arcHeight);
    /* 44 +0xb0 */ int (*slot44)(IGraphics *po, ...);   /* unknown slot */
    /* 45 +0xb4 */ int (*slot45)(IGraphics *po, ...);   /* unknown slot */
    /* 46 +0xb8 */ int (*slot46)(IGraphics *po, ...);   /* unknown slot */
    /* 47 +0xbc */ int (*slot47)(IGraphics *po, ...);   /* unknown slot */
    /* 48 +0xc0 */ int (*slot48)(IGraphics *po, ...);   /* unknown slot */
    /* 49 +0xc4 */ int (*slot49)(IGraphics *po, ...);   /* unknown slot */
    /* 50 +0xc8 */ int (*slot50)(IGraphics *po, ...);   /* unknown slot */
    /* 51 +0xcc */ int (*slot51)(IGraphics *po, ...);   /* unknown slot */
    /* 52 +0xd0 */ int (*slot52)(IGraphics *po, ...);   /* unknown slot */
    /* 53 +0xd4 */ int (*slot53)(IGraphics *po, ...);   /* unknown slot */
    /* 54 +0xd8 */ int (*slot54)(IGraphics *po, ...);   /* unknown slot */
    /* 55 +0xdc */ int (*slot55)(IGraphics *po, ...);   /* unknown slot */
} IGraphicsVtbl;
struct IGraphics { const IGraphicsVtbl *pvt; };

/* IImage: 11 slots, order from khvcemu/image.py class Image. */
typedef struct IImageVtbl {
    /*  0 +0x00 */ uint32 (*AddRef)(IImage *po);
    /*  1 +0x04 */ uint32 (*Release)(IImage *po);
    /*  2 +0x08 */ void (*Draw)(IImage *po, int x, int y);
    /*  3 +0x0c */ void (*DrawFrame)(IImage *po, int nFrame, int x, int y);
    /*  4 +0x10 */ void (*GetInfo)(IImage *po, AEEImageInfo *pii);
    /*  5 +0x14 */ void (*SetParm)(IImage *po, int nParm, int p1, int p2);
    /*  6 +0x18 */ void (*Start)(IImage *po, int x, int y);
    /*  7 +0x1c */ void (*Stop)(IImage *po);
    /*  8 +0x20 */ void (*SetStream)(IImage *po, void *ps);
    /*  9 +0x24 */ boolean (*HandleEvent)(IImage *po, AEEEvent evt, uint16 wp, uint32 dwp);
    /* 10 +0x28 */ void (*Notify)(IImage *po, PFNIMAGEINFO pfn, void *pUser);
} IImageVtbl;
struct IImage { const IImageVtbl *pvt; };

/* IFileMgr: 21 slots, order from khvcemu/files.py class FileMgr. */
typedef struct IFileMgrVtbl {
    /*  0 +0x00 */ uint32 (*AddRef)(IFileMgr *po);
    /*  1 +0x04 */ uint32 (*Release)(IFileMgr *po);
    /*  2 +0x08 */ IFile * (*OpenFile)(IFileMgr *po, const char *pszFile, OpenFileMode mode);
    /*  3 +0x0c */ int (*GetInfo)(IFileMgr *po, const char *pszName, FileInfo *pInfo);
    /*  4 +0x10 */ int (*Remove)(IFileMgr *po, const char *pszName);
    /*  5 +0x14 */ int (*MkDir)(IFileMgr *po, const char *pszDir);
    /*  6 +0x18 */ int (*RmDir)(IFileMgr *po, const char *pszDir);
    /*  7 +0x1c */ int (*Test)(IFileMgr *po, const char *pszName);
    /*  8 +0x20 */ uint32 (*GetFreeSpace)(IFileMgr *po, uint32 *pdwTotal);
    /*  9 +0x24 */ int (*GetLastError)(IFileMgr *po);
    /* 10 +0x28 */ int (*EnumInit)(IFileMgr *po, const char *pszDir, boolean bDirs);
    /* 11 +0x2c */ boolean (*EnumNext)(IFileMgr *po, FileInfo *pInfo);
    /* 12 +0x30 */ int (*Rename)(IFileMgr *po, const char *pszSrc, const char *pszDest);
    /* 13 +0x34 */ int (*EnumNextEx)(IFileMgr *po, ...);   /* signature unknown */
    /* 14 +0x38 */ int (*SetDescription)(IFileMgr *po, ...);   /* signature unknown */
    /* 15 +0x3c */ int (*GetInfoEx)(IFileMgr *po, ...);   /* signature unknown */
    /* 16 +0x40 */ int (*Use)(IFileMgr *po, ...);   /* signature unknown */
    /* 17 +0x44 */ int (*GetFileUseInfo)(IFileMgr *po, ...);   /* signature unknown */
    /* 18 +0x48 */ int (*ResolvePath)(IFileMgr *po, ...);   /* signature unknown */
    /* 19 +0x4c */ int (*CheckPathAccess)(IFileMgr *po, ...);   /* signature unknown */
    /* 20 +0x50 */ int (*GetFreeSpaceEx)(IFileMgr *po, ...);   /* signature unknown */
} IFileMgrVtbl;
struct IFileMgr { const IFileMgrVtbl *pvt; };

/* IFile: 12 slots, order from khvcemu/files.py class File. */
typedef struct IFileVtbl {
    /*  0 +0x00 */ uint32 (*AddRef)(IFile *po);
    /*  1 +0x04 */ uint32 (*Release)(IFile *po);
    /*  2 +0x08 */ void (*Readable)(IFile *po, PFNNOTIFY pfn, void *pUser);
    /*  3 +0x0c */ int32 (*Read)(IFile *po, void *pBuffer, uint32 dwCount);
    /*  4 +0x10 */ void (*Cancel)(IFile *po, PFNNOTIFY pfn, void *pUser);
    /*  5 +0x14 */ uint32 (*Write)(IFile *po, const void *pBuffer, uint32 dwCount);
    /*  6 +0x18 */ int (*GetInfo)(IFile *po, FileInfo *pInfo);
    /*  7 +0x1c */ int32 (*Seek)(IFile *po, FileSeekType seek, int32 position);
    /*  8 +0x20 */ int (*Truncate)(IFile *po, uint32 truncate_pos);
    /*  9 +0x24 */ int (*GetInfoEx)(IFile *po, ...);   /* signature unknown */
    /* 10 +0x28 */ int (*SetCacheSize)(IFile *po, ...);   /* signature unknown */
    /* 11 +0x2c */ int (*Map)(IFile *po, ...);   /* signature unknown */
} IFileVtbl;
struct IFile { const IFileVtbl *pvt; };

/* IMedia: 14 slots, order from khvcemu/media.py class Media. */
typedef struct IMediaVtbl {
    /*  0 +0x00 */ uint32 (*AddRef)(IMedia *po);
    /*  1 +0x04 */ uint32 (*Release)(IMedia *po);
    /*  2 +0x08 */ int (*QueryInterface)(IMedia *po, AEECLSID id, void **ppo);
    /*  3 +0x0c */ int (*RegisterNotify)(IMedia *po, PFNMEDIANOTIFY pfn, void *pUser);
    /*  4 +0x10 */ int (*SetMediaParm)(IMedia *po, int nParmID, int32 p1, int32 p2);
    /*  5 +0x14 */ int (*GetMediaParm)(IMedia *po, int nParmID, int32 *pP1, int32 *pP2);
    /*  6 +0x18 */ int (*Play)(IMedia *po);
    /*  7 +0x1c */ int (*Record)(IMedia *po);
    /*  8 +0x20 */ int (*Stop)(IMedia *po);
    /*  9 +0x24 */ int (*Seek)(IMedia *po, AEEMediaSeek eSeek, int32 lTimeMS);
    /* 10 +0x28 */ int (*Pause)(IMedia *po);
    /* 11 +0x2c */ int (*Resume)(IMedia *po);
    /* 12 +0x30 */ int (*GetTotalTime)(IMedia *po);
    /* 13 +0x34 */ int (*GetState)(IMedia *po, boolean *pbStateChanging);
} IMediaVtbl;
struct IMedia { const IMediaVtbl *pvt; };

/* IWeb: 7 slots, order from khvcemu/web.py class Web. */
typedef struct IWebVtbl {
    /*  0 +0x00 */ uint32 (*AddRef)(IWeb *po);
    /*  1 +0x04 */ uint32 (*Release)(IWeb *po);
    /*  2 +0x08 */ int (*QueryInterface)(IWeb *po, AEECLSID id, void **ppo);
    /*  3 +0x0c */ int (*AddOpt)(IWeb *po, WebOpt *awozList);
    /*  4 +0x10 */ int (*RemoveOpt)(IWeb *po, int32 nOptId, int32 nIndex);
    /*  5 +0x14 */ void (*GetResponseV)(IWeb *po, IWebResp **ppiwresp, AEECallback *pcb, const char *cpszUrl, WebOpt *awozList);
    /*  6 +0x18 */ void (*GetResponse)(IWeb *po, IWebResp **ppiwresp, AEECallback *pcb, const char *cpszUrl, ...);
} IWebVtbl;
struct IWeb { const IWebVtbl *pvt; };

/* IWebResp: 7 slots, order from khvcemu/web.py class WebResp. */
typedef struct IWebRespVtbl {
    /*  0 +0x00 */ uint32 (*AddRef)(IWebResp *po);
    /*  1 +0x04 */ uint32 (*Release)(IWebResp *po);
    /*  2 +0x08 */ int (*QueryInterface)(IWebResp *po, AEECLSID id, void **ppo);
    /*  3 +0x0c */ int (*AddOpt)(IWebResp *po, WebOpt *awozList);
    /*  4 +0x10 */ int (*RemoveOpt)(IWebResp *po, int32 nOptId, int32 nIndex);
    /*  5 +0x14 */ int (*GetOpt)(IWebResp *po, int32 nOptId, int32 nIndex, WebOpt *pwo);
    /*  6 +0x18 */ WebRespInfo * (*GetInfo)(IWebResp *po);
} IWebRespVtbl;
struct IWebResp { const IWebRespVtbl *pvt; };

/* ISource: 5 slots, order from khvcemu/web.py class BodySource. */
typedef struct ISourceVtbl {
    /*  0 +0x00 */ uint32 (*AddRef)(ISource *po);
    /*  1 +0x04 */ uint32 (*Release)(ISource *po);
    /*  2 +0x08 */ int (*QueryInterface)(ISource *po, AEECLSID id, void **ppo);
    /*  3 +0x0c */ int32 (*Read)(ISource *po, char *pcBuf, int32 cbBuf);
    /*  4 +0x10 */ void (*Readable)(ISource *po, AEECallback *pcb);
} ISourceVtbl;
struct ISource { const ISourceVtbl *pvt; };

/* ---- IModule / IApplet (AEE.h) and the generic module/applet objects (AEEModGen.c,
        AEEAppGen.c). Layouts confirmed from kh.mod: AEEStaticMod_New @0x1a18 and
        AEEApplet_New @0x1760 build exactly these. ----------------------------------------- */
typedef struct IHeapVtbl { uint32 (*AddRef)(IHeap *po); uint32 (*Release)(IHeap *po); } IHeapVtbl;
struct IHeap { const IHeapVtbl *pvt; };

typedef struct IModuleVtbl {
    /* 0 +0x0 */ uint32 (*AddRef)(IModule *po);
    /* 1 +0x4 */ uint32 (*Release)(IModule *po);
    /* 2 +0x8 */ int    (*CreateInstance)(IModule *po, IShell *pIShell, AEECLSID ClsId, void **ppObj);
    /* 3 +0xc */ void   (*FreeResources)(IModule *po, IHeap *ph, IFileMgr *pfm);
} IModuleVtbl;
struct IModule { const IModuleVtbl *pvt; };

typedef struct IAppletVtbl {
    /* 0 +0x0 */ uint32  (*AddRef)(IApplet *po);
    /* 1 +0x4 */ uint32  (*Release)(IApplet *po);
    /* 2 +0x8 */ boolean (*HandleEvent)(IApplet *po, AEEEvent evt, uint16 wParam, uint32 dwParam);
} IAppletVtbl;
struct IApplet { const IAppletVtbl *pvt; };

typedef int     (*PFNMODCREATEINST)(AEECLSID ClsId, IShell *pIShell, IModule *po, void **ppObj);
typedef void    (*PFNFREEMODDATA)(IModule *po);
typedef void    (*PFNFREEAPPDATA)(IApplet *po);

typedef struct AEEApplet AEEApplet;
typedef boolean (*AEEHANDLER)(AEEApplet *pMe, AEEEvent eCode, uint16 wParam, uint32 dwParam);

/* AEEMod: allocated as nSize + 0x10 bytes; its 4-entry vtable sits at the end (+nSize). */
typedef struct AEEMod {
    const IModuleVtbl *pvt;          /* +0x00 */
    uint32             m_nRefs;      /* +0x04 */
    IShell            *m_pIShell;    /* +0x08 */
    PFNMODCREATEINST   pfnModCrInst; /* +0x0C NULL in kh.mod -> AEEClsCreateInstance */
    PFNFREEMODDATA     pfnModFreeData; /* +0x10 */
} AEEMod;

/* AEEApplet: allocated as nIn + 0x0C bytes (nIn >= 0x20); 3-entry vtable at +nIn.
   The game's own data follows from +0x20 (see kh_mod.h / swv21brew.h). */
struct AEEApplet {
    const IAppletVtbl *pvt;          /* +0x00 */
    AEECLSID           clsID;        /* +0x04 */
    uint32             m_nRefs;      /* +0x08 */
    IShell            *m_pIShell;    /* +0x0C */
    IModule           *m_pIModule;   /* +0x10 */
    IDisplay          *m_pIDisplay;  /* +0x14 */
    AEEHANDLER         pAppHandleEvent; /* +0x18 */
    PFNFREEAPPDATA     pFreeAppData; /* +0x1C */
};

#endif /* BREW_TYPES_H */
