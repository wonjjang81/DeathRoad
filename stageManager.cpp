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
	_mapFileName = "room1";
	stageScale = 3;

	//타일 화면 중앙으로
	string tmpFileName;
	tmpFileName.append("map//");
	tmpFileName.append(_mapFileName);
	int tileX = INIDATA->loadDataInterger(tmpFileName.c_str(), "mapData", "tileX");
	int tileY = INIDATA->loadDataInterger(tmpFileName.c_str(), "mapData", "tileY");
	_moveX = (WINSIZEX - tileX * TILE_SIZEX * stageScale) / 2;
	_moveY = (WINSIZEY - tileY * TILE_SIZEY * stageScale) / 2;


	_room1 = new stage;
	_room1->init(_mapFileName, _moveX, _moveY, stageScale);

	_startPoint.x = _room1->getStartPoint().x * stageScale + _moveX;
	_startPoint.y = _room1->getStartPoint().y * stageScale + _moveY;

	_player1 = new player;
	_player1->init(0, _startPoint.x, _startPoint.y, 1.5);

	//플레이어  이동
	_isLeft   = true;
	_isRight  = true;
	_isTop    = true;
	_isBottom = true;
	_isPlayerMove = true;

	//충돌판단
	_collOn = false;

	//이동 증감량
	_moveChange.x = 0.0f;
	_moveChange.y = 0.0f;

	//Timer
	_timer = new gameTime;
	_timer->init();

	//낮&밤 조명처리
	daynNightInit();



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

	_room1->update(CAMERAMANAGER->tileCamMove().x, CAMERAMANAGER->tileCamMove().y);

	_moveChange.x += CAMERAMANAGER->tileCamMove().x;
	_moveChange.y += CAMERAMANAGER->tileCamMove().y;

	//timer
	_timer->update();

	//밤낮 전환
	daynNightSet();
}

void stageManager::render()	 
{
	//배경색
	D2DMANAGER->fillRectangle(D2DMANAGER->createBrush(RGB(0, 0, 0)), 0, 0, WINSIZEX, WINSIZEY);

	_room1->render();
	_player1->render();
	_room1->afterRender();

	D2DMANAGER->opacityMask(_player1->getPlayerXY().x + 15, _player1->getPlayerXY().y + 15, _gradientRadius, _isNight);


	//게임시간
	_timer->render();




	//======================================== TEST ========================================
	//충돌 확인용
	if (_collOn) D2DMANAGER->drawTextD2d(D2DMANAGER->createBrush(RGB(0, 0, 255)), L"충돌",
		_player1->getRect(BODY_UPBODY).left, _player1->getRect(BODY_UPBODY).top - 50,
		_player1->getRect(BODY_UPBODY).left + 100, _player1->getRect(BODY_UPBODY).top);

	CAMERAMANAGER->render();
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

	//게임시간
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