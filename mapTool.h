#pragma once
#include "gameNode.h"
#include "tile.h"
#include "button.h"


class mapTool : public gameNode
{
private:
	//editWindow
	image * _editWindow;

	//keyControl
	float _moveX, _moveY;
	float _moveSpeed;

	//grid
	float _showWindowX, _showWindowY;
	int   _viewScale;

	//버튼
	HWND _bt;


public:
	HRESULT init();
	void release();
	void update();
	void render();

	void gridRender(float scale = 1.0f);  	//타일 그리드맵 렌더
	void mapKeyControl();                   //맵 키 컨트롤
	void selectTile();                      //타일 선택시 화면출력

	mapTool();
	~mapTool();
};

