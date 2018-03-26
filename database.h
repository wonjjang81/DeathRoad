#pragma once
#include "singletonBase.h"
#include "charInfo.h"
#include "inventory.h"

#include <vector>
#include <map>

//elements == ¼Ó¼ºµé 
class elements
{
public:


	elements() {};
	~elements() {};
};


//³»ºÎ ½Ì±ÛÅæ DB ¸¸µé¾îµÐ´Ù
class database : public singletonBase <database>
{
private:
	typedef vector<string>						arrElements;
	typedef vector<string>::iterator			iterElements;

	typedef map<string, elements*>				arrElement;
	typedef map<string, elements*>::iterator	iterElement;

	typedef vector<charInfo*>					vCharInfo;
	typedef vector<charInfo*>::iterator			viCharInfo;

	typedef vector<inventory*>					vInven;
	typedef vector<inventory*>::iterator		viInven;
private:
	arrElement _mTotalElement;

public:
	vCharInfo player;
	vInven	  inven;


public:
	HRESULT init();
	void release();

	void loadDatabase(string name);

	//=================================== getter & setter ===================================
	//-------------------------------------- elements ---------------------------------------
	elements* getElementData(string str) { return _mTotalElement.find(str)->second; }

	void setElementDataCurrentHP(string str, float ch);
	void setElementDataMaxHP(string str, float mh);
	void setElementDataAngle(string str, float a);
	void setElementDataAccelaration(string str, float accel);
	void setElementDataMaxSpeed(string str, float ms);



	database();
	~database();
};

