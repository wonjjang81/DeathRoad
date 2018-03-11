#pragma once
#include "gameNode.h"
#include "tile.h"
#include "button.h"

#include "mapTool_menu_terrain.h"

#include <vector>

enum MENU_TYPE
{
	MENU_TERRAIN,
	MENU_BULIDING,
	MENU_ITEM,
	MENU_WEAPON,
	MENU_ENEMY,
	MENU_SETTING,
	MENU_NONE
};

static struct tagMenu
{
	image*		imgTab;
	image*		imgTile;
	MENU_TYPE	menuType;
	bool        typeChange;
}_menuTab;



class mapTool : public gameNode
{
private:
	typedef vector<tagSampleTile>			   vSampTile;
	typedef vector<tagSampleTile>::iterator    viSampTile;

	typedef vector<tagTile>					   vSaveTile;
	typedef vector<tagTile>::iterator          viSaveTile;

private:
	//editWindow
	image* _editWindow;

	//keyControl
	float _moveX, _moveY;
	float _moveSpeed;

	//grid
	float _showWindowX, _showWindowY;
	int   _viewScale;
	vSampTile  _vTile;
	viSampTile _viTile;

	//��ư
	int _btnScale;
	button* _btnTerrain;
	button* _btnBuiliding;
	button* _btnItems;
	button* _btnWeapon;
	button* _btnEnemy;
	button* _btnSetting;

	//�޴�
	mapTool_menu_terrain* _menuTr;

	//Ÿ�� draw & save
	tagTile    _drawTile;
	bool       _menuTabOn;  //�޴��� Ȱ��ȭ ����
	vSaveTile  _vSaveTr;
	viSaveTile _viSaveTr;



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

	//------------------- MENU -------------------
	static void menuTerrainSetup();  	//Terrain
	static void menuBuilidingSetup();  	//Buliding
	static void menuItemSetup();  		//Item
	static void menuWeaponSetup();  	//Weapon
	static void menuEnemySetup();  		//Enemy
	static void menuSettingSetup();  	//Setting

	void menuRender();
	void menuAddChild();
	//------------------- MENU -------------------

	//Ÿ�� �׸���
	void tileDraw(float scale);



	mapTool();
	~mapTool();
};

