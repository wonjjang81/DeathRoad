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

			D2DMANAGER->drawRectangle(D2DMANAGER->createBrush(RGB(0, 255, 0), 0.3f),
				_vTile[i].rc.left + _moveX,
				_vTile[i].rc.top + _moveY,
				_vTile[i].rc.right + _moveX,
				_vTile[i].rc.bottom + _moveY, 0.3f);
		}


		//index
		//for (int i = 0; i < _tileY; ++i)
		//{
		//	for (int j = 0; j < _tileX; ++j)
		//	{
		//		//����ó��: ȭ��� ����X
		//		if ((j * TILE_SIZEX) + _moveX >= _showWindowX / scale) continue;  //���ο�(����)
		//		if ((j * TILE_SIZEX) + _moveX < 0)					   continue;	 //���ο�(����)
		//		if ((i * TILE_SIZEY) + _moveY >= _showWindowY / scale) continue;  //���ο�(����)
		//		if ((i * TILE_SIZEY) + _moveY < 0)					   continue;  //���ο�(����)

		//		WCHAR strIndex[128];
		//		ZeroMemory(&strIndex, sizeof(strIndex));
		//		swprintf(strIndex, L"%d", (_tileX * i) + j);

		//		D2DMANAGER->drawTextDwd(D2DMANAGER->createBrush(RGB(0, 0, 255), 0.3f), L"�������", 3, strIndex,
		//			(j * TILE_SIZEX) + _moveX, (i * TILE_SIZEY) + _moveY,
		//			(j * TILE_SIZEX) + 30 + _moveX, (i * TILE_SIZEY) + 30 + _moveY);
		//	}
		//}

		//�Ӽ� �׸���(Ellipse)
		for (int i = 0; i < _tileY; ++i)
		{
			for (int j = 0; j < _tileX; ++j)
			{
				if (_vSaveTr[(_tileX * i) + j].attribute == ATTR_CRECT_NONE)  continue;  //�Ӽ��� ������...
		

				//��ġ����
				float rcWidth = _vTile[(_tileX * i) + j].rc.right - _vTile[(_tileX * i) + j].rc.left;
				float rcHeight = _vTile[(_tileX * i) + j].rc.bottom - _vTile[(_tileX * i) + j].rc.top;
				float centerX = _vTile[(_tileX * i) + j].rc.left + (rcWidth / 2);
				float centerY = _vTile[(_tileX * i) + j].rc.top + (rcHeight / 2);
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
	

				switch (_vSaveTr[(_tileX * i) + j].attribute)
				{
					case ATTR_CRECT_NONE:
						D2DMANAGER->drawEllipse(D2DMANAGER->createBrush(RGB(255, 0, 0)), startX + _moveX, startY + _moveY, endX + _moveX, endY + _moveY, 0.5f);
					break;
					case ATTR_CRECT_CENTER:
						D2DMANAGER->drawEllipse(D2DMANAGER->createBrush(RGB(0, 255, 0)), startX + _moveX, startY + _moveY, endX + _moveX, endY + _moveY, 0.5f);
					break;
					case ATTR_CRECT_ORIGINAL:
						D2DMANAGER->drawEllipse(D2DMANAGER->createBrush(RGB(0, 0, 255)), startX + _moveX, startY + _moveY, endX + _moveX, endY + _moveY, 0.5f);
					break;
					case ATTR_CRECT_RESIZE:
						D2DMANAGER->drawEllipse(D2DMANAGER->createBrush(RGB(0, 255, 255)), startX + _moveX, startY + _moveY, endX + _moveX, endY + _moveY, 0.5f);
					break;
				}
			}
		}

		//�Ӽ� �׸���: ��
		attrDraw(_vSaveWl);
		typeAttrDraw(_vSaveWl);
		typeAttrDraw(_vSaveArWl);
		//�Ӽ� �׸���: ��
		attrDraw(_vSaveDr);
		typeAttrDraw(_vSaveDr);
		//�Ӽ� �׸���: ����
		attrDraw(_vSaveFt);
		typeAttrDraw(_vSaveFt);
		//�Ӽ� �׸���: ������
		attrDraw(_vSaveIt);
		typeAttrDraw(_vSaveIt);
		//�Ӽ� �׸���: ����
		attrDraw(_vSaveWp);
		typeAttrDraw(_vSaveWp);




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

	if (!_btnOneEraser->getBtnOn())
	{
		_tmpSelectIndex = -1;
	}


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
				_vTile[i].rc.bottom + _moveY, 0.5f);

			//����Ÿ�� ���� -> Ÿ�Ͽ� ����
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				//����ó��: Ÿ�� ������ ������...���!!
				if (_vSaveTr.size() == 0) continue;


				//=================================== Ÿ�� Ÿ�Ժ� ���� ===================================
				if (_btnOneEraser->getBtnOn())
				{
					switch (_drawTile.tileType)
					{
						case TYPE_TERRAIN:

							btnTile1Eraser(_vSaveTr[i]);

						break;
						case TYPE_BUILDING: case TYPE_ROAD: case TYPE_FURNITURE: case TYPE_ITEM:
						case TYPE_WEAPON: case TYPE_ENEMY: case TYPE_WALL: case TYPE_DOOR:

							_tmpSelectIndex = i;

						break;
					}
				}
				//========================================================================================

				//=================================== Ÿ�� Ÿ�Ժ� ���� ===================================
				//����Ÿ������->��Ÿ�� �Է�

				//------------------------------------ Ÿ�� �Ӽ� ���� ------------------------------------
				if (_btnA_move->getBtnOn() || _btnA_unMove->getBtnOn() || _btnA_ARender->getBtnOn())  //�Ӽ����� ��ư�� ��������...
				{
					//Ÿ�� Index
					int getIndex = -1;
					
					//Ÿ��Ÿ�� ����
					//if (_drawTile.tileType == TYPE_NONE)
					//{
					//	switch (_menuTab.menuType)
					//	{
					//		case MENU_TERRAIN:
					//			_drawTile.tileType = TYPE_TERRAIN;
					//		break;
					//		case MENU_BULIDING:
					//			_drawTile.tileType = TYPE_BUILDING;
					//		break;
					//		default:
					//			_drawTile.tileType = TYPE_NONE;
					//		break;
					//	}
					//}

					switch (_drawTile.tileType)
					{
						case TYPE_TERRAIN:
							tileReAtrribute(_vSaveTr[i]);
						break;
						case TYPE_BUILDING:
							//Ÿ�� �ε�����ȣ -> ���ͳѹ�
							getIndex = getTileIndex(_vSaveBd, i);
							if (getIndex < 0) break;

							tileReAtrribute(_vSaveBd[getIndex]);
						break;
						case TYPE_ROAD:
							//Ÿ�� �ε�����ȣ -> ���ͳѹ�
							getIndex = getTileIndex(_vSaveRd, i);
							if (getIndex < 0) break;

							tileReAtrribute(_vSaveRd[getIndex]);
						break;
						case TYPE_FURNITURE:
							//Ÿ�� �ε�����ȣ -> ���ͳѹ�
							getIndex = getTileIndex(_vSaveFt, i);
							if (getIndex < 0) break;

							tileReAtrribute(_vSaveFt[getIndex]);
						break;
						case TYPE_ITEM:
							//Ÿ�� �ε�����ȣ -> ���ͳѹ�
							getIndex = getTileIndex(_vSaveIt, i);
							if (getIndex < 0) break;

							tileReAtrribute(_vSaveIt[getIndex]);
						break;
						case TYPE_WEAPON:
							//Ÿ�� �ε�����ȣ -> ���ͳѹ�
							getIndex = getTileIndex(_vSaveWp, i);
							if (getIndex < 0) break;

							tileReAtrribute(_vSaveWp[getIndex]);
						break;
						case TYPE_ENEMY:
							//Ÿ�� �ε�����ȣ -> ���ͳѹ�
							getIndex = getTileIndex(_vSaveEm, i);
							if (getIndex < 0) break;

							tileReAtrribute(_vSaveEm[getIndex]);
						break;
						case TYPE_WALL:
							//Ÿ�� �ε�����ȣ -> ���ͳѹ�
							getIndex = getTileIndex(_vSaveWl, i);
							if (getIndex < 0) break;

							tileReAtrribute(_vSaveWl[getIndex]);
						break;
						case TYPE_DOOR:
							//Ÿ�� �ε�����ȣ -> ���ͳѹ�
							getIndex = getTileIndex(_vSaveDr, i);
							if (getIndex < 0) break;

							tileReAtrribute(_vSaveDr[getIndex]);
						break;
					}
				}
				else  //Ÿ���� ���� �׸��ٸ�...
				{
					if (!_btnAttribute->getBtnOn())
					{
						switch (_drawTile.tileType)
						{
							case TYPE_TERRAIN:
								_vSaveTr[i].tileType = _drawTile.tileType;
								_vSaveTr[i].attribute = _drawTile.attribute;
								_vSaveTr[i].typeAtt = _drawTile.typeAtt;
								_vSaveTr[i].typeAtt2 = _drawTile.typeAtt2;

								_vSaveTr[i].index = _drawTile.index;
								_vSaveTr[i].img = _drawTile.img;
								sprintf(_vSaveTr[i].imgName, "%s", _drawTile.imgName);
								_vSaveTr[i].frameX = _drawTile.frameX;
								_vSaveTr[i].frameY = _drawTile.frameY;
								_vSaveTr[i].id = _drawTile.id;
							break;
							case TYPE_BUILDING: case TYPE_ROAD: case TYPE_FURNITURE: case TYPE_ITEM:
							case TYPE_WEAPON: case TYPE_ENEMY: case TYPE_WALL: case TYPE_DOOR:

								_isSaveVector = true;
								_tmpSaveTile.rc = _vTile[i].rc;
								_tmpSaveTile.index = i;

							break;
						}
					}
				}
	

				//------------------------------------ Ÿ�� Ÿ�� ���� ------------------------------------
				if (_btnT_terrain->getBtnOn() || _btnT_building->getBtnOn() || _btnT_item->getBtnOn() ||
					_btnT_weapon->getBtnOn() || _btnT_enemy->getBtnOn())    //Ÿ�Ժ��� ��ư�� ��������...
				{
					int getIndex = -1;

					switch (_drawTile.tileType)
					{
						case TYPE_TERRAIN:
							tileReType(_vSaveTr[i]);
						break;
						case TYPE_BUILDING:
							//Ÿ�� �ε�����ȣ -> ���ͳѹ�
							getIndex = getTileIndex(_vSaveBd, i);
							if (getIndex < 0) break;

							tileReType(_vSaveBd[getIndex]);
						break;
						case TYPE_ROAD:
							//Ÿ�� �ε�����ȣ -> ���ͳѹ�
							getIndex = getTileIndex(_vSaveRd, i);
							if (getIndex < 0) break;

							tileReType(_vSaveRd[getIndex]);
						break;
						case TYPE_FURNITURE:
							//Ÿ�� �ε�����ȣ -> ���ͳѹ�
							getIndex = getTileIndex(_vSaveFt, i);
							if (getIndex < 0) break;

							tileReType(_vSaveFt[getIndex]);
						break;
						case TYPE_ITEM:
							//Ÿ�� �ε�����ȣ -> ���ͳѹ�
							getIndex = getTileIndex(_vSaveIt, i);
							if (getIndex < 0) break;

							tileReType(_vSaveIt[getIndex]);
						break;
						case TYPE_WEAPON:
							//Ÿ�� �ε�����ȣ -> ���ͳѹ�
							getIndex = getTileIndex(_vSaveWp, i);
							if (getIndex < 0) break;

							tileReType(_vSaveWp[getIndex]);
						break;
						case TYPE_ENEMY:
							//Ÿ�� �ε�����ȣ -> ���ͳѹ�
							getIndex = getTileIndex(_vSaveEm, i);
							if (getIndex < 0) break;

							tileReType(_vSaveEm[getIndex]);
						break;
						case TYPE_WALL:
							//Ÿ�� �ε�����ȣ -> ���ͳѹ�
							getIndex = getTileIndex(_vSaveWl, i);
							if (getIndex < 0) break;

							tileReType(_vSaveWl[getIndex]);
						break;
						case TYPE_DOOR:
							//Ÿ�� �ε�����ȣ -> ���ͳѹ�
							getIndex = getTileIndex(_vSaveDr, i);
							if (getIndex < 0) break;

							tileReType(_vSaveDr[getIndex]);
						break;
					}
				}
			}


			if (!_btnAttribute->getBtnOn())
			{
				if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
				{
					switch (_drawTile.tileType)
					{
						case TYPE_BUILDING:
							if (_btnOneEraser->getBtnOn() && (_tmpSelectIndex >= 0))
							{
								setTile1Eraser(_vSaveBd, _tmpSelectIndex);
								_tmpSelectIndex = -1;
							}
							else
							{
								saveTileVector(_vSaveBd);  //����
							}
						break;
						case TYPE_ROAD:
							if (_btnOneEraser->getBtnOn() && (_tmpSelectIndex >= 0))
							{
								setTile1Eraser(_vSaveBd, _tmpSelectIndex);
								_tmpSelectIndex = -1;
							}
							else
							{
								saveTileVector(_vSaveRd);  //����
							}
						break;
						case TYPE_FURNITURE:
							if (_btnOneEraser->getBtnOn() && (_tmpSelectIndex >= 0))
							{
								setTile1Eraser(_vSaveFt, _tmpSelectIndex);
								_tmpSelectIndex = -1;
							}
							else
							{
								saveTileVector(_vSaveFt);  //����
							}
						break;
						case TYPE_ITEM:
							if (_btnOneEraser->getBtnOn() && (_tmpSelectIndex >= 0))
							{
								setTile1Eraser(_vSaveIt, _tmpSelectIndex);
								_tmpSelectIndex = -1;
							}
							else
							{
								saveTileVector(_vSaveIt);  //������
							}
						break;
						case TYPE_WEAPON:
							if (_btnOneEraser->getBtnOn() && (_tmpSelectIndex >= 0))
							{
								setTile1Eraser(_vSaveWp, _tmpSelectIndex);
								_tmpSelectIndex = -1;
							}
							else
							{
								saveTileVector(_vSaveWp);  //����
							}
						break;
						case TYPE_ENEMY:
							if (_btnOneEraser->getBtnOn() && (_tmpSelectIndex >= 0))
							{
								setTile1Eraser(_vSaveEm, _tmpSelectIndex);
								_tmpSelectIndex = -1;
							}
							else
							{
								saveTileVector(_vSaveEm);  //��
							}
						break;
						case TYPE_WALL:
							if (_btnOneEraser->getBtnOn() && (_tmpSelectIndex >= 0))
							{
								setTile1Eraser(_vSaveWl, _tmpSelectIndex);
								_tmpSelectIndex = -1;
							}
							else
							{
								if (_drawTile.typeAtt2 == TYPE_A_WL_ARENDER)
								{
									saveTileVector(_vSaveArWl);  //After���� ��
								}
								else
								{
									saveTileVector(_vSaveWl);  //��
								}						
							}
						break;
						case TYPE_DOOR:
							if (_btnOneEraser->getBtnOn() && (_tmpSelectIndex >= 0))
							{
								setTile1Eraser(_vSaveDr, _tmpSelectIndex);
								_tmpSelectIndex = -1;
							}
							else
							{
								saveTileVector(_vSaveDr);  //��
							}
						break;
					}
				}

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


//������ Ÿ������ ���Ϳ� ��� [����]
void mapTool::saveTileVector(vSaveTile& tileVector)
{
	if (_isSaveVector)
	{
		//������ ��ġ�� Ÿ���� �ֽ��ϱ�?
		bool indexSame = false;
		int  tmpIndex = -1;
		for (int i = 0; i < tileVector.size(); ++i)
		{
			if (tileVector[i].index == _tmpSaveTile.index)
			{
				indexSame = true;
				tmpIndex = i;
				break;
			}
		}

		//����ó��
		if (indexSame && tileVector[tmpIndex].id == _drawTile.id) return;  //�ߺ�ó��
		if (_btnEraser->getBtnOn())    return;
		if (_btnOneEraser->getBtnOn()) return;
		if (_btnTileType->getBtnOn())  return;
		if (_btnAttribute->getBtnOn()) return;

		//Ÿ������ ��������
		tagTile tmpTile;
		ZeroMemory(&tmpTile, sizeof(tagTile));
		tmpTile.index     = _tmpSaveTile.index;
		tmpTile.img       = _drawTile.img;
		sprintf(tmpTile.imgName, "%s", _drawTile.imgName);
		tmpTile.attribute = _drawTile.attribute;
		tmpTile.typeAtt	  = _drawTile.typeAtt;
		tmpTile.typeAtt2  = _drawTile.typeAtt2;
		tmpTile.tileType  = _drawTile.tileType;
		tmpTile.frameX    = _drawTile.frameX;
		tmpTile.frameY    = _drawTile.frameY;
		tmpTile.rc.left   = _tmpSaveTile.rc.left;
		tmpTile.rc.top	  = _tmpSaveTile.rc.top;
		tmpTile.rc.right  = _tmpSaveTile.rc.right;
		tmpTile.rc.bottom = _tmpSaveTile.rc.bottom;
		tmpTile.centerX   = _drawTile.centerX;
		tmpTile.centerY   = _drawTile.centerY;
		tmpTile.id		  = _drawTile.id;
		tmpTile.overPos   = _drawTile.overPos;

		if (indexSame)
		{
			switch (tileVector[tmpIndex].overPos)
			{
				case OVERPO_NO:
					//������ġ �ߺ� X (SWAP)
					tileVector[tmpIndex] = tmpTile;
				break;
				case OVERPO_YES:
					//������ġ �ߺ� O
					//���Ϳ� ���
					tileVector.push_back(tmpTile);
				break;
			}
		}
		else
		{
			//���Ϳ� ���
			tileVector.push_back(tmpTile);
		}

	}

	//�ʱ�ȭ
	ZeroMemory(&_tmpSaveTile, sizeof(tagTile));
	_isSaveVector = false;
}

//Ÿ������ ����� ����
void mapTool::setTile1Eraser(vSaveTile& eraseTile, int tsIndex)
{
	//����ó��
	if (eraseTile.size() == 0) return;

	int tmpIndex = -1;

	//Ÿ�� �ε�����ȣ -> ���ͳѹ�
	tmpIndex = getTileIndex(eraseTile, tsIndex);

	if (tmpIndex < 0) return;
	//=============== ����� ===============
	//���� �����
	btnTile1Eraser(eraseTile[tmpIndex]);
	//���� ����
	eraseTile.erase(eraseTile.begin() + tmpIndex);
	//=============== ����� ===============
}


//Ÿ�� �ε�����ȣ -> ���ͳѹ�
int mapTool::getTileIndex(vSaveTile& vTile, int tsIndex)
{
	for (int j = 0; j < vTile.size(); ++j)
	{
		if (tsIndex == vTile[j].index)
		{
			return j;
		}
	}

	return -1;
}

//�Ӽ� �׸���
void mapTool::attrDraw(vSaveTile tileVector)
{
	//�Ӽ� �׸���(Ellipse)
	for (int i = 0; i < tileVector.size(); ++i)
	{
		if (tileVector[i].attribute == ATTR_CRECT_NONE)  continue;  //�Ӽ��� ������...

		//��ġ����
		float rcWidth	  = tileVector[i].rc.right - tileVector[i].rc.left;
		float rcHeight	  = tileVector[i].rc.bottom - tileVector[i].rc.top;
		float centerX	  = tileVector[i].rc.left + (rcWidth / 2);
		float centerY	  = tileVector[i].rc.top + (rcHeight / 2);
		float ellipseSize = 7;
		float startX      = centerX - (ellipseSize / 2);
		float startY      = centerY - (ellipseSize / 2);
		float endX        = centerX + (ellipseSize / 2);
		float endY        = centerY + (ellipseSize / 2);


		//����ó��: ȭ��� ����X
		//if ((j * TILE_SIZEX) + _moveX >= _showWindowX / scale) continue;  //���ο�(����)
		//if ((j * TILE_SIZEX) + _moveX < 0)					   continue;  //���ο�(����)
		//if ((i * TILE_SIZEY) + _moveY >= _showWindowY / scale) continue;  //���ο�(����)
		//if ((i * TILE_SIZEY) + _moveY < 0)					   continue;  //���ο�(����)


		switch (tileVector[i].attribute)
		{
			case ATTR_CRECT_NONE:
				D2DMANAGER->drawEllipse(D2DMANAGER->createBrush(RGB(255, 0, 0)), startX + _moveX, startY + _moveY, endX + _moveX, endY + _moveY, 0.5f);
			break;
			case ATTR_CRECT_CENTER:
				D2DMANAGER->drawEllipse(D2DMANAGER->createBrush(RGB(0, 255, 0)), startX + _moveX, startY + _moveY, endX + _moveX, endY + _moveY, 0.5f);
			break;
			case ATTR_CRECT_ORIGINAL:
				D2DMANAGER->drawEllipse(D2DMANAGER->createBrush(RGB(0, 0, 255)), startX + _moveX, startY + _moveY, endX + _moveX, endY + _moveY, 0.5f);
			break;
			case ATTR_CRECT_RESIZE:
				D2DMANAGER->drawEllipse(D2DMANAGER->createBrush(RGB(0, 255, 255)), startX + _moveX, startY + _moveY, endX + _moveX, endY + _moveY, 0.5f);
			break;
		}
	}
}


//Ÿ�ԼӼ� �׸���
void mapTool::typeAttrDraw(vSaveTile tileVector)
{
	//�Ӽ� �׸���(Ellipse)
	for (int i = 0; i < tileVector.size(); ++i)
	{
		if (tileVector[i].typeAtt == TYPE_A_NONE && tileVector[i].typeAtt2 == TYPE_A_NONE)  continue;  //�Ӽ��� ������...

		WCHAR font[32] = L"Press Start 2P";
		int fontSize = 5;

		//��ġ����
		float ellipseSize = 10;
		float startX = tileVector[i].rc.left;
		float startY = tileVector[i].rc.top;
		float endX   = startX + (fontSize * 2);
		float endY   = startY + (fontSize * 2);

		float startY2 = tileVector[i].rc.top + fontSize;
		float endY2 = startY2 + (fontSize * 2);



		//����ó��: ȭ��� ����X
		//if ((j * TILE_SIZEX) + _moveX >= _showWindowX / scale) continue;  //���ο�(����)
		//if ((j * TILE_SIZEX) + _moveX < 0)					   continue;  //���ο�(����)
		//if ((i * TILE_SIZEY) + _moveY >= _showWindowY / scale) continue;  //���ο�(����)
		//if ((i * TILE_SIZEY) + _moveY < 0)					   continue;  //���ο�(����)


		switch (tileVector[i].typeAtt)
		{
			//Start Point
			case TYPE_A_TR_START:
				D2DMANAGER->drawTextDwd(D2DMANAGER->createBrush(RED), font, fontSize, L"SP",
					startX + _moveX, startY + _moveY, endX + _moveX, endY + _moveY);
			break;


			//Furniture
			case TYPE_A_FT_ITEM:
				D2DMANAGER->drawTextDwd(D2DMANAGER->createBrush(GREEN), font, fontSize, L"FI",
					startX + _moveX, startY + _moveY, endX + _moveX, endY + _moveY);
			break;


			//Item
			case TYPE_A_IT_DRUG:
				D2DMANAGER->drawTextDwd(D2DMANAGER->createBrush(BLUE), font, fontSize, L"D",
					startX + _moveX, startY + _moveY, endX + _moveX, endY + _moveY);
			break;
			case TYPE_A_IT_FOOD:
				D2DMANAGER->drawTextDwd(D2DMANAGER->createBrush(BLUE), font, fontSize, L"F",
					startX + _moveX, startY + _moveY, endX + _moveX, endY + _moveY);
			break;
			case TYPE_A_IT_OIL:
				D2DMANAGER->drawTextDwd(D2DMANAGER->createBrush(BLUE), font, fontSize, L"O",
					startX + _moveX, startY + _moveY, endX + _moveX, endY + _moveY);
			break;
			case TYPE_A_IT_BULLET:
				D2DMANAGER->drawTextDwd(D2DMANAGER->createBrush(BLUE), font, fontSize, L"B",
					startX + _moveX, startY + _moveY, endX + _moveX, endY + _moveY);
			break;


			//Wall
			case TYPE_A_WL_CENTER:
				D2DMANAGER->drawTextDwd(D2DMANAGER->createBrush(CYAN), font, fontSize, L"C",
					startX + _moveX, startY + _moveY, endX + _moveX, endY + _moveY);
			break;
			case TYPE_A_WL_ORIGINAL:
				D2DMANAGER->drawTextDwd(D2DMANAGER->createBrush(CYAN), font, fontSize, L"O",
					startX + _moveX, startY + _moveY, endX + _moveX, endY + _moveY);
			break;
			case TYPE_A_WL_ARENDER:
				D2DMANAGER->drawTextDwd(D2DMANAGER->createBrush(CYAN), font, fontSize, L"AR",
					startX + _moveX, startY + _moveY, endX + _moveX, endY + _moveY);
			break;


			//Weapon
			case TYPE_A_WP_GUN:
				D2DMANAGER->drawTextDwd(D2DMANAGER->createBrush(MAGENTA), font, fontSize, L"G",
					startX + _moveX, startY + _moveY, endX + _moveX, endY + _moveY);
			break;
			case TYPE_A_WP_BOMB:
				D2DMANAGER->drawTextDwd(D2DMANAGER->createBrush(MAGENTA), font, fontSize, L"BB",
					startX + _moveX, startY + _moveY, endX + _moveX, endY + _moveY);
			break;
			case TYPE_A_WP_SWORD:
				D2DMANAGER->drawTextDwd(D2DMANAGER->createBrush(MAGENTA), font, fontSize, L"SW",
					startX + _moveX, startY + _moveY, endX + _moveX, endY + _moveY);
			break;
			case TYPE_A_WP_MACHINE:
				D2DMANAGER->drawTextDwd(D2DMANAGER->createBrush(MAGENTA), font, fontSize, L"M",
					startX + _moveX, startY + _moveY, endX + _moveX, endY + _moveY);
			break;
		}

		switch (tileVector[i].typeAtt2)
		{
			//Wall
			case TYPE_A_WL_CENTER:
				D2DMANAGER->drawTextDwd(D2DMANAGER->createBrush(CYAN), font, fontSize, L"C",
					startX + _moveX, startY2 + _moveY, endX + _moveX, endY2 + _moveY);
			break;
			case TYPE_A_WL_ORIGINAL:
				D2DMANAGER->drawTextDwd(D2DMANAGER->createBrush(CYAN), font, fontSize, L"O",
					startX + _moveX, startY2 + _moveY, endX + _moveX, endY2 + _moveY);
			break;
			case TYPE_A_WL_ARENDER:
				D2DMANAGER->drawTextDwd(D2DMANAGER->createBrush(CYAN), font, fontSize, L"AR",
					startX + _moveX, startY2 + _moveY, endX + _moveX, endY2 + _moveY);
			break;
		}
	}



}