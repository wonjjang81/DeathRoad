#include "stdafx.h"
#include "sampleTile.h"


sampleTile::sampleTile()
{
}
sampleTile::~sampleTile()
{

}

HRESULT sampleTile::init(string imgName, ATTRIBUTE att, TILE_TYPE tileType, ANCHOR_TYPE anchorType, OVERLAPPOSITION overPosition, float scale)
{
	//����Ÿ�� ����
	_sTile.imgName = imgName;
	_sTile.att = att;
	_sTile.type = tileType;
	_sTile.anchor = anchorType;
	_sTile.overPos = overPosition;
	_sTile.scale = scale;
	_sTile.showX = 740 + 240;
	_sTile.showY = 100 + 500;
	_sTile.keyMoveX = 0;
	_sTile.keyMoveY = 0;


	//����Ÿ�� �ʱ�ȭ
	_tileSample = new tile;
	_tileSample->tileSetup(_sTile.imgName, 740, 100, _sTile.att, _sTile.type, _sTile.anchor, _sTile.overPos, _sTile.scale);

	//������ ����Ÿ�� ���� ����ü
	ZeroMemory(&_selectTile, sizeof(tagTile));

	_moveSpeed = 3;
	_tileX = IMAGEMANAGER->findImage(_sTile.imgName)->getFrameX();
	_tileY = IMAGEMANAGER->findImage(_sTile.imgName)->getFrameY();
	_tileSizeX = IMAGEMANAGER->findImage(_sTile.imgName)->getFrameWidth();
	_tileSizeY = IMAGEMANAGER->findImage(_sTile.imgName)->getFrameHeight();


	return S_OK;
}

void sampleTile::release()
{

}

void sampleTile::update() 
{
	mapKeyControl();

}

void sampleTile::render() 
{

	//-------------------------------------------------- Ÿ�ϸ� Ŭ���� Start --------------------------------------------------
	D2DMANAGER->pRenderTarget->PushAxisAlignedClip(RectF(740, 100, _sTile.showX, _sTile.showY), D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	//-------------------------------------------------- Ÿ�ϸ� Ŭ���� Start --------------------------------------------------

	//resetSelTile();

	//����Ÿ�� �׸���
	_tileSample->tileRender(_sTile.imgName, _sTile.keyMoveX, _sTile.keyMoveY);

	//����Ÿ�� ����(���� ��Ʈ �׸���)
	_selectTile = _tileSample->tileSelect(_sTile.imgName, _sTile.keyMoveX, _sTile.keyMoveY);  //������ Ÿ������ ���

	//������ ����Ÿ�� ���Ϳ� ���
	if (_selectTile.img != NULL)
	{
		_selectVTile.clear();
		_selectVTile.push_back(_selectTile);
	}

	//������ ����Ÿ�� ĥ���ֱ�
	if (_selectVTile.size() != 0) _tileSample->tileDrawFillRc(_selectVTile[0], RGB(0, 255, 255), 0.5f, _sTile.keyMoveX, _sTile.keyMoveY);


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


void sampleTile::mapKeyControl()
{
	//Ű����
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		//����ó��:�̵�X            (Ÿ��ũ�� X ������ X ȭ��� Ÿ�ϼ�)
		//if (abs(_sTile.keyMoveX) >= (_tileSizeX) * (_tileX - (int)(_sTile.keyMoveX / (_tileSizeX * _sTile.scale)))) return;
		_sTile.keyMoveX -= 1 * _moveSpeed;
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (_sTile.keyMoveX >= 0) return;  //����ó��:�̵�X 
		_sTile.keyMoveX += 1 * _moveSpeed;
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		if (_sTile.keyMoveY >= 0) return;  //����ó��:�̵�X 
		_sTile.keyMoveY += 1 * _moveSpeed;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		//����ó��:�̵�X   (Ÿ��ũ�� X ������ X ȭ��� Ÿ�ϼ�)
		//if (abs(_sTile.keyMoveY) >= (_tileSizeY) * (_tileY - (int)(_sTile.keyMoveY / (_tileSizeY * _sTile.scale)))) return;
		_sTile.keyMoveY -= 1 * _moveSpeed;
	}
}


