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
	float showX;     //클립핑 영역X  
	float showY;     //클립핑 영역Y
	float keyMoveX;  //키무브 X
	float keyMoveY;  //키무브 Y
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

	//keyControl
	float _moveSpeed;            //이동속도
	int _tileX, _tileY;          //타일 총갯수
	int _tileSizeX, _tileSizeY;  //타일 사이즈
	bool _isKeyOn;               //키작동 

public:
	vTile _selectVTile;    //선택한 타일정보를 담아둘 벡터

public:
	virtual HRESULT init(string imgName,ATTRIBUTE att, TILE_TYPE type, float scale);
	virtual void release();
	virtual void update();
	virtual void render();



	virtual void resetSelTile();   //선택한 타일 초기화
	virtual void mapKeyControl();  //맵 키 컨트롤

	//=============================== getter & setter ===============================
	inline void setKeyMove(bool keyMove) { _isKeyOn = keyMove; }

	sampleTile();
	~sampleTile();
};

