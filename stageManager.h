#pragma once
#include "gameNode.h"
#include "stage.h"
#include "player.h"
#include "gameTime.h"
#include "inventory.h"
#include "UIManager.h"


enum COLLISION_DIRECTION
{
	C_NONE,
	C_TOP,
	C_BOTTOM,
	C_LEFT,
	C_RIGHT
};


class stageManager : public gameNode
{
private:
	stage* _room1;
	player* _player1;

	bool _collOn;
	int stageScale;

	POINT _startPoint;

	string _mapFileName;

	float _moveX;
	float _moveY;

	POINT _moveChange;

	//==== keyControl ====
	bool _isLeft;
	bool _isRight;
	bool _isTop;
	bool _isBottom;

	bool _isPlayerMove;
	//====================

	POINT _tilePoint;

	//======= Time =======
	//Day & Night
	bool _isNight;
	int _gRadiusCount;
	float _gradientRadius;

	gameTime* _timer;
	//====================


	//====== Thread ======

	//====================

	//======== UI ========
	UIManager* _ui;
	//====================



public:
	HRESULT init();
	void release();
	void update();
	void render();

	void collisionPS(player* player, stage* room, int scale, bool playerMove);
	void collisionRect(player* player, BODYTYPE bodyType, stage* room, RECTTYPE rectType, float scale);


	void daynNightInit();
	void daynNightSet();
	

	stageManager();
	~stageManager();
};

