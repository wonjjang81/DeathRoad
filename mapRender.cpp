#include "stdafx.h"
#include "mapRender.h"


mapRender::mapRender()
{
}
mapRender::~mapRender()
{
}



void mapRender::mapDraw(vSaveTile tileVector, float moveX, float moveY, float scale, bool aRender)
{
	//-------------------------------------------------- Ÿ�ϸ� Ŭ���� Start --------------------------------------------------
	D2DMANAGER->pRenderTarget->PushAxisAlignedClip(RectF(0, 0, WINSIZEX, WINSIZEY), D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	//-------------------------------------------------- Ÿ�ϸ� Ŭ���� Start --------------------------------------------------


	//========================== Ÿ�� �׸��� Start ==========================

	vMapDraw(tileVector, moveX, moveY, scale, aRender);

	//=========================== Ÿ�� �׸��� End ===========================


	//--------------------------------------------------- Ÿ�ϸ� Ŭ���� end ---------------------------------------------------
	D2DMANAGER->pRenderTarget->PopAxisAlignedClip();
	//--------------------------------------------------- Ÿ�ϸ� Ŭ���� end ---------------------------------------------------
}


//Ÿ�� �׸��� [����]: ����
void mapRender::vMapDraw(vSaveTile tileVector, float moveX, float moveY, float scale, bool aRender)
{
	//�̹����� ������ ����
	for (int i = 0; i < tileVector.size(); ++i)
	{
		if (tileVector[i].img == NULL || tileVector[i].imgName == "")
		{
			tileVector.erase(tileVector.begin() + i);
			//continue;
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
		if (aRender)
		{
			if (tileVector[i].attribute != ATTR_AFTERRENDER) continue;
		}
		else
		{
			if (tileVector[i].attribute == ATTR_AFTERRENDER) continue;
		}

		//�� ����ó��(���� ��)
		if (tileVector[i].tileType == TYPE_DOOR)
		{
			if (tileVector[i].actionValue != 0) continue;
		}
	
		//Ÿ�Ϸ�Ʈ ����
		//RECT reRect;
		//reRect.left   = (tileVector[i].rc.left  ) * scale + moveX;
		//reRect.top    = (tileVector[i].rc.top   ) * scale + moveY;
		//reRect.right  = (tileVector[i].rc.right ) * scale + moveX;
		//reRect.bottom = (tileVector[i].rc.bottom) * scale + moveY;

		tileVector[i].cRc.left   = (tileVector[i].rc.left)   * scale + moveX;
		tileVector[i].cRc.top    = (tileVector[i].rc.top)    * scale + moveY;
		tileVector[i].cRc.right  = (tileVector[i].rc.right)  * scale + moveX;
		tileVector[i].cRc.bottom = (tileVector[i].rc.bottom) * scale + moveY;

		//��ġ ����(Ÿ�� �߽�)
		tileVector[i].centerX = (tileVector[i].x + tileVector[i].centerX) * scale + moveX;
		tileVector[i].centerY = (tileVector[i].y + tileVector[i].centerY) * scale + moveY;

		//����ó��: ȭ��� ����X													
		if (tileVector[i].cRc.left > WINSIZEX)  continue;  //���ο�(����)
		if (tileVector[i].cRc.right  < 0)	   continue;  //���ο�(����)
		if (tileVector[i].cRc.top > WINSIZEY)   continue;  //���ο�(���)
		if (tileVector[i].cRc.bottom < 0)	   continue;  //���ο�(�Ϻ�)

		tileVector[i].img->frameRender(1.0f, tileVector[i].centerX, tileVector[i].centerY,
			tileVector[i].frameX, tileVector[i].frameY, 0.0f, scale);

		//��Ʈ Ȯ�ο�
		D2DMANAGER->drawRectangle(D2DMANAGER->createBrush(RGB(255, 0, 0)),
			tileVector[i].cRc.left,
			tileVector[i].cRc.top,
			tileVector[i].cRc.right,
			tileVector[i].cRc.bottom);

		if (tileVector[i].tileType == TYPE_FURNITURE)
		{
			D2DMANAGER->drawIntText(L"", tileVector[i].x, tileVector[i].centerX, tileVector[i].centerY, WHITE);
			D2DMANAGER->drawIntText(L"", tileVector[i].y, tileVector[i].centerX, tileVector[i].centerY + 20, WHITE);
		}
	}

}