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

	//================================================== ��ư ==================================================
	//HEAD
	int imgReX = 300;
	int imgReY = 100;
	_btnHead = new fButton;
	_btnHead->initB("������ư", L"HEAD",    18, imgReX + 50,  imgReY, 11, 4, PointMake(1, 2), PointMake(0, 2), 3);
	_btnHeadLeft = new fButton;
	_btnHeadLeft->init("������ưȭ��", L"",  5, imgReX,       imgReY + 8, PointMake(1, 0), PointMake(0, 0), 3);
	_btnHeadRight = new fButton;
	_btnHeadRight->init("������ưȭ��", L"", 5, imgReX + 190, imgReY + 8, PointMake(1, 1), PointMake(0, 1), 3);

	//BODY
	imgReX = 300;
	imgReY = 150;
	_btnBody = new fButton;
	_btnBody->initB("������ư", L"BODY",    18, imgReX + 50,  imgReY, 11, 4, PointMake(1, 2), PointMake(0, 2), 3);
	_btnBodyLeft = new fButton;
	_btnBodyLeft->init("������ưȭ��", L"",  5, imgReX,       imgReY + 8, PointMake(1, 0), PointMake(0, 0), 3);
	_btnBodyRight = new fButton;
	_btnBodyRight->init("������ưȭ��", L"", 5, imgReX + 190, imgReY + 8, PointMake(1, 1), PointMake(0, 1), 3);

	//HAIR
	imgReX = 300;
	imgReY = 200;
	_btnHair = new fButton;
	_btnHair->initB("������ư", L"HAIR",    18, imgReX + 50,  imgReY, 11, 4, PointMake(1, 2), PointMake(0, 2), 3);
	_btnHairLeft = new fButton;
	_btnHairLeft->init("������ưȭ��", L"",  5, imgReX,       imgReY + 8, PointMake(1, 0), PointMake(0, 0), 3);
	_btnHairRight = new fButton;
	_btnHairRight->init("������ưȭ��", L"", 5, imgReX + 190, imgReY + 8, PointMake(1, 1), PointMake(0, 1), 3);

	//GLASS
	imgReX = 300;
	imgReY = 250;
	_btnGlass = new fButton;
	_btnGlass->initB("������ư", L"GLASS",  18, imgReX + 50,   imgReY, 7.5, 4, PointMake(1, 2), PointMake(0, 2), 3);
	_btnGlasLeft = new fButton;
	_btnGlasLeft->init("������ưȭ��", L"",  5, imgReX,		   imgReY + 8, PointMake(1, 0), PointMake(0, 0), 3);
	_btnGlasRight = new fButton;
	_btnGlasRight->init("������ưȭ��", L"", 5, imgReX + 190,  imgReY + 8, PointMake(1, 1), PointMake(0, 1), 3);

	//HATS
	imgReX = 300;
	imgReY = 300;
	_btnHats = new fButton;
	_btnHats->initB("������ư", L"HATS",    18, imgReX + 50,  imgReY, 11, 4, PointMake(1, 2), PointMake(0, 2), 3);
	_btnHatsLeft = new fButton;
	_btnHatsLeft->init("������ưȭ��", L"",  5, imgReX,		  imgReY + 8, PointMake(1, 0), PointMake(0, 0), 3);
	_btnHatsRight = new fButton;
	_btnHatsRight->init("������ưȭ��", L"", 5, imgReX + 190, imgReY + 8, PointMake(1, 1), PointMake(0, 1), 3);
	//================================================== ��ư ==================================================

	_headIndex = 0;
	_upBodyIndex = 3;
	_dwBodyIndex = 0;
	_hairIndex = 0;
	_glassIndex = 0;
	_hatsIndex = 0;

	_previousNum = 0;
	
	return S_OK;
}

void charEditor::release()
{

}

void charEditor::update()
{
	//========= ��ư =========
	//-------- update --------
	//HEAD
	_btnHeadLeft->update();
	_btnHeadRight->update();
	//BODY
	_btnBodyLeft->update();
	_btnBodyRight->update();
	//HAIR
	_btnHairLeft->update();
	_btnHairRight->update();
	//GLASS
	_btnGlasLeft->update();
	_btnGlasRight->update();
	//HATS
	_btnHatsLeft->update();
	_btnHatsRight->update();

	//------- keyAction ------
	btnAction(_btnHeadLeft, "Female", HEAD_LEFT);
	btnAction(_btnHeadRight, "Female", HEAD_RIGHT);

	btnAction(_btnBodyLeft, "Female", UPBODY_LEFT);
	btnAction(_btnBodyRight, "Female", UPBODY_RIGHT);

	btnAction(_btnHairLeft, "Female", HAIR_LEFT);
	btnAction(_btnHairRight, "Female", HAIR_RIGHT);

	btnAction(_btnGlasLeft, "Female", GLASS_LEFT);
	btnAction(_btnGlasRight, "Female", GLASS_RIGHT);

	btnAction(_btnHatsLeft, "Female", HATS_LEFT);
	btnAction(_btnHatsRight, "Female", HATS_RIGHT);
	//========================

}

void charEditor::render()
{
	//����
	D2DMANAGER->fillRectangle(D2DMANAGER->createBrush(RGB(0, 0, 0)), 0, 0, WINSIZEX, WINSIZEY);
	D2DMANAGER->fillRectangle(D2DMANAGER->createBrush(RGB(255, 255, 255)), 100, 100, 268, 268);

	//========= ��ư =========
	//HEAD
	_btnHead->render();
	_btnHeadLeft->render();
	_btnHeadRight->render();
	//BODY
	_btnBody->render();
	_btnBodyLeft->render();
	_btnBodyRight->render();
	//HAIR
	_btnHair->render();
	_btnHairLeft->render();
	_btnHairRight->render();
	//GLASS
	_btnGlass->render();
	_btnGlasLeft->render();
	_btnGlasRight->render();
	//HATS
	_btnHats->render();
	_btnHatsLeft->render();
	_btnHatsRight->render();
	//========================


	_selectChar->charRender("FemaleHead",  _headIndex);
	_selectChar->charRender("FemaleBody",  _upBodyIndex);
	_selectChar->charRender("FemaleBody",  _dwBodyIndex);
	_selectChar->charRender("FemaleHair",  _hairIndex);
	_selectChar->charRender("FemaleGlass", _glassIndex);
	_selectChar->charRender("FemaleHats",  _hatsIndex);

}

void charEditor::btnAction(fButton* button, string charTypeName, BTN_CHAR_BODYTYPE btnBodyType)
{
	if (button->getBtnOn())
	{
		switch (btnBodyType)
		{
			case HEAD_LEFT:

				charTypeName.append("Head");
				btnIndexAction(_headIndex, false, 2, charTypeName);
				stringErase(charTypeName, "Head");

			break;
			case HEAD_RIGHT:

				charTypeName.append("Head");
				btnIndexAction(_headIndex, true, 2, charTypeName);
				stringErase(charTypeName, "Head");

			break;
			case UPBODY_LEFT:

				charTypeName.append("Body");
				btnIndexAction(_upBodyIndex, false, 5, charTypeName);
				stringErase(charTypeName, "Body");
	
			break;
			case UPBODY_RIGHT:

				charTypeName.append("Body");
				btnIndexAction(_upBodyIndex, true, 5, charTypeName);
				stringErase(charTypeName, "Body");
	
			break;
			case DWBODY_LEFT:

				charTypeName.append("Body");
				btnIndexAction(_dwBodyIndex, false, 3, charTypeName);
				stringErase(charTypeName, "Body");
	
			break;
			case DWBODY_RIGHT:

				charTypeName.append("Body");
				btnIndexAction(_dwBodyIndex, true, 3, charTypeName);
				stringErase(charTypeName, "Body");
	
			break;
			case HAIR_LEFT:

				charTypeName.append("Hair");
				btnIndexAction(_hairIndex, false, 2, charTypeName);
				stringErase(charTypeName, "Hair");
			
			break;
			case HAIR_RIGHT:

				charTypeName.append("Hair");
				btnIndexAction(_hairIndex, true, 2, charTypeName);
				stringErase(charTypeName, "Hair");
			
			break;
			case GLASS_LEFT:

				charTypeName.append("Glass");
				btnIndexAction(_glassIndex, false, 2, charTypeName);
				stringErase(charTypeName, "Glass");
		
			break;
			case GLASS_RIGHT:

				charTypeName.append("Glass");
				btnIndexAction(_glassIndex, true, 2, charTypeName);
				stringErase(charTypeName, "Glass");
		
			break;
			case HATS_LEFT:

				charTypeName.append("Hats");
				btnIndexAction(_hatsIndex, false, 2, charTypeName);
				stringErase(charTypeName, "Hats");
	
			break;
			case HATS_RIGHT:

				charTypeName.append("Hats");
				btnIndexAction(_hatsIndex, true, 2, charTypeName);
				stringErase(charTypeName, "Hats");
	
			break;
		}

		button->setBtnOff(false);
	}
}


void charEditor::btnIndexAction(int& btnIndexNum, bool Plus, int gapNum, string bodyTypeName)
{
	//����ó��
	int maxIndex = _selectChar->getMaxIndex(bodyTypeName);
	if (btnIndexNum <= 0)
	{
		_previousNum = btnIndexNum;

		if (btnIndexNum == 0)
		{
			btnIndexNum = 0;
		}
		else
		{
			btnIndexNum = _previousNum;
		}
	}
	if (btnIndexNum >= maxIndex)
	{
		_previousNum = btnIndexNum;

		if (btnIndexNum == maxIndex)
		{
			btnIndexNum = maxIndex;
		}
		else
		{
			btnIndexNum = _previousNum;
		}
	}

		//number +-
	if (Plus) btnIndexNum += gapNum;
	else btnIndexNum -= gapNum;
}