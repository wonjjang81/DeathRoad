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

