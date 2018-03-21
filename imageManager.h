#pragma once
#include "singletonBase.h"
#include "image.h"
#include <map>

class imageManager : public singletonBase<imageManager>
{
private:
	//typedef map<string, image*> 이것을 mapImageList라 칭한다
	typedef map<string, image*>				mapImageList;
	typedef map<string, image*>::iterator	mapImageIter;

private:
	mapImageList _mImageList;

public:
	HRESULT init(void);
	void release(void);

	image* addImage(string strKey, int width, int height);
	image* addImage(string strKey, LPCWSTR fileName, int width, int height);
	image* addImage(string strKey, LPCWSTR fileName, float x, float y, int width, int height);

	image* addFrameImage(string strKey, LPCWSTR fileName, float x, float y, int width, int height, int frameX, int frameY);
	image* addFrameImage(string strKey, LPCWSTR fileName, int width, int height, int frameX, int frameY);

	image* findImage(string strKey);

	BOOL deleteImage(string strKey);

	BOOL deleteAll(void);

	void render(string strKey, float opacity, bool flip = false);
	void render(string strKey, int destX, int destY, float opacity, float angle);
	void render(string strKey, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, float opacity);

	//프레임 렌더
	void frameRender(string strKey, int destX, int destY, float opacity, float angle, bool flip = false, float scale = 1);
	void frameRender(string strKey, int destX, int destY, int currentFrameX, int currentFrameY, float opacity, float angle, bool flip = false, float scale = 1);

	//루프렌더
	//void loopRender(string strKey, const LPRECT drawArea, int offSetX = 0, int offSetY = 0, float opacity = 1.0f, float angle = 0.0f);


	imageManager();
	~imageManager();
};

