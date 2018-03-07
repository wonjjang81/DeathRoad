#include "stdafx.h"
#include "mapTool.h"


mapTool::mapTool()
{
}
mapTool::~mapTool()
{

}

HRESULT mapTool::init()
{


	return S_OK;
}

void mapTool::release()
{

}

void mapTool::update() 
{

}

void mapTool::render() 
{
	gridRender();
}


void mapTool::gridRender()
{
	//outLine
	D2DMANAGER->drawRectangle(D2DMANAGER->defaultBrush, 0, 0, TILE_TOTAL_SIZEX, TILE_TOTAL_SIZEY);

	//grid
	for (int i = 1; i < TILEY; ++i)
	{
		for (int j = 1; j < TILEX; ++j)
		{
			D2DMANAGER->drawLine(D2DMANAGER->defaultBrush, (TILE_SIZEX * j), 0, (TILE_SIZEX * j), TILE_TOTAL_SIZEY);
			D2DMANAGER->drawLine(D2DMANAGER->defaultBrush, 0, (TILE_SIZEY * i), TILE_TOTAL_SIZEX, (TILE_SIZEY * i));
		}
	}

}