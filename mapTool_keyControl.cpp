#include "stdafx.h"
#include "mapTool.h"


void mapTool::mapKeyControl()
{
	//Ű����
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		//����ó��:�̵�X   (Ÿ��ũ�� X ������ X ȭ��� Ÿ�ϼ�)
		if (abs(_moveX) >= (TILE_SIZEX) * (_tileX - (int)(_showWindowX / (TILE_SIZEX * _viewScale)))) return;
		_moveX -= 1 * _moveSpeed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (_moveX >= 0) return;  //����ó��:�̵�X 
		_moveX += 1 * _moveSpeed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (_moveY >= 0) return;  //����ó��:�̵�X 
		_moveY += 1 * _moveSpeed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		//����ó��:�̵�X   (Ÿ��ũ�� X ������ X ȭ��� Ÿ�ϼ�)
		if (abs(_moveY) >= (TILE_SIZEY) * (_tileY - (int)(_showWindowY / (TILE_SIZEY * _viewScale)))) return;
		_moveY -= 1 * _moveSpeed;
	}

	//������ ����
	if (KEYMANAGER->isOnceKeyDown('P'))	 _viewScale++;	if (_viewScale >= 5) _viewScale = 5;
	if (KEYMANAGER->isOnceKeyDown('O'))	 _viewScale--;	if (_viewScale <= 2) _viewScale = 2;
}