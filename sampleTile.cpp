#include "stdafx.h"
#include "sampleTile.h"


sampleTile::sampleTile()
{
}
sampleTile::~sampleTile()
{

}

HRESULT sampleTile::init(string imgName, ATTRIBUTE att, TILE_TYPE type, float scale)
{
	//����Ÿ�� ����
	_sTile.imgName = imgName;
	_sTile.att = att;
	_sTile.type = type;
	_sTile.scale = scale;
	_sTile.showX = 740 + 240;
	_sTile.showY = 100 + 505;

	//����Ÿ�� �ʱ�ȭ
	_tileSample = new tile;
	_tileSample->tileSetup(_sTile.imgName, 740, 100, _sTile.att, _sTile.type, _sTile.scale);

	//������ ����Ÿ�� ���� ����ü
	ZeroMemory(&_selectTile, sizeof(tagTile));

	return S_OK;
}

void sampleTile::release()
{

}

void sampleTile::update() 
{

}

void sampleTile::render() 
{

	//-------------------------------------------------- Ÿ�ϸ� Ŭ���� Start --------------------------------------------------
	D2DMANAGER->pRenderTarget->PushAxisAlignedClip(RectF(0, 0, _sTile.showX, _sTile.showY), D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	//-------------------------------------------------- Ÿ�ϸ� Ŭ���� Start --------------------------------------------------

	//resetSelTile();

	//����Ÿ�� �׸���
	_tileSample->tileRender(_sTile.imgName);

	//����Ÿ�� ����(���� ��Ʈ �׸���)
	_selectTile = _tileSample->tileSelect(_sTile.imgName);  //������ Ÿ������ ���

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

void sampleTile::resetSelTile()
{
	if (_selectVTile.size() != 0)
	{
		_selectVTile.clear();
	}
}
