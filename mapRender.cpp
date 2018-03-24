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
	//-------------------------------------------------- 타일맵 클립핑 Start --------------------------------------------------
	D2DMANAGER->pRenderTarget->PushAxisAlignedClip(RectF(0, 0, WINSIZEX, WINSIZEY), D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	//-------------------------------------------------- 타일맵 클립핑 Start --------------------------------------------------


	//========================== 타일 그리기 Start ==========================

	vMapDraw(tileVector, moveX, moveY, scale);

	//=========================== 타일 그리기 End ===========================


	//--------------------------------------------------- 타일맵 클립핑 end ---------------------------------------------------
	D2DMANAGER->pRenderTarget->PopAxisAlignedClip();
	//--------------------------------------------------- 타일맵 클립핑 end ---------------------------------------------------
}


//타일 그리기 [원형]: 벡터
void mapRender::vMapDraw(vSaveTile tileVector, float moveX, float moveY, float scale)
{
	//이미지가 없으면 삭제
	for (int i = 0; i < tileVector.size(); ++i)
	{
		if (tileVector[i].img == NULL || tileVector[i].imgName == "")
		{
			tileVector.erase(tileVector.begin() + i);
			continue;
		}
	}

	//y축값을 비교해서 작은값부터 임시벡터에 담아서 재정렬
	vSaveTile tmpVecotr;
	while (tileVector.size() != 0)
	{
		for (int i = 0; i < tileVector.size(); ++i)
		{
			int index = 0;

			for (int j = i + 1; j < tileVector.size(); ++j)
			{
				if (tileVector[i].y <= tileVector[j].y)
				{
					index = i;
				}
				else index = j;
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

		//타일렉트 보정
		RECT reRect;
		reRect.left   = (tileVector[i].rc.left   + moveX) * scale;
		reRect.top    = (tileVector[i].rc.top    + moveY) * scale;
		reRect.right  = (tileVector[i].rc.right  + moveX) * scale;
		reRect.bottom = (tileVector[i].rc.bottom + moveY) * scale;

		//위치 보정(타일 중심)
		tileVector[i].centerX = (tileVector[i].x + tileVector[i].centerX) * scale;
		tileVector[i].centerY = (tileVector[i].y + tileVector[i].centerY) * scale;

		//예외처리: 화면밖 렌더X
		if (reRect.left > WINSIZEX)  continue;  //가로열(우측)
		if (reRect.right  < 0)		 continue;  //가로열(좌측)
		if (reRect.top > WINSIZEY)   continue;  //세로열(상부)
		if (reRect.bottom < 0)		 continue;  //세로열(하부)

		tileVector[i].img->frameRender(1.0f, tileVector[i].centerX, tileVector[i].centerY,
			tileVector[i].frameX, tileVector[i].frameY, 0.0f, scale);

		//렉트 확인용
		D2DMANAGER->drawRectangle(D2DMANAGER->createBrush(RGB(255, 0, 0)),
			reRect.left,
			reRect.top,
			reRect.right,
			reRect.bottom);
	}

}