#pragma once
#include "tileInfo.h"
#include "tileDataInfo.h"

class inventory
{
public:
	TILE_TYPE tileType;       //타입
	ATTRIBUTE attribute;      //속성
	TYPE_ATTRIBUTE typeAtt;   //타입별 속성

	TCHAR imgName[64];
	int index;



	inventory() {};
	~inventory() {};
};