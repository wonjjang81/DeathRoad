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
	tagTile _selectTile;   //������ Ÿ������

public:
	vTileTr _selectVTile;  //������ Ÿ�������� ��Ƶ� ����

public:
	HRESULT init();
	void release();
	void update();
	void render();


	mapTool_menu_terrain();
	~mapTool_menu_terrain();
};

