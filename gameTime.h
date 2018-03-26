#pragma once
#include "gameNode.h"


class gameTime : public gameNode
{
private:
	float _second;
	int   _minute;
	int   _hour;
	int   _day;

	int   _reTime;

	bool  _isCount;

	POINT _cPosition;


public:
	HRESULT init();
	void release();
	void update();
	void render();


	//========================= getter & setter =========================
	int getHour() { return _hour; }

	gameTime();
	~gameTime();
};

