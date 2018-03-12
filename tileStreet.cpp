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
	//샘플타일 초기화
	_tileSample = new tile;
	_tileSample->tileSetup("맵툴타일거리", 740, 100, ATTR_NONE, TYPE_NONE, 1.5);

	//선택할 샘플타일 담을 구조체
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
	//-------------------------------------------------- 타일맵 클립핑 Start --------------------------------------------------
	D2DMANAGER->pRenderTarget->PushAxisAlignedClip(RectF(0, 0, _showWindowX, _showWindowY), D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	//-------------------------------------------------- 타일맵 클립핑 Start --------------------------------------------------


	//샘플타일 그리기
	_tileSample->tileRender("맵툴타일거리");

	//샘플타일 선택(빨강 렉트 그리기)
	_selectTile = _tileSample->tileSelect("맵툴타일거리");  //선택한 타일정보 담기

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


