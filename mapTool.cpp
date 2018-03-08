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
	//맵이동
	_moveX = _moveY = 0;
	_moveSpeed = 3.0f;
	//타일맵 뷰어 크기
	_showWindowX = SAMPLETILEX * TILE_SIZEX * 3;
	_showWindowY = SAMPLETILEY * TILE_SIZEY * 3;
	_viewScale = 3;  //타일 스케일


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
	//키조작
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		//예외처리:이동X   (타일크기 X 스케일 X 화면밖 타일수)
		if (abs(_moveX) >= (TILE_SIZEX) * (TILEX - (int)(_showWindowX / (TILE_SIZEX * _viewScale)))) return;
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
		if (abs(_moveY) >= (TILE_SIZEY) * (TILEY - (int)(_showWindowX / (TILE_SIZEY * _viewScale)))) return;
		_moveY -= 1 * _moveSpeed;
	}

	//스케일 조정
	if (KEYMANAGER->isOnceKeyDown('P'))	 _viewScale++;	if (_viewScale >= 5) _viewScale = 5;
	if (KEYMANAGER->isOnceKeyDown('O'))	 _viewScale--;	if (_viewScale <= 2) _viewScale = 2;
}