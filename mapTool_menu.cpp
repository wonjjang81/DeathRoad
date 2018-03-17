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
			//�� ����
			menuTerrainTileChange(_btnTabNum);
			//������ Ÿ�� ���� ��������
			sTileInputTerrain(_btnTabNum);	
		break;
		case MENU_BULIDING:
			_btnArrowL->update();
			_btnArrowR->update();

			//�� �ѹ� ī����
			menuTabArrowAction();
			//�� ����
			menuBuildingTileChange(_btnTabNum);
			//������ Ÿ�� ���� ��������
			sTileInputBuilding(_btnTabNum);
		break;
		case MENU_ITEM:
			_btnArrowL->update();
			_btnArrowR->update();

			//�� �ѹ� ī����
			menuTabArrowAction();
			//�� ����
			menuItemTileChange(_btnTabNum);
			//������ Ÿ�� ���� ��������
			sTileInputItem(_btnTabNum);
		break;
		case MENU_WEAPON:
			_btnArrowL->update();
			_btnArrowR->update();

			//�� �ѹ� ī����
			menuTabArrowAction();
			//�� ����
			menuWeaponTileChange(_btnTabNum);
			//������ Ÿ�� ���� ��������
			sTileInputWeapon(_btnTabNum);
		break;
		case MENU_ENEMY:

		break;
		case MENU_SETTING:
			//��ư����
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

	//���ù�ư �ʱ�ȭ
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

			//�� �ѹ�
			D2DMANAGER->drawIntText(L"", _btnTabNum, 847, WINSIZEY - (113));
		break;
		case MENU_BULIDING:
			_btnArrowL->render();
			_btnArrowR->render();

			//�� �ѹ�
			D2DMANAGER->drawIntText(L"", _btnTabNum, 847, WINSIZEY - (113));
		break;
		case MENU_ITEM:
			_btnArrowL->render();
			_btnArrowR->render();

			//�� �ѹ�
			D2DMANAGER->drawIntText(L"", _btnTabNum, 847, WINSIZEY - (113));
		break;
		case MENU_WEAPON:
			_btnArrowL->render();
			_btnArrowR->render();

			//�� �ѹ�
			D2DMANAGER->drawIntText(L"", _btnTabNum, 847, WINSIZEY - (113));
		break;
		case MENU_ENEMY:
			_btnArrowL->render();
			_btnArrowR->render();

			//�� �ѹ�
			D2DMANAGER->drawIntText(L"", _btnTabNum, 847, WINSIZEY - (113));
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
				_btnTabNum = 1;
				_preTabNum = 0;
			break;
			case MENU_ITEM:
				//�ʱ�ȭ
				_menuTab.typeChange = false;
				removeAllChild();
				_btnTabNum = 1;
				_preTabNum = 0;
			break;
			case MENU_WEAPON:
				//�ʱ�ȭ
				_menuTab.typeChange = false;
				removeAllChild();
				_btnTabNum = 1;
				_preTabNum = 0;
			break;
			case MENU_ENEMY:
				//�ʱ�ȭ
				_menuTab.typeChange = false;
				removeAllChild();
				_btnTabNum = 1;
				_preTabNum = 0;
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

			_tileFloor = new sampleTile;
			_tileFloor->init("����Ÿ�Ϲٴ�", ATTR_MOVE, TYPE_TERRAIN, ANCHOR_LEFTTOP, OVERPO_NO, 1.5);
			addChild(_tileFloor);
		break;
		case 2:
			removeAllChild();

			_tileStreet = new sampleTile;
			_tileStreet->init("����Ÿ�ϰŸ�", ATTR_MOVE, TYPE_TERRAIN, ANCHOR_LEFTTOP, OVERPO_NO, 1.5);
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

//���� Ÿ�ϱ�ü
void mapTool::menuBuildingTileChange(int num)
{
	//����ó��: ���� ������� �ʾ�����...��� 
	if (_preTabNum == num) return;

	switch (num)
	{
		case 1:
			removeAllChild();

			_tileBuilding1 = new sampleTile;
			_tileBuilding1->init("����Ÿ�Ϻ���1", ATTR_UNMOVE, TYPE_BUILDING, ANCHOR_BOTTOMCENTER, OVERPO_NO, 1);
			addChild(_tileBuilding1);
		break;
		case 2:
			removeAllChild();
			
			_tileBuilding2 = new sampleTile;
			_tileBuilding2->init("����Ÿ�Ϻ���2", ATTR_UNMOVE, TYPE_BUILDING, ANCHOR_BOTTOMCENTER, OVERPO_NO, 1);
			addChild(_tileBuilding2);
		break;
		case 3:
			removeAllChild();

			_tileFurniture1 = new sampleTile;
			_tileFurniture1->init("����Ÿ�ϰ���1", ATTR_UNMOVE, TYPE_BUILDING, ANCHOR_CENTER, OVERPO_NO, 1);
			addChild(_tileFurniture1);
		break;
		case 4:
			removeAllChild();
	
			_tileWall = new sampleTile;
			_tileWall->init("����Ÿ�Ϻ�", ATTR_UNMOVE, TYPE_BUILDING, ANCHOR_LEFTTOP, OVERPO_YES, 1.5);
			addChild(_tileWall);
		break;
		case 5:
			removeAllChild();

			_tileDoor = new sampleTile;
			_tileDoor->init("����Ÿ�Ϲ�", ATTR_UNMOVE, TYPE_BUILDING, ANCHOR_LEFTTOP, OVERPO_YES, 1.5);
			addChild(_tileDoor);
		break;
		case 6:
			removeAllChild();

			_tileShelves = new sampleTile;
			_tileShelves->init("����Ÿ��å��", ATTR_UNMOVE, TYPE_FURNITURE, ANCHOR_BOTTOMCENTER, OVERPO_NO, 1.5);
			addChild(_tileShelves);
		break;
		case 7:
			removeAllChild();

			_tileTree1 = new sampleTile;
			_tileTree1->init("����Ÿ�ϳ���", ATTR_MOVE, TYPE_ROAD, ANCHOR_BOTTOMCENTER, OVERPO_NO, 1.5);
			addChild(_tileTree1);
		break;
		case 8:
			removeAllChild();

		break;
	}

	_preTabNum = num;
}

//������ ��ü
void mapTool::menuItemTileChange(int num)
{
	//����ó��: ���� ������� �ʾ�����...��� 
	if (_preTabNum == num) return;

	switch (num)
	{
		case 1:
			removeAllChild();

			_tileItem1 = new sampleTile;
			_tileItem1->init("����Ÿ�Ͼ�����", ATTR_UNMOVE, TYPE_ITEM, ANCHOR_LEFTTOP, OVERPO_NO, 1.5);
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

//���� ��ü
void mapTool::menuWeaponTileChange(int num)
{
	//����ó��: ���� ������� �ʾ�����...��� 
	if (_preTabNum == num) return;

	switch (num)
	{
		case 1:
			removeAllChild();

			_tileWeapon1 = new sampleTile;
			_tileWeapon1->init("����Ÿ�Ϲ���", ATTR_UNMOVE, TYPE_WEAPON, ANCHOR_CENTER, OVERPO_NO, 3);
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

//======================== Ÿ������ �������� Start ========================
//������ ����Ÿ�� Ŭ���� ���� ��������
void mapTool::selectTileInput(sampleTile* selectTile)
{
	if (_menuTabOn && selectTile->_selectVTile.size() != 0)
	{
		_drawTile = selectTile->_selectVTile[0];
	}
}

//�������� 
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

//��������
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

//������ ����
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

//���� ����
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
//========================= Ÿ������ �������� End =========================
