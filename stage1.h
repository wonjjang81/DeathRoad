#pragma once
#include "gameNode.h"
#include "stage.h"


class stage1 : public gameNode
{
private:
	typedef vector<tagTile>					vSaveTile;
	typedef vector<tagTile>::iterator		viSaveTile;

private:
	stage* _room;

	POINT _startPoint;

	vSaveTile _vHaveFt;

public:
	HRESULT init(string mapFileName, float mapX, float mapY, float scale);
	void release();
	void update();
	void render();

	void afterRender();

	void removeVItem(RECTTYPE type, int i);
	void getDoorID(int num);


	//========================= getter & setter =========================
	RECT getRect(RECTTYPE type, int i);
	int getVectorSize(RECTTYPE type);

	POINT getStartPoint() { return _startPoint; }

	tagTile getTileInfo(RECTTYPE type, int i);
	void setVTilePush(RECTTYPE type, tagTile newTile) { _room->setVtilePush(type, newTile); }
	void setVTileCpoy(RECTTYPE type, int i, tagTile newTile) { _room->setVtileCopy(type, i, newTile); }

	void setTileDrAction(int i, int value) { _room->getNewMap()->_vSaveDr[i].actionValue = value; };  //문 액션값 설정
	void setTileFtMoveXY(int i, float x, float y) { _room->setNewMapFtMoveXY(i, x, y); }			  //가구 XY 설정
	void setTileFtMoveRc(int i, float x, float y) { _room->setNewMapFtMoveRc(i, x, y); }			  //가구 렉트XY 설정

	vSaveTile getVFt() { return _vHaveFt; }
	void setVFt(vSaveTile vTile) { _vHaveFt.swap(vTile); }


	stage1();
	~stage1();
};

