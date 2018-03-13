#pragma once
#include "gameNode.h"
#include "tile.h"
#include "button.h"
#include "fButton.h"

#include "sampleTile.h"
#include "tileFloor.h"
#include "tileStreet.h"
#include "tileBuildingA.h"
#include "tileBuildingF.h"

#include <vector>

#define TABMAXNUM 5

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

//------------ 전역화 ------------
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
	float _viewScale;
	vSampTile  _vTile;
	viSampTile _viTile;

	//========== 버튼 ==========
	//--------- 메뉴탭 ---------
	float _btnScale;
	button* _btnTerrain;
	button* _btnBuiliding;
	button* _btnItems;
	button* _btnWeapon;
	button* _btnEnemy;
	button* _btnSetting;

	fButton* _btnArrowL;
	fButton* _btnArrowR;
	int _btnTabNum;  //현재 탭넘버
	int _preTabNum;  //이전 탭넘버
	//-------- 타일리셋 --------
	//버튼
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
	//리셋
	bool isAResetOn;
	bool isTResetOn;

	//-------- Edit버튼 --------
	fButton* _btnAllReset;   //버튼 초기화

	fButton* _btnEraser;    //타일 초기화
	fButton* _btnOneEraser; //타일 초기화(하나만)
	fButton* _btnAllEraser; //타일 초기화(전체)
	fButton* _btnAllSet;    //타일 셋팅(전체)
	//==========================

	//======== 샘플타일 ========
	sampleTile* _tileFloor;
	sampleTile* _tileStreet;
	sampleTile* _tileBuilding1;
	sampleTile* _tileBuilding2;
	sampleTile* _tileFurniture1;
	//==========================

	//===== 타일 draw & save =====
	//---------- Terrain ---------
	tagTile    _drawTile;
	bool       _menuTabOn;  //메뉴탭 활성화 여부
	vSaveTile  _vSaveTr;
	viSaveTile _viSaveTr;
	//---------- Building --------
	vSaveTile  _vSaveBd;
	viSaveTile _viSaveBd;

	//============================


public:
	HRESULT init();
	void release();
	void update();
	void render();

	void gridRender(float scale = 1.0f);  	//타일 그리드맵 렌더
	void mapKeyControl();                   //맵 키 컨트롤
	void selectTile(float scale = 1.0f);    //타일 선택시 화면출력

	//버튼
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
	void menuTabArrowAction();          //탭 화살표 버튼 카운팅
	void menuTerrainTileChange(int num);       //지형 타일교체
	void menuBuildingTileChange(int num);      //빌딩 타일교체
	//--------------------- Reset --------------------
	void tileReAtrribute(tagTile& resetTile);  	//Attribute Reset
	void tileReType(tagTile& resetTile);  		//TileType  Reset
	//------------------ Edit Button -----------------
	void btnAllReset();
	void btnTile1Eraser(tagTile& resetTile);
	void btnTileAllEraser();
	void btnTileAllSet(tagTile& resetTile);
	//------------------------------------------------
	void menuRender();
	void menuUpdate();
	void menuAddChild();
	void btnSwitch();
	//================================================

	
	
	//타일 그리기
	void tileDraw(float scale);



	mapTool();
	~mapTool();
};

