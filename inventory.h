#pragma once
#include "tileInfo.h"
#include "tileDataInfo.h"


struct tagInvenItem
{
	TYPE_ATTRIBUTE typeAtt;   //Ÿ�Ժ� �Ӽ�

	TCHAR imgName[64];
	int index;
	int value;
};

struct tagInvenWp
{
	TYPE_ATTRIBUTE typeAtt;   //Ÿ�Ժ� �Ӽ�

	TCHAR imgName[64];
	int index;
	int damage;

	int frameX;
	int frameY;
};






class inventory
{
public:



	inventory() {};
	~inventory() {};
};