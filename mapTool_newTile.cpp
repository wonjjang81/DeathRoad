#include "stdafx.h"
#include "mapTool.h"
#include "dialogProc.h"


void mapTool::newTileMap()
{
	DialogBoxParam(_hInstance, MAKEINTRESOURCE(IDD_DIALOG1), _hWnd, newTileProc, (LPARAM)this);
}


void mapTool::createDefaultMap(POINT mapSize)
{

}