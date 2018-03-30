#include "stdafx.h"
#include "mapTool.h"


void mapTool::tileReAtrribute(tagTile& resetTile)
{

	//����ó��: Ÿ�� ������ �ȵǾ� ������(�̹���X)
	if (resetTile.tileType != TYPE_TERRAIN && resetTile.tileType != TYPE_DOOR) return;

	enum BUTTONSELECT
	{
		BTN_STARTPOINT,
		BTN_EXITPOINT,
		BTN_DOORPOINT,
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
	if (_btnA_move->getBtnOn())    selectBtn = BTN_STARTPOINT;
	if (_btnA_unMove->getBtnOn())  selectBtn = BTN_EXITPOINT;
	if (_btnA_ARender->getBtnOn()) selectBtn = BTN_DOORPOINT;

	//��ư ACTION
	switch (selectBtn)
	{
		case BTN_STARTPOINT:

			//�Ӽ�����
			resetTile.typeAtt = TYPE_A_TR_START;

		break;
		case BTN_EXITPOINT:

			//�Ӽ�����
			resetTile.typeAtt = TYPE_A_TR_EXIT;

		break;
		case BTN_DOORPOINT:

			//����ó��
			//if (resetTile.id != 0) break;

	
			//�Ӽ�����
			doorIDSet();
			if (resetTile.id < 0) break;
			resetTile.id = _doorId;

		break;
	}
}

void mapTool::tileReType(tagTile& resetTile)
{
	//����ó��: Ÿ�� ������ �ȵǾ� ������
	if (resetTile.tileType == TYPE_NONE || resetTile.tileType == TYPE_TERRAIN) return;

	ATTRIBUTE selectBtn;

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
	if (_btnT_terrain->getBtnOn())   selectBtn = ATTR_CRECT_NONE;
	if (_btnT_building->getBtnOn())  selectBtn = ATTR_CRECT_CENTER;
	if (_btnT_item->getBtnOn())		 selectBtn = ATTR_CRECT_ORIGINAL;
	if (_btnT_weapon->getBtnOn())	 selectBtn = ATTR_CRECT_RESIZE;
	if (_btnT_enemy->getBtnOn())	 selectBtn = ATTR_AFTERRENDER;


	//��ư ACTION
	switch (selectBtn)
	{
		case ATTR_CRECT_NONE:

			if (resetTile.tileType == TYPE_NONE) return;
			if (resetTile.tileType == TYPE_ROAD) return;
			//if (resetTile.tileType == TYPE_TERRAIN) return;
			//�Ӽ�����
			resetTile.attribute = ATTR_CRECT_NONE;

		break;
		case ATTR_CRECT_CENTER:

			if (resetTile.tileType == TYPE_NONE) return;
			if (resetTile.tileType == TYPE_ROAD) return;
			if (resetTile.tileType == TYPE_TERRAIN) return;
			//�Ӽ�����
			resetTile.attribute = ATTR_CRECT_CENTER;

		break;
		case ATTR_CRECT_ORIGINAL:

			if (resetTile.tileType == TYPE_NONE) return;
			if (resetTile.tileType == TYPE_ROAD) return;
			//if (resetTile.tileType == TYPE_TERRAIN) return;
			//�Ӽ�����
			resetTile.attribute = ATTR_CRECT_ORIGINAL;

		break;
		case ATTR_CRECT_RESIZE:

			if (resetTile.tileType == TYPE_NONE) return;
			if (resetTile.tileType == TYPE_ROAD) return;
			if (resetTile.tileType == TYPE_TERRAIN) return;
			//�Ӽ�����
			resetTile.attribute = ATTR_CRECT_RESIZE;

		break;
		case ATTR_AFTERRENDER:

			if (resetTile.tileType == TYPE_NONE) return;
			if (resetTile.tileType == TYPE_ROAD) return;
			if (resetTile.tileType == TYPE_TERRAIN) return;
			//�Ӽ�����
			resetTile.attribute = ATTR_AFTERRENDER;

		break;
	}
}

void mapTool::tileReDir(tagTile& resetTile)
{
	//����ó��
	if (resetTile.tileType != TYPE_DOOR) return;

	//����ó��: ��ư�� �ΰ��̻� Ȱ��ȭ �Ǿ� ���� ���-> ALL ����
	if ((_btnT_left->getBtnOn() && _btnT_right->getBtnOn()) ||
		(_btnT_left->getBtnOn() && _btnT_top->getBtnOn()) ||
		(_btnT_left->getBtnOn() && _btnT_bottom->getBtnOn()) ||
		(_btnT_right->getBtnOn() && _btnT_top->getBtnOn()) ||
		(_btnT_right->getBtnOn() && _btnT_bottom->getBtnOn()) ||
		(_btnT_top->getBtnOn() && _btnT_bottom->getBtnOn()))
	{
		_btnAllReset->setBtnOff(true);
	}

	TILE_DIRECTION selectBtn;

	//Ȱ��ȭ�� ��ư ���� �Է� 
	if (_btnT_left->getBtnOn())   selectBtn = DIR_LEFT;
	if (_btnT_right->getBtnOn())  selectBtn = DIR_RIGHT;
	if (_btnT_top->getBtnOn())	  selectBtn = DIR_TOP;
	if (_btnT_bottom->getBtnOn()) selectBtn = DIR_BOTTOM;

	//��ư ACTION
	switch (selectBtn)
	{
		case DIR_LEFT:

			//�Ӽ�����
			resetTile.direction = DIR_LEFT;

		break;
		case DIR_RIGHT:

			//�Ӽ�����
			resetTile.direction = DIR_RIGHT;

		break;
		case DIR_TOP:

			//�Ӽ�����
			resetTile.direction = DIR_TOP;

		break;
		case DIR_BOTTOM:

			//�Ӽ�����
			resetTile.direction = DIR_BOTTOM;

		break;
	}

}

//============= Ÿ������ ����� =============
//------------------- One -------------------
void mapTool::btnTile1Eraser(tagTile& resetTile)
{
	//������ ����Ÿ�� ����
	ZeroMemory(&_drawTile, sizeof(tagTile));

	//����ó��: ����� �ȵǴ� ����
	int index;
	RECT rc;

	switch (resetTile.tileType)
	{
		case TYPE_TERRAIN:
			index = resetTile.index;
			rc = resetTile.rc;

			ZeroMemory(&resetTile, sizeof(tagTile));

			resetTile.index = index;
			resetTile.rc = rc;
		break;
		case TYPE_BUILDING:
			ZeroMemory(&resetTile, sizeof(tagTile));
		break;
		case TYPE_ROAD:
			ZeroMemory(&resetTile, sizeof(tagTile));
		break;
		case TYPE_FURNITURE:
			ZeroMemory(&resetTile, sizeof(tagTile));
		break;
		case TYPE_ITEM:
			ZeroMemory(&resetTile, sizeof(tagTile));
		break;
		case TYPE_WEAPON:
			ZeroMemory(&resetTile, sizeof(tagTile));
		break;
		case TYPE_ENEMY:
			ZeroMemory(&resetTile, sizeof(tagTile));
		break;
		case TYPE_WALL:
			ZeroMemory(&resetTile, sizeof(tagTile));
		break;
		case TYPE_DOOR:
			ZeroMemory(&resetTile, sizeof(tagTile));
		break;
	}



}

//------------------- All -------------------
void mapTool::btnTileAllEraser()
{
	//������ Ÿ������ �ʱ�ȭ
	ZeroMemory(&_drawTile, sizeof(tagTile));
	//���� FillRect �����
	samTileFRectInitialize();

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

	//Wall
	vTileInitialize(_vSaveWl);

	//Door
	vTileInitialize(_vSaveDr);

	//Wall2
	vTileInitialize(_vSaveArWl);

}
//============= Ÿ������ ����� =============

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
		case TYPE_WALL:

			vTileSet(_vSaveWl, resetTile);
			vTileSet(_vSaveArWl, resetTile);

		break;
		case TYPE_DOOR:

			vTileSet(_vSaveDr, resetTile);

		break;
	}

}

void mapTool::vTileInitialize(vSaveTile& saveTile)
{
	for (int i = 0; i < saveTile.size(); ++i)
	{
		switch (saveTile[i].tileType)
		{
			case TYPE_TERRAIN:
				saveTile[i].img = NULL;
				sprintf(saveTile[i].imgName, "");
				saveTile[i].attribute  = ATTR_CRECT_NONE;
				saveTile[i].tileType   = TYPE_NONE;
				saveTile[i].typeAtt    = TYPE_A_NONE;
				saveTile[i].typeAtt2   = TYPE_A_NONE;
				saveTile[i].index	   = -1;
				saveTile[i].id		   = -1; 
				saveTile[i].anchorType = ANCHOR_NONE;
			break;
			default:
				saveTile.clear();
				return;
			break;
		}
	}
}

void mapTool::vTileSet(vSaveTile& saveTile, tagTile& resetTile)
{
	for (int i = 0; i < saveTile.size(); ++i)
	{
		saveTile[i].img = resetTile.img;
		sprintf(saveTile[i].imgName, "%s", resetTile.imgName);
		saveTile[i].attribute = resetTile.attribute;
		saveTile[i].typeAtt   = resetTile.typeAtt;
		saveTile[i].typeAtt2  = resetTile.typeAtt2;
		saveTile[i].tileType  = resetTile.tileType;
		saveTile[i].frameX	  = resetTile.frameX;
		saveTile[i].frameY	  = resetTile.frameY;
	}
}

//��� ���� Ÿ�Ϻ��� FillRect �ʱ�ȭ 
void mapTool::samTileFRectInitialize()
{
	switch (_drawTile.tileType)
	{
		case TYPE_TERRAIN:
			switch (_btnTabNum)
			{
				case 1:
					_tileFloor->resetSelectile();   //�ٴ�Ÿ��
				break;
				case 2:
					_tileStreet->resetSelectile();  //�Ÿ�
				break;
				case 3:

				break;
				case 4:

				break;
				case 5:

				break;
				case 6:

				break;
			}
		break;
		case TYPE_BUILDING:
			switch (_btnTabNum)
			{
				case 1:
					_tileBuilding1->resetSelectile();   //�ǹ�1
				break;
				case 2:
					_tileBuilding2->resetSelectile();   //�ǹ�2
				break;
				case 3:
					_tileFurniture1->resetSelectile();	//����1
				break;
				case 4:
					_tileWall->resetSelectile();		//��
				break;
				case 5:
					_tileDoor->resetSelectile();		//��
				break;
				case 6:
					_tileShelves->resetSelectile();		//å��
				break;
				case 7:
					_tileTree1->resetSelectile();       //����
				break;
			}
	
		break;
		case TYPE_ROAD:
	
			switch (_btnTabNum)
			{
				case 1:
					
				break;
				case 2:
				
				break;
				case 3:

				break;
				case 4:

				break;
				case 5:

				break;
				case 6:

				break;
			}
		break;
		case TYPE_FURNITURE:
			switch (_btnTabNum)
			{
				case 1:

				break;
				case 2:

				break;
				case 3:

				break;
				case 4:

				break;
				case 5:

				break;
				case 6:

				break;
			}
		break;
		case TYPE_ITEM:
			switch (_btnTabNum)
			{
				case 1:
					_tileItem1->resetSelectile();		//������1
				break;
				case 2:

				break;
				case 3:

				break;
				case 4:

				break;
				case 5:

				break;
				case 6:

				break;
			}
		break;
		case TYPE_WEAPON:
			switch (_btnTabNum)
			{
				case 1:
					_tileWeapon1->resetSelectile();		//����1
				break;
				case 2:

				break;
				case 3:

				break;
				case 4:

				break;
				case 5:

				break;
				case 6:

				break;
			}	
		break;
		case TYPE_ENEMY:
			switch (_btnTabNum)
			{
				case 1:

				break;
				case 2:

				break;
				case 3:

				break;
				case 4:

				break;
				case 5:

				break;
				case 6:

				break;
			}
		
		break;
	}
}