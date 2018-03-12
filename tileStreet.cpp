#include "stdafx.h"
#include "tileStreet.h"


tileStreet::tileStreet()
{
}
tileStreet::~tileStreet()
{
}


HRESULT tileStreet::init()
{
	//����Ÿ�� �ʱ�ȭ
	_tileSample = new tile;
	_tileSample->tileSetup("����Ÿ�ϰŸ�", 740, 100, ATTR_NONE, TYPE_NONE, 1.5);

	//������ ����Ÿ�� ���� ����ü
	ZeroMemory(&_selectTile, sizeof(tagTile));

	return S_OK;
}

void tileStreet::release()
{

}

void tileStreet::update() 
{

}

void tileStreet::render() 
{
	//����Ÿ�� �׸���
	_tileSample->tileRender("����Ÿ�ϰŸ�");

	//����Ÿ�� ����(���� ��Ʈ �׸���)
	_selectTile = _tileSample->tileSelect("����Ÿ�ϰŸ�");  //������ Ÿ������ ���

	//������ ����Ÿ�� ���Ϳ� ���
	if (_selectTile.img != NULL)
	{
		_selectVTile.clear();
		_selectVTile.push_back(_selectTile);
	}

	//������ ����Ÿ�� ĥ���ֱ�
	if (_selectVTile.size() != 0) _tileSample->tileDrawFillRc(_selectVTile[0], RGB(0, 255, 255), 0.5f);
}


