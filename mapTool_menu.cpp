#include "stdafx.h"
#include "mapTool.h"



void mapTool::menuTerrainSetup()
{
	_currentMenu = IMAGEMANAGER->findImage("�����޴�â����");
}

void mapTool::menuBuilidingSetup()
{
	_currentMenu = IMAGEMANAGER->findImage("�����޴�â����");
}

void mapTool::menuItemSetup()	 
{
	_currentMenu = IMAGEMANAGER->findImage("�����޴�â������");
}

void mapTool::menuWeaponSetup()	 
{
	_currentMenu = IMAGEMANAGER->findImage("�����޴�â����");
}

void mapTool::menuEnemySetup()
{
	_currentMenu = IMAGEMANAGER->findImage("�����޴�â��");
}

void mapTool::menuSettingSetup() 
{
	_currentMenu = IMAGEMANAGER->findImage("�����޴�â����");
}


void mapTool::menuRender()
{
	if (_currentMenu)
	{
		_currentMenu->render(1.0f, 725, 45);
	}
}