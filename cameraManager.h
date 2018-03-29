#pragma once
#include "singletonBase.h"




class cameraManager : public singletonBase<cameraManager>
{
private:
	typedef struct tagCameraMove
	{
		bool left;
		bool right;
		bool top;
		bool bottom;

		tagCameraMove()
		{
			left   = true;
			right  = true;
			top    = true;
			bottom = true;
		}
	};

	tagCameraMove _camMoveOn;

	RECT _camRc;

	POINT _moveTIle;
	POINT _player;
	float _moveSpeed;
	float _camScale;



public:
	HRESULT init();
	void release();
	void render();

	void charMove(bool& left, bool& top, bool& right, bool& bottom, bool move);


	//========================= getter & setter =========================
	POINT tileCamMove() { return _moveTIle; }
	void getPlayerXY(float playerX, float playerY);

	void setCamMoveLeftOn(bool left)     { _camMoveOn.left   = left; }
	void setCamMoveRightOn(bool right)   { _camMoveOn.right  = right; }
	void setCamMoveTopOn(bool top)       { _camMoveOn.top    = top; }
	void setCamMoveBottomOn(bool bottom) { _camMoveOn.bottom = bottom; }


	cameraManager();
	~cameraManager();
};


