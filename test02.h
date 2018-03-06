#pragma once
#include "gameNode.h"


class test02 : public gameNode
{
private:
	float _loopX, _loopY;


public:
	HRESULT init();
	void release();
	void update();
	void render();


	test02();
	~test02();
};

