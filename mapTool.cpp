#include "stdafx.h"
#include "mapTool.h"


mapTool::mapTool()
{
}
mapTool::~mapTool()
{
}

HRESULT mapTool::init()
{
	//���̵�
	_moveX = _moveY = 0;
	_moveSpeed = 3.0f;
	//Ÿ�ϸ� ��� ũ��
	_showWindowX = SAMPLETILEX * TILE_SIZEX * 3;
	_showWindowY = SAMPLETILEY * TILE_SIZEY * 3;
	_viewScale = 3;  //Ÿ�� ������


	return S_OK;
}

void mapTool::release()
{

}

void mapTool::update() 
{
	mapKeyControl();


}

void mapTool::render() 
{
	gridRender(_viewScale);



}



void mapTool::mapKeyControl()
{
	//Ű����
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		//����ó��:�̵�X   (Ÿ��ũ�� X ������ X ȭ��� Ÿ�ϼ�)
		if (abs(_moveX) >= (TILE_SIZEX) * (TILEX - (int)(_showWindowX / (TILE_SIZEX * _viewScale)))) return;
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
		if (abs(_moveY) >= (TILE_SIZEY) * (TILEY - (int)(_showWindowX / (TILE_SIZEY * _viewScale)))) return;
		_moveY -= 1 * _moveSpeed;
	}

	//������ ����
	if (KEYMANAGER->isOnceKeyDown('P'))	 _viewScale++;	if (_viewScale >= 5) _viewScale = 5;
	if (KEYMANAGER->isOnceKeyDown('O'))	 _viewScale--;	if (_viewScale <= 2) _viewScale = 2;
}