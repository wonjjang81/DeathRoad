#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>


class sampleTile : public gameNode
{
protected:
	typedef vector<tagTile>			  vTile;
	typedef vector<tagTile>::iterator viTile;
protected:
	tile*   _tileSample;
	tagTile _selectTile;   //선택한 타일정보

	float _showWindowX;  //클립핑 영역X
	float _showWindowY;  //클립핑 영역Y
public:
	vTile _selectVTile;    //선택한 타일정보를 담아둘 벡터

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	//선택한 타일 초기화
	virtual void resetSelTile();

	sampleTile();
	~sampleTile();
};

