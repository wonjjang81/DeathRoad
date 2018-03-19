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
	_mapRenderer->mapDraw(_newMap->_vSaveBd, _moveX, _moveY, _mapScale);
	_mapRenderer->mapDraw(_newMap->_vSaveFt, _moveX, _moveY, _mapScale);
	_mapRenderer->mapDraw(_newMap->_vSaveIt, _moveX, _moveY, _mapScale);
	_mapRenderer->mapDraw(_newMap->_vSaveWp, _moveX, _moveY, _mapScale);
}
