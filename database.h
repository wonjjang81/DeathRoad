#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

//elements == �Ӽ��� 
class elements
{
public:


	elements() {};
	~elements() {};
};

//���� �̱��� DB �����д�
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
	vector<charInfo*>* _hero;//���� ������



public:
	HRESULT init();
	void release();

	void loadDatabase(string name);

	//�Ӽ��� ���� ������
	elements* getElementData(string str) { return _mTotalElement.find(str)->second; }

	//������
	void setElementDataCurrentHP(string str, float ch);
	void setElementDataMaxHP(string str, float mh);
	void setElementDataAngle(string str, float a);
	void setElementDataAccelaration(string str, float accel);
	void setElementDataMaxSpeed(string str, float ms);



	database();
	~database();
};

