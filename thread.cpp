#include "stdafx.h"
#include "thread.h"


thread::thread()
{
}
thread::~thread()
{
}

HRESULT thread::init(CALLBACK_FUNCTION cbFunction)
{
	_callbackFunction = static_cast<CALLBACK_FUNCTION>(cbFunction);

	_running = false;

	return S_OK;
}


DWORD WINAPI thread::threadFunc(LPVOID lpParam)
{
	thread* tt = (thread*)lpParam;


	while (tt->isGetRunning())
	{
		tt->threadProc();
	}

	return 0;
}


void thread::threadProc()
{
	_callbackFunction();
}


void thread::startThread()
{
	_running = true;
	
	DWORD threadID = 0;
	CloseHandle(CreateThread(NULL, 0, threadFunc, (void*)this, NULL, &threadID));
}
