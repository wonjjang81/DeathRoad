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

//RGB
#define WHITE	 RGB(255,255,255)
#define BLACK	 RGB(0  ,0  ,0)
#define BLUE	 RGB(255,0  ,0)
#define GREEN	 RGB(0  ,255,0)
#define RED		 RGB(0  ,0  ,255)
#define CYAN	 RGB(255,255,0)
#define MAGENTA  RGB(255,0  ,255)
#define YELLOW   RGB(0  ,255,255)

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

	ATTR_AFTERRENDER      //Z-order
};

//중복위치 렌더
enum OVERLAPPOSITION
{
	OVERPO_NO,
	OVERPO_YES
};




