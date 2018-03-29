#include "stdafx.h"
#include "player.h"


player::player()
{
}
player::~player()
{
}


HRESULT player::init(int playerNum, float startX, float startY, float speed)
{
	_player = new character;

	//저장한 플레이어 데이터 로드
	loadPlayer(DATABASE->player[playerNum]);

	_player->charSetup(_playerInfo.charTypeName, startX, startY, 3);

	_headY = 0;
	_bodyY = 0;
	_walkY = 0;

	//머리Ani
	_head.speed = 0.3f;
	_head.fric  = 0.017f;
	_head.dir   = false;
	_head.count = 1;

	//몸통Ani
	_body.speed = 0.3f;
	_body.fric  = 0.015;
	_body.dir   = false;
	_body.count = 1;

	//WalkAni
	_walk.speed = 0.7f;
	_walk.fric = 0.015;
	_walk.dir = false;
	_walk.count = 1;

	//전체Ani
	_pMove.x = 0;
	_pMove.y = 0;
	_pMove.speed = 0.7f * speed;
	_pMove.count = 1;
	_pMove.keyOn = false;

	_pMove.x = _player->getX(_playerBody.head, _playerInfo.headIndex);
	_pMove.y = _player->getY(_playerBody.head, _playerInfo.headIndex);

	//현재상태
	_currentState = STATE_IDLE;
	_currentDir = DIRECTION_UP;

	//player moveAni
	_bodyFlip = false;

	frameAniInit(_walkAni);
	frameAniInit(_upHeadAni);
	frameAniInit(_upBodyUpAni);
	//frameAniInit(_upHairAni);
	//frameAniInit(_upGlassAni);
	//frameAniInit(_upHatsAni);



	return S_OK;
}

void player::release()
{

}

void player::update(bool left, bool top, bool right, bool bottom)
{
	keyControl(left, top, right, bottom);
	Stateframe(_currentState, _currentDir);
}

void player::render()
{
	_player->charRender(_playerBody.bodyDw, _playerInfo.dwBodyIndex, _bodyFlip);	//하체
	_player->charRender(_playerBody.bodyUp, _playerInfo.upBodyIndex, _bodyFlip);    //상체
	_player->charRender(_playerBody.head,   _playerInfo.headIndex,   _bodyFlip);	//머리
	_player->charRender(_playerBody.hair,   _playerInfo.hairIndex,   _bodyFlip);	//헤어
	_player->charRender(_playerBody.glass,  _playerInfo.glassIndex,  _bodyFlip);	//안경
	_player->charRender(_playerBody.hats,   _playerInfo.hatsIndex,   _bodyFlip);	//모자
}







//내부 데이터베이스 정보 로드
void  player::loadPlayer(charInfo* saveInfo)
{
	_playerInfo.charTypeName = saveInfo->charTypeName;
	_playerBody.head    = _player->bodyNameChange(_playerInfo.charTypeName, BODY_HEAD);
	_playerBody.bodyUp  = _player->bodyNameChange(_playerInfo.charTypeName, BODY_UPBODY);
	_playerBody.bodyDw  = _player->bodyNameChange(_playerInfo.charTypeName, BODY_DWBODY);
	_playerBody.hair    = _player->bodyNameChange(_playerInfo.charTypeName, BODY_HAIR);
	_playerBody.glass   = _player->bodyNameChange(_playerInfo.charTypeName, BODY_GLASS);
	_playerBody.hats    = _player->bodyNameChange(_playerInfo.charTypeName, BODY_HATS);

	_playerInfo.headIndex   = saveInfo->headIndex;
	_playerInfo.upBodyIndex = saveInfo->upBodyIndex;
	_playerInfo.dwBodyIndex = saveInfo->dwBodyIndex;
	_playerInfo.hairIndex   = saveInfo->hairIndex;
	_playerInfo.glassIndex  = saveInfo->glassIndex;
	_playerInfo.hatsIndex   = saveInfo->hatsIndex;
}

//상태값에 따른 프레임 변경
void player::Stateframe(MOVE_STATE state, MOVE_DIRECTION direction)
{
	switch (state)
	{
		case STATE_IDLE:
			totalBodyAni();
			//walkAni 초기화
			_player->setFrameX(_playerBody.bodyDw, _playerInfo.dwBodyIndex, _walkAni.initFrameX);

			switch (direction)
			{
				case DIRECTION_LEFT:
					_bodyFlip = true;
				break;
				case DIRECTION_RIGHT:
					_bodyFlip = false;
				break;
				case DIRECTION_UP:
					_upHeadAni.isChange = true;
					_upBodyUpAni.isChange = true;
				break;
				case DIRECTION_DOWN:
					_upHeadAni.isChange = false;
					_upBodyUpAni.isChange = false;
				break;
			}
		break;
		case STATE_WALK:

			totalBodyAni();
			walkBodyAni();
			frameAni(_playerBody.bodyDw, _playerInfo.dwBodyIndex, _walkAni, 2, 10);

			switch (direction)
			{
				case DIRECTION_LEFT:
					_bodyFlip = true;
				break;
				case DIRECTION_RIGHT:
					_bodyFlip = false;
				break;
				case DIRECTION_UP:
					_upHeadAni.isChange = true;
					_upBodyUpAni.isChange = true;
				break;
				case DIRECTION_DOWN:
					_upHeadAni.isChange = false;
					_upBodyUpAni.isChange = false;
				break;
			}

		break;
		case STATE_DAMAGE:
			switch (direction)
			{
				case DIRECTION_LEFT:
					_bodyFlip = true;
				break;
				case DIRECTION_RIGHT:
					_bodyFlip = false;
				break;
				case DIRECTION_UP:
					_upHeadAni.isChange = true;
				break;
				case DIRECTION_DOWN:
					_upHeadAni.isChange = false;
				break;
			}
		break;
	}

	//상하 애니
	frameAniB(_playerBody.head,   _playerInfo.headIndex,   _upHeadAni);
	frameAniB(_playerBody.bodyUp, _playerInfo.upBodyIndex, _upBodyUpAni);
	frameAniB(_playerBody.hair,	  _playerInfo.hairIndex,   _upHeadAni);
	frameAniB(_playerBody.glass,  _playerInfo.glassIndex,  _upHeadAni);
	frameAniB(_playerBody.hats,   _playerInfo.hatsIndex,   _upHeadAni);
}


void player::bodyAni(tagBodyMove& body, float& moveY, int count)
{
	//증가한 y값만큼 다시 돌아오도록...

	body.count++;

	if (body.count % count == 0)
	{
		if (body.dir)
		{
			moveY += body.speed * 0.04;
			body.speed -= body.fric;

			if (body.speed <= 0)
			{
				moveY = 0;
				body.speed = 0.3f;
				body.dir = false;
			}
		}
		else
		{
			moveY -= body.speed * 0.04;
			body.speed -= body.fric;

			if (body.speed <= 0)
			{
				moveY = 0;
				body.speed = 0.3f;
				body.dir = true;
			}
		}
	}
}

void player::totalBodyAni()
{
	bodyAni(_head, _headY, 3);
	_player->setBodyY(_playerBody.head,  _playerInfo.headIndex,  _headY);	 //머리
	_player->setBodyY(_playerBody.hair,  _playerInfo.hairIndex,  _headY);	 //헤어
	_player->setBodyY(_playerBody.glass, _playerInfo.glassIndex, _headY);	 //안경
	_player->setBodyY(_playerBody.hats,  _playerInfo.hatsIndex,  _headY);	 //모자

	bodyAni(_body, _bodyY, 2);
	_player->setBodyY(_playerBody.bodyUp, _playerInfo.upBodyIndex, _bodyY);  //상체
}

void player::walkBodyAni()
{
	bodyAni(_walk, _walkY, 3);



}

void player::keyControl(bool left, bool top, bool right, bool bottom)
{
	_currentState = STATE_IDLE;
	_currentDir = DIRECTION_DOWN;

	//좌
	if (left)
	{
		_currentState = STATE_WALK;
		_currentDir = DIRECTION_LEFT;
		//_pMove.x -= _pMove.speed;
	}


	//우
	if (right)
	{
		_currentState = STATE_WALK;
		_currentDir = DIRECTION_RIGHT;
		//_pMove.x += _pMove.speed;
	}


	//상
	if (top)
	{
		_currentState = STATE_WALK;
		_currentDir = DIRECTION_UP;
		//_pMove.y -= _pMove.speed;
	}


	//하
	if (bottom)
	{
		_currentState = STATE_WALK;
		_currentDir = DIRECTION_DOWN;
		//_pMove.y += _pMove.speed;
	}


	_player->setX(_playerBody.head,   _playerInfo.headIndex,   _pMove.x);
	_player->setX(_playerBody.hair,   _playerInfo.hairIndex,   _pMove.x);
	_player->setX(_playerBody.glass,  _playerInfo.glassIndex,  _pMove.x);
	_player->setX(_playerBody.hats,   _playerInfo.hatsIndex,   _pMove.x);
	_player->setX(_playerBody.bodyUp, _playerInfo.upBodyIndex, _pMove.x);
	_player->setX(_playerBody.bodyDw, _playerInfo.dwBodyIndex, _pMove.x);

	_player->setY(_playerBody.head,   _playerInfo.headIndex,   _pMove.y);
	_player->setY(_playerBody.hair,   _playerInfo.hairIndex,   _pMove.y);
	_player->setY(_playerBody.glass,  _playerInfo.glassIndex,  _pMove.y);
	_player->setY(_playerBody.hats,   _playerInfo.hatsIndex,   _pMove.y);
	_player->setY(_playerBody.bodyUp, _playerInfo.upBodyIndex, _pMove.y);
	_player->setY(_playerBody.bodyDw, _playerInfo.dwBodyIndex, _pMove.y);
}

//애니 초기화
void player::frameAniInit(tagAni& ani)
{
	ani.frameX = 0;
	ani.initFrameX = 0;
	ani.frameCount = 1;
	ani.isInit = false;
	ani.isChange = false;
}

//애니메이션 타입A: downBody
void player::frameAni(string pBodyName, int pBodyIndex, tagAni& ani, int maxFrame, int countTime)
{
	ani.frameCount++;

	if (!ani.isInit)
	{
		ani.frameX = _player->getFrameX(pBodyName, pBodyIndex);
		ani.initFrameX = ani.frameX;
		ani.isInit = true;
	}
	if (ani.frameX > ani.initFrameX + maxFrame) ani.frameX = ani.initFrameX;


	if (ani.frameCount % countTime == 0)
	{
		_player->setFrameX(pBodyName, pBodyIndex, ani.frameX);
		ani.frameX++;
		ani.frameCount = 1;
	}
}

//애니메이션 타입B
void player::frameAniB(string pBodyName, int pBodyIndex, tagAni& ani)
{
	//프레임 추가
	if (ani.isChange && ani.frameX == ani.initFrameX) ani.frameX++;

	if (!ani.isInit)
	{
		//프레임 초기값 저장
		ani.frameX = _player->getFrameX(pBodyName, pBodyIndex);
		ani.initFrameX = ani.frameX;
		ani.isInit = true;
	}

	//프레임 초기화
	if (!ani.isChange)
	{
		ani.frameX = ani.initFrameX;
	}

	//프레임 셋팅
	_player->setFrameX(pBodyName, pBodyIndex, ani.frameX);
	
}


RECT player::getRect(BODYTYPE type)
{
	switch (type)
	{
		//타격충돌
		case BODY_UPBODY: 
			return _player->getRect(_playerBody.bodyUp, _playerInfo.upBodyIndex);
		break;
		//물체충돌
		case BODY_DWBODY:
			return _player->getRect(_playerBody.bodyDw, _playerInfo.dwBodyIndex);
		break;
	}
}


POINT player::getPlayerXY()
{
	POINT tmpMove;
	RECT tmpPlayerRc = _player->getRect(_playerBody.bodyDw, _playerInfo.dwBodyIndex);

	tmpMove.x = _pMove.x + (tmpPlayerRc.right - tmpPlayerRc.left) / 2;
	tmpMove.y = _pMove.y + (tmpPlayerRc.bottom - tmpPlayerRc.top) / 2;

	return tmpMove;
}

