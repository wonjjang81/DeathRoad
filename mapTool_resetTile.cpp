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

		break;
		case TYPE_ROAD:

			//속성변경
			resetTile.tileType = TYPE_ROAD;

		break;
		case TYPE_FURNITURE:

			//속성변경
			resetTile.tileType = TYPE_FURNITURE;

		break;
		case TYPE_BUILDING:

			//속성변경
			resetTile.tileType = TYPE_BUILDING;

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

//============= 타일정보 지우기 =============
//------------------- One -------------------
void mapTool::btnTile1Eraser(tagTile& resetTile)
{
	//선택한 샘플타일 비우기
	ZeroMemory(&_drawTile, sizeof(tagTile));

	//예외처리: 지우면 안되는 정보
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
	}



}

//------------------- All -------------------
void mapTool::btnTileAllEraser()
{
	//선택한 타일정보 초기화
	ZeroMemory(&_drawTile, sizeof(tagTile));
	//선택 FillRect 지우기
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

}
//============= 타일정보 지우기 =============

void mapTool::btnTileAllSet(tagTile& resetTile)
{
	//예외처리
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
		switch (saveTile[i].tileType)
		{
			case TYPE_TERRAIN:
				saveTile[i].img = NULL;
				sprintf(saveTile[i].imgName, "");
				saveTile[i].attribute = ATTR_NONE;
				saveTile[i].tileType = TYPE_NONE;
				saveTile[i].index = -1;
				saveTile[i].id = -1;
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
		saveTile[i].tileType = resetTile.tileType;
		saveTile[i].frameX = resetTile.frameX;
		saveTile[i].frameY = resetTile.frameY;
	}
}

//모든 샘플 타일벡터 FillRect 초기화 
void mapTool::samTileFRectInitialize()
{
	switch (_drawTile.tileType)
	{
		case TYPE_TERRAIN:
			switch (_btnTabNum)
			{
				case 1:
					_tileFloor->resetSelectile();   //바닥타일
				break;
				case 2:
					_tileStreet->resetSelectile();  //거리
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
					_tileBuilding1->resetSelectile();   //건물1
				break;
				case 2:
					_tileBuilding2->resetSelectile();   //건물2
				break;
				case 3:
					_tileFurniture1->resetSelectile();	//가구1
				break;
				case 4:
					_tileWall->resetSelectile();		//벽
				break;
				case 5:
					_tileDoor->resetSelectile();		//문
				break;
				case 6:
					_tileShelves->resetSelectile();		//책장
				break;
				case 7:
					_tileTree1->resetSelectile();       //나무
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
					_tileItem1->resetSelectile();		//아이템1
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
					_tileWeapon1->resetSelectile();		//무기1
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