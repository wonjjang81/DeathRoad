#include "stdafx.h"
#include "gameTime.h"


gameTime::gameTime()
{
}
gameTime::~gameTime()
{
}


HRESULT gameTime::init()
{
	_second = 0;
	_minute = 0;
	_hour   = 3;  // RND->getFromIntTo(0, 23)
	_day    = 0;


	_cPosition.x = 50;
	_cPosition.y = 10;

	_reTime = 30;

	_isCount = false;

	return S_OK;
}

void gameTime::release()	  
{

}

void gameTime::update()		  
{
	//초
	if (_second >= 60)
	{
		_second = 0.0f;
		_minute++;
	}
	_second += TIMEMANAGER->getElapsedTime() * _reTime;

	//분
	if (_minute >= 60)
	{
		_minute = 0;
		_hour++;
	}

	//시
	if (_hour >= 24)
	{
		_hour = 0;
		_day++;
	}

}

void gameTime::render()		  
{

	WCHAR str[256];

	//분
	swprintf(str, L"%d", _minute);
	D2DMANAGER->drawTextDwd(D2DMANAGER->createBrush(RGB(0, 0, 255)), L"Press Start 2P", 25.0f, str, _cPosition.x + 112, _cPosition.y, _cPosition.x + 200, _cPosition.y + 50);

	//:
	swprintf(str, L":");
	D2DMANAGER->drawTextDwd(D2DMANAGER->createBrush(RGB(0, 0, 255)), L"Press Start 2P", 25.0f, str, _cPosition.x + 90, _cPosition.y, _cPosition.x + 200, _cPosition.y + 50);

	//시
	swprintf(str, L"%d", _hour);
	D2DMANAGER->drawTextDwd(D2DMANAGER->createBrush(RGB(0, 0, 255)), L"Press Start 2P", 25.0f, str, _cPosition.x + 40, _cPosition.y, _cPosition.x + 200, _cPosition.y + 50);

	//일
	swprintf(str, L"%d", _day);
	D2DMANAGER->drawTextDwd(D2DMANAGER->createBrush(RGB(0, 0, 255)), L"Press Start 2P", 25, str, _cPosition.x, _cPosition.y, _cPosition.x + 200, _cPosition.y + 50);
}
