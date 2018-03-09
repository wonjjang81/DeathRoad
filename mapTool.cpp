#include "stdafx.h"
#include "mapTool.h"


mapTool::mapTool()
{
}
mapTool::~mapTool()
{
}

HRESULT mapTool::init()
{
	//����Ʈâ
	_editWindow = IMAGEMANAGER->findImage("����â");

	//���̵�
	_moveX = _moveY = 0;
	_moveSpeed = 3.0f;

	//Ÿ�ϸ� ��� ũ��
	_showWindowX = SAMPLETILEX * TILE_SIZEX * 3;
	_showWindowY = SAMPLETILEY * TILE_SIZEY * 3;
	_viewScale = 3;  //Ÿ�� ������

	//��ư
	btnSetup();

	//�޴�
	_currentMenu = NULL;

	return S_OK;
}

void mapTool::release()
{

}

void mapTool::update() 
{
	mapKeyControl();  //Ÿ�ϸ� Ű ��Ʈ��
	btnUpdate();      //�޴� ��ư

}

void mapTool::render() 
{
	_editWindow->render(1.0f, 720, 0); //�޴�
	gridRender(_viewScale);            //Ÿ�ϸ� �׸���
	selectTile(_viewScale);            //Ÿ�ϸ� ����
	btnRender();					   //�޴� ��ư
	menuRender();                      //�޴� â
}



