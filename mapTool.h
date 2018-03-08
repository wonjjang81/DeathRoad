#pragma once
#include "gameNode.h"
#include "tile.h"


class mapTool : public gameNode
{
private:
	float _moveX, _moveY;
	float _moveSpeed;
	float _showWindowX, _showWindowY;
	int   _tileScale;

public:
	HRESULT init();
	void release();
	void update();
	void render();


	void gridRender(float scale = 1.0f);  	//Å¸ÀÏ ±×¸®µå¸Ê ·»´õ
	void mapKeyControl();                   //¸Ê Å° ÄÁÆ®·Ñ

	mapTool();
	~mapTool();
};

