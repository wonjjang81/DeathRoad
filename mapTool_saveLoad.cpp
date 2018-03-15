#include "stdafx.h"
#include "mapTool.h"


//타일 저장
void mapTool::save()
{
	// 파일 저장을 위한 오픈파일네임
	OPENFILENAME ofn;
	char filePath[1024] = "";
	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = filePath;
	ofn.nMaxFile = sizeof(filePath);
	ofn.nFilterIndex = true;
	ofn.nMaxFileTitle = NULL;
	ofn.lpstrFileTitle = NULL;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrFilter = "Map File(*.map)\0*.map\0";		
	ofn.Flags = OFN_OVERWRITEPROMPT;

	//예외처리
	if (GetSaveFileName(&ofn) == false) return;

	string tempName;
	tempName.append(ofn.lpstrFile);
	tempName.append(".map");

	HANDLE hFile;
	hFile = CreateFile(tempName.c_str(), GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBoxA(0, "CreateFile Error", "", 0);
	}


	//========================================= 저장할 파일 불러오기 =========================================
	//-------------------------------------- 지형정보 벡터에서 가져오기 --------------------------------------
	//타일 사이즈 저장
	char tmpBuff[16];
	INIDATA->addData("mapData", "tileX", itoa(_tileX, tmpBuff, 10));
	INIDATA->addData("mapData", "tileY", itoa(_tileY, tmpBuff, 10));
	INIDATA->iniSave("deathRoad");

	//지형 사이즈 먼저 가져오기
	const int terrainSize = _tileX * _tileY;
	tagTile* ptSaveTileTr = new tagTile[terrainSize];

	//파일 저장을 위한 옮겨담기(형변환)
	for (int i = 0; i < _vSaveTr.size(); ++i)
	{
		 loadVectorTileData(_vSaveTr[i], ptSaveTileTr[i]);
	}

	//파일저장
	DWORD numOfByteWritten = 0;
	WriteFile(hFile, ptSaveTileTr, sizeof(tagTile) * terrainSize, &numOfByteWritten, NULL);
	//-------------------------------------- 빌딩정보 벡터에서 가져오기 --------------------------------------
	//벡터 사이즈 저장
	INIDATA->addData("mapData", "vBdSize", itoa(_vSaveBd.size(), tmpBuff, 10));
	INIDATA->iniSave("deathRoad");

	//빌딩 사이즈 먼저 가져오기
	tagTile* ptSaveTileBd = new tagTile[_vSaveBd.size()];

	//파일 저장을 위한 옮겨담기(형변환)
	for (int i = 0; i < _vSaveBd.size(); ++i)
	{
		loadVectorTileData(_vSaveBd[i], ptSaveTileBd[i]);
	}

	//파일저장
	WriteFile(hFile, ptSaveTileBd, sizeof(tagTile) * terrainSize, &numOfByteWritten, NULL);
	//========================================================================================================


	CloseHandle(hFile);
}

//타일 로드
void mapTool::load()
{
	// 파일 저장을 위한 오픈파일네임
	OPENFILENAME ofn;
	char filePath[1024] = "";
	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = filePath;
	ofn.nMaxFile = sizeof(filePath);
	ofn.nFilterIndex = true;
	ofn.nMaxFileTitle = NULL;
	ofn.lpstrFileTitle = NULL;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrFilter = "Map File(*.map)\0*.map\0";	
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	//예외처리
	if (GetSaveFileName(&ofn) == FALSE) return;

	//초기화
	SCENEMANAGER->changeScene("맵툴");

	string tempName;
	tempName.append(ofn.lpstrFile);

	HANDLE hFile;
	hFile = CreateFile(tempName.c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBoxA(0, "CreateFile Error", "", 0);
	}


	//========================================= 로드한 파일 저장하기 =========================================
	//----------------------------------------- 지형정보 벡터에 입력 -----------------------------------------
	//벡터크기 로드
	int tmpTileX = INIDATA->loadDataInterger("deathRoad", "mapData", "tileX");
	int tmpTileY = INIDATA->loadDataInterger("deathRoad", "mapData", "tileY");
	const int terrainSize = tmpTileX * tmpTileY;
	tagTile* ptTmpTileTr = new tagTile[terrainSize];

	//파일로드
	DWORD numOfByteWritten = 0;
	ReadFile(hFile, ptTmpTileTr, sizeof(tagTile) * terrainSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileTr, _vSaveTr, terrainSize);

	//----------------------------------------- 빌딩정보 벡터에 입력 -----------------------------------------
	//벡터크기 로드
	const int buildingSize = INIDATA->loadDataInterger("deathRoad", "mapData", "vBdSize");
	tagTile* ptTmpTileBd = new tagTile[buildingSize];

	//파일로드
	ReadFile(hFile, ptTmpTileBd, sizeof(tagTile) * buildingSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileBd, _vSaveBd, buildingSize);
	//========================================================================================================


	CloseHandle(hFile);
}


void mapTool::loadVectorTileData(tagTile setTile, tagTile& getTile)
{
	getTile.index     = setTile.index;
	getTile.attribute = setTile.attribute;
	getTile.tileType  = setTile.tileType;
	getTile.img		  = IMAGEMANAGER->findImage(setTile.imgName);
	sprintf(getTile.imgName, "%s", setTile.imgName);
	getTile.frameX    = setTile.frameX;
	getTile.frameY    = setTile.frameY;
	getTile.x		  = setTile.x;
	getTile.y		  = setTile.y;
	getTile.rc		  = setTile.rc;
	getTile.scale     = setTile.scale;
	getTile.gapX	  = setTile.gapX;
	getTile.gapY	  = setTile.gapY;
	getTile.moveX	  = setTile.moveX;
	getTile.moveY	  = setTile.moveY;
}

void mapTool::saveVectorTileData(tagTile* getTile, vSaveTile& vSaveTile, int tileSize)
{
	//수정사항: 벡터의 크기를 타일 사이즈에 따라서 생성

	for (int i = 0; i < tileSize; ++i)
	{
		if (getTile[i].img == NULL) continue;

		vSaveTile[i].index = getTile[i].index;
		vSaveTile[i].attribute = getTile[i].attribute;
		vSaveTile[i].tileType  = getTile[i].tileType;
		vSaveTile[i].img	   = IMAGEMANAGER->findImage(getTile[i].imgName);
		sprintf(vSaveTile[i].imgName, "%s", getTile[i].imgName);
		vSaveTile[i].frameX    = getTile[i].frameX;
		vSaveTile[i].frameY    = getTile[i].frameY;
		vSaveTile[i].x		   = getTile[i].x;
		vSaveTile[i].y		   = getTile[i].y;
		vSaveTile[i].rc		   = getTile[i].rc;
		vSaveTile[i].scale     = getTile[i].scale;
		vSaveTile[i].gapX	   = getTile[i].gapX;
		vSaveTile[i].gapY	   = getTile[i].gapY;
		vSaveTile[i].moveX	   = getTile[i].moveX;
		vSaveTile[i].moveY	   = getTile[i].moveY;
	}
}

