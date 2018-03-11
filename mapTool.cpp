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
	gameNode::init();

	//에디트창
	_editWindow = IMAGEMANAGER->findImage("맵툴창");

	//맵이동
	_moveX = _moveY = 0;
	_moveSpeed = 3.0f;

	//타일맵 뷰어 크기
	_showWindowX = SAMPLETILEX * TILE_SIZEX * 3;
	_showWindowY = SAMPLETILEY * TILE_SIZEY * 3;
	_viewScale = 3;  //타일 스케일

	//버튼
	btnSetup();

	//메뉴


	//타일 그리기
	ZeroMemory(&_drawTile, sizeof(tagTile));
	_menuTabOn = false;

	return S_OK;
}

void mapTool::release()
{

}

void mapTool::update() 
{
	gameNode::update();

	mapKeyControl();  //타일맵 키 컨트롤
	btnUpdate();      //메뉴 버튼
	menuAddChild();   //메뉴타입별 샘플타일 생성(차일드씬으로 구성)
}

void mapTool::render() 
{
	_editWindow->render(1.0f, 720, 0); //메뉴
	gridRender(_viewScale);            //타일맵 그리드
	selectTile(_viewScale);            //타일맵 선택
	btnRender();					   //메뉴 버튼
	menuRender();                      //메뉴 창
	tileDraw(_viewScale);              //타일 그리기

	gameNode::render();                //샘플 타일탭
}





