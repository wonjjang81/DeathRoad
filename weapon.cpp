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
	_wpImg    = IMAGEMANAGER->findImage("����Ÿ�Ϲ���");
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
	//��������
	weaponSet();

	//������ġ
	_center.x = x - (_wpImg->getFrameWidth() / 2  * _scale);
	_center.y = y - (_wpImg->getFrameHeight() / 2 * _scale + 20);
}

void weapon::render(int angle)
{
	//����ó��
	if (_vWp.size() == 0) return;
	//���ͻ����� ���� Ŭ��� ����X
	if (_wpNum >= _vWp.size()) return;

	_wpImg->frameRender(1.0f, _center.x, _center.y, _vWp[_wpNum].frameX, _vWp[_wpNum].frameY, angle, _scale);
}

void weapon::renderB(int frameX, int frameY, int angle, bool flip)
{
	//����ó��
	if (frameX < 0) return;


	_wpImg->frameRender(1.0f, _center.x, _center.y + 15, frameX, frameY, angle, _scale, flip, 1.5, 1.7);
}

void weapon::weaponSet()
{
	//=============================== ����ó�� ===============================
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
	//����ó��
	if (_vWp.size() == 0) return;

	//���� ü����
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		_wpNum++;
	}

	if (_wpNum >= 3) _wpNum = 0;
}

