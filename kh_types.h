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
    struct Progress *progress;       /* +0xa8 the player's progress (munny, experience, level, controls);
                                        created by 0x10b4e4; EVT_APP_MESSAGE handled only while set */
    uint32         field_ac;         /* +0xac */
    uint32         dwStartTimeMS;    /* +0xb0 aee_GetTimeMS() at EVT_APP_START */
    uint32         bStarted;         /* +0xb4 GUESS: set to 1 at EVT_APP_START */
    uint32         bSuspended;       /* +0xb8 GUESS: set to 1 at EVT_APP_SUSPEND */
    uint32         field_bc;         /* +0xbc */
    uint32         field_c0;         /* +0xc0 */
    void          *pBufc4;           /* +0xc4 heap block (helper free in kh_OnAppStop) */
    void          *pBufc8;           /* +0xc8 heap block (helper free in kh_OnAppStop) */
    uint32         field_cc;         /* +0xcc */
    struct ScreenStack *screens;     /* +0xd0 the open screens (menus); created by 0x10ac6c(0, pMe),
                                        destroyed by 0x10c3f8. FUN_00101ad8 handles its events */
    uint32         field_d4;         /* +0xd4 */
    uint32         fpStatus;         /* +0xd8 GUESS: soft-float status word (what a compiler fplib keeps in a
                                        static). Address returned by kh_GetFpStatusPtr; read by
                                        kh.mod's double->float at 0x12479c (tests bit 0x800). */
    uint32         field_dc;         /* +0xdc address returned by kh_GetAppFieldPtr_dc */
} KHApp;

/* ---- Lists (GUESS: names) ----------------------------------------------------------------------
 * The children of a menu or UI element (for example the list at menu +0x24), kept as two parallel
 * arrays. list_get_entry reads an entry by position (0 when out of range); list_find_entry returns the
 * entry whose id matches; list_set_entry adds or replaces one; list_remove_entry takes one out. The key map of a UIElement (+0x60) is searched the same way. */
typedef struct UIList {
    int    count;                 /* +0x00 number of entries */
    int   *ids;                   /* +0x04 one id per entry (the key pickers have ids 400-406) */
    int   *entries;               /* +0x08 the entries, usually UIElement pointers */
    int    capacity;              /* +0x0c room in both arrays */
    int    growBy;                /* +0x10 how much list_set_entry grows them by when they are full */
} UIList;

/* ---- The screen stack (GUESS: names) -------------------------------------------------------------
 * The game's open screens (menus), KHApp.screens. Each screen has its position as its id in the list
 * (0 = the bottom); the top one, id depth - 1, is the one shown (screen_stack_top). Screens have a
 * vtable at +0 whose slots hold self-relative offsets: slot 0 destroys the screen, +0x20 resumes it
 * when it becomes the top again (screen_stack_close_top). */
typedef struct ScreenStack {
    struct KHApp *app;            /* +0x00 */
    uint8  unknown_04[0x30];
    UIList *screens;              /* +0x34 the open screens, by position */
    int    depth;                 /* +0x38 how many screens are open */
} ScreenStack;

/* ---- The game's UI elements (GUESS: names) ------------------------------------------------------
 * A UIElement is a screen, menu entry or widget, created by FUN_0010bba0 with its type in +0x34.
 * Elements form a tree: each has an id and a parent, and keeps its children in a UIList
 * (ui_element_add_child / ui_element_find_child). Only the fields used by the functions named so far
 * are named; the rest is padding.
 * Type 8 is the key picker of the Controls screen; +0x3c..+0x48 and +0x68 are its own fields. */
typedef struct KeyOption {
    struct KeyOption *previous;   /* +0x00 */
    struct KeyOption *next;       /* +0x04 */
    int    label;                 /* +0x08 the text shown for it: 0x1484CCBF "undefined", -1000..-1011
                                     the keys 0..9, *, # (GUESS: glyph ids) */
    int    keyCode;               /* +0x0C AVK_UNDEFINED, AVK_0..AVK_9, AVK_STAR or AVK_POUND */
} KeyOption;                      /* 0x10 bytes; the Controls screen links 13 of them in a ring */

typedef struct UIElement {
    uint8  unknown_00[0x0c];
    int    id;                    /* +0x0c its id among its parent's children (ui_element_add_child) */
    uint32 primaryColor;          /* +0x10 set by ui_element_handle_key for each type and state */
    uint32 secondaryColor;        /* +0x14 */
    uint8  unknown_18[0x08];
    int   *owner;                 /* +0x20 the menu (screen) it belongs to; FUN_00101ad8 handles its events */
    UIList *children;             /* +0x24 its children, by id (ui_element_find_child) */
    int    nextAutomaticId;       /* +0x28 counts down from 0: the ids -1, -2, ... given to children
                                     added without an id (or with one already in use) */
    struct UIElement *parent;     /* +0x2c the element it was added to */
    int    label;                 /* +0x30 the text element that shows the current value */
    int    type;                  /* +0x34 2..10; 8 = key picker */
    int    selectEvent;           /* +0x38 the event sent to the owner when SELECT is pressed */
    KeyOption *options;           /* +0x3c key picker: the ring of options */
    KeyOption *selectedOption;    /* +0x40 key picker: the option shown */
    int   *setting;               /* +0x44 key picker: the setting it edits (a key code) */
    int    index;                 /* +0x48 key picker: its row (0..6), passed to FUN_0010a498 on UP / DOWN */
    uint8  enabled;               /* +0x4c GUESS: meaning; a key picker with 0 is drawn all white */
    uint8  unknown_4d[0x03];
    int   *listener;              /* +0x50 an object (vtable at +0) that gets the keys the element
                                     does not handle itself */
    uint8  unknown_54[0x08];
    uint32 flags;                 /* +0x5c bit 1: keep the colours (no restyling) */
    UIList *keyMap;               /* +0x60 searched with the key code by list_find_entry */
    int    unknown_64;            /* +0x64 passed to FUN_00105224 with the element found there */
    int    originalKeyCode;       /* +0x68 key picker: the setting's value when it was set up */
} UIElement;

/* ---- The player's progress (GUESS: names) -----------------------------------------------------
 * KHApp.progress. Only the fields used by the functions named so far are named; the rest is padding.
 * progress_add_experience levels up through levels[] (levels 0-8); progress_score = munny + 100 *
 * experience. The Controls key bindings (key_picker_setup) are controls[]. */
typedef struct ProgressLevel {
    int    experienceNeeded;      /* +0x00 experience at which this level-up happens */
    int    reward;                /* +0x04 1: maximumHealth + 1.0f, 2: levelRewardTwoCount + 1,
                                     3: levelRewardThreeCount + 1 */
} ProgressLevel;

typedef struct Progress {
    uint8  unknown_000[0x514];
    uint32 health;                /* +0x514 GUESS: a float (its bits); refilled from maximumHealth */
    uint32 maximumHealth;         /* +0x518 GUESS: a float (its bits); +1.0f by a level reward of type 1 */
    uint8  unknown_51c[0x10];
    int    munny;                 /* +0x52c the currency: progress_add_munny; spent in shops */
    int    levelRewardTwoCount;   /* +0x530 GUESS: meaning; +1 by a level reward of type 2 */
    int    levelRewardThreeCount; /* +0x534 GUESS: meaning; +1 by a level reward of type 3 */
    int    experience;            /* +0x538 progress_add_experience */
    ProgressLevel levels[9];      /* +0x53c the level-ups of levels 0-8 */
    uint8  unknown_584[0x08];
    int    level;                 /* +0x58c 0-9; no level-ups after 9 */
    uint8  unknown_590[0x3c];
    int    controls[7];           /* +0x5cc the Controls key bindings (BREW key codes): Forwards, Backwards,
                                     Left, Right, Action, Status, Magic */
    uint8  unknown_5e8[0x13c];
    struct KHApp *app;            /* +0x724 the app it belongs to */
} Progress;

#endif /* KH_TYPES_H */
