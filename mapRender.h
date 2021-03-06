#pragma once
#include "gameNode.h"
#include "tile.h"


class mapRender : public gameNode
{
private:
	typedef vector<tagTile>					   vSaveTile;
	typedef vector<tagTile>::iterator		   viSaveTile;

private:


public:

	void mapDraw(vSaveTile tileVector, float moveX, float moveY, float scale, bool aRender = false);
	void vMapDraw(vSaveTile tileVector, float moveX, float moveY, float scale, bool aRender);

	mapRender();
	~mapRender();
};

