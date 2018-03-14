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
	float showX;     //Ŭ���� ����X  
	float showY;     //Ŭ���� ����Y
	float keyMoveX;  //Ű���� X
	float keyMoveY;  //Ű���� Y
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

	//keyControl
	float _moveSpeed;            //�̵��ӵ�
	int _tileX, _tileY;          //Ÿ�� �Ѱ���
	int _tileSizeX, _tileSizeY;  //Ÿ�� ������
	bool _isKeyOn;               //Ű�۵� 

public:
	vTile _selectVTile;    //������ Ÿ�������� ��Ƶ� ����

public:
	virtual HRESULT init(string imgName,ATTRIBUTE att, TILE_TYPE type, float scale);
	virtual void release();
	virtual void update();
	virtual void render();



	virtual void resetSelTile();   //������ Ÿ�� �ʱ�ȭ
	virtual void mapKeyControl();  //�� Ű ��Ʈ��

	//=============================== getter & setter ===============================
	inline void setKeyMove(bool keyMove) { _isKeyOn = keyMove; }

	sampleTile();
	~sampleTile();
};

