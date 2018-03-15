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
				if (_vSaveTr.size() == 0 && _vSaveBd.size() == 0) continue;
				if (_drawTile.img == NULL) continue;

				//=================================== 타일 타입별 삭제 ===================================
				if (_btnOneEraser->getBtnOn())
				{
					switch (_drawTile.tileType)
					{
						case TYPE_TERRAIN:
							if (_btnOneEraser->getBtnOn())
							{
								btnTile1Eraser(_vSaveTr[i]);
								break;
							}
						break;
						case TYPE_BUILDING:
							if (_btnOneEraser->getBtnOn())
							{
								int tmpIndex = 0;
								int tmpSelectIndex = i;

								//타일 인덱스번호 -> 벡터넘버
								for (int i = 0; i < _vSaveBd.size(); ++i)
								{
									if (tmpSelectIndex == _vSaveBd[i].index) tmpIndex = i;
									break;
								}

								//지우기
								btnTile1Eraser(_vSaveBd[tmpIndex]);
								break;
							}
						break;
						case TYPE_ITEM:

						break;
						case TYPE_WEAPON:

						break;
						case TYPE_ENEMY:

						break;
					}
				}
				//========================================================================================

				//=================================== 타일 타입별 저장 ===================================
				//샘플타일정보->본타일 입력

				//------------------------------------ 타일 속성 변경 ------------------------------------
				if (_btnA_move->getBtnOn() || _btnA_unMove->getBtnOn() || _btnA_ARender->getBtnOn())  //속성변경 버튼을 눌렀으면...
				{
					switch (_drawTile.tileType)
					{
						case TYPE_TERRAIN:
							tileReAtrribute(_vSaveTr[i]);
						break;
						case TYPE_BUILDING:
							tileReAtrribute(_vSaveBd[i]);
						break;
						case TYPE_ITEM:

						break;
						case TYPE_WEAPON:

						break;
						case TYPE_ENEMY:

						break;
					}
				}
				else  //타일을 새로 그린다면...
				{
					if (!_btnTileType->getBtnOn())
					{
						switch (_drawTile.tileType)
						{
							case TYPE_TERRAIN:
								_vSaveTr[i].img    = _drawTile.img;
								sprintf(_vSaveTr[i].imgName, "%s", _drawTile.imgName);
								_vSaveTr[i].frameX = _drawTile.frameX;
								_vSaveTr[i].frameY = _drawTile.frameY;
								_vSaveTr[i].attribute = _drawTile.attribute;
								_vSaveTr[i].tileType = _drawTile.tileType;
							break;
							case TYPE_BUILDING:

								_isSaveVector = true;
								tmpSaveTileBd.rc = _vSaveTr[i].rc;
								tmpSaveTileBd.index = i;

							break;
							case TYPE_ITEM:

							break;
							case TYPE_WEAPON:

							break;
							case TYPE_ENEMY:
	
							break;
						}
					}
				}
			
			

				//------------------------------------ 타일 타입 변경 ------------------------------------
				if (_btnT_terrain->getBtnOn() || _btnT_building->getBtnOn() || _btnT_item->getBtnOn() ||
					_btnT_weapon->getBtnOn() || _btnT_enemy->getBtnOn())    //타입변경 버튼을 눌렀으면...
				{
					switch (_drawTile.tileType)
					{
						case TYPE_TERRAIN:
							tileReType(_vSaveTr[i]);
						break;
						case TYPE_BUILDING:
							tileReType(_vSaveBd[i]);
						break;
						case TYPE_ITEM:

						break;
						case TYPE_WEAPON:

						break;
						case TYPE_ENEMY:

						break;
					}
				
				}
				else  //타일을 새로 그린다면...
				{
					//예외처리: 위에서 입력되었으면... 통과
					if (!_btnTileType->getBtnOn()) break;

					if (!_btnAttribute->getBtnOn())
					{
						switch (_drawTile.tileType)
						{
							case TYPE_TERRAIN:
								_vSaveTr[i].tileType = _drawTile.tileType;

								_vSaveTr[i].index = _drawTile.index;
								_vSaveTr[i].img    = _drawTile.img;
								sprintf(_vSaveTr[i].imgName, "%s", _drawTile.imgName);
								_vSaveTr[i].frameX = _drawTile.frameX;
								_vSaveTr[i].frameY = _drawTile.frameY;
							break;
							case TYPE_BUILDING:

								_isSaveVector = true;
								tmpSaveTileBd.rc = _vSaveTr[i].rc;
								tmpSaveTileBd.index = i;

							break;
							case TYPE_ITEM:

							break;
							case TYPE_WEAPON:

							break;
							case TYPE_ENEMY:

							break;
						}

					}
				}
			}
			break;
		}

	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		saveTileVectorBd();
	}



	//--------------------------------------------------- 타일맵 스케일 end ---------------------------------------------------
	D2DMANAGER->pRenderTarget->SetTransform(Matrix3x2F::Identity());
	//--------------------------------------------------- 타일맵 스케일 end ---------------------------------------------------


	//--------------------------------------------------- 타일맵 클립핑 end ---------------------------------------------------
	D2DMANAGER->pRenderTarget->PopAxisAlignedClip();
	//--------------------------------------------------- 타일맵 클립핑 end ---------------------------------------------------
}


void mapTool::saveTileVectorBd()
{
	if (_isSaveVector)
	{
		//타일정보 가져오기
		tagTile tmpTile;
		ZeroMemory(&tmpTile, sizeof(tagTile));
		tmpTile.index     = tmpSaveTileBd.index;
		tmpTile.img       = _drawTile.img;
		sprintf(tmpTile.imgName, "%s", _drawTile.imgName);
		tmpTile.attribute = _drawTile.attribute;
		tmpTile.tileType  = _drawTile.tileType;
		tmpTile.frameX    = _drawTile.frameX;
		tmpTile.frameY    = _drawTile.frameY;
		tmpTile.rc.left   = tmpSaveTileBd.rc.left;
		tmpTile.rc.top	  = tmpSaveTileBd.rc.top;
		tmpTile.rc.right  = tmpSaveTileBd.rc.left + tmpTile.img->getFrameWidth();
		tmpTile.rc.bottom = tmpSaveTileBd.rc.top + tmpTile.img->getFrameHeight();



		//벡터에 담기
		_vSaveBd.push_back(tmpTile);
	}

	_isSaveVector = false;
}