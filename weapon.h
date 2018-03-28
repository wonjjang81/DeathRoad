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

	vInWp  _vWp;

public:
	HRESULT init();
	void release();
	void update(float x, float y);
	void render(int scale, int angle = 0);

	void weaponSet();
	void weaponChange();


	weapon();
	~weapon();
};

