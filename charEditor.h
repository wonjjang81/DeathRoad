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

enum CHARTYPE
{
	CHAR_FEMALE,
	CHAR_MAN,
	CHAR_SPECIAL,
	CHAR_ZOMBIE
};

struct tagCharInfo
{
	string charTypeName;
	string charHeadName;
	string charBodyName;
	string charHairName;
	string charGlasName;
	string charHatsName;

	int headIndex;
	int upBodyIndex;
	int dwBodyIndex;
	int hairIndex;
	int glassIndex;
	int hatsIndex;
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

	vChar _team;

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
	void typeChange(CHARTYPE typeName);
	
	charEditor();
	~charEditor();
};

