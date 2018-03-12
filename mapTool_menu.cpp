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

			//�� �ѹ� ī����
			menuTabArrowAction();
			menuTerrainTileChange(_btnTabNum);
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

			//�� �ѹ�
			D2DMANAGER->drawIntText(L"", _btnTabNum, 847, WINSIZEY - (113));
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
				//�ʱ�ȭ
				_menuTab.typeChange = false;
				removeAllChild();
				_btnTabNum = 1;
				_preTabNum = 0;
			break;
			case MENU_BULIDING:
				//�ʱ�ȭ
				_menuTab.typeChange = false;
				removeAllChild();

			break;
			case MENU_ITEM:
				//�ʱ�ȭ
				_menuTab.typeChange = false;
				removeAllChild();

			break;
			case MENU_WEAPON:
				//�ʱ�ȭ
				_menuTab.typeChange = false;
				removeAllChild();

			break;
			case MENU_ENEMY:
				//�ʱ�ȭ
				_menuTab.typeChange = false;
				removeAllChild();

			break;
			case MENU_SETTING:
				//�ʱ�ȭ
				_menuTab.typeChange = false;
				removeAllChild();

			break;
		}

		_menuTabOn = true;
	}
}

//���� Ÿ�ϱ�ü
void mapTool::menuTerrainTileChange(int num)
{
	//����ó��: ���� ������� �ʾ�����...��� 
	if (_preTabNum == num) return;

	switch (num)
	{
		case 1:
			removeAllChild();

			_tileFloor = new tileFloor;
			_tileFloor->init();
			addChild(_tileFloor);
		break;
		case 2:
			removeAllChild();

			_tileStreet = new tileStreet;
			_tileStreet->init();
			addChild(_tileStreet);
		break;
		case 3:
			removeAllChild();

		break;
		case 4:
			removeAllChild();

		break;
		case 5:
			removeAllChild();

		break;
	}

	_preTabNum = num;
}