#pragma once

#define ITEMSIZE 8 * 3
#define WALLSIZE 16 * 16

enum TYPE_ATTRIBUTE
{
	TYPE_A_NONE,

	TYPE_A_TR_START,		//시작점

	TYPE_A_FT_ITEM,			//아이템 가구

	TYPE_A_IT_DRUG,			//약품류
	TYPE_A_IT_FOOD,			//음식류
	TYPE_A_IT_OIL,			//기름류
	TYPE_A_IT_BULLET,		//총알류

	TYPE_A_WL_EMPTY,		//빈그림
	TYPE_A_WL_CENTER,		//중앙벽
	TYPE_A_WL_ORIGINAL,		//벽
	TYPE_A_WL_ARENDER,		//After렌더벽

	TYPE_A_WP_GUN,			//총류 (총알/화살 발사)
	TYPE_A_WP_BOMB,			//폭탄류
	TYPE_A_WP_SWORD,		//칼류 (휘두르는 것)
	TYPE_A_WP_MACHINE 		//기계류 (기름소비)
};

enum TXTDATAINFO
{
	INFO_INDEX,
	INFO_TYPE,
	INFO_TYPE2,
	INFO_VALUE
};

struct tagDataInfo
{
	int index;
	int type;
	int type2;
	int value;
};


