#include "stdafx.h"
#include "cameraManager.h"


cameraManager::cameraManager()
{
}
cameraManager::~cameraManager()
{
}


HRESULT cameraManager::init()
{
	float rcWidth  = 300;
	float rcHeight = 300;

	_camRc.left	  = (WINSIZEX - rcWidth) / 2;
	_camRc.top	  = (WINSIZEY - rcHeight) / 2;
	_camRc.right  = _camRc.left + rcWidth;
	_camRc.bottom = _camRc.top + rcHeight;

	_moveSpeed = 1.0f;
	_moveTIle.x = 0.0f;
	_moveTIle.y = 0.0f;


	return S_OK;
}

void cameraManager::release()
{

}


void cameraManager::render()
{
	//카메라 범위
	//D2DMANAGER->drawRectangle(D2DMANAGER->createBrush(RGB(0, 0, 255)), _camRc.left, _camRc.top, _camRc.right, _camRc.bottom);
}



void cameraManager::charMove(bool& left, bool& top, bool& right, bool& bottom, bool move)
{

	left   = false;
	top    = false;
	right  = false;
	bottom = false;
	ZeroMemory(&_moveTIle, sizeof(_moveTIle));

	//좌
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _camMoveOn.left)
	{
		if (move) left = true;

		_moveTIle.x += 1 * _moveSpeed;
	}


	//우
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _camMoveOn.right)
	{
		if (move) right = true;

		_moveTIle.x -= 1 * _moveSpeed;
	}


	//상
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _camMoveOn.top)
	{
		if (move) top = true;

		_moveTIle.y += 1 * _moveSpeed;
	}


	//하
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _camMoveOn.bottom)
	{
		if (move) bottom = true;

		_moveTIle.y -= 1 * _moveSpeed;
	}

}


void cameraManager::getPlayerXY(float playerX, float playerY)
{
	_player.x = playerX;
	_player.y = playerY;
}