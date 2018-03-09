#include "stdafx.h"
#include "d2dManager.h"


d2dManager::d2dManager()
{
}
d2dManager::~d2dManager()
{
}


HRESULT d2dManager::init()
{
	pD2DFactory = nullptr;
	pRenderTarget = nullptr;
	pBitmapRenderTarget = nullptr;

	HRESULT hr = E_FAIL;

	//---------------------------------------------------------------------------
	//	D2D Factory 생성
	//---------------------------------------------------------------------------
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
	assert(hr == S_OK);

	//---------------------------------------------------------------------------
	//	Hwnd Render Target 생성
	//---------------------------------------------------------------------------
	hr = pD2DFactory->CreateHwndRenderTarget(RenderTargetProperties(),
		HwndRenderTargetProperties(_hWnd, SizeU(WINSIZEX, WINSIZEY)), &pRenderTarget);
	assert(hr == S_OK);

	//renderTarget 복사
	hr = pRenderTarget->CreateCompatibleRenderTarget(SizeF((float)WINSIZEX, (float)WINSIZEY), &pBitmapRenderTarget);
	assert(hr == S_OK);

	//---------------------------------------------------------------------------
	//	IDWriteFactory 생성
	//---------------------------------------------------------------------------
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(pWriteFacory),
		reinterpret_cast<IUnknown**>(&pWriteFacory));
	assert(hr == S_OK);

	// 브러쉬 생성
	defaultBrush = createBrush(RGB(0, 0, 0));

	// 기본 텍스트 포맷 생성
	pWriteFacory->CreateTextFormat(L"맑은고딕", NULL, DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 17.0f, L"", &pDefaultTextFormat); 

	// COM 라이브러리 초기화 -> 호출하지 않으면 CoCreateInstance가 제대로 수행되지 않음
	CoInitialize(NULL);

	return S_OK;
}


void d2dManager::release()
{
	SAFE_RELEASE_D2D(defaultBrush);
	SAFE_RELEASE_D2D(pDefaultTextFormat);
	SAFE_RELEASE_D2D(pWriteFacory);	
	SAFE_RELEASE_D2D(pBitmapRenderTarget);
	SAFE_RELEASE_D2D(pRenderTarget);
	SAFE_RELEASE_D2D(pD2DFactory);
}

void d2dManager::update()
{

}

void d2dManager::render()
{

}

void d2dManager::beginDraw()
{
	pRenderTarget->BeginDraw();
	pRenderTarget->Clear(ColorF(ColorF::White));
}

void d2dManager::endDraw()	
{
	pRenderTarget->EndDraw();
}

ID2D1SolidColorBrush* d2dManager::createBrush(COLORREF rgb, float opacity)
{
	HRESULT hr;
	ID2D1SolidColorBrush* brush;
	brush = nullptr;

	hr = pRenderTarget->CreateSolidColorBrush(ColorF(rgb, opacity), &brush);

	return brush;
}


//==================================================================
//  Draw, Fill Method(Line, Rectangle, Ellipse)
//  카메라 이동 보정 & 범위에 들어가는 내용만 렌더
//==================================================================

void d2dManager::drawLine(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY, float strokeWidth)
{
	float x1 = startX;
	float y1 = startY;
	float x2 = endX;
	float y2 = endY;

	if (x1 < 0 && x1 > WINSIZEX) return;
	if (y1 < 0 && y1 > WINSIZEY) return;
	if (x2 < 0 && x2 > WINSIZEX) return;
	if (y2 < 0 && y2 > WINSIZEY) return;

	pRenderTarget->DrawLine(Point2F(x1, y1), Point2F(x2, y2), brush, strokeWidth);
}


void d2dManager::drawRectangle(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY, float strokeWidth)
{
	float x1 = startX;
	float y1 = startY;
	float x2 = endX;
	float y2 = endY;

	if (x1 < 0 && x1 > WINSIZEX) return;
	if (y1 < 0 && y1 > WINSIZEY) return;
	if (x2 < 0 && x2 > WINSIZEX) return;
	if (y2 < 0 && y2 > WINSIZEY) return;

	pRenderTarget->DrawRectangle(RectF(x1, y1, x2, y2), brush, strokeWidth);
}

void d2dManager::drawEllipse(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY, float strokeWidth)
{
	float x1 = startX;
	float y1 = startY;
	float x2 = endX;
	float y2 = endY;
	float width = endX - startX;
	float height = endY - startY;

	if (x1 < 0 && x1 > WINSIZEX) return;
	if (y1 < 0 && y1 > WINSIZEY) return;
	if (x2 < 0 && x2 > WINSIZEX) return;
	if (y2 < 0 && y2 > WINSIZEY) return;

	D2D1_ELLIPSE ellipse;
	ellipse.point.x = x1 + width / 2;
	ellipse.point.y = y1 + height / 2;
	ellipse.radiusX = width / 2;
	ellipse.radiusY = height / 2;

	pRenderTarget->DrawEllipse(&ellipse, brush, strokeWidth);
}

void d2dManager::fillRectangle(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY)
{
	float x1 = startX;
	float y1 = startY;
	float x2 = endX;
	float y2 = endY;

	if (x1 < 0 && x1 > WINSIZEX) return;
	if (y1 < 0 && y1 > WINSIZEY) return;
	if (x2 < 0 && x2 > WINSIZEX) return;
	if (y2 < 0 && y2 > WINSIZEY) return;

	pRenderTarget->FillRectangle(RectF(x1, y1, x2, y2), brush);
}

void d2dManager::fillEllipse(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY)
{
	float x1 = startX;
	float y1 = startY;
	float x2 = endX;
	float y2 = endY;
	float width = endX - startX;
	float height = endY - startY;

	if (x1 < 0 && x1 > WINSIZEX) return;
	if (y1 < 0 && y1 > WINSIZEY) return;
	if (x2 < 0 && x2 > WINSIZEX) return;
	if (y2 < 0 && y2 > WINSIZEY) return;

	D2D1_ELLIPSE ellipse;
	ellipse.point.x = x1 + width / 2;
	ellipse.point.y = y1 + height / 2;
	ellipse.radiusX = width / 2;
	ellipse.radiusY = height / 2;

	pRenderTarget->FillEllipse(&ellipse, brush);
}


void d2dManager::drawTextD2d(ID2D1SolidColorBrush* brush, LPCWSTR string, float startX, float startY, float endX, float endY)
{
	float x1 = startX;
	float y1 = startY;
	float x2 = endX;
	float y2 = endY;
	float width = endX - startX;
	float height = endY - startY;

	if (x1 < 0 && x1 > WINSIZEX) return;
	if (y1 < 0 && y1 > WINSIZEY) return;
	if (x2 < 0 && x2 > WINSIZEX) return;
	if (y2 < 0 && y2 > WINSIZEY) return;

	pRenderTarget->DrawTextA(string, lstrlenW(string), pDefaultTextFormat, RectF(x1, y1, x2, y2), brush);
}

void d2dManager::drawTextDwd(ID2D1SolidColorBrush* brush, LPCWSTR fontName, float fontSize, LPCWSTR string, float startX, float startY, float endX, float endY)
{
	float x1 = startX;
	float y1 = startY;
	float x2 = endX;
	float y2 = endY;

	if (x1 < 0 && x1 > WINSIZEX) return;
	if (y1 < 0 && y1 > WINSIZEY) return;
	if (x2 < 0 && x2 > WINSIZEX) return;
	if (y2 < 0 && y2 > WINSIZEY) return;

	pWriteFacory->CreateTextFormat(fontName, NULL, DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, fontSize, L"", &pCustomTextFormat);

	pRenderTarget->DrawTextA(string, lstrlenW(string), pCustomTextFormat, RectF(x1, y1, x2, y2), brush);

	SAFE_RELEASE_D2D(pCustomTextFormat);
}


//영역 클립핑(레이어)
HRESULT d2dManager::layerContentBound(ID2D1RenderTarget* pRt, D2D1_RECT_F cRect)
{
	HRESULT hr = S_OK;

	//레이어 생성
	ID2D1Layer* player = NULL;
	hr = pRt->CreateLayer(NULL, &player);

	if (SUCCEEDED(hr))
	{
		//push the layer with the content bounds
		pRt->PushLayer(LayerParameters(cRect), player);
	}

	SAFE_RELEASE_D2D(player);

	return hr;
}


void  d2dManager::drawIntText(int value, float x, float y)
{
	WCHAR strIndex[128];
	ZeroMemory(&strIndex, sizeof(strIndex));
	swprintf(strIndex, L"%d", value);

	D2DMANAGER->drawTextDwd(D2DMANAGER->defaultBrush, L"맑은고딕", 18, strIndex, x, y, x + 200, y + 20);
}