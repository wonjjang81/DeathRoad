#pragma once
#include "gameNode.h"
#include "tile.h"
#include "button.h"


class mapTool : public gameNode
{
private:
	//editWindow
	image * _editWindow;

	//keyControl
	float _moveX, _moveY;
	float _moveSpeed;

	//grid
	float _showWindowX, _showWindowY;
	int   _viewScale;

	//��ư
	HWND _bt;


public:
	HRESULT init();
	void release();
	void update();
	void render();

	void gridRender(float scale = 1.0f);  	//Ÿ�� �׸���� ����
	void mapKeyControl();                   //�� Ű ��Ʈ��
	void selectTile();                      //Ÿ�� ���ý� ȭ�����

	mapTool();
	~mapTool();
};

