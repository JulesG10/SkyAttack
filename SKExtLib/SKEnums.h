#pragma once
#include "pch.h"



#define SK_TEXTURE_START 0
#define SK_TEXTURE_END 156


#define SK_MAP_TILE_START 61
#define SK_MAP_TILE_END 144


SKEXT_EXPORTS typedef enum  SKTextureId {
		NONE = -1,

		SHIP_12 = 0,
		SHIP_11 = 1,
		SHIP_10 = 2,
		SHIP_9 = 3,
		SHIP_8 = 4,
		SHIP_7 = 5,
		SHIP_6 = 6,
		SHIP_5 = 7,
		SHIP_4 = 8,
		SHIP_3 = 9,
		SHIP_2 = 10,
		SHIP_1 = 11,

		NSHIP_12 = 12,
		NSHIP_11 = 13,
		NSHIP_10 = 14,
		NSHIP_9 = 15,
		NSHIP_8 = 16,
		NSHIP_7 = 17,
		NSHIP_6 = 18,
		NSHIP_5 = 19,
		NSHIP_4 = 20,
		NSHIP_3 = 21,
		NSHIP_2 = 22,
		NSHIP_1 = 23,

		NID_LAST_SHIP = 24,

		BULLET = 25,
		BULLET_DOUBLE = 26,
		BULLET_MIN = 27,

		BULLET_PING = 28,

		BULLET_HIT = 29,
		BULLET_BOOM = 30,
		BULLET_SURIKEN = 31,
		BULLET_SPLASH = 32,

		SMOKE = 34,

		DOT = 35,
		CROSS = 36,
		DIV = 37,

		AMMO = 38,
		AMMO_DOUBLE = 39,
		AMMO_CHARGE = 40,
		AMMO_MIN = 41,

		BOOB_TRAP = 43,



		NUMBER_0 = 51,
		NUMBER_1 = 52,
		NUMBER_2 = 53,
		NUMBER_3 = 54,
		NUMBER_4 = 55,
		NUMBER_5 = 56,
		NUMBER_6 = 57,
		NUMBER_7 = 58,
		NUMBER_8 = 59,
		NUMBER_9 = 60,

		// tiles 61 - 144

		MENU_TITLE = 145,

		ICON_BORDERLIMIT = 146,
		ICON_DELETEITEM = 147,

		NID_LAST_TILE = 148,

		CLOUDS_0,
		CLOUDS_1,
		CLOUDS_2,
		CLOUDS_3,
		CLOUDS_4,
		CLOUDS_5,

		NID_LAST_CLOUD,

	} SKTextureId; // TODO: update textures

SKEXT_EXPORTS typedef enum SKGameKeys {
		LEFT,
		RIGHT,
		SLOWDOWN,
		SPEEDUP,
		SUICIDE,
		MISSILE,
		ULTIME
	} SKGameKeys;


	extern SKEXT_EXPORTS std::string SKTexureIdToString(std::string prefix, SKTextureId id);
	extern SKEXT_EXPORTS bool SKValidTextureId(SKTextureId id);