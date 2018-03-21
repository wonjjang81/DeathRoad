#pragma once

//타일 규격
#define TILE_SIZEX 16
#define TILE_SIZEY 16

//타일갯수
#define TILEX 50
#define TILEY 50

//타일 총 사이즈
#define TILE_TOTAL_SIZEX TILE_SIZEX * TILEX
#define TILE_TOTAL_SIZEY TILE_SIZEY * TILEY

//타일셋팅
#define SAMPLETILEX 15
#define SAMPLETILEY 15

enum TILE_TYPE
{
	TYPE_NONE,
	TYPE_TERRAIN,
	TYPE_BUILDING,
	TYPE_ROAD,
	TYPE_FURNITURE,
	TYPE_ITEM,
	TYPE_WEAPON,
	TYPE_ENEMY,
	TYPE_WALL,
	TYPE_DOOR
};

//지형속성
enum TERRAIN
{
	TR_NONE,
	TR_LAND,
	TR_STREET,
	TR_GRASS,
	TR_WALL,
	TR_HILL
};

//고정된 물체 (타격 불가능)
enum FIX_OBJECT
{
	FOBJ_NONE,
	FOBJ_TREE, 
	FOBJ_HOUSE_BOTTOM, FOBJ_HOUSE_TOP, FOBJ_HOUSE_DOOR,
	FOBJ_TREE_BOTTOM, FOBJ_TREE_TOP,
	FOBJ_OBSTACLE,
	FOBJ_CAR,
	FOBJ_SHELVES,
	FOBJ_FENCE,
	FOBJ_FURNITURE,
	FOBJ_TRASH
};

//움직일 수 있는 물체 (타격 가능)
enum MOVE_OBJECT
{
	MOBJ_NONE,
	MOBJ_OBSTACLE,
	MOBJ_CAR,
	MOBJ_FURNITURE
};

//아이템
enum ITEM
{
	ITEM_NONE,
	ITEM_HEAL,    //약품류
	ITEM_FOOD,    //음식류
	ITEM_OIL,     //기름류
	ITEM_BULLET   //총알류
};

//무기
enum WEAPON
{
	WP_NONE,
	WP_GUN,		//총류
	WP_BOMB,	//폭탄류
	WP_SWORD,	//칼류
	WP_ROD,		//창류 (휘두를수 있는것)
	WP_AXE,		//도끼류
	WP_BOW,		//활류
	WP_MACHINE 	//기계류 (기름소비)
};

//기타속성
enum ATTRIBUTE
{
	ATTR_NONE,
	ATTR_MOVE,
	ATTR_UNMOVE,
	ATTR_AFTER_RENDER,

	//충돌 렉트 생성용 
	ATTR_WALL_CENTER,
	ATTR_WALL_UNMOVE,
	ATTR_DOOR,

	//시작점
	ATTR_STARTPOINT
};

//포지션
enum POSITION
{
	POS_NONE,
	POS_START,
	POS_END
};

//중복위치 렌더
enum OVERLAPPOSITION
{
	OVERPO_NO,
	OVERPO_YES
};