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
	//�̹����� ������ ����
	for (int i = 0; i < tileVector.size(); ++i)
	{
		if (tileVector[i].img == NULL || tileVector[i].imgName == "")
		{
			tileVector.erase(tileVector.begin() + i);
			continue;
		}
	}

	//y�ప�� ���ؼ� ���������� �ӽú��Ϳ� ��Ƽ� ������
	vSaveTile tmpVecotr;
	int index = 0;
	while (tileVector.size() != 0)
	{
		for (int i = 0; i < tileVector.size(); ++i)
		{	
			for (int j = 0; j < tileVector.size(); ++j)
			{
				index = i;

				if (tileVector[i].y >= tileVector[j].y)
				{
					index = j;
				}
			}

			tmpVecotr.push_back(tileVector[index]);
			tileVector.erase(tileVector.begin() + index);
			break;
		}
	}
	tileVector.clear();  //���� �ʱ�ȭ


	//���ĵ� ������ �ٽ� ���Ϳ� ���
	while (tmpVecotr.size() != 0)
	{
		for (int i = 0; i < tmpVecotr.size(); ++i)
		{
			if (tmpVecotr[i].img == NULL)
			{
				tmpVecotr.erase(tmpVecotr.begin() + i);
				continue;
			}

			tileVector.push_back(tmpVecotr[i]);
			tmpVecotr.erase(tmpVecotr.begin() + i);
			break;
		}
	}
	tmpVecotr.clear();	//���� �ʱ�ȭ


	//����
	for (int i = 0; i < tileVector.size(); ++i)
	{
		//����ó��
		if (tileVector[i].img == NULL) continue;  //�̹��� X

		//Ÿ�Ϸ�Ʈ ����
		RECT reRect;
		reRect.left   = (tileVector[i].rc.left  ) * scale + moveX;
		reRect.top    = (tileVector[i].rc.top   ) * scale + moveY;
		reRect.right  = (tileVector[i].rc.right ) * scale + moveX;
		reRect.bottom = (tileVector[i].rc.bottom) * scale + moveY;

		//��ġ ����(Ÿ�� �߽�)
		tileVector[i].centerX = (tileVector[i].x + tileVector[i].centerX) * scale + moveX;
		tileVector[i].centerY = (tileVector[i].y + tileVector[i].centerY) * scale + moveY;

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