#pragma once
#include "gameNode.h"
#include "tile.h"
#include "button.h"

#include <vector>


class mapTool : public gameNode
{
private:
	typedef vector<RECT>			vD2Rect;
	typedef vector<RECT>::iterator  viD2Rect;

private:
	//editWindow
	image * _editWindow;

	//keyControl
	float _moveX, _moveY;
	float _moveSpeed;

	//grid
	float _showWindowX, _showWindowY;
	int   _viewScale;
	vD2Rect  _vTileRect;
	viD2Rect _viTileRect;

	//��ư
	int _btnScale;
	button* _btnTerrain;
	button* _btnBuliding;
	button* _btnItems;
	button* _btnWeapon;
	button* _btnEnemy;
	button* _btnSetting;




public:
	HRESULT init();
	void release();
	void update();
	void render();

	void gridRender(float scale = 1.0f);  	//Ÿ�� �׸���� ����
	void mapKeyControl();                   //�� Ű ��Ʈ��
	void selectTile(int scale = 1.0f);      //Ÿ�� ���ý� ȭ�����

	//��ư
	void btnSetup();
	void btnUpdate();
	void btnRender();

	//----------------- MENU -----------------
	//Terrain
	static void menuTrSetup();



	mapTool();
	~mapTool();
};

