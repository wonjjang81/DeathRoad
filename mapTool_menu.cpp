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
			//탭 변경
			menuTerrainTileChange(_btnTabNum);
			//선택한 타일 정보 가져오기
			sTileInputTerrain(_btnTabNum);	
		break;
		case MENU_BULIDING:
			_btnArrowL->update();
			_btnArrowR->update();

			//탭 넘버 카운팅
			menuTabArrowAction();
			//탭 변경
			menuBuildingTileChange(_btnTabNum);
			//선택한 타일 정보 가져오기
			sTileInputBuilding(_btnTabNum);
		break;
		case MENU_ITEM:
			_btnArrowL->update();
			_btnArrowR->update();

			//탭 넘버 카운팅
			menuTabArrowAction();
			//탭 변경
			menuItemTileChange(_btnTabNum);
			//선택한 타일 정보 가져오기
			sTileInputItem(_btnTabNum);
		break;
		case MENU_WEAPON:
			_btnArrowL->update();
			_btnArrowR->update();

			//탭 넘버 카운팅
			menuTabArrowAction();
			//탭 변경
			menuWeaponTileChange(_btnTabNum);
			//선택한 타일 정보 가져오기
			sTileInputWeapon(_btnTabNum);
		break;
		case MENU_ENEMY:

		break;
		case MENU_SETTING:
			//버튼생성
			_isSetBtnOn = true;

			if (_btnSave->getBtnOn())
			{
				save();
				_btnSave->setBtnOff(false);
			}
			if (_btnLoad->getBtnOn())
			{
				load();
				_btnLoad->setBtnOff(false);
			}			
		break;
	}

	//셋팅버튼 초기화
	if (_menuTab.menuType != MENU_SETTING)
	{
		_isSetBtnOn = false;
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
			_btnArrowL->render();
			_btnArrowR->render();

			//탭 넘버
			D2DMANAGER->drawIntText(L"", _btnTabNum, 847, WINSIZEY - (113));
		break;
		case MENU_ITEM:
			_btnArrowL->render();
			_btnArrowR->render();

			//탭 넘버
			D2DMANAGER->drawIntText(L"", _btnTabNum, 847, WINSIZEY - (113));
		break;
		case MENU_WEAPON:
			_btnArrowL->render();
			_btnArrowR->render();

			//탭 넘버
			D2DMANAGER->drawIntText(L"", _btnTabNum, 847, WINSIZEY - (113));
		break;
		case MENU_ENEMY:
			_btnArrowL->render();
			_btnArrowR->render();

			//탭 넘버
			D2DMANAGER->drawIntText(L"", _btnTabNum, 847, WINSIZEY - (113));
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
				_btnTabNum = 1;
				_preTabNum = 0;
			break;
			case MENU_ITEM:
				//초기화
				_menuTab.typeChange = false;
				removeAllChild();
				_btnTabNum = 1;
				_preTabNum = 0;
			break;
			case MENU_WEAPON:
				//초기화
				_menuTab.typeChange = false;
				removeAllChild();
				_btnTabNum = 1;
				_preTabNum = 0;
			break;
			case MENU_ENEMY:
				//초기화
				_menuTab.typeChange = false;
				removeAllChild();
				_btnTabNum = 1;
				_preTabNum = 0;
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

			_tileFloor = new sampleTile;
			_tileFloor->init("맵툴타일바닥", ATTR_MOVE, TYPE_TERRAIN, ANCHOR_LEFTTOP, OVERPO_NO, 1.5);
			addChild(_tileFloor);
		break;
		case 2:
			removeAllChild();

			_tileStreet = new sampleTile;
			_tileStreet->init("맵툴타일거리", ATTR_MOVE, TYPE_TERRAIN, ANCHOR_LEFTTOP, OVERPO_NO, 1.5);
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

//빌딩 타일교체
void mapTool::menuBuildingTileChange(int num)
{
	//예외처리: 탭이 변경되지 않았으면...통과 
	if (_preTabNum == num) return;

	switch (num)
	{
		case 1:
			removeAllChild();

			_tileBuilding1 = new sampleTile;
			_tileBuilding1->init("맵툴타일빌딩1", ATTR_UNMOVE, TYPE_BUILDING, ANCHOR_BOTTOMCENTER, OVERPO_NO, 1);
			addChild(_tileBuilding1);
		break;
		case 2:
			removeAllChild();
			
			_tileBuilding2 = new sampleTile;
			_tileBuilding2->init("맵툴타일빌딩2", ATTR_UNMOVE, TYPE_BUILDING, ANCHOR_BOTTOMCENTER, OVERPO_NO, 1);
			addChild(_tileBuilding2);
		break;
		case 3:
			removeAllChild();

			_tileFurniture1 = new sampleTile;
			_tileFurniture1->init("맵툴타일가구1", ATTR_UNMOVE, TYPE_BUILDING, ANCHOR_CENTER, OVERPO_NO, 1);
			addChild(_tileFurniture1);
		break;
		case 4:
			removeAllChild();
	
			_tileWall = new sampleTile;
			_tileWall->init("맵툴타일벽", ATTR_UNMOVE, TYPE_BUILDING, ANCHOR_LEFTTOP, OVERPO_YES, 1.5);
			addChild(_tileWall);
		break;
		case 5:
			removeAllChild();

			_tileDoor = new sampleTile;
			_tileDoor->init("맵툴타일문", ATTR_UNMOVE, TYPE_BUILDING, ANCHOR_LEFTTOP, OVERPO_YES, 1.5);
			addChild(_tileDoor);
		break;
		case 6:
			removeAllChild();

			_tileShelves = new sampleTile;
			_tileShelves->init("맵툴타일책장", ATTR_UNMOVE, TYPE_FURNITURE, ANCHOR_BOTTOMCENTER, OVERPO_NO, 1.5);
			addChild(_tileShelves);
		break;
		case 7:
			removeAllChild();

			_tileTree1 = new sampleTile;
			_tileTree1->init("맵툴타일나무", ATTR_MOVE, TYPE_ROAD, ANCHOR_BOTTOMCENTER, OVERPO_NO, 1.5);
			addChild(_tileTree1);
		break;
		case 8:
			removeAllChild();

		break;
	}

	_preTabNum = num;
}

//아이템 교체
void mapTool::menuItemTileChange(int num)
{
	//예외처리: 탭이 변경되지 않았으면...통과 
	if (_preTabNum == num) return;

	switch (num)
	{
		case 1:
			removeAllChild();

			_tileItem1 = new sampleTile;
			_tileItem1->init("맵툴타일아이템", ATTR_UNMOVE, TYPE_ITEM, ANCHOR_LEFTTOP, OVERPO_NO, 1.5);
			addChild(_tileItem1);
		break;
		case 2:
			removeAllChild();

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

//무기 교체
void mapTool::menuWeaponTileChange(int num)
{
	//예외처리: 탭이 변경되지 않았으면...통과 
	if (_preTabNum == num) return;

	switch (num)
	{
		case 1:
			removeAllChild();

			_tileWeapon1 = new sampleTile;
			_tileWeapon1->init("맵툴타일무기", ATTR_UNMOVE, TYPE_WEAPON, ANCHOR_CENTER, OVERPO_NO, 3);
			addChild(_tileWeapon1);
		break;
		case 2:
			removeAllChild();

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

//======================== 타일정보 가져오기 Start ========================
//선택한 샘플타일 클래스 정보 가져오기
void mapTool::selectTileInput(sampleTile* selectTile)
{
	if (_menuTabOn && selectTile->_selectVTile.size() != 0)
	{
		_drawTile = selectTile->_selectVTile[0];
	}
}

//지형정보 
void mapTool::sTileInputTerrain(int num)
{
	switch (num)
	{
		case 1:
			selectTileInput(_tileFloor);
		break;
		case 2:
			selectTileInput(_tileStreet);
		break;
		case 3:
			
		break;
		case 4:

		break;
		case 5:

		break;
	}
}

//빌딩정보
void mapTool::sTileInputBuilding(int num)
{
	switch (num)
	{
		case 1:
			selectTileInput(_tileBuilding1);
		break;
		case 2:
			selectTileInput(_tileBuilding2);
		break;
		case 3:
			selectTileInput(_tileFurniture1);
		break;
		case 4:
			selectTileInput(_tileWall);
		break;
		case 5:
			selectTileInput(_tileDoor);
		break;
		case 6:
			selectTileInput(_tileShelves);
		break;
		case 7:
			selectTileInput(_tileTree1);
		break;
		case 8:
		
		break;
	}
}

//아이템 정보
void mapTool::sTileInputItem(int num)
{
	switch (num)
	{
		case 1:
			selectTileInput(_tileItem1);
		break;
		case 2:
		
		break;
		case 3:
	
		break;
		case 4:

		break;
		case 5:

		break;
	}
}

//무기 정보
void mapTool::sTileInputWeapon(int num)
{
	switch (num)
	{
		case 1:
			selectTileInput(_tileWeapon1);
		break;
		case 2:
		
		break;
		case 3:
		
		break;
		case 4:

		break;
		case 5:

		break;
	}
}
//========================= 타일정보 가져오기 End =========================
