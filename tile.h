#pragma once
#include "gameNode.h"
#include "tileInfo.h"

#include <vector>
#include <map>

//타일 방향
enum TILE_DIRECTION
{
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_NONE
};

struct tagTile
{
	RECT      rc;
	image*    img;
	TILE_TYPE tileType;
	ATTRIBUTE attribute;

	int index;
	float x, y;
	float gapX, gapY;
	float scale;
	int frameX;
	int frameY;
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



public:
	HRESULT init();
	void release();
	void update();
	void render();

	void tileSetup(string tileName, float x, float y, ATTRIBUTE attribute, TILE_TYPE tileType, float scale);
	void tileRender(string tileName);
	tagTile tileSelect(string tileName);
	void tileDrawFillRc(tagTile selectTile, COLORREF color, float opacity);
	void setTileAttribute(tagTile selectTile, ATTRIBUTE attribute);
	void setTileType(tagTile selectTile, TILE_TYPE tileType);

	tile();
	~tile();
};

