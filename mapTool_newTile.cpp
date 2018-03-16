#include "stdafx.h"
#include "mapTool.h"
#include "dialogProc.h"


void mapTool::newTileMap()
{
	DialogBoxParam(_hInstance, MAKEINTRESOURCE(IDD_DIALOG1), _hWnd, newTileProc, (LPARAM)this);
}


void mapTool::createDefaultMap(POINT mapSize)
{
	//타일 초기화
	vTileClear();

	_tileX = mapSize.x;
	_tileY = mapSize.y;

	//----------------------- grid -----------------------
	//grid 벡터에 담기
	if ((_vTile.size() == 0))
	{
		for (int i = 0; i < _tileY; ++i)
		{
			for (int j = 0; j < _tileX; ++j)
			{
				//렉트로 그리기
				tagSampleTile tile;
				tile.rc.left = TILE_SIZEX * j;
				tile.rc.top = TILE_SIZEY * i;
				tile.rc.right = TILE_SIZEX * (j + 1);
				tile.rc.bottom = TILE_SIZEY * (i + 1);
				tile.index = (_tileX * i) + j;

				_vTile.push_back(tile);
			}
		}
	}
	//----------------------------------------------------
}

//타일정보 초기화(벡터 클리어)
void mapTool::vTileClear()
{
	_vTile.clear();    //그리드
	_vSaveTr.clear();  //지형
	_vSaveBd.clear();  //빌딩
	_vSaveRd.clear();  //도로
	_vSaveFt.clear();  //가구
	_vSaveIt.clear();  //아이템
	_vSaveWp.clear();  //무기
	_vSaveEm.clear();  //적
}