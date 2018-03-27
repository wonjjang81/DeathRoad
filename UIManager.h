#pragma once
#include "gameNode.h"


class UIManager : public gameNode
{
private:
	int _foodNum;
	int _drugNum;
	int _oilNum;
	int _bulletNum;


public:
	HRESULT init();
	void release();
	void update();
	void render();

	void getItem(TYPE_ATTRIBUTE attr);

	UIManager();
	~UIManager();
};

