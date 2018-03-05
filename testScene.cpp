#include "stdafx.h"
#include "testScene.h"


testScene::testScene()
{
}
testScene::~testScene()
{

}

HRESULT testScene::init()
{
	IMAGEMANAGER->addImage("title", L".//source//image//ui//dr2c_title_small.png", 144, 48);

	return S_OK;
}

void testScene::release()
{

}

void testScene::update() 
{

}

void testScene::render() 
{
	IMAGEMANAGER->render("title", 100, 200, 0.2f);
}
