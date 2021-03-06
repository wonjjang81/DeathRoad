#include "stdafx.h"
#include "mapLoad.h"
#include "tileDataInfo.h"


mapLoad::mapLoad()
{
}
mapLoad::~mapLoad()
{
}


void mapLoad::loadMap(string fileName)
{
	//========================================= 로드한 파일 저장하기 =========================================
	//----------------------------------------- 지형정보 벡터에 입력 -----------------------------------------
	//----------------- 파일저장명 가져오기 -----------------

	char str[256];
	GetCurrentDirectory(256, str);   //현재 디렉토리 경로
	string tmpFileName;
	tmpFileName.append(str);         //파일경로
	tmpFileName.append("\\map\\");   //파일경로
	tmpFileName.append(fileName);    //파일명
	tmpFileName.append(".map");      //확장자
	

	HANDLE hFile;
	hFile = CreateFile(tmpFileName.c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBoxA(0, "CreateFile Error", "", 0);
	}

	//벡터 초기화
	//vTileClear();

	tmpFileName.clear();
	tmpFileName.append("map//");
	tmpFileName.append(fileName);


	//벡터크기 로드
	const int trSize = INIDATA->loadDataInterger(tmpFileName.c_str(), "mapData", "vTrSize");

	tagTile* ptTmpTileTr = new tagTile[trSize];

	//파일로드
	DWORD numOfByteWritten = 0;
	ReadFile(hFile, ptTmpTileTr, sizeof(tagTile) * trSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileTr, _vSaveTr, trSize);

	//----------------------------------------- 빌딩정보 벡터에 입력 -----------------------------------------
	//벡터크기 로드
	const int bdSize = INIDATA->loadDataInterger(tmpFileName.c_str(), "mapData", "vBdSize");
	tagTile* ptTmpTileBd = new tagTile[bdSize];

	//파일로드
	ReadFile(hFile, ptTmpTileBd, sizeof(tagTile) * bdSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileBd, _vSaveBd, bdSize);

	//----------------------------------------- 도로정보 벡터에 입력 -----------------------------------------
	//벡터크기 로드
	const int rdSize = INIDATA->loadDataInterger(tmpFileName.c_str(), "mapData", "vRdSize");
	tagTile* ptTmpTileRd = new tagTile[rdSize];

	//파일로드
	ReadFile(hFile, ptTmpTileBd, sizeof(tagTile) * rdSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileRd, _vSaveRd, rdSize);

	//----------------------------------------- 가구정보 벡터에 입력 -----------------------------------------
	//벡터크기 로드
	const int ftSize = INIDATA->loadDataInterger(tmpFileName.c_str(), "mapData", "vFtSize");
	tagTile* ptTmpTileFt = new tagTile[ftSize];

	//파일로드
	ReadFile(hFile, ptTmpTileFt, sizeof(tagTile) * ftSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileFt, _vSaveFt, ftSize);

	//---------------------------------------- 아이템정보 벡터에 입력 ----------------------------------------
	//벡터크기 로드
	const int itSize = INIDATA->loadDataInterger(tmpFileName.c_str(), "mapData", "vItSize");
	tagTile* ptTmpTileIt = new tagTile[itSize];

	//파일로드
	ReadFile(hFile, ptTmpTileIt, sizeof(tagTile) * itSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileIt, _vSaveIt, itSize);

	//----------------------------------------- 무기정보 벡터에 입력 ----------------------------------------
	//벡터크기 로드
	const int wpSize = INIDATA->loadDataInterger(tmpFileName.c_str(), "mapData", "vWpSize");
	tagTile* ptTmpTileWp = new tagTile[wpSize];

	//파일로드
	ReadFile(hFile, ptTmpTileWp, sizeof(tagTile) * wpSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileWp, _vSaveWp, wpSize);

	//------------------------------------------ 적정보 벡터에 입력 -----------------------------------------
	//벡터크기 로드
	const int emSize = INIDATA->loadDataInterger(tmpFileName.c_str(), "mapData", "vEmSize");
	tagTile* ptTmpTileEm = new tagTile[emSize];

	//파일로드
	ReadFile(hFile, ptTmpTileEm, sizeof(tagTile) * emSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileEm, _vSaveEm, emSize);

	//------------------------------------------ 벽정보 벡터에 입력 -----------------------------------------
	//벡터크기 로드
	const int wlSize = INIDATA->loadDataInterger(tmpFileName.c_str(), "mapData", "vWlSize");
	tagTile* ptTmpTileWl = new tagTile[wlSize];

	//파일로드
	ReadFile(hFile, ptTmpTileWl, sizeof(tagTile) * wlSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileWl, _vSaveWl, wlSize);

	//------------------------------------------ 문정보 벡터에 입력 -----------------------------------------
	//벡터크기 로드
	const int drSize = INIDATA->loadDataInterger(tmpFileName.c_str(), "mapData", "vDrSize");
	tagTile* ptTmpTileDr = new tagTile[drSize];

	//파일로드
	ReadFile(hFile, ptTmpTileDr, sizeof(tagTile) * drSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileDr, _vSaveDr, drSize);

	//----------------------------------------- AR벽정보 벡터에 입력 ----------------------------------------
	//벡터크기 로드
	const int arWlSize = INIDATA->loadDataInterger(tmpFileName.c_str(), "mapData", "vArWlSize");
	tagTile* ptTmpTileArWl = new tagTile[arWlSize];

	//파일로드
	ReadFile(hFile, ptTmpTileArWl, sizeof(tagTile) * arWlSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileArWl, _vSaveArWl, arWlSize);
	//========================================================================================================


	CloseHandle(hFile);

	//Start Point
	for (int i = 0; i < _vSaveTr.size(); ++i)
	{
		if (_vSaveTr[i].typeAtt == TYPE_A_TR_START)
		{
			_startPoint.x =  _vSaveTr[i].x - TILE_SIZEX / 3;
			_startPoint.y =  _vSaveTr[i].y - TILE_SIZEY / 2;
		}
	}
}


void mapLoad::saveVectorTileData(tagTile* getTile, vSaveTile& vSaveTile, int tileSize)
{
	//수정사항: 벡터의 크기를 타일 사이즈에 따라서 생성
	tagTile tmpTile;
	ZeroMemory(&tmpTile, sizeof(tagTile));


	for (int i = 0; i < tileSize; ++i)
	{
		vSaveTile.push_back(tmpTile);
	}

	if (tileSize == 0)
	{
		ZeroMemory(&vSaveTile, sizeof(vSaveTile));
	}


	for (int i = 0; i < tileSize; ++i)
	{
		if (getTile[i].img == NULL) continue;

		vSaveTile[i].id = getTile[i].id;
		vSaveTile[i].index = getTile[i].index;
		vSaveTile[i].attribute = getTile[i].attribute;
		vSaveTile[i].tileType = getTile[i].tileType;
		vSaveTile[i].typeAtt = getTile[i].typeAtt;
		vSaveTile[i].typeAtt2 = getTile[i].typeAtt2;
		vSaveTile[i].anchorType = getTile[i].anchorType;
		vSaveTile[i].overPos = getTile[i].overPos;
		vSaveTile[i].img = IMAGEMANAGER->findImage(getTile[i].imgName);
		sprintf(vSaveTile[i].imgName, "%s", getTile[i].imgName);
		vSaveTile[i].frameX = getTile[i].frameX;
		vSaveTile[i].frameY = getTile[i].frameY;
		vSaveTile[i].x = getTile[i].rc.left;
		vSaveTile[i].y = getTile[i].rc.top;

		vSaveTile[i].rc = getTile[i].rc;
		revisonRect(vSaveTile[i].typeAtt, vSaveTile[i].rc);

		vSaveTile[i].scale = getTile[i].scale;
		vSaveTile[i].gapX = getTile[i].gapX;
		vSaveTile[i].gapY = getTile[i].gapY;
		vSaveTile[i].moveX = getTile[i].moveX;
		vSaveTile[i].moveY = getTile[i].moveY;
		vSaveTile[i].centerX = getTile[i].centerX;
		vSaveTile[i].centerY = getTile[i].centerY;

		vSaveTile[i].gridIndex = getTile[i].gridIndex;
		vSaveTile[i].actionValue = getTile[i].actionValue;
		vSaveTile[i].direction = getTile[i].direction;
	}
}


void mapLoad::revisonRect(TYPE_ATTRIBUTE typeAtt, RECT& rc)
{
	switch (typeAtt)
	{
		case TYPE_A_NONE:
			ZeroMemory(&rc, sizeof(RECT));
		break;
		case TYPE_A_TR_START:
			ZeroMemory(&rc, sizeof(RECT));
		break;
		case TYPE_A_WL_EMPTY:
			ZeroMemory(&rc, sizeof(RECT));
		break;
		case TYPE_A_WL_CENTER:
			rectResize(rc, 4, 0, 4, 0);
		break;
		case TYPE_A_WL_ORIGINAL:
	
		break;
		case TYPE_A_WP_GUN:
			rectResize(rc, 4, 0, 4, 0);
		break;
		case TYPE_A_WP_BOMB:
			rectResize(rc, 4, 0, 4, 0);
		break;
		case TYPE_A_WP_SWORD:
			rectResize(rc, 4, 0, 4, 0);
		break;
		case TYPE_A_WP_MACHINE:
			rectResize(rc, 4, 0, 4, 0);
		break;
		case TYPE_A_DR_NONE:
			ZeroMemory(&rc, sizeof(RECT));
		break;
		case TYPE_A_DR_ORIGINAL:
		
		break;
		case TYPE_A_DR_CENTER:
			rectResize(rc, 4, 0, 4, 0);
		break;
	}
}


void mapLoad::rectResize(RECT& rc, float left, float top, float right, float bottom)
{
	RECT tmpRc;
	tmpRc.left   = rc.left   + left;
	tmpRc.top    = rc.top    + top;
	tmpRc.right  = rc.right  - right;
	tmpRc.bottom = rc.bottom - bottom;

	rc = tmpRc;
}