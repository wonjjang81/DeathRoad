#include "stdafx.h"
#include "mapTool.h"


mapTool::mapTool()
{
}
mapTool::~mapTool()
{
}

HRESULT mapTool::init()
{
	//����Ʈâ
	_editWindow = IMAGEMANAGER->findImage("����â");

	//���̵�
	_moveX = _moveY = 0;
	_moveSpeed = 3.0f;

	//Ÿ�ϸ� ��� ũ��
	_showWindowX = SAMPLETILEX * TILE_SIZEX * 3;
	_showWindowY = SAMPLETILEY * TILE_SIZEY * 3;
	_viewScale = 3;  //Ÿ�� ������


	return S_OK;
}

void mapTool::release()
{

}

void mapTool::update() 
{
	mapKeyControl();
	

}

void mapTool::render() 
{
	//D2DMANAGER->fillRectangle(D2DMANAGER->defaultBrush, 0, 0, _showWindowX, _showWindowY);
	_editWindow->render(1.0, 720, 0);
	gridRender(_viewScale);
	selectTile(_viewScale);

}


void mapTool::selectTile(int scale)
{
	//Ÿ�ϸ� Ŭ����
	D2DMANAGER->pRenderTarget->PushAxisAlignedClip(RectF(0, 0, _showWindowX, _showWindowY), D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);

	//������ ����
	Matrix3x2F matScale;
	matScale = Matrix3x2F::Scale(scale, scale, Point2F(0, 0));
	D2DMANAGER->pRenderTarget->SetTransform(matScale);

	for (int i = 0; i < _vTileRect.size(); ++i)
	{
		RECT reRect;
		reRect.left	  = _vTileRect[i].left * scale;
		reRect.top	  = _vTileRect[i].top * scale;
		reRect.right  = _vTileRect[i].right * scale;
		reRect.bottom = _vTileRect[i].bottom * scale;

		if (PtInRect(&reRect, _ptMouse))
		{
			D2DMANAGER->drawRectangle(D2DMANAGER->createBrush(RGB(0, 0, 255)), 
				_vTileRect[i].left + _moveX, _vTileRect[i].top + _moveY,
				_vTileRect[i].right + _moveX, _vTileRect[i].bottom + _moveY);

			break;
		}
	}

	//�ʱ�ȭ
	D2DMANAGER->pRenderTarget->SetTransform(Matrix3x2F::Identity());
	D2DMANAGER->pRenderTarget->PopAxisAlignedClip();
}


void mapTool::testDrawText(int value, float x, float y)
{
	WCHAR strIndex[128];
	ZeroMemory(&strIndex, sizeof(strIndex));
	swprintf(strIndex, L"%d", value);

	D2DMANAGER->drawTextDwd(D2DMANAGER->defaultBrush, L"�������", 18, strIndex, x, y, x + 200, y + 20);
}
