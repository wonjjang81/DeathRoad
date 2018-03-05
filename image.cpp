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

//파일로부터 이미지 초기화           처음 시작 좌표      가로       세로
HRESULT image::init(LPCWSTR fileName, float x, float y, int width, int height)
{


	return S_OK;
}

//이미지 + 프레임초기화
HRESULT image::init(LPCWSTR fileName, float x, float y, int width, int height, int frameX, int frameY)
{


	return S_OK;
}


HRESULT image::init(LPCWSTR fileName, int width, int height, int frameX, int frameY)
{


	return S_OK;
}


//이미지 릴리즈
void image::release(void)
{
	//이미지정보가 있다면
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);
		
		//init함수 안에 블렌드 이미지 정보도 있기에 이렇게 구성한다 
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


//혹시 트랜스처리를 다른 픽셀값으로 바꿔야한다면
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
			hdc,				//복사될 영역의 DC
			_imageInfo->x,		//복사될 좌표 X
			_imageInfo->y,		//복사될 좌표 Y
			_imageInfo->width,	//복사될 크기(가로)
			_imageInfo->height,	//복사될 크기(세로)
			_imageInfo->hMemDC,	//복사해올 DC
			0, 0,				//복사해올 좌표X,Y
			_imageInfo->width,	//복사해올 크기
			_imageInfo->height,	//복사해올 크기
			_transColor);		//복사해올때 어떤 컬러를 빼고 가져올꺼냐
	}
	else
	{
		//백버퍼에 있는 것을 DC영역으로 고속복사해주는 함수
		BitBlt(hdc, 
			_imageInfo->x,
			_imageInfo->y,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}


//렌더링함수 뿌릴DC , 뿌릴곳X(Left), 뿌릴곳Y(top)
void image::render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,				//복사될 영역의 DC
			destX,				//복사될 좌표 X
			destY,				//복사될 좌표 Y
			_imageInfo->width,	//복사될 크기(가로)
			_imageInfo->height,	//복사될 크기(세로)
			_imageInfo->hMemDC,	//복사해올 DC
			0, 0,				//복사해올 좌표X,Y
			_imageInfo->width,	//복사해올 크기
			_imageInfo->height,	//복사해올 크기
			_transColor);		//복사해올때 어떤 컬러를 빼고 가져올꺼냐
	}
	else
	{
		//백버퍼에 있는 것을 DC영역으로 고속복사해주는 함수
		BitBlt(hdc, destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}

//					DC영역   그려줄좌표 X, Y       이미지복사해올X,Y, width, height
void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//복사될 영역DC
			destX,					//복사될 좌표 X
			destY,					//복사될 좌표 Y
			sourWidth,				//복사될 가로크기
			sourHeight,				//복사될 세로크기
			_imageInfo->hMemDC,
			sourX, sourY,			//복사해올 좌표
			sourWidth,				//복사해올 가로크기
			sourHeight,				//복사해올 세로크기
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

			render(hdc, rcDest.left, rcDest.top,//뿌려줄 위치 X, Y
				rcSour.left, rcSour.top,		//뿌려올 위치
				rcSour.right - rcSour.left,		//가로크기
				rcSour.bottom - rcSour.top);	//세로크기
		}
	}

}


void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,								//복사될 영역의 DC
			destX,								//복사될 좌표 X
			destY,								//복사될 좌표 Y
			_imageInfo->frameWidth,				//복사될 크기(가로)
			_imageInfo->frameHeight,			//복사될 크기(세로)
			_imageInfo->hMemDC,					//복사해올 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//복사해올 좌표X,Y
			_imageInfo->frameWidth,				//복사해올 크기
			_imageInfo->frameHeight,			//복사해올 크기
			_transColor);						//복사해올때 어떤 컬러를 빼고 가져올꺼냐
	}
	else
	{
		//백버퍼에 있는 것을 DC영역으로 고속복사해주는 함수
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
			hdc,								//복사될 영역의 DC
			destX,								//복사될 좌표 X
			destY,								//복사될 좌표 Y
			_imageInfo->frameWidth,				//복사될 크기(가로)
			_imageInfo->frameHeight,			//복사될 크기(세로)
			_imageInfo->hMemDC,					//복사해올 DC
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,	//복사해올 좌표X,Y
			_imageInfo->frameWidth,				//복사해올 크기
			_imageInfo->frameHeight,			//복사해올 크기
			_transColor);						//복사해올때 어떤 컬러를 빼고 가져올꺼냐
	}
	else
	{
		//백버퍼에 있는 것을 DC영역으로 고속복사해주는 함수
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
	//실제 이미지 소스에 알파블렌드를 접목시켜주는 함수 == BYTE는 알파수치 0 ~ 255
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		//알파 먹일 이미지를 복사한다
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, hdc, _imageInfo->x, _imageInfo->y, SRCCOPY);
		//복사해온 이미지에서 트랜스컬러를 벗겨낸다
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);
		//벗겨낸 최종이미지에 알파블렌드를 적용시킨다
		//복사하는 곳, 복사해오는 곳을 유심히 보기 바란다. 북두칠성 충성충성^^7
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
	//실제 이미지 소스에 알파블렌드를 접목시켜주는 함수 == BYTE는 알파수치 0 ~ 255
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		//알파 먹일 이미지를 복사한다
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, hdc, destX, destY, SRCCOPY);
		//복사해온 이미지에서 트랜스컬러를 벗겨낸다
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);
		//벗겨낸 최종이미지에 알파블렌드를 적용시킨다
		//복사하는 곳, 복사해오는 곳을 유심히 보기 바란다. 북두칠성 충성충성^^7
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
	//여기는 북두칠성 그 외 사람들이 짜서 북두칠성에게 선물주는 것으로
	//오늘과제 1
	//알파 공부하라고 주는 것!

}

void image::aniRender(HDC hdc, int destX, int destY, animation* ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
}