#include "stdafx.h"
#include "stage.h"


stage::stage()
{
}
stage::~stage()
{
}


HRESULT stage::init(string mapFileName, float scale)
{
	_newMap = new mapLoad;
	_newMap->loadMap(mapFileName);

	_mapRenderer = new mapRender;

	_mapScale = scale;
	_moveX = 0;
	_moveY = 0;

	return S_OK;
}

void stage::release()
{

}

void stage::update(float moveX, float moveY)
{
	_moveX = moveX;
	_moveY = moveY;
}

void stage::render() 
{
	//¸Ê
	_mapRenderer->mapDraw(_newMap->_vSaveTr, _moveX, _moveY, _mapScale);
	_mapRenderer->mapDraw(_newMap->_vSaveRd, _moveX, _moveY, _mapScale);

	_mapRenderer->mapDraw(_newMap->_vSaveWl, _moveX, _moveY, _mapScale);
	_mapRenderer->mapDraw(_newMap->_vSaveBd, _moveX, _moveY, _mapScale);
	_mapRenderer->mapDraw(_newMap->_vSaveFt, _moveX, _moveY, _mapScale);
	_mapRenderer->mapDraw(_newMap->_vSaveIt, _moveX, _moveY, _mapScale);
	_mapRenderer->mapDraw(_newMap->_vSaveWp, _moveX, _moveY, _mapScale);
	_mapRenderer->mapDraw(_newMap->_vSaveDr, _moveX, _moveY, _mapScale);
	_mapRenderer->mapDraw(_newMap->_vSaveArWl, _moveX, _moveY, _mapScale);
}


void stage::afterRender()
{
	
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
		case RECT_DOOR:
			return _newMap->_vSaveDr.size();
		break;
	}
}

