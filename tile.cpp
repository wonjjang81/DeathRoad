#include "stdafx.h"
#include "tile.h"


tile::tile()
{
}
tile::~tile()
{
}


void tile::tileSetup(string tileName, float x, float y, ATTRIBUTE attribute, TILE_TYPE tileType, TYPE_ATTRIBUTE typeAttr, ANCHOR_TYPE anchor, OVERLAPPOSITION overPosition, float scale)
{
	vTile tileVector;

	//타일정보
	tagTile tile;
	tile.img = IMAGEMANAGER->findImage(tileName);
	sprintf(tile.imgName, "%s", tileName.c_str());
	int tileX = tile.img->getMaxFrameX() + 1;  //총타일 수X (*이미지 정보의 maxFrameX는 총 프레임수 - 1)
	int tileY = tile.img->getMaxFrameY() + 1;  //총타일 수Y


	//벡터에 담기
	for (int i = 0; i < tileY; ++i)
	{
		for (int j = 0; j < tileX; ++j)
		{
			tile.rc.left    = tile.img->getFrameWidth()  * scale * j;
			tile.rc.top	    = tile.img->getFrameHeight() * scale * i;
			tile.rc.right   = tile.img->getFrameWidth()  * scale * (j + 1);
			tile.rc.bottom  = tile.img->getFrameHeight() * scale * (i + 1);
			tile.index      = (tileX * i) + j;
			tile.x		    = x;
			tile.y		    = y;
			tile.scale	    = scale;
			tile.frameX     = j;
			tile.frameY     = i;
			tile.gapX       = tile.img->getFrameWidth() * tile.scale * tile.frameX;
			tile.gapY       = tile.img->getFrameHeight() * tile.scale * tile.frameY;
			tile.attribute  = attribute;
			tile.tileType   = tileType;
			tile.typeAtt    = typeAttr;
			tile.anchorType = anchor;
			tile.overPos    = overPosition;
			tile.id		    = tile.index;
			tile.reWidth    = TILE_SIZEX;
			tile.reHeight   = TILE_SIZEY;
			setTileAnchor(tile, tile.anchorType);


			tileVector.push_back(tile);
		}
	}

	_mTile.insert(make_pair(tileName, tileVector));
}


void tile::tileRender(string tileName, float moveX, float moveY)
{
	iterTile iter = _mTile.find(tileName);

	if (iter->first == tileName)
	{
		viTile viter = iter->second.begin();

		for (viter; viter != iter->second.end(); ++viter)
		{
			//예외처리: 화면밖 render(X)
			//if (viter->rc.left   < 0) continue;
			//if (viter->rc.right  > 0) continue;
			//if (viter->rc.top    < 0) continue;
			//if (viter->rc.bottom > 0) continue;

			viter->img->frameRender(1.0f, 
				viter->x + viter->gapX + moveX,
				viter->y + viter->gapY + moveY,
				viter->frameX, viter->frameY,
				0, viter->scale);

			//RECT 확인용
			D2DMANAGER->drawRectangle(D2DMANAGER->createBrush(RGB(0, 255, 0), 0.2f), 
				moveX + viter->x + viter->rc.left, 
				moveY + viter->y + viter->rc.top,
				moveX + viter->x + viter->rc.right, 
				moveY + viter->y + viter->rc.bottom);
		}

	}
}

tagTile tile::tileSelect(string tileName, float moveX, float moveY)
{
	tagTile tmpTile;
	ZeroMemory(&tmpTile, sizeof(tagTile));

	iterTile iter = _mTile.find(tileName);

	if (iter->first == tileName)
	{
		viTile viter = iter->second.begin();

		//예외처리
		if (_ptMouse.x > viter->x + viter->img->getWidth() * viter->scale)  return tmpTile;  //우측
		if (_ptMouse.x < 0)													return tmpTile;  //좌측
		if (_ptMouse.y < 0)													return tmpTile;  //상부
		if (_ptMouse.y > viter->y + viter->img->getHeight() * viter->scale) return tmpTile;  //하부


		for (viter; viter != iter->second.end(); ++viter)
		{
			//타일렉트 보정
			RECT reRect;
			reRect.left   = moveX + viter->x + viter->gapX;
			reRect.top    = moveY + viter->y + viter->gapY;
			reRect.right  = reRect.left + (viter->img->getFrameWidth() * viter->scale);
			reRect.bottom = reRect.top  + (viter->img->getFrameHeight() * viter->scale);

			if (PtInRect(&reRect, _ptMouse))
			{
				D2DMANAGER->drawRectangle(D2DMANAGER->createBrush(RGB(0, 0, 255)),
					moveX + viter->x + viter->rc.left,
					moveY + viter->y + viter->rc.top,
					moveX + viter->x + viter->rc.right,
					moveY + viter->y + viter->rc.bottom);

				//tile 정보 입력
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					tmpTile.img = viter->img;
					sprintf(tmpTile.imgName, "%s", viter->imgName);
					tmpTile.rc.left = viter->rc.left;
					tmpTile.rc.top = viter->rc.top;
					tmpTile.rc.right = viter->rc.right;
					tmpTile.rc.bottom = viter->rc.bottom;
					tmpTile.index = viter->index;
					tmpTile.x = viter->x;
					tmpTile.y = viter->y;
					tmpTile.scale = viter->scale;
					tmpTile.frameX = viter->frameX;
					tmpTile.frameY = viter->frameY;
					tmpTile.gapX = viter->gapX;
					tmpTile.gapY = viter->gapY;
					tmpTile.attribute = viter->attribute;
					tmpTile.tileType = viter->tileType;
					tmpTile.anchorType = viter->anchorType;
					tmpTile.overPos = viter->overPos;
					tmpTile.id = viter->id;
					tmpTile.centerX = viter->centerX;
					tmpTile.centerY = viter->centerY;
					tmpTile.reWidth = viter->reWidth;
					tmpTile.reHeight = viter->reHeight;

					return tmpTile;
				}

				break;
			}
		}
	}

	return tmpTile;
}

void tile::tileDrawFillRc(tagTile selectTile, COLORREF color, float opacity, float moveX, float moveY)
{
	D2DMANAGER->fillRectangle(D2DMANAGER->createBrush(color, opacity),
		moveX + selectTile.x + selectTile.rc.left,
		moveY + selectTile.y + selectTile.rc.top,
		moveX + selectTile.x + selectTile.rc.right,
		moveY + selectTile.y + selectTile.rc.bottom);
}

//=========================== 타일속성 변경 ===========================
//타일특성
void tile::setTileAttribute(tagTile selectTile, ATTRIBUTE attribute)
{
	selectTile.attribute = attribute;
}

//타일타입
void tile::setTileType(tagTile selectTile, TILE_TYPE tileType)
{
	selectTile.tileType = tileType;
}
//=========================== 타일속성 변경 ===========================


//앵커타입별 이미지 Render 기준점 설정
void tile::setTileAnchor(tagTile& tile, ANCHOR_TYPE anchor)
{
	//타일맵 크기비율
	float tileRatioX = (tile.img->getFrameWidth() / (float)TILE_SIZEX);
	float tileRatioY = (tile.img->getFrameHeight() / (float)TILE_SIZEY);

	//타일 중심점 셋팅
	int RectCenterX = tile.rc.left + (tile.rc.right - tile.rc.left) / 2;
	int RectCenterY = tile.rc.top + (tile.rc.bottom - tile.rc.top) / 2;

	//----------------------------- 타일 사이즈에 맞게 위치 보정 -----------------------------
	switch (anchor)
	{
		case ANCHOR_LEFTTOP:
			tile.centerX = 0;
			tile.centerY = 0;
		break;
		case ANCHOR_CENTER:
			if (tileRatioX < 1) tile.centerX = (TILE_SIZEX / (tileRatioX * 4 * 2));								//타일사이즈X 보다 이미지가 작으면
			else tileRatioX == 1 ? tile.centerX = 0 : tile.centerX = -((TILE_SIZEX / 2) * (tileRatioX - 1));	//타일사이즈X 보다 이미지가 크면
			if (tileRatioY < 1) tile.centerY = (TILE_SIZEY / (tileRatioY * 4 * 2));								//타일사이즈Y 보다 이미지가 작으면
			else tileRatioY == 1 ? tile.centerY = 0 : tile.centerY = -((TILE_SIZEY / 2) * (tileRatioY - 1));	//타일사이즈Y 보다 이미지가 크면	
		break;
		case ANCHOR_BOTTOMCENTER:
			if (tileRatioX < 1) tile.centerX = (TILE_SIZEX / (tileRatioX * 4 * 2));								//타일사이즈X 보다 이미지가 작으면
			else tileRatioX == 1 ? tile.centerX = 0 : tile.centerX = -((TILE_SIZEX / 2) * (tileRatioX - 1));	//타일사이즈X 보다 이미지가 크면
			if (tileRatioY < 1) tile.centerY = (TILE_SIZEY / (tileRatioX * 4 * 2 * 2));							//타일사이즈Y 보다 이미지가 작으면
			else tileRatioY == 1 ? tile.centerY = 0 : tile.centerY = -((TILE_SIZEY) * (tileRatioY - 1));		//타일사이즈Y 보다 이미지가 크면
		break;
	}
}