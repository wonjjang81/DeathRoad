#include "stdafx.h"
#include "imageManager.h"


imageManager::imageManager()
{
}


imageManager::~imageManager()
{

}

HRESULT imageManager::init(void)
{

	return S_OK;
}

void imageManager::release(void)
{
	deleteAll();
}


image* imageManager::addImage(string strKey, int width, int height)
{
	image* img = findImage(strKey);

	//이미지가 이미 있다면 그 이미지를 반환
	if (img) return img;
	//그게 아니라면 프로세스가 여기까지 내려왔을 것.!
	img = new image;

	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addImage(string strKey, LPCWSTR fileName, int width, int height)
{
	image* img = findImage(strKey);

	//이미지가 이미 있다면 그 이미지를 반환
	if (img) return img;
	//그게 아니라면 프로세스가 여기까지 내려왔을 것.!
	img = new image;

	if (FAILED(img->init(fileName, width, height)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addImage(string strKey, LPCWSTR fileName, float x, float y, int width, int height)
{
	image* img = findImage(strKey);

	//이미지가 이미 있다면 그 이미지를 반환
	if (img) return img;
	//그게 아니라면 프로세스가 여기까지 내려왔을 것.!
	img = new image;

	if (FAILED(img->init(fileName, x, y, width, height)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}


image* imageManager::addFrameImage(string strKey, LPCWSTR fileName, float x, float y, int width, int height, int frameX, int frameY)
{
	image* img = findImage(strKey);

	//이미지가 이미 있다면 그 이미지를 반환
	if (img) return img;
	//그게 아니라면 프로세스가 여기까지 내려왔을 것.!
	img = new image;

	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addFrameImage(string strKey, LPCWSTR fileName, int width, int height, int frameX, int frameY)
{
	image* img = findImage(strKey);

	//이미지가 이미 있다면 그 이미지를 반환
	if (img) return img;
	//그게 아니라면 프로세스가 여기까지 내려왔을 것.!
	img = new image;

	if (FAILED(img->init(fileName, width, height, frameX, frameY)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}


image* imageManager::findImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);
	
	//찾았다
	if (key != _mImageList.end())
	{
		return key->second;
	}

	return NULL;
}


BOOL imageManager::deleteImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	//지울 이미지를 발견
	if (key != _mImageList.end())
	{
		key->second->release();
		SAFE_DELETE(key->second);
		_mImageList.erase(key);

		return true;
	}

	return false;
}


BOOL imageManager::deleteAll(void)
{
	mapImageIter iter = _mImageList.begin();

	for (; iter != _mImageList.end();)
	{
		//이미지 정보가 있다!
		if (iter->second != NULL)
		{
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else ++iter;
	}

	_mImageList.clear();

	return TRUE;
}


void imageManager::render(string strKey, float opacity)
{
	image* img = findImage(strKey);

	if (img) img->render(opacity);
}

void imageManager::render(string strKey, int destX, int destY, float opacity)
{
	image* img = findImage(strKey);

	if (img) img->render(opacity, destX, destY);
}

void imageManager::render(string strKey, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, float opacity)
{
	image* img = findImage(strKey);

	if (img) img->render(opacity, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void imageManager::frameRender(string strKey, int destX, int destY, float opacity)
{
	image* img = findImage(strKey);

	if (img) img->frameRender(opacity, destX, destY);
}

void imageManager::frameRender(string strKey, int destX, int destY, int currentFrameX, int currentFrameY, float opacity)
{
	image* img = findImage(strKey);

	if (img) img->frameRender(opacity, destX, destY, currentFrameX, currentFrameY);
}


