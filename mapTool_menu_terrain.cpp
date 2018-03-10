#include "stdafx.h"
#include "mapTool_menu_terrain.h"


mapTool_menu_terrain::mapTool_menu_terrain()
{
}
mapTool_menu_terrain::~mapTool_menu_terrain()
{
}

HRESULT mapTool_menu_terrain::init()
{
	_tileTr = new tile;
	_tileTr->tileSetup("����Ÿ�Ϲٴ�", 740, 100, ATTR_MOVE, TYPE_TERRAIN, 1.5);

	ZeroMemory(&_selectTile, sizeof(tagTile));

	return S_OK;
}

void mapTool_menu_terrain::release()
{

}

void mapTool_menu_terrain::update()	
{

}

void mapTool_menu_terrain::render()	
{
	_tileTr->tileRender("����Ÿ�Ϲٴ�");
	//Ÿ�� ����(���� ��Ʈ �׸���)
	_selectTile = _tileTr->tileSelect("����Ÿ�Ϲٴ�");  //������ Ÿ������ ���

	if (_selectTile.img != NULL)
	{
		_selectVTile.clear();
		_selectVTile.push_back(_selectTile);
	}

	if (_selectVTile.size() != 0)
	D2DMANAGER->drawIntText(_selectVTile[0].index, 600, 100);
}

