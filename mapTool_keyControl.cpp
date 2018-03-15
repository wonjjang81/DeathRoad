#include "stdafx.h"
#include "mapTool.h"


void mapTool::mapKeyControl()
{
	//키조작
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		//예외처리:이동X   (타일크기 X 스케일 X 화면밖 타일수)
		if (abs(_moveX) >= (TILE_SIZEX) * (_tileX - (int)(_showWindowX / (TILE_SIZEX * _viewScale)))) return;
		_moveX -= 1 * _moveSpeed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (_moveX >= 0) return;  //예외처리:이동X 
		_moveX += 1 * _moveSpeed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (_moveY >= 0) return;  //예외처리:이동X 
		_moveY += 1 * _moveSpeed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		//예외처리:이동X   (타일크기 X 스케일 X 화면밖 타일수)
		if (abs(_moveY) >= (TILE_SIZEY) * (_tileY - (int)(_showWindowY / (TILE_SIZEY * _viewScale)))) return;
		_moveY -= 1 * _moveSpeed;
	}

	//스케일 조정
	if (KEYMANAGER->isOnceKeyDown('P'))	 _viewScale++;	if (_viewScale >= 5) _viewScale = 5;
	if (KEYMANAGER->isOnceKeyDown('O'))	 _viewScale--;	if (_viewScale <= 2) _viewScale = 2;
}