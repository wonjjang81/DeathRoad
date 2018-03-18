#pragma once
#include "gameNode.h"
#include "fButton.h"
#include "character.h"

#include <vector>


class charEditor : public gameNode
{
private:
	typedef vector<character*>			   vChar;
	typedef vector<character*>::iterator  viChar;

private:
	//ĳ����
	character* _selectChar;

	vChar _hero;
	vChar _friend1;
	vChar _friend2;
	
	//��ư
	fButton* _headLeft;
	fButton* _headRight;
	fButton* _bodyLeft;
	fButton* _bodyRight;
	fButton* _glasLeft;
	fButton* _glasRight;
	fButton* _hairLeft;
	fButton* _hairRight;
	fButton* _hatsLeft;
	fButton* _hatsRight;


public:
	HRESULT init();
	void release();
	void update();
	void render();


	charEditor();
	~charEditor();
};

