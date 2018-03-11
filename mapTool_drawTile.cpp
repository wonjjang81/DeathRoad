#include "stdafx.h"
#include "mapTool.h"


void mapTool::tileDraw(float scale)
{
	//������ Ÿ�� ���� ��������
	if (_menuTabOn && _menuTr->_selectVTile.size() != 0)
	{
		_drawTile = _menuTr->_selectVTile[0];
	}


	//Ÿ�ϸ� Ŭ����
	D2DMANAGER->pRenderTarget->PushAxisAlignedClip(RectF(0, 0, _showWindowX, _showWindowY), D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);

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
				tile.attribute = ATTR_UNMOVE;
				tile.tileType  = TYPE_TERRAIN;

				_vSaveTr.push_back(tile);
			}
		}
	}


	//Ÿ�� �׸���
	for (int i = 0; i < _vSaveTr.size(); ++i)
	{
		//����ó��: �̹���X
		if (_vSaveTr[i].img == NULL)continue;  //�̹���X

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
		//	reRect.bottom );

	}

	//�ʱ�ȭ
	D2DMANAGER->pRenderTarget->PopAxisAlignedClip();
}