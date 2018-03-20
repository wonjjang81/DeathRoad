#pragma once
#include "gameNode.h"
#include "character.h"

struct tagBodyname
{
	string head;
	string bodyUp;
	string bodyDw;
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

//부위 애니
struct tagBodyMove
{
	float speed;
	float fric;
	bool dir;
	int count;
};

//전체 애니
struct tagPlayerMove
{
	float x, y;
	float speed;
	int count;
	bool keyOn;
};


class player : public gameNode
{
private:
	character*  _player;
	tagCharInfo _playerInfo;
	tagBodyname _playerBody;

	MOVE_STATE	   _currentState;
	MOVE_DIRECTION _currentDir;

	float _headY;
	tagBodyMove _head;

	float _bodyY;
	tagBodyMove _body;

	tagPlayerMove _pMove;

public:
	HRESULT init(int playerNum);
	void release();
	void update();
	void render();

	void loadPlayer(charInfo* saveInfo);
	void Stateframe(MOVE_STATE state, MOVE_DIRECTION direction);

	void bodyAni(tagBodyMove& body, float& moveY, int count);
	void totalBodyAni();
	void keyControl();

	player();
	~player();
};

