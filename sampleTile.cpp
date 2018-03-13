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
	//샘플타일 정보
	_sTile.imgName = imgName;
	_sTile.att = att;
	_sTile.type = type;
	_sTile.scale = scale;
	_sTile.showX = 740 + 240;
	_sTile.showY = 100 + 505;

	//샘플타일 초기화
	_tileSample = new tile;
	_tileSample->tileSetup(_sTile.imgName, 740, 100, _sTile.att, _sTile.type, _sTile.scale);

	//선택할 샘플타일 담을 구조체
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

	//-------------------------------------------------- 타일맵 클립핑 Start --------------------------------------------------
	D2DMANAGER->pRenderTarget->PushAxisAlignedClip(RectF(0, 0, _sTile.showX, _sTile.showY), D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	//-------------------------------------------------- 타일맵 클립핑 Start --------------------------------------------------

	//resetSelTile();

	//샘플타일 그리기
	_tileSample->tileRender(_sTile.imgName);

	//샘플타일 선택(빨강 렉트 그리기)
	_selectTile = _tileSample->tileSelect(_sTile.imgName);  //선택한 타일정보 담기

	//선택한 샘플타일 벡터에 담기
	if (_selectTile.img != NULL)
	{
		_selectVTile.clear();
		_selectVTile.push_back(_selectTile);
	}

	//선택한 샘플타일 칠해주기
	if (_selectVTile.size() != 0) _tileSample->tileDrawFillRc(_selectVTile[0], RGB(0, 255, 255), 0.5f);


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
