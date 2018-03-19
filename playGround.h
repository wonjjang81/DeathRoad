#pragma once
#include "gameNode.h"
#include "mapTool.h"
#include "charEditor.h"
#include "stageManager.h"

enum SCENEKEY
{
	SCENE_MAPTOOL,
	SCENE_CHAREDITOR
};

class playGround : public gameNode
{
private:
	
public:
	virtual HRESULT init(void);		//초기화 함수
	virtual void release(void);		//메모리 관련 해제
	virtual void update(void);		//업데이트(연산)
	virtual void render(void);		//그려주는 함수

	void resourceAdd();
	int dFrame(int length, int pixel);

	playGround();
	~playGround();
};

