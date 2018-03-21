#pragma once
#include "gameNode.h"

#include <vector>
#include <map>

enum BODYTYPE
{
	BODY_HEAD,
	BODY_UPBODY,
	BODY_DWBODY,
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
	RECT cRc;  //충돌렉트
	image* img;
	TCHAR imgName[64];
	float x, y;
	float bodyX, bodyY;
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
	void charSetup(string charTypeName, float x, float y, float scale = 1.0f);

	void charBodySet(string imgNameHead, vChar& charVector, BODYTYPE type, float x, float y, float scale = 1.0f);

	void charRender(string charTypeName, int index, bool flip = false);
	void stringErase(string& editStrName, string eraseName);

	string bodyNameChange(string imgName, BODYTYPE typeName);

	//================================ getter & setter ================================
	int getMaxIndex(string charTypeName);
	image* getImg(string charTypeName, int index);

	int getX(string charTypeName, int index);
	int getY(string charTypeName, int index);
	void setX(string charTypeName, int index, float x);
	void setY(string charTypeName, int index, float y);

	int getFrameX(string charTypeName, int index);
	int getFrameY(string charTypeName, int index);
	void setFrameX(string charTypeName, int index, int x);
	void setFrameY(string charTypeName, int index, int y);

	void setBodyY(string charTypeName, int index, float moveY);

	character();
	~character();
};

