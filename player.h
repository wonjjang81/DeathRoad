#pragma once
#include "gameNode.h"
#include "character.h"

struct tagBodyname
{
	string head;
	string body;
	string hair;
	string glass;
	string hats;
};

enum MOVE_STATE
{
	STATE_IDLE,
	STATE_WALK,
	STATE_DAMAGE,
};

enum MOVE_DIRECTION
{
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
	DIRECTION_UP,
	DIRECTION_DOWN,
};


class player : public gameNode
{
private:
	character* _player;
	tagCharInfo _playerInfo;
	tagBodyname _playerBody;

public:
	HRESULT init(int playerNum);
	void release();
	void update();
	void render();

	void loadPlayer(charInfo* saveInfo);
	void Stateframe(MOVE_STATE state, MOVE_DIRECTION direction);

	player();
	~player();
};

