#pragma once
#include "tileInfo.h"
#include "tileDataInfo.h"

class inventory
{
public:
	TILE_TYPE tileType;       //Ÿ��
	ATTRIBUTE attribute;      //�Ӽ�
	TYPE_ATTRIBUTE typeAtt;   //Ÿ�Ժ� �Ӽ�

	TCHAR imgName[64];
	int index;



	inventory() {};
	~inventory() {};
};