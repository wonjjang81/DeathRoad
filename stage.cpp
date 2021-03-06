#include "stdafx.h"
#include "stage.h"


stage::stage()
{
}
stage::~stage()
{
}


HRESULT stage::init(string mapFileName, float mapX, float mapY, float scale)
{
	_newMap = new mapLoad;
	_newMap->loadMap(mapFileName);

	_mapRenderer = new mapRender;

	_mapScale = scale;

	_map.x = mapX;
	_map.y = mapY;


	_startPoint = _newMap->getStartPoint();

	return S_OK;
}

void stage::release()
{
	SAFE_DELETE(_mapRenderer);
	SAFE_DELETE(_newMap);
}

void stage::update(float moveX, float moveY)
{
	_map.x += moveX;
	_map.y += moveY;
}

void stage::render() 
{
	//맵
	_mapRenderer->mapDraw(_newMap->_vSaveTr, _map.x, _map.y, _mapScale);
	_mapRenderer->mapDraw(_newMap->_vSaveRd, _map.x, _map.y, _mapScale);

	_mapRenderer->mapDraw(_newMap->_vSaveWl, _map.x, _map.y, _mapScale);
	_mapRenderer->mapDraw(_newMap->_vSaveBd, _map.x, _map.y, _mapScale);
	_mapRenderer->mapDraw(_newMap->_vSaveFt, _map.x, _map.y, _mapScale);
	_mapRenderer->mapDraw(_newMap->_vSaveIt, _map.x, _map.y, _mapScale);
	_mapRenderer->mapDraw(_newMap->_vSaveWp, _map.x, _map.y, _mapScale);

	_mapRenderer->mapDraw(_newMap->_vSaveArWl, _map.x, _map.y, _mapScale);
	_mapRenderer->mapDraw(_newMap->_vSaveDr,   _map.x, _map.y, _mapScale);
	
}


void stage::afterRender()
{
	_mapRenderer->mapDraw(_newMap->_vSaveWl, _map.x, _map.y, _mapScale, true);
	_mapRenderer->mapDraw(_newMap->_vSaveBd, _map.x, _map.y, _mapScale, true);
	_mapRenderer->mapDraw(_newMap->_vSaveFt, _map.x, _map.y, _mapScale, true);
	_mapRenderer->mapDraw(_newMap->_vSaveIt, _map.x, _map.y, _mapScale, true);
	_mapRenderer->mapDraw(_newMap->_vSaveWp, _map.x, _map.y, _mapScale, true);

	_mapRenderer->mapDraw(_newMap->_vSaveArWl, _map.x, _map.y, _mapScale, true);
	_mapRenderer->mapDraw(_newMap->_vSaveDr,   _map.x, _map.y, _mapScale, true);
}


void stage::afterVectorAdd(vSaveTile& vTile)
{
	for (int i = 0; i < vTile.size(); ++i)
	{



	}
}


RECT stage::getRect(RECTTYPE type, int i)
{
	switch (type)
	{
		case RECT_FURNITURE:
			return _newMap->_vSaveFt[i].rc;
		break;
		case RECT_ITEM:
			return _newMap->_vSaveIt[i].rc;
		break;
		case RECT_WEAPON:
			return _newMap->_vSaveWp[i].rc;
		break;
		case RECT_WALL:
			return _newMap->_vSaveWl[i].rc;
		break;
		case RECT_WALL2:
			return _newMap->_vSaveArWl[i].rc;
		break;
		case RECT_DOOR:
			return _newMap->_vSaveDr[i].rc;
		break;
	}
}


int stage::getVectorSize(RECTTYPE type)
{
	switch (type)
	{
		case RECT_FURNITURE:
			return _newMap->_vSaveFt.size();
		break;
		case RECT_ITEM:
			return _newMap->_vSaveIt.size();
		break;
		case RECT_WEAPON:
			return _newMap->_vSaveWp.size();
		break;
		case RECT_WALL:
			return _newMap->_vSaveWl.size();
		break;
		case RECT_WALL2:
			return _newMap->_vSaveArWl.size();
		break;
		case RECT_DOOR:
			return _newMap->_vSaveDr.size();
		break;
	}
}


tagTile stage::getTileInfo(RECTTYPE type, int i)
{
	tagTile tmpTile;
	ZeroMemory(&tmpTile, sizeof(tagTile));

	switch (type)
	{
		case RECT_FURNITURE:
			if (_newMap->_vSaveFt.size() == 0) break;

			tmpTile.tileType  = _newMap->_vSaveFt[i].tileType;
			tmpTile.attribute = _newMap->_vSaveFt[i].attribute;
			tmpTile.typeAtt   = _newMap->_vSaveFt[i].typeAtt;
			tmpTile.typeAtt2  = _newMap->_vSaveFt[i].typeAtt2;
			sprintf(tmpTile.imgName, "%s", _newMap->_vSaveFt[i].imgName);
			tmpTile.index     = _newMap->_vSaveFt[i].index;

			return tmpTile;
		break;
		case RECT_ITEM:
			if (_newMap->_vSaveIt.size() == 0) break;

			tmpTile.tileType  = _newMap->_vSaveIt[i].tileType;
			tmpTile.attribute = _newMap->_vSaveIt[i].attribute;
			tmpTile.typeAtt   = _newMap->_vSaveIt[i].typeAtt;
			tmpTile.typeAtt2  = _newMap->_vSaveIt[i].typeAtt2;
			sprintf(tmpTile.imgName, "%s", _newMap->_vSaveIt[i].imgName);
			tmpTile.index     = _newMap->_vSaveIt[i].index;

			return tmpTile;
		break;
		case RECT_WEAPON:
			if (_newMap->_vSaveWp.size() == 0) break;

			tmpTile.tileType  = _newMap->_vSaveWp[i].tileType;
			tmpTile.attribute = _newMap->_vSaveWp[i].attribute;
			tmpTile.typeAtt   = _newMap->_vSaveWp[i].typeAtt;
			tmpTile.typeAtt2  = _newMap->_vSaveWp[i].typeAtt2;
			sprintf(tmpTile.imgName, "%s", _newMap->_vSaveWp[i].imgName);
			tmpTile.index     = _newMap->_vSaveWp[i].index;
			tmpTile.frameX	  = _newMap->_vSaveWp[i].frameX;
			tmpTile.frameY	  = _newMap->_vSaveWp[i].frameY;

			return tmpTile;
		break;
	}
}


void stage::removeVItem(RECTTYPE type, int i)
{
	switch (type)
	{
		case RECT_FURNITURE:
			if (_newMap->_vSaveFt.size() == 0) break;


		break;
		case RECT_ITEM:
			if (_newMap->_vSaveIt.size() == 0) break;

			_newMap->_vSaveIt.erase(_newMap->_vSaveIt.begin() + i);
			

		break;
		case RECT_WEAPON:
			if (_newMap->_vSaveWp.size() == 0) break;

			_newMap->_vSaveWp.erase(_newMap->_vSaveWp.begin() + i);

		break;
	}
}

void stage::setVtilePush(RECTTYPE type, tagTile newTile)
{
	switch (type)
	{
		case RECT_FURNITURE:
			_newMap->_vSaveFt.push_back(newTile);
		break;
		case RECT_ITEM:
			_newMap->_vSaveIt.push_back(newTile);
		break;
		case RECT_WEAPON:
			_newMap->_vSaveWp.push_back(newTile);
		break;
		case RECT_WALL:
			_newMap->_vSaveWl.push_back(newTile);
		break;
		case RECT_WALL2:
			_newMap->_vSaveArWl.push_back(newTile);
		break;
		case RECT_DOOR:
			_newMap->_vSaveDr.push_back(newTile);
		break;
	}
}

void stage::setVtileCopy(RECTTYPE type, int i, tagTile newTile)
{
	switch (type)
	{
		case RECT_FURNITURE:
			//특정 정보만 복사
			_newMap->_vSaveFt[i].x = newTile.x;
			_newMap->_vSaveFt[i].y = newTile.y;
			_newMap->_vSaveFt[i].centerX = newTile.centerX;
			_newMap->_vSaveFt[i].centerY = newTile.centerY;
			_newMap->_vSaveFt[i].rc = newTile.rc;
			_newMap->_vSaveFt[i].cRc = newTile.cRc;
		break;
		case RECT_ITEM:
			_newMap->_vSaveIt[i] = newTile;
		break;
		case RECT_WEAPON:
			_newMap->_vSaveWp[i] = newTile;
		break;
		case RECT_WALL:
			_newMap->_vSaveWl[i] = newTile;
		break;
		case RECT_WALL2:
			_newMap->_vSaveArWl[i] = newTile;
		break;
		case RECT_DOOR:
			_newMap->_vSaveDr[i] = newTile;
		break;
	}
}
