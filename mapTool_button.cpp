#include "stdafx.h"
#include "mapTool.h"


void mapTool::btnSetup()
{
	//------------------------------------------------------------------ 메뉴 탭 ------------------------------------------------------------------
	_btnScale = 2;
	_btnImgReWidth = IMAGEMANAGER->findImage("맵툴버튼타이틀탭")->getFrameWidth() * _btnScale;
	_btnImgReHeight = IMAGEMANAGER->findImage("맵툴버튼타이틀탭")->getFrameHeight() * _btnScale;
	float imgReX = 745 - _btnImgReWidth / 2;
	float imgReY = _btnImgReHeight / 2 - 15;

	_btnTerrain = new button;
	_btnTerrain->init("맵툴버튼타이틀탭",  imgReX,					      imgReY, PointMake(1, 0), PointMake(0, 0), menuTerrainSetup, _btnScale);
	_btnBuiliding = new button;
	_btnBuiliding->init("맵툴버튼타이틀탭",imgReX + (_btnImgReWidth * 1), imgReY, PointMake(1, 1), PointMake(0, 1), menuBuilidingSetup, _btnScale);
	_btnItems = new button;
	_btnItems->init("맵툴버튼타이틀탭",    imgReX + (_btnImgReWidth * 2), imgReY, PointMake(1, 2), PointMake(0, 2), menuItemSetup, _btnScale);
	_btnWeapon = new button;
	_btnWeapon->init("맵툴버튼타이틀탭",   imgReX + (_btnImgReWidth * 3), imgReY, PointMake(1, 3), PointMake(0, 3), menuWeaponSetup, _btnScale);
	_btnEnemy = new button;
	_btnEnemy->init("맵툴버튼타이틀탭",	   imgReX + (_btnImgReWidth * 4), imgReY, PointMake(1, 4), PointMake(0, 4), menuEnemySetup, _btnScale);
	_btnSetting = new button;
	_btnSetting->init("맵툴버튼타이틀탭",  imgReX + (_btnImgReWidth * 5), imgReY, PointMake(1, 5), PointMake(0, 5), menuSettingSetup, _btnScale);
	//---------------------------------------------------------------------------------------------------------------------------------------------

	//----------------------------------------------------------------- 타일 리셋 -----------------------------------------------------------------
	imgReX = 750 - _btnImgReWidth / 2;
	imgReY = WINSIZEY - (_btnImgReHeight + 10);
	_btnRCenterX = imgReX + (_btnImgReWidth / 4);
	_btnRCenterY = imgReY + (_btnImgReHeight / 4);

	//속성변경 버튼
	_btnAttribute = new fButton;
	_btnAttribute->init("맵툴버튼타이틀탭", L"A", 18,  imgReX, imgReY, PointMake(1, 6), PointMake(0, 6), _btnScale);

	_btnA_move = new fButton;
	_btnA_move->init("맵툴버튼타이틀탭",    L"X", 10, imgReX,						  imgReY - (_btnImgReHeight), PointMake(1, 6), PointMake(0, 6), _btnScale);
	_btnA_unMove = new fButton;
	_btnA_unMove->init("맵툴버튼타이틀탭",  L"X", 10, imgReX + (_btnImgReWidth * 1), imgReY - (_btnImgReHeight), PointMake(1, 6), PointMake(0, 6), _btnScale);
	_btnA_ARender = new fButton;
	_btnA_ARender->init("맵툴버튼타이틀탭", L"X", 10, imgReX + (_btnImgReWidth * 2), imgReY - (_btnImgReHeight), PointMake(1, 6), PointMake(0, 6), _btnScale);

	//타입변경 버튼
	_btnTileType = new fButton;
	_btnTileType->init("맵툴버튼타이틀탭",   L"A", 18, imgReX + (_btnImgReWidth * 1), imgReY, PointMake(1, 7), PointMake(0, 7), _btnScale);

	_btnT_terrain = new fButton;
	_btnT_terrain->init("맵툴버튼타이틀탭",  L"RN", 10, imgReX,                        imgReY - (_btnImgReHeight), PointMake(1, 7), PointMake(0, 7), _btnScale);
	_btnT_building = new fButton;
	_btnT_building->init("맵툴버튼타이틀탭", L"RC", 10, imgReX + (_btnImgReWidth * 1), imgReY - (_btnImgReHeight), PointMake(1, 7), PointMake(0, 7), _btnScale);
	_btnT_item = new fButton;
	_btnT_item->init("맵툴버튼타이틀탭",     L"RO", 10, imgReX + (_btnImgReWidth * 2), imgReY - (_btnImgReHeight), PointMake(1, 7), PointMake(0, 7), _btnScale);
	_btnT_weapon = new fButton;
	_btnT_weapon->init("맵툴버튼타이틀탭",   L"RR", 10, imgReX + (_btnImgReWidth * 3), imgReY - (_btnImgReHeight), PointMake(1, 7), PointMake(0, 7), _btnScale);
	_btnT_enemy = new fButton;
	_btnT_enemy->init("맵툴버튼타이틀탭",    L"X", 10, imgReX + (_btnImgReWidth * 4), imgReY - (_btnImgReHeight), PointMake(1, 7), PointMake(0, 7), _btnScale);
	//---------------------------------------------------------------------------------------------------------------------------------------------

	//------------------------------------------------------------------ Edit 버튼 ----------------------------------------------------------------
	imgReX = 962;
	imgReY = WINSIZEY - (40);
	float tmpScale = 1.5;
	float tmpImgWidth = _btnImgReWidth / _btnScale * tmpScale;
	float tmpImgHeight = _btnImgReHeight / _btnScale * tmpScale;


	_btnAllReset = new fButton;
	_btnAllReset->init("맵툴버튼타이틀탭",  L"R", 18, imgReX, imgReY, PointMake(1, 8), PointMake(0, 8), tmpScale);
																	  
	_btnEraser = new fButton;										  
	_btnEraser->init("맵툴버튼타이틀탭",    L"E", 18, imgReX - (tmpImgWidth * 1), imgReY,					   PointMake(1, 8), PointMake(0, 8), tmpScale);
	_btnOneEraser = new fButton;
	_btnOneEraser->init("맵툴버튼타이틀탭", L"1", 18, imgReX - (tmpImgWidth * 1), imgReY - (tmpImgHeight * 1), PointMake(1, 8), PointMake(0, 8), tmpScale);
	_btnAllEraser = new fButton;
	_btnAllEraser->init("맵툴버튼타이틀탭", L"-", 18, imgReX					, imgReY - (tmpImgHeight * 1), PointMake(1, 8), PointMake(0, 8), tmpScale);
	_btnAllSet = new fButton;
	_btnAllSet->init("맵툴버튼타이틀탭",    L"+", 18, imgReX - (tmpImgWidth * 2), imgReY - (tmpImgHeight * 1), PointMake(1, 8), PointMake(0, 8), tmpScale);
	//--------------------------------------------------------------------------------------------------------------------------------------------

	//------------------------------------------------------------------ Etc 버튼 ----------------------------------------------------------------
	imgReX = 850;
	imgReY = WINSIZEY - (105);

	_btnArrowL = new fButton;
	_btnArrowL->init("맵툴버튼화살", L"", 5, imgReX - 30, imgReY, PointMake(1, 0), PointMake(0, 0), 1);
	_btnArrowR = new fButton;
	_btnArrowR->init("맵툴버튼화살", L"", 5, imgReX + 30, imgReY, PointMake(1, 1), PointMake(0, 1), 1);

	_btnTabNum = 1;  //현재 탭넘버
	_preTabNum = 0;	 //이전 탭넘버
	//--------------------------------------------------------------------------------------------------------------------------------------------

	//----------------------------------------------------------------- Setting 버튼 -------------------------------------------------------------
	imgReX = 790;
	imgReY = 120;

	_btnNewTile = new fButton;
	_btnNewTile->initB("맵툴버튼", L"NEW", 18, imgReX, imgReY,       14, 4, PointMake(1, 2), PointMake(0, 2), 3);
	_btnSave = new fButton;
	_btnSave->initB("맵툴버튼",   L"SAVE", 18, imgReX, imgReY + 60,  11, 4, PointMake(1, 0), PointMake(0, 0), 3);
	_btnLoad = new fButton;
	_btnLoad->initB("맵툴버튼",   L"LOAD", 18, imgReX, imgReY + 120, 11, 4, PointMake(1, 1), PointMake(0, 1), 3);
	_btnExit = new fButton;
	_btnExit->initB("맵툴버튼",   L"EXIT", 18, imgReX, imgReY + 180, 11, 4, PointMake(1, 3), PointMake(0, 3), 3);

	_isSetBtnOn = false;
	//--------------------------------------------------------------------------------------------------------------------------------------------

}

void mapTool::btnUpdate()
{
	//------- 메뉴 탭 -------
	_btnTerrain->update();
	_btnBuiliding->update();
	_btnItems->update();
	_btnWeapon->update();
	_btnEnemy->update();
	_btnSetting->update();
	//-----------------------

	//------ 타일 리셋 -------
	_btnAttribute->update();
	_btnTileType->update();

	//버튼 On/Off
	btnSwitch();

	//속성버튼 디테일
	if (_btnAttribute->getBtnOn())
	{
		_btnA_move->update();
		_btnA_unMove->update();
		_btnA_ARender->update();
	}

	//타입버튼 디테일
	if (_btnTileType->getBtnOn())
	{
		_btnT_terrain->update();
		_btnT_building->update();
		_btnT_item->update();
		_btnT_weapon->update();
		_btnT_enemy->update();
	}
	//-----------------------

	//------ Edit 버튼 ------
	_btnAllReset->update();
	btnAllReset();

	_btnEraser->update();
	if (_btnEraser->getBtnOn())
	{
		_btnOneEraser->update();
		_btnAllEraser->update();
		_btnAllSet->update();
	}

	//모든 타일정보 지우기
	if (_btnAllEraser->getBtnOn())
	{
		btnTileAllEraser();
		_btnAllEraser->setBtnOff(false);
	}

	//모든 타일에 선택한 타일정보 넣기
	if (_btnAllSet->getBtnOn())
	{
		btnTileAllSet(_drawTile);
		_btnAllSet->setBtnOff(false);
	}
	//-----------------------

	//---- SaveLoad 버튼 ----
	if (_isSetBtnOn)
	{
		_btnNewTile->update();
		_btnSave->update();
		_btnLoad->update();
		_btnExit->update();
	}
	//-----------------------

	//newTile
	if (_btnNewTile->getBtnOn())
	{
		newTileMap();
		_btnNewTile->setBtnOff(false);
	}
}

void mapTool::btnRender()
{
	//----------- 메뉴 탭 -----------
	_btnTerrain->render(_btnScale);
	_btnBuiliding->render(_btnScale);
	_btnItems->render(_btnScale);
	_btnWeapon->render(_btnScale);
	_btnEnemy->render(_btnScale);
	_btnSetting->render(_btnScale);
	//-------------------------------

	//---------- 타일 리셋 ----------
	_btnAttribute->render();
	_btnTileType->render();

	//속성버튼 디테일
	if (_btnAttribute->getBtnOn())
	{
		_btnA_move->render();
		_btnA_unMove->render();
		_btnA_ARender->render();
	}

	//타입버튼 디테일
	if (_btnTileType->getBtnOn())
	{
		_btnT_terrain->render();
		_btnT_building->render();
		_btnT_item->render();
		_btnT_weapon->render();
		_btnT_enemy->render();
	}
	//-------------------------------

	//---------- Edit 버튼 ----------
	_btnAllReset->render();

	_btnEraser->render();
	if (_btnEraser->getBtnOn())
	{
		_btnOneEraser->render();
		_btnAllEraser->render();
		_btnAllSet->render();
	}
	//-------------------------------

	//---- SaveLoad 버튼 ----
	if (_isSetBtnOn)
	{
		_btnNewTile->render();
		_btnSave->render();
		_btnLoad->render();
		_btnExit->render();
	}
	//-----------------------
}


//버튼 ON/OFF
void mapTool::btnSwitch()
{
	//-------------------------------------------- 속성버튼 --------------------------------------------
	//하부버튼 ON/OFF
	if (!_btnAttribute->getBtnOn())
	{
		_btnA_move->setBtnOff(false);
		_btnA_unMove->setBtnOff(false);
		_btnA_ARender->setBtnOff(false);
	}
	//--------------------------------------------------------------------------------------------------

	//-------------------------------------------- 타입버튼 --------------------------------------------
	//하부버튼 ON/OFF
	if (!_btnTileType->getBtnOn())
	{
		_btnT_terrain->setBtnOff(false);
		_btnT_building->setBtnOff(false);
		_btnT_item->setBtnOff(false);
		_btnT_weapon->setBtnOff(false);
		_btnT_enemy->setBtnOff(false);
	}
	//--------------------------------------------------------------------------------------------------

	//--------------------------------------------- Eraser ---------------------------------------------
	//하부버튼 ON/OFF
	if (!_btnEraser->getBtnOn())
	{
		_btnOneEraser->setBtnOff(false);
		_btnAllEraser->setBtnOff(false);
		_btnAllSet->setBtnOff(false);
	}
	//--------------------------------------------------------------------------------------------------
}


void mapTool::btnAllReset()
{
	if (_btnAllReset->getBtnOn()) //버튼ON 이면...
	{
		_btnAttribute->setBtnOff(false);  //속성버튼 Off
		_btnTileType->setBtnOff(false);   //타입버튼 Off
		_btnEraser->setBtnOff(false);     //타일초기화 버튼 Off
		_btnAllReset->setBtnOff(false);   //리셋버튼 Off

		//선택 FillRect 지우기
		samTileFRectInitialize();
		//선택한 타일정보 구조체 초기화
		ZeroMemory(&_drawTile, sizeof(tagTile));
	}
}


//메뉴하단 화살표 버튼 액션: 탭 넘버 카운팅 
void mapTool::menuTabArrowAction()
{
	//좌측탭
	if (_btnArrowL->getBtnOn())
	{
		_btnTabNum--;

		if (_btnTabNum <= 1) _btnTabNum = 1;
		_btnArrowL->setBtnOff(false);
	}

	//우측탭
	if (_btnArrowR->getBtnOn())
	{
		_btnTabNum++;

		if (_btnTabNum >= TABMAXNUM) _btnTabNum = TABMAXNUM;
		_btnArrowR->setBtnOff(false);
	}
}