#include "stdafx.h"
#include "UIManager.h"


UIManager::UIManager()
{
}
UIManager::~UIManager()
{
}


HRESULT UIManager::init()
{
	_foodNum   = 0;
	_drugNum   = 0;
	_oilNum    = 0;
	_bulletNum = 0;

	textX = 50;
	textY = WINSIZEY - 50;

	_itemImg = IMAGEMANAGER->findImage("맵툴타일아이템");
	_wpImg = IMAGEMANAGER->findImage("맵툴타일무기");

	_wpFrameX = -1;
	_wpFrameY = -1;

	//무기
	_vWp = new weapon;
	_vWp->init(2);

	return S_OK;
}

void UIManager::release()
{

}

void UIManager::update() 
{
	_foodNum   = getItem(TYPE_A_IT_FOOD);
	_drugNum   = getItem(TYPE_A_IT_DRUG);
	_oilNum    = getItem(TYPE_A_IT_OIL);
	_bulletNum = getItem(TYPE_A_IT_BULLET);

	//무기
	_vWp->weaponChange();
	_vWp->update(textX, textY);
}

void UIManager::render() 
{
	//무기
	_vWp->render(45);


	//아이템
	_itemImg->frameRender(1.0f, textX, textY, 1, 0, 0, 2.0f);
	D2DMANAGER->drawIntText(L"", _foodNum,   textX + 20 , textY + 5, RGB(255, 255, 255), L"Press Start 2P");

	_itemImg->frameRender(1.0f, textX + 100, textY, 0, 1, 0, 2.0f);
	D2DMANAGER->drawIntText(L"", _drugNum,   textX + 120, textY + 5, RGB(255, 255, 255), L"Press Start 2P");

	_itemImg->frameRender(1.0f, textX + 200, textY, 4, 1, 0, 2.0f);
	D2DMANAGER->drawIntText(L"", _oilNum,    textX + 220, textY + 5, RGB(255, 255, 255), L"Press Start 2P");

	_itemImg->frameRender(1.0f, textX + 300, textY, 0, 2, 0, 2.0f);
	D2DMANAGER->drawIntText(L"", _bulletNum, textX + 320, textY + 5, RGB(255, 255, 255), L"Press Start 2P");
}


int UIManager::getItem(TYPE_ATTRIBUTE attr)
{
	int itemNum = 0;
	for (int i = 0; i < DATABASE->item.size(); ++i)
	{
		if (DATABASE->item[i].typeAtt == attr)
		{
			itemNum += DATABASE->item[i].value;
		}
	}

	return itemNum;
}


