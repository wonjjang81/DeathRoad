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

	_selectChar->charSetup("Female", "여성머리", "여성보디", "여성헤어", "여성안경", "여성모자", 100, 100, 7.0f);

	
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
	//배경색
	D2DMANAGER->fillRectangle(D2DMANAGER->createBrush(RGB(0, 0, 0)), 0, 0, WINSIZEX, WINSIZEY);
	D2DMANAGER->fillRectangle(D2DMANAGER->createBrush(RGB(255, 255, 255)), 100, 100, 268, 268);

	_selectChar->charRender("FemaleHead", 0);
	_selectChar->charRender("FemaleBody", 0);
	_selectChar->charRender("FemaleBody", 3);
	_selectChar->charRender("FemaleHair", 0);
	_selectChar->charRender("FemaleGlass", 0);
	_selectChar->charRender("FemaleHats", 0);

}
