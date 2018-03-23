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

//기타속성
enum ATTRIBUTE
{
	ATTR_CRECT_NONE,      //충돌렉트 없음
	ATTR_CRECT_CENTER,    //충돌렉트 긴직사각형
	ATTR_CRECT_ORIGINAL,  //충돌렉트 타일사이즈
	ATTR_CRECT_RESIZE,    //충돌렉트 수정
};

//중복위치 렌더
enum OVERLAPPOSITION
{
	OVERPO_NO,
	OVERPO_YES
};

//아이템
enum TYPE_ATTRIBUTE
{
	TYPE_A_NONE,

	TYPE_A_TR_START,		//시작점

	TYPE_A_IT_HEAL,			//약품류
	TYPE_A_IT_FOOD,			//음식류
	TYPE_A_IT_OIL,			//기름류
	TYPE_A_IT_BULLET,		//총알류

	TYPE_A_WP_GUN,			//총류
	TYPE_A_WP_BOMB,			//폭탄류
	TYPE_A_WP_SWORD,		//칼류
	TYPE_A_WP_ROD,			//창류 (휘두를수 있는것)
	TYPE_A_WP_AXE,			//도끼류
	TYPE_A_WP_BOW,			//활류
	TYPE_A_WP_MACHINE 		//기계류 (기름소비)
};

