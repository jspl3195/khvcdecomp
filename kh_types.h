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
    uint8  statusFlags[100];      /* +0x000 one byte per status text (GUESS: names) */
    char  *statusTexts[100];      /* +0x064 named status texts, for example "Out of magic" while magicPoints is
                                     0; set and cleared by FUN_0011fef4 */
    uint8  unknown_1f4[0x320];
    uint32 health;                /* +0x514 GUESS: a float (its bits); refilled from maximumHealth */
    uint32 maximumHealth;         /* +0x518 GUESS: a float (its bits); +1.0f by a level reward of type 1 */
    uint32 field_51c;             /* +0x51c a float (its bits), 9.0 at the start; drawn with the health */
    uint32 field_520;             /* +0x520 a float (its bits), 2.0 at the start; drawn with the health */
    int    magicPoints;           /* +0x524 MP: progress_add_magic_points, 0..maximumMagicPoints */
    int    maximumMagicPoints;    /* +0x528 */
    int    munny;                 /* +0x52c the currency: progress_add_munny; spent in shops */
    int    levelRewardTwoCount;   /* +0x530 GUESS: meaning (a stat level?); 1 at the start, +1 by a level
                                     reward of type 2 */
    int    levelRewardThreeCount; /* +0x534 GUESS: meaning (a stat level?); 1 at the start, +1 by a level
                                     reward of type 3 */
    int    experience;            /* +0x538 progress_add_experience */
    ProgressLevel levels[9];      /* +0x53c the level-ups of levels 0-8 */
    uint8  unknown_584[0x08];
    int    level;                 /* +0x58c 0-9; no level-ups after 9 */
    uint8  unknown_590[0x0c];
    int    field_59c;             /* +0x59c 0 at the start */
    int    field_5a0;             /* +0x5a0 0 at the start */
    int    field_5a4;             /* +0x5a4 0 at the start */
    uint8  unknown_5a8[0x04];
    int    field_5ac;             /* +0x5ac 0 at the start */
    int    field_5b0;             /* +0x5b0 0 at the start */
    int    field_5b4;             /* +0x5b4 0 at the start */
    int    field_5b8;             /* +0x5b8 0 at the start */
    uint8  unknown_5bc[0x10];
    int    controls[7];           /* +0x5cc the Controls key bindings (BREW key codes): Forwards, Backwards,
                                     Left, Right, Action, Status, Magic */
    uint8  unknown_5e8[0x13c];
    struct KHApp *app;            /* +0x724 the app it belongs to */
} Progress;

/* ---- Level objects -------------------------------------------------------------------------------
 * game_create_objects walks the level's scene (Swerve nodes) and makes a level object for every node
 * that has a name (its user parameter 0x009660B3), choosing the class by the node's tags (FUN_00119b0c):
 * "MotionEntity", "CombatRegion", "BossCombatRegion", or a plain LevelObject. All of them start with the
 * LevelObject fields (kind, parent, node, nameId, app at +0x84); the subclasses are written out flat
 * rather than embedding it. Names are hashed by FUN_00113654 (strlen, then from the last character
 * hash = hash * 0x19660D + c + 0x3C6EF35F, made positive, & 0x3FFFFFFF); the WORD_HEXADECIMAL_ ids
 * passed around with level data are such hashes. Fields whose meaning is not known are named by offset. */
struct LevelObject;

typedef struct LevelObject {
    uint8  kind;                  /* +0x000 0 LevelObject, 1 MotionEntity, 2 and 3 MotionEntity subclasses
                                     (FUN_0010b70c 0x338 bytes, FUN_0010b3e8 0x214 bytes), 4 CombatRegion,
                                     5 BossCombatRegion */
    uint8  unknown_001[0x03];
    struct LevelObject *parent;   /* +0x004 the object of the nearest named node above it, or 0 for the
                                     "NoParent" tag */
    ISwerveObject *node;          /* +0x008 its scene node (AddRef'd) */
    uint32 nameId;                /* +0x00c the hash (FUN_00113654) of its name */
    int    field_10;              /* +0x010 0 at creation */
    int    field_14;              /* +0x014 0 at creation */
    int    field_18;              /* +0x018 0 at creation */
    int    field_1c;              /* +0x01c 0 at creation */
    uint8  unknown_020[0x10];
    int    field_30;              /* +0x030 0 at creation */
    int    field_34;              /* +0x034 1 at creation */
    int    field_38;              /* +0x038 1 at creation */
    int    field_3c;              /* +0x03c 1 at creation */
    int    field_40;              /* +0x040 0 at creation */
    int    field_44;              /* +0x044 0 at creation */
    int    field_48;              /* +0x048 0 at creation */
    int    field_4c;              /* +0x04c 0 at creation */
    int    field_50;              /* +0x050 0 at creation */
    int    field_54;              /* +0x054 0 at creation */
    int    field_58;              /* +0x058 0 at creation */
    uint8  unknown_05c[0x04];
    int    field_60;              /* +0x060 0 at creation */
    uint8  unknown_064[0x20];
    struct KHApp *app;            /* +0x084 GetAppInstance() at creation */
    uint8  unknown_088[0x58];
    int    field_e0;              /* +0x0e0 0 at creation */
    uint8  unknown_0e4[0x08];
    int    field_ec;              /* +0x0ec 0 at creation */
    int    field_f0;              /* +0x0f0 0 at creation */
    int    field_f4;              /* +0x0f4 0 at creation */
    int    field_f8;              /* +0x0f8 0 at creation */
    int    field_fc;              /* +0x0fc 0 at creation */
    int    field_100;             /* +0x100 0 at creation */
    int    field_104;             /* +0x104 0 at creation */
    int    field_108;             /* +0x108 0 at creation */
    int    field_10c;             /* +0x10c 0 at creation */
} LevelObject;                    /* 0x110 bytes */

/* "MotionEntity" (kind 1): a LevelObject that moves; the base of kinds 2 and 3. */
typedef struct MotionEntity {
    uint8  kind;                  /* +0x000 LevelObject.kind */
    uint8  unknown_001[0x10f];    /* the LevelObject fields */
    int    field_110;             /* +0x110 0 at creation */
    int    field_114;             /* +0x114 0 at creation */
    uint8  unknown_118[0x10];
    int    field_128;             /* +0x128 0 at creation */
    int    field_12c;             /* +0x12c 0 at creation */
    uint8  unknown_130[0x24];
    int    field_154;             /* +0x154 0 at creation */
    int    field_158;             /* +0x158 0 at creation */
    uint8  unknown_15c[0x64];
    int    field_1c0;             /* +0x1c0 0 at creation */
    int    field_1c4;             /* +0x1c4 0 at creation */
} MotionEntity;                   /* 0x1c8 bytes */

/* KHApp.pGame (GUESS: names): the game state; it holds the level objects. */
typedef struct Game {
    ISwerveObject *root;          /* +0x000 a scene whose level objects FUN_0010a5d8 creates */
    ISwerveObject *field_04;      /* +0x004 a scene loaded by FUN_0011ae04; its level objects are created
                                     too */
    uint8  unknown_008[0x08];
    LevelObject *objects[120];    /* +0x010 0 = free slot (game_find_free_object_slot) */
    uint8  unknown_1f0[0x08];
    int    field_1f8;             /* +0x1f8 GUESS: the player's level object; its +0x20c is the current
                                     target */
    uint8  unknown_1fc[0x18];
    struct KHApp *app;            /* +0x214 */
} Game;

/* The Swerve vtable slots game_create_objects calls, past the shared ISwerveObjectVtbl ones (GUESS:
 * names, from the JSR-184 methods they implement in swv21brew). */
typedef struct SwerveGroupVtbl {
    ISwerveObjectVtbl object;                                            /* +0x00 slots 0-2 */
    void  *unknown_0c[0x28];
    void (*GetChildCount)(ISwerveObject *po, int *pCount);               /* +0xac slot 43, 0x01030360 */
    int  (*GetChild)(ISwerveObject *po, int index, ISwerveObject **ppo); /* +0xb0 slot 44, 0x010302ec */
} SwerveGroupVtbl;

typedef struct SwerveSkinnedMeshVtbl {
    ISwerveObjectVtbl object;                                            /* +0x00 slots 0-2 */
    void  *unknown_0c[0x31];
    int  (*GetSkeleton)(ISwerveObject *po, ISwerveObject **ppo);         /* +0xd0 slot 52, 0x01038878 */
} SwerveSkinnedMeshVtbl;

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
    int    entities[10];          /* +0x04 the item shown in each slot */
    uint8  kinds[10];             /* +0x2c 0: health +1.0, 1: MP +1, 2: munny */
    uint8  unknown_36[0x02];
    int    timeLeft[10];          /* +0x38 ms the item stays on the ground; 0 = free slot */
    uint32 munnyPerPickup;        /* +0x60 a float (its bits): 1.0, or 2.0 when the region's field_120 >= 5 */
} ItemDrops;                      /* 100 bytes */

typedef struct Enemy {
    int    vtable;                /* +0x000 slots hold self-relative offsets; +4 is enemy_update, 0 and +0xc
                                     run when the region's field_148 is set */
    int    field_04;              /* +0x004 FUN_00113524 fills +0x04.. (GUESS: its position) */
    int    field_08;              /* +0x008 */
    uint8  unknown_0c[0x04];
    int    field_10;              /* +0x010 FUN_00113cc4 fills +0x10.. from field_20 */
    int    field_14;              /* +0x014 */
    uint8  unknown_18[0x04];
    int    number;                /* +0x01c 1, 2, ...: its place among the region's enemies */
    int    field_20;              /* +0x020 GUESS: its model (an object) */
    int    field_24;              /* +0x024 */
    int    field_28;              /* +0x028 an object; FUN_001201cc(field_28, 0) when it dies */
    uint8  unknown_2c[0x10];
    uint32 health;                /* +0x03c a float (its bits); > 0 alive, shown in the health bar */
    struct CombatRegion *region; /* +0x040 the region that created it */
    uint8  unknown_44[0x1c];
    int    field_60;              /* +0x060 */
    int    field_64;              /* +0x064 */
    int    field_68;              /* +0x068 */
    uint8  unknown_6c[0x08];
    struct KHApp *app;            /* +0x074 GetAppInstance() at creation */
    uint8  unknown_78[0x08];
    int    mode;                  /* +0x080 1: the code at 0x0011db34 runs instead of the states (field_90) */
    uint8  unknown_84[0x04];
    int    field_88;              /* +0x088 2004: the alive behaviour runs even at 0 health */
    uint8  unknown_8c[0x04];
    int    field_90;              /* +0x090 the state while mode is 1: 7001, 7002, 7003 */
    uint8  unknown_94[0x0c];
    int    waitState;             /* +0x0a0 enemy_wait: 5001 idle, 5002 waiting */
    int    state;                 /* +0x0a4 1001 waiting, 1002 alive, 1003 dying, 1004 gone */
    uint8  unknown_a8[0x14];
    int    waitUntil;             /* +0x0bc enemy_wait: the time (ms) the wait ends */
    uint8  unknown_c0[0x38];
    int    field_f8;              /* +0x0f8 */
    uint8  unknown_fc[0x04];
    int    field_100;             /* +0x100 -1 at creation */
    int    type;                  /* +0x104 1-11, from the region's enemy name (combat_region_setup) */
    int    field_108;             /* +0x108 when set (or for type 2) its health bar is shown */
    uint8  unknown_10c[0x1c];
    int    field_128;             /* +0x128 a countdown (enemy_update subtracts the elapsed time) */
    int    field_12c;             /* +0x12c another countdown */
    int    field_130;             /* +0x130 */
    uint8  unknown_134[0x68];
    int  (*field_19c)(struct Enemy *enemy, int now);   /* +0x19c alive, mode 2 and field_130 == 0 */
    int  (*field_1a0)(struct Enemy *enemy, int now);   /* +0x1a0 alive, otherwise */
    uint8  unknown_1a4[0xcc];
    int    field_270;             /* +0x270 1 at creation */
    uint8  unknown_274[0x0c];
} Enemy;                          /* 0x280 bytes */

typedef struct CombatRegion {
    uint8  kind;                  /* +0x000 4 (LevelObject.kind) */
    uint8  unknown_001[0x03];
    LevelObject *parent;          /* +0x004 LevelObject.parent */
    int    node;                  /* +0x008 its scene node, an ISwerveObject (LevelObject.node); the setup
                                     reads its parameters from it */
    uint32 nameId;                /* +0x00c LevelObject.nameId; passed with message 0x11E3EE3E
                                     (combat_region_update) */
    uint8  unknown_10[0x74];
    struct KHApp *app;            /* +0x084 */
    uint8  unknown_88[0x88];
    int    active;                /* +0x110 0 at creation; GUESS: the player is in its area */
    ItemDrops *itemDrops;         /* +0x114 its item drops (FUN_0010b014; updated by FUN_001226e8) */
    uint32 enemyMaximumHealth;    /* +0x118 a float (its bits); level data, default 5.0 */
    uint32 field_11c;             /* +0x11c a float (its bits); level data, default 1.0 */
    int    field_120;             /* +0x120 level data; below 5 the item drops get 1.0, else 2.0 */
    int    waves;                 /* +0x124 level data */
    int    enemiesPerWave;        /* +0x128 level data */
    int    enemyCount;            /* +0x12c enemy objects: 2 for type 1, else 1; at most enemiesPerWave */
    int    state;                 /* +0x130 1 at creation; 1 waiting, 2 fighting, 3 the player left during a wave (GUESS) */
    int    wavesLeft;             /* +0x134 */
    int    enemiesLeftInWave;     /* +0x138 combat_region_take_one takes them one by one */
    int    field_13c;             /* +0x13c 1 at creation; set to 1 when state 2 ends */
    int    field_140;             /* +0x140 0 at creation */
    uint8  unknown_144[0x04];
    int    field_148;             /* +0x148 1 at creation; when set, each enemy's vtable slots 0 and +0xc
                                     run once */
    Enemy **enemies;              /* +0x14c enemyCount of them */
    int    field_150;             /* +0x150 0 at creation */
    int    field_154;             /* +0x154 0 at creation */
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
    int    vtable;                /* +0x00 0x00101650; slots hold self-relative offsets: +4 update,
                                     +8 take a hit (damage, x, y, z, player state) */
    int    entity;                /* +0x04 the scene entity it follows */
    uint32 radius;                /* +0x08 a float (its bits); not set by hitsphere_create */
    uint8  unknown_0c[0x08];
    uint32 field_14;              /* +0x14 a float (its bits); the first hitsphere's is shown in the HUD
                                     (field_d4 +0x4c, +0x50) */
    uint8  unknown_18[0x08];
    struct KHApp *app;            /* +0x20 GetAppInstance() at creation */
    struct BossCombatRegion *owner; /* +0x24 */
    uint8  unknown_28[0x1c];
    int    field_44;              /* +0x44 0 at creation */
    int    secondary;             /* +0x48 set on every hitsphere but the first */
    int    field_4c;              /* +0x4c -1 at creation */
    uint8  unknown_50[0x30];
    int    field_80;              /* +0x80 0 at creation */
    uint8  unknown_84[0x20];
    int    field_a4;              /* +0xa4 0 at creation */
    int    field_a8;              /* +0xa8 0 at creation */
    int    field_ac;              /* +0xac 0 at creation */
    uint8  unknown_b0[0x08];
    int    field_b8;              /* +0xb8 0 at creation */
    int    field_bc;              /* +0xbc 0 at creation */
    int    field_c0;              /* +0xc0 0 at creation */
    int    field_c4;              /* +0xc4 0 at creation */
    uint32 field_c8;              /* +0xc8 a float (its bits), 3.0 at creation */
    uint32 field_cc;              /* +0xcc a float (its bits), 0.3 at creation */
    int    field_d0;              /* +0xd0 0 at creation */
} Hitsphere;                      /* 0xd4 bytes */

typedef struct BossCombatRegion {
    uint8  kind;                  /* +0x000 5 (LevelObject.kind) */
    uint8  unknown_001[0x03];
    LevelObject *parent;          /* +0x004 LevelObject.parent */
    int    node;                  /* +0x008 its scene node, an ISwerveObject (LevelObject.node) */
    uint32 nameId;                /* +0x00c LevelObject.nameId */
    uint8  unknown_10[0x74];
    struct KHApp *app;            /* +0x084 */
    uint8  unknown_88[0x88];
    int    active;                /* +0x110 0 at creation; GUESS: the player is in its area (FUN_00123d7c) */
    ItemDrops *itemDrops;         /* +0x114 its item drops (updated by FUN_001226e8) */
    int   *field_118;             /* +0x118 more scene entities named in the level data (field_12c of them) */
    int    extraEntity;           /* +0x11c one more scene entity (id 0x2E583064): it can be targeted within
                                     3.0, and a hit hides it and clears its +0x34 (targetable) */
    Hitsphere **hitspheres;       /* +0x120 */
    uint32 field_124;             /* +0x124 a float (its bits), 1.0 at creation */
    int    hitsphereCount;        /* +0x128 */
    int    field_12c;             /* +0x12c how many field_118 holds */
    int    field_130;             /* +0x130 1 at creation; when set, FUN_00123d7c runs each hitsphere's
                                     vtable slot 0 and fills the HUD from the first one, then clears it */
    uint8  unknown_134[0x08];
} BossCombatRegion;               /* 0x13c bytes */

#endif /* KH_TYPES_H */
