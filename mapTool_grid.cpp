#include "stdafx.h"
#include "mapTool.h"


void mapTool::gridRender(float scale)
{
	//cameraOutLine
	D2DMANAGER->drawRectangle(D2DMANAGER->defaultBrush, 0, 0, _showWindowX, _showWindowY);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{

		//타일맵 클립핑
		D2DMANAGER->pRenderTarget->PushAxisAlignedClip(RectF(0, 0, _showWindowX, _showWindowY), D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);


		//스케일 설정
		Matrix3x2F matScale;
		matScale = Matrix3x2F::Scale(scale, scale, Point2F(0, 0));
		D2DMANAGER->pRenderTarget->SetTransform(matScale);


		//grid 벡터에 담기
		if ((_vTile.size() == 0))
		{
			for (int i = 0; i < TILEY; ++i)
			{
				for (int j = 0; j < TILEX; ++j)
				{
					//렉트로 그리기
					tagSampleTile tile;
					tile.rc.left   = TILE_SIZEX * j;
					tile.rc.top    = TILE_SIZEY * i;
					tile.rc.right  = TILE_SIZEX * (j + 1);
					tile.rc.bottom = TILE_SIZEY * (i + 1);
					tile.index = (TILEX * i) + j;

					_vTile.push_back(tile);  
				}
			}
		}

		for (int i = 0; i < _vTile.size(); ++i)
		{
			//예외처리: 화면밖 렌더X
			if (_vTile[i].rc.left + _moveX >= _showWindowX / scale) continue;  //가로열(우측)
			if (_vTile[i].rc.right + _moveX < 0)					 continue;  //가로열(좌측)
			if (_vTile[i].rc.top + _moveY >= _showWindowY / scale)  continue;  //세로열(상부)
			if (_vTile[i].rc.bottom + _moveY < 0)					 continue;  //세로열(하부)

			D2DMANAGER->drawRectangle(D2DMANAGER->createBrush(RGB(0, 255, 0), 0.03f),
				_vTile[i].rc.left + _moveX,
				_vTile[i].rc.top + _moveY,
				_vTile[i].rc.right + _moveX,
				_vTile[i].rc.bottom + _moveY);
		}


		//index
		for (int i = 0; i < TILEY; ++i)
		{
			for (int j = 0; j < TILEX; ++j)
			{
				//예외처리: 화면밖 렌더X
				if ((j * TILE_SIZEX) + _moveX >= _showWindowX / scale) continue;  //가로열(우측)
				if ((j * TILE_SIZEX) + _moveX < 0)					   continue;	 //가로열(좌측)
				if ((i * TILE_SIZEY) + _moveY >= _showWindowY / scale) continue;  //세로열(우측)
				if ((i * TILE_SIZEY) + _moveY < 0)					   continue;  //세로열(좌측)

				WCHAR strIndex[128];
				ZeroMemory(&strIndex, sizeof(strIndex));
				swprintf(strIndex, L"%d", (TILEX * i) + j);

				D2DMANAGER->drawTextDwd(D2DMANAGER->createBrush(RGB(0, 0, 255), 0.3f), L"맑은고딕", 3, strIndex,
					(j * TILE_SIZEX) + _moveX, (i * TILE_SIZEY) + _moveY,
					(j * TILE_SIZEX) + 30 + _moveX, (i * TILE_SIZEY) + 30 + _moveY);
			}
		}


		//초기화
		D2DMANAGER->pRenderTarget->SetTransform(Matrix3x2F::Identity());
		D2DMANAGER->pRenderTarget->PopAxisAlignedClip();
	}
}


void mapTool::selectTile(int scale)
{
	//타일맵 클립핑
	D2DMANAGER->pRenderTarget->PushAxisAlignedClip(RectF(0, 0, _showWindowX, _showWindowY), D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);

	//스케일 설정
	Matrix3x2F matScale;
	matScale = Matrix3x2F::Scale(scale, scale, Point2F(0, 0));
	D2DMANAGER->pRenderTarget->SetTransform(matScale);

	for (int i = 0; i < _vTile.size(); ++i)
	{
		//예외처리
		if (_ptMouse.x > _showWindowX) break;  //우측
		if (_ptMouse.x < 0)			   break;  //좌측
		if (_ptMouse.y < 0)			   break;  //상부
		if (_ptMouse.y > _showWindowY) break;  //하부

		//타일렉트 보정
		RECT reRect;
		reRect.left   = (_vTile[i].rc.left	  + _moveX) * scale;
		reRect.top    = (_vTile[i].rc.top	  + _moveY) * scale;
		reRect.right  = (_vTile[i].rc.right  + _moveX) * scale;
		reRect.bottom = (_vTile[i].rc.bottom + _moveY) * scale;

		if (PtInRect(&reRect, _ptMouse))
		{
			D2DMANAGER->drawRectangle(D2DMANAGER->createBrush(RGB(0, 0, 255)),
				_vTile[i].rc.left   + _moveX,
				_vTile[i].rc.top    + _moveY,
				_vTile[i].rc.right  + _moveX,
				_vTile[i].rc.bottom + _moveY);

			break;
		}
	}

	//초기화
	D2DMANAGER->pRenderTarget->SetTransform(Matrix3x2F::Identity());
	D2DMANAGER->pRenderTarget->PopAxisAlignedClip();
}
