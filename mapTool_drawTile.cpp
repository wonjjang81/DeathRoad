#include "stdafx.h"
#include "mapTool.h"


void mapTool::tileDraw(float scale)
{
	//-------------------------------------------------- Ÿ�ϸ� Ŭ���� Start --------------------------------------------------
	D2DMANAGER->pRenderTarget->PushAxisAlignedClip(RectF(0, 0, _showWindowX, _showWindowY), D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	//-------------------------------------------------- Ÿ�ϸ� Ŭ���� Start --------------------------------------------------


	//�⺻Ÿ�� ���Ϳ� ���
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


	//========================== Ÿ�� �׸��� Start ==========================
	//------------------------------- Terrain -------------------------------
	for (int i = 0; i < _vSaveTr.size(); ++i)
	{
		//����ó��
		if (_vSaveTr[i].img == NULL) continue;  //�̹��� X


		//Ÿ�Ϸ�Ʈ ����
		RECT reRect;
		reRect.left   = (_vSaveTr[i].rc.left   + _moveX) * scale;
		reRect.top    = (_vSaveTr[i].rc.top    + _moveY) * scale;
		reRect.right  = (_vSaveTr[i].rc.right  + _moveX) * scale;
		reRect.bottom = (_vSaveTr[i].rc.bottom + _moveY) * scale;

		//����ó��: ȭ��� ����X
		if (reRect.left   >= _showWindowX)  continue;  //���ο�(����)
		if (reRect.right  < 0)			    continue;  //���ο�(����)
		if (reRect.top    >= _showWindowY)  continue;  //���ο�(���)
		if (reRect.bottom < 0)			    continue;  //���ο�(�Ϻ�)

		_vSaveTr[i].img->frameRender(1.0f, reRect.left, reRect.top,
			_vSaveTr[i].frameX, _vSaveTr[i].frameY, 0.0f, scale);

		//��Ʈ Ȯ�ο�
		//D2DMANAGER->drawRectangle(D2DMANAGER->createBrush(RGB(255, 0, 0)),
		//	reRect.left   ,
		//	reRect.top    ,
		//	reRect.right  ,
		//	reRect.bottom);
	}
	//------------------------------- Building ------------------------------
	for (int i = 0; i < _vSaveBd.size(); ++i)
	{
		//����ó��
		if (_vSaveBd[i].img == NULL) continue;  //�̹��� X

		//Ÿ�Ϸ�Ʈ ����
		RECT reRect;
		reRect.left   = (_vSaveBd[i].rc.left   + _moveX) * scale;
		reRect.top    = (_vSaveBd[i].rc.top    + _moveY) * scale;
		reRect.right  = (_vSaveBd[i].rc.right  + _moveX) * scale;
		reRect.bottom = (_vSaveBd[i].rc.bottom + _moveY) * scale;

		//����ó��: ȭ��� ����X
		if (reRect.left >= _showWindowX)  continue;  //���ο�(����)
		if (reRect.right  < 0)			  continue;  //���ο�(����)
		if (reRect.top  >= _showWindowY)  continue;  //���ο�(���)
		if (reRect.bottom < 0)			  continue;  //���ο�(�Ϻ�)

		_vSaveBd[i].img->frameRender(1.0f, reRect.left, reRect.top,
			_vSaveBd[i].frameX, _vSaveBd[i].frameY, 0.0f, scale);

		//��Ʈ Ȯ�ο�
		//D2DMANAGER->drawRectangle(D2DMANAGER->createBrush(RGB(255, 0, 0)),
		//	reRect.left   ,
		//	reRect.top    ,
		//	reRect.right  ,
		//	reRect.bottom);
	}

	//=========================== Ÿ�� �׸��� End ===========================


	//--------------------------------------------------- Ÿ�ϸ� Ŭ���� end ---------------------------------------------------
	D2DMANAGER->pRenderTarget->PopAxisAlignedClip();
	//--------------------------------------------------- Ÿ�ϸ� Ŭ���� end ---------------------------------------------------
}