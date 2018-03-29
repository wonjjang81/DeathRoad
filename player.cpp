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

	//������ �÷��̾� ������ �ε�
	loadPlayer(DATABASE->player[playerNum]);

	_player->charSetup(_playerInfo.charTypeName, startX, startY, 3);

	_headY = 0;
	_bodyY = 0;
	_walkY = 0;

	//�Ӹ�Ani
	_head.speed = 0.3f;
	_head.fric  = 0.017f;
	_head.dir   = false;
	_head.count = 1;

	//����Ani
	_body.speed = 0.3f;
	_body.fric  = 0.015;
	_body.dir   = false;
	_body.count = 1;

	//WalkAni
	_walk.speed = 0.7f;
	_walk.fric = 0.015;
	_walk.dir = false;
	_walk.count = 1;

	//��üAni
	_pMove.x = 0;
	_pMove.y = 0;
	_pMove.speed = 0.7f * speed;
	_pMove.count = 1;
	_pMove.keyOn = false;

	_pMove.x = _player->getX(_playerBody.head, _playerInfo.headIndex);
	_pMove.y = _player->getY(_playerBody.head, _playerInfo.headIndex);

	//�������
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
	_player->charRender(_playerBody.bodyDw, _playerInfo.dwBodyIndex, _bodyFlip);	//��ü
	_player->charRender(_playerBody.bodyUp, _playerInfo.upBodyIndex, _bodyFlip);    //��ü
	_player->charRender(_playerBody.head,   _playerInfo.headIndex,   _bodyFlip);	//�Ӹ�
	_player->charRender(_playerBody.hair,   _playerInfo.hairIndex,   _bodyFlip);	//���
	_player->charRender(_playerBody.glass,  _playerInfo.glassIndex,  _bodyFlip);	//�Ȱ�
	_player->charRender(_playerBody.hats,   _playerInfo.hatsIndex,   _bodyFlip);	//����
}







//���� �����ͺ��̽� ���� �ε�
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

//���°��� ���� ������ ����
void player::Stateframe(MOVE_STATE state, MOVE_DIRECTION direction)
{
	switch (state)
	{
		case STATE_IDLE:
			totalBodyAni();
			//walkAni �ʱ�ȭ
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

	//���� �ִ�
	frameAniB(_playerBody.head,   _playerInfo.headIndex,   _upHeadAni);
	frameAniB(_playerBody.bodyUp, _playerInfo.upBodyIndex, _upBodyUpAni);
	frameAniB(_playerBody.hair,	  _playerInfo.hairIndex,   _upHeadAni);
	frameAniB(_playerBody.glass,  _playerInfo.glassIndex,  _upHeadAni);
	frameAniB(_playerBody.hats,   _playerInfo.hatsIndex,   _upHeadAni);
}


void player::bodyAni(tagBodyMove& body, float& moveY, int count)
{
	//������ y����ŭ �ٽ� ���ƿ�����...

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
	_player->setBodyY(_playerBody.head,  _playerInfo.headIndex,  _headY);	 //�Ӹ�
	_player->setBodyY(_playerBody.hair,  _playerInfo.hairIndex,  _headY);	 //���
	_player->setBodyY(_playerBody.glass, _playerInfo.glassIndex, _headY);	 //�Ȱ�
	_player->setBodyY(_playerBody.hats,  _playerInfo.hatsIndex,  _headY);	 //����

	bodyAni(_body, _bodyY, 2);
	_player->setBodyY(_playerBody.bodyUp, _playerInfo.upBodyIndex, _bodyY);  //��ü
}

void player::walkBodyAni()
{
	bodyAni(_walk, _walkY, 3);



}

void player::keyControl(bool left, bool top, bool right, bool bottom)
{
	_currentState = STATE_IDLE;
	_currentDir = DIRECTION_DOWN;

	//��
	if (left)
	{
		_currentState = STATE_WALK;
		_currentDir = DIRECTION_LEFT;
		//_pMove.x -= _pMove.speed;
	}


	//��
	if (right)
	{
		_currentState = STATE_WALK;
		_currentDir = DIRECTION_RIGHT;
		//_pMove.x += _pMove.speed;
	}


	//��
	if (top)
	{
		_currentState = STATE_WALK;
		_currentDir = DIRECTION_UP;
		//_pMove.y -= _pMove.speed;
	}


	//��
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

//�ִ� �ʱ�ȭ
void player::frameAniInit(tagAni& ani)
{
	ani.frameX = 0;
	ani.initFrameX = 0;
	ani.frameCount = 1;
	ani.isInit = false;
	ani.isChange = false;
}

//�ִϸ��̼� Ÿ��A: downBody
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

//�ִϸ��̼� Ÿ��B
void player::frameAniB(string pBodyName, int pBodyIndex, tagAni& ani)
{
	//������ �߰�
	if (ani.isChange && ani.frameX == ani.initFrameX) ani.frameX++;

	if (!ani.isInit)
	{
		//������ �ʱⰪ ����
		ani.frameX = _player->getFrameX(pBodyName, pBodyIndex);
		ani.initFrameX = ani.frameX;
		ani.isInit = true;
	}

	//������ �ʱ�ȭ
	if (!ani.isChange)
	{
		ani.frameX = ani.initFrameX;
	}

	//������ ����
	_player->setFrameX(pBodyName, pBodyIndex, ani.frameX);
	
}


RECT player::getRect(BODYTYPE type)
{
	switch (type)
	{
		//Ÿ���浹
		case BODY_UPBODY: 
			return _player->getRect(_playerBody.bodyUp, _playerInfo.upBodyIndex);
		break;
		//��ü�浹
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

