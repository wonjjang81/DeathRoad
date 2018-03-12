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

	//����Ʈâ
	_editWindow = IMAGEMANAGER->findImage("����â");

	//----------------------- grid -----------------------
	//grid ���Ϳ� ���
	if ((_vTile.size() == 0))
	{
		for (int i = 0; i < TILEY; ++i)
		{
			for (int j = 0; j < TILEX; ++j)
			{
				//��Ʈ�� �׸���
				tagSampleTile tile;
				tile.rc.left = TILE_SIZEX * j;
				tile.rc.top = TILE_SIZEY * i;
				tile.rc.right = TILE_SIZEX * (j + 1);
				tile.rc.bottom = TILE_SIZEY * (i + 1);
				tile.index = (TILEX * i) + j;

				_vTile.push_back(tile);
			}
		}
	}
	//----------------------------------------------------

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
	selectTile(_viewScale);            //Ÿ�ϸ� ����
	menuRender();                      //�޴� â
	tileDraw(_viewScale);              //Ÿ�� �׸���

	gameNode::render();                //���� Ÿ����
	gridRender(_viewScale);            //Ÿ�ϸ� �׸���
	btnRender();					   //�޴� ��ư
}





