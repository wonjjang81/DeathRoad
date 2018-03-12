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
	//샘플타일 초기화
	_tileTr = new tile;
	_tileTr->tileSetup("맵툴타일바닥", 740, 100, ATTR_MOVE, TYPE_TERRAIN, 1.5);

	//선택할 샘플타일 담을 구조체
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
	//샘플타일 그리기
	_tileTr->tileRender("맵툴타일바닥");

	//샘플타일 선택(빨강 렉트 그리기)
	_selectTile = _tileTr->tileSelect("맵툴타일바닥");  //선택한 타일정보 담기

	//선택한 샘플타일 벡터에 담기
	if (_selectTile.img != NULL)
	{
		_selectVTile.clear();
		_selectVTile.push_back(_selectTile);	
	}

	//선택한 샘플타일 칠해주기
	if (_selectVTile.size() != 0) _tileTr->tileDrawFillRc(_selectVTile[0], RGB(0, 255, 255), 0.5f);
}

void mapTool_menu_terrain::resetSelTile()
{
	if (_selectVTile.size() != 0)
	{
		_selectVTile.clear();
	}
}