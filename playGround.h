#pragma once
#include "gameNode.h"
#include "testScene.h"
#include "mapTool.h"


class playGround : public gameNode
{
private:
	
public:
	virtual HRESULT init(void);		//�ʱ�ȭ �Լ�
	virtual void release(void);		//�޸� ���� ����
	virtual void update(void);		//������Ʈ(����)
	virtual void render(void);		//�׷��ִ� �Լ�


	playGround();
	~playGround();
};

