#include "stdafx.h"
#include "fButton.h"


fButton::fButton()
{
}
fButton::~fButton()
{
}

HRESULT fButton::init(const char* imageName, LPCWSTR titleText, float textSize, float x, float y, POINT downFrame, POINT upFrame, float scale)
{
	_button.direction = BUTTONSTATE_NULL;
	_button.img = IMAGEMANAGER->findImage(imageName);
	_button.titleText = titleText;
	_button.x = x;
	_button.y = y;
	_button.btnDownFrame = downFrame;
	_button.btnUPFrame = upFrame;
	_button.rc = RectMake(x, y, _button.img->getFrameWidth() * scale, _button.img->getFrameHeight() * scale);
	_button.centerX = x + _button.img->getFrameWidth() / 4 * scale;
	_button.centerY = y + _button.img->getFrameWidth() / 4 * scale;
	_button.scale = scale;
	_button.textSize = textSize;
	_button.isOn = false;
	_button.ptIn = false;

	return S_OK;
}

void fButton::release()
{

}


void fButton::update()
{
	if (PtInRect(&_button.rc, _ptMouse))
	{
		_button.ptIn = true;

		//Ŭ���ϸ� ��ư�� ���´� ������
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_button.direction = BUTTONSTATE_DOWN;
			_button.isOn = true;
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _button.direction == BUTTONSTATE_DOWN)
		{
			//������ ���� ��ư�� ���´� �ö�Դ�
			_button.direction = BUTTONSTATE_UP;
		}
	}
	else _button.ptIn = false;

	//��ư OFF ���·�(�ܺο��� �Է�)
	if (!_button.isOn)
	{
		_button.direction = BUTTONSTATE_NULL;
	}

	

}

void fButton::render()
{
	switch (_button.direction)
	{
		//��ư�� �ʱ�ȭ �� �ö���ִ� ������ �̹����� ����
		case BUTTONSTATE_NULL:	case BUTTONSTATE_UP:
			_button.img->frameRender(1.0f, _button.rc.left, _button.rc.top,
				_button.btnUPFrame.x, _button.btnUPFrame.y, 0, _button.scale);

		break;

		//��ư ���������� �̹���
		case BUTTONSTATE_DOWN:
			_button.img->frameRender(1.0f, _button.rc.left, _button.rc.top,
				_button.btnDownFrame.x, _button.btnDownFrame.y, 0, _button.scale);

		break;
	}

	D2DMANAGER->drawTextDwd(D2DMANAGER->defaultBrush, L"Press Start 2P",
		_button.textSize, _button.titleText,
		_button.centerX, _button.centerY, _button.centerX + 200, _button.centerY + 30);
}

