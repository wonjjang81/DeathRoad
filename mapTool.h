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

	//타일 갯수
	int _tileX, _tileY;

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
	fButton* _btnAllReset;		//버튼 초기화

	fButton* _btnEraser;		//타일 초기화
	fButton* _btnOneEraser;		//타일 초기화(하나만)
	fButton* _btnAllEraser;		//타일 초기화(전체)
	fButton* _btnAllSet;		//타일 셋팅(전체)

	int      _tmpSelectIndex;   //선택한 벡터 지울 인덱스 담을 변수
	//------ SaveLoad버튼 ------
	fButton* _btnSave;
	fButton* _btnLoad;
	bool     _isSetBtnOn;

	fButton* _btnExit;
	//==========================

	//======== 샘플타일 ========
	//지형
	sampleTile* _tileFloor;
	//도로
	sampleTile* _tileTree1;
	sampleTile* _tileStreet;
	//빌딩
	sampleTile* _tileWall;
	sampleTile* _tileBuilding1;
	sampleTile* _tileBuilding2;
	sampleTile* _tileDoor;
	//빌딩: 가구
	sampleTile* _tileFurniture1;
	sampleTile* _tileShelves;
	//아이템
	sampleTile* _tileItem1;
	//무기
	sampleTile* _tileWeapon1;
	//==========================

	//===== 타일 draw & save =====
	//---------- Terrain ---------
	tagTile    _drawTile;
	bool       _menuTabOn;  //메뉴탭 활성화 여부
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
	//타일 사이즈 입력
	HWND _hDlgNewTile;
	fButton* _btnNewTile;
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
	void sTileInputItem(int num);
	void sTileInputWeapon(int num);
	void menuTabArrowAction();             //탭 화살표 버튼 카운팅
	void menuTerrainTileChange(int num);   //지형   타일교체
	void menuBuildingTileChange(int num);  //빌딩   타일교체
	void menuItemTileChange(int num);	   //아이템 타일교체
	void menuWeaponTileChange(int num);    //무기   타일교체 
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

	//타일정보 저장
	void saveTileVector(vSaveTile& tileVector);
	//샘플타일 FillRect 초기화
	void samTileFRectInitialize();
	
	//타일 그리기
	void gridVectorDraw(int tileX, int tileY);
	void tileDraw(float scale);
	void vTileDraw(vSaveTile tileVector, float scale);


	//저장, 불러오기
	void save();
	void load();
	void loadVectorTileData(tagTile setTile, tagTile& getTile);
	void saveVectorTileData(tagTile* getTile, vSaveTile& vSaveTile, int tileSize);

	//타일생성(사이즈 입력)
	void newTileMap();					   //입력한 사이즈의 그리드 타일 생성
	void createDefaultMap(POINT mapSize);  //타일 사이즈 입력
	void vTileClear();

	//=========================== getter & setter ===========================
	inline void setHandleNewTile(HWND handle) { _hDlgNewTile = handle; }  //다이얼로그 박스 get
	inline HWND getHandleNewTile(void) { return _hDlgNewTile; }           //다이얼로그 박스 set


	mapTool();
	~mapTool();
};

