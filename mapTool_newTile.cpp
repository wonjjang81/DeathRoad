#include "stdafx.h"
#include "mapTool.h"
#include "dialogProc.h"


void mapTool::newTileMap()
{
	DialogBoxParam(_hInstance, MAKEINTRESOURCE(IDD_DIALOG1), _hWnd, newTileProc, (LPARAM)this);
}


void mapTool::createDefaultMap(POINT mapSize)
{
	//Ÿ�� �ʱ�ȭ
	vTileClear();

	_tileX = mapSize.x;
	_tileY = mapSize.y;

	//----------------------- grid -----------------------
	//grid ���Ϳ� ���
	if ((_vTile.size() == 0))
	{
		for (int i = 0; i < _tileY; ++i)
		{
			for (int j = 0; j < _tileX; ++j)
			{
				//��Ʈ�� �׸���
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

//Ÿ������ �ʱ�ȭ(���� Ŭ����)
void mapTool::vTileClear()
{
	_vTile.clear();    //�׸���
	_vSaveTr.clear();  //����
	_vSaveBd.clear();  //����
}