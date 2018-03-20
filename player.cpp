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
	_head.speed = 0.1f;
	_head.fric  = 0.017f;
	_head.dir   = false;
	_head.count = 1;

	//����Ani
	_body.speed = 0.12f;
	_body.fric  = 0.017f;
	_body.dir   = false;
	_body.count = 1;


	return S_OK;
}

void player::release()
{

}

void player::update()
{
	Stateframe(STATE_IDLE, DIRECTION_LEFT);



}

void player::render()
{

	_player->charRender(_playerBody.body, _playerInfo.upBodyIndex);  //��ü
	_player->charRender(_playerBody.body, _playerInfo.dwBodyIndex);  //��ü
	_player->charRender(_playerBody.head, _playerInfo.headIndex);	 //�Ӹ�
	_player->charRender(_playerBody.hair, _playerInfo.hairIndex);    //���
	_player->charRender(_playerBody.glass, _playerInfo.glassIndex);  //�Ȱ�
	_player->charRender(_playerBody.hats, _playerInfo.hatsIndex);    //����

}


//���� �����ͺ��̽� ���� �ε�
void  player::loadPlayer(charInfo* saveInfo)
{
	_playerInfo.charTypeName = saveInfo->charTypeName;
	_playerBody.head  = _player->bodyNameChange(_playerInfo.charTypeName, BODY_HEAD);
	_playerBody.body  = _player->bodyNameChange(_playerInfo.charTypeName, BODY_UPBODY);
	_playerBody.hair  = _player->bodyNameChange(_playerInfo.charTypeName, BODY_HAIR);
	_playerBody.glass = _player->bodyNameChange(_playerInfo.charTypeName, BODY_GLASS);
	_playerBody.hats  = _player->bodyNameChange(_playerInfo.charTypeName, BODY_HATS);

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
			switch (direction)
			{
				case DIRECTION_LEFT:
					bodyAni(_head, _headY, 3);
					_player->setBodyY(_playerBody.head,  0, _headY);   //�Ӹ�
					_player->setBodyY(_playerBody.hair,  0, _headY);   //���
					_player->setBodyY(_playerBody.glass, 0, _headY);   //�Ȱ�
					_player->setBodyY(_playerBody.hats,  0, _headY);   //����

					bodyAni(_body, _bodyY, 2);
					_player->setBodyY(_playerBody.body, 0, _bodyY);    //��ü
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


void player::bodyAni(tagMove& body, float& moveY, int count)
{
	body.count++;

	if (body.count % count == 0)
	{
		if (body.dir)
		{
			moveY += body.speed * 0.03;
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
			moveY -= body.speed * 0.03;
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