#pragma once
#include "gameNode.h"


class player : public gameNode
{
private:



public:
	HRESULT init();
	void release();
	void update();
	void render();

	player();
	~player();
};

