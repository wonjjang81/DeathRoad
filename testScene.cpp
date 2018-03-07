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
	gameNode::init();


	EFFECTMANAGER->addEffect("Æø¹ß", "explosion", L".//source//image//test//explosion.bmp", 832, 62, 32, 62, 1.0f, 1.0f, 20);

	_degree = 0.0f;


	_t2 = new test02;
	_t2->init();

	addChild(_t2);

	return S_OK;
}

void testScene::release()
{

}

void testScene::update() 
{
	gameNode::update();

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		EFFECTMANAGER->play("Æø¹ß", _ptMouse.x, _ptMouse.y);
		removeChild(_t2);
	}

	EFFECTMANAGER->update();
	_degree++;

}

void testScene::render()
{
	gameNode::render();

	EFFECTMANAGER->render(_degree);

	for (int i = 0; i < 100; ++i)
	{ 
		D2DMANAGER->drawEllipse(D2DMANAGER->defaultBrush, 100 + (i * 20), 200 + (i * 20), 120, 220);
	}
	D2DMANAGER->drawRectangle(D2DMANAGER->defaultBrush, 300, 300, 400, 400);
	D2DMANAGER->drawLine(D2DMANAGER->defaultBrush, 0, 0, WINSIZEX, WINSIZEY);
	D2DMANAGER->drawTextD2d(D2DMANAGER->defaultBrush, L"ÇÁ·¹ÀÓ¿÷", 500, 500, 600, 600);


}
