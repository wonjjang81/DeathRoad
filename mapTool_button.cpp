#include "stdafx.h"
#include "mapTool.h"


void mapTool::btnSetup()
{
	//------------------------------------------------------------------ �޴� �� ------------------------------------------------------------------
	_btnScale = 2;
	_btnImgReWidth = IMAGEMANAGER->findImage("������ưŸ��Ʋ��")->getFrameWidth() * _btnScale;
	_btnImgReHeight = IMAGEMANAGER->findImage("������ưŸ��Ʋ��")->getFrameHeight() * _btnScale;
	float imgReX = 745 - _btnImgReWidth / 2;
	float imgReY = _btnImgReHeight / 2 - 15;

	_btnTerrain = new button;
	_btnTerrain->init("������ưŸ��Ʋ��",  imgReX,					      imgReY, PointMake(1, 0), PointMake(0, 0), menuTerrainSetup, _btnScale);
	_btnBuiliding = new button;
	_btnBuiliding->init("������ưŸ��Ʋ��",imgReX + (_btnImgReWidth * 1), imgReY, PointMake(1, 1), PointMake(0, 1), menuBuilidingSetup, _btnScale);
	_btnItems = new button;
	_btnItems->init("������ưŸ��Ʋ��",    imgReX + (_btnImgReWidth * 2), imgReY, PointMake(1, 2), PointMake(0, 2), menuItemSetup, _btnScale);
	_btnWeapon = new button;
	_btnWeapon->init("������ưŸ��Ʋ��",   imgReX + (_btnImgReWidth * 3), imgReY, PointMake(1, 3), PointMake(0, 3), menuWeaponSetup, _btnScale);
	_btnEnemy = new button;
	_btnEnemy->init("������ưŸ��Ʋ��",	   imgReX + (_btnImgReWidth * 4), imgReY, PointMake(1, 4), PointMake(0, 4), menuEnemySetup, _btnScale);
	_btnSetting = new button;
	_btnSetting->init("������ưŸ��Ʋ��",  imgReX + (_btnImgReWidth * 5), imgReY, PointMake(1, 5), PointMake(0, 5), menuSettingSetup, _btnScale);
	//---------------------------------------------------------------------------------------------------------------------------------------------

	//----------------------------------------------------------------- Ÿ�� ���� -----------------------------------------------------------------
	imgReX = 750 - _btnImgReWidth / 2;
	imgReY = WINSIZEY - (_btnImgReHeight + 10);
	_btnRCenterX = imgReX + (_btnImgReWidth / 4);
	_btnRCenterY = imgReY + (_btnImgReHeight / 4);

	//�Ӽ����� ��ư
	_btnAttribute = new fButton;
	_btnAttribute->init("������ưŸ��Ʋ��", L"A", 18,  imgReX, imgReY, PointMake(1, 6), PointMake(0, 6), _btnScale);

	_btnA_move = new fButton;
	_btnA_move->init("������ưŸ��Ʋ��",    L"X", 10, imgReX,						  imgReY - (_btnImgReHeight), PointMake(1, 6), PointMake(0, 6), _btnScale);
	_btnA_unMove = new fButton;
	_btnA_unMove->init("������ưŸ��Ʋ��",  L"X", 10, imgReX + (_btnImgReWidth * 1), imgReY - (_btnImgReHeight), PointMake(1, 6), PointMake(0, 6), _btnScale);
	_btnA_ARender = new fButton;
	_btnA_ARender->init("������ưŸ��Ʋ��", L"X", 10, imgReX + (_btnImgReWidth * 2), imgReY - (_btnImgReHeight), PointMake(1, 6), PointMake(0, 6), _btnScale);

	//Ÿ�Ժ��� ��ư
	_btnTileType = new fButton;
	_btnTileType->init("������ưŸ��Ʋ��",   L"A", 18, imgReX + (_btnImgReWidth * 1), imgReY, PointMake(1, 7), PointMake(0, 7), _btnScale);

	_btnT_terrain = new fButton;
	_btnT_terrain->init("������ưŸ��Ʋ��",  L"RN", 10, imgReX,                        imgReY - (_btnImgReHeight), PointMake(1, 7), PointMake(0, 7), _btnScale);
	_btnT_building = new fButton;
	_btnT_building->init("������ưŸ��Ʋ��", L"RC", 10, imgReX + (_btnImgReWidth * 1), imgReY - (_btnImgReHeight), PointMake(1, 7), PointMake(0, 7), _btnScale);
	_btnT_item = new fButton;
	_btnT_item->init("������ưŸ��Ʋ��",     L"RO", 10, imgReX + (_btnImgReWidth * 2), imgReY - (_btnImgReHeight), PointMake(1, 7), PointMake(0, 7), _btnScale);
	_btnT_weapon = new fButton;
	_btnT_weapon->init("������ưŸ��Ʋ��",   L"RR", 10, imgReX + (_btnImgReWidth * 3), imgReY - (_btnImgReHeight), PointMake(1, 7), PointMake(0, 7), _btnScale);
	_btnT_enemy = new fButton;
	_btnT_enemy->init("������ưŸ��Ʋ��",    L"X", 10, imgReX + (_btnImgReWidth * 4), imgReY - (_btnImgReHeight), PointMake(1, 7), PointMake(0, 7), _btnScale);
	//---------------------------------------------------------------------------------------------------------------------------------------------

	//------------------------------------------------------------------ Edit ��ư ----------------------------------------------------------------
	imgReX = 962;
	imgReY = WINSIZEY - (40);
	float tmpScale = 1.5;
	float tmpImgWidth = _btnImgReWidth / _btnScale * tmpScale;
	float tmpImgHeight = _btnImgReHeight / _btnScale * tmpScale;


	_btnAllReset = new fButton;
	_btnAllReset->init("������ưŸ��Ʋ��",  L"R", 18, imgReX, imgReY, PointMake(1, 8), PointMake(0, 8), tmpScale);
																	  
	_btnEraser = new fButton;										  
	_btnEraser->init("������ưŸ��Ʋ��",    L"E", 18, imgReX - (tmpImgWidth * 1), imgReY,					   PointMake(1, 8), PointMake(0, 8), tmpScale);
	_btnOneEraser = new fButton;
	_btnOneEraser->init("������ưŸ��Ʋ��", L"1", 18, imgReX - (tmpImgWidth * 1), imgReY - (tmpImgHeight * 1), PointMake(1, 8), PointMake(0, 8), tmpScale);
	_btnAllEraser = new fButton;
	_btnAllEraser->init("������ưŸ��Ʋ��", L"-", 18, imgReX					, imgReY - (tmpImgHeight * 1), PointMake(1, 8), PointMake(0, 8), tmpScale);
	_btnAllSet = new fButton;
	_btnAllSet->init("������ưŸ��Ʋ��",    L"+", 18, imgReX - (tmpImgWidth * 2), imgReY - (tmpImgHeight * 1), PointMake(1, 8), PointMake(0, 8), tmpScale);
	//--------------------------------------------------------------------------------------------------------------------------------------------

	//------------------------------------------------------------------ Etc ��ư ----------------------------------------------------------------
	imgReX = 850;
	imgReY = WINSIZEY - (105);

	_btnArrowL = new fButton;
	_btnArrowL->init("������ưȭ��", L"", 5, imgReX - 30, imgReY, PointMake(1, 0), PointMake(0, 0), 1);
	_btnArrowR = new fButton;
	_btnArrowR->init("������ưȭ��", L"", 5, imgReX + 30, imgReY, PointMake(1, 1), PointMake(0, 1), 1);

	_btnTabNum = 1;  //���� �ǳѹ�
	_preTabNum = 0;	 //���� �ǳѹ�
	//--------------------------------------------------------------------------------------------------------------------------------------------

	//----------------------------------------------------------------- Setting ��ư -------------------------------------------------------------
	imgReX = 790;
	imgReY = 120;

	_btnNewTile = new fButton;
	_btnNewTile->initB("������ư", L"NEW", 18, imgReX, imgReY,       14, 4, PointMake(1, 2), PointMake(0, 2), 3);
	_btnSave = new fButton;
	_btnSave->initB("������ư",   L"SAVE", 18, imgReX, imgReY + 60,  11, 4, PointMake(1, 0), PointMake(0, 0), 3);
	_btnLoad = new fButton;
	_btnLoad->initB("������ư",   L"LOAD", 18, imgReX, imgReY + 120, 11, 4, PointMake(1, 1), PointMake(0, 1), 3);
	_btnExit = new fButton;
	_btnExit->initB("������ư",   L"EXIT", 18, imgReX, imgReY + 180, 11, 4, PointMake(1, 3), PointMake(0, 3), 3);

	_isSetBtnOn = false;
	//--------------------------------------------------------------------------------------------------------------------------------------------

}

void mapTool::btnUpdate()
{
	//------- �޴� �� -------
	_btnTerrain->update();
	_btnBuiliding->update();
	_btnItems->update();
	_btnWeapon->update();
	_btnEnemy->update();
	_btnSetting->update();
	//-----------------------

	//------ Ÿ�� ���� -------
	_btnAttribute->update();
	_btnTileType->update();

	//��ư On/Off
	btnSwitch();

	//�Ӽ���ư ������
	if (_btnAttribute->getBtnOn())
	{
		_btnA_move->update();
		_btnA_unMove->update();
		_btnA_ARender->update();
	}

	//Ÿ�Թ�ư ������
	if (_btnTileType->getBtnOn())
	{
		_btnT_terrain->update();
		_btnT_building->update();
		_btnT_item->update();
		_btnT_weapon->update();
		_btnT_enemy->update();
	}
	//-----------------------

	//------ Edit ��ư ------
	_btnAllReset->update();
	btnAllReset();

	_btnEraser->update();
	if (_btnEraser->getBtnOn())
	{
		_btnOneEraser->update();
		_btnAllEraser->update();
		_btnAllSet->update();
	}

	//��� Ÿ������ �����
	if (_btnAllEraser->getBtnOn())
	{
		btnTileAllEraser();
		_btnAllEraser->setBtnOff(false);
	}

	//��� Ÿ�Ͽ� ������ Ÿ������ �ֱ�
	if (_btnAllSet->getBtnOn())
	{
		btnTileAllSet(_drawTile);
		_btnAllSet->setBtnOff(false);
	}
	//-----------------------

	//---- SaveLoad ��ư ----
	if (_isSetBtnOn)
	{
		_btnNewTile->update();
		_btnSave->update();
		_btnLoad->update();
		_btnExit->update();
	}
	//-----------------------

	//newTile
	if (_btnNewTile->getBtnOn())
	{
		newTileMap();
		_btnNewTile->setBtnOff(false);
	}
}

void mapTool::btnRender()
{
	//----------- �޴� �� -----------
	_btnTerrain->render(_btnScale);
	_btnBuiliding->render(_btnScale);
	_btnItems->render(_btnScale);
	_btnWeapon->render(_btnScale);
	_btnEnemy->render(_btnScale);
	_btnSetting->render(_btnScale);
	//-------------------------------

	//---------- Ÿ�� ���� ----------
	_btnAttribute->render();
	_btnTileType->render();

	//�Ӽ���ư ������
	if (_btnAttribute->getBtnOn())
	{
		_btnA_move->render();
		_btnA_unMove->render();
		_btnA_ARender->render();
	}

	//Ÿ�Թ�ư ������
	if (_btnTileType->getBtnOn())
	{
		_btnT_terrain->render();
		_btnT_building->render();
		_btnT_item->render();
		_btnT_weapon->render();
		_btnT_enemy->render();
	}
	//-------------------------------

	//---------- Edit ��ư ----------
	_btnAllReset->render();

	_btnEraser->render();
	if (_btnEraser->getBtnOn())
	{
		_btnOneEraser->render();
		_btnAllEraser->render();
		_btnAllSet->render();
	}
	//-------------------------------

	//---- SaveLoad ��ư ----
	if (_isSetBtnOn)
	{
		_btnNewTile->render();
		_btnSave->render();
		_btnLoad->render();
		_btnExit->render();
	}
	//-----------------------
}


//��ư ON/OFF
void mapTool::btnSwitch()
{
	//-------------------------------------------- �Ӽ���ư --------------------------------------------
	//�Ϻι�ư ON/OFF
	if (!_btnAttribute->getBtnOn())
	{
		_btnA_move->setBtnOff(false);
		_btnA_unMove->setBtnOff(false);
		_btnA_ARender->setBtnOff(false);
	}
	//--------------------------------------------------------------------------------------------------

	//-------------------------------------------- Ÿ�Թ�ư --------------------------------------------
	//�Ϻι�ư ON/OFF
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
	//�Ϻι�ư ON/OFF
	if (!_btnEraser->getBtnOn())
	{
		_btnOneEraser->setBtnOff(false);
		_btnAllEraser->setBtnOff(false);
		_btnAllSet->setBtnOff(false);
	}
	//--------------------------------------------------------------------------------------------------
}


void mapTool::btnAllReset()
{
	if (_btnAllReset->getBtnOn()) //��ưON �̸�...
	{
		_btnAttribute->setBtnOff(false);  //�Ӽ���ư Off
		_btnTileType->setBtnOff(false);   //Ÿ�Թ�ư Off
		_btnEraser->setBtnOff(false);     //Ÿ���ʱ�ȭ ��ư Off
		_btnAllReset->setBtnOff(false);   //���¹�ư Off

		//���� FillRect �����
		samTileFRectInitialize();
		//������ Ÿ������ ����ü �ʱ�ȭ
		ZeroMemory(&_drawTile, sizeof(tagTile));
	}
}


//�޴��ϴ� ȭ��ǥ ��ư �׼�: �� �ѹ� ī���� 
void mapTool::menuTabArrowAction()
{
	//������
	if (_btnArrowL->getBtnOn())
	{
		_btnTabNum--;

		if (_btnTabNum <= 1) _btnTabNum = 1;
		_btnArrowL->setBtnOff(false);
	}

	//������
	if (_btnArrowR->getBtnOn())
	{
		_btnTabNum++;

		if (_btnTabNum >= TABMAXNUM) _btnTabNum = TABMAXNUM;
		_btnArrowR->setBtnOff(false);
	}
}