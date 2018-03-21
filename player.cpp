#include "stdafx.h"
#include "player.h"


player::player()
{
}
player::~player()
{
}


HRESULT player::init(int playerNum)
{
	_player = new character;

	//������ �÷��̾� ������ �ε�
	loadPlayer(DATABASE->player[playerNum]);

	_player->charSetup(_playerInfo.charTypeName, 200, 200, 3);

	_headY = 0;
	_bodyY = 0;

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

	//��üAni
	_pMove.x = 0;
	_pMove.y = 0;
	_pMove.speed = 0.7f;
	_pMove.count = 1;
	_pMove.keyOn = false;

	_pMove.x = _player->getX(_playerBody.head, _playerInfo.headIndex);
	_pMove.y = _player->getY(_playerBody.head, _playerInfo.headIndex);

	//�������
	_currentState = STATE_IDLE;
	_currentDir = DIRECTION_LEFT;

	//player moveAni
	_frameX = 0;
	_initFrameX = 0;
	_frmaeCount = 1;
	_isInit = false;

	return S_OK;
}

void player::release()
{

}

void player::update()
{
	keyControl();
	Stateframe(_currentState, _currentDir);



}

void player::render()
{
	_player->charRender(_playerBody.bodyDw, _playerInfo.dwBodyIndex);   //��ü
	_player->charRender(_playerBody.bodyUp, _playerInfo.upBodyIndex);   //��ü
	_player->charRender(_playerBody.head, _playerInfo.headIndex);		//�Ӹ�
	_player->charRender(_playerBody.hair, _playerInfo.hairIndex);		//���
	_player->charRender(_playerBody.glass, _playerInfo.glassIndex);		//�Ȱ�
	_player->charRender(_playerBody.hats, _playerInfo.hatsIndex);		//����
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

			switch (direction)
			{
				case DIRECTION_LEFT:

				break;
				case DIRECTION_RIGHT:
					
				break;
				case DIRECTION_UP:
				
				break;
				case DIRECTION_DOWN:
				
				break;
			}
		break;
		case STATE_WALK:

			totalBodyAni();
			walkAni(_playerBody.bodyDw, _playerInfo.dwBodyIndex);

		break;
		case STATE_DAMAGE:
			switch (direction)
			{
				case DIRECTION_LEFT:

				break;
				case DIRECTION_RIGHT:

				break;
				case DIRECTION_UP:

				break;
				case DIRECTION_DOWN:

				break;
			}
		break;
	}
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
	_player->setBodyY(_playerBody.head,  _playerInfo.headIndex,  _headY);   //�Ӹ�
	_player->setBodyY(_playerBody.hair,  _playerInfo.hairIndex,  _headY);   //���
	_player->setBodyY(_playerBody.glass, _playerInfo.glassIndex, _headY);	//�Ȱ�
	_player->setBodyY(_playerBody.hats,  _playerInfo.hatsIndex,  _headY);   //����

	bodyAni(_body, _bodyY, 2);
	_player->setBodyY(_playerBody.bodyUp, _playerInfo.upBodyIndex, _bodyY);  //��ü
}

void player::keyControl()
{
	_currentState = STATE_IDLE;

	//��
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_currentState = STATE_WALK;
		_currentDir = DIRECTION_LEFT;
		_pMove.x -= _pMove.speed;
	}


	//��
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_currentState = STATE_WALK;
		_currentDir = DIRECTION_RIGHT;
		_pMove.x += _pMove.speed;
	}


	//��
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_currentState = STATE_WALK;
		_currentDir = DIRECTION_UP;
		_pMove.y -= _pMove.speed;
	}


	//��
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_currentState = STATE_WALK;
		_currentDir = DIRECTION_DOWN;
		_pMove.y += _pMove.speed;
	}


	_player->setX(_playerBody.head, _playerInfo.headIndex, _pMove.x);
	_player->setX(_playerBody.hair, _playerInfo.hairIndex, _pMove.x);
	_player->setX(_playerBody.glass, _playerInfo.glassIndex, _pMove.x);
	_player->setX(_playerBody.hats, _playerInfo.hatsIndex, _pMove.x);
	_player->setX(_playerBody.bodyUp, _playerInfo.upBodyIndex, _pMove.x);
	_player->setX(_playerBody.bodyDw, _playerInfo.dwBodyIndex, _pMove.x);

	_player->setY(_playerBody.head, _playerInfo.headIndex, _pMove.y);
	_player->setY(_playerBody.hair, _playerInfo.hairIndex, _pMove.y);
	_player->setY(_playerBody.glass, _playerInfo.glassIndex, _pMove.y);
	_player->setY(_playerBody.hats, _playerInfo.hatsIndex, _pMove.y);
	_player->setY(_playerBody.bodyUp, _playerInfo.upBodyIndex, _pMove.y);
	_player->setY(_playerBody.bodyDw, _playerInfo.dwBodyIndex, _pMove.y);
}

void player::walkAni(string pBodyName, int pBodyIndex)
{
	_frmaeCount++;

	if (!_isInit)
	{
		_frameX = _player->getFrameX(pBodyName, pBodyIndex);
		_initFrameX = _frameX;
		_isInit = true;
	}
	if (_frameX > _initFrameX + 2) _frameX = _initFrameX;


	if (_frmaeCount % 10 == 0)
	{
		_player->setFrameX(pBodyName, pBodyIndex, _frameX);
		_frameX++;
		_frmaeCount = 1;
	}
}

