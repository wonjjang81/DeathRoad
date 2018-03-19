#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

//elements == 속성들 
class elements
{
public:


	elements() {};
	~elements() {};
};

//내부 싱글톤 DB 만들어둔다
class database : public singletonBase <database>
{
private:
	typedef vector<string> arrElements;
	typedef vector<string>::iterator iterElements;

	typedef map<string, elements*> arrElement;
	typedef map<string, elements*>::iterator iterElement;

private:
	arrElement _mTotalElement;

public:
	vector<charInfo*>* _hero;//벡터 포인터



public:
	HRESULT init();
	void release();

	void loadDatabase(string name);

	//속성에 대한 접근자
	elements* getElementData(string str) { return _mTotalElement.find(str)->second; }

	//설정자
	void setElementDataCurrentHP(string str, float ch);
	void setElementDataMaxHP(string str, float mh);
	void setElementDataAngle(string str, float a);
	void setElementDataAccelaration(string str, float accel);
	void setElementDataMaxSpeed(string str, float ms);



	database();
	~database();
};

