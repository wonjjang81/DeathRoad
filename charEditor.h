#pragma once
#include "gameNode.h"
#include "fButton.h"
#include "character.h"
#include "charInfo.h"


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
	typedef vector<tagCharInfo>				vChar;
	typedef vector<tagCharInfo>::iterator  viChar;

private:
	//캐릭터
	CHARTYPE _charType;
	character* _selectChar;
	charInfo* _saveChar;


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
	fButton* _btnUpBody;
	fButton* _btnUpBodyLeft;
	fButton* _btnUpBodyRight;
	fButton* _btnDwBody;
	fButton* _btnDwBodyLeft;
	fButton* _btnDwBodyRight;
	fButton* _btnHair;
	fButton* _btnHairLeft;
	fButton* _btnHairRight;
	fButton* _btnGlass;
	fButton* _btnGlasLeft;
	fButton* _btnGlasRight;
	fButton* _btnHats;
	fButton* _btnHatsLeft;
	fButton* _btnHatsRight;

	fButton* _btnCharType;
	fButton* _btnSave;
	//======================



public:
	HRESULT init();
	void release();
	void update();
	void render();

	void btnAction(fButton* button, string charTypeName, BTN_CHAR_BODYTYPE btnBodyType);
	void btnIndexAction(int& btnIndexNum, bool Plus, int gapNum, string bodyTypeName);
	void saveChar();
	void charTypeRender(string charTypeName);

	
	charEditor();
	~charEditor();
};

