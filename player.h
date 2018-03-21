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
	float saveY;
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

	//==== BodyAni ====
	float _headY;
	tagBodyMove _head;

	float _bodyY;
	tagBodyMove _body;
	//=================

	//player Move
	tagPlayerMove _pMove;

	//player FrameAni
	int _frameX;
	int _initFrameX;
	int _frmaeCount;
	bool _isInit;


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

	void walkAni(string pBodyName, int pBodyIndex);


	player();
	~player();
};

