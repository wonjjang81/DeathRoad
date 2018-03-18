#pragma once
#include "gameNode.h"
#include "fButton.h"
#include "character.h"

#include <vector>

enum BTN_CHAR_BODYTYPE
{
	HEAD_LEFT,
	HEAD_RIGHT,
	UPBODY_LEFT,
	UPBODY_RIGHT,
	DWBODY_LEFT,
	DWBODY_RIGHT,
	HAIR_LEFT,
	HAIR_RIGHT,
	GLASS_LEFT,
	GLASS_RIGHT,
	HATS_LEFT,
	HATS_RIGHT
};

class charEditor : public gameNode
{
private:
	typedef vector<character*>			   vChar;
	typedef vector<character*>::iterator  viChar;

private:
	//캐릭터
	character* _selectChar;

	vChar _hero;
	vChar _friend1;
	vChar _friend2;

	int _headIndex;
	int _upBodyIndex;
	int _dwBodyIndex;
	int _hairIndex;
	int _glassIndex;
	int _hatsIndex;

	int _previousNum;
	
	//======== 버튼 ========
	fButton* _btnHead;
	fButton* _btnHeadLeft;
	fButton* _btnHeadRight;
	fButton* _btnBody;
	fButton* _btnBodyLeft;
	fButton* _btnBodyRight;
	fButton* _btnHair;
	fButton* _btnHairLeft;
	fButton* _btnHairRight;
	fButton* _btnGlass;
	fButton* _btnGlasLeft;
	fButton* _btnGlasRight;
	fButton* _btnHats;
	fButton* _btnHatsLeft;
	fButton* _btnHatsRight;
	//======================



public:
	HRESULT init();
	void release();
	void update();
	void render();

	void btnAction(fButton* button, string charTypeName, BTN_CHAR_BODYTYPE btnBodyType);
	void btnIndexAction(int& btnIndexNum, bool Plus, int gapNum, string bodyTypeName);

	charEditor();
	~charEditor();
};

