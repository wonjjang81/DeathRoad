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
		for (int i = 0; i < _tileY; ++i)
		{
			for (int j = 0; j < _tileX; ++j)
			{
				tagTile tile;
				ZeroMemory(&tile, sizeof(tagTile));

				tile.rc.left   = TILE_SIZEX * j;
				tile.rc.top    = TILE_SIZEY * i;
				tile.rc.right  = TILE_SIZEX * (j + 1);
				tile.rc.bottom = TILE_SIZEY * (i + 1);
				tile.index     = (_tileX * i) + j;
				tile.attribute = ATTR_NONE;
				tile.tileType  = TYPE_NONE;

				_vSaveTr.push_back(tile);
			}
		}
	}


	//========================== 타일 그리기 Start ==========================
	//Terrain
	vTileDraw(_vSaveTr, scale);

	//Building
	vTileDraw(_vSaveBd, scale);

	//Road
	vTileDraw(_vSaveRd, scale);

	//Furniture
	vTileDraw(_vSaveFt, scale);

	//Item
	vTileDraw(_vSaveIt, scale);

	//Weapon
	vTileDraw(_vSaveWp, scale);

	//Enemy
	vTileDraw(_vSaveEm, scale);
	//=========================== 타일 그리기 End ===========================


	//--------------------------------------------------- 타일맵 클립핑 end ---------------------------------------------------
	D2DMANAGER->pRenderTarget->PopAxisAlignedClip();
	//--------------------------------------------------- 타일맵 클립핑 end ---------------------------------------------------
}


//타일 그리기 [원형]: 벡터
void mapTool::vTileDraw(vSaveTile tileVector, float scale)
{
	for (int i = 0; i < tileVector.size(); ++i)
	{
		//예외처리
		if (tileVector[i].img == NULL) continue;  //이미지 X

												//타일렉트 보정
		RECT reRect;
		reRect.left = (tileVector[i].rc.left     + _moveX) * scale;
		reRect.top = (tileVector[i].rc.top       + _moveY) * scale;
		reRect.right = (tileVector[i].rc.right   + _moveX) * scale;
		reRect.bottom = (tileVector[i].rc.bottom + _moveY) * scale;

		//위치 보정(타일 중심)
		float tmpCenterX = reRect.left + (tileVector[i].centerX * scale);
		float tmpCenterY = reRect.top  + (tileVector[i].centerY * scale);

		//예외처리: 화면밖 렌더X
		if (reRect.left >= _showWindowX)  continue;  //가로열(우측)
		if (reRect.right  < 0)			  continue;  //가로열(좌측)
		if (reRect.top >= _showWindowY)  continue;  //세로열(상부)
		if (reRect.bottom < 0)			  continue;  //세로열(하부)

		tileVector[i].img->frameRender(1.0f, tmpCenterX, tmpCenterY,
			tileVector[i].frameX, tileVector[i].frameY, 0.0f, scale);

		//렉트 확인용
		D2DMANAGER->drawRectangle(D2DMANAGER->createBrush(RGB(255, 0, 0)),
			reRect.left,
			reRect.top,
			reRect.right,
			reRect.bottom);
	}

}