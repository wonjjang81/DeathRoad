#include "stdafx.h"
#include "tileFloor.h"


tileFloor::tileFloor()
{
}
tileFloor::~tileFloor()
{
}

HRESULT tileFloor::init()
{
	////����Ÿ�� �ʱ�ȭ
	//_tileSample = new tile;
	//_tileSample->tileSetup("����Ÿ�Ϲٴ�", 740, 100, ATTR_NONE, TYPE_TERRAIN, 1.5);

	////������ ����Ÿ�� ���� ����ü
	//ZeroMemory(&_selectTile, sizeof(tagTile));

	//_showWindowX = 740 + 240;
	//_showWindowY = 100 + 505;

	return S_OK;
}

void tileFloor::release()
{

}

void tileFloor::update()	
{

}

void tileFloor::render()	
{

	////-------------------------------------------------- Ÿ�ϸ� Ŭ���� Start --------------------------------------------------
	//D2DMANAGER->pRenderTarget->PushAxisAlignedClip(RectF(0, 0, _showWindowX, _showWindowY), D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	////-------------------------------------------------- Ÿ�ϸ� Ŭ���� Start --------------------------------------------------


	////����Ÿ�� �׸���
	//_tileSample->tileRender("����Ÿ�Ϲٴ�");

	////����Ÿ�� ����(���� ��Ʈ �׸���)
	//_selectTile = _tileSample->tileSelect("����Ÿ�Ϲٴ�");  //������ Ÿ������ ���

	////������ ����Ÿ�� ���Ϳ� ���
	//if (_selectTile.img != NULL)
	//{
	//	_selectVTile.clear();
	//	_selectVTile.push_back(_selectTile);	
	//}

	////������ ����Ÿ�� ĥ���ֱ�
	//if (_selectVTile.size() != 0) _tileSample->tileDrawFillRc(_selectVTile[0], RGB(0, 255, 255), 0.5f);


	////--------------------------------------------------- Ÿ�ϸ� Ŭ���� end ---------------------------------------------------
	//D2DMANAGER->pRenderTarget->PopAxisAlignedClip();
	////--------------------------------------------------- Ÿ�ϸ� Ŭ���� end ---------------------------------------------------
}

