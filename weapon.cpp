#include "stdafx.h"
#include "weapon.h"


weapon::weapon()
{
}
weapon::~weapon()
{
}


HRESULT weapon::init(float scale)
{
	_wpImg    = IMAGEMANAGER->findImage("맵툴타일무기");
	_center.x = 0;
	_center.y = 0;
	_wpNum    = 0;
	_scale	  = scale;



	return S_OK;
}

void weapon::release()
{

}

void weapon::update(float x, float y)
{
	//무기저장
	weaponSet();

	//무기위치
	_center.x = x - (_wpImg->getFrameWidth() / 2  * _scale);
	_center.y = y - (_wpImg->getFrameHeight() / 2 * _scale + 20);
}

void weapon::render(int angle)
{
	//예외처리
	if (_vWp.size() == 0) return;
	//벡터사이즈 보다 클경우 렌더X
	if (_wpNum >= _vWp.size()) return;

	_wpImg->frameRender(1.0f, _center.x, _center.y, _vWp[_wpNum].frameX, _vWp[_wpNum].frameY, angle, _scale);
}

void weapon::renderB(int frameX, int frameY, int angle, bool flip)
{
	//예외처리
	if (frameX < 0) return;


	_wpImg->frameRender(1.0f, _center.x, _center.y + 15, frameX, frameY, angle, _scale, flip, 1.5, 1.7);
}

void weapon::weaponSet()
{
	//=============================== 예외처리 ===============================
	if (DATABASE->weapon.size() == 0 || DATABASE->weapon.size() >= 3) return;


	int vNum = -1;
	for (int i = 0; i < DATABASE->weapon.size(); ++i)
	{
		if (_vWp.size() == 0) vNum = 0;

		for (int j = 0; j < _vWp.size(); ++j)
		{
			if (_vWp[j].index == DATABASE->weapon[i].index) continue;
			vNum = i;
		}
	}
	//========================================================================


	if (vNum < 0) return;
	_vWp.push_back(DATABASE->weapon[vNum]);
	DATABASE->weapon.erase(DATABASE->weapon.begin() + vNum);
}

void weapon::weaponChange()
{
	//예외처리
	if (_vWp.size() == 0) return;

	//무기 체인지
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		_wpNum++;
	}

	if (_wpNum >= 3) _wpNum = 0;
}

