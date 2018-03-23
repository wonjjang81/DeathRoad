#pragma once
#include "gameNode.h"
#include "tileInfo.h"

#include "dataSave.h"
#include "tileDataInfo.h"

#include <vector>
#include <map>

//타일방향
enum TILE_DIRECTION
{
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_NONE
};

//앵커타입
enum ANCHOR_TYPE
{
	ANCHOR_NONE,
	ANCHOR_LEFTTOP,
	ANCHOR_CENTER,
	ANCHOR_BOTTOMCENTER
};

struct tagTile
{
	RECT      rc;
	image*    img;
	TILE_TYPE tileType;       //타입
	ATTRIBUTE attribute;      //속성
	TYPE_ATTRIBUTE typeAtt;   //타입별 속성
	TYPE_ATTRIBUTE typeAtt2;  //타입별 속성
	ANCHOR_TYPE anchorType;   //앵커타입
	OVERLAPPOSITION overPos;  //중복위치 여부
	TCHAR imgName[64];
	int index;
	float x, y;
	float gapX, gapY;
	float scale;
	int frameX;
	int frameY;
	float moveX;
	float moveY;
	float centerX, centerY;   //렉트 중심좌표
	float reWidth, reHeight;  //렉트 사이즈 재설정(16 X 16)
	int id;                   //tile ID
};

struct tagSampleTile
{
	RECT rc;
	int index;
	int frameX;
	int frameY;
};

struct tagCurrentTile
{
	int index;
	float x;
	float y;
};

class tile : public gameNode
{
private:
	typedef vector<tagTile>				 vTile;
	typedef vector<tagTile>::iterator	 viTile;

	typedef map<string, vTile>           mTile;
	typedef map<string, vTile>::iterator iterTile;
private:
	mTile _mTile;

	//DataInfo
	dataSave* _tileData;


public:
	void tileSetup(string tileName, float x, float y, ATTRIBUTE attribute, TILE_TYPE tileType, TYPE_ATTRIBUTE typeAttr, ANCHOR_TYPE anchor, OVERLAPPOSITION overPosition, float scale);
	void tileRender(string tileName, float moveX = 0, float moveY = 0);
	tagTile tileSelect(string tileName, float moveX = 0, float moveY = 0);
	void tileDrawFillRc(tagTile selectTile, COLORREF color, float opacity, float moveX = 0, float moveY = 0);
	void setTileAttribute(tagTile selectTile, ATTRIBUTE attribute);
	void setTileType(tagTile selectTile, TILE_TYPE tileType);

	void setTileAnchor(tagTile& tile, ANCHOR_TYPE anchor);  //앵커타입별 이미지 Render 기준점 설정

	TYPE_ATTRIBUTE loadTileTypeAttribute(TILE_TYPE tileType, int index, int typeNum = 1);

	tile();
	~tile();
};

