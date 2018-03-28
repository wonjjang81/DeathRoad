#pragma once
#include "gameNode.h"


class weapon : public gameNode
{
private:
	typedef vector<tagInvenWp>				vInWp;
	typedef vector<tagInvenWp>::iterator	viInWp;

private:
	image* _wpImg;   //무기 이미지
	POINT  _center;  //무기 센터XY
	int    _wpNum;   //무기 번호

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

