#pragma once
#include "sampleTile.h"


class tileBuildingF : public sampleTile
{
private:

public:
	HRESULT init();
	void release();
	void update();
	void render();


	tileBuildingF();
	~tileBuildingF();
};
