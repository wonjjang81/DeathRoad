#pragma once
#include "gameNode.h"


class UIManager : public gameNode
{
private:
	int _foodNum;
	int _drugNum;
	int _oilNum;
	int _bulletNum;

	float textX, textY;

	//아이템
	image* _itemImg;

	//무기
	image* _wpImg;
	int _wpFrameX;
	int _wpFrameY;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	int getItem(TYPE_ATTRIBUTE attr);

	void weaponSet();

	UIManager();
	~UIManager();
};

