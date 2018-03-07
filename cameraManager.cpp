#include "stdafx.h"
#include "cameraManager.h"


cameraManager::cameraManager()
{
}
cameraManager::~cameraManager()
{
}


HRESULT cameraManager::init(int totalWidth, int totalHeight, int showWidth, int showHeight, float x, float y, float magnification)
{
	if (_cameraInfo != NULL) release();

	HRESULT hr = E_FAIL;

	_cameraInfo = new CAMERAINFO;
	_cameraInfo->pD2DCameraFactory		= D2DMANAGER->pD2DFactory;
	_cameraInfo->pCameraRenderTarget	= nullptr;
	_cameraInfo->pOCameraRenderTarget	= nullptr;
	_cameraInfo->showWidth				= showWidth / magnification;
	_cameraInfo->showHeight				= showHeight / magnification;
	_cameraInfo->totalWidth				= totalWidth;
	_cameraInfo->totalHeight			= totalHeight;
	_cameraInfo->magnification			= magnification;

	//---------------------------------------------------------------------------
	//	Hwnd Render Target 생성
	//---------------------------------------------------------------------------
	hr = _cameraInfo->pD2DCameraFactory->CreateHwndRenderTarget(RenderTargetProperties(),
		HwndRenderTargetProperties(_hWnd, SizeU(totalWidth, totalHeight)), &_cameraInfo->pCameraRenderTarget);
	assert(hr == S_OK);

	_cameraInfo->pOCameraRenderTarget = _cameraInfo->pCameraRenderTarget;


	//if (_cameraInfo->pCameraRenderTarget == nullptr)
	//{
	//	this->release();

	//	return E_FAIL;
	//}

	//COM 라이브러리 초기화
	CoInitialize(NULL);

	return S_OK;
}

void cameraManager::release()
{
	if (_cameraInfo)
	{
		SAFE_RELEASE_D2D(_cameraInfo->pCameraRenderTarget);
		SAFE_RELEASE_D2D(_cameraInfo->pOCameraRenderTarget);
		SAFE_RELEASE_D2D(_cameraInfo->pD2DCameraFactory);

		SAFE_DELETE(_cameraInfo)
	}
}

void cameraManager::cameraMove(float focusX, float focusY)
{
	_cameraInfo->x = focusX - _cameraInfo->showWidth / 2;
	_cameraInfo->y = focusY - _cameraInfo->showHeight / 2;

	if (_cameraInfo->x < 0)														_cameraInfo->x = 0;
	if (_cameraInfo->x + _cameraInfo->showWidth > _cameraInfo->totalWidth)		_cameraInfo->x = _cameraInfo->totalWidth - _cameraInfo->showWidth;

	if (_cameraInfo->y < 0)														_cameraInfo->y = 0;
	if (_cameraInfo->y + _cameraInfo->showHeight > _cameraInfo->totalHeight)	_cameraInfo->y = _cameraInfo->totalHeight - _cameraInfo->showHeight;
}

void cameraManager::render(ID2D1HwndRenderTarget* renderTarget)
{
	//_cameraInfo->pCameraRenderTarget->CreateCompatibleRenderTarget(D2D1::SizeF(_cameraInfo->showWidth, _cameraInfo->showHeight), );
}