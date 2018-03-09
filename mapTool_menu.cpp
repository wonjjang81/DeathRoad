#include "stdafx.h"
#include "mapTool.h"



void mapTool::menuTerrainSetup()
{
	_currentMenu = IMAGEMANAGER->findImage("¸ÊÅø¸Þ´ºÃ¢ÁöÇü");
}

void mapTool::menuBuilidingSetup()
{
	_currentMenu = IMAGEMANAGER->findImage("¸ÊÅø¸Þ´ºÃ¢ºôµù");
}

void mapTool::menuItemSetup()	 
{
	_currentMenu = IMAGEMANAGER->findImage("¸ÊÅø¸Þ´ºÃ¢¾ÆÀÌÅÛ");
}

void mapTool::menuWeaponSetup()	 
{
	_currentMenu = IMAGEMANAGER->findImage("¸ÊÅø¸Þ´ºÃ¢¹«±â");
}

void mapTool::menuEnemySetup()
{
	_currentMenu = IMAGEMANAGER->findImage("¸ÊÅø¸Þ´ºÃ¢Àû");
}

void mapTool::menuSettingSetup() 
{
	_currentMenu = IMAGEMANAGER->findImage("¸ÊÅø¸Þ´ºÃ¢¼ÂÆÃ");
}


void mapTool::menuRender()
{
	if (_currentMenu)
	{
		_currentMenu->render(1.0f, 725, 45);
	}
}