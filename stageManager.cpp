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
	stageScale = 3;

	_room1 = new stage;
	_room1->init("room1", stageScale);

	_player1 = new player;
	_player1->init(0, 1.5);


	_collOn = false;

	return S_OK;
}

void stageManager::release()
{

}

void stageManager::update()	
{
	_room1->update(0, 0);
	_player1->update();
	collisionPS(_player1, _room1, stageScale);

}

void stageManager::render()	
{
	//배경색
	D2DMANAGER->fillRectangle(D2DMANAGER->createBrush(RGB(0, 0, 0)), 0, 0, WINSIZEX, WINSIZEY);

	_room1->render();
	_player1->render();




	//======================================== TEST ========================================
	//충돌 확인용
	if (_collOn) D2DMANAGER->drawTextD2d(D2DMANAGER->createBrush(RGB(0, 0, 255)), L"충돌",
		_player1->getRect(BODY_UPBODY).left, _player1->getRect(BODY_UPBODY).top - 50,
		_player1->getRect(BODY_UPBODY).left + 100, _player1->getRect(BODY_UPBODY).top);
}

