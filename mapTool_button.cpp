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
	_btnAttribute->init("맵툴버튼타이틀탭", L"A", 18,  imgReX,						 imgReY, PointMake(1, 6), PointMake(0, 6), _btnScale);

	_btnA_move = new fButton;
	_btnA_move->init("맵툴버튼타이틀탭",    L"Mv", 10, imgReX,						 imgReY - (_btnImgReHeight), PointMake(1, 6), PointMake(0, 6), _btnScale);
	_btnA_unMove = new fButton;
	_btnA_unMove->init("맵툴버튼타이틀탭",  L"Um", 10, imgReX + (_btnImgReWidth * 1), imgReY - (_btnImgReHeight), PointMake(1, 6), PointMake(0, 6), _btnScale);
	_btnA_ARender = new fButton;
	_btnA_ARender->init("맵툴버튼타이틀탭", L"Ar", 10, imgReX + (_btnImgReWidth * 2), imgReY - (_btnImgReHeight), PointMake(1, 6), PointMake(0, 6), _btnScale);

	//타입변경 버튼
	_btnTileType = new fButton;
	_btnTileType->init("맵툴버튼타이틀탭", L"T", 18, imgReX + (_btnImgReWidth * 1), imgReY, PointMake(1, 7), PointMake(0, 7), _btnScale);

	_btnT_terrain = new fButton;
	_btnT_terrain->init("맵툴버튼타이틀탭",  L"Tr", 10, imgReX,                        imgReY - (_btnImgReHeight), PointMake(1, 7), PointMake(0, 7), _btnScale);
	_btnT_building = new fButton;
	_btnT_building->init("맵툴버튼타이틀탭", L"Bd", 10, imgReX + (_btnImgReWidth * 1), imgReY - (_btnImgReHeight), PointMake(1, 7), PointMake(0, 7), _btnScale);
	_btnT_item = new fButton;
	_btnT_item->init("맵툴버튼타이틀탭",     L"It", 10, imgReX + (_btnImgReWidth * 2), imgReY - (_btnImgReHeight), PointMake(1, 7), PointMake(0, 7), _btnScale);
	_btnT_weapon = new fButton;
	_btnT_weapon->init("맵툴버튼타이틀탭",   L"Wp", 10, imgReX + (_btnImgReWidth * 3), imgReY - (_btnImgReHeight), PointMake(1, 7), PointMake(0, 7), _btnScale);
	_btnT_enemy = new fButton;
	_btnT_enemy->init("맵툴버튼타이틀탭",    L"Em", 10, imgReX + (_btnImgReWidth * 4), imgReY - (_btnImgReHeight), PointMake(1, 7), PointMake(0, 7), _btnScale);
	//---------------------------------------------------------------------------------------------------------------------------------------------

	//------------------------------------------------------------------ Edit 버튼 ----------------------------------------------------------------
	_btnAllReset = new fButton;
	_btnAllReset->init("맵툴버튼타이틀탭", L"R", 18, imgReX + (_btnImgReWidth * 5), imgReY, PointMake(1, 7), PointMake(0, 7), _btnScale);
	
	_btnEraser = new fButton;
	_btnEraser->init("맵툴버튼타이틀탭",    L"E", 18, imgReX + (_btnImgReWidth * 4), imgReY, PointMake(1, 7), PointMake(0, 7), _btnScale);
	_btnOneEraser = new fButton;
	_btnOneEraser->init("맵툴버튼타이틀탭", L"1", 10, imgReX + (_btnImgReWidth * 4), imgReY - (_btnImgReHeight), PointMake(1, 7), PointMake(0, 7), _btnScale);
	_btnAllEraser = new fButton;
	_btnAllEraser->init("맵툴버튼타이틀탭", L"A", 10, imgReX + (_btnImgReWidth * 5), imgReY - (_btnImgReHeight), PointMake(1, 7), PointMake(0, 7), _btnScale);
	//--------------------------------------------------------------------------------------------------------------------------------------------

	//------------------------------------------------------------------ Etc 버튼 ----------------------------------------------------------------
	imgReX = 850;
	imgReY = WINSIZEY - (105);

	_btnArrowL = new fButton;
	_btnArrowL->init("맵툴버튼화살", L"", 5, imgReX - 30, imgReY, PointMake(1, 0), PointMake(0, 0), 1);
	_btnArrowR = new fButton;
	_btnArrowR->init("맵툴버튼화살", L"", 5, imgReX + 30, imgReY, PointMake(1, 1), PointMake(0, 1), 1);

	_btnTabNum = 1;
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
	}

	if (_btnAllEraser->getBtnOn())
	{
		btnTileAllEraser();
		_btnAllEraser->setBtnOff(false);
	}
	//-----------------------
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
	}
	//-------------------------------

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
	}
}


void mapTool::menuTabArrowAction()
{
	if (_btnArrowL->)
	{
		TABMAXNUM
	}
}