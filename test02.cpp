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

	IMAGEMANAGER->addFrameImage("버튼", L".//source//image//test//button.bmp", 122, 62, 1, 2);
	_btnSceneChange = new button;
	_btnSceneChange->init("버튼", WINSIZEX / 2, WINSIZEY / 2, PointMake(0, 1), PointMake(0, 0), cbSceneChange);


	return S_OK;
}

void test02::release()
{

}

void test02::update() 
{
	_loopY++;

	_btnSceneChange->update();
}

void test02::render() 
{
	//IMAGEMANAGER->findImage("그라비티")->loopRender(1.0f, &RectMake(0, 0, WINSIZEX, WINSIZEY), _loopX, _loopY);
	D2DMANAGER->fillEllipse(D2DMANAGER->createBrush(RGB(255,0,0)), 100, 200, 200, 300);
	_btnSceneChange->render();
}


void test02::cbSceneChange()
{
	DATABASE->setElementDataAngle("battle", DATABASE->getElementData("battle")->angle += 0.2f);
}