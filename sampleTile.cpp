#include "stdafx.h"
#include "sampleTile.h"


sampleTile::sampleTile()
{
}
sampleTile::~sampleTile()
{

}

HRESULT sampleTile::init()
{


	return S_OK;
}

void sampleTile::release()
{

}

void sampleTile::update() 
{

}

void sampleTile::render() 
{

}

void sampleTile::resetSelTile()
{
	if (_selectVTile.size() != 0)
	{
		_selectVTile.clear();
	}
}
