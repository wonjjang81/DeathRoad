#include "stdafx.h"
#include "image.h"

//�����Ϸ� ���ñ� ���� �����̹���(32��Ʈ) ���̺귯���� ����ϰڴ�
#pragma comment(lib, "msimg32.lib")

//��� �̴ϼȶ�����
image::image()
	: _imageInfo(NULL),
	_fileName(NULL)
{
}
image::~image()
{

}


//================================================================== 
//	                         �̹��� �ʱ�ȭ
//==================================================================

//�� ��Ʈ�� �̹��� �ʱ�ȭ
HRESULT image::init(int width, int height)
{
	//�̹��� ������ �����ִٸ� ���������
	if (_imageInfo != NULL) release();

	//�̹��� ���� ����
	HRESULT hr = E_FAIL;
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->width = width;	
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width;
	_imageInfo->frameHeight = height;

	_fileName = NULL;

	// WIC�� ����ϱ� ���� Factory ��ü ����
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&_imageInfo->pWICImageingFactory));
	assert(hr == S_OK);

	//���ڴ� ����
	hr = _imageInfo->pWICImageingFactory->CreateDecoderFromFilename(_fileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand,
		&(_imageInfo->pWICDecoder));
	assert(hr == S_OK);

	//ù ��° �������� ����� �� �ִ� ��ü����
	hr = _imageInfo->pWICDecoder->GetFrame(0, &_imageInfo->pWICFrameDecoder);
	assert(hr == S_OK);

	//���� ������ ����
	hr = _imageInfo->pWICImageingFactory->CreateFormatConverter(&_imageInfo->pWICFormatConverter);
	assert(hr == S_OK);

	//��Ʈ������ ��ȯ
	hr = _imageInfo->pWICFormatConverter->Initialize(_imageInfo->pWICFrameDecoder, GUID_WICPixelFormat32bppBGRA,
		WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);

	//��ȯ�� �̹��� ������ ����Ͽ� D2D�� ��Ʈ�� ����
	hr = D2DMANAGER->pRenderTarget->CreateBitmapFromWicBitmap(_imageInfo->pWICFormatConverter, NULL, &_imageInfo->pBitmap);


	//��Ʈ���� ������ �����ʾҴٸ�
	if (_imageInfo->pBitmap == NULL)
	{
		//�޸� ���� ��Ű��
		release();
		return E_FAIL;	//�����ߴٰ� �˷���
	}

	return S_OK;
}


//���Ϸκ��� �̹��� �ʱ�ȭ
HRESULT image::init(LPCWSTR fileName, int width, int height)
{
	if (fileName == NULL) return E_FAIL;

	//�̹��� ������ �����ִٸ� ���������
	if (_imageInfo != NULL) release();

	//�̹��� ���� ����
	HRESULT hr = E_FAIL;
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width;
	_imageInfo->frameHeight = height;

	//���ϰ�� ����
	int len;
	len = lstrlenW(fileName);
	_fileName = new WCHAR[len + 1];
	lstrcpyW(_fileName, fileName);

	// WIC�� ����ϱ� ���� Factory ��ü ����
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&_imageInfo->pWICImageingFactory));
	assert(hr == S_OK);

	//���ڴ� ����
	hr = _imageInfo->pWICImageingFactory->CreateDecoderFromFilename(_fileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand,
		&(_imageInfo->pWICDecoder));
	assert(hr == S_OK);

	//ù ��° �������� ����� �� �ִ� ��ü����
	hr = _imageInfo->pWICDecoder->GetFrame(0, &_imageInfo->pWICFrameDecoder);
	assert(hr == S_OK);

	//���� ������ ����
	hr = _imageInfo->pWICImageingFactory->CreateFormatConverter(&_imageInfo->pWICFormatConverter);
	assert(hr == S_OK);

	//��Ʈ������ ��ȯ
	hr = _imageInfo->pWICFormatConverter->Initialize(_imageInfo->pWICFrameDecoder, GUID_WICPixelFormat32bppBGRA,
		WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);

	//��ȯ�� �̹��� ������ ����Ͽ� D2D�� ��Ʈ�� ����
	hr = D2DMANAGER->pRenderTarget->CreateBitmapFromWicBitmap(_imageInfo->pWICFormatConverter, NULL, &_imageInfo->pBitmap);


	//��Ʈ���� ������ �����ʾҴٸ�
	if (_imageInfo->pBitmap == NULL)
	{
		//�޸� ���� ��Ű��
		release();
		return E_FAIL;	//�����ߴٰ� �˷���
	}

	return S_OK;
}

//���Ϸκ��� �̹��� �ʱ�ȭ           ó�� ���� ��ǥ      ����       ����
HRESULT image::init(LPCWSTR fileName, float x, float y, int width, int height)
{


	return S_OK;
}

//�̹��� + �������ʱ�ȭ
HRESULT image::init(LPCWSTR fileName, float x, float y, int width, int height, int frameX, int frameY)
{


	return S_OK;
}


HRESULT image::init(LPCWSTR fileName, int width, int height, int frameX, int frameY)
{


	return S_OK;
}


//�̹��� ������
void image::release(void)
{
	//�̹��������� �ִٸ�
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);
		
		//init�Լ� �ȿ� ���� �̹��� ������ �ֱ⿡ �̷��� �����Ѵ� 
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);
		SAFE_DELETE(_blendImage);

		_trans = false;
		_transColor = RGB(0, 0, 0);
	}
}


//Ȥ�� Ʈ����ó���� �ٸ� �ȼ������� �ٲ���Ѵٸ�
void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

void image::render(HDC hdc)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,				//����� ������ DC
			_imageInfo->x,		//����� ��ǥ X
			_imageInfo->y,		//����� ��ǥ Y
			_imageInfo->width,	//����� ũ��(����)
			_imageInfo->height,	//����� ũ��(����)
			_imageInfo->hMemDC,	//�����ؿ� DC
			0, 0,				//�����ؿ� ��ǥX,Y
			_imageInfo->width,	//�����ؿ� ũ��
			_imageInfo->height,	//�����ؿ� ũ��
			_transColor);		//�����ؿö� � �÷��� ���� �����ò���
	}
	else
	{
		//����ۿ� �ִ� ���� DC�������� ��Ӻ������ִ� �Լ�
		BitBlt(hdc, 
			_imageInfo->x,
			_imageInfo->y,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}


//�������Լ� �Ѹ�DC , �Ѹ���X(Left), �Ѹ���Y(top)
void image::render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,				//����� ������ DC
			destX,				//����� ��ǥ X
			destY,				//����� ��ǥ Y
			_imageInfo->width,	//����� ũ��(����)
			_imageInfo->height,	//����� ũ��(����)
			_imageInfo->hMemDC,	//�����ؿ� DC
			0, 0,				//�����ؿ� ��ǥX,Y
			_imageInfo->width,	//�����ؿ� ũ��
			_imageInfo->height,	//�����ؿ� ũ��
			_transColor);		//�����ؿö� � �÷��� ���� �����ò���
	}
	else
	{
		//����ۿ� �ִ� ���� DC�������� ��Ӻ������ִ� �Լ�
		BitBlt(hdc, destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}

//					DC����   �׷�����ǥ X, Y       �̹��������ؿ�X,Y, width, height
void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//����� ����DC
			destX,					//����� ��ǥ X
			destY,					//����� ��ǥ Y
			sourWidth,				//����� ����ũ��
			sourHeight,				//����� ����ũ��
			_imageInfo->hMemDC,
			sourX, sourY,			//�����ؿ� ��ǥ
			sourWidth,				//�����ؿ� ����ũ��
			sourHeight,				//�����ؿ� ����ũ��
			_transColor);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			sourWidth,
			sourHeight,
			_imageInfo->hMemDC,
			sourX, sourY,
			SRCCOPY);
	}

}

void image::loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);


	int sourWidth;
	int sourHeight;

	RECT rcDest;
	RECT rcSour;

	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawAreaX;
	int drawAreaH = drawArea->bottom - drawAreaY;

	//Y�� ��������
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;

		sourHeight = rcSour.bottom - rcSour.top;

		//ȭ������� ��������~  ����������ŭ�� Ȯ���Ѵ�
		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//ȭ������� ����������ŭ �ѷ��� ��ġ�� �����Ѵ�
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc, rcDest.left, rcDest.top,//�ѷ��� ��ġ X, Y
				rcSour.left, rcSour.top,		//�ѷ��� ��ġ
				rcSour.right - rcSour.left,		//����ũ��
				rcSour.bottom - rcSour.top);	//����ũ��
		}
	}

}


void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,								//����� ������ DC
			destX,								//����� ��ǥ X
			destY,								//����� ��ǥ Y
			_imageInfo->frameWidth,				//����� ũ��(����)
			_imageInfo->frameHeight,			//����� ũ��(����)
			_imageInfo->hMemDC,					//�����ؿ� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//�����ؿ� ��ǥX,Y
			_imageInfo->frameWidth,				//�����ؿ� ũ��
			_imageInfo->frameHeight,			//�����ؿ� ũ��
			_transColor);						//�����ؿö� � �÷��� ���� �����ò���
	}
	else
	{
		//����ۿ� �ִ� ���� DC�������� ��Ӻ������ִ� �Լ�
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, 
			SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		GdiTransparentBlt(
			hdc,								//����� ������ DC
			destX,								//����� ��ǥ X
			destY,								//����� ��ǥ Y
			_imageInfo->frameWidth,				//����� ũ��(����)
			_imageInfo->frameHeight,			//����� ũ��(����)
			_imageInfo->hMemDC,					//�����ؿ� DC
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,	//�����ؿ� ��ǥX,Y
			_imageInfo->frameWidth,				//�����ؿ� ũ��
			_imageInfo->frameHeight,			//�����ؿ� ũ��
			_transColor);						//�����ؿö� � �÷��� ���� �����ò���
	}
	else
	{
		//����ۿ� �ִ� ���� DC�������� ��Ӻ������ִ� �Լ�
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

void image::alphaRender(HDC hdc, BYTE alpha)
{
	//���� �̹��� �ҽ��� ���ĺ��带 ��������ִ� �Լ� == BYTE�� ���ļ�ġ 0 ~ 255
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		//���� ���� �̹����� �����Ѵ�
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, hdc, _imageInfo->x, _imageInfo->y, SRCCOPY);
		//�����ؿ� �̹������� Ʈ�����÷��� ���ܳ���
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);
		//���ܳ� �����̹����� ���ĺ��带 �����Ų��
		//�����ϴ� ��, �����ؿ��� ���� ������ ���� �ٶ���. �ϵ�ĥ�� �漺�漺^^7
		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width,
			_imageInfo->height, _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width,
			_imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	//���� �̹��� �ҽ��� ���ĺ��带 ��������ִ� �Լ� == BYTE�� ���ļ�ġ 0 ~ 255
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		//���� ���� �̹����� �����Ѵ�
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, hdc, destX, destY, SRCCOPY);
		//�����ؿ� �̹������� Ʈ�����÷��� ���ܳ���
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);
		//���ܳ� �����̹����� ���ĺ��带 �����Ų��
		//�����ϴ� ��, �����ؿ��� ���� ������ ���� �ٶ���. �ϵ�ĥ�� �漺�漺^^7
		AlphaBlend(hdc, destX, destY, _imageInfo->width,
			_imageInfo->height, _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->width,
			_imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	//����� �ϵ�ĥ�� �� �� ������� ¥�� �ϵ�ĥ������ �����ִ� ������
	//���ð��� 1
	//���� �����϶�� �ִ� ��!

}

void image::aniRender(HDC hdc, int destX, int destY, animation* ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
}