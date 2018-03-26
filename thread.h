#pragma once
#include "gameNode.h"

//�ݹ��Լ� == �Լ�������
typedef void(*CALLBACK_FUNCTION)(void);

class thread : public gameNode
{
private:
	bool _running;

	CALLBACK_FUNCTION _callbackFunction;


public:
	HRESULT init(CALLBACK_FUNCTION cbFunction);

	static DWORD WINAPI threadFunc(LPVOID lpParam);
	void startThread();
	void threadProc();

	//====================== getter & setter ======================
	bool isGetRunning() { return _running; }
	void setRunning(bool run) { _running = run; }


	thread();
	~thread();
};

