#pragma once
#include "gameNode.h"

#include <vector>
#include <map>

enum BODYTYPE
{
	BODY_HEAD,
	BODY_BODY,
	BODY_HAIR,
	BODY_GLASS,
	BODY_HATS
};

enum CHARTYPE
{
	CHAR_FEMALE,
	CHAR_MAN,
	CHAR_SPECIAL,
	CHAR_ZOMBIE
};

struct tagChar
{
	RECT rc;
	image* img;
	TCHAR imgName[64];
	float x, y;
	int index;
	int frameX;
	int frameY;
	float scale;
	BODYTYPE type;
};

struct tagCharInfo
{
	string charTypeName;

	int headIndex;
	int upBodyIndex;
	int dwBodyIndex;
	int hairIndex;
	int glassIndex;
	int hatsIndex;
};


class character : public gameNode
{
private:
	typedef vector<tagChar>			     vChar;
	typedef vector<tagChar>::iterator    viChar;

	typedef map<string, vChar>			 mChar;
	typedef map<string, vChar>::iterator iterChar;

private:
	mChar	 _mChar;
	iterChar _miChar;



public:
	void charSetup(string charTypeName, float x, float y, float scale);

	void charBodySet(string imgNameHead, vChar& charVector, BODYTYPE type, float x, float y, float scale);

	void charRender(string charTypeName, int index);
	void stringErase(string& editStrName, string eraseName);

	string bodyNameChange(string imgName, BODYTYPE typeName);

	//================================ getter & setter ================================
	int getMaxIndex(string charTypeName);




	character();
	~character();
};

