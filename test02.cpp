#include "stdafx.h"
#include "test02.h"


test02::test02()
{
}
test02::~test02()
{
}


HRESULT test02::init()
{

	IMAGEMANAGER->addImage("그라비티", L".//source//image//test//그라비티.bmp", 1190, 595);


	_loopX = _loopY = 0;

	return S_OK;
}

void test02::release()
{

}

void test02::update() 
{

	_loopX++;
	_loopY++;
}

void test02::render() 
{
	//IMAGEMANAGER->findImage("그라비티")->loopRender(1.0f, &RectMake(0, 0, WINSIZEX, WINSIZEY), _loopX, _loopY);
}
