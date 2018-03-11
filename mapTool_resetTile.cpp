#include "stdafx.h"
#include "mapTool.h"


void mapTool::tileReAtrribute(tagTile& resetTile)
{
	//타일속성 변경
	if (_btnA_move->getBtnOn())
	{
		resetTile.attribute = ATTR_MOVE;
	}
	if (_btnA_unMove->getBtnOn())
	{
		resetTile.attribute = ATTR_UNMOVE;
	}
	if (_btnA_ARender->getBtnOn())
	{
		resetTile.attribute = ATTR_AFTER_RENDER;
	}
}

void mapTool::tileReType(tagTile resetTile)
{
	//타일타입 변경

}

