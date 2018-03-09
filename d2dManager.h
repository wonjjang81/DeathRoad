#pragma once
#include "singletonBase.h"


class d2dManager : public singletonBase<d2dManager>
{
public:
	ID2D1Factory*				pD2DFactory;
	ID2D1HwndRenderTarget*		pRenderTarget;
	ID2D1BitmapRenderTarget*	pBitmapRenderTarget;
	IDWriteFactory*				pWriteFacory;
	IDWriteTextFormat*			pDefaultTextFormat;
	IDWriteTextFormat*			pCustomTextFormat;
	ID2D1SolidColorBrush*		defaultBrush;


public:
	HRESULT init();
	void release();
	void update();
	void render();

	void beginDraw();
	void endDraw();

	ID2D1SolidColorBrush* createBrush(COLORREF rgb, float opacity = 1.0f);
	HRESULT layerContentBound(ID2D1RenderTarget* prt, D2D1_RECT_F cRect);


	//==================================================================
	//  Draw, Fill Method(Line, Rectangle, Ellipse)
	//  카메라 이동 보정 & 범위에 들어가는 내용만 렌더
	//==================================================================

	void drawLine(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY, float strokeWidth = 1.0f);
	void drawRectangle(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY, float strokeWidth = 1.0f);
	void drawEllipse(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY, float strokeWidth = 1.0f);
	void fillRectangle(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY);
	void fillEllipse(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY);

	//               그릴 브러쉬                  출력할 문자열   문자열 그릴 Rect 위치
	void drawTextD2d(ID2D1SolidColorBrush* brush, LPCWSTR string, float startX, float startY, float endX, float endY);
	void drawTextDwd(ID2D1SolidColorBrush* brush, LPCWSTR fontName, float fontSize, LPCWSTR string, float startX, float startY, float endX, float endY);


	//텍스트 in Value
	void drawIntText(int value, float x, float y);

	d2dManager();
	~d2dManager();
};

