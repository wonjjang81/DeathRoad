#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>

struct tagTileSample
{
	string imgName;
	TILE_TYPE type;
	ATTRIBUTE att;
	float scale;
	float showX;  //클립핑 영역X  
	float showY;  //클립핑 영역Y
};


class sampleTile : public gameNode
{
protected:
	typedef vector<tagTile>		   vTile;
	typedef vector<tagTile>::iterator viTile;
protected:
	tile*   _tileSample;
	tagTile _selectTile;   //선택한 타일정보

	tagTileSample _sTile;  //샘플타일 구조체
public:
	vTile _selectVTile;    //선택한 타일정보를 담아둘 벡터

public:
	virtual HRESULT init(string imgName,ATTRIBUTE att, TILE_TYPE type, float scale);
	virtual void release();
	virtual void update();
	virtual void render();


	//선택한 타일 초기화
	virtual void resetSelTile();

	sampleTile();
	~sampleTile();
};

