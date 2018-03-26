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

	//���ҽ� �߰�
	resourceAdd();
	
	SCENEMANAGER->addScene("ĳ������", new charEditor);
	SCENEMANAGER->addScene("����", new mapTool);
	SCENEMANAGER->addScene("��������", new stageManager);

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

	if (KEYMANAGER->isOnceKeyDown(VK_F2)) SCENEMANAGER->changeScene("����");
	if (KEYMANAGER->isOnceKeyDown(VK_F3)) SCENEMANAGER->changeScene("ĳ������");
	if (KEYMANAGER->isOnceKeyDown(VK_F4)) SCENEMANAGER->changeScene("��������");
}

//�׸��°�.......
void playGround::render(void)
{
	D2DMANAGER->beginDraw();
	//================== �� ���� �մ��� ���ÿ� =========================


	SCENEMANAGER->render();


	//�ð� ���� ���
	//TIMEMANAGER->render();


	//================== �� �Ʒ��� �մ��� ���ÿ� ========================
	D2DMANAGER->endDraw();
}


