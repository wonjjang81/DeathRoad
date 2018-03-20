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

	//저장한 플레이어 데이터 로드
	loadPlayer(DATABASE->player[playerNum]);

	_player->charSetup(_playerInfo.charTypeName, 200, 200, 3);

	_headY = 0;
	_bodyY = 0;

	//머리Ani
	_head.speed = 0.1f;
	_head.fric  = 0.017f;
	_head.dir   = false;
	_head.count = 1;

	//몸통Ani
	_body.speed = 0.1f;
	_body.fric  = 0.019f;
	_body.dir   = false;
	_body.count = 1;

	//전체Ani
	_pMove.x = 0;
	_pMove.y = 0;
	_pMove.speed = 0.7f;
	_pMove.count = 1;
	_pMove.keyOn = false;

	_pMove.x = _player->getX(_playerBody.head, _playerInfo.headIndex);
	_pMove.y = _player->getY(_playerBody.head, _playerInfo.headIndex);



	return S_OK;
}

void player::release()
{

}

void player::update()
{
	keyControl();
	Stateframe(STATE_IDLE, DIRECTION_LEFT);



}

void player::render()
{
	_player->charRender(_playerBody.bodyDw, _playerInfo.dwBodyIndex);   //하체
	_player->charRender(_playerBody.bodyUp, _playerInfo.upBodyIndex);   //상체
	_player->charRender(_playerBody.head, _playerInfo.headIndex);		//머리
	_player->charRender(_playerBody.hair, _playerInfo.hairIndex);		//헤어
	_player->charRender(_playerBody.glass, _playerInfo.glassIndex);		//안경
	_player->charRender(_playerBody.hats, _playerInfo.hatsIndex);		//모자
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

void player::totalBodyAni()
{
	bodyAni(_head, _headY, 3);
	_player->setY(_playerBody.head,  _playerInfo.headIndex, _pMove.y, _headY);    //머리
	_player->setY(_playerBody.hair, _playerInfo.hairIndex,  _pMove.y, _headY);    //헤어
	_player->setY(_playerBody.glass, _playerInfo.glassIndex,_pMove.y, _headY);	  //안경
	_player->setY(_playerBody.hats, _playerInfo.hatsIndex,  _pMove.y, _headY);    //모자

	bodyAni(_body, _bodyY, 2);
	_player->setY(_playerBody.bodyUp, _playerInfo.upBodyIndex, _pMove.y, _bodyY);  //상체
}

void player::keyControl()
{
	//좌
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_pMove.x -= _pMove.speed;
	}


	//우
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_pMove.x += _pMove.speed;
	}


	//상
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_pMove.y -= _pMove.speed;
	}


	//하
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_pMove.y += _pMove.speed;
	}


	

	_player->setX(_playerBody.head, _playerInfo.headIndex, _pMove.x);
	_player->setX(_playerBody.hair, _playerInfo.hairIndex, _pMove.x);
	_player->setX(_playerBody.glass, _playerInfo.glassIndex, _pMove.x);
	_player->setX(_playerBody.hats, _playerInfo.hatsIndex, _pMove.x);
	_player->setX(_playerBody.bodyUp, _playerInfo.upBodyIndex, _pMove.x);
	_player->setX(_playerBody.bodyDw, _playerInfo.dwBodyIndex, _pMove.x);

	//_player->setY(_playerBody.head, _playerInfo.headIndex, _pMove.y);
	//_player->setY(_playerBody.hair, _playerInfo.hairIndex, _pMove.y);
	//_player->setY(_playerBody.glass, _playerInfo.glassIndex, _pMove.y);
	//_player->setY(_playerBody.hats, _playerInfo.hatsIndex, _pMove.y);
	//_player->setY(_playerBody.bodyUp, _playerInfo.upBodyIndex, _pMove.y);
	//_player->setY(_playerBody.bodyDw, _playerInfo.dwBodyIndex, _pMove.y);

}