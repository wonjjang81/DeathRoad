// stdafx.h : 미리 컴파일된 헤더파일 : 자주 사용하는 것들을 미리 정의해 두는 곳
#pragma once

// D2D 라이브러리
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "WindowsCodecs.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "Comdlg32.lib")

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>
#include <cassert>

// C 런타임 헤더 파일입니다.
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
// ## 윈도우 설정 디파인 ## 2017.11.08 ##
//=======================================================

#define WINNAME		(LPTSTR)TEXT("Zerone")
#define WINSTARTX	50		//윈도우 시작좌표 X
#define WINSTARTY	50		//윈도우 시작좌표 Y
#define WINSIZEX	1000	//윈도우 가로크기
#define WINSIZEY	700		//윈도우 세로크기
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
// ## 매크로 ## 2017.11.15 ##
//=======================================================

#define SAFE_DELETE(p)			{if(p) { delete(p);		 (p) = nullptr; }}
#define SAFE_RELEASE(p)			{if(p) { (p)->release(); (p) = nullptr; }}
#define SAFE_RELEASE_D2D(p)		{if(p) { (p)->Release(); (p) = nullptr; }}
#define SAFE_DELETE_ARRAY(p)	{if(p) { delete[](p);	 (p) = nullptr; }}

//=======================================================
// ## 윈도우 설정 extern ## 2017.11.08 ##
//=======================================================

extern HINSTANCE	_hInstance;		//인스턴스 핸들
extern HWND			_hWnd;			//핸들
extern POINT		_ptMouse;
extern BOOL			_leftButtonDown;