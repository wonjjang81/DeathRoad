#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{

}

HRESULT playGround::init()
{
	gameNode::init(true);


	SCENEMANAGER->addScene("test", new testScene);
	SCENEMANAGER->addScene("����", new mapTool);

	SCENEMANAGER->changeScene("����");
	
	return S_OK;
}

//�޸� ���� ����
void playGround::release(void)
{
	gameNode::release();




}

//����
void playGround::update(void)
{
	gameNode::update();

	SCENEMANAGER->update();
}

//�׸��°�.......
void playGround::render(void)
{
	D2DMANAGER->beginDraw();
	//================== �� ���� �մ��� ���ÿ� =========================


	SCENEMANAGER->render();


	//�ð� ���� ���
	TIMEMANAGER->render();


	//================== �� �Ʒ��� �մ��� ���ÿ� ========================
	D2DMANAGER->endDraw();
}


