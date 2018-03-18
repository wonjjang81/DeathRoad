#include "stdafx.h"
#include "character.h"


character::character()
{
}
character::~character()
{
}

HRESULT character::init()
{

	return S_OK;
}

void character::release()
{

}

void character::update()
{

}

void character::render()
{


}


//캐릭터 부위별 맵에 담기
void character::charSetup(string charTypeName, string imgNameHead, string imgNameBody,
	string imgNameHair, string imgNameGlas, string imgNameHats,
	float x, float y, float scale)
{
	//----------------------------------------------- HEAD -----------------------------------------------
	vChar tmpVCharHead;
	charBodySet(imgNameHead, tmpVCharHead, BODY_HEAD, x, y, scale);

	charTypeName.append("Head");
	_mChar.insert(make_pair(charTypeName, tmpVCharHead));

	//charTypeName 초기화
	stringErase(charTypeName, "Head");
	//----------------------------------------------- BODY -----------------------------------------------
	vChar tmpVCharBody;
	charBodySet(imgNameBody, tmpVCharBody, BODY_BODY, x, y, scale);

	charTypeName.append("Body");
	_mChar.insert(make_pair(charTypeName, tmpVCharBody));

	//charTypeName 초기화
	stringErase(charTypeName, "Body");
	//----------------------------------------------- HAIR -----------------------------------------------
	vChar tmpVCharHair;
	charBodySet(imgNameHair, tmpVCharHair, BODY_HAIR, x, y, scale);

	charTypeName.append("Hair");
	_mChar.insert(make_pair(charTypeName, tmpVCharHair));

	//charTypeName 초기화
	stringErase(charTypeName, "Hair");
	//----------------------------------------------- GLASS ----------------------------------------------
	vChar tmpVCharGlass;
	charBodySet(imgNameGlas, tmpVCharGlass, BODY_GLASS, x, y, scale);

	charTypeName.append("Glass");
	_mChar.insert(make_pair(charTypeName, tmpVCharGlass));

	//charTypeName 초기화
	stringErase(charTypeName, "Glass");
	//----------------------------------------------- HATS -----------------------------------------------
	vChar tmpVCharHats;
	charBodySet(imgNameHats, tmpVCharHats, BODY_HATS, x, y, scale);

	charTypeName.append("Hats");
	_mChar.insert(make_pair(charTypeName, tmpVCharHats));

	//charTypeName 초기화
	stringErase(charTypeName, "Hats");
}


//캐릭터 부위별 디테일 셋팅 벡터에 담기
void character::charBodySet(string imgName, vChar& charVector, BODYTYPE type, float x, float y, float scale)
{
	tagChar bodyType;
	bodyType.img = IMAGEMANAGER->findImage(imgName);
	sprintf(bodyType.imgName, "%s", imgName.c_str());
	int tileX = bodyType.img->getMaxFrameX() + 1;  //총타일 수X (*이미지 정보의 maxFrameX는 총 프레임수 - 1)
	int tileY = bodyType.img->getMaxFrameY() + 1;  //총타일 수Y

	//벡터에 담기
	for (int i = 0; i < tileY; ++i)
	{
		for (int j = 0; j < tileX; ++j)
		{
			bodyType.rc.left = x;
			bodyType.rc.top  = y;
			bodyType.rc.right  = x + bodyType.img->getFrameWidth()  * scale;
			bodyType.rc.bottom = y + bodyType.img->getFrameHeight() * scale;
			bodyType.index = (tileX * i) + j;
			bodyType.x = x;
			bodyType.y = y;
			bodyType.frameX = j;
			bodyType.frameY = i;
			bodyType.scale = scale;
			bodyType.gapX = bodyType.img->getFrameWidth() * bodyType.scale * bodyType.frameX;
			bodyType.gapY = bodyType.img->getFrameHeight() * bodyType.scale * bodyType.frameY;


			bodyType.type = type;

			charVector.push_back(bodyType);
		}
	}
}

void character::charRender(string charTypeName, int index)
{
	iterChar iter = _mChar.find(charTypeName);

	if (iter->first == charTypeName)
	{
		viChar viter = iter->second.begin();

		for (viter; viter != iter->second.end(); ++viter)
		{
			//예외처리
			int maxIndex = (viter->img->getMaxFrameX() * viter->img->getMaxFrameY());
			if (index > maxIndex) index = maxIndex;  
			if (index < 0) index = 0;  

			if (viter->index == index)
			{
				viter->img->frameRender(1.0f,
					viter->x,
					viter->y,
					viter->frameX, viter->frameY,
					0, viter->scale);

				//RECT 확인용
				D2DMANAGER->drawRectangle(D2DMANAGER->createBrush(RGB(0, 255, 0), 0.2f),
					viter->rc.left,
					viter->rc.top,
					viter->rc.right,
					viter->rc.bottom);

				break;
			}
		}
	}
}

void character::stringErase(string& editStrName, string eraseName)
{
	int strIndex = editStrName.find(eraseName);
	int strMaxIndex = editStrName.length();
	editStrName.erase(strIndex, strMaxIndex);
}


//최대 인덱스 넘버 반환
int character::getMaxIndex(string charTypeName)
{
	iterChar iter = _mChar.find(charTypeName);

	if (iter->first == charTypeName)
	{
		viChar viter = iter->second.begin();

		int maxFrameX = viter->img->getMaxFrameX();
		int maxFrameY = viter->img->getMaxFrameY();
		return maxFrameX * maxFrameY;
	}

	return -1;
}