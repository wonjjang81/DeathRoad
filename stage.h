#pragma once
#include "gameNode.h"
#include "mapLoad.h"
#include "mapRender.h"

enum RECTTYPE
{
	RECT_FURNITURE,
	RECT_ITEM,
	RECT_WEAPON,
	RECT_WALL,
	RECT_DOOR
};


class stage : public gameNode
{
private: 
	typedef vector<tagTile>			   vSaveTile;
	typedef vector<tagTile>::iterator  viSaveTile;

private:
	mapLoad* _newMap;
	mapRender* _mapRenderer;

	float _mapScale;
	float _moveX, _moveY;

	//afterRender ¥„¿ª ∫§≈Õ
	vSaveTile  _afterVTile;
	viSaveTile _afterViTile;

public:
	HRESULT init(string mapFileName, float scale);
	void release();
	void update(float moveX, float moveY);
	void render();

	void afterRender();
	void afterVectorAdd(vSaveTile& vTile);

	//========================= getter & setter =========================
	RECT getRect(RECTTYPE type, int i);
	int getVectorSize(RECTTYPE type);

	stage();
	~stage();
};

