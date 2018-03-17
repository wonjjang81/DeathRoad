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
	//샘플타일 정보
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


	//샘플타일 초기화
	_tileSample = new tile;
	_tileSample->tileSetup(_sTile.imgName, 740, 100, _sTile.att, _sTile.type, _sTile.anchor, _sTile.overPos, _sTile.scale);

	//선택할 샘플타일 담을 구조체
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

	//-------------------------------------------------- 타일맵 클립핑 Start --------------------------------------------------
	D2DMANAGER->pRenderTarget->PushAxisAlignedClip(RectF(740, 100, _sTile.showX, _sTile.showY), D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	//-------------------------------------------------- 타일맵 클립핑 Start --------------------------------------------------

	//resetSelTile();

	//샘플타일 그리기
	_tileSample->tileRender(_sTile.imgName, _sTile.keyMoveX, _sTile.keyMoveY);

	//샘플타일 선택(빨강 렉트 그리기)
	_selectTile = _tileSample->tileSelect(_sTile.imgName, _sTile.keyMoveX, _sTile.keyMoveY);  //선택한 타일정보 담기

	//선택한 샘플타일 벡터에 담기
	if (_selectTile.img != NULL)
	{
		_selectVTile.clear();
		_selectVTile.push_back(_selectTile);
	}

	//선택한 샘플타일 칠해주기
	if (_selectVTile.size() != 0) _tileSample->tileDrawFillRc(_selectVTile[0], RGB(0, 255, 255), 0.5f, _sTile.keyMoveX, _sTile.keyMoveY);


	//--------------------------------------------------- 타일맵 클립핑 end ---------------------------------------------------
	D2DMANAGER->pRenderTarget->PopAxisAlignedClip();
	//--------------------------------------------------- 타일맵 클립핑 end ---------------------------------------------------
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
	//키조작
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		//예외처리:이동X            (타일크기 X 스케일 X 화면밖 타일수)
		//if (abs(_sTile.keyMoveX) >= (_tileSizeX) * (_tileX - (int)(_sTile.keyMoveX / (_tileSizeX * _sTile.scale)))) return;
		_sTile.keyMoveX -= 1 * _moveSpeed;
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (_sTile.keyMoveX >= 0) return;  //예외처리:이동X 
		_sTile.keyMoveX += 1 * _moveSpeed;
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		if (_sTile.keyMoveY >= 0) return;  //예외처리:이동X 
		_sTile.keyMoveY += 1 * _moveSpeed;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		//예외처리:이동X   (타일크기 X 스케일 X 화면밖 타일수)
		//if (abs(_sTile.keyMoveY) >= (_tileSizeY) * (_tileY - (int)(_sTile.keyMoveY / (_tileSizeY * _sTile.scale)))) return;
		_sTile.keyMoveY -= 1 * _moveSpeed;
	}
}


