#pragma once
#include "gameNode.h"
#include "tile.h"


class mapTool : public gameNode
{
private:




public:
	HRESULT init();
	void release();
	void update();
	void render();

	void gridRender();

	mapTool();
	~mapTool();
};

