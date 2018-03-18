#pragma once
#include "gameNode.h"
#include "tile.h"
#include "button.h"
#include "fButton.h"
#include "Resource1.h"

#include "sampleTile.h"
#include "tileFloor.h"
#include "tileStreet.h"
#include "tileBuildingA.h"
#include "tileBuildingF.h"

#include <vector>
#include <commdlg.h>


#define TABMAXNUM 10

enum MENU_TYPE
{
	MENU_NONE,
	MENU_TERRAIN,
	MENU_BULIDING,
	MENU_ITEM,
	MENU_WEAPON,
	MENU_ENEMY,
	MENU_SETTING
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
	typedef vector<tagTile>::iterator		   viSaveTile;

private:
	//editWindow
	image* _editWindow;

	//keyControl
	float _moveX, _moveY;
	float _moveSpeed;

	//grid
	float _showWindowX, _showWindowY;
	float _viewScale;
	vSampTile  _vTile;
	viSampTile _viTile;

	//Ÿ�� ����
	int _tileX, _tileY;

	//========== ��ư ==========
	//--------- �޴��� ---------
	float _btnScale;
	button* _btnTerrain;
	button* _btnBuiliding;
	button* _btnItems;
	button* _btnWeapon;
	button* _btnEnemy;
	button* _btnSetting;

	fButton* _btnArrowL;
	fButton* _btnArrowR;
	int _btnTabNum;  //���� �ǳѹ�
	int _preTabNum;  //���� �ǳѹ�
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

	//-------- Edit��ư --------
	fButton* _btnAllReset;		//��ư �ʱ�ȭ

	fButton* _btnEraser;		//Ÿ�� �ʱ�ȭ
	fButton* _btnOneEraser;		//Ÿ�� �ʱ�ȭ(�ϳ���)
	fButton* _btnAllEraser;		//Ÿ�� �ʱ�ȭ(��ü)
	fButton* _btnAllSet;		//Ÿ�� ����(��ü)

	int      _tmpSelectIndex;   //������ ���� ���� �ε��� ���� ����
	//------ SaveLoad��ư ------
	fButton* _btnSave;
	fButton* _btnLoad;
	bool     _isSetBtnOn;

	fButton* _btnExit;
	//==========================

	//======== ����Ÿ�� ========
	//����
	sampleTile* _tileFloor;
	//����
	sampleTile* _tileTree1;
	sampleTile* _tileStreet;
	//����
	sampleTile* _tileWall;
	sampleTile* _tileBuilding1;
	sampleTile* _tileBuilding2;
	sampleTile* _tileDoor;
	//����: ����
	sampleTile* _tileFurniture1;
	sampleTile* _tileShelves;
	//������
	sampleTile* _tileItem1;
	//����
	sampleTile* _tileWeapon1;
	//==========================

	//===== Ÿ�� draw & save =====
	//---------- Terrain ---------
	tagTile    _drawTile;
	bool       _menuTabOn;  //�޴��� Ȱ��ȭ ����
	vSaveTile  _vSaveTr;
	viSaveTile _viSaveTr;
	//----------- PUBLIC ---------
	bool       _isSaveVector;
	tagTile    _tmpSaveTile;
	//---------- Building --------
	vSaveTile  _vSaveBd;
	viSaveTile _viSaveBd;
	//------------ Road ----------
	vSaveTile  _vSaveRd;
	viSaveTile _viSaveRd;
	//---------- Furniture -------
	vSaveTile  _vSaveFt;
	viSaveTile _viSaveFt;
	//------------ Item ----------
	vSaveTile  _vSaveIt;
	viSaveTile _viSaveIt;
	//----------- Weapon ---------
	vSaveTile  _vSaveWp;
	viSaveTile _viSaveWp;
	//----------- Enemy ----------
	vSaveTile  _vSaveEm;
	viSaveTile _viSaveEm;
	//============================



	//========= NewTile ==========
	//Ÿ�� ������ �Է�
	HWND _hDlgNewTile;
	fButton* _btnNewTile;
	//============================


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

	void selectTileInput(sampleTile* selectTile);
	void sTileInputTerrain(int num);
	void sTileInputBuilding(int num);
	void sTileInputItem(int num);
	void sTileInputWeapon(int num);
	void menuTabArrowAction();             //�� ȭ��ǥ ��ư ī����
	void menuTerrainTileChange(int num);   //����   Ÿ�ϱ�ü
	void menuBuildingTileChange(int num);  //����   Ÿ�ϱ�ü
	void menuItemTileChange(int num);	   //������ Ÿ�ϱ�ü
	void menuWeaponTileChange(int num);    //����   Ÿ�ϱ�ü 
	//--------------------- Reset --------------------
	void tileReAtrribute(tagTile& resetTile);  	//Attribute Reset
	void tileReType(tagTile& resetTile);  		//TileType  Reset
	//------------------ Edit Button -----------------
	void btnAllReset();
	void setTile1Eraser(vSaveTile& eraseTile, int tsIndex);
	void btnTile1Eraser(tagTile& resetTile);
	void btnTileAllEraser();
	void btnTileAllSet(tagTile& resetTile);

	void vTileInitialize(vSaveTile& saveTile);
	void vTileSet(vSaveTile& saveTile, tagTile& resetTile);
	int getTileIndex(vSaveTile& vTile, int tsIndex);
	//------------------------------------------------
	void menuRender();
	void menuUpdate();
	void menuAddChild();
	void btnSwitch();
	//================================================

	//Ÿ������ ����
	void saveTileVector(vSaveTile& tileVector);
	//����Ÿ�� FillRect �ʱ�ȭ
	void samTileFRectInitialize();
	
	//Ÿ�� �׸���
	void gridVectorDraw(int tileX, int tileY);
	void tileDraw(float scale);
	void vTileDraw(vSaveTile tileVector, float scale);


	//����, �ҷ�����
	void save();
	void load();
	void loadVectorTileData(tagTile setTile, tagTile& getTile);
	void saveVectorTileData(tagTile* getTile, vSaveTile& vSaveTile, int tileSize);

	//Ÿ�ϻ���(������ �Է�)
	void newTileMap();					   //�Է��� �������� �׸��� Ÿ�� ����
	void createDefaultMap(POINT mapSize);  //Ÿ�� ������ �Է�
	void vTileClear();

	//=========================== getter & setter ===========================
	inline void setHandleNewTile(HWND handle) { _hDlgNewTile = handle; }  //���̾�α� �ڽ� get
	inline HWND getHandleNewTile(void) { return _hDlgNewTile; }           //���̾�α� �ڽ� set


	mapTool();
	~mapTool();
};

