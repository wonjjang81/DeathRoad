#pragma once
#include "sampleTile.h"


class tileFloor : public sampleTile
{
private:


public:
	HRESULT init();
	void release();
	void update();
	void render();



	tileFloor();
	~tileFloor();
};

