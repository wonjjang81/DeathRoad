#include "stdafx.h"
#include "mapTool.h"


void mapTool::tileDraw(float scale)
{
	//선택한 타일 정보 가져오기
	if (_menuTabOn && _menuTr->_selectVTile.size() != 0)
	{
		_darwTile = _menuTr->_selectVTile[0];
	}
	else return;


	//타일맵 클립핑
	D2DMANAGER->pRenderTarget->PushAxisAlignedClip(RectF(0, 0, _showWindowX, _showWindowY), D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);

	//기본타일 벡터에 담기
	if ((_vSaveTr.size() == 0))
	{
		for (int i = 0; i < TILEY; ++i)
		{
			for (int j = 0; j < TILEX; ++j)
			{
				tagTile tile;
				ZeroMemory(&tile, sizeof(tagTile));

				tile.rc.left   = TILE_SIZEX * j;
				tile.rc.top    = TILE_SIZEY * i;
				tile.rc.right  = TILE_SIZEX * (j + 1);
				tile.rc.bottom = TILE_SIZEY * (i + 1);
				tile.index     = (TILEX * i) + j;
				tile.attribute = ATTR_UNMOVE;
				tile.tileType  = TYPE_TERRAIN;

				_vSaveTr.push_back(tile);
			}
		}
	}


	//타일 그리기
	for (int i = 0; i < _vSaveTr.size(); ++i)
	{
		//예외처리: 화면밖 렌더X
		if (_vSaveTr[i].rc.left   + _moveX >= _showWindowX / scale)  continue;  //가로열(우측)
		if (_vSaveTr[i].rc.right  + _moveX < 0)					     continue;  //가로열(좌측)
		if (_vSaveTr[i].rc.top    + _moveY >= _showWindowY / scale)  continue;  //세로열(상부)
		if (_vSaveTr[i].rc.bottom + _moveY < 0)					     continue;  //세로열(하부)
		if (_vSaveTr[i].img == NULL) 					             continue;  //이미지X

		_vSaveTr[i].img->frameRender(1.0f, 
			_vSaveTr[i].rc.left + _moveX,
			_vSaveTr[i].rc.top + _moveY,
			_vSaveTr[i].frameX, _vSaveTr[i].frameY, 1.0f, scale);
	}

	//초기화
	D2DMANAGER->pRenderTarget->PopAxisAlignedClip();
}