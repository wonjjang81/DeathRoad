#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>


class mapTool_menu_terrain : public gameNode
{
private:
	typedef vector<tagTile>			  vTileTr;
	typedef vector<tagTile>::iterator viTileTr;
private:
	tile*   _tileTr;
	tagTile _selectTile;   //선택한 타일정보

public:
	vTileTr _selectVTile;  //선택한 타일정보를 담아둘 벡터

public:
	HRESULT init();
	void release();
	void update();
	void render();


	mapTool_menu_terrain();
	~mapTool_menu_terrain();
};

