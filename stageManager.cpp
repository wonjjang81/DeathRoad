#include "stdafx.h"
#include "stageManager.h"


stageManager::stageManager()
{
}
stageManager::~stageManager()
{
}


HRESULT stageManager::init()
{
	_mapFileName = "room1";
	stageScale = 3;

	//타일 화면 중앙으로
	string tmpFileName;
	tmpFileName.append("map//");
	tmpFileName.append(_mapFileName);
	int tileX = INIDATA->loadDataInterger(tmpFileName.c_str(), "mapData", "tileX");
	int tileY = INIDATA->loadDataInterger(tmpFileName.c_str(), "mapData", "tileY");
	_moveX = (WINSIZEX - tileX * TILE_SIZEX * stageScale) / 2;
	_moveY = (WINSIZEY - tileY * TILE_SIZEY * stageScale) / 2;


	_room1 = new stage;
	_room1->init(_mapFileName, _moveX, _moveY, stageScale);

	_startPoint.x = _room1->getStartPoint().x * stageScale + _moveX;
	_startPoint.y = _room1->getStartPoint().y * stageScale + _moveY;

	_player1 = new player;
	_player1->init(0, _startPoint.x, _startPoint.y, 1.5);


	_isLeft   = true;
	_isRight  = true;
	_isTop    = true;
	_isBottom = true;


	_collOn = false;



	return S_OK;
}

void stageManager::release()
{

}

void stageManager::update()	
{
	_player1->update(_isLeft, _isTop, _isRight, _isBottom);

	collisionPS(_player1, _room1, stageScale);

	CAMERAMANAGER->getPlayerXY(_player1->getPlayerXY().x, _player1->getPlayerXY().y);

	_room1->update(CAMERAMANAGER->tileCamMove().x, CAMERAMANAGER->tileCamMove().y);
}

void stageManager::render()	 
{
	//배경색
	D2DMANAGER->fillRectangle(D2DMANAGER->createBrush(RGB(0, 0, 0)), 0, 0, WINSIZEX, WINSIZEY);

	_room1->render();
	_player1->render();
	_room1->afterRender();

	D2DMANAGER->opacityMask(_player1->getPlayerXY().x + 20, _player1->getPlayerXY().y + 20);


	//======================================== TEST ========================================
	//충돌 확인용
	if (_collOn) D2DMANAGER->drawTextD2d(D2DMANAGER->createBrush(RGB(0, 0, 255)), L"충돌",
		_player1->getRect(BODY_UPBODY).left, _player1->getRect(BODY_UPBODY).top - 50,
		_player1->getRect(BODY_UPBODY).left + 100, _player1->getRect(BODY_UPBODY).top);

	CAMERAMANAGER->render();
}

