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
	SCENEMANAGER->addScene("맵툴", new mapTool);

	SCENEMANAGER->changeScene("맵툴");
	
	return S_OK;
}

//메모리 관련 삭제
void playGround::release(void)
{
	gameNode::release();




}

//연산
void playGround::update(void)
{
	gameNode::update();

	SCENEMANAGER->update();
}

//그리는거.......
void playGround::render(void)
{
	D2DMANAGER->beginDraw();
	//================== 이 위는 손대지 마시오 =========================


	SCENEMANAGER->render();


	//시간 정보 출력
	TIMEMANAGER->render();


	//================== 이 아래는 손대지 마시오 ========================
	D2DMANAGER->endDraw();
}


