#include "stdafx.h"
#include "weapon.h"


weapon::weapon()
{
}
weapon::~weapon()
{
}


HRESULT weapon::init()
{
	_wpImg    = IMAGEMANAGER->findImage("����Ÿ�Ϲ���");
	_center.x = 0;
	_center.y = 0;
	_wpNum    = 0;



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
	_center.x = x;
	_center.y = y;
}

void weapon::render(int scale, int angle)
{
	//����ó��
	if (DATABASE->weapon.size() == 0) return;

	_wpImg->frameRender(1.0f, _center.x, _center.y, _vWp[_wpNum].frameX, _vWp[_wpNum].frameY, angle, scale);
}

void weapon::weaponSet()
{
	//����ó��
	if (DATABASE->weapon.size() > 3) return;

	for (int i = 0; i < DATABASE->weapon.size(); ++i)
	{
		switch (DATABASE->weapon[i].typeAtt)
		{
			case TYPE_A_WP_GUN:
				_vWp.push_back(DATABASE->weapon[i]);
			break;
			case TYPE_A_WP_BOMB:
				_vWp.push_back(DATABASE->weapon[i]);
			break;
			case TYPE_A_WP_SWORD:
				_vWp.push_back(DATABASE->weapon[i]);
			break;
			case TYPE_A_WP_MACHINE:
				_vWp.push_back(DATABASE->weapon[i]);
			break;
		}
	}
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

	if (_wpNum > 3) _wpNum = 0;
}