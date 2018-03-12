#pragma once
#include "sampleTile.h"


class tileBuildingA : public sampleTile
{
private:

public:
	HRESULT init();
	void release();
	void update();
	void render();


	tileBuildingA();
	~tileBuildingA();
};

