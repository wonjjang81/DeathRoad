#include "stdafx.h"
#include "mapTool.h"


void mapTool::menuTerrainSetup()
{
	MENU.imgTab = IMAGEMANAGER->findImage("¸ÊÅø¸Þ´ºÃ¢ÁöÇü");
	MENU.menuType = MENU_TERRAIN;
	MENU.typeChange = true;
}

void mapTool::menuBuilidingSetup()
{
	MENU.imgTab = IMAGEMANAGER->findImage("¸ÊÅø¸Þ´ºÃ¢ºôµù");
	MENU.menuType = MENU_BULIDING;
	MENU.typeChange = true;
}

void mapTool::menuItemSetup()	 
{
	MENU.imgTab = IMAGEMANAGER->findImage("¸ÊÅø¸Þ´ºÃ¢¾ÆÀÌÅÛ");
	MENU.menuType = MENU_ITEM;
	MENU.typeChange = true;
}

void mapTool::menuWeaponSetup()	 
{
	MENU.imgTab = IMAGEMANAGER->findImage("¸ÊÅø¸Þ´ºÃ¢¹«±â");
	MENU.menuType = MENU_WEAPON;
	MENU.typeChange = true;
}

void mapTool::menuEnemySetup()
{
	MENU.imgTab = IMAGEMANAGER->findImage("¸ÊÅø¸Þ´ºÃ¢Àû");
	MENU.menuType = MENU_ENEMY;
	MENU.typeChange = true;
}

void mapTool::menuSettingSetup() 
{
	MENU.imgTab = IMAGEMANAGER->findImage("¸ÊÅø¸Þ´ºÃ¢¼ÂÆÃ");
	MENU.menuType = MENU_SETTING;
	MENU.typeChange = true;
}

void mapTool::menuAddChild()
{
	if (MENU.typeChange)
	{
		switch (MENU.menuType)
		{
			case MENU_TERRAIN:
				MENU.typeChange = false;
				removeAllChild();

				_menuTr = new mapTool_menu_terrain;
				_menuTr->init();
				addChild(_menuTr);
			break;
			case MENU_BULIDING:
				removeAllChild();
				MENU.typeChange = false;
			break;
			case MENU_ITEM:
				removeAllChild();
				MENU.typeChange = false;
			break;
			case MENU_WEAPON:
				removeAllChild();
				MENU.typeChange = false;
			break;
			case MENU_ENEMY:
				removeAllChild();
				MENU.typeChange = false;
			break;
			case MENU_SETTING:
				removeAllChild();
				MENU.typeChange = false;
			break;
		}
	}
}

void mapTool::menuRender()
{
	if (MENU.imgTab)
	{
		MENU.imgTab->render(1.0f, 725, 45);
	}

	if (MENU.imgTile)
	{
		MENU.imgTile->render(1.0f, 770, 190, 0, 1.5f);
	}

}