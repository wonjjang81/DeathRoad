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

//���� �ִ�
struct tagBodyMove
{
	float speed;
	float fric;
	bool dir;
	int count;
	float saveY;
};

//��ü �ִ�
struct tagPlayerMove
{
	float x, y;
	float speed;
	int count;
	bool keyOn;
};

struct tagAni
{
	int frameX;      //�ִ� �����ӳѹ� 
	int initFrameX;  //���� �����ӳѹ�
	int frameCount;  //������ ī��Ʈ
	bool isInit;     //���� �����ӳѹ� �����
	bool isChange;   //������ �����
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
	bool _bodyFlip;   //�̹��� ����
	tagAni _walkAni;
	tagAni _upHeadAni;
	tagAni _upBodyUpAni;
	//tagAni _upHairAni;
	//tagAni _upGlassAni;
	//tagAni _upHatsAni;

	//==== keyControl ====


public:
	HRESULT init(int playerNum, float startX, float startY, float speed = 1.0f);
	void release();
	void update(bool left, bool top, bool right, bool bottom);
	void render();

	void loadPlayer(charInfo* saveInfo);
	void Stateframe(MOVE_STATE state, MOVE_DIRECTION direction);

	void bodyAni(tagBodyMove& body, float& moveY, int count);
	void totalBodyAni();
	void keyControl(bool left, bool top, bool right, bool bottom);

	void frameAniInit(tagAni& ani);
	void frameAni(string pBodyName, int pBodyIndex, tagAni& ani, int maxFrame, int countTime);
	void frameAniB(string pBodyName, int pBodyIndex, tagAni& ani);

	//========================= getter & setter =========================
	RECT getRect(BODYTYPE type);
	character* getChar() { return _player; }

	POINT getPlayerXY();
	

	player();
	~player();
};

