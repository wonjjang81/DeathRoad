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


	return S_OK;
}

void mapTool::release()
{

}

void mapTool::update() 
{
	mapKeyControl();
	selectTile();

}

void mapTool::render() 
{
	//D2DMANAGER->fillRectangle(D2DMANAGER->defaultBrush, 0, 0, _showWindowX, _showWindowY);
	_editWindow->render(1.0, 720, 0);
	gridRender(_viewScale);



}


void mapTool::selectTile()
{
	if ()
	{
		D2DMANAGER->pRenderTarget->
	}


}

