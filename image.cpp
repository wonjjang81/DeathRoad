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
	////�̹��� ������ �����ִٸ� ���������
	//if (_imageInfo != NULL) release();

	////�̹��� ���� ����
	//HRESULT hr = E_FAIL;
	//_imageInfo = new IMAGE_INFO;
	//_imageInfo->loadType = LOAD_EMPTY;
	//_imageInfo->resID = 0;
	//_imageInfo->x = 0;
	//_imageInfo->y = 0;
	//_imageInfo->width = width;	
	//_imageInfo->height = height;
	//_imageInfo->currentFrameX = 0;
	//_imageInfo->currentFrameY = 0;
	//_imageInfo->frameWidth = width;
	//_imageInfo->frameHeight = height;

	//_fileName = NULL;

	//// WIC�� ����ϱ� ���� Factory ��ü ����
	//hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
	//	IID_PPV_ARGS(&_imageInfo->pWICImageingFactory));
	//assert(hr == S_OK);

	////���ڴ� ����
	//hr = _imageInfo->pWICImageingFactory->CreateDecoderFromFilename(_fileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand,
	//	&(_imageInfo->pWICDecoder));
	//assert(hr == S_OK);

	////ù ��° �������� ����� �� �ִ� ��ü����
	//hr = _imageInfo->pWICDecoder->GetFrame(0, &_imageInfo->pWICFrameDecoder);
	//assert(hr == S_OK);

	////���� ������ ����
	//hr = _imageInfo->pWICImageingFactory->CreateFormatConverter(&_imageInfo->pWICFormatConverter);
	//assert(hr == S_OK);

	////��Ʈ������ ��ȯ
	//hr = _imageInfo->pWICFormatConverter->Initialize(_imageInfo->pWICFrameDecoder, GUID_WICPixelFormat32bppBGRA,
	//	WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);

	////��ȯ�� �̹��� ������ ����Ͽ� D2D�� ��Ʈ�� ����
	//hr = D2DMANAGER->pRenderTarget->CreateBitmapFromWicBitmap(_imageInfo->pWICFormatConverter, NULL, &_imageInfo->pBitmap);


	////��Ʈ���� ������ �����ʾҴٸ�
	//if (_imageInfo->pBitmap == NULL)
	//{
	//	//�޸� ���� ��Ű��
	//	release();
	//	return E_FAIL;	//�����ߴٰ� �˷���
	//}



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
	_imageInfo->x = 0;
	_imageInfo->y = 0;
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
		IID_PPV_ARGS(&_imageInfo->pWICImagingFactory));
	assert(hr == S_OK);

	// ���ڴ� ����
	hr = _imageInfo->pWICImagingFactory->CreateDecoderFromFilename(_fileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand,
		&(_imageInfo->pWICDecoder));
	assert(hr == S_OK);

	// �̹��� Flip
	hr = _imageInfo->pWICImagingFactory->CreateBitmapFlipRotator(&_imageInfo->pWICFlip);
	assert(hr == S_OK);

	// ù ��° �������� ����� �� �ִ� ��ü ����
	hr = _imageInfo->pWICDecoder->GetFrame(0, &_imageInfo->pWICFrameDecoder);
	assert(hr == S_OK);

	// ���� ������ ����
	hr = _imageInfo->pWICImagingFactory->CreateFormatConverter(&_imageInfo->pWICFormatConverter);
	assert(hr == S_OK);

	// ��Ʈ������ ��ȯ
	hr = _imageInfo->pWICFormatConverter->Initialize(_imageInfo->pWICFrameDecoder, GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);

	// ��ȯ�� �̹��� ������ ����Ͽ� D2D�� ��Ʈ�� ����
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

//���Ϸκ��� �̹��� �ʱ�ȭ            ó�� ���� ��ǥ    ����       ����
HRESULT image::init(LPCWSTR fileName, float x, float y, int width, int height)
{
	if (fileName == NULL) return E_FAIL;

	//�̹��� ������ �����ִٸ� ���������
	if (_imageInfo != NULL) release();

	//�̹��� ���� ����
	HRESULT hr = E_FAIL;
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->x = x;
	_imageInfo->y = y;
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
		IID_PPV_ARGS(&_imageInfo->pWICImagingFactory));
	assert(hr == S_OK);

	//���ڴ� ����
	hr = _imageInfo->pWICImagingFactory->CreateDecoderFromFilename(_fileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand,
		&(_imageInfo->pWICDecoder));
	assert(hr == S_OK);

	// �̹��� Flip
	hr = _imageInfo->pWICImagingFactory->CreateBitmapFlipRotator(&_imageInfo->pWICFlip);
	assert(hr == S_OK);

	//ù ��° �������� ����� �� �ִ� ��ü����
	hr = _imageInfo->pWICDecoder->GetFrame(0, &_imageInfo->pWICFrameDecoder);
	assert(hr == S_OK);

	//���� ������ ����
	hr = _imageInfo->pWICImagingFactory->CreateFormatConverter(&_imageInfo->pWICFormatConverter);
	assert(hr == S_OK);

	//��Ʈ������ ��ȯ
	hr = _imageInfo->pWICFormatConverter->Initialize(_imageInfo->pWICFrameDecoder, GUID_WICPixelFormat32bppPBGRA,
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

//�̹��� + �������ʱ�ȭ
HRESULT image::init(LPCWSTR fileName, int width, int height, int frameX, int frameY)
{
	if (fileName == NULL) return E_FAIL;

	//�̹��� ������ �����ִٸ� ���������
	if (_imageInfo != NULL) release();

	//�̹��� ���� ����
	HRESULT hr = E_FAIL;
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->x = 0;
	_imageInfo->y = 0;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	//���ϰ�� ����
	int len;
	len = lstrlenW(fileName);
	_fileName = new WCHAR[len + 1];
	lstrcpyW(_fileName, fileName);


	// WIC�� ����ϱ� ���� Factory ��ü ����
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&_imageInfo->pWICImagingFactory));
	assert(hr == S_OK);

	//���ڴ� ����
	hr = _imageInfo->pWICImagingFactory->CreateDecoderFromFilename(_fileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand,
		&(_imageInfo->pWICDecoder));
	assert(hr == S_OK);

	//ù ��° �������� ����� �� �ִ� ��ü����
	hr = _imageInfo->pWICDecoder->GetFrame(0, &_imageInfo->pWICFrameDecoder);
	assert(hr == S_OK);

	// �̹��� Flip
	hr = _imageInfo->pWICImagingFactory->CreateBitmapFlipRotator(&_imageInfo->pWICFlip);
	assert(hr == S_OK);

	//���� ������ ����
	hr = _imageInfo->pWICImagingFactory->CreateFormatConverter(&_imageInfo->pWICFormatConverter);
	assert(hr == S_OK);

	//��Ʈ������ ��ȯ
	hr = _imageInfo->pWICFormatConverter->Initialize(_imageInfo->pWICFrameDecoder, GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);

	//��ȯ�� �̹��� ������ ����Ͽ� D2D�� ��Ʈ�� ����
	hr = D2DMANAGER->pRenderTarget->CreateBitmapFromWicBitmap(_imageInfo->pWICFormatConverter, NULL, &_imageInfo->pBitmap);
	

	//��Ʈ���� ������ �����ʾҴٸ�
	if (_imageInfo->pBitmap == NULL)
	{	
		release();      //�޸� ���� ��Ű��
		return E_FAIL;	//�����ߴٰ� �˷���
	}

	return S_OK;
}

HRESULT image::init(LPCWSTR fileName, float x, float y, int width, int height, int frameX, int frameY)
{
	if (fileName == NULL) return E_FAIL;

	//�̹��� ������ �����ִٸ� ���������
	if (_imageInfo != NULL) release();

	//�̹��� ���� ����
	HRESULT hr = E_FAIL;
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	//���ϰ�� ����
	int len;
	len = lstrlenW(fileName);
	_fileName = new WCHAR[len + 1];
	lstrcpyW(_fileName, fileName);


	// WIC�� ����ϱ� ���� Factory ��ü ����
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&_imageInfo->pWICImagingFactory));
	assert(hr == S_OK);

	//���ڴ� ����
	hr = _imageInfo->pWICImagingFactory->CreateDecoderFromFilename(_fileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand,
		&(_imageInfo->pWICDecoder));
	assert(hr == S_OK);

	// �̹��� Flip
	hr = _imageInfo->pWICImagingFactory->CreateBitmapFlipRotator(&_imageInfo->pWICFlip);
	assert(hr == S_OK);

	//ù ��° �������� ����� �� �ִ� ��ü����
	hr = _imageInfo->pWICDecoder->GetFrame(0, &_imageInfo->pWICFrameDecoder);
	assert(hr == S_OK);

	//���� ������ ����
	hr = _imageInfo->pWICImagingFactory->CreateFormatConverter(&_imageInfo->pWICFormatConverter);
	assert(hr == S_OK);

	//��Ʈ������ ��ȯ
	hr = _imageInfo->pWICFormatConverter->Initialize(_imageInfo->pWICFrameDecoder, GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);

	//��ȯ�� �̹��� ������ ����Ͽ� D2D�� ��Ʈ�� ����
	hr = D2DMANAGER->pRenderTarget->CreateBitmapFromWicBitmap(_imageInfo->pWICFormatConverter, NULL, &_imageInfo->pBitmap);



	//��Ʈ���� ������ �����ʾҴٸ�
	if (_imageInfo->pBitmap == NULL)
	{
		release();      //�޸� ���� ��Ű��
		return E_FAIL;	//�����ߴٰ� �˷���
	}


	return S_OK;
}


//================================================================== 
//	                         Pixel �浹
//==================================================================

const HRESULT image::loadImageFromWIC(IWICBitmapSource* const source, int gridCountX, int gridCountY)
{
	//assert(_bitmapData->hMemDC == 0);

	//HRESULT hr;

	//WICPixelFormatGUID pixelFormat;
	//CHECK_HRESULT_RETURN_HR(source->GetPixelFormat(&pixelFormat));

	//if (pixelFormat != GUID_WICPixelFormat32bppBGR &&
	//	pixelFormat != GUID_WICPixelFormat32bppBGRA &&
	//	pixelFormat != GUID_WICPixelFormat32bppPBGRA)
	//	return E_FAIL;
	//
	//UINT width, height;
	//CHECK_HRESULT_RETURN_HR(source->GetSize(&width, &height));

	//BITMAPINFO bminfo;
	//ZeroMemory(&bminfo, sizeof(bminfo));
	//bminfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	//bminfo.bmiHeader.biWidth = width;
	//bminfo.bmiHeader.biHeight = -(LONG)height;
	//bminfo.bmiHeader.biPlanes = 1;
	//bminfo.bmiHeader.biBitCount = 32;
	//bminfo.bmiHeader.biCompression = BI_RGB;

	//HDC moniterDC = GetDC(NULL);
	//void* buffer = nullptr;

	//_bitmapData->hMemDC = CreateCompatibleDC(moniterDC);
	//_bitmapData->hBit = CreateDIBSection(_bitmapData->hMemDC, &bminfo, DIB_PAL_COLORS, &buffer, NULL, 0);
	//_bitmapData->hOBit = (HBITMAP)SelectObject(_bitmapData->hMemDC, _bitmapData->hBit);
	//_bitmapData->width = width;
	//_bitmapData->height = height;
	//_bitmapData->gridCountX = gridCountX;
	//_bitmapData->gridCountY = gridCountY;

	//ReleaseDC(NULL, moniterDC);

	return S_OK;
}


//================================================================== 
//	                         �̹��� ����
//==================================================================

//�̹��� ������
void image::release(void)
{
	//�̹��������� �ִٸ�
	if (_imageInfo)
	{
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);
	}
}


//================================================================== 
//	                         �̹��� ����
//==================================================================

//�⺻ �̹��� ����
void image::render(float opacity)
{
	float posX = _imageInfo->x;
	float posY = _imageInfo->y;

	if (_imageInfo->pBitmap != NULL)
	{
		//ȭ����̸� ���� X
		if (posX + _imageInfo->width < 0) return;
		if (posY + _imageInfo->height < 0) return;
		if (posX > WINSIZEX) return;
		if (posY > WINSIZEY) return;

		D2D1_RECT_F dxArea = RectF(posX, posY, posX + _imageInfo->width, posY + _imageInfo->height);
		D2D1_RECT_F dxArea2 = RectF(0, 0, _imageInfo->width, _imageInfo->height);

		D2DMANAGER->pRenderTarget->DrawBitmap(_imageInfo->pBitmap, dxArea, opacity,
			D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, dxArea2);
	}
}


//Translate �̹��� ����           �̵���ġXY				ȸ��(degree)
void image::render(float opacity, float destX, float destY, float angle, float scale)
{
	Matrix3x2F matTranslation;  //�¿��̵�
	Matrix3x2F matRot;          //ȸ��
	Matrix3x2F matScale;        //������
	Matrix3x2F matTM;           //�¿��̵� * ȸ�� * ������

	float posX = _imageInfo->x;
	float posY = _imageInfo->y;
	float centerX = posX + _imageInfo->width / 2 + destX;
	float centerY = posY + _imageInfo->height / 2 + destY;

	if (_imageInfo->pBitmap != NULL)
	{
		//ȭ����̸� ���� X
		if (posX + _imageInfo->width < 0) return;
		if (posY + _imageInfo->height < 0) return;
		if (posX > WINSIZEX) return;
		if (posY > WINSIZEY) return;

		D2D1_RECT_F dxArea = RectF(posX, posY, posX + _imageInfo->width, posY + _imageInfo->height);
		D2D1_RECT_F dxArea2 = RectF(0, 0, _imageInfo->width, _imageInfo->height);

		matTranslation = Matrix3x2F::Translation(destX, destY);
		matRot = Matrix3x2F::Rotation(angle, D2D1::Point2F(centerX, centerY));
		matScale = Matrix3x2F::Scale(scale, scale, Point2F(centerX, centerY));
		matTM = matTranslation * matRot * matScale;

		D2DMANAGER->pRenderTarget->SetTransform(matTM);
		D2DMANAGER->pRenderTarget->DrawBitmap(_imageInfo->pBitmap, dxArea, opacity,
			D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, dxArea2);

		//�ʱ�ȭ
		D2DMANAGER->pRenderTarget->SetTransform(Matrix3x2F::Identity());
	}
}


void image::render(float opacity, float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight)
{
	float posX = _imageInfo->x;
	float posY = _imageInfo->y;

	if (_imageInfo->pBitmap != NULL)
	{
		//ȭ����̸� ���� X
		if (posX + _imageInfo->width < 0) return;
		if (posY + _imageInfo->height < 0) return;
		if (posX > WINSIZEX) return;
		if (posY > WINSIZEY) return;

		D2D1_RECT_F dxArea = RectF(destX, destY, destX + _imageInfo->width, destY + _imageInfo->height);  // ����Ÿ�� ��¿���
		D2D1_RECT_F dxArea2 = RectF(sourX, sourY, sourX + sourWidth, sourY + sourHeight);				  // ��Ʈ�ʻ� ��¿���

		D2DMANAGER->pRenderTarget->DrawBitmap(_imageInfo->pBitmap, dxArea, opacity,
			D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, dxArea2);
	}
}

//------------------------------------------------------------------------------------
//*************************************** ���� ***************************************
//------------------------------------------------------------------------------------
void image::loopRender(float opacity, const LPRECT drawArea, int offSetX, int offSetY)
{
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % (int)_imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % (int)_imageInfo->height);

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
		rcSour.top = (y + offSetY) % (int)_imageInfo->height;
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
			rcSour.left = (x + offSetX) % (int)_imageInfo->width;
			rcSour.right = _imageInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(opacity, rcDest.left, rcDest.top,	        //�ѷ��� ��ġ X, Y
							rcSour.left, rcSour.top,			//�ѷ��� ��ġ
							rcSour.right - rcSour.left,			//����ũ��
							rcSour.bottom - rcSour.top);		//����ũ��
		}
	}

}


//================================================================== 
//	                     ������ �̹��� ����
//==================================================================

void image::frameRender(float opacity, float destX, float destY, float angle, float scale)
{
	Matrix3x2F matScale;	//������
	Matrix3x2F matRot;      //ȸ��
	Matrix3x2F matTM;       //�¿��̵� * ȸ��

	float posX = _imageInfo->x;
	float posY = _imageInfo->y;
	float centerX = posX + _imageInfo->frameWidth / 2;
	float centerY = posY + _imageInfo->frameHeight / 2;

	if (_imageInfo->pBitmap != NULL)
	{
		//ȭ����̸� ���� X
		if (posX + _imageInfo->width < 0) return;
		if (posY + _imageInfo->height < 0) return;
		if (posX > WINSIZEX) return;
		if (posY > WINSIZEY) return;

		D2D1_RECT_F dxArea = RectF(posX, posY, posX + _imageInfo->frameWidth, posY + _imageInfo->frameHeight);
		D2D1_RECT_F dxArea2 = RectF(_imageInfo->currentFrameX * _imageInfo->frameWidth,
									_imageInfo->currentFrameY * _imageInfo->frameHeight,
									(_imageInfo->currentFrameX + 1) * _imageInfo->frameWidth,
									(_imageInfo->currentFrameY + 1) * _imageInfo->frameHeight);

		matScale = Matrix3x2F::Scale(scale, scale, Point2F(centerX, centerY));
		matRot = Matrix3x2F::Rotation(angle, Point2F(centerX, centerY));
		matTM = matScale * matRot;

		D2DMANAGER->pRenderTarget->SetTransform(matTM);
		D2DMANAGER->pRenderTarget->DrawBitmap(_imageInfo->pBitmap, dxArea, opacity,
			D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, dxArea2);

		//�ʱ�ȭ
		D2DMANAGER->pRenderTarget->SetTransform(Matrix3x2F::Identity());
	}
}


void image::frameRender(float opacity, float destX, float destY, int currentFrameX, int currentFrameY, float angle, float scale)
{
	Matrix3x2F matScale;	//������
	Matrix3x2F matRot;      //ȸ��
	Matrix3x2F matTM;       //�¿��̵� * ȸ��

	float posX = destX;
	float posY = destY;
	float centerX = posX + _imageInfo->frameWidth / 2;
	float centerY = posY + _imageInfo->frameHeight / 2;

	if (_imageInfo->pBitmap != NULL)
	{
		//ȭ����̸� ���� X
		if (posX / scale + _imageInfo->frameWidth < 0) return;
		if (posY / scale + _imageInfo->frameHeight < 0) return;
		if (posX / scale > WINSIZEX) return;
		if (posY / scale > WINSIZEY) return;

		_imageInfo->pWICFlip->Initialize(_imageInfo->pWICFrameDecoder, WICBitmapTransformFlipHorizontal);
	

		D2D1_RECT_F dxArea = RectF(posX, posY, posX + _imageInfo->frameWidth, posY + _imageInfo->frameHeight);
		D2D1_RECT_F dxArea2 = RectF(currentFrameX * _imageInfo->frameWidth, currentFrameY * _imageInfo->frameHeight,
			((currentFrameX + 1) * _imageInfo->frameWidth), ((currentFrameY + 1) * _imageInfo->frameHeight));

		matScale = Matrix3x2F::Scale(scale, scale, Point2F(posX, posY));
		matRot = Matrix3x2F::Rotation(angle, Point2F(centerX, centerY));
		matTM = matScale * matRot;

		D2DMANAGER->pRenderTarget->SetTransform(matTM);
		D2DMANAGER->pRenderTarget->DrawBitmap(_imageInfo->pBitmap, dxArea, opacity, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, dxArea2);

		//�ʱ�ȭ
		D2DMANAGER->pRenderTarget->SetTransform(Matrix3x2F::Identity());
	}
}


void image::frameAniRender(float opacity, float destX, float destY, int framePosX, int framePosY, float angle)
{
	Matrix3x2F matTranslation;  //�¿��̵�
	Matrix3x2F matRot;          //ȸ��
	Matrix3x2F matTM;           //�¿��̵� * ȸ��

	float posX = destX;
	float posY = destY;
	float centerX = posX + _imageInfo->width / 2 + destX;
	float centerY = posY + _imageInfo->height / 2 + destY;

	if (_imageInfo->pBitmap != NULL)
	{
		//ȭ����̸� ���� X
		if (posX + _imageInfo->frameWidth < 0) return;
		if (posY + _imageInfo->frameHeight < 0) return;
		if (posX > WINSIZEX) return;
		if (posY > WINSIZEY) return;

		D2D1_RECT_F dxArea = RectF(posX, posY, posX + _imageInfo->frameWidth, posY + _imageInfo->frameHeight);
		D2D1_RECT_F dxArea2 = RectF(framePosX, framePosY, 
			(framePosX + _imageInfo->frameWidth), (framePosY + _imageInfo->frameHeight));

		matTranslation = Matrix3x2F::Translation(destX, destY);
		matRot = Matrix3x2F::Rotation(angle, D2D1::Point2F(centerX, centerY));
		matTM = matRot;

		D2DMANAGER->pRenderTarget->SetTransform(matTM);
		D2DMANAGER->pRenderTarget->DrawBitmap(_imageInfo->pBitmap, dxArea, opacity, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, dxArea2);

		//�ʱ�ȭ
		D2DMANAGER->pRenderTarget->SetTransform(Matrix3x2F::Identity());
	}
}


void image::frameEffectRender(float opacity, float destX, float destY, int framePosX, int framePosY, float frameWidth, float frameHeight, float angle)
{
	Matrix3x2F matTranslation;  //�¿��̵�
	Matrix3x2F matRot;          //ȸ��
	Matrix3x2F matTM;           //�¿��̵� * ȸ��

	float posX = destX;
	float posY = destY;
	float centerX = posX + frameWidth / 2;
	float centerY = posY + frameHeight / 2;
	float effectFrameWidth = frameWidth;
	float effectFrameHeight = frameHeight;

	if (_imageInfo->pBitmap != NULL)
	{
		//ȭ����̸� ���� X
		if (posX + _imageInfo->frameWidth < 0) return;
		if (posY + _imageInfo->frameHeight < 0) return;
		if (posX > WINSIZEX) return;
		if (posY > WINSIZEY) return;

		D2D1_RECT_F dxArea = RectF(posX, posY, posX + effectFrameWidth, posY + effectFrameHeight);
		D2D1_RECT_F dxArea2 = RectF(framePosX, framePosY,
			(framePosX + effectFrameWidth), (framePosY + effectFrameHeight));

		matTranslation = Matrix3x2F::Translation(destX, destY);
		matRot = Matrix3x2F::Rotation(angle, D2D1::Point2F(centerX, centerY));
		matTM = matRot;

		D2DMANAGER->pRenderTarget->SetTransform(matTM);
		D2DMANAGER->pRenderTarget->DrawBitmap(_imageInfo->pBitmap, dxArea, opacity, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, dxArea2);

		//�ʱ�ȭ
		D2DMANAGER->pRenderTarget->SetTransform(Matrix3x2F::Identity());
	}
}


//keyAnimation��
void image::aniRender(float opacity, float destX, float destY, animation* ani, float angle)
{
	frameAniRender(opacity, destX, destY, ani->getFramePos().x, ani->getFramePos().y, angle);
}

//effectManager��
void image::aniEffectRender(float opacity, float destX, float destY, animation* ani, float angle)
{
	frameEffectRender(opacity, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight(), angle);
}


