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

	_showWindowX = 740 + 240;
	_showWindowY = 100 + 505;


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
	//-------------------------------------------------- Ÿ�ϸ� Ŭ���� Start --------------------------------------------------
	D2DMANAGER->pRenderTarget->PushAxisAlignedClip(RectF(0, 0, _showWindowX, _showWindowY), D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	//-------------------------------------------------- Ÿ�ϸ� Ŭ���� Start --------------------------------------------------


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


	//--------------------------------------------------- Ÿ�ϸ� Ŭ���� end ---------------------------------------------------
	D2DMANAGER->pRenderTarget->PopAxisAlignedClip();
	//--------------------------------------------------- Ÿ�ϸ� Ŭ���� end ---------------------------------------------------
}


