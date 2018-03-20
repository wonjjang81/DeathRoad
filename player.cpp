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




	return S_OK;
}

void player::release()
{

}

void player::update()
{



}

void player::render()
{
	_player->charRender(_playerBody.head, _playerInfo.headIndex);	 //�Ӹ�
	_player->charRender(_playerBody.body, _playerInfo.upBodyIndex);  //��ü
	_player->charRender(_playerBody.body, _playerInfo.dwBodyIndex);  //��ü
	_player->charRender(_playerBody.hair, _playerInfo.hairIndex);    //���
	_player->charRender(_playerBody.glass, _playerInfo.glassIndex);  //�Ȱ�
	_player->charRender(_playerBody.hats, _playerInfo.hatsIndex);    //����

	Matrix3x2F m;
	m.Invert();

	D2DMANAGER->pRenderTarget->SetTransform(m);
	D2DMANAGER->drawRectangle(D2DMANAGER->defaultBrush, 300, 300, 150, 150, 1);
	D2DMANAGER->pRenderTarget->SetTransform(Matrix3x2F::Identity());
}


//���� �����ͺ��̽� ���� �ε�
void  player::loadPlayer(charInfo* saveInfo)
{
	_playerInfo.charTypeName = saveInfo->charTypeName;
	_playerBody.head  = _player->bodyNameChange(_playerInfo.charTypeName, BODY_HEAD);
	_playerBody.body  = _player->bodyNameChange(_playerInfo.charTypeName, BODY_BODY);
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