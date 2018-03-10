#include "stdafx.h"
#include "button.h"


button::button()
{
}


button::~button()
{
}

HRESULT button::init(const char* imageName, int x, int y,
	POINT btnDownFramePoint, POINT btnUpFramePoint,
	CALLBACK_FUNCTION cbFunction, float scale)
{
	//�ݹ��Լ��� �Լ������ͷ� ����ȭ ���ѳ��⶧���� ����ȯ�� �����
	_callbackFunction = static_cast<CALLBACK_FUNCTION>(cbFunction);

	_direction = BUTTONDIRECTION_NULL;

	_x = x;
	_y = y;

	_btnUpFramePoint = btnUpFramePoint;
	_btnDownFramePoint = btnDownFramePoint;

	_imageName = imageName;
	_image = IMAGEMANAGER->findImage(imageName);

	_rc = RectMake(x, y, _image->getFrameWidth() * scale, _image->getFrameHeight() * scale);

	return S_OK;
}

void button::release(void)
{

}

void button::update(void) 
{
	if (PtInRect(&_rc, _ptMouse))
	{
		//Ŭ���ϸ� ��ư�� ���´� ������
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_direction = BUTTONDIRECTION_DOWN;
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _direction == BUTTONDIRECTION_DOWN)
		{
			//������ ���� ��ư�� ���´� �ö�Դ�
			_direction = BUTTONDIRECTION_UP;
			_callbackFunction(); //�̶� �ݹ��Լ��� ����ȴ�
		}
	}
	else _direction = BUTTONDIRECTION_NULL;
}

void button::render(float scale) 
{
	switch (_direction)
	{
		//��ư�� �ʱ�ȭ �� �ö���ִ� ������ �̹����� ����
		case BUTTONDIRECTION_NULL:	case BUTTONDIRECTION_UP:
			_image->frameRender(1.0f, _rc.left, _rc.top,
				_btnUpFramePoint.x, _btnUpFramePoint.y, 0, scale);

			//��Ʈ Ȯ�ο�
			//D2DMANAGER->drawRectangle(D2DMANAGER->defaultBrush, _rc.left, _rc.top, _rc.right, _rc.bottom);
		break;
		//��ư ���������� �̹���
		case BUTTONDIRECTION_DOWN:
			_image->frameRender(1.0f, _rc.left, _rc.top,
				_btnDownFramePoint.x, _btnDownFramePoint.y, 0, scale);
		break;

	}
}
