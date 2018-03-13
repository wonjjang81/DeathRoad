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
	float showX;  //Ŭ���� ����X  
	float showY;  //Ŭ���� ����Y
};


class sampleTile : public gameNode
{
protected:
	typedef vector<tagTile>		   vTile;
	typedef vector<tagTile>::iterator viTile;
protected:
	tile*   _tileSample;
	tagTile _selectTile;   //������ Ÿ������

	tagTileSample _sTile;  //����Ÿ�� ����ü
public:
	vTile _selectVTile;    //������ Ÿ�������� ��Ƶ� ����

public:
	virtual HRESULT init(string imgName,ATTRIBUTE att, TILE_TYPE type, float scale);
	virtual void release();
	virtual void update();
	virtual void render();


	//������ Ÿ�� �ʱ�ȭ
	virtual void resetSelTile();

	sampleTile();
	~sampleTile();
};

