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

struct tagChar
{
	RECT rc;
	image* img;
	TCHAR imgName[64];
	float x, y;
	float gapX, gapY;
	int index;
	int frameX;
	int frameY;
	float scale;
	BODYTYPE type;
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
	HRESULT init();
	void release();
	void update();
	void render();

	void charSetup(string charTypeName, string imgNameHead, string imgNameBody,
		string imgNameHair, string imgNameGlas, string imgNameHats,
		float x, float y, float scale);

	void charBodySet(string imgNameHead, vChar& charVector, BODYTYPE type, float x, float y, float scale);

	void charRender(string charTypeName, int index);
	void stringErase(string& editStrName, string eraseName);


	//================================ getter & setter ================================
	int getMaxIndex(string charTypeName);


	character();
	~character();
};

