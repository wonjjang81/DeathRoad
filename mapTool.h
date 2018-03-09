#pragma once
#include "gameNode.h"
#include "tile.h"
#include "button.h"

#include <vector>

static image* _currentMenu;

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

	//버튼
	int _btnScale;
	button* _btnTerrain;
	button* _btnBuiliding;
	button* _btnItems;
	button* _btnWeapon;
	button* _btnEnemy;
	button* _btnSetting;

	//메뉴




public:
	HRESULT init();
	void release();
	void update();
	void render();

	void gridRender(float scale = 1.0f);  	//타일 그리드맵 렌더
	void mapKeyControl();                   //맵 키 컨트롤
	void selectTile(int scale = 1.0f);      //타일 선택시 화면출력

	//버튼
	void btnSetup();
	void btnUpdate();
	void btnRender();

	//----------------- MENU -----------------
	static void menuTerrainSetup();  	//Terrain
	static void menuBuilidingSetup();  	//Buliding
	static void menuItemSetup();  		//Item
	static void menuWeaponSetup();  	//Weapon
	static void menuEnemySetup();  		//Enemy
	static void menuSettingSetup();  	//Setting

	void menuRender();
	



	mapTool();
	~mapTool();
};

