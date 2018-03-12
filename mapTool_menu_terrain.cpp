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
	//����Ÿ�� �ʱ�ȭ
	_tileTr = new tile;
	_tileTr->tileSetup("����Ÿ�Ϲٴ�", 740, 100, ATTR_MOVE, TYPE_TERRAIN, 1.5);

	//������ ����Ÿ�� ���� ����ü
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
	//����Ÿ�� �׸���
	_tileTr->tileRender("����Ÿ�Ϲٴ�");

	//����Ÿ�� ����(���� ��Ʈ �׸���)
	_selectTile = _tileTr->tileSelect("����Ÿ�Ϲٴ�");  //������ Ÿ������ ���

	//������ ����Ÿ�� ���Ϳ� ���
	if (_selectTile.img != NULL)
	{
		_selectVTile.clear();
		_selectVTile.push_back(_selectTile);	
	}

	//������ ����Ÿ�� ĥ���ֱ�
	if (_selectVTile.size() != 0) _tileTr->tileDrawFillRc(_selectVTile[0], RGB(0, 255, 255), 0.5f);
}

void mapTool_menu_terrain::resetSelTile()
{
	if (_selectVTile.size() != 0)
	{
		_selectVTile.clear();
	}
}