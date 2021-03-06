#pragma once
#include "tile.h"

class mapLoad
{
private:
	typedef vector<tagTile>			   vSaveTile;
	typedef vector<tagTile>::iterator  viSaveTile;

private:
	int _tileX;
	int _tileY;

	POINT _startPoint;

	
public:
	//----------- Terrain --------
	vSaveTile  _vSaveTr;
	viSaveTile _viSaveTr;
	//---------- Building --------
	vSaveTile  _vSaveBd;
	viSaveTile _viSaveBd;
	//------------ Road ----------
	vSaveTile  _vSaveRd;
	viSaveTile _viSaveRd;
	//---------- Furniture -------
	vSaveTile  _vSaveFt;
	viSaveTile _viSaveFt;
	//------------ Item ----------
	vSaveTile  _vSaveIt;
	viSaveTile _viSaveIt;
	//----------- Weapon ---------
	vSaveTile  _vSaveWp;
	viSaveTile _viSaveWp;
	//----------- Enemy ----------
	vSaveTile  _vSaveEm;
	viSaveTile _viSaveEm;
	//----------- Wall -----------
	vSaveTile  _vSaveWl;
	viSaveTile _viSaveWl;

	vSaveTile  _vSaveArWl;
	viSaveTile _viSaveArWl;
	//----------- Door -----------
	vSaveTile  _vSaveDr;
	viSaveTile _viSaveDr;

public:
	void loadMap(string fileName);
	void saveVectorTileData(tagTile* getTile, vSaveTile& vSaveTile, int tileSize);
	void revisonRect(TYPE_ATTRIBUTE typeAtt, RECT& rc);

	void rectResize(RECT& rc, float left, float top, float right, float bottom);

	POINT getStartPoint() { return _startPoint; }

	mapLoad();
	~mapLoad();
};

