#pragma once
#include "singletonBase.h"


class cameraManager : public singletonBase<cameraManager>
{
public:
	typedef struct tagCameraInfo
	{
		ID2D1Factory*			pD2DCameraFactory;
		ID2D1HwndRenderTarget*	pCameraRenderTarget;
		ID2D1HwndRenderTarget*	pOCameraRenderTarget;

		float	x;										//카메라 X좌표 (left)
		float	y;										//카메라 Y좌표 (top)
		int		showWidth;								//가로 크기(카메라)
		int		showHeight;								//세로 크기(카메라)
		int		totalWidth;								//배경 총 가로크기
		int		totalHeight;							//배경 총 세로크기
		float	magnification;							//카메라 확대


		tagCameraInfo()
		{
			pD2DCameraFactory = nullptr;
			pCameraRenderTarget = nullptr;
			x = 0.0f;
			y = 0.0f;
			showWidth = 0;
			showHeight = 0;
			totalWidth = 0;
			totalHeight = 0;
			magnification = 1.0f;
		}
	}CAMERAINFO, *LPCAMERA_INFO;


private:
	LPCAMERA_INFO _cameraInfo;		//카메라 정보 구조체


public:
	HRESULT init(int totalWidth, int totalHeight, int showWidth, int showHeight, float x, float y, float magnification);
	void release();
	void cameraMove(float focusX, float focusY);
	void render(ID2D1HwndRenderTarget* renderTarget);



	cameraManager();
	~cameraManager();
};

