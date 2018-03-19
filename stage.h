#pragma once
#include "gameNode.h"
#include "mapLoad.h"
#include "mapRender.h"


class stage : public gameNode
{
private:
	mapLoad * _newMap;
	mapRender* _mapRenderer;

	float _mapScale;
	float _moveX, _moveY;

public:
	HRESULT init(string mapFileName, float scale);
	void release();
	void update(float moveX, float moveY);
	void render();


	stage();
	~stage();
};

