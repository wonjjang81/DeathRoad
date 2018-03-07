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

		float	x;										//ī�޶� X��ǥ (left)
		float	y;										//ī�޶� Y��ǥ (top)
		int		showWidth;								//���� ũ��(ī�޶�)
		int		showHeight;								//���� ũ��(ī�޶�)
		int		totalWidth;								//��� �� ����ũ��
		int		totalHeight;							//��� �� ����ũ��
		float	magnification;							//ī�޶� Ȯ��


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
	LPCAMERA_INFO _cameraInfo;		//ī�޶� ���� ����ü


public:
	HRESULT init(int totalWidth, int totalHeight, int showWidth, int showHeight, float x, float y, float magnification);
	void release();
	void cameraMove(float focusX, float focusY);
	void render(ID2D1HwndRenderTarget* renderTarget);



	cameraManager();
	~cameraManager();
};

