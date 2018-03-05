// stdafx.h : �̸� �����ϵ� ������� : ���� ����ϴ� �͵��� �̸� ������ �δ� ��
#pragma once

// D2D ���̺귯��
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "WindowsCodecs.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "Comdlg32.lib")

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>
#include <cassert>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>

// D2D Header Files
#include <d2d1.h>
#include <d2d1helper.h>
#include <wincodec.h>
#include <dwrite.h>

#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "soundManager.h"
#include "timeManager.h"
#include "effectManager.h"
#include "iniDataManager.h"
#include "sceneManager.h"
#include "keyAniManager.h"
#include "utils.h"
#include "collision.h"
#include "txtData.h"
#include "database.h"

using namespace std;
using namespace HEPTA_UTIL;
using namespace D2D1;

//=======================================================
// ## ������ ���� ������ ## 2017.11.08 ##
//=======================================================

#define WINNAME		(LPTSTR)TEXT("Zerone")
#define WINSTARTX	50		//������ ������ǥ X
#define WINSTARTY	50		//������ ������ǥ Y
#define WINSIZEX	1000	//������ ����ũ��
#define WINSIZEY	700		//������ ����ũ��
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

#define KEYMANAGER		keyManager::getSingleton()
#define RND				randomFunction::getSingleton()
#define IMAGEMANAGER	imageManager::getSingleton()
#define SOUNDMANAGER	soundManager::getSingleton()
#define TIMEMANAGER		timeManager::getSingleton()
#define EFFECTMANAGER	effectManager::getSingleton()
#define SCENEMANAGER	sceneManager::getSingleton()
#define KEYANIMANAGER	keyAniManager::getSingleton()
#define TXTDATA			txtData::getSingleton()
#define INIDATA			iniDataManager::getSingleton()
#define DATABASE		database::getSingleton()

//=======================================================
// ## ��ũ�� ## 2017.11.15 ##
//=======================================================

#define SAFE_DELETE(p)			{if(p) { delete(p);		 (p) = nullptr; }}
#define SAFE_RELEASE(p)			{if(p) { (p)->release(); (p) = nullptr; }}
#define SAFE_RELEASE_D2D(p)		{if(p) { (p)->Release(); (p) = nullptr; }}
#define SAFE_DELETE_ARRAY(p)	{if(p) { delete[](p);	 (p) = nullptr; }}

//=======================================================
// ## ������ ���� extern ## 2017.11.08 ##
//=======================================================

extern HINSTANCE	_hInstance;		//�ν��Ͻ� �ڵ�
extern HWND			_hWnd;			//�ڵ�
extern POINT		_ptMouse;
extern BOOL			_leftButtonDown;