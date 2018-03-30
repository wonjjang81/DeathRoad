#pragma once
#include "tileInfo.h"
#include "tileDataInfo.h"


struct tagInvenItem
{
	TYPE_ATTRIBUTE typeAtt;   //타입별 속성

	TCHAR imgName[64];
	int index;
	int value;
};

struct tagInvenWp
{
	TYPE_ATTRIBUTE typeAtt;   //타입별 속성

	TCHAR imgName[64];
	int index;
	int damage;

	int frameX;
	int frameY;
};

struct tagCollDoor
{
	TYPE_ATTRIBUTE typeAtt;   //타입별 속성

	int id;
};






class inventory
{
public:



	inventory() {};
	~inventory() {};
};