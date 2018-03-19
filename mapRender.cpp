#include "stdafx.h"
#include "mapRender.h"


mapRender::mapRender()
{
}
mapRender::~mapRender()
{
}



void mapRender::mapDraw(vSaveTile tileVector, float moveX, float moveY, float scale)
{
	//-------------------------------------------------- Ÿ�ϸ� Ŭ���� Start --------------------------------------------------
	D2DMANAGER->pRenderTarget->PushAxisAlignedClip(RectF(0, 0, WINSIZEX, WINSIZEY), D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	//-------------------------------------------------- Ÿ�ϸ� Ŭ���� Start --------------------------------------------------


	//========================== Ÿ�� �׸��� Start ==========================

	vMapDraw(tileVector, moveX, moveY, scale);

	//=========================== Ÿ�� �׸��� End ===========================


	//--------------------------------------------------- Ÿ�ϸ� Ŭ���� end ---------------------------------------------------
	D2DMANAGER->pRenderTarget->PopAxisAlignedClip();
	//--------------------------------------------------- Ÿ�ϸ� Ŭ���� end ---------------------------------------------------
}


//Ÿ�� �׸��� [����]: ����
void mapRender::vMapDraw(vSaveTile tileVector, float moveX, float moveY, float scale)
{
	for (int i = 0; i < tileVector.size(); ++i)
	{
		//����ó��
		if (tileVector[i].img == NULL) continue;  //�̹��� X

		//Ÿ�Ϸ�Ʈ ����
		RECT reRect;
		reRect.left   = (tileVector[i].rc.left   + moveX) * scale;
		reRect.top    = (tileVector[i].rc.top    + moveY) * scale;
		reRect.right  = (tileVector[i].rc.right  + moveX) * scale;
		reRect.bottom = (tileVector[i].rc.bottom + moveY) * scale;

		//��ġ ����(Ÿ�� �߽�)
		tileVector[i].centerX = (tileVector[i].x + tileVector[i].centerX) * scale;
		tileVector[i].centerY = (tileVector[i].y + tileVector[i].centerY) * scale;

		//����ó��: ȭ��� ����X
		if (reRect.left > WINSIZEX)  continue;  //���ο�(����)
		if (reRect.right  < 0)		 continue;  //���ο�(����)
		if (reRect.top > WINSIZEY)   continue;  //���ο�(���)
		if (reRect.bottom < 0)		 continue;  //���ο�(�Ϻ�)

		tileVector[i].img->frameRender(1.0f, tileVector[i].centerX, tileVector[i].centerY,
			tileVector[i].frameX, tileVector[i].frameY, 0.0f, scale);

		//��Ʈ Ȯ�ο�
		D2DMANAGER->drawRectangle(D2DMANAGER->createBrush(RGB(255, 0, 0)),
			reRect.left,
			reRect.top,
			reRect.right,
			reRect.bottom);
	}

}