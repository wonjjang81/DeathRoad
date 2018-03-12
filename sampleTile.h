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
	tagTile _selectTile;   //������ Ÿ������

	float _showWindowX;  //Ŭ���� ����X
	float _showWindowY;  //Ŭ���� ����Y
public:
	vTile _selectVTile;    //������ Ÿ�������� ��Ƶ� ����

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	//������ Ÿ�� �ʱ�ȭ
	virtual void resetSelTile();

	sampleTile();
	~sampleTile();
};

