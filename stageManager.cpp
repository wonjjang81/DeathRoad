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
	_room1 = new stage;
	_room1->init("room1", 3);



	return S_OK;
}

void stageManager::release()
{

}

void stageManager::update()	
{
	_room1->update(0, 0);



}

void stageManager::render()	
{
	//¹è°æ»ö
	D2DMANAGER->fillRectangle(D2DMANAGER->createBrush(RGB(0, 0, 0)), 0, 0, WINSIZEX, WINSIZEY);

	_room1->render();



}

