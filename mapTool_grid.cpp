#include "stdafx.h"
#include "mapTool.h"


void mapTool::gridRender(float scale)
{
	//cameraOutLine
	D2DMANAGER->drawRectangle(D2DMANAGER->defaultBrush, 0, 0, _showWindowX, _showWindowY);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{

		//-------------------------------------------------- Ÿ�ϸ� Ŭ���� Start --------------------------------------------------
		D2DMANAGER->pRenderTarget->PushAxisAlignedClip(RectF(0, 0, _showWindowX, _showWindowY), D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
		//-------------------------------------------------- Ÿ�ϸ� Ŭ���� Start --------------------------------------------------


		//-------------------------------------------------- Ÿ�ϸ� ������ Start --------------------------------------------------
		Matrix3x2F matScale;
		matScale = Matrix3x2F::Scale(scale, scale, Point2F(0, 0));
		D2DMANAGER->pRenderTarget->SetTransform(matScale);
		//-------------------------------------------------- Ÿ�ϸ� ������ Start --------------------------------------------------


		for (int i = 0; i < _vTile.size(); ++i)
		{
			//����ó��: ȭ��� ����X
			if (_vTile[i].rc.left   + _moveX >= _showWindowX / scale)  continue;  //���ο�(����)
			if (_vTile[i].rc.right  + _moveX < 0)					   continue;  //���ο�(����)
			if (_vTile[i].rc.top    + _moveY >= _showWindowY / scale)  continue;  //���ο�(���)
			if (_vTile[i].rc.bottom + _moveY < 0)					   continue;  //���ο�(�Ϻ�)

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
				//����ó��: ȭ��� ����X
				if ((j * TILE_SIZEX) + _moveX >= _showWindowX / scale) continue;  //���ο�(����)
				if ((j * TILE_SIZEX) + _moveX < 0)					   continue;	 //���ο�(����)
				if ((i * TILE_SIZEY) + _moveY >= _showWindowY / scale) continue;  //���ο�(����)
				if ((i * TILE_SIZEY) + _moveY < 0)					   continue;  //���ο�(����)

				WCHAR strIndex[128];
				ZeroMemory(&strIndex, sizeof(strIndex));
				swprintf(strIndex, L"%d", (TILEX * i) + j);

				D2DMANAGER->drawTextDwd(D2DMANAGER->createBrush(RGB(0, 0, 255), 0.3f), L"�������", 3, strIndex,
					(j * TILE_SIZEX) + _moveX, (i * TILE_SIZEY) + _moveY,
					(j * TILE_SIZEX) + 30 + _moveX, (i * TILE_SIZEY) + 30 + _moveY);
			}
		}

		//�Ӽ� �׸���(Ellipse)
		for (int i = 0; i < TILEY; ++i)
		{
			for (int j = 0; j < TILEX; ++j)
			{
				if (_vSaveTr[(TILEX * i) + j].attribute == ATTR_NONE)  continue;  //�Ӽ��� ������...

				//��ġ����
				float rcWidth = _vTile[(TILEX * i) + j].rc.right - _vTile[(TILEX * i) + j].rc.left;
				float rcHeight = _vTile[(TILEX * i) + j].rc.bottom - _vTile[(TILEX * i) + j].rc.top;
				float centerX = _vTile[(TILEX * i) + j].rc.left + (rcWidth / 2);
				float centerY = _vTile[(TILEX * i) + j].rc.top + (rcHeight / 2);
				float ellipseSize = 3;
				float startX = centerX - (ellipseSize / 2);
				float startY = centerY - (ellipseSize / 2);
				float endX = centerX + (ellipseSize / 2);
				float endY = centerY + (ellipseSize / 2);


				//����ó��: ȭ��� ����X
				if ((j * TILE_SIZEX) + _moveX >= _showWindowX / scale) continue;  //���ο�(����)
				if ((j * TILE_SIZEX) + _moveX < 0)					   continue;  //���ο�(����)
				if ((i * TILE_SIZEY) + _moveY >= _showWindowY / scale) continue;  //���ο�(����)
				if ((i * TILE_SIZEY) + _moveY < 0)					   continue;  //���ο�(����)
	

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


		//Ÿ�� �׸���(Ellipse)
		for (int i = 0; i < TILEY; ++i)
		{
			for (int j = 0; j < TILEX; ++j)
			{
				if (_vSaveTr[(TILEX * i) + j].tileType == TYPE_NONE)   continue;  //Ÿ���� ������...

				//��ġ����
				float rcWidth = _vTile[(TILEX * i) + j].rc.right - _vTile[(TILEX * i) + j].rc.left;
				float rcHeight = _vTile[(TILEX * i) + j].rc.bottom - _vTile[(TILEX * i) + j].rc.top;
				float centerX = _vTile[(TILEX * i) + j].rc.left + (rcWidth / 2);
				float centerY = _vTile[(TILEX * i) + j].rc.top + (rcHeight / 2);
				float ellipseSize = 5;
				float startX = centerX - (ellipseSize / 2);
				float startY = centerY - (ellipseSize / 2);
				float endX = centerX + (ellipseSize / 2);
				float endY = centerY + (ellipseSize / 2);


				//����ó��: ȭ��� ����X
				if ((j * TILE_SIZEX) + _moveX >= _showWindowX / scale) continue;  //���ο�(����)
				if ((j * TILE_SIZEX) + _moveX < 0)					   continue;  //���ο�(����)
				if ((i * TILE_SIZEY) + _moveY >= _showWindowY / scale) continue;  //���ο�(����)
				if ((i * TILE_SIZEY) + _moveY < 0)					   continue;  //���ο�(����)


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


		//--------------------------------------------------- Ÿ�ϸ� ������ end ---------------------------------------------------
		D2DMANAGER->pRenderTarget->SetTransform(Matrix3x2F::Identity());
		//--------------------------------------------------- Ÿ�ϸ� ������ end ---------------------------------------------------


		//--------------------------------------------------- Ÿ�ϸ� Ŭ���� end ---------------------------------------------------
		D2DMANAGER->pRenderTarget->PopAxisAlignedClip();
		//--------------------------------------------------- Ÿ�ϸ� Ŭ���� end ---------------------------------------------------
	}
}


void mapTool::selectTile(float scale)
{
	//-------------------------------------------------- Ÿ�ϸ� Ŭ���� Start --------------------------------------------------
	D2DMANAGER->pRenderTarget->PushAxisAlignedClip(RectF(0, 0, _showWindowX, _showWindowY), D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	//-------------------------------------------------- Ÿ�ϸ� Ŭ���� Start --------------------------------------------------


	//-------------------------------------------------- Ÿ�ϸ� ������ Start --------------------------------------------------
	Matrix3x2F matScale;
	matScale = Matrix3x2F::Scale(scale, scale, Point2F(0, 0));
	D2DMANAGER->pRenderTarget->SetTransform(matScale);
	//-------------------------------------------------- Ÿ�ϸ� ������ Start --------------------------------------------------


	for (int i = 0; i < _vTile.size(); ++i)
	{
		//����ó��
		if (_ptMouse.x > _showWindowX) break;  //����
		if (_ptMouse.x < 0)			   break;  //����
		if (_ptMouse.y < 0)			   break;  //���
		if (_ptMouse.y > _showWindowY) break;  //�Ϻ�

		//Ÿ�Ϸ�Ʈ ����
		RECT reRect;
		reRect.left   = (_vTile[i].rc.left	 + _moveX) * scale;
		reRect.top    = (_vTile[i].rc.top	 + _moveY) * scale;
		reRect.right  = (_vTile[i].rc.right  + _moveX) * scale;
		reRect.bottom = (_vTile[i].rc.bottom + _moveY) * scale;

		if (PtInRect(&reRect, _ptMouse))
		{
			//���� Ÿ����ġ ��Ʈ �׸���
			D2DMANAGER->drawRectangle(D2DMANAGER->createBrush(RGB(0, 0, 255)),
				_vTile[i].rc.left   + _moveX,
				_vTile[i].rc.top    + _moveY,
				_vTile[i].rc.right  + _moveX,
				_vTile[i].rc.bottom + _moveY);

			//����Ÿ�� ���� -> Ÿ�Ͽ� ����
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				//����ó��: Ÿ�� ������ ������...���!!
				if (_vSaveTr.size() == 0 && _vSaveBd.size() == 0) continue;
				if (_drawTile.img == NULL) continue;

				//=================================== Ÿ�� Ÿ�Ժ� ���� ===================================
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

								//Ÿ�� �ε�����ȣ -> ���ͳѹ�
								for (int i = 0; i < _vSaveBd.size(); ++i)
								{
									if (tmpSelectIndex == _vSaveBd[i].index) tmpIndex = i;
									break;
								}

								//�����
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

				//=================================== Ÿ�� Ÿ�Ժ� ���� ===================================
				//����Ÿ������->��Ÿ�� �Է�

				//------------------------------------ Ÿ�� �Ӽ� ���� ------------------------------------
				if (_btnA_move->getBtnOn() || _btnA_unMove->getBtnOn() || _btnA_ARender->getBtnOn())  //�Ӽ����� ��ư�� ��������...
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
				else  //Ÿ���� ���� �׸��ٸ�...
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
			
			

				//------------------------------------ Ÿ�� Ÿ�� ���� ------------------------------------
				if (_btnT_terrain->getBtnOn() || _btnT_building->getBtnOn() || _btnT_item->getBtnOn() ||
					_btnT_weapon->getBtnOn() || _btnT_enemy->getBtnOn())    //Ÿ�Ժ��� ��ư�� ��������...
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
				else  //Ÿ���� ���� �׸��ٸ�...
				{
					//����ó��: ������ �ԷµǾ�����... ���
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



	//--------------------------------------------------- Ÿ�ϸ� ������ end ---------------------------------------------------
	D2DMANAGER->pRenderTarget->SetTransform(Matrix3x2F::Identity());
	//--------------------------------------------------- Ÿ�ϸ� ������ end ---------------------------------------------------


	//--------------------------------------------------- Ÿ�ϸ� Ŭ���� end ---------------------------------------------------
	D2DMANAGER->pRenderTarget->PopAxisAlignedClip();
	//--------------------------------------------------- Ÿ�ϸ� Ŭ���� end ---------------------------------------------------
}


void mapTool::saveTileVectorBd()
{
	if (_isSaveVector)
	{
		//Ÿ������ ��������
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



		//���Ϳ� ���
		_vSaveBd.push_back(tmpTile);
	}

	_isSaveVector = false;
}