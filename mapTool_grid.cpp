#include "stdafx.h"
#include "mapTool.h"


void mapTool::gridRender(float scale)
{
	//cameraOutLine
	D2DMANAGER->drawRectangle(D2DMANAGER->defaultBrush, 0, 0, _showWindowX, _showWindowY);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{

		//-------------------------------------------------- 타일맵 클립핑 Start --------------------------------------------------
		D2DMANAGER->pRenderTarget->PushAxisAlignedClip(RectF(0, 0, _showWindowX, _showWindowY), D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
		//-------------------------------------------------- 타일맵 클립핑 Start --------------------------------------------------


		//-------------------------------------------------- 타일맵 스케일 Start --------------------------------------------------
		Matrix3x2F matScale;
		matScale = Matrix3x2F::Scale(scale, scale, Point2F(0, 0));
		D2DMANAGER->pRenderTarget->SetTransform(matScale);
		//-------------------------------------------------- 타일맵 스케일 Start --------------------------------------------------


		for (int i = 0; i < _vTile.size(); ++i)
		{
			//예외처리: 화면밖 렌더X
			if (_vTile[i].rc.left   + _moveX >= _showWindowX / scale)  continue;  //가로열(우측)
			if (_vTile[i].rc.right  + _moveX < 0)					   continue;  //가로열(좌측)
			if (_vTile[i].rc.top    + _moveY >= _showWindowY / scale)  continue;  //세로열(상부)
			if (_vTile[i].rc.bottom + _moveY < 0)					   continue;  //세로열(하부)

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

		//속성 그리기(Ellipse)
		for (int i = 0; i < TILEY; ++i)
		{
			for (int j = 0; j < TILEX; ++j)
			{
				if (_vSaveTr[(TILEX * i) + j].attribute == ATTR_NONE)  continue;  //속성이 없으면...

				//위치정보
				float rcWidth = _vTile[(TILEX * i) + j].rc.right - _vTile[(TILEX * i) + j].rc.left;
				float rcHeight = _vTile[(TILEX * i) + j].rc.bottom - _vTile[(TILEX * i) + j].rc.top;
				float centerX = _vTile[(TILEX * i) + j].rc.left + (rcWidth / 2);
				float centerY = _vTile[(TILEX * i) + j].rc.top + (rcHeight / 2);
				float ellipseSize = 3;
				float startX = centerX - (ellipseSize / 2);
				float startY = centerY - (ellipseSize / 2);
				float endX = centerX + (ellipseSize / 2);
				float endY = centerY + (ellipseSize / 2);


				//예외처리: 화면밖 렌더X
				if ((j * TILE_SIZEX) + _moveX >= _showWindowX / scale) continue;  //가로열(우측)
				if ((j * TILE_SIZEX) + _moveX < 0)					   continue;  //가로열(좌측)
				if ((i * TILE_SIZEY) + _moveY >= _showWindowY / scale) continue;  //세로열(우측)
				if ((i * TILE_SIZEY) + _moveY < 0)					   continue;  //세로열(좌측)
	

				switch (_vSaveTr[(TILEX * i) + j].attribute)
				{
					case ATTR_MOVE:
						D2DMANAGER->drawEllipse(D2DMANAGER->createBrush(RGB(255, 0, 0)), startX + _moveX, startY + _moveY, endX + _moveX, endY + _moveY);
					break;
					case ATTR_UNMOVE:
						D2DMANAGER->drawEllipse(D2DMANAGER->createBrush(RGB(0, 255, 0)), startX + _moveX, startY + _moveY, endX + _moveX, endY + _moveY);
					break;
					case ATTR_AFTER_RENDER:
						D2DMANAGER->drawEllipse(D2DMANAGER->createBrush(RGB(0, 0, 255)), startX + _moveX, startY + _moveY, endX + _moveX, endY + _moveY);
					break;
				}
			}
		}


		//타입 그리기(Ellipse)
		for (int i = 0; i < TILEY; ++i)
		{
			for (int j = 0; j < TILEX; ++j)
			{
				if (_vSaveTr[(TILEX * i) + j].tileType == TYPE_NONE)   continue;  //타입이 없으면...

				//위치정보
				float rcWidth = _vTile[(TILEX * i) + j].rc.right - _vTile[(TILEX * i) + j].rc.left;
				float rcHeight = _vTile[(TILEX * i) + j].rc.bottom - _vTile[(TILEX * i) + j].rc.top;
				float centerX = _vTile[(TILEX * i) + j].rc.left + (rcWidth / 2);
				float centerY = _vTile[(TILEX * i) + j].rc.top + (rcHeight / 2);
				float ellipseSize = 5;
				float startX = centerX - (ellipseSize / 2);
				float startY = centerY - (ellipseSize / 2);
				float endX = centerX + (ellipseSize / 2);
				float endY = centerY + (ellipseSize / 2);


				//예외처리: 화면밖 렌더X
				if ((j * TILE_SIZEX) + _moveX >= _showWindowX / scale) continue;  //가로열(우측)
				if ((j * TILE_SIZEX) + _moveX < 0)					   continue;  //가로열(좌측)
				if ((i * TILE_SIZEY) + _moveY >= _showWindowY / scale) continue;  //세로열(우측)
				if ((i * TILE_SIZEY) + _moveY < 0)					   continue;  //세로열(좌측)


				switch (_vSaveTr[(TILEX * i) + j].tileType)
				{
					case TYPE_TERRAIN:
						D2DMANAGER->drawEllipse(D2DMANAGER->createBrush(RGB(255, 0, 0)), startX + _moveX, startY + _moveY, endX + _moveX, endY + _moveY);
					break;
					case TYPE_BUILDING:
						D2DMANAGER->drawEllipse(D2DMANAGER->createBrush(RGB(0, 255, 0)), startX + _moveX, startY + _moveY, endX + _moveX, endY + _moveY);
					break;
					case TYPE_ITEM:
						D2DMANAGER->drawEllipse(D2DMANAGER->createBrush(RGB(0, 0, 255)), startX + _moveX, startY + _moveY, endX + _moveX, endY + _moveY);
					break;
					case TYPE_WEAPON:
						D2DMANAGER->drawEllipse(D2DMANAGER->createBrush(RGB(0, 255, 255)), startX + _moveX, startY + _moveY, endX + _moveX, endY + _moveY);
					break;
					case TYPE_ENEMY:
						D2DMANAGER->drawEllipse(D2DMANAGER->createBrush(RGB(255, 255, 255)), startX + _moveX, startY + _moveY, endX + _moveX, endY + _moveY);
					break;
				}
			}
		}


		//--------------------------------------------------- 타일맵 스케일 end ---------------------------------------------------
		D2DMANAGER->pRenderTarget->SetTransform(Matrix3x2F::Identity());
		//--------------------------------------------------- 타일맵 스케일 end ---------------------------------------------------


		//--------------------------------------------------- 타일맵 클립핑 end ---------------------------------------------------
		D2DMANAGER->pRenderTarget->PopAxisAlignedClip();
		//--------------------------------------------------- 타일맵 클립핑 end ---------------------------------------------------
	}
}


void mapTool::selectTile(float scale)
{
	//-------------------------------------------------- 타일맵 클립핑 Start --------------------------------------------------
	D2DMANAGER->pRenderTarget->PushAxisAlignedClip(RectF(0, 0, _showWindowX, _showWindowY), D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	//-------------------------------------------------- 타일맵 클립핑 Start --------------------------------------------------


	//-------------------------------------------------- 타일맵 스케일 Start --------------------------------------------------
	Matrix3x2F matScale;
	matScale = Matrix3x2F::Scale(scale, scale, Point2F(0, 0));
	D2DMANAGER->pRenderTarget->SetTransform(matScale);
	//-------------------------------------------------- 타일맵 스케일 Start --------------------------------------------------


	for (int i = 0; i < _vTile.size(); ++i)
	{
		//예외처리
		if (_ptMouse.x > _showWindowX) break;  //우측
		if (_ptMouse.x < 0)			   break;  //좌측
		if (_ptMouse.y < 0)			   break;  //상부
		if (_ptMouse.y > _showWindowY) break;  //하부

		//타일렉트 보정
		RECT reRect;
		reRect.left   = (_vTile[i].rc.left	 + _moveX) * scale;
		reRect.top    = (_vTile[i].rc.top	 + _moveY) * scale;
		reRect.right  = (_vTile[i].rc.right  + _moveX) * scale;
		reRect.bottom = (_vTile[i].rc.bottom + _moveY) * scale;

		if (PtInRect(&reRect, _ptMouse))
		{
			//현재 타일위치 렉트 그리기
			D2DMANAGER->drawRectangle(D2DMANAGER->createBrush(RGB(0, 0, 255)),
				_vTile[i].rc.left   + _moveX,
				_vTile[i].rc.top    + _moveY,
				_vTile[i].rc.right  + _moveX,
				_vTile[i].rc.bottom + _moveY);

			//샘플타일 정보 -> 타일에 저장
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				//예외처리: 타일 정보가 없으면...통과!!
				if (_vSaveTr.size() == 0) continue;
				if (_drawTile.img == NULL) continue;

				//이미지가 타일사이즈보다 클 경우
				if (_drawTile.img->getFrameWidth() > TILE_SIZEX)
				{
					int tileStandardNum = i;  //지울 기준타일
					int tileNumX = _drawTile.img->getFrameWidth() / TILE_SIZEX;  //X축 타일갯수
					int tileNumY = _drawTile.img->getFrameHeight() / TILE_SIZEY; //Y축 타일갯수

					//=================================== 타일 Eraser =================================
					if (_btnOneEraser->getBtnOn())
					{
						//타일삭제
						for (int i = 0; i < tileNumY; ++i)
						{
							for (int j = 0; j < tileNumX; ++j)
							{
								btnTile1Eraser(_vSaveTr[(tileStandardNum + j) + (50 * i)]);
							}
						}
						break;
					}

					//========================== 샘플타일정보 -> 본타일 입력 ==========================	
					//타일 이미지 변경
					_vSaveTr[tileStandardNum].img = _drawTile.img;
					_vSaveTr[tileStandardNum].frameX = _drawTile.frameX;
					_vSaveTr[tileStandardNum].frameY = _drawTile.frameY;

					//타일속성 변경
					if (_btnA_move->getBtnOn() || _btnA_unMove->getBtnOn() || _btnA_ARender->getBtnOn())
					{
						tileReAtrribute(_vSaveTr[tileStandardNum]);
					}
					else
					{
						if (!_btnTileType->getBtnOn())
						{
							for (int i = 0; i < tileNumY; ++i)
							{
								for (int j = 0; j < tileNumX; ++j)
								{
									_vSaveTr[(tileStandardNum + j) + (50 * i)].attribute = _drawTile.attribute;
								}
							}
						}
					}

					//타일타입 변경
					if (_btnT_terrain->getBtnOn() || _btnT_building->getBtnOn() || _btnT_item->getBtnOn() ||
						_btnT_weapon->getBtnOn() || _btnT_enemy->getBtnOn())
					{
						tileReType(_vSaveTr[tileStandardNum]);
					}
					else
					{
						if (!_btnAttribute->getBtnOn())
						{
							for (int i = 0; i < tileNumY; ++i)
							{
								for (int j = 0; j < tileNumX; ++j)
								{
									_vSaveTr[(tileStandardNum + j) + (50 * i)].tileType = _drawTile.tileType;
								}
							}
						}
					}

				}
				else  //타일이 16 X 16일 경우
				{
					//=================================== 타일 Eraser =================================
					if (_btnOneEraser->getBtnOn())
					{
						btnTile1Eraser(_vSaveTr[i]);
						break;
					}

					//========================== 샘플타일정보 -> 본타일 입력 ==========================	
					//타일속성 변경
					if (_btnA_move->getBtnOn() || _btnA_unMove->getBtnOn() || _btnA_ARender->getBtnOn())
					{
						tileReAtrribute(_vSaveTr[i]);
					}
					else
					{
						if (!_btnTileType->getBtnOn())
						{
							_vSaveTr[i].attribute = _drawTile.attribute;
							_vSaveTr[i].img = _drawTile.img;
							_vSaveTr[i].frameX = _drawTile.frameX;
							_vSaveTr[i].frameY = _drawTile.frameY;
						}
					}

					//타일타입 변경
					if (_btnT_terrain->getBtnOn() || _btnT_building->getBtnOn() || _btnT_item->getBtnOn() ||
						_btnT_weapon->getBtnOn() || _btnT_enemy->getBtnOn())
					{
						tileReType(_vSaveTr[i]);
					}
					else
					{
						if (!_btnAttribute->getBtnOn())
						{
							_vSaveTr[i].tileType = _drawTile.tileType;
							_vSaveTr[i].img = _drawTile.img;
							_vSaveTr[i].frameX = _drawTile.frameX;
							_vSaveTr[i].frameY = _drawTile.frameY;
						}
					}
				}

			}
			break;
		}
	}

	//--------------------------------------------------- 타일맵 스케일 end ---------------------------------------------------
	D2DMANAGER->pRenderTarget->SetTransform(Matrix3x2F::Identity());
	//--------------------------------------------------- 타일맵 스케일 end ---------------------------------------------------


	//--------------------------------------------------- 타일맵 클립핑 end ---------------------------------------------------
	D2DMANAGER->pRenderTarget->PopAxisAlignedClip();
	//--------------------------------------------------- 타일맵 클립핑 end ---------------------------------------------------
}
