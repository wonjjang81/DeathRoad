#include "stdafx.h"
#include "charEditor.h"


charEditor::charEditor()
{
}
charEditor::~charEditor()
{
}


HRESULT charEditor::init()
{
	_selectChar = new character;
	_selectChar->init();

	_selectChar->charSetup("Female", "�����Ӹ�", "��������", "�������", "�����Ȱ�", "��������", 100, 100, 7.0f);

	
	return S_OK;
}

void charEditor::release()
{

}

void charEditor::update()
{

}

void charEditor::render()
{
	//����
	D2DMANAGER->fillRectangle(D2DMANAGER->createBrush(RGB(0, 0, 0)), 0, 0, WINSIZEX, WINSIZEY);
	D2DMANAGER->fillRectangle(D2DMANAGER->createBrush(RGB(255, 255, 255)), 100, 100, 268, 268);

	_selectChar->charRender("FemaleHead", 0);
	_selectChar->charRender("FemaleBody", 0);
	_selectChar->charRender("FemaleBody", 3);
	_selectChar->charRender("FemaleHair", 0);
	_selectChar->charRender("FemaleGlass", 0);
	_selectChar->charRender("FemaleHats", 0);

}
