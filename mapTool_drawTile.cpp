#include "stdafx.h"
#include "mapTool.h"


void mapTool::tileDraw(float scale)
{
	//-------------------------------------------------- 타일맵 클립핑 Start --------------------------------------------------
	D2DMANAGER->pRenderTarget->PushAxisAlignedClip(RectF(0, 0, _showWindowX, _showWindowY), D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	//-------------------------------------------------- 타일맵 클립핑 Start --------------------------------------------------


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
				tile.attribute = ATTR_NONE;
				tile.tileType  = TYPE_NONE;

				_vSaveTr.push_back(tile);
			}
		}
	}


	//========================== 타일 그리기 Start ==========================
	//------------------------------- Terrain -------------------------------
	for (int i = 0; i < _vSaveTr.size(); ++i)
	{
		//예외처리
		if (_vSaveTr[i].img == NULL) continue;  //이미지 X


		//타일렉트 보정
		RECT reRect;
		reRect.left   = (_vSaveTr[i].rc.left   + _moveX) * scale;
		reRect.top    = (_vSaveTr[i].rc.top    + _moveY) * scale;
		reRect.right  = (_vSaveTr[i].rc.right  + _moveX) * scale;
		reRect.bottom = (_vSaveTr[i].rc.bottom + _moveY) * scale;

		//예외처리: 화면밖 렌더X
		if (reRect.left   >= _showWindowX)  continue;  //가로열(우측)
		if (reRect.right  < 0)			    continue;  //가로열(좌측)
		if (reRect.top    >= _showWindowY)  continue;  //세로열(상부)
		if (reRect.bottom < 0)			    continue;  //세로열(하부)

		_vSaveTr[i].img->frameRender(1.0f, reRect.left, reRect.top,
			_vSaveTr[i].frameX, _vSaveTr[i].frameY, 0.0f, scale);

		//렉트 확인용
		//D2DMANAGER->drawRectangle(D2DMANAGER->createBrush(RGB(255, 0, 0)),
		//	reRect.left   ,
		//	reRect.top    ,
		//	reRect.right  ,
		//	reRect.bottom);
	}
	//------------------------------- Building ------------------------------
	for (int i = 0; i < _vSaveBd.size(); ++i)
	{
		//예외처리
		if (_vSaveBd[i].img == NULL) continue;  //이미지 X

		//타일렉트 보정
		RECT reRect;
		reRect.left   = (_vSaveBd[i].rc.left   + _moveX) * scale;
		reRect.top    = (_vSaveBd[i].rc.top    + _moveY) * scale;
		reRect.right  = (_vSaveBd[i].rc.right  + _moveX) * scale;
		reRect.bottom = (_vSaveBd[i].rc.bottom + _moveY) * scale;

		//예외처리: 화면밖 렌더X
		if (reRect.left >= _showWindowX)  continue;  //가로열(우측)
		if (reRect.right  < 0)			  continue;  //가로열(좌측)
		if (reRect.top  >= _showWindowY)  continue;  //세로열(상부)
		if (reRect.bottom < 0)			  continue;  //세로열(하부)

		_vSaveBd[i].img->frameRender(1.0f, reRect.left, reRect.top,
			_vSaveBd[i].frameX, _vSaveBd[i].frameY, 0.0f, scale);

		//렉트 확인용
		//D2DMANAGER->drawRectangle(D2DMANAGER->createBrush(RGB(255, 0, 0)),
		//	reRect.left   ,
		//	reRect.top    ,
		//	reRect.right  ,
		//	reRect.bottom);
	}

	//=========================== 타일 그리기 End ===========================


	//--------------------------------------------------- 타일맵 클립핑 end ---------------------------------------------------
	D2DMANAGER->pRenderTarget->PopAxisAlignedClip();
	//--------------------------------------------------- 타일맵 클립핑 end ---------------------------------------------------
}