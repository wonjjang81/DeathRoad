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
	//���̵�
	_moveX = _moveY = 0;
	_moveSpeed = 3.0f;
	_showWindowX = SAMPLETILEX * TILE_SIZEX * 3;
	_showWindowY = SAMPLETILEY * TILE_SIZEY * 3;
	_tileScale = 3;


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
	gridRender(_tileScale);



}


void mapTool::gridRender(float scale)
{
	//cameraOutLine
	D2DMANAGER->drawRectangle(D2DMANAGER->defaultBrush, 0, 0, _showWindowX, _showWindowY);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{

		//Ÿ�ϸ� Ŭ����
		D2DMANAGER->pRenderTarget->PushAxisAlignedClip(RectF(0, 0, _showWindowX, _showWindowY), D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);


		//������ ����
		Matrix3x2F matScale;
		matScale = Matrix3x2F::Scale(scale, scale, Point2F(0, 0));
		D2DMANAGER->pRenderTarget->SetTransform(matScale);


		//grid
		for (int i = 0; i <= TILEY; ++i)
		{
			for (int j = 0; j <= TILEX; ++j)
			{
				//����ó��: ȭ��� ����X
				if ((j * TILE_SIZEX) + _moveX >= _showWindowX / scale) continue;  //���ο�(����)
				if ((j * TILE_SIZEX) + _moveX <= 0)					  continue;	 //���ο�(����)
				if ((i * TILE_SIZEY) + _moveY >= _showWindowY / scale) continue;  //���ο�(����)
				if ((i * TILE_SIZEY) + _moveY <= 0)					  continue;  //���ο�(����)

				D2DMANAGER->drawLine(D2DMANAGER->createBrush(RGB(0, 255, 0), 0.03f), (TILE_SIZEX * j) + _moveX, 0 + _moveY, (TILE_SIZEX * j) + _moveX, TILE_TOTAL_SIZEY + _moveY, 0.3f);
				D2DMANAGER->drawLine(D2DMANAGER->createBrush(RGB(0, 255, 0), 0.03f), 0 + _moveX, (TILE_SIZEY * i) + _moveY, TILE_TOTAL_SIZEX + _moveX, (TILE_SIZEY * i) + _moveY, 0.3f);
			}
		}

		//index
		for (int i = 0; i < TILEY; ++i)
		{
			for (int j = 0; j < TILEX; ++j)
			{
				//����ó��: ȭ��� ����X
				if ((j * TILE_SIZEX) + _moveX >= _showWindowX / scale) continue;  //���ο�(����)
				if ((j * TILE_SIZEX) + _moveX < 0)					  continue;	 //���ο�(����)
				if ((i * TILE_SIZEY) + _moveY >= _showWindowY / scale) continue;  //���ο�(����)
				if ((i * TILE_SIZEY) + _moveY < 0)					  continue;  //���ο�(����)

				WCHAR strIndex[128];
				ZeroMemory(&strIndex, sizeof(strIndex));
				swprintf(strIndex, L"%d", (TILEX * i) + j);

				D2DMANAGER->drawTextDwd(D2DMANAGER->createBrush(RGB(0, 0, 255), 0.3f), L"�������", 3, strIndex,
					(j * TILE_SIZEX) + _moveX, (i * TILE_SIZEY) + _moveY,
					(j * TILE_SIZEX) + 30 + _moveX, (i * TILE_SIZEY) + 30 + _moveY);
			}
		}


		//�ʱ�ȭ
		D2DMANAGER->pRenderTarget->SetTransform(Matrix3x2F::Identity());
		D2DMANAGER->pRenderTarget->PopAxisAlignedClip();

	}

}

void mapTool::mapKeyControl()
{
	//Ű����
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		//����ó��:�̵�X   (Ÿ��ũ�� X ������ X ȭ��� Ÿ�ϼ�)
		if (abs(_moveX) >= (TILE_SIZEX) * (TILEX - (int)(_showWindowX / (TILE_SIZEX * _tileScale)))) return;
		_moveX -= 1 * _moveSpeed;		
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (_moveX >= 0) return;  //����ó��:�̵�X 
		_moveX += 1 * _moveSpeed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (_moveY >= 0) return;  //����ó��:�̵�X 
		_moveY += 1 * _moveSpeed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		//����ó��:�̵�X   (Ÿ��ũ�� X ������ X ȭ��� Ÿ�ϼ�)
		if (abs(_moveY) >= (TILE_SIZEY) * (TILEY - (int)(_showWindowX / (TILE_SIZEY * _tileScale)))) return;
		_moveY -= 1 * _moveSpeed;
	}

	//������ ����
	if (KEYMANAGER->isOnceKeyDown('P'))	 _tileScale++;	if (_tileScale >= 5) _tileScale = 5;
	if (KEYMANAGER->isOnceKeyDown('O'))	 _tileScale--;	if (_tileScale <= 2) _tileScale = 2;
}