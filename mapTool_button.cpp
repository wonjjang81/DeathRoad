#include "stdafx.h"
#include "mapTool.h"


void mapTool::btnSetup()
{
	_btnScale = 2;
	int imgReWidth = IMAGEMANAGER->findImage("¸ÊÅø¹öÆ°Å¸ÀÌÆ²ÅÇ")->getFrameWidth() * _btnScale;
	int imgReHeight = IMAGEMANAGER->findImage("¸ÊÅø¹öÆ°Å¸ÀÌÆ²ÅÇ")->getFrameHeight() * _btnScale;
	int imgReX = 745 - imgReWidth / 2;
	int imgReY = imgReHeight / 2 - 15;

	_btnTerrain = new button;
	_btnTerrain->init("¸ÊÅø¹öÆ°Å¸ÀÌÆ²ÅÇ",  imgReX,					  imgReY, PointMake(1, 0), PointMake(0, 0), menuTerrainSetup, _btnScale);
	_btnBuiliding = new button;
	_btnBuiliding->init("¸ÊÅø¹öÆ°Å¸ÀÌÆ²ÅÇ",imgReX + (imgReWidth * 1), imgReY, PointMake(1, 1), PointMake(0, 1), menuBuilidingSetup, _btnScale);
	_btnItems = new button;
	_btnItems->init("¸ÊÅø¹öÆ°Å¸ÀÌÆ²ÅÇ",    imgReX + (imgReWidth * 2), imgReY, PointMake(1, 2), PointMake(0, 2), menuItemSetup, _btnScale);
	_btnWeapon = new button;
	_btnWeapon->init("¸ÊÅø¹öÆ°Å¸ÀÌÆ²ÅÇ",   imgReX + (imgReWidth * 3), imgReY, PointMake(1, 3), PointMake(0, 3), menuWeaponSetup, _btnScale);
	_btnEnemy = new button;
	_btnEnemy->init("¸ÊÅø¹öÆ°Å¸ÀÌÆ²ÅÇ",	   imgReX + (imgReWidth * 4), imgReY, PointMake(1, 4), PointMake(0, 4), menuEnemySetup, _btnScale);
	_btnSetting = new button;
	_btnSetting->init("¸ÊÅø¹öÆ°Å¸ÀÌÆ²ÅÇ",  imgReX + (imgReWidth * 5), imgReY, PointMake(1, 5), PointMake(0, 5), menuSettingSetup, _btnScale);
}

void mapTool::btnUpdate()
{
	_btnTerrain->update();
	_btnBuiliding->update();
	_btnItems->update();
	_btnWeapon->update();
	_btnEnemy->update();
	_btnSetting->update();
}

void mapTool::btnRender()
{
	_btnTerrain->render(_btnScale);
	_btnBuiliding->render(_btnScale);
	_btnItems->render(_btnScale);
	_btnWeapon->render(_btnScale);
	_btnEnemy->render(_btnScale);
	_btnSetting->render(_btnScale);
}