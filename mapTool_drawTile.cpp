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


	//========================== Ÿ�� �׸��� Start ==========================
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
	//=========================== Ÿ�� �׸��� End ===========================


	//--------------------------------------------------- Ÿ�ϸ� Ŭ���� end ---------------------------------------------------
	D2DMANAGER->pRenderTarget->PopAxisAlignedClip();
	//--------------------------------------------------- Ÿ�ϸ� Ŭ���� end ---------------------------------------------------
}


//Ÿ�� �׸��� [����]: ����
void mapTool::vTileDraw(vSaveTile tileVector, float scale)
{
	for (int i = 0; i < tileVector.size(); ++i)
	{
		//����ó��
		if (tileVector[i].img == NULL) continue;  //�̹��� X

												//Ÿ�Ϸ�Ʈ ����
		RECT reRect;
		reRect.left = (tileVector[i].rc.left     + _moveX) * scale;
		reRect.top = (tileVector[i].rc.top       + _moveY) * scale;
		reRect.right = (tileVector[i].rc.right   + _moveX) * scale;
		reRect.bottom = (tileVector[i].rc.bottom + _moveY) * scale;

		//��ġ ����(Ÿ�� �߽�)
		float tmpCenterX = reRect.left + (tileVector[i].centerX * scale);
		float tmpCenterY = reRect.top  + (tileVector[i].centerY * scale);

		//����ó��: ȭ��� ����X
		if (reRect.left >= _showWindowX)  continue;  //���ο�(����)
		if (reRect.right  < 0)			  continue;  //���ο�(����)
		if (reRect.top >= _showWindowY)  continue;  //���ο�(���)
		if (reRect.bottom < 0)			  continue;  //���ο�(�Ϻ�)

		tileVector[i].img->frameRender(1.0f, tmpCenterX, tmpCenterY,
			tileVector[i].frameX, tileVector[i].frameY, 0.0f, scale);

		//��Ʈ Ȯ�ο�
		D2DMANAGER->drawRectangle(D2DMANAGER->createBrush(RGB(255, 0, 0)),
			reRect.left,
			reRect.top,
			reRect.right,
			reRect.bottom);
	}

}