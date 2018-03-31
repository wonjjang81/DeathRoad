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
	//-------------------------------------------------- 타일맵 클립핑 Start --------------------------------------------------
	D2DMANAGER->pRenderTarget->PushAxisAlignedClip(RectF(0, 0, WINSIZEX, WINSIZEY), D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	//-------------------------------------------------- 타일맵 클립핑 Start --------------------------------------------------


	//========================== 타일 그리기 Start ==========================

	vMapDraw(tileVector, moveX, moveY, scale, aRender);

	//=========================== 타일 그리기 End ===========================


	//--------------------------------------------------- 타일맵 클립핑 end ---------------------------------------------------
	D2DMANAGER->pRenderTarget->PopAxisAlignedClip();
	//--------------------------------------------------- 타일맵 클립핑 end ---------------------------------------------------
}


//타일 그리기 [원형]: 벡터
void mapRender::vMapDraw(vSaveTile tileVector, float moveX, float moveY, float scale, bool aRender)
{
	//이미지가 없으면 삭제
	for (int i = 0; i < tileVector.size(); ++i)
	{
		if (tileVector[i].img == NULL || tileVector[i].imgName == "")
		{
			tileVector.erase(tileVector.begin() + i);
			//continue;
		}
	}

	//y축값을 비교해서 작은값부터 임시벡터에 담아서 재정렬
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
	tileVector.clear();  //벡터 초기화


	//정렬된 데이터 다시 벡터에 담기
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
	tmpVecotr.clear();	//벡터 초기화


	//렌더
	for (int i = 0; i < tileVector.size(); ++i)
	{
		//예외처리
		if (tileVector[i].img == NULL) continue;  //이미지 X
		if (aRender)
		{
			if (tileVector[i].attribute != ATTR_AFTERRENDER) continue;
		}
		else
		{
			if (tileVector[i].attribute == ATTR_AFTERRENDER) continue;
		}

		//문 예외처리(열린 문)
		if (tileVector[i].tileType == TYPE_DOOR)
		{
			if (tileVector[i].actionValue != 0) continue;
		}
	
		//타일렉트 보정
		//RECT reRect;
		//reRect.left   = (tileVector[i].rc.left  ) * scale + moveX;
		//reRect.top    = (tileVector[i].rc.top   ) * scale + moveY;
		//reRect.right  = (tileVector[i].rc.right ) * scale + moveX;
		//reRect.bottom = (tileVector[i].rc.bottom) * scale + moveY;

		tileVector[i].cRc.left   = (tileVector[i].rc.left)   * scale + moveX;
		tileVector[i].cRc.top    = (tileVector[i].rc.top)    * scale + moveY;
		tileVector[i].cRc.right  = (tileVector[i].rc.right)  * scale + moveX;
		tileVector[i].cRc.bottom = (tileVector[i].rc.bottom) * scale + moveY;

		//위치 보정(타일 중심)
		tileVector[i].centerX = (tileVector[i].x + tileVector[i].centerX) * scale + moveX;
		tileVector[i].centerY = (tileVector[i].y + tileVector[i].centerY) * scale + moveY;

		//예외처리: 화면밖 렌더X													
		if (tileVector[i].cRc.left > WINSIZEX)  continue;  //가로열(우측)
		if (tileVector[i].cRc.right  < 0)	   continue;  //가로열(좌측)
		if (tileVector[i].cRc.top > WINSIZEY)   continue;  //세로열(상부)
		if (tileVector[i].cRc.bottom < 0)	   continue;  //세로열(하부)

		tileVector[i].img->frameRender(1.0f, tileVector[i].centerX, tileVector[i].centerY,
			tileVector[i].frameX, tileVector[i].frameY, 0.0f, scale);

		//렉트 확인용
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