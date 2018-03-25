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

}

void stage::update(float moveX, float moveY)
{
	_map.x += moveX;
	_map.y += moveY;
}

void stage::render() 
{
	//¸Ê
	_mapRenderer->mapDraw(_newMap->_vSaveTr, _map.x, _map.y, _mapScale);
	_mapRenderer->mapDraw(_newMap->_vSaveRd, _map.x, _map.y, _mapScale);

	_mapRenderer->mapDraw(_newMap->_vSaveWl, _map.x, _map.y, _mapScale);
	_mapRenderer->mapDraw(_newMap->_vSaveBd, _map.x, _map.y, _mapScale);
	_mapRenderer->mapDraw(_newMap->_vSaveFt, _map.x, _map.y, _mapScale);
	_mapRenderer->mapDraw(_newMap->_vSaveIt, _map.x, _map.y, _mapScale);
	_mapRenderer->mapDraw(_newMap->_vSaveWp, _map.x, _map.y, _mapScale);
	
}


void stage::afterRender()
{
	_mapRenderer->mapDraw(_newMap->_vSaveArWl, _map.x, _map.y, _mapScale);
	_mapRenderer->mapDraw(_newMap->_vSaveDr,   _map.x, _map.y, _mapScale);
}


void stage::afterVectorAdd(vSaveTile& vTile)
{
	for (int i = 0; i < vTile.size(); ++i)
	{
		//if (vTile[i].y == )
		//{

		//}
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

