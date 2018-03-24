#pragma once
#include "gameNode.h"
#include "stage.h"
#include "player.h"


class stageManager : public gameNode
{
private:
	stage* _room1;
	player* _player1;

	bool _collOn;
	int stageScale;

	POINT _startPoint;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void collisionPS(player* player, stage* room, int scale);
	void collisionRect(player* player, BODYTYPE bodyType, stage* room, RECTTYPE rectType, float scale);
	

	stageManager();
	~stageManager();
};

