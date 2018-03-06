#pragma once
#include "gameNode.h"
#include "button.h"


class test02 : public gameNode
{
private:
	float _loopX, _loopY;
	button* _btnSceneChange;



public:
	HRESULT init();
	void release();
	void update();
	void render();

	static void cbSceneChange();


	test02();
	~test02();
};

