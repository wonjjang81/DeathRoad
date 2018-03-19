#pragma once
#include "gameNode.h"
#include "stage.h"



class stageManager : public gameNode
{
private:
	stage* _room1;

public:
	HRESULT init();
	void release();
	void update();
	void render();


	stageManager();
	~stageManager();
};

