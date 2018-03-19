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
	virtual HRESULT init(void);		//�ʱ�ȭ �Լ�
	virtual void release(void);		//�޸� ���� ����
	virtual void update(void);		//������Ʈ(����)
	virtual void render(void);		//�׷��ִ� �Լ�

	void resourceAdd();
	int dFrame(int length, int pixel);

	playGround();
	~playGround();
};

