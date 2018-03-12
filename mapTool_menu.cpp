#include "stdafx.h"
#include "mapTool.h"


void mapTool::menuTerrainSetup()
{
	_menuTab.imgTab = IMAGEMANAGER->findImage("�����޴�â����");
	_menuTab.menuType = MENU_TERRAIN;
	_menuTab.typeChange = true;
}

void mapTool::menuBuilidingSetup()
{
	_menuTab.imgTab = IMAGEMANAGER->findImage("�����޴�â����");
	_menuTab.menuType = MENU_BULIDING;
	_menuTab.typeChange = true;
}

void mapTool::menuItemSetup()	 
{
	_menuTab.imgTab = IMAGEMANAGER->findImage("�����޴�â������");
	_menuTab.menuType = MENU_ITEM;
	_menuTab.typeChange = true;
}

void mapTool::menuWeaponSetup()	 
{
	_menuTab.imgTab = IMAGEMANAGER->findImage("�����޴�â����");
	_menuTab.menuType = MENU_WEAPON;
	_menuTab.typeChange = true;
}

void mapTool::menuEnemySetup()
{
	_menuTab.imgTab = IMAGEMANAGER->findImage("�����޴�â��");
	_menuTab.menuType = MENU_ENEMY;
	_menuTab.typeChange = true;
}

void mapTool::menuSettingSetup() 
{
	_menuTab.imgTab = IMAGEMANAGER->findImage("�����޴�â����");
	_menuTab.menuType = MENU_SETTING;
	_menuTab.typeChange = true;
}

void mapTool::menuUpdate()
{
	menuAddChild();

	switch (_menuTab.menuType)
	{
		case MENU_TERRAIN:
			_btnArrowL->update();
			_btnArrowR->update();
		break;
		case MENU_BULIDING:

		break;
		case MENU_ITEM:

		break;
		case MENU_WEAPON:

		break;
		case MENU_ENEMY:

		break;
		case MENU_SETTING:

		break;
	}

}

void mapTool::menuRender()
{
	if (_menuTab.imgTab)
	{
		_menuTab.imgTab->render(1.0f, 725, 45);
	}

	switch (_menuTab.menuType)
	{
		case MENU_TERRAIN:
			_btnArrowL->render();
			_btnArrowR->render();
		break;
		case MENU_BULIDING:

		break;
		case MENU_ITEM:

		break;
		case MENU_WEAPON:

		break;
		case MENU_ENEMY:

		break;
		case MENU_SETTING:

		break;
	}

}


//�޴�Ÿ�Ժ� ����Ÿ�� ����(���ϵ������ ����)
void mapTool::menuAddChild()
{
	if (_menuTab.typeChange)
	{
		switch (_menuTab.menuType)
		{
		case MENU_TERRAIN:
			_menuTab.typeChange = false;
			removeAllChild();

			_menuTr = new mapTool_menu_terrain;
			_menuTr->init();
			addChild(_menuTr);
			break;
		case MENU_BULIDING:
			removeAllChild();
			_menuTab.typeChange = false;
			break;
		case MENU_ITEM:
			removeAllChild();
			_menuTab.typeChange = false;
			break;
		case MENU_WEAPON:
			removeAllChild();
			_menuTab.typeChange = false;
			break;
		case MENU_ENEMY:
			removeAllChild();
			_menuTab.typeChange = false;
			break;
		case MENU_SETTING:
			removeAllChild();
			_menuTab.typeChange = false;
			break;
		}

		_menuTabOn = true;
	}
}