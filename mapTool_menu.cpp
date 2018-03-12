#include "stdafx.h"
#include "mapTool.h"


void mapTool::menuTerrainSetup()
{
	_menuTab.imgTab = IMAGEMANAGER->findImage("맵툴메뉴창지형");
	_menuTab.menuType = MENU_TERRAIN;
	_menuTab.typeChange = true;
}

void mapTool::menuBuilidingSetup()
{
	_menuTab.imgTab = IMAGEMANAGER->findImage("맵툴메뉴창빌딩");
	_menuTab.menuType = MENU_BULIDING;
	_menuTab.typeChange = true;
}

void mapTool::menuItemSetup()	 
{
	_menuTab.imgTab = IMAGEMANAGER->findImage("맵툴메뉴창아이템");
	_menuTab.menuType = MENU_ITEM;
	_menuTab.typeChange = true;
}

void mapTool::menuWeaponSetup()	 
{
	_menuTab.imgTab = IMAGEMANAGER->findImage("맵툴메뉴창무기");
	_menuTab.menuType = MENU_WEAPON;
	_menuTab.typeChange = true;
}

void mapTool::menuEnemySetup()
{
	_menuTab.imgTab = IMAGEMANAGER->findImage("맵툴메뉴창적");
	_menuTab.menuType = MENU_ENEMY;
	_menuTab.typeChange = true;
}

void mapTool::menuSettingSetup() 
{
	_menuTab.imgTab = IMAGEMANAGER->findImage("맵툴메뉴창셋팅");
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

			//탭 넘버 카운팅
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

			//탭 넘버
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


//메뉴타입별 샘플타일 생성(차일드씬으로 구성)
void mapTool::menuAddChild()
{
	if (_menuTab.typeChange)
	{
		switch (_menuTab.menuType)
		{
			case MENU_TERRAIN:
				//초기화
				_menuTab.typeChange = false;
				removeAllChild();
				_btnTabNum = 1;
				_preTabNum = 0;
			break;
			case MENU_BULIDING:
				//초기화
				_menuTab.typeChange = false;
				removeAllChild();

			break;
			case MENU_ITEM:
				//초기화
				_menuTab.typeChange = false;
				removeAllChild();

			break;
			case MENU_WEAPON:
				//초기화
				_menuTab.typeChange = false;
				removeAllChild();

			break;
			case MENU_ENEMY:
				//초기화
				_menuTab.typeChange = false;
				removeAllChild();

			break;
			case MENU_SETTING:
				//초기화
				_menuTab.typeChange = false;
				removeAllChild();

			break;
		}

		_menuTabOn = true;
	}
}

//지형 타일교체
void mapTool::menuTerrainTileChange(int num)
{
	//예외처리: 탭이 변경되지 않았으면...통과 
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