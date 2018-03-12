#pragma once
#include "sampleTile.h"


class tileStreet : public sampleTile
{
private:


public:
	HRESULT init();
	void release();
	void update();
	void render();


	tileStreet();
	~tileStreet();
};

