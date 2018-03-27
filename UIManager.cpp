#include "stdafx.h"
#include "UIManager.h"


UIManager::UIManager()
{
}
UIManager::~UIManager()
{
}


HRESULT UIManager::init()
{
	_foodNum   = 0;
	_drugNum   = 0;
	_oilNum    = 0;
	_bulletNum = 0;


	return S_OK;
}

void UIManager::release()
{

}

void UIManager::update() 
{
	
}

void UIManager::render() 
{

}


void UIManager::getItem(TYPE_ATTRIBUTE attr)
{

}

