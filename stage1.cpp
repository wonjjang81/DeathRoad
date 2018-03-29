#include "stdafx.h"
#include "stage1.h"


stage1::stage1()
{
}
stage1::~stage1()
{
}


HRESULT stage1::init(string mapFileName, float mapX, float mapY, float scale)
{
	_room = new stage;
	_room->init(mapFileName, mapX, mapY, scale);

	_startPoint = _room->getNewMap()->getStartPoint();


	return S_OK;
}

void stage1::release() 
{
	delete _room;
}

void stage1::update()  
{
	_room->update(CAMERAMANAGER->tileCamMove().x, CAMERAMANAGER->tileCamMove().y);
}

void stage1::render()  
{
	_room->render();
}

void stage1::afterRender()
{
	_room->afterRender();
}



RECT stage1::getRect(RECTTYPE type, int i)
{
	switch (type)
	{
		case RECT_FURNITURE:
			return _room->getNewMap()->_vSaveFt[i].rc;
		break;
		case RECT_ITEM:
			return _room->getNewMap()->_vSaveIt[i].rc;
		break;
		case RECT_WEAPON:
			return _room->getNewMap()->_vSaveWp[i].rc;
		break;
		case RECT_WALL:
			return _room->getNewMap()->_vSaveWl[i].rc;
		break;
		case RECT_WALL2:
			return _room->getNewMap()->_vSaveArWl[i].rc;
		break;
		case RECT_DOOR:
			return _room->getNewMap()->_vSaveDr[i].rc;
		break;
	}
}

int stage1::getVectorSize(RECTTYPE type)
{
	switch (type)
	{
		case RECT_FURNITURE:
			return _room->getNewMap()->_vSaveFt.size();
		break;
		case RECT_ITEM:
			return _room->getNewMap()->_vSaveIt.size();
		break;
		case RECT_WEAPON:
			return _room->getNewMap()->_vSaveWp.size();
		break;
		case RECT_WALL:
			return _room->getNewMap()->_vSaveWl.size();
		break;
		case RECT_WALL2:
			return _room->getNewMap()->_vSaveArWl.size();
		break;
		case RECT_DOOR:
			return _room->getNewMap()->_vSaveDr.size();
		break;
	}
}


tagTile stage1::getTileInfo(RECTTYPE type, int i)
{
	tagTile tmpTile;
	ZeroMemory(&tmpTile, sizeof(tagTile));

	switch (type)
	{
		case RECT_FURNITURE:
			if (_room->getNewMap()->_vSaveFt.size() == 0) break;

			tmpTile.tileType  = _room->getNewMap()->_vSaveFt[i].tileType;
			tmpTile.attribute = _room->getNewMap()->_vSaveFt[i].attribute;
			tmpTile.typeAtt   = _room->getNewMap()->_vSaveFt[i].typeAtt;
			tmpTile.typeAtt2  = _room->getNewMap()->_vSaveFt[i].typeAtt2;
			sprintf(tmpTile.imgName, "%s", _room->getNewMap()->_vSaveFt[i].imgName);
			tmpTile.index     = _room->getNewMap()->_vSaveFt[i].index;

			return tmpTile;
		break;
		case RECT_ITEM:
			if (_room->getNewMap()->_vSaveIt.size() == 0) break;

			tmpTile.tileType  = _room->getNewMap()->_vSaveIt[i].tileType;
			tmpTile.attribute = _room->getNewMap()->_vSaveIt[i].attribute;
			tmpTile.typeAtt   = _room->getNewMap()->_vSaveIt[i].typeAtt;
			tmpTile.typeAtt2  = _room->getNewMap()->_vSaveIt[i].typeAtt2;
			sprintf(tmpTile.imgName, "%s", _room->getNewMap()->_vSaveIt[i].imgName);
			tmpTile.index     = _room->getNewMap()->_vSaveIt[i].index;

			return tmpTile;
		break;
		case RECT_WEAPON:
			if (_room->getNewMap()->_vSaveWp.size() == 0) break;

			tmpTile.tileType  = _room->getNewMap()->_vSaveWp[i].tileType;
			tmpTile.attribute = _room->getNewMap()->_vSaveWp[i].attribute;
			tmpTile.typeAtt   = _room->getNewMap()->_vSaveWp[i].typeAtt;
			tmpTile.typeAtt2  = _room->getNewMap()->_vSaveWp[i].typeAtt2;
			sprintf(tmpTile.imgName, "%s", _room->getNewMap()->_vSaveWp[i].imgName);
			tmpTile.index     = _room->getNewMap()->_vSaveWp[i].index;
			tmpTile.frameX	  = _room->getNewMap()->_vSaveWp[i].frameX;
			tmpTile.frameY	  = _room->getNewMap()->_vSaveWp[i].frameY;

			return tmpTile;
		break;
	}
}


void stage1::removeVItem(RECTTYPE type, int i)
{
	switch (type)
	{
		case RECT_FURNITURE:
			if (_room->getNewMap()->_vSaveFt.size() == 0) break;


		break;
		case RECT_ITEM:
			if (_room->getNewMap()->_vSaveIt.size() == 0) break;

			_room->getNewMap()->_vSaveIt.erase(_room->getNewMap()->_vSaveIt.begin() + i);
			

		break;
		case RECT_WEAPON:
			if (_room->getNewMap()->_vSaveWp.size() == 0) break;

			_room->getNewMap()->_vSaveWp.erase(_room->getNewMap()->_vSaveWp.begin() + i);

		break;
	}
}
