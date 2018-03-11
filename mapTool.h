#pragma once
#include "gameNode.h"
#include "tile.h"
#include "button.h"
#include "fButton.h"

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

//------------ ����ȭ ------------
static struct tagMenu
{
	image*		imgTab;
	image*		imgTile;
	MENU_TYPE	menuType;
	bool        typeChange;
}_menuTab;

//-------------------------------



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

	//========== ��ư ==========
	//--------- �޴��� ---------
	int _btnScale;
	button* _btnTerrain;
	button* _btnBuiliding;
	button* _btnItems;
	button* _btnWeapon;
	button* _btnEnemy;
	button* _btnSetting;

	//-------- Ÿ�ϸ��� --------
	//��ư
	fButton* _btnAttribute;
	fButton* _btnA_move;
	fButton* _btnA_unMove;
	fButton* _btnA_ARender;

	fButton* _btnTileType;
	fButton* _btnT_terrain;
	fButton* _btnT_building;
	fButton* _btnT_item;
	fButton* _btnT_weapon;
	fButton* _btnT_enemy;

	float	_btnRCenterX;
	float   _btnRCenterY;
	float   _btnImgReWidth;
	float   _btnImgReHeight;
	//����
	bool isAResetOn;
	bool isTResetOn;
	//==========================

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
	void selectTile(float scale = 1.0f);    //Ÿ�� ���ý� ȭ�����

	//��ư
	void btnSetup();
	void btnUpdate();
	void btnRender();

	//==================== BUTTON ====================
	//--------------------- MENU ---------------------
	static void menuTerrainSetup();  	//Terrain
	static void menuBuilidingSetup();  	//Buliding
	static void menuItemSetup();  		//Item
	static void menuWeaponSetup();  	//Weapon
	static void menuEnemySetup();  		//Enemy
	static void menuSettingSetup();  	//Setting
	//--------------------- Reset --------------------
	void tileReAtrribute(tagTile& resetTile);  	//Attribute Reset
	void tileReType(tagTile resetTile);  		//TileType  Reset
	//------------------------------------------------
	void menuRender();
	void menuAddChild();
	void btnSwitch();
	void btnSwitch1(fButton* btn, fButton* offBtn);
	//================================================

	
	
	//Ÿ�� �׸���
	void tileDraw(float scale);



	mapTool();
	~mapTool();
};

