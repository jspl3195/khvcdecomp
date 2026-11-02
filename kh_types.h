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
    struct Animations *animations;   /* +0x9c the scene's animations; created by animations_create,
                                        destroyed by 0x10c9dc */
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

/* A level object's collision shape (GUESS: names), 0x48 bytes (collision_shape_create), filled by
 * collision_shape_setup from a text: its first word starts with "inner" or "outer" and ends with the
 * form ("circle", "cylinder", "cuboid", "rect", "sphere", "poly"); the next words give the sizes, or
 * "use verts" for the size of the entity's vertices. */
typedef struct CollisionShape {
    int    kind;                  /* +0x00 1 "inner", 2 "outer" */
    int    form;                  /* +0x04 3 circle, 4 cylinder, 5 cuboid, 6 rect, 7 sphere, 8 poly */
    uint32 position[3];           /* +0x08 floats (their bits): the entity's position (FUN_001147ec) */
    uint32 minimum[3];            /* +0x14 floats: the box around it */
    uint32 maximum[3];            /* +0x20 floats */
    uint32 radius;                /* +0x2c a float (its bits) */
    uint32 height;                /* +0x30 a float (its bits); level_object_get_height */
    struct KHApp *app;            /* +0x34 GetAppInstance() at creation */
    uint32 *vertices;             /* +0x38 floats, 3 per vertex (a "poly", or the 4 corners of a "rect") */
    int    vertexCount;           /* +0x3c */
    int    clockwise;             /* +0x40 a "poly": the entity's "Clockwise" tag */
    int   *vertexEntities;        /* +0x44 a "poly": the entities named "%dtransform", one per vertex */
} CollisionShape;                 /* 0x48 bytes */

typedef struct LevelObject {
    uint8  kind;                  /* +0x000 0 LevelObject, 1 MotionEntity, 2 Character (FUN_0010b70c,
                                     0x338 bytes), 3 "Camera" (FUN_0010b3e8, 0x214 bytes), 4 CombatRegion,
                                     5 BossCombatRegion; 2 and 3 are MotionEntity subclasses */
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
    int    sceneShapeCount;       /* +0x0e0 0 at creation */
    CollisionShape *shapes[2];    /* +0x0e4 the shapes its node's user parameter 0x2101870D lists */
    int    shapeCount;            /* +0x0ec 0 at creation */
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
    uint8  unknown_001[0x07];     /* the LevelObject fields, where not named */
    ISwerveObject *node;          /* +0x008 LevelObject.node: handed the position (slot +0x4c) and the
                                     heading (slot +0x5c) by motion_entity_turn */
    uint8  unknown_00c[0x5c];
    uint32 position[3];           /* +0x068 LevelObject.position */
    uint8  unknown_074[0x10];
    struct KHApp *app;            /* +0x084 LevelObject.app */
    uint8  unknown_088[0x88];
    int    field_110;             /* +0x110 0 at creation */
    int    field_114;             /* +0x114 0 at creation */
    uint8  unknown_118[0x10];
    LevelObject *orbitCenter;     /* +0x128 0 at creation; when set, motion_entity_turn moves the entity
                                     around it (the camera around its target) */
    int    field_12c;             /* +0x12c 0 at creation */
    uint32 pitch;                 /* +0x130 a float (its bits): the up/down angle, in degrees, -180..180
                                     (motion_entity_get_pitch / _set_pitch / _pitch_by) */
    uint8  unknown_134[0x0c];
    uint32 heading;               /* +0x140 a float (its bits): the direction it faces, in degrees,
                                     -180..180 (motion_entity_get_heading / _turn / _start_turn) */
    uint8  unknown_144[0x10];
    int    turning;               /* +0x154 0 at creation; 1 while a turn started by motion_entity_start_turn
                                     runs */
    ISwerveObject *field_158;     /* +0x158 0 at creation; a Swerve object that is handed &pitch through its
                                     slot +0x5c whenever the pitch changes (GUESS: a tilting child node) */
    uint8  unknown_15c[0x64];
    uint32 turnAngle;             /* +0x1c0 a float (its bits): the angle left to turn, positive */
    uint32 turnSpeed;             /* +0x1c4 a float (its bits): the turn speed, its sign the direction */
} MotionEntity;                   /* 0x1c8 bytes */

/* "Character" (kind 2, 0x338 bytes, FUN_0010b70c; GUESS: names): the player's character, a MotionEntity.
 * It plays its animations on three channels (character_play_animation): channel 0 alone, or channels 2
 * and 3 together (GUESS: two body parts); a request on 2 or 3 stops channel 0, and one on 0 stops 2 and 3. */
typedef struct Character {
    uint8  kind;                  /* +0x000 2 (LevelObject.kind) */
    uint8  unknown_001[0x07];     /* the LevelObject and MotionEntity fields, where not named */
    int    node;                  /* +0x008 its scene node, an ISwerveObject (LevelObject.node) */
    uint8  unknown_00c[0x40];
    int    field_4c;              /* +0x04c set to 1 by character_setup */
    uint8  unknown_050[0x34];
    struct KHApp *app;            /* +0x084 LevelObject.app */
    uint8  unknown_088[0x154];
    ISwerveObject *field_1dc;     /* +0x1dc the game scene's object with user id 0x0F846A96 (Find); its
                                     slot +0x48 fills field_1f8 */
    ISwerveObject *field_1e0;     /* +0x1e0 the object with user id 0x0D44B786 */
    ISwerveObject *field_1e4;     /* +0x1e4 the object with user id 0x1DFBEC7F; its slot +0x8c is called
                                     with 0 */
    ISwerveObject *field_1e8;     /* +0x1e8 the object with user id 0x314D49C5 */
    ISwerveObject *field_1ec;     /* +0x1ec the object with user id 0x0A893452 */
    ISwerveObject *shadow;        /* +0x1f0 the scene "CharacterShadow" (FUN_0011ae04) */
    int    hasShadow;             /* +0x1f4 1 when shadow was loaded */
    int    field_1f8;             /* +0x1f8 filled by field_1dc's slot +0x48 */
    uint8  unknown_1fc[0x38];
    LevelObject *field_234;       /* +0x234 the level object named by hash 0x2BB0C920 (FUN_00112dbc) */
    LevelObject *field_238;       /* +0x238 the level object named by hash 0x19DB98DB */
    uint8  unknown_23c[0x4c];
    uint32 field_288;             /* +0x288 a float (its bits); level data 0x1218EC09 */
    uint32 field_28c;             /* +0x28c a float (its bits); level data 0x2073D363 */
    uint8  unknown_290[0x04];
    uint32 field_294;             /* +0x294 a float (its bits): FUN_00126618(level data 0x1932DEDD, 1000.0) */
    uint8  unknown_298[0x0c];
    int    layered;               /* +0x2a4 0 at creation; 1 while channels 2 and 3 are in use */
    uint8  unknown_2a8[0x04];
    int    animation;             /* +0x2ac the animation on channel 0, -1 none */
    int    channelTwoAnimation;   /* +0x2b0 the animation on channel 2, -1 none */
    int    channelThreeAnimation; /* +0x2b4 the animation on channel 3, -1 none */
    int    animations[29];        /* +0x2b8 its animations' indexes, found by user id (character_setup); 9-12
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
    uint8  unknown_1f0[0x08];
    struct Character *character;  /* +0x1f8 the player's character (FUN_0010a5d8 creates it from the scene's
                                     entity 0x0AD65F3D); its +0x20c is the current target */
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

/* The Swerve Object3D vtable slots kh.mod calls, shared by every object class (GUESS: names, from the
 * JSR-184 methods they implement in swv21brew, 0x0103517c fills them). */
typedef struct SwerveObject3DVtbl {
    ISwerveObjectVtbl object;                                            /* +0x00 slots 0-2 */
    void (*GetUserId)(ISwerveObject *po, int *pUserId);                  /* +0x0c slot 3, 0x010350fc */
    void  *unknown_10;
    void (*GetAnimationTrackCount)(ISwerveObject *po, int *pCount);      /* +0x14 slot 5, 0x01034f74 */
    int  (*GetAnimationTrack)(ISwerveObject *po, int index, ISwerveObject **ppo); /* +0x18 slot 6, 0x01034f00 */
    void  *unknown_1c[0x02];
    int  (*Animate)(ISwerveObject *po, int worldTime, int *pResult);     /* +0x24 slot 9, 0x01034da8 */
    int  (*Find)(ISwerveObject *po, int userId, ISwerveObject **ppo);    /* +0x28 slot 10, 0x01034e8c */
} SwerveObject3DVtbl;

typedef struct SwerveAnimationTrackVtbl {
    ISwerveObjectVtbl object;                                            /* +0x00 slots 0-2 */
    void  *unknown_0c[0x10];                                             /* the Object3D slots and more */
    int  (*GetController)(ISwerveObject *po, ISwerveObject **ppo);       /* +0x4c slot 19, 0x0102d1c0 */
    void  *unknown_50;
    int  (*GetKeyframeSequence)(ISwerveObject *po, ISwerveObject **ppo); /* +0x54 slot 21, 0x0102d22c */
} SwerveAnimationTrackVtbl;

typedef struct SwerveKeyframeSequenceVtbl {
    ISwerveObjectVtbl object;                                            /* +0x00 slots 0-2 */
    void  *unknown_0c[0x10];
    void (*GetDuration)(ISwerveObject *po, int *pDuration);              /* +0x4c slot 19, 0x01032ac0 */
} SwerveKeyframeSequenceVtbl;

typedef struct SwerveAnimationControllerVtbl {
    ISwerveObjectVtbl object;                                            /* +0x00 slots 0-2 */
    void  *unknown_0c[0x14];
    int  (*SetActiveInterval)(ISwerveObject *po, int start, int end);    /* +0x5c slot 23, 0x0102cf84 */
    void  *unknown_60;
    int  (*SetPosition)(ISwerveObject *po, uint32 sequenceTime, int worldTime); /* +0x64 slot 25, 0x0102cfec;
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
    int    elapsed;               /* +0x008 ms since the last update (animations_update) */
    int    worldTime;             /* +0x00c the time the controllers are set at (animations_update) */
    int    userIds[100];          /* +0x010 the controllers' user ids (animations_find); -1 = free slot */
    int    durations[100];        /* +0x1a0 the longest keyframe sequence of each controller
                                     (animations_get_duration) */
    uint8  states[100];           /* +0x330 0 free (animations_reset); 1 added, never played (stopped at the
                                     next update); 2 playing once (becomes 4 at its end); 3 looping; 4 stopped
                                     or finished (animations_stop, animations_finish, animations_update) */
    uint8  priorities[100];       /* +0x394 2 when added; on a character's animation channel a new animation
                                     replaces the playing one only when its priority is not lower
                                     (character_play_animation) */
    uint32 speeds[100];           /* +0x3f8 floats (their bits), 1.0 when added (animations_set_speed) */
    int    positions[100];        /* +0x588 where each one plays from: 0, or its last frame when its speed is
                                     not above 0 */
    ISwerveObject **controllers;  /* +0x718 100 controllers, found by user id when first played; 0 until then
                                     and after animations_release_controllers */
} Animations;                     /* 0x71c bytes */

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
    int    field_10;              /* +0x010 level_object_get_position fills +0x10.. from field_20 */
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
