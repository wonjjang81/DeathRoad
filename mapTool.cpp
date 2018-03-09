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
	//에디트창
	_editWindow = IMAGEMANAGER->findImage("맵툴창");

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
	selectTile();

}

void mapTool::render() 
{
	_editWindow->render(1.0, 720, 0);
	gridRender(_viewScale);



}


void mapTool::selectTile()
{

}

