#pragma once
#include "gameNode.h"
#include "tileInfo.h"

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
	int tileType;
	int attribute;
	D2D1_RECT_F rc;
	int frameX;
	int frameY;
};

struct tagSampleTile
{
	D2D1_RECT_F rc;
	int frameX;
	int frameY;
};

struct tagCurrentTile
{
	int x;
	int y;
};

class tile : public gameNode
{
private:
	tagCurrentTile _currentTile;
	tagSampleTile  _sampleTile[SAMPLETILEX * SAMPLETILEY];
	tagTile		   _tiles[TILEX * TILEY];



public:
	HRESULT init();
	void release();
	void update();
	void render();

	tile();
	~tile();
};

