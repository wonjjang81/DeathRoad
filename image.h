#pragma once
#include "animation.h"
//============================================
// ## 17.11.24 ## - image Class - ##
//============================================

class image
{
public:

	//�̹��� �ҷ����� Ÿ��
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,		//���ҽ��κ���
		LOAD_FILE,			//���Ϸκ���
		LOAD_EMPTY,			//�� ��Ʈ�����κ���
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		DWORD					resID;							
		IWICImagingFactory*		pWICImagingFactory;		//Windows Imagind Component�� ���� Factory �������̽�
		IWICFormatConverter*    pWICFormatConverter;	//Format Converter
		IWICBitmapDecoder*      pWICDecoder;			//Bitmap Decoder
		IWICBitmapFrameDecode*  pWICFrameDecoder;       //������ Decoder �������̽�
		ID2D1Bitmap*			pBitmap;                //D2D�� ��Ʈ��
		float                   x, y;                   //�̹��� ��ġ
		float					width;					//���� ũ��(�̹���)
		float					height;					//���� ũ��(�̹���)
		int						currentFrameX;			//���� ������ X
		int						currentFrameY;			//���� ������ Y
		int						maxFrameX;				//�ִ� ������ X
		int						maxFrameY;				//�ִ� ������ Y
		float					frameWidth;				//������ ����ũ��
		float					frameHeight;			//������ ����ũ��
		BYTE					loadType;				//�̹��� �ҷ��� Ÿ��
		RECT					boundingBox;			//�ٿ�� �ڽ�(�浹üũ�� �ڽ�)

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
	LPIMAGE_INFO	_imageInfo;		//�̹��� ���� ����ü
	WCHAR*			_fileName;		//���� �̸�

public:
	image();
	~image();
	
	//================================================================== 
	//	                         �̹��� �ʱ�ȭ
	//================================================================== 

	//�� ��Ʈ�� �̹��� �ʱ�ȭ
	HRESULT init(int width, int height);
	//���Ϸκ��� �̹��� �ʱ�ȭ
	HRESULT init(LPCWSTR fileName, int width, int height);
	//���Ϸκ��� �̹��� �ʱ�ȭ     ó�� ���� ��ǥ    ����       ����
	HRESULT init(LPCWSTR fileName, float x, float y, int width, int height);
	//�̹��� + �������ʱ�ȭ
	HRESULT init(LPCWSTR fileName, int width, int height, int frameX, int frameY);
	HRESULT init(LPCWSTR fileName, float x, float y, int width, int height, int frameX, int frameY);


	//�̹��� ������
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

	//��������    
	void loopRender(float opacity, const LPRECT drawArea, int offSetX, int offSetY);

	//�ִϸ��̼� ������ (�ѷ��� DC, �ѷ��� ��ġ X, Y(left, top) ����ϰ��� �ִϸ��̼�)
	void aniRender(float opacity, float destX, float destY, animation* ani, float angle = 0.0f);

	//����Ʈ �ִϸ��̼� ������
	void aniEffectRender(float opacity, float destX, float destY, animation* ani, float angle = 0.0f);



	//==============================================
	// ## �̹��� ��� ���Ǹ� ���� ������, ������
	//==============================================


	//�̹��� �ѷ��ִ� ��ġ X
	inline void setX(float x) { _imageInfo->x = x; }
	inline float getX(void) { return _imageInfo->x; }

	//�̹��� �ѷ��ִ� ��ġ Y
	inline void setY(float y) { _imageInfo->y = y; }
	inline float getY(void) { return _imageInfo->y; }

	//�̹����� ������ǥ�� �̵�
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

	//�ٿ�� �ڽ�
	inline RECT boundingBox(void)
	{
		RECT rc = { int(_imageInfo->x),
					int(_imageInfo->y),
					int(_imageInfo->x + _imageInfo->frameWidth),
					int(_imageInfo->y + _imageInfo->frameHeight) };

		return rc;
	}

	//������
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

