#include "stdafx.h"
#include "image.h"

//컴파일러 지시기 나는 마소이미지(32비트) 라이브러리를 사용하겠다
#pragma comment(lib, "msimg32.lib")

//멤버 이니셜라이즈
image::image()
	: _imageInfo(NULL),
	_fileName(NULL)
{
}
image::~image()
{

}


//================================================================== 
//	                         이미지 초기화
//==================================================================

//빈 비트맵 이미지 초기화
HRESULT image::init(int width, int height)
{
	//이미지 정보가 뭔가있다면 해제해줘라
	if (_imageInfo != NULL) release();

	//이미지 정보 생성
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

	_fileName = NULL;

	// WIC를 사용하기 위한 Factory 객체 생성
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&_imageInfo->pWICImageingFactory));
	assert(hr == S_OK);

	//디코더 생성
	hr = _imageInfo->pWICImageingFactory->CreateDecoderFromFilename(_fileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand,
		&(_imageInfo->pWICDecoder));
	assert(hr == S_OK);

	//첫 번째 프레임을 사용할 수 있는 객체구성
	hr = _imageInfo->pWICDecoder->GetFrame(0, &_imageInfo->pWICFrameDecoder);
	assert(hr == S_OK);

	//포맷 컨버터 생성
	hr = _imageInfo->pWICImageingFactory->CreateFormatConverter(&_imageInfo->pWICFormatConverter);
	assert(hr == S_OK);

	//비트맵으로 변환
	hr = _imageInfo->pWICFormatConverter->Initialize(_imageInfo->pWICFrameDecoder, GUID_WICPixelFormat32bppBGRA,
		WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);

	//변환된 이미지 형식을 사용하여 D2D용 비트맵 생성
	hr = D2DMANAGER->pRenderTarget->CreateBitmapFromWicBitmap(_imageInfo->pWICFormatConverter, NULL, &_imageInfo->pBitmap);


	//비트맵이 생성이 되지않았다면
	if (_imageInfo->pBitmap == NULL)
	{
		//메모리 해제 시키고
		release();
		return E_FAIL;	//실패했다고 알려라
	}

	return S_OK;
}


//파일로부터 이미지 초기화
HRESULT image::init(LPCWSTR fileName, int width, int height)
{
	if (fileName == NULL) return E_FAIL;

	//이미지 정보가 뭔가있다면 해제해줘라
	if (_imageInfo != NULL) release();

	//이미지 정보 생성
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

	//파일경로 복사
	int len;
	len = lstrlenW(fileName);
	_fileName = new WCHAR[len + 1];
	lstrcpyW(_fileName, fileName);

	// WIC를 사용하기 위한 Factory 객체 생성
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&_imageInfo->pWICImageingFactory));
	assert(hr == S_OK);

	//디코더 생성
	hr = _imageInfo->pWICImageingFactory->CreateDecoderFromFilename(_fileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand,
		&(_imageInfo->pWICDecoder));
	assert(hr == S_OK);

	//첫 번째 프레임을 사용할 수 있는 객체구성
	hr = _imageInfo->pWICDecoder->GetFrame(0, &_imageInfo->pWICFrameDecoder);
	assert(hr == S_OK);

	//포맷 컨버터 생성
	hr = _imageInfo->pWICImageingFactory->CreateFormatConverter(&_imageInfo->pWICFormatConverter);
	assert(hr == S_OK);

	//비트맵으로 변환
	hr = _imageInfo->pWICFormatConverter->Initialize(_imageInfo->pWICFrameDecoder, GUID_WICPixelFormat32bppBGRA,
		WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);

	//변환된 이미지 형식을 사용하여 D2D용 비트맵 생성
	hr = D2DMANAGER->pRenderTarget->CreateBitmapFromWicBitmap(_imageInfo->pWICFormatConverter, NULL, &_imageInfo->pBitmap);


	//비트맵이 생성이 되지않았다면
	if (_imageInfo->pBitmap == NULL)
	{
		//메모리 해제 시키고
		release();
		return E_FAIL;	//실패했다고 알려라
	}

	return S_OK;
}

//파일로부터 이미지 초기화            처음 시작 좌표    가로       세로
HRESULT image::init(LPCWSTR fileName, float x, float y, int width, int height)
{
	if (fileName == NULL) return E_FAIL;

	//이미지 정보가 뭔가있다면 해제해줘라
	if (_imageInfo != NULL) release();

	//이미지 정보 생성
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

	//파일경로 복사
	int len;
	len = lstrlenW(fileName);
	_fileName = new WCHAR[len + 1];
	lstrcpyW(_fileName, fileName);

	// WIC를 사용하기 위한 Factory 객체 생성
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&_imageInfo->pWICImageingFactory));
	assert(hr == S_OK);

	//디코더 생성
	hr = _imageInfo->pWICImageingFactory->CreateDecoderFromFilename(_fileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand,
		&(_imageInfo->pWICDecoder));
	assert(hr == S_OK);

	//첫 번째 프레임을 사용할 수 있는 객체구성
	hr = _imageInfo->pWICDecoder->GetFrame(0, &_imageInfo->pWICFrameDecoder);
	assert(hr == S_OK);

	//포맷 컨버터 생성
	hr = _imageInfo->pWICImageingFactory->CreateFormatConverter(&_imageInfo->pWICFormatConverter);
	assert(hr == S_OK);

	//비트맵으로 변환
	hr = _imageInfo->pWICFormatConverter->Initialize(_imageInfo->pWICFrameDecoder, GUID_WICPixelFormat32bppBGRA,
		WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);

	//변환된 이미지 형식을 사용하여 D2D용 비트맵 생성
	hr = D2DMANAGER->pRenderTarget->CreateBitmapFromWicBitmap(_imageInfo->pWICFormatConverter, NULL, &_imageInfo->pBitmap);


	//비트맵이 생성이 되지않았다면
	if (_imageInfo->pBitmap == NULL)
	{
		//메모리 해제 시키고
		release();
		return E_FAIL;	//실패했다고 알려라
	}

	return S_OK;
}

//이미지 + 프레임초기화
HRESULT image::init(LPCWSTR fileName, int width, int height, int frameX, int frameY)
{
	if (fileName == NULL) return E_FAIL;

	//이미지 정보가 뭔가있다면 해제해줘라
	if (_imageInfo != NULL) release();

	//이미지 정보 생성
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
	_imageInfo->currentFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	//파일경로 복사
	int len;
	len = lstrlenW(fileName);
	_fileName = new WCHAR[len + 1];
	lstrcpyW(_fileName, fileName);


	// WIC를 사용하기 위한 Factory 객체 생성
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&_imageInfo->pWICImageingFactory));
	assert(hr == S_OK);

	//디코더 생성
	hr = _imageInfo->pWICImageingFactory->CreateDecoderFromFilename(_fileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand,
		&(_imageInfo->pWICDecoder));
	assert(hr == S_OK);

	//첫 번째 프레임을 사용할 수 있는 객체구성
	hr = _imageInfo->pWICDecoder->GetFrame(0, &_imageInfo->pWICFrameDecoder);
	assert(hr == S_OK);

	//포맷 컨버터 생성
	hr = _imageInfo->pWICImageingFactory->CreateFormatConverter(&_imageInfo->pWICFormatConverter);
	assert(hr == S_OK);

	//비트맵으로 변환
	hr = _imageInfo->pWICFormatConverter->Initialize(_imageInfo->pWICFrameDecoder, GUID_WICPixelFormat32bppBGRA,
		WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);

	//변환된 이미지 형식을 사용하여 D2D용 비트맵 생성
	hr = D2DMANAGER->pRenderTarget->CreateBitmapFromWicBitmap(_imageInfo->pWICFormatConverter, NULL, &_imageInfo->pBitmap);


	//비트맵이 생성이 되지않았다면
	if (_imageInfo->pBitmap == NULL)
	{	
		release();      //메모리 해제 시키고
		return E_FAIL;	//실패했다고 알려라
	}

	return S_OK;
}

HRESULT image::init(LPCWSTR fileName, float x, float y, int width, int height, int frameX, int frameY)
{
	if (fileName == NULL) return E_FAIL;

	//이미지 정보가 뭔가있다면 해제해줘라
	if (_imageInfo != NULL) release();

	//이미지 정보 생성
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
	_imageInfo->currentFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	//파일경로 복사
	int len;
	len = lstrlenW(fileName);
	_fileName = new WCHAR[len + 1];
	lstrcpyW(_fileName, fileName);


	// WIC를 사용하기 위한 Factory 객체 생성
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&_imageInfo->pWICImageingFactory));
	assert(hr == S_OK);

	//디코더 생성
	hr = _imageInfo->pWICImageingFactory->CreateDecoderFromFilename(_fileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand,
		&(_imageInfo->pWICDecoder));
	assert(hr == S_OK);

	//첫 번째 프레임을 사용할 수 있는 객체구성
	hr = _imageInfo->pWICDecoder->GetFrame(0, &_imageInfo->pWICFrameDecoder);
	assert(hr == S_OK);

	//포맷 컨버터 생성
	hr = _imageInfo->pWICImageingFactory->CreateFormatConverter(&_imageInfo->pWICFormatConverter);
	assert(hr == S_OK);

	//비트맵으로 변환
	hr = _imageInfo->pWICFormatConverter->Initialize(_imageInfo->pWICFrameDecoder, GUID_WICPixelFormat32bppBGRA,
		WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);

	//변환된 이미지 형식을 사용하여 D2D용 비트맵 생성
	hr = D2DMANAGER->pRenderTarget->CreateBitmapFromWicBitmap(_imageInfo->pWICFormatConverter, NULL, &_imageInfo->pBitmap);


	//비트맵이 생성이 되지않았다면
	if (_imageInfo->pBitmap == NULL)
	{
		release();      //메모리 해제 시키고
		return E_FAIL;	//실패했다고 알려라
	}


	return S_OK;
}



//이미지 릴리즈
void image::release(void)
{
	//이미지정보가 있다면
	if (_imageInfo)
	{
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);
	}
}


//================================================================== 
//	                         이미지 렌더
//==================================================================

//기본 이미지 렌더
void image::render(float opacity)
{
	float posX = _imageInfo->x;
	float posY = _imageInfo->y;

	if (_imageInfo->pBitmap != NULL)
	{
		//화면밖이면 렌더 X
		if (posX + _imageInfo->width < 0) return;
		if (posY + _imageInfo->height < 0) return;
		if (posX > WINSIZEX) return;
		if (posY > WINSIZEY) return;

		D2D1_RECT_F dxArea = RectF(posX, posY, posX + _imageInfo->width, posY + _imageInfo->height);
		D2D1_RECT_F dxArea2 = RectF(0, 0, _imageInfo->width, _imageInfo->height);

		D2DMANAGER->pRenderTarget->DrawBitmap(_imageInfo->pBitmap, dxArea, opacity,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxArea2);
	}
}


//Translate 이미지 렌더           이동위치XY				회전(degree)
void image::render(float opacity, float destX, float destY, float angle)
{
	Matrix3x2F matTranslation;  //좌우이동
	Matrix3x2F matRot;          //회전
	Matrix3x2F matTM;           //좌우이동 * 회전

	float posX = destX;
	float posY = destY;
	float centerX = posX + _imageInfo->width / 2 + destX;
	float centerY = posY + _imageInfo->height / 2 + destY;

	if (_imageInfo->pBitmap != NULL)
	{
		//화면밖이면 렌더 X
		if (posX + _imageInfo->width < 0) return;
		if (posY + _imageInfo->height < 0) return;
		if (posX > WINSIZEX) return;
		if (posY > WINSIZEY) return;

		D2D1_RECT_F dxArea = RectF(posX, posY, posX + _imageInfo->width, posY + _imageInfo->height);
		D2D1_RECT_F dxArea2 = RectF(0, 0, _imageInfo->width, _imageInfo->height);

		matTranslation = Matrix3x2F::Translation(destX, destY);
		matRot = Matrix3x2F::Rotation(angle, D2D1::Point2F(centerX, centerY));
		matTM = matTranslation * matRot;

		D2DMANAGER->pRenderTarget->SetTransform(matTM);
		D2DMANAGER->pRenderTarget->DrawBitmap(_imageInfo->pBitmap, dxArea, opacity,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxArea2);

		//초기화
		D2DMANAGER->pRenderTarget->SetTransform(Matrix3x2F::Identity());
	}
}


void image::render(float opacity, float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight)
{
	float posX = destX;
	float posY = destY;

	if (_imageInfo->pBitmap != NULL)
	{
		//화면밖이면 렌더 X
		if (posX + sourWidth < 0) return;
		if (posY + sourHeight < 0) return;
		if (posX > WINSIZEX) return;
		if (posY > WINSIZEY) return;

		D2D1_RECT_F dxArea = RectF(posX, posY, posX + _imageInfo->width, posY + _imageInfo->height);
		D2D1_RECT_F dxArea2 = RectF(sourX, sourY, sourWidth, sourHeight);

		D2DMANAGER->pRenderTarget->DrawBitmap(_imageInfo->pBitmap, dxArea, opacity,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxArea2);
	}
}

void image::loopRender(float opacity, const LPRECT drawArea, int offSetX, int offSetY)
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

	//Y축 루프부터
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;

		sourHeight = rcSour.bottom - rcSour.top;

		//화면밖으로 나갔으면~  나간영역만큼을 확보한다
		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//화면밖으로 나간영역만큼 뿌려줄 위치에 산정한다
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

			render(opacity, rcDest.left, rcDest.top,	        //뿌려줄 위치 X, Y
							rcSour.left, rcSour.top,			//뿌려올 위치
							rcSour.right - rcSour.left,			//가로크기
							rcSour.bottom - rcSour.top);		//세로크기
		}
	}

}


//================================================================== 
//	                     프레임 이미지 렌더
//==================================================================

void image::frameRender(float opacity, int destX, int destY, float angle)
{
	Matrix3x2F matTranslation;  //좌우이동
	Matrix3x2F matRot;          //회전
	Matrix3x2F matTM;           //좌우이동 * 회전

	float posX = destX;
	float posY = destY;
	float centerX = posX + _imageInfo->width / 2 + destX;
	float centerY = posY + _imageInfo->height / 2 + destY;

	if (_imageInfo->pBitmap != NULL)
	{
		//화면밖이면 렌더 X
		if (posX + _imageInfo->width < 0) return;
		if (posY + _imageInfo->height < 0) return;
		if (posX > WINSIZEX) return;
		if (posY > WINSIZEY) return;

		D2D1_RECT_F dxArea = RectF(posX, posY, posX + _imageInfo->frameWidth, posY + _imageInfo->frameHeight);
		D2D1_RECT_F dxArea2 = RectF(_imageInfo->currentFrameX * _imageInfo->frameWidth,
									_imageInfo->currentFrameY * _imageInfo->frameHeight,
									(_imageInfo->currentFrameX + 1) * _imageInfo->frameWidth,
									(_imageInfo->currentFrameY + 1) * _imageInfo->frameHeight);

		matTranslation = Matrix3x2F::Translation(destX, destY);
		matRot = Matrix3x2F::Rotation(angle, D2D1::Point2F(centerX, centerY));
		matTM = matTranslation * matRot;

		D2DMANAGER->pRenderTarget->SetTransform(matTM);
		D2DMANAGER->pRenderTarget->DrawBitmap(_imageInfo->pBitmap, dxArea, opacity,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxArea2);

		//초기화
		D2DMANAGER->pRenderTarget->SetTransform(Matrix3x2F::Identity());
	}
}


void image::frameRender(float opacity, int destX, int destY, int currentFrameX, int currentFrameY, float angle)
{
	Matrix3x2F matTranslation;  //좌우이동
	Matrix3x2F matRot;          //회전
	Matrix3x2F matTM;           //좌우이동 * 회전

	float posX = destX;
	float posY = destY;
	float centerX = posX + _imageInfo->width / 2 + destX;
	float centerY = posY + _imageInfo->height / 2 + destY;

	if (_imageInfo->pBitmap != NULL)
	{
		//화면밖이면 렌더 X
		if (posX + _imageInfo->width < 0) return;
		if (posY + _imageInfo->height < 0) return;
		if (posX > WINSIZEX) return;
		if (posY > WINSIZEY) return;

		D2D1_RECT_F dxArea = RectF(posX, posY, posX + _imageInfo->frameWidth, posY + _imageInfo->frameHeight);
		D2D1_RECT_F dxArea2 = RectF(currentFrameX * _imageInfo->frameWidth,
									currentFrameY * _imageInfo->frameHeight,
									(currentFrameX + 1) * _imageInfo->frameWidth,
									(currentFrameY + 1) * _imageInfo->frameHeight);

		matTranslation = Matrix3x2F::Translation(destX, destY);
		matRot = Matrix3x2F::Rotation(angle, D2D1::Point2F(centerX, centerY));
		matTM = matTranslation * matRot;

		D2DMANAGER->pRenderTarget->SetTransform(matTM);
		D2DMANAGER->pRenderTarget->DrawBitmap(_imageInfo->pBitmap, dxArea, opacity,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxArea2);

		//초기화
		D2DMANAGER->pRenderTarget->SetTransform(Matrix3x2F::Identity());
	}
}


void image::aniRender(float opacity, int destX, int destY, animation* ani)
{
	render(opacity, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
}