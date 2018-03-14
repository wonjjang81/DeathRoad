#include "stdafx.h"
#include "mapTool.h"


void mapTool::tileReAtrribute(tagTile& resetTile)
{

	//예외처리: 타일 셋팅이 안되어 있으면(이미지X)
	if (resetTile.tileType == TYPE_NONE) return;

	enum BUTTONSELECT
	{
		BTN_MOVE,
		BTN_UNMOVE,
		BTN_ARENDER
	};
	BUTTONSELECT selectBtn;

	//예외처리: 버튼이 두개이상 활성화 되어 있을 경우-> ALL 해제
	if ((_btnA_move->getBtnOn() && _btnA_unMove->getBtnOn()) ||
		(_btnA_move->getBtnOn() && _btnA_ARender->getBtnOn()) ||
		(_btnA_unMove->getBtnOn() && _btnA_ARender->getBtnOn()) ||
		(_btnA_move->getBtnOn() && _btnA_unMove->getBtnOn() && _btnA_ARender->getBtnOn()))
	{
		_btnAllReset->setBtnOff(true);
	}

	//활성화된 버튼 상태 입력 
	if (_btnA_move->getBtnOn())    selectBtn = BTN_MOVE;
	if (_btnA_unMove->getBtnOn())  selectBtn = BTN_UNMOVE;
	if (_btnA_ARender->getBtnOn()) selectBtn = BTN_ARENDER;

	//버튼 ACTION
	switch (selectBtn)
	{
		case BTN_MOVE:

			//속성변경
			resetTile.attribute = ATTR_MOVE;

		break;
		case BTN_UNMOVE:

			//속성변경
			resetTile.attribute = ATTR_UNMOVE;

		break;
		case BTN_ARENDER:

			//속성변경
			resetTile.attribute = ATTR_AFTER_RENDER;

		break;
	}
}

void mapTool::tileReType(tagTile& resetTile)
{
	//예외처리: 타일 셋팅이 안되어 있으면
	//if (resetTile.tileType == TYPE_NONE) return;

	TILE_TYPE selectBtn;

	//예외처리: 버튼이 두개이상 활성화 되어 있을 경우-> ALL 해제
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

	//활성화된 버튼 상태 입력 
	if (_btnT_terrain->getBtnOn())   selectBtn = TYPE_TERRAIN;
	if (_btnT_building->getBtnOn())  selectBtn = TYPE_BUILDING;
	if (_btnT_item->getBtnOn())		 selectBtn = TYPE_ITEM;
	if (_btnT_weapon->getBtnOn())	 selectBtn = TYPE_WEAPON;
	if (_btnT_enemy->getBtnOn())	 selectBtn = TYPE_ENEMY;

	//버튼 ACTION
	switch (selectBtn)
	{
		case TYPE_TERRAIN:

			//속성변경
			resetTile.tileType = TYPE_TERRAIN;
			save();

		break;
		case TYPE_BUILDING:

			//속성변경
			resetTile.tileType = TYPE_BUILDING;
			load();

		break;
		case TYPE_ITEM:

			//속성변경
			resetTile.tileType = TYPE_ITEM;

		break;
		case TYPE_WEAPON:

			//속성변경
			resetTile.tileType = TYPE_WEAPON;

		break;
		case TYPE_ENEMY:

			//속성변경
			resetTile.tileType = TYPE_ENEMY;

		break;
	}
}

//타일정보 지우기: 1
void mapTool::btnTile1Eraser(tagTile& resetTile)
{
	resetTile.img = NULL;
	sprintf(resetTile.imgName, "");
	resetTile.attribute = ATTR_NONE;
	resetTile.tileType = TYPE_NONE;
}

//타일정보 지우기: All
void mapTool::btnTileAllEraser()
{
	for (int i = 0; i < _vSaveTr.size(); ++i)
	{
		_vSaveTr[i].img = NULL;
		sprintf(_vSaveTr[i].imgName, "");
		_vSaveTr[i].attribute = ATTR_NONE;
		_vSaveTr[i].tileType = TYPE_NONE;
	}
}

void mapTool::btnTileAllSet(tagTile& resetTile)
{
	//예외처리
	if (resetTile.img == NULL) return;

	for (int i = 0; i < _vSaveTr.size(); ++i)
	{
		_vSaveTr[i].img = resetTile.img;
		sprintf(_vSaveTr[i].imgName, "%s", resetTile.imgName);
		_vSaveTr[i].attribute = resetTile.attribute;
		_vSaveTr[i].tileType = resetTile.tileType;
		_vSaveTr[i].frameX = resetTile.frameX;
		_vSaveTr[i].frameY = resetTile.frameY;
	}

	for (int i = 0; i < _vSaveBd.size(); ++i)
	{
		_vSaveBd[i].img = resetTile.img;
		sprintf(_vSaveBd[i].imgName, "%s", resetTile.imgName);
		_vSaveBd[i].attribute = resetTile.attribute;
		_vSaveBd[i].tileType = resetTile.tileType;
		_vSaveBd[i].frameX = resetTile.frameX;
		_vSaveBd[i].frameY = resetTile.frameY;
	}
}