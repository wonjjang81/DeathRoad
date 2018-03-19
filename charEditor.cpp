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
	_saveChar = new charInfo;

	typeChange(CHAR_FEMALE);


	_selectChar = new character;
	_selectChar->init();
	_selectChar->charSetup(_saveChar->charTypeName, _saveChar->charHeadName,
		_saveChar->charBodyName, _saveChar->charHairName, _saveChar->charGlasName,
		_saveChar->charHatsName, 100, 100, 7.0f);

	//================================================== 버튼 ==================================================
	//HEAD
	int imgReX = 300;
	int imgReY = 100;
	_btnHead = new fButton;
	_btnHead->initB("맵툴버튼", L"HEAD",    18, imgReX + 50,  imgReY, 11, 4, PointMake(1, 2), PointMake(0, 2), 3);
	_btnHeadLeft = new fButton;
	_btnHeadLeft->init("맵툴버튼화살", L"",  5, imgReX,       imgReY + 8, PointMake(1, 0), PointMake(0, 0), 3);
	_btnHeadRight = new fButton;
	_btnHeadRight->init("맵툴버튼화살", L"", 5, imgReX + 190, imgReY + 8, PointMake(1, 1), PointMake(0, 1), 3);

	//BODY
	imgReX = 300;
	imgReY = 150;
	_btnBody = new fButton;
	_btnBody->initB("맵툴버튼", L"BODY",    18, imgReX + 50,  imgReY, 11, 4, PointMake(1, 2), PointMake(0, 2), 3);
	_btnBodyLeft = new fButton;
	_btnBodyLeft->init("맵툴버튼화살", L"",  5, imgReX,       imgReY + 8, PointMake(1, 0), PointMake(0, 0), 3);
	_btnBodyRight = new fButton;
	_btnBodyRight->init("맵툴버튼화살", L"", 5, imgReX + 190, imgReY + 8, PointMake(1, 1), PointMake(0, 1), 3);

	//HAIR
	imgReX = 300;
	imgReY = 200;
	_btnHair = new fButton;
	_btnHair->initB("맵툴버튼", L"HAIR",    18, imgReX + 50,  imgReY, 11, 4, PointMake(1, 2), PointMake(0, 2), 3);
	_btnHairLeft = new fButton;
	_btnHairLeft->init("맵툴버튼화살", L"",  5, imgReX,       imgReY + 8, PointMake(1, 0), PointMake(0, 0), 3);
	_btnHairRight = new fButton;
	_btnHairRight->init("맵툴버튼화살", L"", 5, imgReX + 190, imgReY + 8, PointMake(1, 1), PointMake(0, 1), 3);

	//GLASS
	imgReX = 300;
	imgReY = 250;
	_btnGlass = new fButton;
	_btnGlass->initB("맵툴버튼", L"GLASS",  18, imgReX + 50,   imgReY, 7.5, 4, PointMake(1, 2), PointMake(0, 2), 3);
	_btnGlasLeft = new fButton;
	_btnGlasLeft->init("맵툴버튼화살", L"",  5, imgReX,		   imgReY + 8, PointMake(1, 0), PointMake(0, 0), 3);
	_btnGlasRight = new fButton;
	_btnGlasRight->init("맵툴버튼화살", L"", 5, imgReX + 190,  imgReY + 8, PointMake(1, 1), PointMake(0, 1), 3);

	//HATS
	imgReX = 300;
	imgReY = 300;
	_btnHats = new fButton;
	_btnHats->initB("맵툴버튼", L"HATS",    18, imgReX + 50,  imgReY, 11, 4, PointMake(1, 2), PointMake(0, 2), 3);
	_btnHatsLeft = new fButton;
	_btnHatsLeft->init("맵툴버튼화살", L"",  5, imgReX,		  imgReY + 8, PointMake(1, 0), PointMake(0, 0), 3);
	_btnHatsRight = new fButton;
	_btnHatsRight->init("맵툴버튼화살", L"", 5, imgReX + 190, imgReY + 8, PointMake(1, 1), PointMake(0, 1), 3);

	//SAVE
	imgReX = 600;
	imgReY = 100;
	_btnSave = new fButton;
	_btnSave->initB("맵툴버튼", L"SAVE", 18, imgReX, imgReY, 11, 4, PointMake(1, 2), PointMake(0, 2), 3);
	//================================================== 버튼 ==================================================

	_headIndex   = 0;
	_upBodyIndex = 3;
	_dwBodyIndex = 0;
	_hairIndex   = 0;
	_glassIndex  = 0;
	_hatsIndex   = 0;

	_previousNum = 0;


	
	return S_OK;
}

void charEditor::release()
{

}

void charEditor::update()
{
	//========= 버튼 =========
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

	//SAVE
	_btnSave->update();
	if (_btnSave->getBtnOn())
	{
		saveChar();
		_btnSave->setBtnOff(false);
	}

	//------- keyAction ------
	btnAction(_btnHeadLeft,  _saveChar->charTypeName, HEAD_LEFT);
	btnAction(_btnHeadRight, _saveChar->charTypeName, HEAD_RIGHT);
							
	btnAction(_btnBodyLeft,  _saveChar->charTypeName, UPBODY_LEFT);
	btnAction(_btnBodyRight, _saveChar->charTypeName, UPBODY_RIGHT);

	btnAction(_btnHairLeft,  _saveChar->charTypeName, HAIR_LEFT);
	btnAction(_btnHairRight, _saveChar->charTypeName, HAIR_RIGHT);
								
	btnAction(_btnGlasLeft,  _saveChar->charTypeName, GLASS_LEFT);
	btnAction(_btnGlasRight, _saveChar->charTypeName, GLASS_RIGHT);
									
	btnAction(_btnHatsLeft,  _saveChar->charTypeName, HATS_LEFT);
	btnAction(_btnHatsRight, _saveChar->charTypeName, HATS_RIGHT);
	//========================

}

void charEditor::render()
{
	//배경색
	D2DMANAGER->fillRectangle(D2DMANAGER->createBrush(RGB(0, 0, 0)), 0, 0, WINSIZEX, WINSIZEY);
	D2DMANAGER->fillRectangle(D2DMANAGER->createBrush(RGB(255, 255, 255)), 100, 100, 268, 268);

	//========= 버튼 =========
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

	//SAVE
	_btnSave->render();
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
	//예외처리
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


void charEditor::saveChar()
{
	//3명까지만 저장
	if (_team.size() > 3) _team.erase(_team.begin());

	_saveChar->headIndex   = _headIndex;
	_saveChar->upBodyIndex = _upBodyIndex;
	_saveChar->dwBodyIndex = _dwBodyIndex;
	_saveChar->hairIndex   = _hairIndex;
	_saveChar->glassIndex  = _glassIndex;
	_saveChar->hatsIndex   = _hatsIndex;


	DATABASE->player.push_back(_saveChar);
	//_team.push_back(_saveChar);
}

void charEditor::typeChange(CHARTYPE typeName)
{
	switch (typeName)
	{
		case CHAR_FEMALE:
			_saveChar->charTypeName.clear();
			_saveChar->charTypeName.append("Female");
			_saveChar->charHeadName.clear();
			_saveChar->charHeadName.append("여성머리");
			_saveChar->charBodyName.clear();
			_saveChar->charBodyName.append("여성보디");
			_saveChar->charHairName.clear();
			_saveChar->charHairName.append("여성헤어");
			_saveChar->charGlasName.clear();
			_saveChar->charGlasName.append("여성안경");
			_saveChar->charHatsName.clear();
			_saveChar->charHatsName.append("여성모자");
		break;
		case CHAR_MAN:

		break;
		case CHAR_SPECIAL:

		break;
		case CHAR_ZOMBIE:

		break;
	}
}