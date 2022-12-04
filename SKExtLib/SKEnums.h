#pragma once
#include "pch.h"



#define SK_TEXTURE_START 1
#define SK_TEXTURE_END 157


#define SK_MAP_TILE_START 62
#define SK_MAP_TILE_END 145


SKEXT_EXPORTS typedef enum  SKTextureId {
		NONE = 0,

		SHIP_12 = 1,
		SHIP_11 ,
		SHIP_10 ,
		SHIP_9 ,
		SHIP_8 ,
		SHIP_7 ,
		SHIP_6 ,
		SHIP_5 ,
		SHIP_4 ,
		SHIP_3 ,
		SHIP_2 ,
		SHIP_1 ,

		NSHIP_12 ,
		NSHIP_11 ,
		NSHIP_10 ,
		NSHIP_9 ,
		NSHIP_8 ,
		NSHIP_7 ,
		NSHIP_6,
		NSHIP_5 ,
		NSHIP_4 ,
		NSHIP_3 ,
		NSHIP_2,
		NSHIP_1 ,

		NID_LAST_SHIP = 25,

		BULLET ,
		BULLET_DOUBLE ,
		BULLET_MIN ,

		BULLET_PING ,

		BULLET_HIT ,
		BULLET_BOOM ,
		BULLET_SURIKEN ,
		BULLET_SPLASH ,

		SMOKE ,

		DOT ,
		CROSS ,
		DIV ,

		AMMO ,
		AMMO_DOUBLE ,
		AMMO_CHARGE ,
		AMMO_MIN ,
		
		AMMO_KIT, // todo

		BOOB_TRAP ,

		// items...

		NUMBER_0 = 52,
		NUMBER_1 ,
		NUMBER_2 ,
		NUMBER_3 ,
		NUMBER_4 ,
		NUMBER_5 ,
		NUMBER_6 ,
		NUMBER_7 ,
		NUMBER_8,
		NUMBER_9 = 61,

		// tiles 62 - 145

		MENU_TITLE = 146,

		ICON_BORDERLIMIT,
		ICON_DELETEITEM,

		NID_LAST_TILE,

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