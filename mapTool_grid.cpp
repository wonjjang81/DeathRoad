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


		//grid
		for (int i = 0; i <= TILEY; ++i)
		{
			for (int j = 0; j <= TILEX; ++j)
			{
				//예외처리: 화면밖 렌더X
				if ((j * TILE_SIZEX) + _moveX >= _showWindowX / scale) continue;  //가로열(우측)
				if ((j * TILE_SIZEX) + _moveX <= 0)					  continue;	 //가로열(좌측)
				if ((i * TILE_SIZEY) + _moveY >= _showWindowY / scale) continue;  //세로열(우측)
				if ((i * TILE_SIZEY) + _moveY <= 0)					  continue;  //세로열(좌측)

				D2DMANAGER->drawLine(D2DMANAGER->createBrush(RGB(0, 255, 0), 0.03f), (TILE_SIZEX * j) + _moveX, 0 + _moveY, (TILE_SIZEX * j) + _moveX, TILE_TOTAL_SIZEY + _moveY, 0.3f);
				D2DMANAGER->drawLine(D2DMANAGER->createBrush(RGB(0, 255, 0), 0.03f), 0 + _moveX, (TILE_SIZEY * i) + _moveY, TILE_TOTAL_SIZEX + _moveX, (TILE_SIZEY * i) + _moveY, 0.3f);
			}
		}

		//index
		for (int i = 0; i < TILEY; ++i)
		{
			for (int j = 0; j < TILEX; ++j)
			{
				//예외처리: 화면밖 렌더X
				if ((j * TILE_SIZEX) + _moveX >= _showWindowX / scale) continue;  //가로열(우측)
				if ((j * TILE_SIZEX) + _moveX < 0)					  continue;	 //가로열(좌측)
				if ((i * TILE_SIZEY) + _moveY >= _showWindowY / scale) continue;  //세로열(우측)
				if ((i * TILE_SIZEY) + _moveY < 0)					  continue;  //세로열(좌측)

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