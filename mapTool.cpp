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
	gameNode::init();

	//Ÿ������ ����
	_tileData = new dataSave;
	_tileData->dataSet();

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


	//Ÿ�� �׸���
	ZeroMemory(&_drawTile, sizeof(tagTile));
	_menuTabOn = false;

	//Ÿ�ϸ���
	isAResetOn = false;
	isTResetOn = false;

	//Ÿ������
	_isSaveVector = false;

	//Ÿ�� 
	_tileX = _tileY = 0;

	//��ID
	_doorId = 0;


	return S_OK;
}

void mapTool::release()
{

}

void mapTool::update() 
{
	gameNode::update();

	mapKeyControl();  //Ÿ�ϸ� Ű ��Ʈ��
	btnUpdate();      //�޴� ��ư
	menuUpdate();     //�޴� ��

} 

void mapTool::render() 
{
	_editWindow->render(1.0f, 720, 0); //�޴�
	menuRender();                      //�޴� â
	gameNode::render();                //���� Ÿ����
	tileDraw(_viewScale);              //Ÿ�� �׸���
	gridRender(_viewScale);            //Ÿ�ϸ� �׸���
	selectTile(_viewScale);            //Ÿ�ϸ� ����
	btnRender();					   //�޴� ��ư
}





