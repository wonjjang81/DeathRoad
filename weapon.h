#pragma once
#include "gameNode.h"


class weapon : public gameNode
{
private:
	typedef vector<tagInvenWp>				vInWp;
	typedef vector<tagInvenWp>::iterator	viInWp;

private:
	image* _wpImg;   //���� �̹���
	POINT  _center;  //���� ����XY
	int    _wpNum;   //���� ��ȣ
	float  _scale;

	vInWp  _vWp;

public:
	HRESULT init(float scale);
	void release();
	void update(float x, float y);
	void render(int angle = 0);
	void renderB(int frameX, int frameY, int angle = 0, bool flip = false);

	void weaponSet();
	void weaponChange();


	//========================= getter && setter =========================
	vInWp getVWp() { return _vWp; }

	int getWpNum() { return _wpNum; }



	weapon();
	~weapon();
};

