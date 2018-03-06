#pragma once
#include "gameNode.h"
#include "test02.h"



class testScene : public gameNode
{
private:
	float moveX;
	float moveY;
	float angle;

	test02* _t2;
	image* _camel;
	animation*  _ani1;

	float _degree;

public:
	HRESULT init();
	void release();
	void update();
	void render();


	testScene();
	~testScene();
};

