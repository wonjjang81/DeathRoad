#pragma once
#include "animation.h"
//============================================
// ## 17.11.24 ## - image Class - ##
//============================================

class image
{
public:

	//이미지 불러오는 타입
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,		//리소스로부터
		LOAD_FILE,			//파일로부터
		LOAD_EMPTY,			//빈 비트맵으로부터
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		DWORD					resID;							
		IWICImagingFactory*		pWICImagingFactory;		//Windows Imagind Component를 위한 Factory 인터페이스
		IWICFormatConverter*    pWICFormatConverter;	//Format Converter
		IWICBitmapDecoder*      pWICDecoder;			//Bitmap Decoder
		IWICBitmapFrameDecode*  pWICFrameDecoder;       //프레임 Decoder 인터페이스
		ID2D1Bitmap*			pBitmap;                //D2D용 비트맵
		float                   x, y;                   //이미지 위치
		float					width;					//가로 크기(이미지)
		float					height;					//세로 크기(이미지)
		int						currentFrameX;			//현재 프레임 X
		int						currentFrameY;			//현재 프레임 Y
		int						maxFrameX;				//최대 프레임 X
		int						maxFrameY;				//최대 프레임 Y
		float					frameWidth;				//프레임 가로크기
		float					frameHeight;			//프레임 세로크기
		BYTE					loadType;				//이미지 불러올 타입
		RECT					boundingBox;			//바운딩 박스(충돌체크용 박스)

		tagImageInfo()
		{
			resID				= 0;
			pWICImagingFactory = nullptr;
			pWICFormatConverter = nullptr;
			pWICDecoder			= nullptr;
			pWICFrameDecoder	= nullptr;
			pBitmap				= nullptr;
			x					= 0;
			y					= 0;
			width				= 0;
			height				= 0;
			currentFrameX		= 0;
			currentFrameY		= 0;
			maxFrameX			= 0;
			maxFrameY			= 0;
			frameWidth			= 0;
			frameHeight			= 0;
			loadType			= LOAD_RESOURCE;
			boundingBox			= RectMake(0, 0, 0, 0);
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		//이미지 정보 구조체
	WCHAR*			_fileName;		//파일 이름

public:
	image();
	~image();
	
	//================================================================== 
	//	                         이미지 초기화
	//================================================================== 

	//빈 비트맵 이미지 초기화
	HRESULT init(int width, int height);
	//파일로부터 이미지 초기화
	HRESULT init(LPCWSTR fileName, int width, int height);
	//파일로부터 이미지 초기화     처음 시작 좌표    가로       세로
	HRESULT init(LPCWSTR fileName, float x, float y, int width, int height);
	//이미지 + 프레임초기화
	HRESULT init(LPCWSTR fileName, int width, int height, int frameX, int frameY);
	HRESULT init(LPCWSTR fileName, float x, float y, int width, int height, int frameX, int frameY);


	//이미지 릴리즈
	void release(void);

	//=================================================================== 
	//	                           Render
	//=================================================================== 

	void render(float opacity);
	void render(float opacity, float destX, float destY, float angle = 0);
	void render(float opacity, float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight);

	void frameRender(float opacity, float destX, float destY, float angle = 0, float scale = 1);
	void frameRender(float opacity, float destX, float destY, int currentFrameX, int currentFrameY, float angle = 0.0f, float scale = 1);
	void frameAniRender(float opacity, float destX, float destY, int currentFrameX, int currentFrameY, float angle = 0.0f);
	void frameEffectRender(float opacity, float destX, float destY, int currentFrameX, int currentFrameY, float frameWidth, float frameHeight, float angle = 0.0f);

	//루프렌더    
	void loopRender(float opacity, const LPRECT drawArea, int offSetX, int offSetY);

	//애니메이션 렌더링 (뿌려줄 DC, 뿌려줄 위치 X, Y(left, top) 재생하고픈 애니메이션)
	void aniRender(float opacity, float destX, float destY, animation* ani, float angle = 0.0f);

	//이펙트 애니메이션 렌더링
	void aniEffectRender(float opacity, float destX, float destY, animation* ani, float angle = 0.0f);



	//==============================================
	// ## 이미지 사용 편의를 위한 접근자, 설정자
	//==============================================


	//이미지 뿌려주는 위치 X
	inline void setX(float x) { _imageInfo->x = x; }
	inline float getX(void) { return _imageInfo->x; }

	//이미지 뿌려주는 위치 Y
	inline void setY(float y) { _imageInfo->y = y; }
	inline float getY(void) { return _imageInfo->y; }

	//이미지를 중점좌표로 이동
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	inline float getCenterX(void)
	{
		return _imageInfo->maxFrameX <= 0 ? _imageInfo->x + (_imageInfo->width / 2) : _imageInfo->x + (_imageInfo->frameWidth / 2);
	}

	inline float getCenterY(void)
	{
		return _imageInfo->maxFrameY <= 0 ? _imageInfo->y + (_imageInfo->height / 2) : _imageInfo->y + (_imageInfo->frameHeight / 2);
	}

	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }

	//바운딩 박스
	inline RECT boundingBox(void)
	{
		RECT rc = { int(_imageInfo->x),
					int(_imageInfo->y),
					int(_imageInfo->x + _imageInfo->frameWidth),
					int(_imageInfo->y + _imageInfo->frameHeight) };

		return rc;
	}

	//프레임
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}

	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY) _imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }

	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

};

