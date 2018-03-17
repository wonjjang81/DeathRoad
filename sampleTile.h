#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>

struct tagTileSample
{
	string imgName;
	TILE_TYPE type;
	ATTRIBUTE att;
	ANCHOR_TYPE anchor;
	OVERLAPPOSITION overPos;
	float scale;
	float showX;     //클립핑 영역X  
	float showY;     //클립핑 영역Y
	float keyMoveX;  //키무브 X
	float keyMoveY;  //키무브 Y
};



class sampleTile : public gameNode
{
protected:
	typedef vector<tagTile>		      vTile;
	typedef vector<tagTile>::iterator viTile;
protected:
	tile*   _tileSample;
	tagTile _selectTile;   //선택한 타일정보

	tagTileSample _sTile;  //샘플타일 구조체

	//keyControl
	float _moveSpeed;            //이동속도
	int _tileX, _tileY;          //타일 총갯수
	int _tileSizeX, _tileSizeY;  //타일 사이즈

public:
	vTile _selectVTile;    //선택한 타일정보를 담아둘 벡터

public:
	HRESULT init(string imgName,ATTRIBUTE att, TILE_TYPE type, ANCHOR_TYPE anchorType, OVERLAPPOSITION overPosition, float scale);
	void release();
	void update();
	void render();



	void resetSelTile();   //선택한 타일 초기화
	void mapKeyControl();  //맵 키 컨트롤

	//=============================== getter & setter ===============================
	inline void resetSelectile() { if (_selectVTile.size() != 0) _selectVTile.clear(); }

	sampleTile();
	~sampleTile();
};

