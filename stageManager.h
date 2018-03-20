#pragma once
#include "gameNode.h"
#include "stage.h"
#include "player.h"



class stageManager : public gameNode
{
private:
	stage* _room1;
	player* _player1;

public:
	HRESULT init();
	void release();
	void update();
	void render();


	stageManager();
	~stageManager();
};

