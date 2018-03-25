#include "stdafx.h"
#include "timeManager.h"


timeManager::timeManager()
	: _timer(NULL)
{
}


timeManager::~timeManager()
{

}

HRESULT timeManager::init(void)		
{
	_timer = new timer;
	_timer->init();

	return S_OK;
}

void timeManager::release(void)		
{
	if (_timer != NULL)
	{
		SAFE_DELETE(_timer);
	}
}

void timeManager::update(float lock)
{
	if (_timer != NULL)
	{
		_timer->tick(lock);
	}
}

void timeManager::render()
{
	WCHAR str[256];
	string strFrame;


#ifdef _DEBUG
	{
		swprintf(str, L"FPS : %d", _timer->getFrameRate());
		D2DMANAGER->drawTextDwd(D2DMANAGER->createBrush(RGB(255, 255, 255)), L"¸¼Àº°íµñ", 18.0f, str, 0, 0, 200, 20);

		swprintf(str, L"worldTime : %f", _timer->getWorldTime());
		D2DMANAGER->drawTextDwd(D2DMANAGER->createBrush(RGB(255, 255, 255)), L"¸¼Àº°íµñ", 18.0f, str, 0, 20, 200, 40);


		swprintf(str, L"elapsedTime : %f", _timer->getElapsedTime());
		D2DMANAGER->drawTextDwd(D2DMANAGER->createBrush(RGB(255, 255, 255)), L"¸¼Àº°íµñ", 18.0f, str, 0, 40, 200, 60);

	}
#else
	{
		swprintf(str, L"FPS : %d", _timer->getFrameRate());
		D2DMANAGER->drawTextDwd(D2DMANAGER->createBrush(RGB(255, 255, 255)), L"¸¼Àº°íµñ", 18.0f, str, 0, 0, 200, 20);
	}
#endif

}
