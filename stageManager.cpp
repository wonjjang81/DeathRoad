#include "stdafx.h"
#include "stageManager.h"


stageManager::stageManager()
{
}
stageManager::~stageManager()
{
}


HRESULT stageManager::init()
{
	intToMapFileName(1);

	stageScale = 3;

	//Ÿ�� ȭ�� �߾�����
	tileCenterXY();

	//stage
	_room1 = new stage1;
	_room1->init(_mapFileName, _moveX, _moveY, stageScale);
	addChild(_room1);


	_currentStage = new stage1;
	_currentStage = _room1;

	_startPoint.x = _room1->getStartPoint().x * stageScale + _moveX;
	_startPoint.y = _room1->getStartPoint().y * stageScale + _moveY;

	//player
	_player1 = new player;
	_player1->init(0, WINSIZEX / 2, WINSIZEY / 2, 1.5);

	//�÷��̾�  �̵�
	_isLeft   = true;
	_isRight  = true;
	_isTop    = true;
	_isBottom = true;
	_isPlayerMove = true;

	//�浹�Ǵ�
	_collOn = false;

	//�̵� ������
	_moveChange.x = 0.0f;
	_moveChange.y = 0.0f;

	//Timer
	_timer = new gameTime;
	_timer->init();

	//��&�� ����ó��
	daynNightInit();

	//������


	//UI
	_ui = new UIManager;
	_ui->init();


	//Weapon
	pCenter.x = _player1->getPlayerXY().x;
	pCenter.y = _player1->getPlayerXY().y;

	_pWp = new weapon;
	_pWp->init(stageScale);

	_wpAngle = 0;
	_wpFlip = false;
	_prevDir = DIRECTION_DOWN;
	_swordAction = false;
	_swordDirSwing = false;

	return S_OK;
}


void stageManager::release()
{

}


void stageManager::update()	
{
	_player1->update(_isLeft, _isTop, _isRight, _isBottom);

	collisionPS(_player1, _room1, stageScale, _isPlayerMove);

	CAMERAMANAGER->getPlayerXY(_player1->getPlayerXY().x, _player1->getPlayerXY().y);

	//stage
	gameNode::update();

	_moveChange.x += CAMERAMANAGER->tileCamMove().x;
	_moveChange.y += CAMERAMANAGER->tileCamMove().y;

	//timer
	_timer->update();

	//�㳷 ��ȯ
	daynNightSet();

	//UI
	_ui->update();

	//����
	_pWp->update(pCenter.x, pCenter.y);
	weaponAngleSet();

}


void stageManager::render()	 
{
	//����
	D2DMANAGER->fillRectangle(D2DMANAGER->createBrush(RGB(0, 0, 0)), 0, 0, WINSIZEX, WINSIZEY);

	//stage
	gameNode::render();  

	playerRender();

	gameNode::afterRender();



	D2DMANAGER->opacityMask(_player1->getPlayerXY().x + 15, _player1->getPlayerXY().y + 15, _gradientRadius, _isNight);


	//���ӽð�
	_timer->render();

	//UI
	_ui->render();


	//======================================== TEST ========================================
	//�浹 Ȯ�ο�
	if (_collOn) D2DMANAGER->drawTextD2d(D2DMANAGER->createBrush(RGB(0, 0, 255)), L"!!!",
		_player1->getRect(BODY_UPBODY).left + 20, _player1->getRect(BODY_UPBODY).top - 50,
		_player1->getRect(BODY_UPBODY).left + 100, _player1->getRect(BODY_UPBODY).top);

	CAMERAMANAGER->render();

	playerCenter();
}


void stageManager::playerRender()
{
	if (_player1->getDirect() == DIRECTION_DOWN || _player1->getDirect() == DIRECTION_UP)
	{
		_prevDir = _player1->getDirect();
	}

	switch (_player1->getDirect())
	{
		case DIRECTION_LEFT: case DIRECTION_RIGHT:

			if (_player1->getDirect() == DIRECTION_LEFT)
			{
				_wpFlip = true;
			}
			if (_player1->getDirect() == DIRECTION_RIGHT)
			{
				_wpFlip = false;
			}

			switch (_prevDir)
			{
				case DIRECTION_DOWN:
					_player1->render();

					if (_ui->getVwp().size() != 0 && _ui->getWpNum() < _ui->getVwp().size())
						_pWp->renderB(_ui->getVwp()[_ui->getWpNum()].frameX, _ui->getVwp()[_ui->getWpNum()].frameY, _wpAngle, _wpFlip);
				break;
				case DIRECTION_UP:
					if (_ui->getVwp().size() != 0 && _ui->getWpNum() < _ui->getVwp().size())
						_pWp->renderB(_ui->getVwp()[_ui->getWpNum()].frameX, _ui->getVwp()[_ui->getWpNum()].frameY, _wpAngle, _wpFlip);

					_player1->render();
				break;
			}
		break;
		case DIRECTION_DOWN: 
			_player1->render();

			if (_ui->getVwp().size() != 0 && _ui->getWpNum() < _ui->getVwp().size())
				_pWp->renderB(_ui->getVwp()[_ui->getWpNum()].frameX, _ui->getVwp()[_ui->getWpNum()].frameY, _wpAngle, _wpFlip);
		break;
		case DIRECTION_UP: 
			if (_ui->getVwp().size() != 0 && _ui->getWpNum() < _ui->getVwp().size())
				_pWp->renderB(_ui->getVwp()[_ui->getWpNum()].frameX, _ui->getVwp()[_ui->getWpNum()].frameY, _wpAngle, _wpFlip);

			_player1->render();
		break;
	}

}


void stageManager::daynNightInit()
{
	_isNight = false;
	_gRadiusCount = 1;

	switch (_timer->getHour())
	{
		case 21:
			_gradientRadius = 0.1f;
		break;
		case 22:
			_gradientRadius = 0.2f;
		break;
		case 23:
			_gradientRadius = 0.3f;
		break;
		case 0:
			_gradientRadius = 0.4f;
		break;
		case 1:
			_gradientRadius = 0.5f;
		break;
		case 2:
			_gradientRadius = 0.5f;
		break;
		case 3:
			_gradientRadius = 0.4f;
		break;
		case 4:
			_gradientRadius = 0.3f;
		break;
		case 5:
			_gradientRadius = 0.2f;
		break;
		case 6:
			_gradientRadius = 0.1f;
		break;
		default:
			_gradientRadius = 0.0f;
		break;
	}
}


void stageManager::daynNightSet()
{
	int perCount = 60;

	//���ӽð�
	if ((_timer->getHour() >= 20 && _timer->getHour() <= 24) || 
		(_timer->getHour() >= 0 && _timer->getHour() <= 7)) _isNight = true;
	else _isNight = false;

	//night
	if (_isNight)
	{
		_gRadiusCount++;
		if (_gradientRadius >= 0.5f) _gradientRadius = 0.5f;

		if (_gRadiusCount % perCount == 0)
		{
			_gradientRadius += 0.01f;

			_gRadiusCount = 1;
		}
	}
	else  //day
	{
		if (_timer->getHour() >= 7 && _gradientRadius <= 0.5f && _gradientRadius != 0.0f)
		{
			_gRadiusCount++;
			if (_gradientRadius <= 0.0f) _gradientRadius = 0.0f;

			if (_gRadiusCount % perCount == 0)
			{
				_gradientRadius -= 0.01f;

				_gRadiusCount = 1;
			}
		}
	}
}


void stageManager::playerCenter()
{
	pCenter.x = _player1->getPlayerXY().x + 18;
	pCenter.y = _player1->getPlayerXY().y + 50;

	int length = 5;
	D2DMANAGER->drawLine(D2DMANAGER->createBrush(RED), pCenter.x - length, pCenter.y, pCenter.x + length, pCenter.y);
	D2DMANAGER->drawLine(D2DMANAGER->createBrush(RED), pCenter.x, pCenter.y - length, pCenter.x, pCenter.y + length);
}


void stageManager::weaponAngleSet()
{
	if (!_swordAction) _wpAngle = 315;

	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		_swordAction = true;
	}

	if (_swordAction)
	{
		if ((_wpAngle >= 315 && _wpAngle <= 360 && !_swordDirSwing) || (_wpAngle >= 0 && _wpAngle <= 120 && !_swordDirSwing)) _wpAngle += 30;
		if (_wpAngle >= 360) _wpAngle = 0;

		if (_wpAngle >= 120 && _wpAngle <= 315 && !_swordDirSwing) _swordDirSwing = true;
		if (_wpAngle < 0) _wpAngle = 360;

		if (_swordDirSwing) _wpAngle -= 10;

		if (_wpAngle >= 300 && _wpAngle <= 315)
		{
			_swordDirSwing = false;
			_swordAction = false;
		}
	}
}


string stageManager::intToMapFileName(int mapNum)
{
	TCHAR intNum[32];
	sprintf(intNum, "%d", mapNum);

	_mapFileName.clear();
	_mapFileName.append("room");
	_mapFileName.append(intNum);

	return _mapFileName;
}


void stageManager::stageChange(int num)
{
	removeChild(_room1);

	intToMapFileName(num);  //mapFileName ����  
	tileCenterXY();	        //Ÿ�� ȭ�� �߾�����

	_room1 = new stage1;
	_room1->init(_mapFileName, _moveX, _moveY, stageScale);
	addChild(_room1);

	//��ġ �ʱ�ȭ
	_moveChange.x = 0.0f;
	_moveChange.y = 0.0f;

}


void stageManager::tileCenterXY()
{
	string tmpFileName;
	tmpFileName.append("map//");
	tmpFileName.append(_mapFileName);
	int tileX = INIDATA->loadDataInterger(tmpFileName.c_str(), "mapData", "tileX");
	int tileY = INIDATA->loadDataInterger(tmpFileName.c_str(), "mapData", "tileY");
	_moveX = (WINSIZEX - tileX * TILE_SIZEX * stageScale) / 2;
	_moveY = (WINSIZEY - tileY * TILE_SIZEY * stageScale) / 2;
}


