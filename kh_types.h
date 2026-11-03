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
    struct AppContext *context;      /* +0x94 GUESS: name; the object most functions take first
                                        (app_context_create, app_context_destroy) */
    void          *pObj98;           /* +0x98 created by 0x10be14, destroyed by 0x10cda4 */
    struct Animations *animations;   /* +0x9c the scene's animations; created by animations_create,
                                        destroyed by animations_destroy */
    struct Intro  *intro;            /* +0xa0 the opening sequence (intro_create), destroyed by 0x10cd2c */
    void          *pGame;            /* +0xa4 GUESS: game state; receives key releases (kh_OnKeyRelease);
                                        destroyed by 0x10c2c4 */
    struct Progress *progress;       /* +0xa8 the player's progress (munny, experience, level, controls);
                                        created by 0x10b4e4; EVT_APP_MESSAGE handled only while set */
    uint32         field_ac;         /* +0xac */
    uint32         dwStartTimeMS;    /* +0xb0 aee_GetTimeMS() at EVT_APP_START */
    uint32         bStarted;         /* +0xb4 GUESS: set to 1 at EVT_APP_START */
    uint32         bSuspended;       /* +0xb8 GUESS: set to 1 at EVT_APP_SUSPEND */
    uint32         field_bc;         /* +0xbc */
    uint32         field_c0;         /* +0xc0 */
    char          *pBufc4;           /* +0xc4 a heap string (string_replace; freed in kh_OnAppStop): the
                                        level's name ("training", a progress record's name) */
    char          *pBufc8;           /* +0xc8 a heap string (string_replace; freed in kh_OnAppStop): the
                                        script summary's level name, copied to pBufc4 */
    uint32         field_cc;         /* +0xcc */
    struct ScreenStack *screens;     /* +0xd0 the open screens (menus); created by 0x10ac6c(0, pMe),
                                        destroyed by 0x10c3f8. FUN_00101ad8 handles its events */
    uint32         field_d4;         /* +0xd4 */
    uint32         fpStatus;         /* +0xd8 GUESS: soft-float status word (what a compiler fplib keeps in a
                                        static). Address returned by kh_GetFpStatusPtr; read by
                                        kh.mod's double->float at 0x12479c (tests bit 0x800). */
    int32          errnoValue;       /* +0xdc the C library's errno (set_errno, kh_GetErrnoPtr); GUESS: kept here as
                                        BREW modules have no writable statics */
} KHApp;

/* ---- The app's context (GUESS: names) ----------------------------------------------------------------
 * KHApp.context (app_context_create, 0x14 bytes): passed first to most of the game's functions
 * (string_split, string_to_float, the scene loaders, ...), which mostly do not read it. */
typedef struct AppContext {
    int32    type;                  /* +0x00 3 */
    int32    sounds[2];             /* +0x04 two sound sets (FUN_0010bec4's kind, destroyed by FUN_0010ce08);
                                     the Options screen sets their volume (FUN_0010a03c, Progress +0x598) */
    struct KHApp *app;            /* +0x0c */
    ISwerveObject *transform;     /* +0x10 a Swerve Transform (ISwerve::CreateObject) */
} AppContext;                     /* 0x14 bytes */

/* ---- A web request (GUESS: names) ------------------------------------------------------------------
 * The game's HTTP client for its server, http://swervenet.superscape.com/ (web_request_create, 0x5c
 * bytes): downloads (disney/download.php, web_request_download) and rankings (disney/rank.php and
 * rankex.php). The response is read through `callback` (web_request_read), the reply parsed by
 * web_request_parse_reply, and the listener told what happened (web_request_notify). */
typedef void (*WebRequestListener)(int32 context,int32 event,int32 value,int32 detail,int32 extra);
typedef struct WebRequest {
    WebRequestListener listener;  /* +0x00 told about progress, replies and failures (FUN_0010888c) */
    AEECallback callback;         /* +0x04 the IWeb's callback: pfnNotify = web_request_read */
    IWebResp *response;           /* +0x20 the response being read */
    int32    received;              /* +0x24 bytes received so far (the resume position) */
    char    *data;                  /* +0x28 the data received */
    int32    dataSize;              /* +0x2c the size of data */
    int32    started;               /* +0x30 set once the first part of the response was read */
    int32    retries;               /* +0x34 retries so far (web_request_retry); -1 after the last */
    char    *url;                   /* +0x38 the URL of the request */
    char    *baseUrl;               /* +0x3c a download's URL without its position */
    uint32   readCount;             /* +0x40 reads so far; progress is reported every 20 */
    int32    context;               /* +0x44 passed to the listener (the screen stack) */
    int32    state;                 /* +0x48 0 new, 1 idle, 3 downloading, 4 rankex, or the rank state */
    KHApp   *app;                   /* +0x4c */
    IFileMgr *fileMgr;            /* +0x50 created by web_request_download */
    IWeb    *web;                   /* +0x54 */
    IShell  *shell;                 /* +0x58 the app's (the retry timer) */
} WebRequest;                     /* 0x5c bytes */

/* ---- Lists (GUESS: names) ----------------------------------------------------------------------
 * The children of a menu or UI element (for example the list at menu +0x24), kept as two parallel
 * arrays. list_get_entry reads an entry by position (0 when out of range); list_find_entry returns the
 * entry whose id matches; list_set_entry adds or replaces one; list_remove_entry takes one out. The key map of a UIElement (+0x60) is searched the same way. */
typedef struct UIList {
    int32    count;                 /* +0x00 number of entries */
    int32   *ids;                   /* +0x04 one id per entry (the key pickers have ids 400-406) */
    int32   *entries;               /* +0x08 the entries, usually UIElement pointers */
    int32    capacity;              /* +0x0c room in both arrays */
    int32    growBy;                /* +0x10 how much list_set_entry grows them by when they are full */
} UIList;

/* ---- The screen stack (GUESS: names) -------------------------------------------------------------
 * The game's open screens (menus), KHApp.screens. Each screen has its position as its id in the list
 * (0 = the bottom); the top one, id depth - 1, is the one shown (screen_stack_top). Screens have a
 * vtable at +0 whose slots hold self-relative offsets: slot 0 destroys the screen, +0x20 resumes it
 * when it becomes the top again (screen_stack_close_top). */
typedef struct ScreenStack {
    struct KHApp *app;            /* +0x00 */
    uint8  unknown_04[0x04];
    struct TextTable *texts;      /* +0x08 the app's text table (KHApp.pObj98; screen_stack_get_text) */
    IDisplay *display;            /* +0x0c passed to the elements' draw methods (ui_element_draw); GUESS: the
                                     IDisplay */
    IGraphics *graphics;          /* +0x10 what the elements draw with (ui_element_draw, graphics_set_color) */
    AEERect *rect;                /* +0x14 GUESS: name; the display's rectangle: every screen's size
                                     (screen_create) */
    uint8  unknown_18[0x04];
    IImage *frameImages[6];       /* +0x1c the corners of the framed text boxes (text_box_draw): left and
                                     right for style 1, 3 and 2 */
    UIList *screens;              /* +0x34 the open screens, by position */
    int32    depth;                 /* +0x38 how many screens are open */
    struct KeyOption *keyOptions; /* +0x3c GUESS: name; the Controls screen's ring of key options
                                     (key_picker_setup), freed when the screen closes */
    UIList  *keyTexts;              /* +0x40 the key glyphs "0" - "9", "*", "#" (wide), by the ids -1000 -
                                     -1011 (FUN_0010ac6c; screen_stack_get_text) */
    struct UIElement *keyPickers[7]; /* +0x44 GUESS: name; the Controls screen's key pickers (ids 400 -
                                     406), one per Progress.controls[] entry (screen_stack_all_keys_bound) */
    int32    field_60;              /* +0x60 0 when FUN_00101ad8 starts a download for event 100, else 1;
                                     the web reply handler (FUN_0010888c) reads it */
    char    *savedLevelName;        /* +0x64 GUESS: name; a copy of KHApp.pBufc4 made (string_replace)
                                     before pBufc8 replaces it for a download; 0 at creation */
} ScreenStack;                    /* 0x68 bytes (FUN_0010ac6c); only the fields named so far */

/* ---- The text table (GUESS: names) -------------------------------------------------------------------
 * KHApp.pObj98 (FUN_0010be14, 8 bytes): the game's texts by id, read from `source` (FUN_0011448c:
 * its vtable +0x30 copies the text with an id), narrow (text_table_get_text) or wide
 * (text_table_get_wide_text). */
typedef struct TextTable {
    struct KHApp *app;            /* +0x00 */
    int     *source;              /* +0x04 */
} TextTable;

/* ---- The game's UI elements (GUESS: names) ------------------------------------------------------
 * A UIElement is a screen, menu entry or widget, created by FUN_0010bba0 with its type in +0x34.
 * Elements form a tree: each has an id and a parent, and keeps its children in a UIList
 * (ui_element_add_child / ui_element_find_child). Only the fields used by the functions named so far
 * are named; the rest is padding.
 * Type 8 is the key picker of the Controls screen; +0x3c..+0x48 and +0x68 are its own fields. */
typedef struct KeyOption {
    struct KeyOption *previous;   /* +0x00 */
    struct KeyOption *next;       /* +0x04 */
    int32    label;                 /* +0x08 the text shown for it: 0x1484CCBF "undefined", -1000..-1011
                                     the keys 0..9, *, # (GUESS: glyph ids) */
    int32    keyCode;               /* +0x0C AVK_UNDEFINED, AVK_0..AVK_9, AVK_STAR or AVK_POUND */
} KeyOption;                      /* 0x10 bytes; the Controls screen links 13 of them in a ring */

typedef struct UIElement {
    int32    vtable;                /* +0x00 its class's vtable (VTABLE_00101724 for a plain element) */
    uint8  visible;               /* +0x04 drawn only when set (FUN_00107d24); 1 from ui_element_create */
    uint8  unknown_05[0x03];
    AEERect *rect;                /* +0x08 its rectangle (allocated by ui_element_create) */
    int32    id;                    /* +0x0c its id among its parent's children (ui_element_add_child) */
    uint32 primaryColor;          /* +0x10 set by ui_element_handle_key for each type and state; -1: the
                                     parent's (ui_element_get_primary_color) */
    uint32 secondaryColor;        /* +0x14 the fill of its background; -1: the parent's
                                     (ui_element_get_secondary_color) */
    uint32 borderColor;           /* +0x18 the outline of its background; -1: the parent's
                                     (ui_element_get_border_color) */
    uint8  hasBackground;         /* +0x1c FUN_00107d24 paints its rectangle (secondary fill, border outline) */
    uint8  unknown_1d[0x03];
    int32   *owner;                 /* +0x20 the menu (screen) it belongs to; FUN_00101ad8 handles its events */
    UIList *children;             /* +0x24 its children, by id (ui_element_find_child) */
    int32    nextAutomaticId;       /* +0x28 counts down from 0: the ids -1, -2, ... given to children
                                     added without an id (or with one already in use) */
    struct UIElement *parent;     /* +0x2c the element it was added to */
    int32    label;                 /* +0x30 the text element that shows the current value */
    int32    type;                  /* +0x34 2..10; 8 = key picker */
    int32    selectEvent;           /* +0x38 the event sent to the owner when SELECT is pressed */
    KeyOption *options;           /* +0x3c key picker: the ring of options */
    KeyOption *selectedOption;    /* +0x40 key picker: the option shown */
    int32   *setting;               /* +0x44 key picker: the setting it edits (a key code) */
    int32    index;                 /* +0x48 key picker: its row (0..6), passed to FUN_0010a498 on UP / DOWN */
    uint8  enabled;               /* +0x4c GUESS: meaning; a key picker with 0 is drawn all white */
    uint8  unknown_4d[0x03];
    int32   *listener;              /* +0x50 an object (vtable at +0) that gets the keys the element
                                     does not handle itself */
    uint8  unknown_54[0x08];
    uint32 flags;                 /* +0x5c bit 1: keep the colours (no restyling) */
    UIList *keyMap;               /* +0x60 searched with the key code by list_find_entry */
    int32    unknown_64;            /* +0x64 passed to FUN_00105224 with the element found there */
    int32    originalKeyCode;       /* +0x68 key picker: the setting's value when it was set up */
} UIElement;


/* ---- Text boxes and text lines (GUESS: names) -------------------------------------------------------
 * A text box (text_box_create, VTABLE_001016A0) shows a wide text wrapped into text lines
 * (text_box_set_text), a page at a time (UP / DOWN scroll it, text_box_handle_key), in the look of its
 * style (text_style_create). A text line (text_line_create, VTABLE_001016C0) is one line of text in a
 * font, placed in its rectangle by its alignment; the menus also use them as labels. Both start with the
 * UI element's 0x30 bytes (ui_element_create): cast to UIElement for those. */
typedef struct TextStyle {
    int32  type;                  /* +0x00 0 a round-cornered box, 1-3 framed (blue, red, orange), 5 scrolls */
    uint32 alignment;             /* +0x04 of its lines (text_line_draw); bit 0x20 lines from the top, 0x10
                                     from the bottom, else centred (text_box_layout); 9 by default */
    int32  horizontalMargin;      /* +0x08 6 (15 framed) */
    int32  verticalMargin;        /* +0x0c 4 (6 framed) */
    int32  lineSpacing;           /* +0x10 0 */
    int16  font;                  /* +0x14 AEE_FONT_NORMAL (0x8000) */
    uint8  unknown_16[0x02];
    uint32 fillColor;             /* +0x18 the box's secondary colour (its background) */
    uint32 primaryColor;          /* +0x1c the box's primary colour (the text, the outline) */
    uint32 borderColor;           /* +0x20 */
    uint8  autoSize;              /* +0x24 the box takes the height of its text (text_box_set_text) */
    uint8  unknown_25[0x03];
} TextStyle;                      /* 0x28 bytes */

typedef struct TextLine {
    uint8    element[0x30];       /* +0x00 the UI element */
    int32    textWidth;           /* +0x30 the text's width in its font */
    int32    height;              /* +0x34 the font's ascent + descent */
    AECHAR  *text;                /* +0x38 */
    int16    font;                /* +0x3c AEE_FONT_NORMAL */
    uint8    unknown_3e[0x02];
    uint32   alignment;           /* +0x40 bits 4 left, 2 right, else centred; 0x20 top, 0x10 bottom, else
                                     in the middle */
    int32    textX;               /* +0x44 where text_line_draw last drew it */
    int32    textY;               /* +0x48 */
} TextLine;                       /* 0x4c bytes */

typedef struct TextBox {
    uint8    element[0x30];       /* +0x00 the UI element */
    UIList  *lines;               /* +0x30 its text lines, by position */
    TextStyle *style;             /* +0x34 */
    int32    firstLine;           /* +0x38 the first line shown */
    int32    visibleLines;        /* +0x3c how many fit; -1 until text_box_set_text works it out */
    AEETriangle *tail;           /* +0x40 a speech bubble's tail: its tip and a base on one side
                                     (text_box_set_tail), drawn under a type 0 box; freed with the box */
    uint8    scrollable;          /* +0x44 a type 5 style with more lines than fit: a scroll bar */
    uint8    unknown_45[0x03];
    TextLine *moreLine;           /* +0x48 the "more" mark shown when lines follow (text_box_layout) */
    int32    framed;              /* +0x4c a style of type 1, 2 or 3 */
} TextBox;                        /* 0x50 bytes */

/* ---- A screen (GUESS: names) -------------------------------------------------------------------------
 * A plain screen (screen_create, VTABLE_00101700): a UI element the size of the display, put on the
 * screen stack, with the element that has the focus and up to two soft key entries. Starts with the UI
 * element's 0x30 bytes: cast to UIElement for those (the UIElement struct also carries the menu items'
 * fields from +0x30 on, which a screen does not have). The menus' pages and dialogs are plain screens;
 * the HUD (Hud) builds on one. */
typedef struct Screen {
    uint8    element[0x30];       /* +0x00 the UI element */
    UIElement *focus;             /* +0x30 the element with the focus (FUN_00105224 sets it) */
    UIElement **softKeys;         /* +0x34 its first and second soft key entries (8 bytes); their selectEvent
                                     is sent when the player's soft key is pressed */
    uint8    framed;              /* +0x38 screen_create's third argument; set: the draw method
                                     FUN_00106e44 paints a window frame (dark 0xFF615A6D, light
                                     0xFF9795A5, then frameFillColor inside) */
    uint8    unknown_39[0x03];
    int32    field_3c;            /* +0x3c 0 */
    uint32   frameFillColor;      /* +0x40 GUESS: name; 0xFFEBEBF7 at creation */
    struct KHApp *app;            /* +0x44 the stack's app */
} Screen;                         /* 0x48 bytes (screen_create) */

/* The in-game HUD screen (KHApp.field_d4; FUN_0010aa8c, vtable VTABLE_0010165C): a screen element with
 * the player's bars and the level script's texts. Only what hud_show_loading / hud_hide_loading use is
 * named so far; the script code (script_command_run) still reads the rest through offsets. */
typedef struct Hud {
    Screen   screen;              /* +0x00 the plain screen it builds on (screen_create, framed 0) */
    uint8    unknown_48[0x94];
    UIElement *loadingText;       /* +0xdc GUESS: name; child 900 (text 0x254DA109), hidden until
                                     hud_show_loading */
    uint32   savedColor;          /* +0xe0 the primary colour from before hud_show_loading */
} Hud;                           /* 0xe4 bytes (FUN_0010aa8c) */

/* ---- Level scripts (GUESS: names) ------------------------------------------------------------------
 * The levels and screens are driven by scripts: lines of text, one command each ("AddSoftKey ...",
 * "PlayAnim ...", "If ... / Else / EndIf", "SaveGame", ...), parsed into script commands
 * (script_command_parse) and run by script_command_run. A timed script (a sequence) runs its commands
 * at given times (script_sequence_update). */
typedef struct ScriptCommand {
    int32    type;                  /* +0x00 by the command's name (script_command_parse, script_command_run);
                                     0x4c none */
    struct KHApp *app;            /* +0x04 */
    int32    owner;                 /* +0x08 the object or screen whose script it is (0 for a sequence's) */
    struct LevelObject *object;   /* +0x0c the object it acts on, by name (FUN_00112e20) */
    struct LevelObject *target;   /* +0x10 a second object */
    uint32   value[2];              /* +0x14 floats (their bits): a speed, an angle, an amount, ... */
    int32    number[4];             /* +0x1c integers: a mode, a sound, an animation's user id (a hash),
                                     a colour 0xRRGGBB, a text box's rectangle, ... */
    uint32   hash;                  /* +0x2c a name's hash (string_hash): a text's parameter */
    int32    flag[4];               /* +0x30 options, by command */
    char    *text;                  /* +0x40 a text argument: a name, a condition, a list (freed by
                                     script_command_destroy) */
    uint32   vector[3];             /* +0x44 floats (their bits): a position, an offset, a view */
} ScriptCommand;                  /* 0x50 bytes */

typedef struct ScriptSequence {
    ScriptCommand **commands;     /* +0x00 count commands */
    int32   *times;                 /* +0x04 count + 1 times (ms); the last one ends the sequence */
    int32    count;                 /* +0x08 */
    int32    elapsed;               /* +0x0c ms since the sequence started */
    int32    next;                  /* +0x10 the next command to run */
} ScriptSequence;                 /* 0x14 bytes */

/* ---- The player's progress (GUESS: names) -----------------------------------------------------
 * KHApp.progress. Only the fields used by the functions named so far are named; the rest is padding.
 * progress_add_experience levels up through levels[] (levels 0-8); progress_score = munny + 100 *
 * experience. The Controls key bindings (key_picker_setup) are controls[]. */
typedef struct ProgressLevel {
    int32    experienceNeeded;      /* +0x00 experience at which this level-up happens */
    int32    reward;                /* +0x04 1: maximumHealth + 1.0f, 2: levelRewardTwoCount + 1,
                                     3: levelRewardThreeCount + 1 */
} ProgressLevel;

typedef struct ProgressRecord {
    int32    best;                  /* +0x00 GUESS: a best score; replaced only by a higher one after a level */
    int32    field_04;              /* +0x04 GUESS: meaning unknown; -1 from the setter call after a level */
} ProgressRecord;                 /* GUESS: names; Progress.records */
typedef struct Progress {
    uint8  statusFlags[100];      /* +0x000 one byte per status text (GUESS: names) */
    char  *statusTexts[100];      /* +0x064 named status texts, for example "Out of magic" while magicPoints is
                                     0; set and cleared by progress_set_status */
    int32    variableValues[100];   /* +0x1f4 GUESS: names; the level script's variables (setVar, incVar, decVar,
                                     ifVar): their values (progress_find_variable, progress_set_variable) */
    char    *variableNames[100];    /* +0x384 and their names; 0 = free slot */
    uint32 health;                /* +0x514 GUESS: a float (its bits); refilled from maximumHealth */
    uint32 maximumHealth;         /* +0x518 GUESS: a float (its bits); +1.0f by a level reward of type 1 */
    uint32 field_51c;             /* +0x51c a float (its bits), 9.0 at the start; drawn with the health */
    uint32 field_520;             /* +0x520 a float (its bits), 2.0 at the start; drawn with the health */
    int32    magicPoints;           /* +0x524 MP: progress_add_magic_points, 0..maximumMagicPoints */
    int32    maximumMagicPoints;    /* +0x528 */
    int32    munny;                 /* +0x52c the currency: progress_add_munny; spent in shops */
    int32    levelRewardTwoCount;   /* +0x530 GUESS: meaning (a stat level?); 1 at the start, +1 by a level
                                     reward of type 2 */
    int32    levelRewardThreeCount; /* +0x534 GUESS: meaning (a stat level?); 1 at the start, +1 by a level
                                     reward of type 3 */
    int32    experience;            /* +0x538 progress_add_experience */
    ProgressLevel levels[10];     /* +0x53c the level-ups of levels 0-8 (progress_add_experience), and
                                     levels[9] (+0x584): GUESS, a tenth entry nothing reads - 500 and 0 for
                                     a new game (progress_new_game), its experience also set by the
                                     script's setLevelUp of level 9. Until 2026-11-03 this was levels[9]
                                     followed by field_584 and unknown_588[4]; split them again if a
                                     reader of +0x584 / +0x588 turns up. */
    int32    level;                 /* +0x58c 0-9; no level-ups after 9 */
    char    *userId;                /* +0x590 GUESS: name; the online user id (the web requests'
                                     uid=), set once by progress_set_user_id */
    int32    soundVolume;           /* +0x594 GUESS: name; the sound effects' volume: 40 at creation, the
                                     menu (FUN_00101ad8) cycles it through 20, 40, 60 and 0; set on the
                                     app's effects (field_bc) with FUN_0010a03c, and an effect plays
                                     (FUN_00108f28) only while it is above 0; saved with the settings */
    int32    musicVolume;           /* +0x598 GUESS: name; the music's volume: 40 at creation, cycled the
                                     same way; set with FUN_0010a03c on the context's two sound sets, a
                                     level's and the training's music; saved with the settings */
    int32    spells[3];             /* +0x59c 0 at the start; set for each spell the player has (GUESS: names);
                                     character_on_key casts only those */
    int32    showEnemyHealth;       /* +0x5a8 GUESS: name (a fourth ability after the spells, a "scan"); 1
                                     after a reset (FUN_0010f9a4); when set, an enemy that is hit shows its
                                     health in the HUD (FUN_0011d28c, FUN_0011d3ec); saved as '0'/'1' */
    int32    field_5ac;             /* +0x5ac 0 at the start */
    int32    field_5b0;             /* +0x5b0 0 at the start */
    int32    field_5b4;             /* +0x5b4 0 at the start; GUESS: a count of items that refill half the MP
                                     (the Magic key with no MP, after field_5b8) */
    int32    field_5b8;             /* +0x5b8 0 at the start; GUESS: a count of items that refill all of it */
    AECHAR  *collectablesText;      /* +0x5bc script setCollectables: the collectables' name */
    int32    collectables;          /* +0x5c0 and their number */
    int32    field_5c4;             /* +0x5c4 0 at creation; sent as the time (t=) of the ranking and
                                     download requests; FUN_001216c4 adds the seconds since app +0xb0
                                     (GUESS: the time played); saved with the settings */
    int32    field_5c8;             /* +0x5c8 1 at creation; sent as the ranking's u1= value; +1 when the
                                     settings are loaded with app +0xb4 set (FUN_0011b6f0) */
    int32    controls[7];           /* +0x5cc the Controls key bindings (BREW key codes): Forwards, Backwards,
                                     Left, Right, Action, Status, Magic */
    int32    softKeys[2];           /* +0x5e8 the keys that act as the left and the right soft key (screen_handle_key):
                                     AVK_SOFT1 and AVK_SOFT2, swapped when the text 0x052F918F exists */
    char    *recordNames[25];       /* +0x5f0 GUESS: names; the saved records' names (a level's, KHApp.pBufc4);
                                     0 or "" when free (progress_find_record, FUN_0011fddc) */
    ProgressRecord records[25];   /* +0x654 their values */
    int32    summaryPending;        /* +0x71c GUESS: name; set when the level's summary (event 0x75) saves
                                     the game, so that after a suspend (FUN_001242b4) the summary opens
                                     again; saved as '0'/'1' */
    int32    levelLoaded;           /* +0x720 GUESS: name; 1 once the level file is loaded (FUN_0010a5d8),
                                     0 after a reset and a finished download (FUN_0010888c); saved */
    struct KHApp *app;            /* +0x724 the app it belongs to */
    uint8   *saveCopy;             /* +0x728 GUESS: name; the last saved game, 0x800 bytes (FUN_0011e6b8
                                     copies it there), which the loader FUN_0011b178 reads with no file
                                     name */
} Progress;                       /* 0x72c bytes (INTEGER_1836, FUN_0010b4e4) */

/* ---- Level objects -------------------------------------------------------------------------------
 * game_create_objects walks the level's scene (Swerve nodes) and makes a level object for every node
 * that has a name (its user parameter 0x009660B3), choosing the class by the node's tags (FUN_00119b0c):
 * "MotionEntity", "CombatRegion", "BossCombatRegion", or a plain LevelObject. All of them start with the
 * LevelObject fields (kind, parent, node, nameId, app at +0x84); the subclasses are written out flat
 * rather than embedding it. Names are hashed by string_hash (strlen, then from the last character
 * hash = hash * 0x19660D + c + 0x3C6EF35F, made positive, & 0x3FFFFFFF); the WORD_HEXADECIMAL_ ids
 * passed around with level data are such hashes. Fields whose meaning is not known are named by offset. */
struct LevelObject;

/* A level object's collision shape (GUESS: names), 0x48 bytes (collision_shape_create), filled by
 * collision_shape_setup from a text: its first word starts with "inner" or "outer" and ends with the
 * form ("circle", "cylinder", "cuboid", "rect", "sphere", "poly"); the next words give the sizes, or
 * "use verts" for the size of the entity's vertices. */
typedef struct CollisionShape {
    int32    kind;                  /* +0x00 1 "inner", 2 "outer" */
    int32    form;                  /* +0x04 3 circle, 4 cylinder, 5 cuboid, 6 rect, 7 sphere, 8 poly */
    uint32 position[3];           /* +0x08 floats (their bits): the entity's position (FUN_001147ec) */
    uint32 minimum[3];            /* +0x14 floats: the box around it */
    uint32 maximum[3];            /* +0x20 floats */
    uint32 radius;                /* +0x2c a float (its bits) */
    uint32 height;                /* +0x30 a float (its bits); level_object_get_height */
    struct KHApp *app;            /* +0x34 GetAppInstance() at creation */
    uint32 *vertices;             /* +0x38 floats, 3 per vertex (a "poly", or the 4 corners of a "rect") */
    int32    vertexCount;           /* +0x3c */
    int32    clockwise;             /* +0x40 a "poly": the entity's "Clockwise" tag */
    int32   *vertexEntities;        /* +0x44 a "poly": the entities named "%dtransform", one per vertex */
} CollisionShape;                 /* 0x48 bytes */

typedef struct LevelObject {
    uint8  kind;                  /* +0x000 0 LevelObject, 1 MotionEntity, 2 Character (character_create,
                                     0x338 bytes), 3 "Camera" (camera_create, 0x214 bytes), 4 CombatRegion,
                                     5 BossCombatRegion; 2 and 3 are MotionEntity subclasses */
    uint8  unknown_001[0x03];
    struct LevelObject *parent;   /* +0x004 the object of the nearest named node above it, or 0 for the
                                     "NoParent" tag */
    ISwerveObject *node;          /* +0x008 its scene node (AddRef'd) */
    uint32 nameId;                /* +0x00c the hash (string_hash) of its name */
    int32    field_10;              /* +0x010 0 at creation */
    char    *clipart;               /* +0x014 GUESS: name; 0 at creation; the name of its clipart (script
                                     loadClipart, or the first word of its node's user data, FUN_00118910),
                                     loaded by FUN_0011b044 */
    int32    field_18;              /* +0x018 0 at creation */
    int32    field_1c;              /* +0x01c 0 at creation */
    uint8  unknown_020[0x10];
    int32    field_30;              /* +0x030 0 at creation */
    int32    field_34;              /* +0x034 1 at creation */
    int32    field_38;              /* +0x038 1 at creation */
    int32    field_3c;              /* +0x03c 1 at creation */
    int32    field_40;              /* +0x040 0 at creation */
    int32    field_44;              /* +0x044 0 at creation */
    int32    field_48;              /* +0x048 0 at creation */
    int32    field_4c;              /* +0x04c 0 at creation */
    int32    field_50;              /* +0x050 0 at creation */
    int32    field_54;              /* +0x054 0 at creation */
    int32    field_58;              /* +0x058 0 at creation */
    uint8  unknown_05c[0x04];
    int32    field_60;              /* +0x060 0 at creation */
    uint8  unknown_064[0x04];
    uint32 position[3];           /* +0x068 floats (their bits): x, y, z (level_object_get_position); z is
                                     the bottom (callers add half the height for the middle) */
    uint8  unknown_074[0x0c];
    uint32 radius;                /* +0x080 a float (its bits): the first scene shape's radius, or 0
                                     (FUN_00118910) */
    struct KHApp *app;            /* +0x084 GetAppInstance() at creation */
    uint8  unknown_088[0x08];
    CollisionShape *sceneShapes[20]; /* +0x090 the shapes of the nodes of its scene with user parameter
                                     0x019E5BAF (FUN_00120f8c, through FUN_00112cdc) */
    int32    sceneShapeCount;       /* +0x0e0 0 at creation */
    CollisionShape *shapes[2];    /* +0x0e4 the shapes its node's user parameter 0x2101870D lists */
    int32    shapeCount;            /* +0x0ec 0 at creation */
    int32    field_f0;              /* +0x0f0 0 at creation */
    int32    field_f4;              /* +0x0f4 0 at creation */
    int32    field_f8;              /* +0x0f8 0 at creation */
    int32    field_fc;              /* +0x0fc 0 at creation */
    int32    field_100;             /* +0x100 0 at creation */
    int32    field_104;             /* +0x104 0 at creation */
    int32    field_108;             /* +0x108 0 at creation */
    int32    field_10c;             /* +0x10c 0 at creation */
} LevelObject;                    /* 0x110 bytes */

/* "MotionEntity" (kind 1): a LevelObject that moves; the base of kinds 2 and 3. */
typedef struct MotionEntity {
    uint8  kind;                  /* +0x000 LevelObject.kind */
    uint8  unknown_001[0x07];     /* the LevelObject fields, where not named */
    ISwerveObject *node;          /* +0x008 LevelObject.node: handed the position (slot +0x4c) and the
                                     heading (slot +0x5c) by motion_entity_turn */
    uint8  unknown_00c[0x5c];
    uint32 position[3];           /* +0x068 LevelObject.position */
    uint8  unknown_074[0x10];
    struct KHApp *app;            /* +0x084 LevelObject.app */
    uint8  unknown_088[0x88];
    int32    field_110;             /* +0x110 0 at creation */
    int32    field_114;             /* +0x114 0 at creation */
    uint8  unknown_118[0x08];
    int32    field_120;             /* +0x120 0 at creation (character_create) */
    int32    field_124;             /* +0x124 0 at creation (character_create) */
    LevelObject *orbitCenter;     /* +0x128 0 at creation; when set, motion_entity_turn moves the entity
                                     around it (the camera around its target) */
    int32    field_12c;             /* +0x12c 0 at creation */
    uint32 pitch;                 /* +0x130 a float (its bits): the up/down angle, in degrees, -180..180
                                     (motion_entity_get_pitch / _set_pitch / _pitch_by) */
    uint8  unknown_134[0x0c];
    uint32 heading;               /* +0x140 a float (its bits): the direction it faces, in degrees,
                                     -180..180 (motion_entity_get_heading / _turn / _start_turn) */
    uint8  unknown_144[0x10];
    int32    turning;               /* +0x154 0 at creation; 1 while a turn started by motion_entity_start_turn
                                     runs */
    ISwerveObject *field_158;     /* +0x158 0 at creation; a Swerve object that is handed &pitch through its
                                     slot +0x5c whenever the pitch changes (GUESS: a tilting child node) */
    uint8  unknown_15c[0x64];
    uint32 turnAngle;             /* +0x1c0 a float (its bits): the angle left to turn, positive */
    uint32 turnSpeed;             /* +0x1c4 a float (its bits): the turn speed, its sign the direction */
} MotionEntity;                   /* 0x1c8 bytes */

/* ---- The camera (GUESS: names) -----------------------------------------------------------------------
 * The "Camera" level object (kind 3, camera_create, 0x214 bytes; name hash 0x2E6723BD): a motion entity
 * that follows its target. Only what the level scripts set (script_command_run) is named. */
typedef struct Camera {
    uint8    entity[0x1c8];       /* +0x000 the MotionEntity (its first byte LevelObject.kind, 3) */
    int32    field_1c8;           /* +0x1c8 0 at creation */
    LevelObject *target;          /* +0x1cc the object it follows (the player's character, name hash
                                     0x10C617E4) */
    uint8    unknown_1d0[0x08];
    uint32   view[3];             /* +0x1d8 floats (their bits): setCameraFocus's named views (STANDARD_VIEW
                                     90, 0, 10; HIGH_VIEW 60, 45, 45; ...) */
    uint32   field_1e4;           /* +0x1e4 0 at creation */
    int32    activeRotation;      /* +0x1e8 setActiveRotOn / setActiveRotOff */
    uint32   focus[3];            /* +0x1ec floats (their bits): a point it looks at (matchPosition) */
    uint32   pitch;               /* +0x1f8 a float (its bits), degrees (GUESS: name): how far above the
                                     focus it sits, z = focus + sin pitch * distance; setXRot's angle;
                                     10.0 from matchPosition; 0 at creation */
    uint32   yaw;                 /* +0x1fc a float (its bits), degrees (GUESS: name): its direction around
                                     the focus, x, y = focus - (cos yaw, sin yaw) * cos pitch * distance
                                     (the update FUN_00122b90); setYRot - 90 (camera_set_yaw); 0 at
                                     creation */
    uint8    unknown_200[0x04];
    ISwerveObject *field_204;     /* +0x204 0 at creation */
    uint32   distance;            /* +0x208 a float (its bits; GUESS: name): how far it is from the focus;
                                     3.5 at creation, eased back to 3.5 by the update */
    LevelObject *field_20c;       /* +0x20c 0 at creation */
    int32    skipCollision;       /* +0x210 GUESS: name; when set, the next update skips the wall check
                                     (FUN_0010e280) and clears it; set by camera_set_yaw; 0 at creation */
} Camera;                         /* 0x214 bytes (camera_create) */

/* "Character" (kind 2, 0x338 bytes, character_create; GUESS: names): the player's character, a MotionEntity.
 * It plays its animations on three channels (character_play_animation): channel 0 alone, or channels 2
 * and 3 together (GUESS: two body parts); a request on 2 or 3 stops channel 0, and one on 0 stops 2 and 3. */
typedef struct Character {
    uint8  kind;                  /* +0x000 2 (LevelObject.kind) */
    uint8  unknown_001[0x07];     /* the LevelObject and MotionEntity fields, where not named */
    int32    node;                  /* +0x008 its scene node, an ISwerveObject (LevelObject.node) */
    uint8  unknown_00c[0x40];
    int32    field_4c;              /* +0x04c set to 1 by character_setup */
    uint8  unknown_050[0x30];
    uint32 radius;                /* +0x080 LevelObject.radius */
    struct KHApp *app;            /* +0x084 LevelObject.app */
    int32    field_88;              /* +0x088 GUESS: a time in ms; its seconds pick a random spell */
    uint8  unknown_08c[0x9c];
    LevelObject *orbitCenter;     /* +0x128 MotionEntity.orbitCenter */
    int32    field_12c;             /* +0x12c MotionEntity.field_12c */
    uint8  unknown_130[0x98];
    int32    state;                 /* +0x1c8 0xc at creation; the action key starts an attack in states 4, 5,
                                     6, 0x11 and 0x12, forwards turns 0x11 into 0x13 */
    int32    field_1cc;             /* +0x1cc 10 at creation; 0xb and 8 set by the action key */
    uint8  unknown_1d0[0x08];
    int32    controllable;          /* +0x1d8 1 at creation (character_create); the keys move it only while set */
    ISwerveObject *field_1dc;     /* +0x1dc the game scene's object with user id 0x0F846A96 (Find); its
                                     slot +0x48 fills field_1f8 */
    ISwerveObject *field_1e0;     /* +0x1e0 the object with user id 0x0D44B786 */
    ISwerveObject *field_1e4;     /* +0x1e4 the object with user id 0x1DFBEC7F; its slot +0x8c is called
                                     with 0 */
    ISwerveObject *field_1e8;     /* +0x1e8 the object with user id 0x314D49C5 */
    ISwerveObject *field_1ec;     /* +0x1ec the object with user id 0x0A893452 */
    ISwerveObject *shadow;        /* +0x1f0 the scene "CharacterShadow" (FUN_0011ae04) */
    int32    hasShadow;             /* +0x1f4 1 when shadow was loaded */
    int32    field_1f8;             /* +0x1f8 filled by field_1dc's slot +0x48 */
    uint8  unknown_1fc[0x10];
    int32    targets[3];            /* +0x20c entities the player's attacks hit: [0] the current target
                                     (boss_combat_region_hit_target), [n] the one of the enemy numbered n;
                                     set by the enemies (enemy_set_target) and FUN_00123d7c */
    uint8  unknown_218[0x0c];
    int32    field_224;             /* +0x224 set to 1 when the Magic key refills MP with an item */
    int32    field_228;             /* +0x228 7 at creation; the player's state handed to the hit functions */
    int32    selectedSpell;         /* +0x22c 0-2, or 8 for a random known one (character_on_key) */
    int32    field_230;             /* +0x230 */
    LevelObject *field_234;       /* +0x234 the level object named by hash 0x2BB0C920 (FUN_00112dbc) */
    LevelObject *field_238;       /* +0x238 the level object named by hash 0x19DB98DB */
    struct CombatRegion *combatRegion;          /* +0x23c the combat region it is in, or 0 */
    struct BossCombatRegion *bossCombatRegion;  /* +0x240 the boss combat region it is in, or 0 */
    int32    field_244;             /* +0x244 cleared when the action key starts an attack; the tree or ladder
                                     climbed (script setCharacterMode) */
    LevelObject *hangTarget;      /* +0x248 script setCharacterMode HANG's second object */
    LevelObject *carried;         /* +0x24c GUESS: name; the object it carries (character_lift; character_drop
                                     clears it) */
    LevelObject *mirrorObject;    /* +0x250 script setMirror: the object, or 0 */
    uint32 mirrorOffset[3];       /* +0x254 floats (their bits) */
    uint32 mirrorAngle;           /* +0x260 a float (its bits) */
    int32    mirrorFlags[4];        /* +0x264 -X, -Y, -Z, -R */
    int32    swimNoClimb;           /* +0x274 script setCharacterMode SWIM: 1 for SWIM_NO_CLIMB */
    uint8  forwardsHeld;          /* +0x278 the movement keys: 0 up, 1 held (character_on_key, from its */
    uint8  backwardsHeld;         /* +0x279 Controls binding or its arrow key: AVK_UP, AVK_DOWN, AVK_LEFT, */
    uint8  leftHeld;              /* +0x27a AVK_RIGHT, and AVK_SELECT for the action), 2 held since before */
    uint8  rightHeld;             /* +0x27b an interruption (character_freeze_held_keys: ignored until */
    uint8  actionHeld;            /* +0x27c released, character_on_key_release); FUN_0011386c reads them */
    uint8  unknown_27d[0x03];
    int32    controlDirection;      /* +0x280 -1: the movement keys are reversed (forwards <-> backwards, left
                                     <-> right; FUN_0011386c), else normal; set by the level script
                                     (character_set_control_direction) */
    int32    field_284;             /* +0x284 set to 1 by a script setCombatRegion without a region */
    uint32 field_288;             /* +0x288 a float (its bits); level data 0x1218EC09 */
    uint32 field_28c;             /* +0x28c a float (its bits); level data 0x2073D363 */
    int32    field_290;             /* +0x290 0 at creation */
    uint32 field_294;             /* +0x294 a float (its bits): FUN_00126618(level data 0x1932DEDD, 1000.0) */
    uint8  unknown_298[0x08];
    int32    field_2a0;             /* +0x2a0 0 at creation */
    int32    layered;               /* +0x2a4 0 at creation; 1 while channels 2 and 3 are in use */
    uint8  unknown_2a8[0x04];
    int32    animation;             /* +0x2ac the animation on channel 0, -1 none */
    int32    channelTwoAnimation;   /* +0x2b0 the animation on channel 2, -1 none */
    int32    channelThreeAnimation; /* +0x2b4 the animation on channel 3, -1 none */
    int32    animations[29];        /* +0x2b8 its animations' indexes, found by user id (character_setup); 9-12
                                     play at speed 2.0, 19, 21 and 27 at 1.5 */
    uint8  unknown_32c[0x0c];
} Character;                      /* 0x338 bytes */

/* KHApp.pGame (GUESS: names): the game state; it holds the level objects. */
typedef struct Game {
    ISwerveObject *root;          /* +0x000 a scene whose level objects FUN_0010a5d8 creates */
    ISwerveObject *field_04;      /* +0x004 a scene loaded by FUN_0011ae04; its level objects are created
                                     too */
    uint8  unknown_008[0x08];
    LevelObject *objects[120];    /* +0x010 0 = free slot (game_find_free_object_slot) */
    struct Camera *camera;        /* +0x1f0 the camera */
    uint8  unknown_1f4[0x04];
    struct Character *character;  /* +0x1f8 the player's character (FUN_0010a5d8 creates it from the scene's
                                     entity 0x0AD65F3D); its +0x20c is the current target */
    LevelObject *actionObject;    /* +0x1fc the object of the action shown (script addUIAction; cleared by
                                     removeUIAction) */
    uint8  unknown_200[0x04];
    int32    terrainLevelSet;       /* +0x204 script setTerrainLevel: 1 with a level, 0 without */
    uint32   terrainLevel;          /* +0x208 a float (its bits): that level's height */
    int32    field_20c;             /* +0x20c set to 1 by a script addUIText with flag 1 */
    uint8  unknown_210[0x04];
    struct KHApp *app;            /* +0x214 */
} Game;

/* The Swerve vtable slots game_create_objects calls, past the shared ISwerveObjectVtbl ones (GUESS:
 * names, from the JSR-184 methods they implement in swv21brew). */
typedef struct SwerveGroupVtbl {
    ISwerveObjectVtbl object;                                            /* +0x00 slots 0-2 */
    void  *unknown_0c[0x28];
    void (*GetChildCount)(ISwerveObject *po, int32 *pCount);               /* +0xac slot 43, 0x01030360 */
    int32  (*GetChild)(ISwerveObject *po, int32 index, ISwerveObject **ppo); /* +0xb0 slot 44, 0x010302ec */
} SwerveGroupVtbl;

typedef struct SwerveSkinnedMeshVtbl {
    ISwerveObjectVtbl object;                                            /* +0x00 slots 0-2 */
    void  *unknown_0c[0x31];
    int32  (*GetSkeleton)(ISwerveObject *po, ISwerveObject **ppo);         /* +0xd0 slot 52, 0x01038878 */
} SwerveSkinnedMeshVtbl;

/* The Swerve Object3D vtable slots kh.mod calls, shared by every object class (GUESS: names, from the
 * JSR-184 methods they implement in swv21brew, 0x0103517c fills them). */
typedef struct SwerveObject3DVtbl {
    ISwerveObjectVtbl object;                                            /* +0x00 slots 0-2 */
    void (*GetUserId)(ISwerveObject *po, int32 *pUserId);                  /* +0x0c slot 3, 0x010350fc */
    void  *unknown_10;
    void (*GetAnimationTrackCount)(ISwerveObject *po, int32 *pCount);      /* +0x14 slot 5, 0x01034f74 */
    int32  (*GetAnimationTrack)(ISwerveObject *po, int32 index, ISwerveObject **ppo); /* +0x18 slot 6, 0x01034f00 */
    void  *unknown_1c[0x02];
    int32  (*Animate)(ISwerveObject *po, int32 worldTime, int32 *pResult);     /* +0x24 slot 9, 0x01034da8 */
    int32  (*Find)(ISwerveObject *po, int32 userId, ISwerveObject **ppo);    /* +0x28 slot 10, 0x01034e8c */
} SwerveObject3DVtbl;

typedef struct SwerveAnimationTrackVtbl {
    ISwerveObjectVtbl object;                                            /* +0x00 slots 0-2 */
    void  *unknown_0c[0x10];                                             /* the Object3D slots and more */
    int32  (*GetController)(ISwerveObject *po, ISwerveObject **ppo);       /* +0x4c slot 19, 0x0102d1c0 */
    void  *unknown_50;
    int32  (*GetKeyframeSequence)(ISwerveObject *po, ISwerveObject **ppo); /* +0x54 slot 21, 0x0102d22c */
} SwerveAnimationTrackVtbl;

typedef struct SwerveKeyframeSequenceVtbl {
    ISwerveObjectVtbl object;                                            /* +0x00 slots 0-2 */
    void  *unknown_0c[0x10];
    void (*GetDuration)(ISwerveObject *po, int32 *pDuration);              /* +0x4c slot 19, 0x01032ac0 */
} SwerveKeyframeSequenceVtbl;

typedef struct SwerveAnimationControllerVtbl {
    ISwerveObjectVtbl object;                                            /* +0x00 slots 0-2 */
    void  *unknown_0c[0x14];
    int32  (*SetActiveInterval)(ISwerveObject *po, int32 start, int32 end);    /* +0x5c slot 23, 0x0102cf84 */
    void  *unknown_60;
    int32  (*SetPosition)(ISwerveObject *po, uint32 sequenceTime, int32 worldTime); /* +0x64 slot 25, 0x0102cfec;
                                                                            sequenceTime is a float */
} SwerveAnimationControllerVtbl;

/* ---- The scene's animations (GUESS: names) -------------------------------------------------------
 * KHApp.animations (1820 bytes, animations_create). A table of up to 100 animations, one per animation
 * controller of the loaded scene, keyed by the controller's user id (animations_add_from_scene); the
 * game refers to an animation by its index. A slot is free when its user id is -1. Each animation is
 * played at a speed from a position that animations_set_position hands to its controller (looked up by
 * user id in the world the first time). */
typedef struct Animations {
    struct KHApp *app;            /* +0x000 GetAppInstance() at creation */
    ISwerveObject *world;         /* +0x004 GUESS: the scene's World; controllers are found in it (Find) */
    int32    elapsed;               /* +0x008 ms since the last update (animations_update) */
    int32    worldTime;             /* +0x00c the time the controllers are set at (animations_update) */
    int32    userIds[100];          /* +0x010 the controllers' user ids (animations_find); -1 = free slot */
    int32    durations[100];        /* +0x1a0 the longest keyframe sequence of each controller
                                     (animations_get_duration) */
    uint8  states[100];           /* +0x330 0 free (animations_reset); 1 added, never played (stopped at the
                                     next update); 2 playing once (becomes 4 at its end); 3 looping; 4 stopped
                                     or finished (animations_stop, animations_finish, animations_update) */
    uint8  priorities[100];       /* +0x394 2 when added; on a character's animation channel a new animation
                                     replaces the playing one only when its priority is not lower
                                     (character_play_animation) */
    uint32 speeds[100];           /* +0x3f8 floats (their bits), 1.0 when added (animations_set_speed) */
    int32    positions[100];        /* +0x588 where each one plays from: 0, or its last frame when its speed is
                                     not above 0 */
    ISwerveObject **controllers;  /* +0x718 100 controllers, found by user id when first played; 0 until then
                                     and after animations_release_controllers */
} Animations;                     /* 0x71c bytes */

/* ---- The opening sequence (GUESS: names) ----------------------------------------------------------
 * KHApp.intro (0xa4 bytes, intro_create): stage 0 waits 2 s, stage 1 plays one animation of its scene
 * to the end, stage 2 runs the title scene's timeline (11 animations, each shown between its start and
 * end time), opens the title menu (screen 0x5a, GUESS) at 4.2 s and loops 4467..13802 ms behind it.
 * Each stage change loads the stage's scene (FUN_0011b890). The select key skips to the menu (intro_on_key).
 * A return to the title creates it at stage 2. */
typedef struct Intro {
    int32    running;               /* +0x00 0 at creation; intro_update does nothing until it is set */
    struct KHApp *app;            /* +0x04 GetAppInstance() at creation */
    int32    field_08;              /* +0x08 0 at creation */
    int32    field_0c;              /* +0x0c 0 at creation */
    int32    animation;             /* +0x10 stage 1's animation (an Animations index) */
    int32    timelineAnimations[11];   /* +0x14 stage 2's animations */
    int32    starts[11];            /* +0x40 when each of them starts (ms into stage 2) */
    int32    ends[11];              /* +0x6c when each ends */
    int32    time;                  /* +0x98 ms since the stage started */
    int32    stage;                 /* +0x9c 0, 1, 2 */
    int32    menuOpened;            /* +0xa0 stage 2 has opened the title menu */
} Intro;                          /* 0xa4 bytes */

/* ---- Enemies and combat regions (GUESS: names) ----------------------------------------------
 * A CombatRegion ("CombatRegion" level object, kind 4) is a place in a level that sends enemies in
 * waves: combat_region_setup reads its parameters from the level data, combat_region_update runs its
 * waves and updates its enemies. Each Enemy (0x280 bytes, enemy_create) waits until the region lets it
 * appear (combat_region_take_one), then lives through the states of enemy_update. */
struct CombatRegion;

/* The items an combat region's enemies drop (100 bytes, FUN_0010b014; GUESS: names): 10 slots, each an
 * item on the ground for a limited time. A slot is free when its timeLeft is 0
 * (item_drops_find_free_slot). FUN_0010fbf4 drops items into free slots; FUN_001226e8 counts the times
 * down and gives the reward when the player picks one up. */
typedef struct ItemDrops {
    struct KHApp *app;            /* +0x00 GetAppInstance() at creation */
    int32    entities[10];          /* +0x04 the item shown in each slot: the objects "ball1" - "ball10" */
    uint8  kinds[10];             /* +0x2c 0: health +1.0, 1: MP +1, 2: munny */
    uint8  unknown_36[0x02];
    int32    timeLeft[10];          /* +0x38 ms the item stays on the ground; 0 = free slot */
    uint32 munnyPerPickup;        /* +0x60 a float (its bits): 1.0, or 2.0 when the region's field_120 >= 5 */
} ItemDrops;                      /* 100 bytes */

typedef struct Enemy {
    int32    vtable;                /* +0x000 slots hold self-relative offsets; +4 is enemy_update, 0 and +0xc
                                     run when the region's field_148 is set */
    uint32   playerPoint[3];      /* +0x004 GUESS: name; floats (their bits): the point near the player it
                                     aims at, set every update (enemy_get_player_point) */
    uint32   position[3];         /* +0x010 GUESS: name; floats (their bits): its model's (field_20)
                                     position, read every update (level_object_get_position) */
    int32    number;                /* +0x01c 1, 2, ...: its place among the region's enemies */
    int32    field_20;              /* +0x020 GUESS: its model (an object) */
    int32    field_24;              /* +0x024 */
    int32    field_28;              /* +0x028 an object; FUN_001201cc(field_28, 0) when it dies */
    uint8  unknown_2c[0x10];
    uint32 health;                /* +0x03c a float (its bits); > 0 alive, shown in the health bar */
    struct CombatRegion *region; /* +0x040 the region that created it */
    uint8  unknown_44[0x1c];
    int32    field_60;              /* +0x060 */
    int32    field_64;              /* +0x064 */
    int32    field_68;              /* +0x068 */
    uint8  unknown_6c[0x08];
    struct KHApp *app;            /* +0x074 GetAppInstance() at creation */
    uint8  unknown_78[0x08];
    int32    mode;                  /* +0x080 1: the code at 0x0011db34 runs instead of the states (field_90) */
    int32    field_84;              /* +0x084 a state machine: 3001 first (enemy_reset_states) */
    int32    field_88;              /* +0x088 a state machine: 2001 first; 2004: the alive behaviour runs even
                                     at 0 health */
    int32    field_8c;              /* +0x08c a state machine: 6001 first */
    int32    field_90;              /* +0x090 the state while mode is 1: 7001, 7002, 7003 */
    uint8  unknown_94[0x08];
    int32    field_9c;              /* +0x09c a state machine: 4001 first */
    int32    waitState;             /* +0x0a0 enemy_wait: 5001 idle, 5002 waiting */
    int32    state;                 /* +0x0a4 1001 waiting, 1002 alive, 1003 dying, 1004 gone */
    uint8  unknown_a8[0x14];
    int32    waitUntil;             /* +0x0bc enemy_wait: the time (ms) the wait ends */
    uint8  unknown_c0[0x38];
    int32    field_f8;              /* +0x0f8 */
    uint8  unknown_fc[0x04];
    int32    animation;             /* +0x100 GUESS: name; the animation it plays (enemy_play_animation), -1
                                     none */
    int32    type;                  /* +0x104 1-11, from the region's enemy name (combat_region_setup) */
    int32    field_108;             /* +0x108 when set (or for type 2) its health bar is shown */
    uint8  unknown_10c[0x14];
    int32    field_120;             /* +0x120 cleared by enemy_reset_states */
    uint8  unknown_124[0x04];
    int32    field_128;             /* +0x128 a countdown (enemy_update subtracts the elapsed time) */
    int32    field_12c;             /* +0x12c another countdown */
    int32    field_130;             /* +0x130 */
    uint8  unknown_134[0x04];
    int32    actionSteps[8];        /* +0x138 the step of each of its action sequences: 0x65 first, 0x66 next
                                     (+0x138 used by FUN_0010eb74, +0x13c by FUN_0011ec28); GUESS: names */
    uint8  unknown_158[0x44];
    int32  (*field_19c)(struct Enemy *enemy, int32 now);   /* +0x19c alive, mode 2 and field_130 == 0 */
    int32  (*field_1a0)(struct Enemy *enemy, int32 now);   /* +0x1a0 alive, otherwise */
    uint8  unknown_1a4[0xcc];
    int32    field_270;             /* +0x270 1 at creation */
    uint8  unknown_274[0x0c];
} Enemy;                          /* 0x280 bytes */

typedef struct CombatRegion {
    uint8  kind;                  /* +0x000 4 (LevelObject.kind) */
    uint8  unknown_001[0x03];
    LevelObject *parent;          /* +0x004 LevelObject.parent */
    int32    node;                  /* +0x008 its scene node, an ISwerveObject (LevelObject.node); the setup
                                     reads its parameters from it */
    uint32 nameId;                /* +0x00c LevelObject.nameId; passed with message 0x11E3EE3E
                                     (combat_region_update) */
    uint8  unknown_10[0x74];
    struct KHApp *app;            /* +0x084 */
    uint8  unknown_88[0x88];
    int32    active;                /* +0x110 0 at creation; GUESS: the player is in its area */
    ItemDrops *itemDrops;         /* +0x114 its item drops (FUN_0010b014; updated by FUN_001226e8) */
    uint32 enemyMaximumHealth;    /* +0x118 a float (its bits); level data, default 5.0 */
    uint32 field_11c;             /* +0x11c a float (its bits); level data, default 1.0 */
    int32    field_120;             /* +0x120 level data; below 5 the item drops get 1.0, else 2.0 */
    int32    waves;                 /* +0x124 level data */
    int32    enemiesPerWave;        /* +0x128 level data */
    int32    enemyCount;            /* +0x12c enemy objects: 2 for type 1, else 1; at most enemiesPerWave */
    int32    state;                 /* +0x130 1 at creation; 1 waiting, 2 fighting, 3 the player left during a wave (GUESS) */
    int32    wavesLeft;             /* +0x134 */
    int32    enemiesLeftInWave;     /* +0x138 combat_region_take_one takes them one by one */
    int32    field_13c;             /* +0x13c 1 at creation; set to 1 when state 2 ends */
    int32    field_140;             /* +0x140 0 at creation */
    uint8  unknown_144[0x04];
    int32    field_148;             /* +0x148 1 at creation; when set, each enemy's vtable slots 0 and +0xc
                                     run once */
    Enemy **enemies;              /* +0x14c enemyCount of them */
    int32    field_150;             /* +0x150 0 at creation */
    int32    attackToken;           /* +0x154 0 at creation; 1 while one of its enemies holds it
                                     (combat_region_take_attack_token / _release_attack_token) */
} CombatRegion;                   /* 0x158 bytes */

/* ---- Boss combat regions (GUESS: the hitsphere reading and the function names) ---------------------
 * A "BossCombatRegion" level object (kind 5; setup FUN_0011868c starts with the base setup FUN_00118910,
 * as combat_region_setup does), whose boss is a set of hitspheres: scene entities named in the level
 * data, each with a radius. Every frame (FUN_00123d7c) the nearest hitsphere whose radius holds the
 * player (a 3D distance, FUN_00113820) becomes the game's current target, and a player attack hits it
 * (boss_combat_region_hit_target). The first hitsphere's field_14 is shown in the HUD (GUESS: the boss's
 * health). */
struct BossCombatRegion;

typedef struct Hitsphere {
    int32    vtable;                /* +0x00 0x00101650; slots hold self-relative offsets: +4 update,
                                     +8 take a hit (damage, x, y, z, player state) */
    int32    entity;                /* +0x04 the scene entity it follows */
    uint32 radius;                /* +0x08 a float (its bits); not set by hitsphere_create */
    uint8  unknown_0c[0x08];
    uint32 field_14;              /* +0x14 a float (its bits); the first hitsphere's is shown in the HUD
                                     (field_d4 +0x4c, +0x50) */
    uint8  unknown_18[0x08];
    struct KHApp *app;            /* +0x20 GetAppInstance() at creation */
    struct BossCombatRegion *owner; /* +0x24 */
    uint32   playerPoint[3];      /* +0x28 GUESS: name; floats (their bits): the point near the player it
                                     aims at, set every update (hitsphere_get_player_point) */
    uint32   position[3];         /* +0x34 GUESS: name; floats (their bits): its entity's position, read
                                     every update (level_object_get_position) */
    uint8  unknown_40[0x04];
    int32    field_44;              /* +0x44 0 at creation */
    int32    secondary;             /* +0x48 set on every hitsphere but the first */
    int32    animation;             /* +0x4c GUESS: name; the animation it plays (hitsphere_play_animation), -1
                                     none */
    uint8  unknown_50[0x30];
    int32    field_80;              /* +0x80 0 at creation */
    uint8  unknown_84[0x20];
    int32    field_a4;              /* +0xa4 0 at creation */
    int32    field_a8;              /* +0xa8 0 at creation */
    int32    field_ac;              /* +0xac 0 at creation */
    uint8  unknown_b0[0x08];
    int32    field_b8;              /* +0xb8 0 at creation */
    int32    field_bc;              /* +0xbc 0 at creation */
    int32    field_c0;              /* +0xc0 0 at creation */
    int32    field_c4;              /* +0xc4 0 at creation */
    uint32 field_c8;              /* +0xc8 a float (its bits), 3.0 at creation */
    uint32 field_cc;              /* +0xcc a float (its bits), 0.3 at creation */
    int32    field_d0;              /* +0xd0 0 at creation */
} Hitsphere;                      /* 0xd4 bytes */

typedef struct BossCombatRegion {
    uint8  kind;                  /* +0x000 5 (LevelObject.kind) */
    uint8  unknown_001[0x03];
    LevelObject *parent;          /* +0x004 LevelObject.parent */
    int32    node;                  /* +0x008 its scene node, an ISwerveObject (LevelObject.node) */
    uint32 nameId;                /* +0x00c LevelObject.nameId */
    uint8  unknown_10[0x74];
    struct KHApp *app;            /* +0x084 */
    uint8  unknown_88[0x88];
    int32    active;                /* +0x110 0 at creation; GUESS: the player is in its area (FUN_00123d7c) */
    ItemDrops *itemDrops;         /* +0x114 its item drops (updated by FUN_001226e8) */
    int32   *field_118;             /* +0x118 more scene entities named in the level data (field_12c of them) */
    int32    extraEntity;           /* +0x11c one more scene entity (id 0x2E583064): it can be targeted within
                                     3.0, and a hit hides it and clears its +0x34 (targetable) */
    Hitsphere **hitspheres;       /* +0x120 */
    uint32 field_124;             /* +0x124 a float (its bits), 1.0 at creation */
    int32    hitsphereCount;        /* +0x128 */
    int32    field_12c;             /* +0x12c how many field_118 holds */
    int32    field_130;             /* +0x130 1 at creation; when set, FUN_00123d7c runs each hitsphere's
                                     vtable slot 0 and fills the HUD from the first one, then clears it */
    uint8  unknown_134[0x08];
} BossCombatRegion;               /* 0x13c bytes */

#endif /* KH_TYPES_H */
