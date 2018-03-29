#pragma once
#include "gameNode.h"
#include "stage.h"


class stage1 : public gameNode
{
private:
	stage* _room;

	POINT _startPoint;

public:
	HRESULT init(string mapFileName, float mapX, float mapY, float scale);
	void release();
	void update();
	void render();

	void afterRender();

	void removeVItem(RECTTYPE type, int i);


	//========================= getter & setter =========================
	RECT getRect(RECTTYPE type, int i);
	int getVectorSize(RECTTYPE type);

	POINT getStartPoint() { return _startPoint; }

	tagTile getTileInfo(RECTTYPE type, int i);


	stage1();
	~stage1();
};

