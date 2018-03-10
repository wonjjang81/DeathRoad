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
	_tileTr->tileSetup("맵툴타일바닥", 740, 100, ATTR_MOVE, TYPE_TERRAIN, 1.5);

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
	_tileTr->tileRender("맵툴타일바닥");
	//타일 선택(빨강 렉트 그리기)
	_selectTile = _tileTr->tileSelect("맵툴타일바닥");  //선택한 타일정보 담기

	if (_selectTile.img != NULL)
	{
		_selectVTile.clear();
		_selectVTile.push_back(_selectTile);
	}

	if (_selectVTile.size() != 0)
	D2DMANAGER->drawIntText(_selectVTile[0].index, 600, 100);
}

