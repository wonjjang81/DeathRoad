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
	float showX;     //Ŭ���� ����X  
	float showY;     //Ŭ���� ����Y
	float keyMoveX;  //Ű���� X
	float keyMoveY;  //Ű���� Y
};



class sampleTile : public gameNode
{
protected:
	typedef vector<tagTile>		      vTile;
	typedef vector<tagTile>::iterator viTile;
protected:
	tile*   _tileSample;
	tagTile _selectTile;   //������ Ÿ������

	tagTileSample _sTile;  //����Ÿ�� ����ü

	//keyControl
	float _moveSpeed;            //�̵��ӵ�
	int _tileX, _tileY;          //Ÿ�� �Ѱ���
	int _tileSizeX, _tileSizeY;  //Ÿ�� ������

public:
	vTile _selectVTile;    //������ Ÿ�������� ��Ƶ� ����

public:
	HRESULT init(string imgName,ATTRIBUTE att, TILE_TYPE type, ANCHOR_TYPE anchorType, OVERLAPPOSITION overPosition, float scale);
	void release();
	void update();
	void render();



	void resetSelTile();   //������ Ÿ�� �ʱ�ȭ
	void mapKeyControl();  //�� Ű ��Ʈ��

	//=============================== getter & setter ===============================
	inline void resetSelectile() { if (_selectVTile.size() != 0) _selectVTile.clear(); }

	sampleTile();
	~sampleTile();
};

