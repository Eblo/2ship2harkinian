/*
 * File: z_en_an.c
 * Overlay: ovl_En_An
 * Description: Anju
 */

#include "z_en_an.h"
#include "overlays/actors/ovl_En_Door/z_en_door.h"

#include "assets/objects/object_an2/object_an2.h"
#include "assets/objects/object_an3/object_an3.h"
#include "assets/objects/object_an4/object_an4.h"
#include "assets/objects/object_mask_kerfay/object_mask_kerfay.h"
#include "assets/objects/object_msmo/object_msmo.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnAn*)thisx)

void EnAn_Init(Actor* thisx, PlayState* play);
void EnAn_Destroy(Actor* thisx, PlayState* play);
void EnAn_Update(Actor* thisx, PlayState* play);
void EnAn_Draw(Actor* thisx, PlayState* play);

// Action funcs
void func_80B577F0(EnAn* this, PlayState* play);
void func_80B578F8(EnAn* this, PlayState* play);
void func_80B57A44(EnAn* this, PlayState* play);

typedef enum AnjuScheduleResult {
    /*  0 */ ANJU_SCH_NONE,
    /*  1 */ ANJU_SCH_1,
    /*  2 */ ANJU_SCH_2,
    /*  3 */ ANJU_SCH_3,
    /*  4 */ ANJU_SCH_4,
    /*  5 */ ANJU_SCH_5,
    /*  6 */ ANJU_SCH_6,
    /*  7 */ ANJU_SCH_7,
    /*  8 */ ANJU_SCH_8,
    /*  9 */ ANJU_SCH_9,
    /* 10 */ ANJU_SCH_A,
    /* 11 */ ANJU_SCH_B,
    /* 12 */ ANJU_SCH_C,
    /* 13 */ ANJU_SCH_D,
    /* 14 */ ANJU_SCH_E,
    /* 15 */ ANJU_SCH_F,
    /* 16 */ ANJU_SCH_10,
    /* 17 */ ANJU_SCH_11,
    /* 18 */ ANJU_SCH_12,
    /* 19 */ ANJU_SCH_13,
    /* 20 */ ANJU_SCH_14,
    /* 21 */ ANJU_SCH_15,
    /* 22 */ ANJU_SCH_16,
    /* 23 */ ANJU_SCH_17,
    /* 24 */ ANJU_SCH_18,
    /* 25 */ ANJU_SCH_19,
    /* 26 */ ANJU_SCH_1A,
    /* 27 */ ANJU_SCH_1B,
    /* 28 */ ANJU_SCH_1C,
    /* 29 */ ANJU_SCH_1D,
    /* 30 */ ANJU_SCH_1E,
    /* 31 */ ANJU_SCH_1F,
    /* 32 */ ANJU_SCH_20,
    /* 33 */ ANJU_SCH_21,
    /* 34 */ ANJU_SCH_22,
    /* 35 */ ANJU_SCH_23,
    /* 36 */ ANJU_SCH_24,
    /* 37 */ ANJU_SCH_25,
    /* 38 */ ANJU_SCH_26,
    /* 39 */ ANJU_SCH_27,
    /* 40 */ ANJU_SCH_28,
    /* 41 */ ANJU_SCH_29,
    /* 42 */ ANJU_SCH_2A,
    /* 43 */ ANJU_SCH_2B,
    /* 44 */ ANJU_SCH_2C,
    /* 45 */ ANJU_SCH_2D,
    /* 46 */ ANJU_SCH_2E,
    /* 47 */ ANJU_SCH_2F,
    /* 48 */ ANJU_SCH_30,
    /* 49 */ ANJU_SCH_31,
    /* 50 */ ANJU_SCH_32,
    /* 51 */ ANJU_SCH_33,
    /* 52 */ ANJU_SCH_34,
    /* 53 */ ANJU_SCH_35,
    /* 54 */ ANJU_SCH_36,
    /* 55 */ ANJU_SCH_37,
    /* 56 */ ANJU_SCH_38,
    /* 57 */ ANJU_SCH_39,
    /* 58 */ ANJU_SCH_3A,
    /* 59 */ ANJU_SCH_3B,
    /* 60 */ ANJU_SCH_3C,
    /* 61 */ ANJU_SCH_3D,
    /* 62 */ ANJU_SCH_3E,
    /* 63 */ ANJU_SCH_3F,
    /* 64 */ ANJU_SCH_MAX // ?
} AnjuScheduleResult;

static u8 sScheduleScript[] = {
    /* 0x000 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_L(1, 0x151 - 0x005),
    /* 0x005 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_L(SCENE_YADOYA, 0x150 - 0x00A),
    /* 0x00A */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(6, 0, 10, 55, 0x14A - 0x011),
    /* 0x011 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(10, 55, 11, 10, 0x144 - 0x018),
    /* 0x018 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(11, 10, 11, 30, 0x13E - 0x01F),
    /* 0x01F */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(11, 30, 11, 50, 0x138 - 0x026),
    /* 0x026 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(11, 50, 11, 55, 0x132 - 0x02D),
    /* 0x02D */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(11, 55, 12, 0, 0x12C - 0x034),
    /* 0x034 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(12, 0, 12, 15, 0x126 - 0x03B),
    /* 0x03B */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(12, 15, 12, 20, 0x120 - 0x042),
    /* 0x042 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(12, 20, 12, 25, 0x11A - 0x049),
    /* 0x049 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(12, 25, 12, 55, 0x114 - 0x050),
    /* 0x050 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(12, 55, 13, 0, 0x10E - 0x057),
    /* 0x057 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(13, 15, 13, 20, 0x108 - 0x05E),
    /* 0x05E */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(13, 20, 13, 50, 0x102 - 0x065),
    /* 0x065 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(13, 50, 14, 8, 0x0FC - 0x06C),
    /* 0x06C */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(14, 8, 14, 18, 0x0F6 - 0x073),
    /* 0x073 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(14, 18, 16, 10, 0x0F0 - 0x079),
    /* 0x079 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(16, 10, 16, 30, 0x0EA - 0x07F),
    /* 0x07F */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(16, 30, 19, 50, 0x0E4 - 0x085),
    /* 0x085 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(19, 50, 20, 20, 0x0DE - 0x08B),
    /* 0x08B */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(20, 20, 20, 30, 0x0D8 - 0x091),
    /* 0x091 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(20, 30, 21, 5, 0x0D2 - 0x097),
    /* 0x097 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(21, 5, 21, 10, 0x0CC - 0x09D),
    /* 0x09D */ SCHEDULE_CMD_CHECK_FLAG_S(WEEKEVENTREG_PROMISED_MIDNIGHT_MEETING, 0x0A2 - 0x0A1),
    /* 0x0A1 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x0A2 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(23, 10, 23, 15, 0x0C6 - 0x0A8),
    /* 0x0A8 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(23, 15, 0, 0, 0x0C0 - 0x0AE),
    /* 0x0AE */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(0, 0, 6, 0, 0x0B5 - 0x0B4),
    /* 0x0B4 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x0B5 */ SCHEDULE_CMD_CHECK_FLAG_S(WEEKEVENTREG_HAD_MIDNIGHT_MEETING, 0x0BF - 0x0B9),
    /* 0x0B9 */ SCHEDULE_CMD_RET_TIME(0, 0, 6, 0, 23),
    /* 0x0BF */ SCHEDULE_CMD_RET_NONE(),
    /* 0x0C0 */ SCHEDULE_CMD_RET_TIME(23, 15, 0, 0, ANJU_SCH_31),
    /* 0x0C6 */ SCHEDULE_CMD_RET_TIME(23, 10, 23, 15, ANJU_SCH_1F),
    /* 0x0CC */ SCHEDULE_CMD_RET_TIME(21, 5, 21, 10, ANJU_SCH_1E),
    /* 0x0D2 */ SCHEDULE_CMD_RET_TIME(20, 30, 21, 5, ANJU_SCH_30),
    /* 0x0D8 */ SCHEDULE_CMD_RET_TIME(20, 20, 20, 30, ANJU_SCH_13),
    /* 0x0DE */ SCHEDULE_CMD_RET_TIME(19, 50, 20, 20, ANJU_SCH_2F),
    /* 0x0E4 */ SCHEDULE_CMD_RET_TIME(16, 30, 19, 50, ANJU_SCH_12),
    /* 0x0EA */ SCHEDULE_CMD_RET_TIME(16, 10, 16, 30, ANJU_SCH_11),
    /* 0x0F0 */ SCHEDULE_CMD_RET_TIME(14, 18, 16, 10, ANJU_SCH_12),
    /* 0x0F6 */ SCHEDULE_CMD_RET_TIME(14, 8, 14, 18, ANJU_SCH_10),
    /* 0x0FC */ SCHEDULE_CMD_RET_TIME(13, 50, 14, 8, ANJU_SCH_12),
    /* 0x102 */ SCHEDULE_CMD_RET_TIME(13, 20, 13, 50, ANJU_SCH_2E),
    /* 0x108 */ SCHEDULE_CMD_RET_TIME(13, 15, 13, 20, ANJU_SCH_1D),
    /* 0x10E */ SCHEDULE_CMD_RET_TIME(12, 55, 13, 0, ANJU_SCH_1C),
    /* 0x114 */ SCHEDULE_CMD_RET_TIME(12, 25, 12, 55, ANJU_SCH_2D),
    /* 0x11A */ SCHEDULE_CMD_RET_TIME(12, 20, 12, 25, ANJU_SCH_1B),
    /* 0x120 */ SCHEDULE_CMD_RET_TIME(12, 15, 12, 20, ANJU_SCH_2C),
    /* 0x126 */ SCHEDULE_CMD_RET_TIME(12, 0, 12, 15, ANJU_SCH_15),
    /* 0x12C */ SCHEDULE_CMD_RET_TIME(11, 55, 12, 0, ANJU_SCH_2B),
    /* 0x132 */ SCHEDULE_CMD_RET_TIME(11, 50, 11, 55, ANJU_SCH_1A),
    /* 0x138 */ SCHEDULE_CMD_RET_TIME(11, 30, 11, 50, ANJU_SCH_2A),
    /* 0x13E */ SCHEDULE_CMD_RET_TIME(11, 10, 11, 30, ANJU_SCH_E),
    /* 0x144 */ SCHEDULE_CMD_RET_TIME(10, 55, 11, 10, ANJU_SCH_28),
    /* 0x14A */ SCHEDULE_CMD_RET_TIME(6, 0, 10, 55, ANJU_SCH_12),
    /* 0x150 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x151 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_L(2, 0x391 - 0x156),
    /* 0x156 */ SCHEDULE_CMD_CHECK_FLAG_L(WEEKEVENTREG_HAD_MIDNIGHT_MEETING, 0x29E - 0x15B),
    /* 0x15B */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_L(SCENE_YADOYA, 0x1F2 - 0x160),
    /* 0x160 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(11, 3, 11, 9, 0x1EC - 0x167),
    /* 0x167 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 9, 11, 29, 0x1E6 - 0x16D),
    /* 0x16D */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 29, 11, 39, 0x1E0 - 0x173),
    /* 0x173 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(17, 24, 17, 30, 0x1DA - 0x179),
    /* 0x179 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(17, 30, 17, 55, 0x1D4 - 0x17F),
    /* 0x17F */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(17, 55, 18, 0, 0x1CE - 0x185),
    /* 0x185 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(18, 0, 19, 50, 0x1C8 - 0x18B),
    /* 0x18B */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(19, 50, 20, 20, 0x1C2 - 0x191),
    /* 0x191 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(20, 20, 20, 30, 0x1BC - 0x197),
    /* 0x197 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(20, 30, 21, 0, 0x1B6 - 0x19D),
    /* 0x19D */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(21, 0, 21, 5, 0x1B0 - 0x1A3),
    /* 0x1A3 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(21, 30, 23, 0, 0x1AA - 0x1A9),
    /* 0x1A9 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x1AA */ SCHEDULE_CMD_RET_TIME(21, 30, 23, 0, ANJU_SCH_18),
    /* 0x1B0 */ SCHEDULE_CMD_RET_TIME(21, 0, 21, 5, ANJU_SCH_1E),
    /* 0x1B6 */ SCHEDULE_CMD_RET_TIME(20, 30, 21, 0, ANJU_SCH_30),
    /* 0x1BC */ SCHEDULE_CMD_RET_TIME(20, 20, 20, 30, ANJU_SCH_13),
    /* 0x1C2 */ SCHEDULE_CMD_RET_TIME(19, 50, 20, 20, ANJU_SCH_2F),
    /* 0x1C8 */ SCHEDULE_CMD_RET_TIME(18, 0, 19, 50, ANJU_SCH_12),
    /* 0x1CE */ SCHEDULE_CMD_RET_TIME(17, 55, 18, 0, ANJU_SCH_23),
    /* 0x1D4 */ SCHEDULE_CMD_RET_TIME(17, 30, 17, 55, ANJU_SCH_33),
    /* 0x1DA */ SCHEDULE_CMD_RET_TIME(17, 24, 17, 30, ANJU_SCH_22),
    /* 0x1E0 */ SCHEDULE_CMD_RET_TIME(11, 29, 11, 39, ANJU_SCH_21),
    /* 0x1E6 */ SCHEDULE_CMD_RET_TIME(11, 9, 11, 29, ANJU_SCH_32),
    /* 0x1EC */ SCHEDULE_CMD_RET_TIME(11, 3, 11, 9, ANJU_SCH_20),
    /* 0x1F2 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_TOWN, 0x23F - 0x1F6),
    /* 0x1F6 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 29, 11, 39, 0x239 - 0x1FC),
    /* 0x1FC */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 39, 12, 25, 0x233 - 0x202),
    /* 0x202 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(12, 25, 13, 15, 0x22D - 0x208),
    /* 0x208 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(15, 55, 16, 45, 0x227 - 0x20E),
    /* 0x20E */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(16, 45, 17, 24, 0x221 - 0x214),
    /* 0x214 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(17, 24, 17, 30, 0x21B - 0x21A),
    /* 0x21A */ SCHEDULE_CMD_RET_NONE(),
    /* 0x21B */ SCHEDULE_CMD_RET_TIME(17, 24, 17, 30, ANJU_SCH_26),
    /* 0x221 */ SCHEDULE_CMD_RET_TIME(16, 45, 17, 24, ANJU_SCH_3B),
    /* 0x227 */ SCHEDULE_CMD_RET_TIME(15, 55, 16, 45, ANJU_SCH_3A),
    /* 0x22D */ SCHEDULE_CMD_RET_TIME(12, 25, 13, 15, ANJU_SCH_37),
    /* 0x233 */ SCHEDULE_CMD_RET_TIME(11, 39, 12, 25, ANJU_SCH_36),
    /* 0x239 */ SCHEDULE_CMD_RET_TIME(11, 29, 11, 39, ANJU_SCH_25),
    /* 0x23F */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_CLOCKTOWER, 0x274 - 0x243),
    /* 0x243 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 39, 12, 25, 0x26E - 0x249),
    /* 0x249 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(12, 25, 13, 15, 0x268 - 0x24F),
    /* 0x24F */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(15, 55, 16, 45, 0x262 - 0x255),
    /* 0x255 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(16, 45, 17, 24, 0x25C - 0x25B),
    /* 0x25B */ SCHEDULE_CMD_RET_NONE(),
    /* 0x25C */ SCHEDULE_CMD_RET_TIME(16, 45, 17, 24, ANJU_SCH_3F),
    /* 0x262 */ SCHEDULE_CMD_RET_TIME(15, 55, 16, 45, ANJU_SCH_3E),
    /* 0x268 */ SCHEDULE_CMD_RET_TIME(12, 25, 13, 15, ANJU_SCH_3D),
    /* 0x26E */ SCHEDULE_CMD_RET_TIME(11, 39, 12, 25, ANJU_SCH_3C),
    /* 0x274 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_ALLEY, 0x29D - 0x278),
    /* 0x278 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(13, 15, 13, 45, 0x297 - 0x27E),
    /* 0x27E */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(13, 45, 15, 25, 0x291 - 0x284),
    /* 0x284 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(15, 25, 15, 55, 0x28B - 0x28A),
    /* 0x28A */ SCHEDULE_CMD_RET_NONE(),
    /* 0x28B */ SCHEDULE_CMD_RET_TIME(15, 25, 15, 55, ANJU_SCH_39),
    /* 0x291 */ SCHEDULE_CMD_RET_TIME(13, 45, 15, 25, ANJU_SCH_3),
    /* 0x297 */ SCHEDULE_CMD_RET_TIME(13, 15, 13, 45, ANJU_SCH_38),
    /* 0x29D */ SCHEDULE_CMD_RET_NONE(),
    /* 0x29E */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_L(SCENE_YADOYA, 0x390 - 0x2A3),
    /* 0x2A3 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(6, 0, 10, 55, 0x38A - 0x2AA),
    /* 0x2AA */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(10, 55, 11, 10, 0x384 - 0x2B1),
    /* 0x2B1 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(11, 10, 11, 30, 0x37E - 0x2B8),
    /* 0x2B8 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(11, 30, 11, 50, 0x378 - 0x2BF),
    /* 0x2BF */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(11, 50, 11, 55, 0x372 - 0x2C6),
    /* 0x2C6 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(11, 55, 12, 0, 0x36C - 0x2CD),
    /* 0x2CD */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(12, 0, 12, 15, 0x366 - 0x2D4),
    /* 0x2D4 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(12, 15, 12, 20, 0x360 - 0x2DB),
    /* 0x2DB */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(12, 20, 12, 25, 0x35A - 0x2E1),
    /* 0x2E1 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(12, 25, 12, 55, 0x354 - 0x2E7),
    /* 0x2E7 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(12, 55, 13, 0, 0x34E - 0x2ED),
    /* 0x2ED */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(13, 15, 13, 20, 0x348 - 0x2F3),
    /* 0x2F3 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(13, 20, 13, 50, 0x342 - 0x2F9),
    /* 0x2F9 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(13, 50, 19, 50, 0x33C - 0x2FF),
    /* 0x2FF */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(19, 50, 20, 20, 0x336 - 0x305),
    /* 0x305 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(20, 20, 20, 30, 0x330 - 0x30B),
    /* 0x30B */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(20, 30, 21, 5, 0x32A - 0x311),
    /* 0x311 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(21, 5, 21, 10, 0x324 - 0x317),
    /* 0x317 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(21, 30, 23, 0, 0x31E - 0x31D),
    /* 0x31D */ SCHEDULE_CMD_RET_NONE(),
    /* 0x31E */ SCHEDULE_CMD_RET_TIME(21, 30, 23, 0, ANJU_SCH_18),
    /* 0x324 */ SCHEDULE_CMD_RET_TIME(21, 5, 21, 10, ANJU_SCH_1E),
    /* 0x32A */ SCHEDULE_CMD_RET_TIME(20, 30, 21, 5, ANJU_SCH_30),
    /* 0x330 */ SCHEDULE_CMD_RET_TIME(20, 20, 20, 30, ANJU_SCH_13),
    /* 0x336 */ SCHEDULE_CMD_RET_TIME(19, 50, 20, 20, ANJU_SCH_2F),
    /* 0x33C */ SCHEDULE_CMD_RET_TIME(13, 50, 19, 50, ANJU_SCH_12),
    /* 0x342 */ SCHEDULE_CMD_RET_TIME(13, 20, 13, 50, ANJU_SCH_2E),
    /* 0x348 */ SCHEDULE_CMD_RET_TIME(13, 15, 13, 20, ANJU_SCH_1D),
    /* 0x34E */ SCHEDULE_CMD_RET_TIME(12, 55, 13, 0, ANJU_SCH_1C),
    /* 0x354 */ SCHEDULE_CMD_RET_TIME(12, 25, 12, 55, ANJU_SCH_2D),
    /* 0x35A */ SCHEDULE_CMD_RET_TIME(12, 20, 12, 25, ANJU_SCH_1B),
    /* 0x360 */ SCHEDULE_CMD_RET_TIME(12, 15, 12, 20, ANJU_SCH_2C),
    /* 0x366 */ SCHEDULE_CMD_RET_TIME(12, 0, 12, 15, ANJU_SCH_15),
    /* 0x36C */ SCHEDULE_CMD_RET_TIME(11, 55, 12, 0, ANJU_SCH_2B),
    /* 0x372 */ SCHEDULE_CMD_RET_TIME(11, 50, 11, 55, ANJU_SCH_1A),
    /* 0x378 */ SCHEDULE_CMD_RET_TIME(11, 30, 11, 50, ANJU_SCH_2A),
    /* 0x37E */ SCHEDULE_CMD_RET_TIME(11, 10, 11, 30, ANJU_SCH_E),
    /* 0x384 */ SCHEDULE_CMD_RET_TIME(10, 55, 11, 10, ANJU_SCH_28),
    /* 0x38A */ SCHEDULE_CMD_RET_TIME(6, 0, 10, 55, ANJU_SCH_12),
    /* 0x390 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x391 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_L(3, 0x447 - 0x396),
    /* 0x396 */ SCHEDULE_CMD_CHECK_FLAG_S(WEEKEVENTREG_DELIVERED_PENDANT_OF_MEMORIES, 0x3ED - 0x39A),
    /* 0x39A */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_YADOYA, 0x3DB - 0x39E),
    /* 0x39E */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(6, 0, 11, 0, 0x3D5 - 0x3A4),
    /* 0x3A4 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 0, 11, 25, 0x3CF - 0x3AA),
    /* 0x3AA */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 25, 11, 30, 0x3C9 - 0x3B0),
    /* 0x3B0 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 30, 11, 50, 0x3C3 - 0x3B6),
    /* 0x3B6 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 50, 12, 0, 0x3BD - 0x3BC),
    /* 0x3BC */ SCHEDULE_CMD_RET_NONE(),
    /* 0x3BD */ SCHEDULE_CMD_RET_TIME(11, 50, 12, 0, ANJU_SCH_27),
    /* 0x3C3 */ SCHEDULE_CMD_RET_TIME(11, 30, 11, 50, ANJU_SCH_35),
    /* 0x3C9 */ SCHEDULE_CMD_RET_TIME(11, 25, 11, 30, ANJU_SCH_24),
    /* 0x3CF */ SCHEDULE_CMD_RET_TIME(11, 0, 11, 25, ANJU_SCH_34),
    /* 0x3D5 */ SCHEDULE_CMD_RET_TIME(6, 0, 11, 0, ANJU_SCH_16),
    /* 0x3DB */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_OMOYA, 0x3EC - 0x3DF),
    /* 0x3DF */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(18, 0, 6, 0, 0x3E6 - 0x3E5),
    /* 0x3E5 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x3E6 */ SCHEDULE_CMD_RET_TIME(18, 0, 6, 0, ANJU_SCH_C),
    /* 0x3EC */ SCHEDULE_CMD_RET_NONE(),
    /* 0x3ED */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_YADOYA, 0x446 - 0x3F1),
    /* 0x3F1 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(6, 0, 11, 0, 0x440 - 0x3F7),
    /* 0x3F7 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 0, 11, 25, 0x43A - 0x3FD),
    /* 0x3FD */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 25, 11, 30, 0x434 - 0x403),
    /* 0x403 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 30, 11, 50, 0x42E - 0x409),
    /* 0x409 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 50, 12, 0, 0x428 - 0x40F),
    /* 0x40F */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(18, 0, 5, 0, 0x422 - 0x415),
    /* 0x415 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(5, 0, 6, 0, 0x41C - 0x41B),
    /* 0x41B */ SCHEDULE_CMD_RET_NONE(),
    /* 0x41C */ SCHEDULE_CMD_RET_TIME(5, 0, 6, 0, ANJU_SCH_1),
    /* 0x422 */ SCHEDULE_CMD_RET_TIME(18, 0, 5, 0, ANJU_SCH_1),
    /* 0x428 */ SCHEDULE_CMD_RET_TIME(11, 50, 12, 0, ANJU_SCH_27),
    /* 0x42E */ SCHEDULE_CMD_RET_TIME(11, 30, 11, 50, ANJU_SCH_35),
    /* 0x434 */ SCHEDULE_CMD_RET_TIME(11, 25, 11, 30, ANJU_SCH_24),
    /* 0x43A */ SCHEDULE_CMD_RET_TIME(11, 0, 11, 25, ANJU_SCH_34),
    /* 0x440 */ SCHEDULE_CMD_RET_TIME(6, 0, 11, 0, ANJU_SCH_16),
    /* 0x446 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x447 */ SCHEDULE_CMD_RET_NONE(),
};

static s32 sSearchTimePathLimit[ANJU_SCH_MAX] = {
    -1, // ANJU_SCH_NONE
    10, // ANJU_SCH_1
    -1, // ANJU_SCH_2
    0,  // ANJU_SCH_3
    -1, // ANJU_SCH_4
    -1, // ANJU_SCH_5
    -1, // ANJU_SCH_6
    -1, // ANJU_SCH_7
    -1, // ANJU_SCH_8
    -1, // ANJU_SCH_9
    -1, // ANJU_SCH_A
    -1, // ANJU_SCH_B
    -1, // ANJU_SCH_C
    -1, // ANJU_SCH_D
    0,  // ANJU_SCH_E
    -1, // ANJU_SCH_F
    10, // ANJU_SCH_10
    10, // ANJU_SCH_11
    10, // ANJU_SCH_12
    11, // ANJU_SCH_13
    -1, // ANJU_SCH_14
    4,  // ANJU_SCH_15
    22, // ANJU_SCH_16
    15, // ANJU_SCH_17
    -1, // ANJU_SCH_18
    -1, // ANJU_SCH_19
    3,  // ANJU_SCH_1A
    6,  // ANJU_SCH_1B
    8,  // ANJU_SCH_1C
    9,  // ANJU_SCH_1D
    13, // ANJU_SCH_1E
    14, // ANJU_SCH_1F
    16, // ANJU_SCH_20
    18, // ANJU_SCH_21
    19, // ANJU_SCH_22
    21, // ANJU_SCH_23
    23, // ANJU_SCH_24
    0,  // ANJU_SCH_25
    5,  // ANJU_SCH_26
    25, // ANJU_SCH_27
    0,  // ANJU_SCH_28
    1,  // ANJU_SCH_29
    2,  // ANJU_SCH_2A
    4,  // ANJU_SCH_2B
    5,  // ANJU_SCH_2C
    7,  // ANJU_SCH_2D
    10, // ANJU_SCH_2E
    11, // ANJU_SCH_2F
    12, // ANJU_SCH_30
    15, // ANJU_SCH_31
    17, // ANJU_SCH_32
    20, // ANJU_SCH_33
    22, // ANJU_SCH_34
    24, // ANJU_SCH_35
    1,  // ANJU_SCH_36
    2,  // ANJU_SCH_37
    0,  // ANJU_SCH_38
    1,  // ANJU_SCH_39
    3,  // ANJU_SCH_3A
    4,  // ANJU_SCH_3B
    0,  // ANJU_SCH_3C
    1,  // ANJU_SCH_3D
    2,  // ANJU_SCH_3E
    3,  // ANJU_SCH_3F
};

s32 D_80B58718[0x1B] = {
    0x00560800, 0x44090000, 0x0E28BA0C, 0x09000017, 0x0E28BB0C, 0x09000018, 0x0E28BC0C, 0x09000017, 0x0E28BD0C,
    0x09000018, 0x0E28BE0C, 0x09000017, 0x0E28BF0C, 0x09000018, 0x0E28C02D, 0x00012D00, 0x0B0C0900, 0x00115608,
    0x10090000, 0x0E295C0C, 0x09000017, 0x0E295D0C, 0x09000018, 0x0E295E2D, 0x00012D00, 0x0B0C0900, 0x00100000,
};
s32 D_80B58784[0x21] = {
    0x09000000, 0x4B10001E, 0x0E28B10C, 0x09000017, 0x0E28B20C, 0x09000018, 0x0E28B32D, 0x00011137, 0x020C0900,
    0x00100056, 0x10002E0E, 0x28B10C09, 0x0000170E, 0x28B50C09, 0x0000180E, 0x28B60C09, 0x0000170E, 0x28B70C09,
    0x0000180E, 0x28B82D00, 0x010C0900, 0x00115610, 0x10090000, 0x170E2956, 0x0C090000, 0x180E2957, 0x0C090000,
    0x170E2958, 0x0C090000, 0x180E2959, 0x2D00010C, 0x09000012, 0x10000000,
};
s32 D_80B58808[0x15] = {
    0x09000017, 0x0E28C70C, 0x09000018, 0x0E28C80C, 0x09000017, 0x0E28C90C, 0x09000018,
    0x0E28CA0C, 0x09000017, 0x0E28CB0C, 0x09000018, 0x0E28CC0C, 0x09000017, 0x0E28CD0C,
    0x09000018, 0x0E28CE0C, 0x09000017, 0x0E28CF2D, 0x12D00,    0x0E0C0900, 0x100000,
};
s32 D_80B5885C[0x37] = {
    0x220B0000, 0x69002020, 0x64004B,   0x1000B700, 0x370100AA, 0x370200,   0x550E28A0, 0x0C090000,
    0x0F28A80C, 0x05000000, 0x30000030, 0x0E28A90C, 0x0F28AA0C, 0x0F28AB0C, 0x120600A0, 0x1300,
    0xA02F0000, 0x2E2D0014, 0x0C114B10, 0x0700000E, 0x28AD2D00, 0x010C2400, 0x41161031, 0x0E28A30C,
    0x0900000F, 0x28A52D00, 0x010C1137, 0x01100020, 0x2000340E, 0x28A00C09, 0xF28,      0xA10C0500,
    0xF00,      0x300E28,   0xA20C0900, 0xF28A3,    0x0C190008, 0x310E28A4, 0x0C090000, 0x0F28A52D,
    0x10C11,    0x20201023, 0x400012,   0x0E28A00C, 0x0900000F, 0x28A62D00, 0x010C2400, 0x40100E28,
    0xA72D0001, 0x0C102300, 0x41000B0E, 0x28AC2D00, 0x010C2400, 0x41100E28, 0xAD0C1000,
};
s32 D_80B58938[3] = { 0x0E18852D, 0x10C12, 0x10000000 };
s32 D_80B58944[2] = { 0x0E28AF2D, 0x10C10 };
s32 D_80B5894C[2] = { 0x0E28C12D, 0x10C10 };
s32 D_80B58954[0xB] = {
    0x350100,   0x1C0E28C3, 0x0C0F28C4, 0x0C150900, 0xE28C5,    0x2D00010C,
    0x15090000, 0x11350112, 0x100E28C2, 0x2D00010C, 0x10000000,
};
s32 D_80B58980[2] = { 0x0E28C62D, 0x10C10 };
s32 D_80B58988[3] = { 0x0E28F70C, 0x0F28F82D, 0x10C10 };
s32 D_80B58994[2] = { 0x0E28F82D, 0x10C10 };
s32 D_80B5899C[4] = { 0x0E28F90C, 0x0F28FA0C, 0x0F28FB2D, 0x10C10 };
s32 D_80B589AC[0x14] = {
    0x0E28D70C, 0x0F28D80C, 0x0F28D90C, 0x0F28DA0C, 0x0F28DB0C, 0x05000700, 0x731,
    0x0E28D919, -0x16CFF2,  0x28DC0C11, 0x32201132, 0x10120600, 0xAA000013, 0xAA2F00,
    0x2E2D00,   0x012D0017, 0x2D00160C, 0x0700000E, 0x28DE0C15, 0x09000010,
};
s32 D_80B589FC[2] = { 0x0E28D62D, 0x10C10 };
s32 D_80B58A04[8] = {
    0x522000, 0x100E294F, 0x0C0F2950, 0x2D00010C, 0x12115220, 0x100E2951, 0x2D00010C, 0x12100000,
};
s32 D_80B58A24[6] = { 0x524000, 0x0B0E2952, 0x2D00010C, 0x11524010, 0x0E29532D, 0x10C10 };
s32 D_80B58A3C[2] = { 0x0E28E02D, 0x10C10 };
s32 D_80B58A44[0x1E] = {
    0x320800,   0x080E28D5, 0x2D00010C, 0x10003220,  0x80E28,    -0x2BD2FFFF, 0x0C100033, 0x01001A25,
    0x30001D,   0x27000300, 0x080E28E3, 0x2D00010C,  0x100E28E2, 0x2D00010C,  0x100E28E1, 0x2D00010C,
    0x100E28E4, 0x0C0E00FF, 0x1E003600, 0x0E000000,  0x0C2C28E7, 0x0C2F0000,  0x2D00010C, 0x1012102C,
    0x28E50C2F, 0xC2A,      0x300F28,   -0x19D2FFFF, 0x2D001A0C, 0x11330110,
};
s32 D_80B58ABC[2] = { 0x0E28D02D, 0x10C10 };
s32 D_80B58AC4[9] = {
    0x320800, 0x160E28D1, 0x0C0F28D2, 0x0C0F28D3, 0x2D00152D, 0x10C11, 0x3208100E, 0x28D32D00, 0x010C1000,
};
s32 D_80B58AE8[3] = { 0x0E28DF2D, 0x10C12, 0x10000000 };
s32 D_80B58AF4[0x12] = {
    0x372000,    0x29003208, 0x2A0E28,   -0x17F3EAF7, 0xE28,      -0x16F3F0D8, -0x15F3EAF7, 0xE28,   -0x14F3F0D8,
    -0x13D2FFFF, 0x0C121137, 0x20100E28, -0x13F3EDF0, 0x0E28EE0C, 0x0F28EB0C,  0x0F28EC2D,  0x10C12, 0x11372010,
};
s32 D_80B58B3C[0x10] = {
    0x372000,   0x21003208, 0x220E28,    -0x17F3F0D8, -0x12F3EAF7, 0xE28,      -0x14F3F0D8, -0x13D2FFFF,
    0x0C121137, 0x20100E28, -0x13F3EDF0, 0x0E28EE0C,  0x0F28EB0C,  0x0F28EC2D, 0x10C12,     0x11372010,
};
s32 D_80B58B7C[3] = { 0x0E29512D, 0x10C12, 0x10000000 };
s32 D_80B58B88[2] = { 0x0E29612D, 0x10C10 };
s32 D_80B58B90[3] = { 0x0E291B2D, 0x10C12, 0x10000000 };

ActorInit En_An_InitVars = {
    ACTOR_EN_AN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_AN1,
    sizeof(EnAn),
    (ActorFunc)EnAn_Init,
    (ActorFunc)EnAn_Destroy,
    (ActorFunc)EnAn_Update,
    (ActorFunc)NULL,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B58BBC = {
    {
        COLTYPE_HIT1,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 14, 62, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_80B58BE8 = { 0, 0, 0, 0, MASS_IMMOVABLE };

s32 func_80B53840(EnAn* this, PlayState* play) {
    s32 ret = false;

    if ((this->unk_214 != play->roomCtx.curRoom.num) && (play->roomCtx.status == 0) && !this->unk_3B8) {
        this->msmoObjectSlot = SubS_GetObjectSlot(OBJECT_MSMO, play);
        this->an4ObjectSlot = SubS_GetObjectSlot(OBJECT_AN4, play);
        this->maskKerfayObjectSlot = SubS_GetObjectSlot(OBJECT_MASK_KERFAY, play);
        this->an3ObjectSlot = SubS_GetObjectSlot(OBJECT_AN3, play);
        this->an2ObjectSlot = SubS_GetObjectSlot(OBJECT_AN2, play);
        this->actor.draw = NULL;
        this->unk_214 = play->roomCtx.curRoom.num;
        this->unk_3B8 = true;
    }

    if (!this->unk_3B8) {
        return false;
    }

    if (((this->an2ObjectSlot >= 0) && (SubS_IsObjectLoaded(this->an2ObjectSlot, play) == 0)) ||
        ((this->an3ObjectSlot >= 0) && (SubS_IsObjectLoaded(this->an3ObjectSlot, play) == 0)) ||
        ((this->maskKerfayObjectSlot >= 0) && (SubS_IsObjectLoaded(this->maskKerfayObjectSlot, play) == 0)) ||
        ((this->an4ObjectSlot >= 0) && (SubS_IsObjectLoaded(this->an4ObjectSlot, play) == 0)) ||
        ((this->msmoObjectSlot >= 0) && (SubS_IsObjectLoaded(this->msmoObjectSlot, play) == 0))) {
        ret = true;
    } else {
        this->actor.draw = EnAn_Draw;
        this->unk_3B8 = false;
    }

    return ret;
}

Actor* func_80B539CC(EnAn* this, PlayState* play, u8 actorCategory, s16 actorId) {
    Actor* foundActor = NULL;

    while (true) {
        foundActor = SubS_FindActor(play, foundActor, actorCategory, actorId);

        if (foundActor == NULL) {
            break;
        }

        if ((this != (EnAn*)foundActor) && (foundActor->update != NULL)) {
            break;
        }

        if (foundActor->next == NULL) {
            foundActor = NULL;
            break;
        }

        foundActor = foundActor->next;
    }

    return foundActor;
}

Actor* func_80B53A7C(EnAn* this, PlayState* play, u8 actorCategory, s16 actorId) {
    Actor* foundActor = NULL;

    while (true) {
        foundActor = SubS_FindActor(play, foundActor, actorCategory, actorId);

        if (foundActor == NULL) {
            break;
        }

        if ((this != (EnAn*)foundActor) && (foundActor->update != NULL)) {
            if (!(foundActor->params & ENAN_8000)) {
                break;
            }
        }

        if (foundActor->next == NULL) {
            foundActor = NULL;
            break;
        }

        foundActor = foundActor->next;
    }

    return foundActor;
}

EnDoor* EnAn_FindDoor(PlayState* play, s32 scheduleOutputResult) {
    s32 switchFlag;

    switch (scheduleOutputResult) {
        case ANJU_SCH_1A:
        case ANJU_SCH_1B:
            switchFlag = 0xD;
            break;

        case ANJU_SCH_21:
        case ANJU_SCH_22:
        case ANJU_SCH_25:
        case ANJU_SCH_26:
            switchFlag = 0xB;
            break;

        case ANJU_SCH_24:
            switchFlag = 0x10;
            break;

        case ANJU_SCH_1C:
        case ANJU_SCH_1D:
        case ANJU_SCH_1E:
        case ANJU_SCH_1F:
        case ANJU_SCH_20:
        case ANJU_SCH_23:
        case ANJU_SCH_27:
            switchFlag = 0xE;
            break;

        default:
            return NULL;
    }

    return SubS_FindDoor(play, switchFlag);
}

s32 func_80B53BA8(EnAn* this, PlayState* play) {
    s8 originalObjectSlot = this->actor.objectSlot;
    s8 otherObjectSlot = -1;
    s32 ret = 0;

    if ((this->animIndex >= 0x19) && (this->an4ObjectSlot >= 0)) {
        otherObjectSlot = this->an4ObjectSlot;
    } else if ((this->animIndex >= 0x15) && (this->an3ObjectSlot >= 0)) {
        otherObjectSlot = this->an3ObjectSlot;
    } else if ((this->animIndex >= 0x11) && (this->an2ObjectSlot >= 0)) {
        otherObjectSlot = this->an2ObjectSlot;
    } else if (this->animIndex < 0x11) {
        otherObjectSlot = originalObjectSlot;
    }

    if (otherObjectSlot < 0) {
        return 0;
    }

    if (otherObjectSlot >= 0) {
        gSegments[0x6] = OS_K0_TO_PHYSICAL(play->objectCtx.slots[otherObjectSlot].segment);
        this->skelAnime.playSpeed = this->unk_368;
        ret = SkelAnime_Update(&this->skelAnime);
        gSegments[0x6] = OS_K0_TO_PHYSICAL(play->objectCtx.slots[originalObjectSlot].segment);
    }

    return ret;
}

typedef enum EnAnAnimation {
    /* -1 */ ENAN_ANIM_NONE = -1,
    /*  0 */ ENAN_ANIM_0,
    /*  1 */ ENAN_ANIM_1,
    /*  2 */ ENAN_ANIM_2,
    /*  3 */ ENAN_ANIM_3,
    /*  4 */ ENAN_ANIM_4,
    /*  5 */ ENAN_ANIM_5,
    /*  6 */ ENAN_ANIM_6,
    /*  7 */ ENAN_ANIM_7,
    /*  8 */ ENAN_ANIM_8,
    /*  9 */ ENAN_ANIM_9,
    /* 10 */ ENAN_ANIM_10,
    /* 11 */ ENAN_ANIM_11,
    /* 12 */ ENAN_ANIM_12,
    /* 13 */ ENAN_ANIM_13,
    /* 14 */ ENAN_ANIM_14,
    /* 15 */ ENAN_ANIM_15,
    /* 16 */ ENAN_ANIM_16,

    /* 17 */ ENAN_ANIM_17,
    /* 18 */ ENAN_ANIM_18,
    /* 19 */ ENAN_ANIM_19,
    /* 20 */ ENAN_ANIM_20,

    /* 21 */ ENAN_ANIM_21,
    /* 22 */ ENAN_ANIM_22,
    /* 23 */ ENAN_ANIM_23,
    /* 24 */ ENAN_ANIM_24,

    /* 25 */ ENAN_ANIM_25,
    /* 26 */ ENAN_ANIM_26,
    /* 27 */ ENAN_ANIM_27,
    /* 28 */ ENAN_ANIM_28,
    /* 29 */ ENAN_ANIM_29,
    /* 30 */ ENAN_ANIM_30,
    /* 31 */ ENAN_ANIM_31,
    /* 32 */ ENAN_ANIM_32,
    /* 33 */ ENAN_ANIM_33,
    /* 34 */ ENAN_ANIM_34,
    /* 35 */ ENAN_ANIM_35,
    /* 36 */ ENAN_ANIM_MAX
} EnAnAnimation;

// sAnimationInfo
AnimationInfoS D_80B58BF4[ENAN_ANIM_MAX] = {
    { &object_an1_Anim_013E1C, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },  // ENAN_ANIM_0
    { &object_an1_Anim_008B6C, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },  // ENAN_ANIM_1
    { &object_an1_Anim_008B6C, 1.0f, 0, -1, ANIMMODE_LOOP, -6 }, // ENAN_ANIM_2
    { &object_an1_Anim_00544C, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },  // ENAN_ANIM_3
    { &object_an1_Anim_00544C, 1.0f, 0, -1, ANIMMODE_ONCE, -6 }, // ENAN_ANIM_4
    { &object_an1_Anim_0026B4, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },  // ENAN_ANIM_5
    { &object_an1_Anim_001E74, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },  // ENAN_ANIM_6
    { &object_an1_Anim_013048, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },  // ENAN_ANIM_7
    { &object_an1_Anim_013048, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },  // ENAN_ANIM_8
    { &object_an1_Anim_0071E8, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },  // ENAN_ANIM_9
    { &object_an1_Anim_0071E8, 1.0f, 0, -1, ANIMMODE_LOOP, -6 }, // ENAN_ANIM_10
    { &object_an1_Anim_007E08, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },  // ENAN_ANIM_11
    { &object_an1_Anim_0065C8, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },  // ENAN_ANIM_12
    { &object_an1_Anim_001090, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },  // ENAN_ANIM_13
    { &object_an1_Anim_00144C, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },  // ENAN_ANIM_14
    { &object_an1_Anim_00341C, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },  // ENAN_ANIM_15
    { &object_an1_Anim_003EA8, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },  // ENAN_ANIM_16

    { &object_an2_Anim_0028DC, 1.0f, 0, -1, ANIMMODE_LOOP, 0 }, // ENAN_ANIM_17
    { &object_an2_Anim_0042CC, 1.0f, 0, -1, ANIMMODE_LOOP, 0 }, // ENAN_ANIM_18
    { &object_an2_Anim_0038A0, 1.0f, 0, -1, ANIMMODE_ONCE, 0 }, // ENAN_ANIM_19
    { &object_an2_Anim_001B80, 1.0f, 0, -1, ANIMMODE_LOOP, 0 }, // ENAN_ANIM_20

    { &object_an3_Anim_00201C, 1.0f, 0, -1, ANIMMODE_LOOP, 0 }, // ENAN_ANIM_21
    { &object_an3_Anim_002A4C, 1.0f, 0, -1, ANIMMODE_LOOP, 0 }, // ENAN_ANIM_22
    { &object_an3_Anim_0012C0, 1.0f, 0, -1, ANIMMODE_LOOP, 0 }, // ENAN_ANIM_23
    //! @bug Uses symbol from OBJECT_AN2 instead of OBJECT_AN3
    { &object_an2_Anim_0038A0, -1.0f, 0, -1, ANIMMODE_ONCE, 0 }, // ENAN_ANIM_24

    { &object_an4_Anim_006CC0, 1.0f, 0, -1, ANIMMODE_LOOP, 0 }, // ENAN_ANIM_25
    { &object_an4_Anim_007E3C, 1.0f, 0, -1, ANIMMODE_ONCE, 0 }, // ENAN_ANIM_26
    { &object_an4_Anim_0088C0, 1.0f, 0, -1, ANIMMODE_LOOP, 0 }, // ENAN_ANIM_27
    { &object_an4_Anim_0013C8, 1.0f, 0, -1, ANIMMODE_ONCE, 0 }, // ENAN_ANIM_28
    { &object_an4_Anim_002550, 1.0f, 0, -1, ANIMMODE_LOOP, 0 }, // ENAN_ANIM_29
    { &object_an4_Anim_00353C, 1.0f, 0, -1, ANIMMODE_ONCE, 0 }, // ENAN_ANIM_30
    { &object_an4_Anim_004498, 1.0f, 0, -1, ANIMMODE_LOOP, 0 }, // ENAN_ANIM_31
    { &object_an4_Anim_0060B4, 1.0f, 0, -1, ANIMMODE_ONCE, 0 }, // ENAN_ANIM_32
    { &object_an4_Anim_00041C, 1.0f, 0, -1, ANIMMODE_ONCE, 0 }, // ENAN_ANIM_33
    { &object_an4_Anim_004A78, 1.0f, 0, -1, ANIMMODE_ONCE, 0 }, // ENAN_ANIM_34
    { &object_an4_Anim_00506C, 1.0f, 0, -1, ANIMMODE_LOOP, 0 }, // ENAN_ANIM_35
};

s32 EnAn_ChangeAnim(EnAn* this, PlayState* play, EnAnAnimation animIndex) {
    s8 originalObjectSlot = this->actor.objectSlot;
    s8 otherObjectSlot = -1;
    s32 var_t0 = 0;
    s32 var_t2 = 0;

    if ((animIndex >= 25) && (this->an4ObjectSlot >= 0)) {
        otherObjectSlot = this->an4ObjectSlot;
    } else if ((animIndex >= 21) && (this->an3ObjectSlot >= 0)) {
        otherObjectSlot = this->an3ObjectSlot;
    } else if ((animIndex >= 17) && (this->an2ObjectSlot >= 0)) {
        otherObjectSlot = this->an2ObjectSlot;
    } else if (animIndex < 17) {
        otherObjectSlot = originalObjectSlot;
    }

    if (otherObjectSlot < 0) {
        return 0;
    }

    switch (animIndex) {
        case ENAN_ANIM_1:
        case ENAN_ANIM_2:
            if ((this->animIndex != ENAN_ANIM_1) && (this->animIndex != ENAN_ANIM_2)) {
                var_t0 = 1;
            }
            break;

        case ENAN_ANIM_7:
        case ENAN_ANIM_8:
            if ((this->animIndex != ENAN_ANIM_7) && (this->animIndex != ENAN_ANIM_8)) {
                var_t0 = 1;
            }
            break;

        case ENAN_ANIM_9:
        case ENAN_ANIM_10:
            if ((this->animIndex != ENAN_ANIM_9) && (this->animIndex != ENAN_ANIM_10)) {
                var_t0 = 1;
            }
            break;

        default:
            if (animIndex != this->animIndex) {
                var_t0 = 1;
            }
            break;
    }

    if ((var_t0 != 0) && (otherObjectSlot >= 0)) {
        gSegments[0x6] = OS_K0_TO_PHYSICAL(play->objectCtx.slots[otherObjectSlot].segment);
        this->animIndex = animIndex;
        var_t2 = SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80B58BF4, animIndex);
        this->unk_368 = this->skelAnime.playSpeed;
        gSegments[0x6] = OS_K0_TO_PHYSICAL(play->objectCtx.slots[originalObjectSlot].segment);
    }

    return var_t2;
}

Vec3f D_80B58E34 = { 0.0f, 0.0f, 8.0f };

void func_80B53ED4(EnAn* this, PlayState* play) {
    f32 temp;
    s32 pad;
    Vec3f sp24;

    if (this->scheduleResult == ANJU_SCH_19) {
        Lib_Vec3f_TranslateAndRotateY(&this->actor.world.pos, this->actor.shape.rot.y, &D_80B58E34, &sp24);
        this->collider.dim.radius = 20;
        Math_Vec3f_ToVec3s(&this->collider.dim.pos, &sp24);
    } else {
        Collider_UpdateCylinder(&this->actor, &this->collider);
    }

    temp = this->actor.focus.pos.y - this->actor.world.pos.y;
    this->collider.dim.height = TRUNCF_BINANG(temp);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
}

typedef enum EnAnEyes {
    /* 0 */ ENAN_EYES_0,
    /* 1 */ ENAN_EYES_1,
    /* 2 */ ENAN_EYES_2,
    /* 3 */ ENAN_EYES_3,
    /* 4 */ ENAN_EYES_4,
    /* 5 */ ENAN_EYES_5,
    /* 6 */ ENAN_EYES_6,
    /* 7 */ ENAN_EYES_MAX
} EnAnEyes;

typedef enum EnAnMouth {
    /* 0 */ ENAN_MOUTH_0,
    /* 1 */ ENAN_MOUTH_1,
    /* 2 */ ENAN_MOUTH_2,
    /* 3 */ ENAN_MOUTH_MAX
} EnAnMouth;

typedef enum EnAnFace {
    /*  0 */ ENAN_FACE_0,
    /*  1 */ ENAN_FACE_1,
    /*  2 */ ENAN_FACE_2,
    /*  3 */ ENAN_FACE_3,
    /*  4 */ ENAN_FACE_4,
    /*  5 */ ENAN_FACE_5,
    /*  6 */ ENAN_FACE_6,
    /*  7 */ ENAN_FACE_7,
    /*  8 */ ENAN_FACE_8,
    /*  9 */ ENAN_FACE_9,
    /* 10 */ ENAN_FACE_MAX
} EnAnFace;

s16 D_80B58E40[ENAN_FACE_MAX] = {
    ENAN_MOUTH_0, // ENAN_FACE_0
    ENAN_MOUTH_2, // ENAN_FACE_1
    ENAN_MOUTH_0, // ENAN_FACE_2
    ENAN_MOUTH_1, // ENAN_FACE_3
    ENAN_MOUTH_2, // ENAN_FACE_4
    ENAN_MOUTH_0, // ENAN_FACE_5
    ENAN_MOUTH_1, // ENAN_FACE_6
    ENAN_MOUTH_2, // ENAN_FACE_7
    ENAN_MOUTH_1, // ENAN_FACE_8
    ENAN_MOUTH_1, // ENAN_FACE_9
};

void EnAn_UpdateFace(EnAn* this) {
    s32 var_a1 = false;

    if (this->unk_360 & 0x100) {
        if (DECR(this->unk_38E) == 0) {
            // default case doesn't match
            switch (this->faceIndex) {
                case ENAN_FACE_2:
                case ENAN_FACE_4:
                case ENAN_FACE_6:
                    if ((this->eyeTexIndex == ENAN_EYES_5) || (this->eyeTexIndex == ENAN_EYES_2)) {
                        var_a1 = true;
                        this->eyeTexIndex = ENAN_EYES_5;
                    }
                    break;

                case ENAN_FACE_5:
                case ENAN_FACE_7:
                    if ((this->eyeTexIndex == ENAN_EYES_6) || (this->eyeTexIndex == ENAN_EYES_1)) {
                        var_a1 = true;
                        this->eyeTexIndex = ENAN_EYES_6;
                    }
                    break;

                case ENAN_FACE_8:
                    if ((this->eyeTexIndex == ENAN_EYES_4) || (this->eyeTexIndex == ENAN_EYES_2)) {
                        var_a1 = true;
                        this->eyeTexIndex = ENAN_EYES_4;
                    }
                    break;
            }

            if (!var_a1) {
                if ((this->eyeTexIndex == ENAN_EYES_4) || (this->eyeTexIndex == ENAN_EYES_5)) {
                    this->eyeTexIndex = ENAN_EYES_0;
                } else if (this->eyeTexIndex == ENAN_EYES_6) {
                    this->eyeTexIndex = ENAN_EYES_1;
                }
            }

            if (!var_a1) {
                this->eyeTexIndex++;

                if (this->eyeTexIndex >= ENAN_EYES_4) {
                    if ((this->faceIndex == ENAN_FACE_0) || (this->faceIndex == ENAN_FACE_1) ||
                        (this->faceIndex == ENAN_FACE_3)) {
                        this->unk_38E = Rand_S16Offset(0x1E, 0x1E);
                    } else {
                        this->unk_38E = 8;
                    }
                    this->eyeTexIndex = ENAN_EYES_0;
                }
            }
        }
    }

    this->mouthTexIndex = D_80B58E40[this->faceIndex];
}

Vec3f D_80B58E54 = { 190.0f, -130.0f, 0.0f };
Vec3s D_80B58E60 = { 0, 0, 0x4168 };
Vec3f D_80B58E68 = { 450.0f, 700.0f, -760.0f };
Vec3s D_80B58E74 = { 0x238C, 0, -0x3FFC };

void func_80B54124(EnAn* this, PlayState* play, u32 arg2) {
    s32 pad;
    s8 originalObjectSlot = this->actor.objectSlot;
    s8 otherObjectSlot;

    OPEN_DISPS(play->state.gfxCtx);

    Matrix_Push();

    switch (arg2) {
        case 0x0:
            if ((this->unk_360 & 0x800) && !this->unk_3B0) {
                this->unk_3A8++;
                this->unk_3AC -= 2;
                Gfx_SetupDL25_Xlu(play->state.gfxCtx);

                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPSegment(POLY_XLU_DISP++, 0x08,
                           Gfx_TwoTexScroll(play->state.gfxCtx, 0, this->unk_3A8, 0U, 0x10, 0x10, 1, 0U, this->unk_3AC,
                                            0x10, 0x10));
                gSPDisplayList(POLY_XLU_DISP++, object_an1_DL_0111E8);

                Gfx_SetupDL25_Opa(play->state.gfxCtx);
            }
            break;

        case 0x1:
            otherObjectSlot = this->maskKerfayObjectSlot;
            if ((this->unk_360 & 0x4000) && !this->unk_3B0 && (otherObjectSlot >= 0)) {
                gSPSegment(POLY_OPA_DISP++, 0x0A, play->objectCtx.slots[otherObjectSlot].segment);

                Matrix_TranslateRotateZYX(&D_80B58E54, &D_80B58E60);

                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_OPA_DISP++, object_mask_kerfay_DL_000D40);
                gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.slots[originalObjectSlot].segment);
            }
            break;

        case 0x2:
            otherObjectSlot = this->an2ObjectSlot;
            if ((this->unk_360 & 0x1000) && !this->unk_3B0 && (otherObjectSlot >= 0)) {
                gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.slots[otherObjectSlot].segment);
                gSPDisplayList(POLY_OPA_DISP++, object_an2_DL_000378);
                gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.slots[originalObjectSlot].segment);
            }
            break;

        case 0x3:
            otherObjectSlot = this->an3ObjectSlot;
            if ((this->unk_360 & 0x2000) && !this->unk_3B0 && (otherObjectSlot >= 0)) {
                gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.slots[otherObjectSlot].segment);
                gSPDisplayList(POLY_OPA_DISP++, object_an3_DL_000308);
                gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.slots[originalObjectSlot].segment);
            }
            break;

        case 0x4:
            if ((this->unk_360 & 0x8000) && !this->unk_3B0) {
                gSPDisplayList(POLY_OPA_DISP++, object_an1_DL_012478);
            }
            break;

        case 0x5:
            otherObjectSlot = this->msmoObjectSlot;
            if (this->unk_3B4 && (otherObjectSlot >= 0)) {
                Matrix_TranslateRotateZYX(&D_80B58E68, &D_80B58E74);

                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.slots[otherObjectSlot].segment);
                gSPDisplayList(POLY_OPA_DISP++, gMoonMaskDL);
                gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.slots[originalObjectSlot].segment);
            }
            break;
    }

    Matrix_Pop();

    CLOSE_DISPS(play->state.gfxCtx);
}

s32 func_80B54678(EnAn* this, s16 csId) {
    s32 ret = false;

    if (CutsceneManager_GetCurrentCsId() == CS_ID_GLOBAL_TALK) {
        CutsceneManager_Stop(CS_ID_GLOBAL_TALK);
        CutsceneManager_Queue(csId);
    } else if (CutsceneManager_IsNext(csId)) {
        CutsceneManager_StartWithPlayerCs(csId, &this->actor);
        ret = true;
    } else {
        CutsceneManager_Queue(csId);
    }

    return ret;
}

s16 func_80B546F4(EnAn* this, s32 arg1) {
    s16 csId = this->actor.csId;
    s32 i;

    for (i = 0; i < arg1; i++) {
        csId = CutsceneManager_GetAdditionalCsId(csId);
    }

    return csId;
}

s16 func_80B54750(EnAn* this, s32 arg1) {
    Actor* temp_v0 = this->actor.child;
    s16 csId = -1;
    s32 i;

    if ((temp_v0 != NULL) && (temp_v0->update != NULL)) {
        csId = temp_v0->csId;

        for (i = 0; i < arg1; i++) {
            csId = CutsceneManager_GetAdditionalCsId(csId);
        }
    }

    return csId;
}

s32 func_80B547C8(Actor* thisx, PlayState* play) {
    EnAn* this = THIS;
    s16 csId = func_80B546F4(this, 0);
    s32 ret = 0;

    switch (this->unk_394) {
        case 0x0:
            ret = 0;
            if (func_80B54678(this, csId)) {
                goto label;
            }
            break;

        case 0x2:
        case 0x4:
        case 0x6:
        label:
            Camera_SetTargetActor(Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(csId)), &this->actor);
            ret = 1;
            this->unk_394++;
            break;

        case 0x1:
        case 0x3:
        case 0x5:
            if ((CHECK_WEEKEVENTREG(WEEKEVENTREG_86_08)) && (this->unk_394 == 3)) {
                CutsceneManager_Stop(csId);
            } else if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
                Camera_SetTargetActor(Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(csId)),
                                      this->actor.child);
            }
            this->unk_394++;
            ret = 1;
            break;

        case 0x7:
            CutsceneManager_Stop(csId);
            ret = 1;
            this->unk_394++;
            break;
    }

    return ret;
}
s32 func_80B5492C(Actor* thisx, PlayState* play) {
    EnAn* this = THIS;
    s16 csId = func_80B546F4(this, 0);
    s32 var_a2 = 0;

    switch (this->unk_394) {
        case 0x0:
            var_a2 = 0;
            if (func_80B54678(this, csId)) {
                goto label;
            }
            break;

        case 0x2:
        case 0x4:
        label:
            Camera_SetTargetActor(Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(csId)), &this->actor);
            var_a2 = 1;
            this->unk_394++;
            break;

        case 0x1:
        case 0x3:
            if (!(CHECK_WEEKEVENTREG(WEEKEVENTREG_RECEIVED_ROOM_KEY)) && (this->unk_394 == 3)) {
                CutsceneManager_Stop(csId);
                this->unk_394 = 5;
            } else if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
                Camera_SetTargetActor(Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(csId)),
                                      this->actor.child);
            }
            this->unk_394++;
            var_a2 = 1;
            break;

        case 0x5:
            CutsceneManager_Stop(csId);
            var_a2 = 1;
            this->unk_394++;
            break;
    }
    return var_a2;
}

s32 func_80B54A94(Actor* thisx, PlayState* play) {
    EnAn* this = THIS;
    s16 csId = func_80B54750(this, 0);
    s32 ret = 0;

    switch (this->unk_394) {
        case 0x0:
            ret = 0;
            if (func_80B54678(this, csId)) {
                goto label;
            }
            break;

        case 0x2:
        case 0x4:
        case 0x6:
        case 0x8:
        label:
            if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
                Camera_SetTargetActor(Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(csId)),
                                      this->actor.child);
            }
            ret = 1;
            this->unk_394++;
            break;

        case 0x1:
        case 0x3:
        case 0x5:
        case 0x7:
            Camera_SetTargetActor(Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(csId)), &this->actor);
            ret = 1;
            this->unk_394++;
            break;

        case 0x9:
            CutsceneManager_Stop(csId);
            ret = 1;
            this->unk_394++;
            break;
    }

    return ret;
}

s32 func_80B54BC4(Actor* thisx, PlayState* play) {
    EnAn* this = THIS;

    if (this->unk_394 == 0) {
        func_800B7298(play, &this->actor, PLAYER_CSMODE_WAIT);
        play->nextEntrance = ENTRANCE(STOCK_POT_INN, 3);
        gSaveContext.nextCutsceneIndex = 0;
        play->transitionTrigger = TRANS_TRIGGER_START;
        play->transitionType = TRANS_TYPE_FADE_BLACK;
        gSaveContext.nextTransitionType = TRANS_TYPE_FADE_BLACK_SLOW;
        this->unk_394++;
    }
    return 0;
}

s32 func_80B54C5C(Actor* thisx, PlayState* play) {
    EnAn* this = THIS;
    s32 sp20 = false;

    switch (this->unk_394) {
        case 0x0:
            EnAn_ChangeAnim(this, play, ENAN_ANIM_13);
            this->unk_394++;
            break;

        case 0x1:
        case 0x3:
            if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                this->unk_394++;
                sp20 = true;
            }
            break;

        case 0x2:
            EnAn_ChangeAnim(this, play, ENAN_ANIM_14);
            this->unk_394++;
            break;
    }

    return sp20;
}

s32 func_80B54D18(Actor* thisx, PlayState* play) {
    EnAn* this = THIS;
    s32 ret = false;

    switch (this->unk_394) {
        case 0x0:
            if ((Player_GetMask(play) == PLAYER_MASK_KAFEIS_MASK) || CHECK_WEEKEVENTREG(WEEKEVENTREG_55_20)) {
                this->unk_394++;
                goto label;
            } else {
                ret = true;
                this->unk_360 |= 0x4000;
                this->unk_394++;
            }
            break;

        case 0x1:
        label:
            this->unk_360 &= ~(0x20 | 0x4000);
            this->unk_360 |= 0x200;
            EnAn_ChangeAnim(this, play, ENAN_ANIM_20);
            ret = true;
            this->unk_394++;
            break;
    }

    return ret;
}

// TODO: figure out what to do with this
#define SCHEDULE_CALC_TIME_ALT(hour, minute) SCHEDULE_CONVERT_TIME((((hour)*60.0f) + (minute)) * (0x10000 / 60 / 24.0f))

s32* func_80B54DF4(EnAn* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    switch (this->scheduleResult) {
        case ANJU_SCH_15:
            this->msgEventFunc = func_80B54A94;
            return D_80B58808;

        case ANJU_SCH_10:
            this->msgEventFunc = func_80B547C8;
            return D_80B58718;

        case ANJU_SCH_11:
            this->msgEventFunc = func_80B5492C;
            return D_80B58784;

        case ANJU_SCH_E:
            this->msgEventFunc = func_80B54C5C;
            return D_80B58954;

        case ANJU_SCH_C:
            return D_80B5899C;

        case ANJU_SCH_19:
            return D_80B58B90;

        default:
            if (player->transformation == PLAYER_FORM_DEKU) {
                switch (this->scheduleResult) {
                    case ANJU_SCH_1:
                        return D_80B58AE8;

                    case ANJU_SCH_28:
                    case ANJU_SCH_2A:
                    case ANJU_SCH_2B:
                    case ANJU_SCH_2C:
                    case ANJU_SCH_2D:
                    case ANJU_SCH_2F:
                        return D_80B58B7C;

                    case ANJU_SCH_3:
                        return D_80B58A24;

                    case ANJU_SCH_31:
                        return D_80B589FC;

                    default:
                        return D_80B58A04;
                }
            } else {
                if (Player_GetMask(play) == PLAYER_MASK_KAFEIS_MASK) {
                    if (this->scheduleResult == ANJU_SCH_31) {
                        return D_80B58B88;
                    }

                    if (this->scheduleResult == ANJU_SCH_17) {
                        this->msgEventFunc = func_80B54BC4;
                        return D_80B589AC;
                    }

                    if (this->scheduleResult == ANJU_SCH_3) {
                        this->msgEventFunc = func_80B54D18;
                        return D_80B58B3C;
                    }

                    if (gSaveContext.save.day >= 2) {
                        return D_80B58A44;
                    }

                    // if ((gSaveContext.save.time - 0x3FFC) < 0x5883) {
                    // if (SCHEDULE_CONVERT_TIME_ALT(gSaveContext.save.time) < SCHEDULE_CONVERT_TIME_ALT(CLOCK_TIME(14,
                    // 18))) {
                    if (SCHEDULE_CONVERT_TIME_ALT(gSaveContext.save.time) < SCHEDULE_CALC_TIME_ALT(14, 18)) {
                        return D_80B58ABC;
                    }
                    return D_80B58AC4;
                }

                if ((player->transformation == PLAYER_FORM_HUMAN) &&
                    CHECK_WEEKEVENTREG(WEEKEVENTREG_PROMISED_MIDNIGHT_MEETING)) {
                    if (this->scheduleResult == ANJU_SCH_17) {
                        this->msgEventFunc = func_80B54BC4;
                        return D_80B589AC;
                    }
                    if (this->scheduleResult == ANJU_SCH_3) {
                        this->msgEventFunc = func_80B54D18;
                        return D_80B58AF4;
                    }
                    if (gSaveContext.save.day >= 2) {
                        return D_80B58A44;
                    }
                }

                switch (this->scheduleResult) {
                    case ANJU_SCH_1:
                        return D_80B58AE8;

                    case ANJU_SCH_28:
                        return D_80B5894C;

                    case ANJU_SCH_2A:
                    case ANJU_SCH_2B:
                    case ANJU_SCH_2C:
                    case ANJU_SCH_2D:
                        return D_80B58980;

                    case ANJU_SCH_3:
                        this->msgEventFunc = func_80B54D18;
                        return D_80B58AF4;

                    case ANJU_SCH_12:
                        if (gSaveContext.save.day >= 2) {
                            return D_80B58A3C;
                        }
                        return D_80B5885C;

                    case ANJU_SCH_13:
                    case ANJU_SCH_2F:
                        return D_80B58938;

                    case ANJU_SCH_16:
                        return D_80B58988;

                    case ANJU_SCH_17:
                        return D_80B589FC;

                    case ANJU_SCH_30:
                        return D_80B58944;

                    case ANJU_SCH_31:
                        if (player->transformation == PLAYER_FORM_HUMAN) {
                            return D_80B58B88;
                        }
                        return D_80B589FC;

                    case ANJU_SCH_34:
                    case ANJU_SCH_35:
                        return D_80B58994;

                    default:
                        break;
                }
            }
            break;
    }

    return NULL;
}

s32 func_80B55180(EnAn* this, PlayState* play) {
    s32 ret = false;

    if ((this->unk_360 & 7) && Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        SubS_SetOfferMode(&this->unk_360, SUBS_OFFER_MODE_NONE, SUBS_OFFER_MODE_MASK);
        this->unk_3C4 = 0;
        this->unk_394 = 0;
        this->msgEventFunc = NULL;
        this->actor.child = this->unk_218;
        this->msgEventScript = func_80B54DF4(this, play);

        if ((this->scheduleResult == ANJU_SCH_1) || (this->scheduleResult == ANJU_SCH_3) ||
            (this->scheduleResult == ANJU_SCH_12) || (this->scheduleResult == ANJU_SCH_13) ||
            (this->scheduleResult == ANJU_SCH_17) || (this->scheduleResult == ANJU_SCH_16) ||
            (this->scheduleResult == ANJU_SCH_28) || (this->scheduleResult == ANJU_SCH_2A) ||
            (this->scheduleResult == ANJU_SCH_2B) || (this->scheduleResult == ANJU_SCH_2C) ||
            (this->scheduleResult == ANJU_SCH_2D) || (this->scheduleResult == ANJU_SCH_2F) ||
            (this->scheduleResult == ANJU_SCH_30) || (this->scheduleResult == ANJU_SCH_31) ||
            (this->scheduleResult == ANJU_SCH_34) || (this->scheduleResult == ANJU_SCH_35)) {
            this->unk_360 |= 0x20;
        }

        if ((this->scheduleResult == ANJU_SCH_3) && CHECK_WEEKEVENTREG(WEEKEVENTREG_55_20)) {
            this->unk_360 &= ~0x20;
        }

        this->actionFunc = func_80B57A44;
        ret = true;
    }

    return ret;
}

s32 func_80B552E4(EnAn* this, PlayState* play) {
    u16 temp_v0 = play->csCtx.scriptIndex;
    s32 ret = false;

    if ((play->csCtx.state != 0) && (play->sceneId == 0x61) && (gSaveContext.sceneLayer == 0) &&
        ((temp_v0 == 0) || (temp_v0 == 1))) {
        if (!this->unk_3B0) {
            this->unk_38A = ENAN_FACE_0;
            this->faceIndex = ENAN_FACE_0;
            this->unk_360 |= 0x300;
            this->unk_38E = 8;
            this->cueId = -1;
            this->unk_3B0 = true;
            this->unk_3B4 = false;
        }

        ret = true;
    } else if (this->unk_3B0) {
        this->unk_3B0 = false;
        this->unk_3B4 = false;
        this->unk_3C0 = true;
        this->actor.room = play->roomCtx.curRoom.num;
        this->actionFunc = func_80B578F8;
    }

    return ret;
}

void func_80B553AC(EnAn* this) {
    Actor* temp_v0_2;
    Vec3f sp40;
    Vec3f sp34;
    s32 pad;

    Math_Vec3f_Copy(&sp40, &this->unk_218->world.pos);
    Math_Vec3f_Copy(&sp34, &this->actor.world.pos);
    Math_ApproachS(&this->unk_37E, Math_Vec3f_Yaw(&sp34, &sp40) - this->actor.shape.rot.y, 4, 0x2AA8);

    this->unk_37E = CLAMP(this->unk_37E, -0x1FFE, 0x1FFE);

    Math_Vec3f_Copy(&sp34, &this->actor.focus.pos);

    temp_v0_2 = this->unk_218;
    if (temp_v0_2->id == ACTOR_PLAYER) {
        sp40.y = ((Player*)temp_v0_2)->bodyPartsPos[PLAYER_BODYPART_HEAD].y + 3.0f;
    } else {
        Math_Vec3f_Copy(&sp40, &temp_v0_2->focus.pos);
    }

    Math_ApproachS(&this->unk_37C, Math_Vec3f_Pitch(&sp34, &sp40), 4, 0x2AA8);

    this->unk_37C = CLAMP(this->unk_37C, -0x1554, 0x1554);
}

void func_80B554E8(EnAn* this) {
    if (this->unk_360 & 0x20) {
        if ((this->unk_218 != NULL) && (this->unk_218->update != NULL)) {
            if (DECR(this->unk_388) == 0) {
                func_80B553AC(this);
                this->unk_360 &= ~0x200;
                this->unk_360 |= 0x80;
                return;
            }
        }
    }

    if (this->unk_360 & 0x80) {
        this->unk_360 &= ~0x80;
        this->unk_37C = 0;
        this->unk_37E = 0;
        this->unk_388 = 20;
        return;
    }

    if (DECR(this->unk_388) == 0) {
        this->unk_360 |= 0x200;
    }
}

s32 func_80B555C8(EnAn* this, PlayState* play) {
    switch (this->scheduleResult) {
        case ANJU_SCH_10:
        case ANJU_SCH_11:
        case ANJU_SCH_12:
        case ANJU_SCH_13:
        case ANJU_SCH_17:
            EnAn_ChangeAnim(this, play, ENAN_ANIM_1);
            break;

        case ANJU_SCH_16:
            EnAn_ChangeAnim(this, play, ENAN_ANIM_23);
            this->unk_360 |= 0x2000;
            break;

        case ANJU_SCH_E:
            EnAn_ChangeAnim(this, play, ENAN_ANIM_12);
            break;

        case ANJU_SCH_15:
            EnAn_ChangeAnim(this, play, ENAN_ANIM_15);
            break;

        case ANJU_SCH_2F:
        case ANJU_SCH_31:
            EnAn_ChangeAnim(this, play, ENAN_ANIM_7);
            break;

        case ANJU_SCH_34:
        case ANJU_SCH_35:
            EnAn_ChangeAnim(this, play, ENAN_ANIM_22);
            this->unk_360 |= 0x2000;
            break;

        default:
            if (this->animIndex == ENAN_ANIM_15) {
                EnAn_ChangeAnim(this, play, ENAN_ANIM_16);
            }
            if (this->animIndex == ENAN_ANIM_17) {
                EnAn_ChangeAnim(this, play, ENAN_ANIM_18);
            }
            if ((this->animIndex == ENAN_ANIM_1) || (this->animIndex == ENAN_ANIM_2)) {
                EnAn_ChangeAnim(this, play, ENAN_ANIM_8);
            }
            break;
    }

    return 0;
}

void func_80B556F8(EnAn* this, PlayState* play) {
    if (this->unk_396 == 0) {
        EnAn_ChangeAnim(this, play, ENAN_ANIM_6);
        this->unk_360 &= ~0x20;
        this->unk_360 |= 0x200;
        this->unk_396++;
    } else if ((this->unk_396 == 1) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        EnAn_ChangeAnim(this, play, ENAN_ANIM_2);
        this->unk_360 &= ~0x200;
        this->unk_360 |= 0x20;
        this->unk_396++;
    }
}

void func_80B557AC(EnAn* this, PlayState* play) {
    if (this->unk_396 == 0) {
        EnAn_ChangeAnim(this, play, ENAN_ANIM_3);
        this->unk_360 &= 0xFFDF;
        this->unk_360 |= 0x200;
        this->unk_396++;
    } else if ((this->unk_396 == 1) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        EnAn_ChangeAnim(this, play, ENAN_ANIM_2);
        this->unk_360 &= 0xFDFF;
        this->unk_360 |= 0x20;
        this->unk_396++;
    }
}

void func_80B55860(EnAn* this, PlayState* play) {
    if (this->unk_396 == 0) {
        EnAn_ChangeAnim(this, play, ENAN_ANIM_4);
        this->unk_360 |= 0x200;
        this->unk_360 &= 0xFFDF;
        this->unk_396++;
    } else if ((this->unk_396 == 1) && (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) != 0)) {
        EnAn_ChangeAnim(this, play, ENAN_ANIM_2);
        this->unk_360 &= 0xFDFF;
        this->unk_360 |= 0x20;
        this->unk_396++;
    }
}

s32 func_80B55914(EnAn* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    u16 textId = play->msgCtx.currentTextId;

    if (player->stateFlags1 & PLAYER_STATE1_40) {
        this->unk_360 |= 0x400;
        if (this->prevTextId != textId) {

            switch (textId) {
                case 0x28E5:
                    EnAn_ChangeAnim(this, play, ENAN_ANIM_5);
                    this->unk_360 &= 0xDFFF;
                    break;

                case 0x28BA:
                case 0x28D1:
                    EnAn_ChangeAnim(this, play, ENAN_ANIM_5);
                    break;

                case 0x28AF:
                case 0x28C1:
                    EnAn_ChangeAnim(this, play, ENAN_ANIM_1);
                    break;

                case 0x28BC:
                    EnAn_ChangeAnim(this, play, ENAN_ANIM_2);
                    break;

                case 0x28C6:
                    EnAn_ChangeAnim(this, play, ENAN_ANIM_15);
                    break;

                case 0x28F5:
                    EnAn_ChangeAnim(this, play, ENAN_ANIM_10);
                    break;

                case 0x28F7:
                case 0x28F8:
                    EnAn_ChangeAnim(this, play, ENAN_ANIM_21);
                    break;

                case 0x28EB:
                    if (this->animIndex != ENAN_ANIM_20) {
                        this->unk_360 &= 0xBFDF;
                        this->unk_360 |= 0x200;
                        EnAn_ChangeAnim(this, play, ENAN_ANIM_20);
                    }
                    break;

                case 0x28A4:
                case 0x28A9:
                case 0x28BE:
                case 0x28C0:
                case 0x295E:
                    this->unk_18C = func_80B556F8;
                    this->unk_396 = 0;
                    break;

                case 0x28E6:
                    this->unk_360 &= 0xDFFF;
                    this->unk_18C = func_80B55860;
                    this->unk_396 = 0;
                    break;

                case 0x1885:
                case 0x28A0:
                case 0x28A3:
                case 0x28A5:
                case 0x28B1:
                case 0x28D2:
                case 0x28D9:
                case 0x28DC:
                case 0x28DE:
                    this->unk_18C = func_80B557AC;
                    this->unk_396 = 0;
                    break;

                case 0x28A1:
                case 0x28A2:
                case 0x28A6:
                case 0x28A7:
                case 0x28A8:
                case 0x28AA:
                case 0x28AB:
                case 0x28AC:
                case 0x28AD:
                case 0x28AE:
                case 0x28B0:
                case 0x28B2:
                case 0x28B3:
                case 0x28B4:
                case 0x28B5:
                case 0x28B6:
                case 0x28B7:
                case 0x28B8:
                case 0x28B9:
                case 0x28BB:
                case 0x28BD:
                case 0x28BF:
                case 0x28C2:
                case 0x28C3:
                case 0x28C4:
                case 0x28C5:
                case 0x28C7:
                case 0x28C8:
                case 0x28C9:
                case 0x28CA:
                case 0x28CB:
                case 0x28CC:
                case 0x28CD:
                case 0x28CE:
                case 0x28CF:
                case 0x28D0:
                case 0x28D3:
                case 0x28D4:
                case 0x28D5:
                case 0x28D6:
                case 0x28D7:
                case 0x28D8:
                case 0x28DA:
                case 0x28DB:
                case 0x28DD:
                case 0x28DF:
                case 0x28E0:
                case 0x28E1:
                case 0x28E2:
                case 0x28E3:
                case 0x28E4:
                case 0x28E7:
                case 0x28E8:
                case 0x28E9:
                case 0x28EA:
                case 0x28EC:
                case 0x28ED:
                case 0x28EE:
                case 0x28EF:
                case 0x28F0:
                case 0x28F1:
                case 0x28F2:
                case 0x28F3:
                case 0x28F4:
                case 0x28F6:
                default:
                    if (this->animIndex == ENAN_ANIM_16) {
                        EnAn_ChangeAnim(this, play, ENAN_ANIM_15);
                    }
                    if (this->animIndex == ENAN_ANIM_18) {
                        EnAn_ChangeAnim(this, play, ENAN_ANIM_17);
                    }
                    if ((this->animIndex == ENAN_ANIM_22) || (this->animIndex == ENAN_ANIM_23)) {
                        EnAn_ChangeAnim(this, play, ENAN_ANIM_21);
                    }
                    if ((this->animIndex == ENAN_ANIM_7) || (this->animIndex == ENAN_ANIM_8)) {
                        EnAn_ChangeAnim(this, play, ENAN_ANIM_2);
                    }
                    break;
            }

            switch (textId) {
                case 0x28F5:
                    this->unk_38A = ENAN_FACE_0;
                    /* fallthrough */
                case 0x28A5:
                case 0x28AA:
                case 0x28F8:
                    this->faceIndex = ENAN_FACE_0;
                    this->unk_38E = 8;
                    break;

                case 0x1885:
                case 0x28A0:
                case 0x28A6:
                case 0x28AF:
                case 0x28C1:
                    this->faceIndex = ENAN_FACE_3;
                    this->unk_38E = 8;
                    break;

                case 0x28A2:
                case 0x28B3:
                case 0x28B6:
                case 0x28BA:
                case 0x28BE:
                case 0x28CE:
                case 0x28D0:
                case 0x28D6:
                case 0x28E5:
                case 0x28E7:
                case 0x28ED:
                    this->faceIndex = ENAN_FACE_1;
                    this->unk_38E = 8;
                    break;

                case 0x28AD:
                    this->faceIndex = ENAN_FACE_8;
                    this->unk_38E = 8;
                    break;

                case 0x28C0:
                case 0x28D7:
                case 0x28DE:
                    this->faceIndex = ENAN_FACE_2;
                    this->unk_38E = 8;
                    break;

                case 0x28E6:
                case 0x28F7:
                    this->faceIndex = ENAN_FACE_6;
                    this->unk_38E = 8;
                    break;

                case 0x28A3:
                case 0x28B1:
                case 0x28B8:
                case 0x28C6:
                case 0x28CA:
                case 0x28CC:
                case 0x28D5:
                case 0x28E2:
                case 0x28E3:
                case 0x28E4:
                    this->faceIndex = ENAN_FACE_4;
                    this->unk_38E = 8;
                    break;

                case 0x28EC:
                    this->unk_38A = ENAN_FACE_5;
                    /* fallthrough */
                case 0x28DC:
                case 0x28EB:
                case 0x28F2:
                case 0x28F9:
                    this->faceIndex = ENAN_FACE_5;
                    this->unk_38E = 8;
                    break;

                case 0x28F6:
                    this->faceIndex = ENAN_FACE_9;
                    this->unk_38E = 8;
                    break;

                case 0x28A4:
                case 0x28A9:
                    this->faceIndex = ENAN_FACE_7;
                    this->unk_38E = 8;
                    break;
            }
        }

        this->prevTextId = textId;
    } else if (this->unk_360 & 0x400) {
        this->unk_18C = NULL;
        this->prevTextId = 0;
        this->unk_360 &= ~0x400;
        this->faceIndex = this->unk_38A;
        this->unk_38E = 4;
        func_80B555C8(this, play);
    }

    if (this->unk_18C != NULL) {
        this->unk_18C(this, play);
    }

    return 0;
}

Actor* func_80B55D20(EnAn* this, PlayState* play) {
    Actor* actor;

    switch (this->scheduleResult) {
        default:
            actor = &GET_PLAYER(play)->actor;
            break;

        case ANJU_SCH_15:
            actor = func_80B539CC(this, play, ACTORCAT_NPC, ACTOR_EN_NB);
            break;

        case ANJU_SCH_10:
            actor = func_80B539CC(this, play, ACTORCAT_NPC, ACTOR_EN_PM);
            break;

        case ANJU_SCH_11:
            actor = func_80B539CC(this, play, ACTORCAT_NPC, ACTOR_EN_IG);
            break;
    }

    return actor;
}

s32 func_80B55D98(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput, u8 actorCategory, s16 actorId) {
    u8 pathIndex = ENAN_GET_PATH_INDEX(&this->actor);
    Vec3s* temp_v0_3;
    Vec3f sp3C;
    Vec3f sp30;
    Actor* actor;
    s32 pad;
    s32 ret = false;

    actor = func_80B539CC(this, play, actorCategory, actorId);
    this->timePath = NULL;

    if (sSearchTimePathLimit[scheduleOutput->result] >= 0) {
        this->timePath = SubS_GetAdditionalPath(play, pathIndex, sSearchTimePathLimit[scheduleOutput->result]);
    }

    if ((actor != NULL) && (actor->update != NULL)) {
        if (this->timePath != NULL) {
            temp_v0_3 = Lib_SegmentedToVirtual(this->timePath->points);
            Math_Vec3s_ToVec3f(&sp3C, &temp_v0_3[this->timePath->count - 2]);
            Math_Vec3s_ToVec3f(&sp30, &temp_v0_3[this->timePath->count - 1]);
            this->actor.shape.shadowDraw = NULL;
            this->actor.world.rot.y = Math_Vec3f_Yaw(&sp3C, &sp30);
            Math_Vec3f_Copy(&this->actor.world.pos, &sp30);
            ret = true;
        }
    }

    return ret;
}

s32 func_80B55ECC(EnAn* this) {
    s32 ret = false;

    if (Actor_IsFacingAndNearPlayer(&this->actor, (this->unk_3BC != 0) ? 150.0f : 100.0f, 0x2800)) {
        ret = true;
    }

    if (DECR(this->unk_386) == 0) {
        this->unk_3BC ^= 1;
        this->unk_386 = Rand_S16Offset(0x3C, 0x3C);
    }

    return ret;
}

s32 func_80B55F8C(PlayState* play) {
    Player* player = GET_PLAYER(play);
    s32 var_v1 = false;

    if ((Player_GetMask(play) == PLAYER_MASK_KAFEIS_MASK) &&
        CHECK_WEEKEVENTREG(WEEKEVENTREG_PROMISED_MIDNIGHT_MEETING)) {
        var_v1 = true;
    } else if ((player->transformation == PLAYER_FORM_HUMAN) &&
               CHECK_WEEKEVENTREG(WEEKEVENTREG_PROMISED_MIDNIGHT_MEETING)) {
        var_v1 = true;
    }

    return var_v1;
}

s32 func_80B5600C(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    s32 ret = false;

    if (func_80B55D98(this, play, scheduleOutput, ACTORCAT_NPC, ACTOR_EN_PM) != 0) {
        EnAn_ChangeAnim(this, play, ENAN_ANIM_1);
        SubS_SetOfferMode(&this->unk_360, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
        ret = true;

        this->unk_360 |= 0x120;
        this->unk_360 |= 0x200;
    }

    return ret;
}

s32 func_80B56094(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    s32 ret = false;

    if (func_80B55D98(this, play, scheduleOutput, ACTORCAT_NPC, ACTOR_EN_IG) != 0) {
        EnAn_ChangeAnim(this, play, ENAN_ANIM_1);
        SubS_SetOfferMode(&this->unk_360, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
        ret = true;

        this->unk_360 |= 0x120;
        this->unk_360 |= 0x200;
    }

    return ret;
}

s32 func_80B5611C(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    s32 ret = false;

    if (func_80B55D98(this, play, scheduleOutput, 4, 0x243) != 0) {
        EnAn_ChangeAnim(this, play, ENAN_ANIM_15);
        SubS_SetOfferMode(&this->unk_360, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
        ret = true;

        this->unk_360 |= 0x120;
        this->unk_360 |= 0xA00;
    }

    return ret;
}

s32 func_80B561A4(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    u16 sp56 = SCHEDULE_TIME_NOW;
    u8 pathIndex = ENAN_GET_PATH_INDEX(&this->actor);
    EnDoor* door;
    Vec3s* temp_v0_2;
    Vec3f sp40;
    Vec3f sp34;
    s32 limit;
    s32 ret = false;

    this->timePath = NULL;
    door = EnAn_FindDoor(play, scheduleOutput->result);

    limit = sSearchTimePathLimit[scheduleOutput->result];
    if (limit >= 0) {
        this->timePath = SubS_GetAdditionalPath(play, pathIndex, limit);
    }

    if ((door != NULL) && (door->knobDoor.dyna.actor.update != NULL)) {
        if (this->timePath != NULL) {
            temp_v0_2 = Lib_SegmentedToVirtual(this->timePath->points);
            Math_Vec3s_ToVec3f(&sp40, &temp_v0_2[0]);
            Math_Vec3s_ToVec3f(&sp34, &temp_v0_2[1]);
            Math_Vec3f_Copy(&this->unk_228, &sp40);
            Math_Vec3f_Copy(&this->unk_234, &sp34);
            this->actor.world.rot.y = Math_Vec3f_Yaw(&sp40, &sp34);
            Math_Vec3f_Copy(&this->actor.world.pos, &sp40);

            if (ABS_ALT(BINANG_SUB(this->actor.world.rot.y, door->knobDoor.dyna.actor.shape.rot.y)) <= 0x4000) {
                this->unk_215 = -0x4B;
            } else {
                this->unk_215 = 0x4B;
            }

            this->unk_378 = scheduleOutput->time1 - scheduleOutput->time0;
            this->unk_37A = sp56 - scheduleOutput->time0;

            switch (scheduleOutput->result) {
                case ANJU_SCH_1B:
                case ANJU_SCH_1C:
                case ANJU_SCH_20:
                case ANJU_SCH_21:
                case ANJU_SCH_22:
                case ANJU_SCH_23:
                case ANJU_SCH_25:
                case ANJU_SCH_26:
                    this->unk_38A = ENAN_FACE_2;
                    this->faceIndex = ENAN_FACE_2;
                    this->unk_38E = 8;
                    break;
            }

            switch (scheduleOutput->result) {
                case ANJU_SCH_1A:
                case ANJU_SCH_1B:
                case ANJU_SCH_1C:
                    this->unk_360 |= 0x900;
                    EnAn_ChangeAnim(this, play, ENAN_ANIM_16);
                    break;

                case ANJU_SCH_24:
                case ANJU_SCH_27:
                    this->unk_360 |= 0x2100;
                    EnAn_ChangeAnim(this, play, ENAN_ANIM_22);
                    break;

                default:
                    this->unk_360 |= 0x100;
                    EnAn_ChangeAnim(this, play, ENAN_ANIM_7);
                    break;
            }

            this->actor.flags &= ~ACTOR_FLAG_TARGETABLE;
            this->unk_360 |= 0x200;
            this->actor.gravity = 0.0f;
            ret = true;
        }
    }

    return ret;
}

s32 func_80B56418(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    u16 temp_t0 = (gSaveContext.save.time - 0x3FFC);
    u16 var_v1_2;
    u8 pathIndex = ENAN_GET_PATH_INDEX(&this->actor);
    s32 pad;
    s32 var_v1 = 0;
    s32 temp_a3;

    this->timePath = NULL;
    temp_a3 = sSearchTimePathLimit[scheduleOutput->result];

    if (temp_a3 >= 0) {
        this->timePath = SubS_GetAdditionalPath(play, pathIndex, temp_a3);
    }

    if ((this->timePath != NULL) && (this->timePath->count < 3)) {
        this->timePath = NULL;
    }

    if (this->timePath != NULL) {
        if ((this->scheduleResult < ANJU_SCH_28) && (this->scheduleResult != ANJU_SCH_NONE) && (this->timePathTimeSpeed >= 0)) {
            var_v1_2 = temp_t0;
        } else {
            var_v1_2 = scheduleOutput->time0;
        }

        if (scheduleOutput->time1 < var_v1_2) {
            this->timePathTotalTime = (var_v1_2 - scheduleOutput->time1) + 0xFFFF;
        } else {
            this->timePathTotalTime = scheduleOutput->time1 - var_v1_2;
        }

        this->timePathElapsedTime = temp_t0 - var_v1_2;
        var_v1_2 = (this->timePath->count - 2);
        this->timePathWaypointTime = this->timePathTotalTime / var_v1_2;

        this->timePathWaypoint = (this->timePathElapsedTime / this->timePathWaypointTime) + 2;
        this->unk_360 &= ~8;
        this->unk_360 &= ~0x10;

        switch (scheduleOutput->result) {
            case ANJU_SCH_2C:
            case ANJU_SCH_2D:
            case ANJU_SCH_32:
            case ANJU_SCH_33:
            case ANJU_SCH_36:
            case ANJU_SCH_37:
            case ANJU_SCH_38:
            case ANJU_SCH_39:
            case ANJU_SCH_3A:
            case ANJU_SCH_3B:
            case ANJU_SCH_3C:
            case ANJU_SCH_3D:
            case ANJU_SCH_3E:
            case ANJU_SCH_3F:
                this->unk_38A = ENAN_FACE_2;
                this->faceIndex = ENAN_FACE_2;
                this->unk_38E = 8;
                break;
        }

        switch (scheduleOutput->result) {
            case ANJU_SCH_2A:
            case ANJU_SCH_2B:
                SubS_SetOfferMode(&this->unk_360, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
                /* fallthrough */
            case ANJU_SCH_2C:
            case ANJU_SCH_2D:
                EnAn_ChangeAnim(this, play, ENAN_ANIM_16);
                this->unk_360 |= 0x300;
                this->unk_360 |= 0x800;
                break;

            case ANJU_SCH_34:
            case ANJU_SCH_35:
                EnAn_ChangeAnim(this, play, ENAN_ANIM_22);
                SubS_SetOfferMode(&this->unk_360, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);

                this->unk_360 |= 0x300;
                this->unk_360 |= 0x2000;
                break;

            case ANJU_SCH_32:
            case ANJU_SCH_33:
                EnAn_ChangeAnim(this, play, ENAN_ANIM_7);
                this->unk_360 |= 0x300;
                break;

            case ANJU_SCH_36:
            case ANJU_SCH_37:
            case ANJU_SCH_38:
            case ANJU_SCH_39:
            case ANJU_SCH_3A:
            case ANJU_SCH_3B:
            case ANJU_SCH_3C:
            case ANJU_SCH_3D:
            case ANJU_SCH_3E:
            case ANJU_SCH_3F:
                EnAn_ChangeAnim(this, play, ENAN_ANIM_18);
                this->unk_360 |= 0x300;
                this->unk_360 |= 0x1000;
                break;

            case ANJU_SCH_28:
            case ANJU_SCH_2F:
            case ANJU_SCH_30:
            case ANJU_SCH_31:
                SubS_SetOfferMode(&this->unk_360, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
                this->unk_360 |= 0x300;
                /* fallthrough */
            default:
                EnAn_ChangeAnim(this, play, ENAN_ANIM_7);
                break;
        }

        var_v1 = 1;
        this->actor.gravity = -1.0f;
    }

    return var_v1;
}

s32 func_80B56744(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    u8 pathIndex = ENAN_GET_PATH_INDEX(&this->actor);
    Vec3f sp40;
    Vec3f sp34;
    Vec3s* temp_v0_2;
    s32 limit;
    s32 ret = false;

    this->timePath = NULL;

    limit = sSearchTimePathLimit[scheduleOutput->result];
    if (limit >= 0) {
        this->timePath = SubS_GetAdditionalPath(play, pathIndex, limit);
    }

    if ((this->timePath != NULL) && (this->timePath->count >= 2)) {
        temp_v0_2 = Lib_SegmentedToVirtual(this->timePath->points);
        Math_Vec3s_ToVec3f(&sp40, &temp_v0_2[0]);
        Math_Vec3s_ToVec3f(&sp34, &temp_v0_2[1]);

        this->actor.world.rot.y = Math_Vec3f_Yaw(&sp40, &sp34);
        Math_Vec3s_Copy(&this->actor.shape.rot, &this->actor.world.rot);
        Math_Vec3f_Copy(&this->actor.world.pos, &sp40);
        Math_Vec3f_Copy(&this->actor.prevPos, &sp40);
        if (scheduleOutput->result == ANJU_SCH_16) {
            EnAn_ChangeAnim(this, play, ENAN_ANIM_23);
            SubS_SetOfferMode(&this->unk_360, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);

            this->unk_360 |= 0x300;
            this->unk_360 |= 0x2000;
        }
        ret = true;
    }

    return ret;
}

s32 func_80B56880(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    u8 pathIndex = ENAN_GET_PATH_INDEX(&this->actor);
    Vec3f sp40;
    Vec3f sp34;
    Vec3s* temp_v0_2; // sp30
    s32 limit;
    s32 ret = false;

    this->timePath = NULL;
    limit = sSearchTimePathLimit[scheduleOutput->result];
    if (limit >= 0) {
        this->timePath = SubS_GetAdditionalPath(play, pathIndex, limit);
    }

    if ((this->timePath != NULL) && (this->timePath->count >= 2)) {
        temp_v0_2 = Lib_SegmentedToVirtual(this->timePath->points);
        Math_Vec3s_ToVec3f(&sp40, &temp_v0_2[this->timePath->count - 1]);
        Math_Vec3s_ToVec3f(&sp34, &temp_v0_2[this->timePath->count - 2]);

        this->actor.world.rot.y = Math_Vec3f_Yaw(&sp34, &sp40);

        Math_Vec3s_Copy(&this->actor.shape.rot, &this->actor.world.rot);
        Math_Vec3s_Copy(&this->actor.home.rot, &this->actor.world.rot);
        Math_Vec3f_Copy(&this->actor.world.pos, &sp40);
        Math_Vec3f_Copy(&this->actor.prevPos, &sp40);

        switch (scheduleOutput->result) {
            case ANJU_SCH_13:
                this->actor.world.rot.y += 0x7FF8;
                /* fallthrough */
            case ANJU_SCH_12:
            case ANJU_SCH_17:
                EnAn_ChangeAnim(this, play, ENAN_ANIM_1);
                SubS_SetOfferMode(&this->unk_360, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
                this->unk_37A = 0;
                this->unk_360 |= 0x300;
                if (scheduleOutput->result == ANJU_SCH_12) {
                    this->unk_374 = 70.0f;
                }
                break;

            case ANJU_SCH_3:
                this->unk_360 |= 0x300;
                this->unk_360 |= 0x1000;

                if (CHECK_WEEKEVENTREG(WEEKEVENTREG_55_20)) {
                    EnAn_ChangeAnim(this, play, ENAN_ANIM_20);
                    this->unk_360 |= 0x40;
                    this->actor.world.rot.y += 0x7FF8;
                    this->actor.shape.rot.y = this->actor.world.rot.y;
                    this->unk_37A = 4;
                } else {
                    EnAn_ChangeAnim(this, play, ENAN_ANIM_18);
                    this->unk_37A = 0;
                }

                this->unk_38A = ENAN_FACE_2;
                this->faceIndex = ENAN_FACE_2;
                this->unk_38E = 8;
                break;

            case ANJU_SCH_E:
                EnAn_ChangeAnim(this, play, ENAN_ANIM_12);
                SubS_SetOfferMode(&this->unk_360, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);

                this->unk_360 |= 0x300;
                this->unk_360 |= 0x8000;
                break;
        }
        ret = true;
    }

    return ret;
}

Vec3f D_80B58E7C = { 905.0f, 260.0f, -64.0f };
Vec3s D_80B58E88 = { 0, 0, 0 };

s32 func_80B56B00(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    s32 pad;

    Math_Vec3f_Copy(&this->actor.world.pos, &D_80B58E7C);
    Math_Vec3s_Copy(&this->actor.shape.rot, &D_80B58E88);
    Math_Vec3s_Copy(&this->actor.world.rot, &this->actor.shape.rot);

    if (scheduleOutput->result == ANJU_SCH_C) {
        EnAn_ChangeAnim(this, play, ENAN_ANIM_11);
        SubS_SetOfferMode(&this->unk_360, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);

        this->unk_360 |= 0x300;
        this->unk_360 |= 0x40;

        this->unk_38A = ENAN_FACE_5;
        this->faceIndex = ENAN_FACE_5;
        this->unk_38E = 8;
    }

    return true;
}

Vec3f D_80B58E90 = { -508.0f, 210.0f, -162.0f };
Vec3s D_80B58E9C = { 0, 0x3FFC, 0 };

s32 func_80B56BC0(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    s32 pad;

    Math_Vec3f_Copy(&this->actor.world.pos, &D_80B58E90);
    Math_Vec3s_Copy(&this->actor.shape.rot, &D_80B58E9C);
    Math_Vec3s_Copy(&this->actor.world.rot, &this->actor.shape.rot);

    switch (scheduleOutput->result) {
        case ANJU_SCH_1:
            SubS_SetOfferMode(&this->unk_360, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
            EnAn_ChangeAnim(this, play, ENAN_ANIM_9);
            break;

        case ANJU_SCH_18:
            EnAn_ChangeAnim(this, play, ENAN_ANIM_11);
            this->unk_38A = ENAN_FACE_5;
            this->faceIndex = ENAN_FACE_5;
            this->unk_38E = 8;
            break;
    }

    this->unk_360 |= 0x300;
    this->unk_360 |= 0x40;

    this->actor.gravity = 0.0f;
    return true;
}

Vec3s D_80B58EA4 = { 0, -0x2AAD, 0 };

s32 func_80B56CAC(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    s32 pad;

    Math_Vec3s_Copy(&this->actor.shape.rot, &D_80B58EA4);
    Math_Vec3s_Copy(&this->actor.world.rot, &this->actor.shape.rot);
    EnAn_ChangeAnim(this, play, ENAN_ANIM_0);
    SubS_SetOfferMode(&this->unk_360, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
    this->unk_360 |= 0x300;

    return 1;
}

s32 EnAn_ProcessScheduleOutput(EnAn* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    s32 ret;

    this->actor.flags |= ACTOR_FLAG_TARGETABLE;
    this->actor.targetMode = TARGET_MODE_6;
    this->unk_360 = 0;
    this->unk_38A = ENAN_FACE_0;
    this->faceIndex = ENAN_FACE_0;
    this->unk_38E = 8;
    this->unk_374 = 40.0f;

    switch (scheduleOutput->result) {
        case ANJU_SCH_10:
            ret = func_80B5600C(this, play, scheduleOutput);
            break;

        case ANJU_SCH_11:
            ret = func_80B56094(this, play, scheduleOutput);
            break;

        case ANJU_SCH_15:
            ret = func_80B5611C(this, play, scheduleOutput);
            break;

        case ANJU_SCH_C:
            ret = func_80B56B00(this, play, scheduleOutput);
            break;

        case ANJU_SCH_1:
        case ANJU_SCH_18:
            ret = func_80B56BC0(this, play, scheduleOutput);
            break;

        case ANJU_SCH_3:
        case ANJU_SCH_E:
        case ANJU_SCH_12:
        case ANJU_SCH_13:
        case ANJU_SCH_17:
            ret = func_80B56880(this, play, scheduleOutput);
            break;

        case ANJU_SCH_16:
            ret = func_80B56744(this, play, scheduleOutput);
            break;

        case ANJU_SCH_19:
            ret = func_80B56CAC(this, play, scheduleOutput);
            break;

        case ANJU_SCH_1A:
        case ANJU_SCH_1B:
        case ANJU_SCH_1C:
        case ANJU_SCH_1D:
        case ANJU_SCH_1E:
        case ANJU_SCH_1F:
        case ANJU_SCH_20:
        case ANJU_SCH_21:
        case ANJU_SCH_22:
        case ANJU_SCH_23:
        case ANJU_SCH_24:
        case ANJU_SCH_25:
        case ANJU_SCH_26:
        case ANJU_SCH_27:
            ret = func_80B561A4(this, play, scheduleOutput);
            break;

        case ANJU_SCH_28:
        case ANJU_SCH_2A:
        case ANJU_SCH_2B:
        case ANJU_SCH_2C:
        case ANJU_SCH_2D:
        case ANJU_SCH_2E:
        case ANJU_SCH_2F:
        case ANJU_SCH_30:
        case ANJU_SCH_31:
        case ANJU_SCH_32:
        case ANJU_SCH_33:
        case ANJU_SCH_34:
        case ANJU_SCH_35:
        case ANJU_SCH_36:
        case ANJU_SCH_37:
        case ANJU_SCH_38:
        case ANJU_SCH_39:
        case ANJU_SCH_3A:
        case ANJU_SCH_3B:
        case ANJU_SCH_3C:
        case ANJU_SCH_3D:
        case ANJU_SCH_3E:
        case ANJU_SCH_3F:
            ret = func_80B56418(this, play, scheduleOutput);
            break;

        default:
            ret = 0;
            break;
    }

    return ret;
}

s32 func_80B56E44(EnAn* this, PlayState* play) {
    Vec3f sp2C;
    Vec3f sp20;

    if ((this->unk_218 != NULL) && (this->unk_218->update != NULL)) {
        Math_Vec3f_Copy(&sp2C, &this->unk_218->world.pos);
        Math_Vec3f_Copy(&sp20, &this->actor.world.pos);
        this->actor.world.rot.y = Math_Vec3f_Yaw(&sp20, &sp2C);
    }

    return true;
}

s32 func_80B56EB4(EnAn* this, PlayState* play) {
    EnDoor* door = EnAn_FindDoor(play, this->scheduleResult);
    Vec3f sp38;
    f32 temp_fv0;
    s32 pad;

    if (!SubS_InCsMode(play) && (this->timePathTimeSpeed != 0)) {
        if ((door != NULL) && (door->knobDoor.dyna.actor.update != NULL)) {
            if ((this->unk_37A / (f32)this->unk_378) <= 0.9f) {
                door->unk_1A7 = this->unk_215;
            } else {
                door->unk_1A7 = 0;
            }
        }

        this->unk_37A = CLAMP(this->unk_37A, 0, this->unk_378);
        temp_fv0 = Math_Vec3f_DistXZ(&this->unk_228, &this->unk_234) / this->unk_378;

        sp38.x = 0.0f;
        sp38.y = 0.0f;
        sp38.z = this->unk_37A * temp_fv0;

        Lib_Vec3f_TranslateAndRotateY(&this->unk_228, this->actor.world.rot.y, &sp38, &this->actor.world.pos);

        this->unk_37A += this->timePathTimeSpeed;
        if (Animation_OnFrame(&this->skelAnime, 3.0f) || Animation_OnFrame(&this->skelAnime, 15.0f)) {
            Actor_PlaySfx(&this->actor, NA_SE_EV_PIRATE_WALK);
        }
    }

    return 0;
}

s32 func_80B5702C(EnAn* this, PlayState* play) {
    f32 knots[265];
    Vec3f sp70;
    Vec3f sp64;
    Vec3f timePathTargetPos;
    s32 sp54;
    s32 sp50 = 0;
    s32 pad;

    sp54 = 0;
    SubS_TimePathing_FillKnots(knots, 3, this->timePath->count + 3);

    if (!(this->unk_360 & 8)) {
        timePathTargetPos = gZeroVec3f;
        SubS_TimePathing_Update(this->timePath, &this->timePathProgress, &this->timePathElapsedTime, this->timePathWaypointTime, this->timePathTotalTime,
                                &this->timePathWaypoint, knots, &timePathTargetPos, this->timePathTimeSpeed);
        SubS_TimePathing_ComputeInitialY(play, this->timePath, this->timePathWaypoint, &timePathTargetPos);
        this->actor.world.pos.y = timePathTargetPos.y;
        this->unk_360 |= 8;
    } else {
        timePathTargetPos = this->timePathTargetPos;
    }

    this->actor.world.pos.x = timePathTargetPos.x;
    this->actor.world.pos.z = timePathTargetPos.z;

    if (SubS_InCsMode(play) != 0) {
        sp54 = this->timePathElapsedTime;
        sp50 = this->timePathWaypoint;
        timePathTargetPos = this->actor.world.pos;
    }
    this->timePathTargetPos = gZeroVec3f;

    if (SubS_TimePathing_Update(this->timePath, &this->timePathProgress, &this->timePathElapsedTime, this->timePathWaypointTime, this->timePathTotalTime,
                                &this->timePathWaypoint, knots, &this->timePathTargetPos, this->timePathTimeSpeed)) {
        this->unk_360 |= 0x10;
    } else {
        sp70 = this->actor.world.pos;
        sp64 = this->timePathTargetPos;
        this->actor.world.rot.y = Math_Vec3f_Yaw(&sp70, &sp64);
    }

    if (SubS_InCsMode(play) != 0) {
        this->timePathElapsedTime = sp54;
        this->timePathWaypoint = sp50;
        this->timePathTargetPos = timePathTargetPos;
    } else if (Animation_OnFrame(&this->skelAnime, 3.0f) || Animation_OnFrame(&this->skelAnime, 15.0f)) {
        Actor_PlaySfx(&this->actor, NA_SE_EV_PIRATE_WALK);
    }

    return 0;
}

s32 func_80B572D4(EnAn* this, PlayState* play) {
    switch (this->scheduleResult) {
        case ANJU_SCH_17:
            if ((func_80B55F8C(play) != 0) && (func_80B55ECC(this) != 0)) {
                this->unk_360 |= 0x20;
            } else {
                this->unk_360 &= ~0x20;
            }
            break;

        case ANJU_SCH_1:
            if (func_80B55ECC(this) != 0) {
                this->unk_360 |= 0x20;
            } else {
                this->unk_360 &= ~0x20;
            }
            break;

        case ANJU_SCH_12:
        case ANJU_SCH_13:
            if (func_80B55ECC(this) != 0) {
                this->unk_360 |= 0x20;
            } else {
                this->unk_360 &= ~0x20;
            }
            break;

        case ANJU_SCH_16:
            if (Animation_OnFrame(&this->skelAnime, 6.0f) && (this->animIndex == ENAN_ANIM_23)) {
                Actor_PlaySfx(&this->actor, NA_SE_EV_SWEEP);
            }
            break;
    }

    return 0;
}

s32 func_80B573F4(EnAn* this, PlayState* play) {
    s16 temp1;
    s16 temp2;

    switch (this->unk_37A) {
        case 0x0:
            this->actor.world.rot.y += 0x7FF8;
            this->unk_37A++;
            break;

        case 0x1:
            temp1 = (this->actor.world.rot.y / 0xB6) * 0xB6;
            temp2 = (this->actor.shape.rot.y / 0xB6) * 0xB6;
            if (temp1 == temp2) {
                Math_Vec3s_Copy(&this->actor.shape.rot, &this->actor.world.rot);
                EnAn_ChangeAnim(this, play, ENAN_ANIM_19);
                this->unk_360 |= 0x40;
                this->unk_37A++;
            }
            break;

        case 0x2:
            if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                this->unk_37A++;
            }
            break;

        case 0x3:
            if (ABS_ALT(BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.shape.rot.y)) < 0x3000) {
                SubS_SetOfferMode(&this->unk_360, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
            } else {
                SubS_SetOfferMode(&this->unk_360, SUBS_OFFER_MODE_NONE, SUBS_OFFER_MODE_MASK);
            }
            break;

        case 0x4:
            SubS_SetOfferMode(&this->unk_360, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
            this->unk_37A++;
            break;
    }

    return 0;
}

s32 func_80B575BC(EnAn* this, PlayState* play) {
    s32 temp = this->actor.shape.rot.y;
    s16 temp_v1 = ABS_ALT(BINANG_SUB(this->actor.yawTowardsPlayer, temp));

    if (temp_v1 < 0x4000) {
        SubS_SetOfferMode(&this->unk_360, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
    } else {
        SubS_SetOfferMode(&this->unk_360, SUBS_OFFER_MODE_NONE, SUBS_OFFER_MODE_MASK);
    }

    if (func_80B55ECC(this) != 0) {
        this->unk_360 |= 0x20;
    } else {
        this->unk_360 &= ~0x20;
    }

    return 1;
}

s32 func_80B57674(EnAn* this, PlayState* play) {
    s16 temp = BINANG_ADD(this->actor.shape.rot.y, 0x3000);
    s16 temp_v1 = ABS_ALT(BINANG_SUB(this->actor.yawTowardsPlayer, temp));

    if (temp_v1 < 0x3000) {
        SubS_SetOfferMode(&this->unk_360, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
    } else {
        SubS_SetOfferMode(&this->unk_360, SUBS_OFFER_MODE_NONE, SUBS_OFFER_MODE_MASK);
    }

    this->unk_360 &= ~0x20;
    return 1;
}

void func_80B57718(EnAn* this, PlayState* play) {
    switch (this->scheduleResult) {
        case ANJU_SCH_10:
        case ANJU_SCH_11:
        case ANJU_SCH_15:
            func_80B56E44(this, play);
            break;

        case ANJU_SCH_3:
            func_80B573F4(this, play);
            break;

        case ANJU_SCH_1:
            func_80B575BC(this, play);
            break;

        case ANJU_SCH_19:
            func_80B57674(this, play);
            break;

        case ANJU_SCH_C:
        case ANJU_SCH_E:
        case ANJU_SCH_12:
        case ANJU_SCH_13:
        case ANJU_SCH_16:
        case ANJU_SCH_18:
            func_80B572D4(this, play);
            break;

        case ANJU_SCH_17:
            func_80B572D4(this, play);
            break;

        case ANJU_SCH_1A:
        case ANJU_SCH_1B:
        case ANJU_SCH_1C:
        case ANJU_SCH_1D:
        case ANJU_SCH_1E:
        case ANJU_SCH_1F:
        case ANJU_SCH_20:
        case ANJU_SCH_21:
        case ANJU_SCH_22:
        case ANJU_SCH_23:
        case ANJU_SCH_24:
        case ANJU_SCH_25:
        case ANJU_SCH_26:
        case ANJU_SCH_27:
            func_80B56EB4(this, play);
            break;

        case ANJU_SCH_28:
        case ANJU_SCH_2A:
        case ANJU_SCH_2B:
        case ANJU_SCH_2C:
        case ANJU_SCH_2D:
        case ANJU_SCH_2E:
        case ANJU_SCH_2F:
        case ANJU_SCH_30:
        case ANJU_SCH_31:
        case ANJU_SCH_32:
        case ANJU_SCH_33:
        case ANJU_SCH_34:
        case ANJU_SCH_35:
        case ANJU_SCH_36:
        case ANJU_SCH_37:
        case ANJU_SCH_38:
        case ANJU_SCH_39:
        case ANJU_SCH_3A:
        case ANJU_SCH_3B:
        case ANJU_SCH_3C:
        case ANJU_SCH_3D:
        case ANJU_SCH_3E:
        case ANJU_SCH_3F:
            func_80B5702C(this, play);
            break;
    }

    Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0x2AA8);
}

void func_80B577F0(EnAn* this, PlayState* play) {
    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 14.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &object_an1_Skel_012618, NULL, this->jointTable, this->morphTable,
                       OBJECT_AN1_LIMB_MAX);

    this->animIndex = ENAN_ANIM_NONE;
    EnAn_ChangeAnim(this, play, ENAN_ANIM_1);
    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &D_80B58BBC);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &D_80B58BE8);

    if (this->actor.params & ENAN_8000) {
        this->unk_3C0 = true;
    }

    this->actor.draw = EnAn_Draw;
    Actor_SetScale(&this->actor, 0.01f);
    this->unk_360 = 0;
    this->scheduleResult = ANJU_SCH_NONE;

    this->actionFunc = func_80B578F8;
    this->actionFunc(this, play);
}

void func_80B578F8(EnAn* this, PlayState* play) {
    ScheduleOutput scheduleOutput;

    this->timePathTimeSpeed = R_TIME_SPEED + ((void)0, gSaveContext.save.timeSpeedOffset);

    if (!(this->actor.params & ENAN_8000) && !this->unk_3C0 && CHECK_WEEKEVENTREG(WEEKEVENTREG_51_40)) {
        Actor_Kill(&this->actor);
        return;
    }

    if (this->unk_3C0) {
        scheduleOutput.result = ANJU_SCH_19;
        if (this->scheduleResult != ANJU_SCH_19) {
            EnAn_ProcessScheduleOutput(this, play, &scheduleOutput);
        }
    } else if (!Schedule_RunScript(play, sScheduleScript, &scheduleOutput) ||
               ((this->scheduleResult != scheduleOutput.result) &&
                (EnAn_ProcessScheduleOutput(this, play, &scheduleOutput) == 0))) {
        this->actor.shape.shadowDraw = NULL;
        this->actor.flags &= ~ACTOR_FLAG_TARGETABLE;
        scheduleOutput.result = ANJU_SCH_NONE;
    } else {
        this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        this->actor.flags |= ACTOR_FLAG_TARGETABLE;
    }

    this->scheduleResult = scheduleOutput.result;
    this->unk_218 = func_80B55D20(this, play);
    func_80B57718(this, play);
}

void func_80B57A44(EnAn* this, PlayState* play) {
    if (func_8010BF58(&this->actor, play, this->msgEventScript, this->msgEventFunc, &this->msgScriptResumePos) != 0) {
        SubS_SetOfferMode(&this->unk_360, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);

        this->unk_360 &= ~0x20;
        this->unk_360 |= 0x200;
        this->unk_388 = 20;
        this->msgScriptResumePos = 0;
        this->actionFunc = func_80B578F8;
    } else if ((this->scheduleResult != ANJU_SCH_1) && (this->scheduleResult != ANJU_SCH_3) &&
               (this->scheduleResult != ANJU_SCH_C) && (this->scheduleResult != ANJU_SCH_E) &&
               (this->scheduleResult != ANJU_SCH_19)) {
        if ((this->unk_218 != NULL) && (this->unk_218->update != NULL)) {
            s32 temp;
            Vec3f sp38;
            Vec3f sp2C;

            Math_Vec3f_Copy(&sp38, &this->unk_218->world.pos);
            Math_Vec3f_Copy(&sp2C, &this->actor.world.pos);
            temp = Math_Vec3f_Yaw(&sp2C, &sp38);

            Math_ApproachS(&this->actor.shape.rot.y, temp, 4, 0x2AA8);
        }
    }
}

void func_80B57B48(EnAn* this, PlayState* play) {
    s32 sp30[] = {
        ENAN_ANIM_0,  ENAN_ANIM_11, ENAN_ANIM_34, ENAN_ANIM_25, ENAN_ANIM_26,
        ENAN_ANIM_28, ENAN_ANIM_30, ENAN_ANIM_32, ENAN_ANIM_33, ENAN_ANIM_0,
    };
    s32 pad;

    if (0) {}

    if (Cutscene_IsCueInChannel(play, CS_CMD_ACTOR_CUE_557)) {
        s32 cueChannel = Cutscene_GetCueChannel(play, CS_CMD_ACTOR_CUE_557);
        u16 cueId = play->csCtx.actorCues[cueChannel]->id;

        if (this->cueId != (cueId & 0xFF)) {
            this->cueId = cueId;
            if (this->cueId == 3) {
                SET_WEEKEVENTREG(WEEKEVENTREG_87_02);
                this->unk_3B4 = true;
            }
            if (this->cueId == 9) {
                this->unk_3B4 = false;
            }
            EnAn_ChangeAnim(this, play, sp30[cueId]);
        }

        if ((this->animIndex == ENAN_ANIM_26) || (this->animIndex == ENAN_ANIM_28) ||
            (this->animIndex == ENAN_ANIM_30) || (this->animIndex == ENAN_ANIM_34)) {
            if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                EnAn_ChangeAnim(this, play, this->animIndex + 1);
            }
        }
        Cutscene_ActorTranslateAndYaw(&this->actor, play, cueChannel);
    }
}

void EnAn_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnAn* this = THIS;
    s32 temp_v1;
    s32 temp_v0;

    if (play->sceneId != SCENE_YADOYA) {
        this->actor.params &= (s16)~ENAN_8000;
    }

    temp_v1 = (this->actor.params & ENAN_8000) >> 0xF;
    temp_v0 = CHECK_WEEKEVENTREG(WEEKEVENTREG_51_40);

    if (((temp_v0 == 0) && (temp_v1 == 1)) || ((temp_v0 != 0) && (temp_v1 == 0))) {
        Actor_Kill(&this->actor);
        return;
    }

    if (temp_v1 == 0) {
        if (func_80B53A7C(this, play, ACTORCAT_NPC, ACTOR_EN_AN) != NULL) {
            Actor_Kill(&this->actor);
            return;
        }
    }

    this->unk_214 = -0x80;
    this->unk_3B8 = false;
    if (temp_v1 == 0) {
        this->actor.room = -1;
    }

    this->actionFunc = func_80B577F0;
}

void EnAn_Destroy(Actor* thisx, PlayState* play) {
    EnAn* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void EnAn_Update(Actor* thisx, PlayState* play) {
    EnAn* this = THIS;

    if (func_80B53840(this, play)) {
        return;
    }

    if ((this->actionFunc != func_80B577F0) && !func_80B55180(this, play) && (func_80B552E4(this, play) != 0)) {
        func_80B57B48(this, play);
        func_80B53BA8(this, play);
        EnAn_UpdateFace(this);
        return;
    }

    this->actionFunc(this, play);
    if (this->scheduleResult != ANJU_SCH_NONE) {
        func_80B55914(this, play);
        func_80B53BA8(this, play);
        EnAn_UpdateFace(this);
        func_80B554E8(this);
        SubS_Offer(&this->actor, play, this->unk_374, 30.0f, 0, this->unk_360 & SUBS_OFFER_MODE_MASK);

        if (!(this->unk_360 & 0x40)) {
            Actor_MoveWithGravity(&this->actor);
            Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 12.0f, 0.0f, 4U);
        }

        func_80B53ED4(this, play);
    }
}

Vec3f D_80B58ED4 = { 1000.0f, 0.0f, 0.0f };

void EnAn_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnAn* this = THIS;

    if (limbIndex == OBJECT_AN1_LIMB_09) {
        Matrix_MultVec3f(&D_80B58ED4, &this->actor.focus.pos);
        Math_Vec3s_Copy(&this->actor.focus.rot, &this->actor.world.rot);
        func_80B54124(this, play, 1U);
    } else if (limbIndex == OBJECT_AN1_LIMB_08) {
        func_80B54124(this, play, 0U);
        func_80B54124(this, play, 4U);
        func_80B54124(this, play, 2U);
        func_80B54124(this, play, 3U);
    } else if (limbIndex == OBJECT_AN1_LIMB_05) {
        func_80B54124(this, play, 5U);
    }
}

void EnAn_TransformLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx) {
    EnAn* this = THIS;
    s32 stepRot;
    s32 overrideRot;

    if (!(this->unk_360 & 0x200)) {
        if (this->unk_360 & 0x80) {
            overrideRot = true;
        } else {
            overrideRot = false;
        }
        stepRot = true;
    } else {
        overrideRot = false;
        stepRot = false;
    }

    if (limbIndex == OBJECT_AN1_LIMB_09) {
        SubS_UpdateLimb(this->unk_37C + 0x4000, this->unk_37E + this->actor.shape.rot.y + 0x4000, &this->unk_240,
                        &this->unk_258, stepRot, overrideRot);
        Matrix_Pop();
        Matrix_Translate(this->unk_240.x, this->unk_240.y, this->unk_240.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateYS(this->unk_258.y, MTXMODE_APPLY);
        Matrix_RotateXS(this->unk_258.x, MTXMODE_APPLY);
        Matrix_RotateZS(this->unk_258.z, MTXMODE_APPLY);
        Matrix_Push();
    }
}

// mouth textures
TexturePtr D_80B58EE0[ENAN_MOUTH_MAX] = {
    object_an1_Tex_00E6E0, // ENAN_MOUTH_0
    object_an1_Tex_00F7A0, // ENAN_MOUTH_1
    object_an1_Tex_0101A0, // ENAN_MOUTH_2
};

// eye textures
TexturePtr D_80B58EEC[ENAN_EYES_MAX] = {
    object_an1_Tex_00E1E0, // ENAN_EYES_0
    object_an1_Tex_00EFA0, // ENAN_EYES_1
    object_an1_Tex_00F3A0, // ENAN_EYES_2
    object_an1_Tex_00EFA0, // ENAN_EYES_3
    object_an1_Tex_00FDA0, // ENAN_EYES_4
    object_an1_Tex_00F9A0, // ENAN_EYES_5
    object_an1_Tex_0103A0, // ENAN_EYES_6
};

void EnAn_Draw(Actor* thisx, PlayState* play) {
    EnAn* this = THIS;

    if ((this->scheduleResult != ANJU_SCH_NONE) || this->unk_3B0) {
        OPEN_DISPS(play->state.gfxCtx);

        Gfx_SetupDL25_Opa(play->state.gfxCtx);

        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80B58EEC[this->eyeTexIndex]));
        gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(D_80B58EE0[this->mouthTexIndex]));

        SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                       this->skelAnime.dListCount, NULL, EnAn_PostLimbDraw, EnAn_TransformLimbDraw,
                                       &this->actor);

        CLOSE_DISPS(play->state.gfxCtx);
    }
}
