#include "stdafx.h"
#include "tile.h"


tile::tile()
{
}
tile::~tile()
{
}

HRESULT tile::init()
{



	return S_OK;
}

void tile::release()
{

}

void tile::update()	
{

}

void tile::render()	
{

}

void tile::tileSetup(string tileName, float x, float y, ATTRIBUTE attribute, TILE_TYPE tileType, float scale)
{
	vTile tileVector;

	//타일정보
	tagTile tile;
	tile.img = IMAGEMANAGER->findImage(tileName);
	int tileX = tile.img->getMaxFrameX();
	int tileY = tile.img->getMaxFrameY();

	//벡터에 담기
	for (int i = 0; i < tileY; ++i)
	{
		for (int j = 0; j < tileX; ++j)
		{
			tile.rc.left   = TILE_SIZEX * scale * j;
			tile.rc.top	   = TILE_SIZEY * scale * i;
			tile.rc.right  = TILE_SIZEX * scale * (j + 1);
			tile.rc.bottom = TILE_SIZEY * scale * (i + 1);
			tile.index     = (tileX * i) + j;
			tile.x		   = x;
			tile.y		   = y;
			tile.scale	   = scale;
			tile.frameX    = j;
			tile.frameY    = i;
			tile.gapX = tile.img->getFrameWidth() * tile.scale * tile.frameX;
			tile.gapY = tile.img->getFrameHeight() * tile.scale * tile.frameY;
			tile.attribute = attribute;
			tile.tileType  = tileType;

			tileVector.push_back(tile);
		}
	}

	_mTile.insert(make_pair(tileName, tileVector));
}


void tile::tileRender(string tileName)
{
	iterTile iter = _mTile.find(tileName);

	if (iter->first == tileName)
	{
		viTile viter = iter->second.begin();

		for (viter; viter != iter->second.end(); ++viter)
		{
			viter->img->frameRender(1.0f, 
				viter->x + viter->gapX,
				viter->y + viter->gapY,
				viter->frameX, viter->frameY,
				0, viter->scale);

			//RECT 확인용
			D2DMANAGER->drawRectangle(D2DMANAGER->createBrush(RGB(0, 255, 0), 0.2f), 
				viter->x + viter->rc.left, 
				viter->y + viter->rc.top,
				viter->x + viter->rc.right, 
				viter->y + viter->rc.bottom);
		}
	}
}

tagTile tile::tileSelect(string tileName)
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
			reRect.left   = viter->x + viter->gapX;
			reRect.top    = viter->y + viter->gapY;
			reRect.right  = viter->x + viter->gapX + viter->img->getFrameWidth();
			reRect.bottom = viter->y + viter->gapY + viter->img->getFrameHeight();

			if (PtInRect(&reRect, _ptMouse))
			{
				D2DMANAGER->drawRectangle(D2DMANAGER->createBrush(RGB(0, 0, 255)),
					viter->x + viter->rc.left,
					viter->y + viter->rc.top,
					viter->x + viter->rc.right,
					viter->y + viter->rc.bottom);

				//tile 정보 입력
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					tmpTile.img = viter->img;
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

					return tmpTile;
				}

				break;
			}
		}
	}

	return tmpTile;
}

void tile::tileDrawFillRc(tagTile selectTile, COLORREF color, float opacity)
{
	D2DMANAGER->fillRectangle(D2DMANAGER->createBrush(color, opacity),
		selectTile.x + selectTile.rc.left,
		selectTile.y + selectTile.rc.top,
		selectTile.x + selectTile.rc.right,
		selectTile.y + selectTile.rc.bottom);
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