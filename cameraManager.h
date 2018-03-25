#pragma once
#include "singletonBase.h"


class cameraManager : public singletonBase<cameraManager>
{
private:
	RECT _camRc;

	POINT _moveTIle;
	POINT _player;
	float _moveSpeed;
	float _camScale;

public:
	HRESULT init();
	void release();
	void render();

	void charMove(bool& left, bool& top, bool& right, bool& bottom);

	POINT tileCamMove() { return _moveTIle; }
	void getPlayerXY(float playerX, float playerY);


	cameraManager();
	~cameraManager();
};


