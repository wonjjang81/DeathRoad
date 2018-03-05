#pragma once
#include "gameNode.h"


class testScene : public gameNode
{
private:


public:
	HRESULT init();
	void release();
	void update();
	void render();


	testScene();
	~testScene();
};

