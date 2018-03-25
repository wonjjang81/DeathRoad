#include "stdafx.h"
#include "character.h"


character::character()
{
}
character::~character()
{
}


//캐릭터 부위별 맵에 담기
void character::charSetup(string charTypeName, float x, float y, float scale)
{
	if (charTypeName == "") return;

	//----------------------------------------------- HEAD -----------------------------------------------
	vChar tmpVCharHead;
	charTypeName.append("Head");
	charBodySet(charTypeName, tmpVCharHead, BODY_HEAD, x, y, scale);

	_mChar.insert(make_pair(charTypeName, tmpVCharHead));

	//charTypeName 초기화
	stringErase(charTypeName, "Head");
	//----------------------------------------------- BODY -----------------------------------------------
	//----------------------------- upBody
	vChar tmpVCharUpBody;
	charTypeName.append("Body");
	charBodySet(charTypeName, tmpVCharUpBody, BODY_UPBODY, x, y, scale);

	charTypeName.append("Up");
	_mChar.insert(make_pair(charTypeName, tmpVCharUpBody));

	//charTypeName 초기화
	stringErase(charTypeName, "BodyUp");

	//----------------------------- dwBody
	vChar tmpVCharDwBody;
	charTypeName.append("Body");
	charBodySet(charTypeName, tmpVCharDwBody, BODY_DWBODY, x, y, scale);

	charTypeName.append("Dw");
	_mChar.insert(make_pair(charTypeName, tmpVCharDwBody));

	//charTypeName 초기화
	stringErase(charTypeName, "BodyDw");
	//----------------------------------------------- HAIR -----------------------------------------------
	vChar tmpVCharHair;
	charTypeName.append("Hair");
	charBodySet(charTypeName, tmpVCharHair, BODY_HAIR, x, y, scale);

	_mChar.insert(make_pair(charTypeName, tmpVCharHair));

	//charTypeName 초기화
	stringErase(charTypeName, "Hair");
	//----------------------------------------------- GLASS ----------------------------------------------
	vChar tmpVCharGlass;
	charTypeName.append("Glass");
	charBodySet(charTypeName, tmpVCharGlass, BODY_GLASS, x, y, scale);

	_mChar.insert(make_pair(charTypeName, tmpVCharGlass));

	//charTypeName 초기화
	stringErase(charTypeName, "Glass");
	//----------------------------------------------- HATS -----------------------------------------------
	vChar tmpVCharHats;
	charTypeName.append("Hats");
	charBodySet(charTypeName, tmpVCharHats, BODY_HATS, x, y, scale);

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
			switch (type)
			{
				case BODY_UPBODY:
					bodyType.rc.left   = (8 * scale);
					bodyType.rc.top    = (10 * scale);
					bodyType.rc.right  = (15 * scale);
					bodyType.rc.bottom = (bodyType.img->getFrameHeight() * scale);
				break;
				case BODY_DWBODY:
					bodyType.rc.left   = (6 * scale);
					bodyType.rc.top    = (20 * scale);
					bodyType.rc.right  = (18 * scale);
					bodyType.rc.bottom = ((bodyType.img->getFrameHeight() + 2) * scale);
				break;
				default:
					ZeroMemory(&bodyType.rc, sizeof(RECT));
				break;
			}

			bodyType.index = (tileX * i) + j;
			bodyType.x = x;
			bodyType.y = y;
			bodyType.bodyX = 0;
			bodyType.bodyY = 0;
			bodyType.frameX = j;
			bodyType.frameY = i;
			bodyType.scale = scale;

			bodyType.type = type;

			charVector.push_back(bodyType);
		}
	}
}

void character::charRender(string charTypeName, int index, bool flip)
{
	iterChar iter = _mChar.find(charTypeName);

	if (iter->first == charTypeName)
	{
		viChar viter = iter->second.begin();


		//vChar tmpChar;
		//int i = 0;
		////index정보만 벡터에 남기고 삭제
		//for (int i = 0; i < iter->second.size(); ++i)
		//{
		//	if (iter->second[i].index == index)
		//	{
		//		tmpChar.push_back(iter->second[i]);
		//		iter->second.erase(iter->second.begin() + i);
		//		continue;
		//	}
		//}
		//iter->second.clear();

		////다시 데이터 벡터에 담기
		//for (int i = 0; i < tmpChar.size(); ++i)
		//{
		//	iter->second.push_back(tmpChar[i]);
		//}


		for (viter; viter != iter->second.end(); ++viter)
		{
			//예외처리
			int maxIndex = (viter->img->getMaxFrameX() * viter->img->getMaxFrameY());
			if (index > maxIndex) index = maxIndex;  
			if (index < 0) index = 0;  


			if (viter->index == index)
			{
				viter->img->frameRender(1.0f,
					viter->x + (viter->bodyX / viter->scale),
					viter->y + (viter->bodyY / viter->scale),
					viter->frameX, viter->frameY,
					0, viter->scale, flip);

				RECT tmpRc;
				viter->cRc.left   = viter->x + viter->rc.left;
				viter->cRc.top    = viter->y + viter->rc.top;
				viter->cRc.right  = viter->x + viter->rc.right;
				viter->cRc.bottom = viter->y + viter->rc.bottom;

				//RECT 확인용
				switch (viter->type)
				{
					case BODY_UPBODY: case BODY_DWBODY:
						D2DMANAGER->drawRectangle(D2DMANAGER->createBrush(RGB(0, 0, 255), 0.5f),
							viter->cRc.left,
							viter->cRc.top,
							viter->cRc.right,
							viter->cRc.bottom);
					break;
				}

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

image* character::getImg(string charTypeName, int index)
{
	iterChar iter = _mChar.find(charTypeName);

	if (iter->first == charTypeName)
	{
		viChar viter = iter->second.begin();

		for (viter; viter != iter->second.end(); ++viter)
		{
			if (viter->index == index)
			{
				return viter->img;
				break;
			}
		}
	}
}

int character::getX(string charTypeName, int index)
{
	iterChar iter = _mChar.find(charTypeName);

	if (iter->first == charTypeName)
	{
		viChar viter = iter->second.begin();

		for (viter; viter != iter->second.end(); ++viter)
		{
			if (viter->index == index)
			{
				return viter->x;
				break;
			}
		}
	}
}

int character::getY(string charTypeName, int index)
{
	iterChar iter = _mChar.find(charTypeName);

	if (iter->first == charTypeName)
	{
		viChar viter = iter->second.begin();

		for (viter; viter != iter->second.end(); ++viter)
		{
			if (viter->index == index)
			{
				return viter->y;
				break;
			}
		}
	}
}

void character::setX(string charTypeName, int index, float x)
{
	iterChar iter = _mChar.find(charTypeName);

	if (iter->first == charTypeName)
	{
		viChar viter = iter->second.begin();

		for (viter; viter != iter->second.end(); ++viter)
		{
			if (viter->index == index)
			{
				viter->x = x;
				break;
			}
		}
	}
}

void character::setY(string charTypeName, int index, float y)
{
	iterChar iter = _mChar.find(charTypeName);

	if (iter->first == charTypeName)
	{
		viChar viter = iter->second.begin();

		for (viter; viter != iter->second.end(); ++viter)
		{
			if (viter->index == index)
			{
				viter->y  = y;
				break;
			}
		}
	}
}

void character::setBodyY(string charTypeName, int index, float moveY)
{
	iterChar iter = _mChar.find(charTypeName);

	if (iter->first == charTypeName)
	{
		viChar viter = iter->second.begin();

		for (viter; viter != iter->second.end(); ++viter)
		{
			if (viter->index == index)
			{
				viter->bodyY += moveY;
				break;
			}
		}
	}
}


int character::getFrameX(string charTypeName, int index)
{
	iterChar iter = _mChar.find(charTypeName);

	if (iter->first == charTypeName)
	{
		viChar viter = iter->second.begin();

		for (viter; viter != iter->second.end(); ++viter)
		{
			if (viter->index == index)
			{
				return viter->frameX;
				break;
			}
		}
	}
}

int character::getFrameY(string charTypeName, int index)
{
	iterChar iter = _mChar.find(charTypeName);

	if (iter->first == charTypeName)
	{
		viChar viter = iter->second.begin();

		for (viter; viter != iter->second.end(); ++viter)
		{
			if (viter->index == index)
			{
				return viter->frameX;
				break;
			}
		}
	}
}

void character::setFrameX(string charTypeName, int index, int x)
{
	iterChar iter = _mChar.find(charTypeName);

	if (iter->first == charTypeName)
	{
		viChar viter = iter->second.begin();

		for (viter; viter != iter->second.end(); ++viter)
		{
			if (viter->index == index)
			{
				viter->frameX = x;
				break;
			}
		}
	}
}

void character::setFrameY(string charTypeName, int index, int y)
{
	iterChar iter = _mChar.find(charTypeName);

	if (iter->first == charTypeName)
	{
		viChar viter = iter->second.begin();

		for (viter; viter != iter->second.end(); ++viter)
		{
			if (viter->index == index)
			{
				viter->frameY = y;
				break;
			}
		}
	}
}


string character::bodyNameChange(string imgName, BODYTYPE typeName)
{
	switch (typeName)
	{
	case BODY_HEAD:
		imgName.append("Head");
		break;
	case BODY_UPBODY:
		imgName.append("BodyUp");
		break;
	case BODY_DWBODY:
		imgName.append("BodyDw");
		break;
	case BODY_HAIR:
		imgName.append("Hair");
		break;
	case BODY_GLASS:
		imgName.append("Glass");
		break;
	case BODY_HATS:
		imgName.append("Hats");
		break;
	}

	return imgName;
}


RECT character::getRect(string charTypeName, int index)
{
	iterChar iter = _mChar.find(charTypeName);

	if (iter->first == charTypeName)
	{
		viChar viter = iter->second.begin();

		for (viter; viter != iter->second.end(); ++viter)
		{
			if (viter->index == index)
			{
				return viter->cRc;
				break;
			}
		}
	}
}