#include "stdafx.h"
#include "mapTool.h"


void mapTool::tileReAtrribute(tagTile& resetTile)
{

	//����ó��: Ÿ�� ������ �ȵǾ� ������(�̹���X)
	if (resetTile.tileType == TYPE_NONE) return;

	enum BUTTONSELECT
	{
		BTN_MOVE,
		BTN_UNMOVE,
		BTN_ARENDER
	};
	BUTTONSELECT selectBtn;

	//����ó��: ��ư�� �ΰ��̻� Ȱ��ȭ �Ǿ� ���� ���-> ALL ����
	if ((_btnA_move->getBtnOn() && _btnA_unMove->getBtnOn()) ||
		(_btnA_move->getBtnOn() && _btnA_ARender->getBtnOn()) ||
		(_btnA_unMove->getBtnOn() && _btnA_ARender->getBtnOn()) ||
		(_btnA_move->getBtnOn() && _btnA_unMove->getBtnOn() && _btnA_ARender->getBtnOn()))
	{
		_btnAllReset->setBtnOff(true);
	}

	//Ȱ��ȭ�� ��ư ���� �Է� 
	if (_btnA_move->getBtnOn())    selectBtn = BTN_MOVE;
	if (_btnA_unMove->getBtnOn())  selectBtn = BTN_UNMOVE;
	if (_btnA_ARender->getBtnOn()) selectBtn = BTN_ARENDER;

	//��ư ACTION
	switch (selectBtn)
	{
		case BTN_MOVE:

			//�Ӽ�����
			resetTile.attribute = ATTR_MOVE;

		break;
		case BTN_UNMOVE:

			//�Ӽ�����
			resetTile.attribute = ATTR_UNMOVE;

		break;
		case BTN_ARENDER:

			//�Ӽ�����
			resetTile.attribute = ATTR_AFTER_RENDER;

		break;
	}
}

void mapTool::tileReType(tagTile& resetTile)
{
	//����ó��: Ÿ�� ������ �ȵǾ� ������
	//if (resetTile.tileType == TYPE_NONE) return;

	TILE_TYPE selectBtn;

	//����ó��: ��ư�� �ΰ��̻� Ȱ��ȭ �Ǿ� ���� ���-> ALL ����
	if ((_btnT_terrain->getBtnOn() && _btnT_building->getBtnOn()) ||
		(_btnT_terrain->getBtnOn() && _btnT_item->getBtnOn()) ||
		(_btnT_terrain->getBtnOn() && _btnT_weapon->getBtnOn()) ||
		(_btnT_terrain->getBtnOn() && _btnT_enemy->getBtnOn()) ||
		(_btnT_building->getBtnOn() && _btnT_item->getBtnOn()) ||
		(_btnT_building->getBtnOn() && _btnT_weapon->getBtnOn()) ||
		(_btnT_building->getBtnOn() && _btnT_enemy->getBtnOn()) ||
		(_btnT_item->getBtnOn() && _btnT_weapon->getBtnOn()) ||
		(_btnT_item->getBtnOn() && _btnT_enemy->getBtnOn()) ||
		(_btnT_weapon->getBtnOn() && _btnT_enemy->getBtnOn()))
	{
		_btnAllReset->setBtnOff(true);
	}

	//Ȱ��ȭ�� ��ư ���� �Է� 
	if (_btnT_terrain->getBtnOn())   selectBtn = TYPE_TERRAIN;
	if (_btnT_building->getBtnOn())  selectBtn = TYPE_BUILDING;
	if (_btnT_item->getBtnOn())		 selectBtn = TYPE_ITEM;
	if (_btnT_weapon->getBtnOn())	 selectBtn = TYPE_WEAPON;
	if (_btnT_enemy->getBtnOn())	 selectBtn = TYPE_ENEMY;

	//��ư ACTION
	switch (selectBtn)
	{
		case TYPE_TERRAIN:

			//�Ӽ�����
			resetTile.tileType = TYPE_TERRAIN;

		break;
		case TYPE_ROAD:


		break;
		case TYPE_FURNITURE:


		break;
		case TYPE_BUILDING:

			//�Ӽ�����
			resetTile.tileType = TYPE_BUILDING;

		break;
		case TYPE_ITEM:

			//�Ӽ�����
			resetTile.tileType = TYPE_ITEM;

		break;
		case TYPE_WEAPON:

			//�Ӽ�����
			resetTile.tileType = TYPE_WEAPON;

		break;
		case TYPE_ENEMY:

			//�Ӽ�����
			resetTile.tileType = TYPE_ENEMY;

		break;
	}
}

//Ÿ������ �����: 1
void mapTool::btnTile1Eraser(tagTile& resetTile)
{
	resetTile.img = NULL;
	sprintf(resetTile.imgName, "");
	resetTile.attribute = ATTR_NONE;
	resetTile.tileType = TYPE_NONE;
}

//Ÿ������ �����: All
void mapTool::btnTileAllEraser()
{
	//������ Ÿ������ �ʱ�ȭ
	ZeroMemory(&_drawTile, sizeof(tagTile));
	//���� FillRect �����


	//Terrain
	vTileInitialize(_vSaveTr);

	//Building
	vTileInitialize(_vSaveBd);

	//Road
	vTileInitialize(_vSaveRd);

	//Furniture
	vTileInitialize(_vSaveFt);

	//Item
	vTileInitialize(_vSaveIt);

	//Weapon
	vTileInitialize(_vSaveWp);

	//Enemy
	vTileInitialize(_vSaveEm);

}

void mapTool::btnTileAllSet(tagTile& resetTile)
{
	//����ó��
	if (resetTile.tileType == TYPE_NONE) return;

	switch (resetTile.tileType)
	{
		case TYPE_TERRAIN:

			vTileSet(_vSaveTr, resetTile);

		break;		
		case TYPE_ROAD:
			
			vTileSet(_vSaveRd, resetTile);

		break;
		case TYPE_FURNITURE:

			vTileSet(_vSaveFt, resetTile);

		break;
		case TYPE_BUILDING:

			vTileSet(_vSaveBd, resetTile);

		break;
		case TYPE_ITEM:

			vTileSet(_vSaveIt, resetTile);

		break;
		case TYPE_WEAPON:

			vTileSet(_vSaveWp, resetTile);

		break;
		case TYPE_ENEMY:

			vTileSet(_vSaveEm, resetTile);

		break;
	}

}

void mapTool::vTileInitialize(vSaveTile& saveTile)
{
	for (int i = 0; i < saveTile.size(); ++i)
	{
		saveTile[i].img = NULL;
		sprintf(saveTile[i].imgName, "");
		saveTile[i].attribute = ATTR_NONE;
		saveTile[i].tileType = TYPE_NONE;
	}
}

void mapTool::vTileSet(vSaveTile& saveTile, tagTile& resetTile)
{
	for (int i = 0; i < saveTile.size(); ++i)
	{
		saveTile[i].img = resetTile.img;
		sprintf(saveTile[i].imgName, "%s", resetTile.imgName);
		saveTile[i].attribute = resetTile.attribute;
		saveTile[i].tileType = resetTile.tileType;
		saveTile[i].frameX = resetTile.frameX;
		saveTile[i].frameY = resetTile.frameY;
	}
}