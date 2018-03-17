#include "stdafx.h"
#include "mapTool.h"


//타일 저장
void mapTool::save()
{
	// 파일 저장을 위한 오픈파일네임
	OPENFILENAME ofn;
	char filePath[1024] = "";
	char fileName[1024] = "";
	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = filePath;
	ofn.nMaxFile = sizeof(filePath);
	ofn.nFilterIndex = true;
	ofn.nMaxFileTitle = sizeof(fileName);
	ofn.lpstrFileTitle = fileName;
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


	//=============================================== 파일 저장 ===============================================
	//-------------------------------------- 지형 정보 벡터에서 가져오기 --------------------------------------
	//파일저장명 가져오기
	string tmpStrFileName;
	tmpStrFileName.append(ofn.lpstrFileTitle);

	TCHAR tmpFileName[128];
	ZeroMemory(&tmpFileName, sizeof(tmpFileName));
	sprintf(tmpFileName, "%s", tmpStrFileName.c_str());

	

	//타일 사이즈 저장
	char tmpBuff[32];
	INIDATA->addData("mapData", "tileX", itoa(_tileX, tmpBuff, 10));
	INIDATA->addData("mapData", "tileY", itoa(_tileY, tmpBuff, 10));
	INIDATA->iniSave(tmpFileName);  //map 파일명과 동일하게 저장


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

	//-------------------------------------- 빌딩 정보 벡터에서 가져오기 --------------------------------------
	//벡터 사이즈 저장
	INIDATA->addData("mapData", "vBdSize", itoa(_vSaveBd.size(), tmpBuff, 10));
	INIDATA->iniSave(tmpFileName);

	//빌딩 사이즈 먼저 가져오기
	tagTile* ptSaveTileBd = new tagTile[_vSaveBd.size()];

	//파일 저장을 위한 옮겨담기(형변환)
	for (int i = 0; i < _vSaveBd.size(); ++i)
	{
		loadVectorTileData(_vSaveBd[i], ptSaveTileBd[i]);
	}

	//파일저장
	WriteFile(hFile, ptSaveTileBd, sizeof(tagTile) * _vSaveBd.size(), &numOfByteWritten, NULL);

	//-------------------------------------- 도로 정보 벡터에서 가져오기 -------------------------------------
	//벡터 사이즈 저장
	INIDATA->addData("mapData", "vRdSize", itoa(_vSaveRd.size(), tmpBuff, 10));
	INIDATA->iniSave(tmpFileName);

	//빌딩 사이즈 먼저 가져오기
	tagTile* ptSaveTileRd = new tagTile[_vSaveRd.size()];

	//파일 저장을 위한 옮겨담기(형변환)
	for (int i = 0; i < _vSaveRd.size(); ++i)
	{
		loadVectorTileData(_vSaveRd[i], ptSaveTileRd[i]);
	}

	//파일저장
	WriteFile(hFile, ptSaveTileRd, sizeof(tagTile) * _vSaveRd.size(), &numOfByteWritten, NULL);

	//-------------------------------------- 가구 정보 벡터에서 가져오기 -------------------------------------
	//벡터 사이즈 저장
	INIDATA->addData("mapData", "vFtSize", itoa(_vSaveFt.size(), tmpBuff, 10));
	INIDATA->iniSave(tmpFileName);

	//빌딩 사이즈 먼저 가져오기
	tagTile* ptSaveTileFt = new tagTile[_vSaveFt.size()];

	//파일 저장을 위한 옮겨담기(형변환)
	for (int i = 0; i < _vSaveFt.size(); ++i)
	{
		loadVectorTileData(_vSaveFt[i], ptSaveTileFt[i]);
	}

	//파일저장
	WriteFile(hFile, ptSaveTileFt, sizeof(tagTile) * _vSaveFt.size(), &numOfByteWritten, NULL);


	//------------------------------------- 아이템 정보 벡터에서 가져오기 -------------------------------------
	//벡터 사이즈 저장
	INIDATA->addData("mapData", "vItSize", itoa(_vSaveIt.size(), tmpBuff, 10));
	INIDATA->iniSave(tmpFileName);

	//빌딩 사이즈 먼저 가져오기
	tagTile* ptSaveTileIt = new tagTile[_vSaveIt.size()];

	//파일 저장을 위한 옮겨담기(형변환)
	for (int i = 0; i < _vSaveIt.size(); ++i)
	{
		loadVectorTileData(_vSaveIt[i], ptSaveTileIt[i]);
	}

	//파일저장
	WriteFile(hFile, ptSaveTileIt, sizeof(tagTile) * _vSaveIt.size(), &numOfByteWritten, NULL);

	//------------------------------------- 무기 정보 벡터에서 가져오기 --------------------------------------
	//벡터 사이즈 저장
	INIDATA->addData("mapData", "vWpSize", itoa(_vSaveWp.size(), tmpBuff, 10));
	INIDATA->iniSave(tmpFileName);

	//빌딩 사이즈 먼저 가져오기
	tagTile* ptSaveTileWp = new tagTile[_vSaveWp.size()];

	//파일 저장을 위한 옮겨담기(형변환)
	for (int i = 0; i < _vSaveWp.size(); ++i)
	{
		loadVectorTileData(_vSaveWp[i], ptSaveTileWp[i]);
	}

	//파일저장
	WriteFile(hFile, ptSaveTileWp, sizeof(tagTile) * _vSaveWp.size(), &numOfByteWritten, NULL);

	//-------------------------------------- 적 정보 벡터에서 가져오기 --------------------------------------
	//벡터 사이즈 저장
	INIDATA->addData("mapData", "vEmSize", itoa(_vSaveEm.size(), tmpBuff, 10));
	INIDATA->iniSave(tmpFileName);

	//빌딩 사이즈 먼저 가져오기
	tagTile* ptSaveTileEm = new tagTile[_vSaveEm.size()];

	//파일 저장을 위한 옮겨담기(형변환)
	for (int i = 0; i < _vSaveEm.size(); ++i)
	{
		loadVectorTileData(_vSaveEm[i], ptSaveTileEm[i]);
	}

	//파일저장
	WriteFile(hFile, ptSaveTileEm, sizeof(tagTile) * _vSaveEm.size(), &numOfByteWritten, NULL);


	//========================================================================================================


	CloseHandle(hFile);
}

//타일 로드
void mapTool::load()
{
	// 파일 저장을 위한 오픈파일네임
	OPENFILENAME ofn;
	char filePath[1024] = "";
	char fileName[1024] = "";
	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = filePath;
	ofn.nMaxFile = sizeof(filePath);
	ofn.nFilterIndex = true;
	ofn.nMaxFileTitle = sizeof(fileName);
	ofn.lpstrFileTitle = fileName;
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
	//----------------- 파일저장명 가져오기 -----------------
	string tmpStrFileName;
	tmpStrFileName.append(ofn.lpstrFileTitle);
	//파일명에서 확장자 지우기
	int tmpStringLength = tmpStrFileName.length();
	int tmpStringIndex = tmpStrFileName.find(".map");
	tmpStrFileName.erase(tmpStringIndex, (tmpStringLength - tmpStringIndex));
	//String -> char
	TCHAR tmpFileName[128];
	ZeroMemory(&tmpFileName, sizeof(tmpFileName));
	sprintf(tmpFileName, "%s", tmpStrFileName.c_str());
	//-------------------------------------------------------


	//벡터 초기화
	vTileClear();

	//벡터크기 로드
	int tmpTileX = INIDATA->loadDataInterger(tmpFileName, "mapData", "tileX");
	int tmpTileY = INIDATA->loadDataInterger(tmpFileName, "mapData", "tileY");

	//grid 벡터에 담기
	gridVectorDraw(tmpTileX, tmpTileY);

	const int terrainSize = tmpTileX * tmpTileY;
	tagTile* ptTmpTileTr = new tagTile[terrainSize];

	//파일로드
	DWORD numOfByteWritten = 0;
	ReadFile(hFile, ptTmpTileTr, sizeof(tagTile) * terrainSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileTr, _vSaveTr, terrainSize);

	//----------------------------------------- 빌딩정보 벡터에 입력 -----------------------------------------
	//벡터크기 로드
	const int bdSize = INIDATA->loadDataInterger(tmpFileName, "mapData", "vBdSize");
	tagTile* ptTmpTileBd = new tagTile[bdSize];

	//파일로드
	ReadFile(hFile, ptTmpTileBd, sizeof(tagTile) * bdSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileBd, _vSaveBd, bdSize);

	//----------------------------------------- 도로정보 벡터에 입력 -----------------------------------------
	//벡터크기 로드
	const int rdSize = INIDATA->loadDataInterger(tmpFileName, "mapData", "vRdSize");
	tagTile* ptTmpTileRd = new tagTile[rdSize];

	//파일로드
	ReadFile(hFile, ptTmpTileBd, sizeof(tagTile) * rdSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileRd, _vSaveRd, rdSize);

	//----------------------------------------- 가구정보 벡터에 입력 -----------------------------------------
	//벡터크기 로드
	const int ftSize = INIDATA->loadDataInterger(tmpFileName, "mapData", "vFtSize");
	tagTile* ptTmpTileFt = new tagTile[ftSize];

	//파일로드
	ReadFile(hFile, ptTmpTileFt, sizeof(tagTile) * ftSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileFt, _vSaveRd, ftSize);

	//---------------------------------------- 아이템정보 벡터에 입력 ----------------------------------------
	//벡터크기 로드
	const int itSize = INIDATA->loadDataInterger(tmpFileName, "mapData", "vItSize");
	tagTile* ptTmpTileIt = new tagTile[itSize];

	//파일로드
	ReadFile(hFile, ptTmpTileIt, sizeof(tagTile) * itSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileIt, _vSaveRd, itSize);

	//----------------------------------------- 무기정보 벡터에 입력 ----------------------------------------
	//벡터크기 로드
	const int wpSize = INIDATA->loadDataInterger(tmpFileName, "mapData", "vWpSize");
	tagTile* ptTmpTileWp = new tagTile[wpSize];

	//파일로드
	ReadFile(hFile, ptTmpTileWp, sizeof(tagTile) * wpSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileWp, _vSaveRd, wpSize);

	//------------------------------------------ 적정보 벡터에 입력 -----------------------------------------
	//벡터크기 로드
	const int emSize = INIDATA->loadDataInterger(tmpFileName, "mapData", "vEmSize");
	tagTile* ptTmpTileEm = new tagTile[emSize];

	//파일로드
	ReadFile(hFile, ptTmpTileEm, sizeof(tagTile) * emSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileEm, _vSaveRd, emSize);
	//========================================================================================================

	CloseHandle(hFile);
}


void mapTool::loadVectorTileData(tagTile setTile, tagTile& getTile)
{
	getTile.id         = setTile.id;
	getTile.index      = setTile.index;
	getTile.attribute  = setTile.attribute;
	getTile.tileType   = setTile.tileType;
	getTile.anchorType = setTile.anchorType;
	getTile.overPos    = setTile.overPos;
	getTile.img		   = IMAGEMANAGER->findImage(setTile.imgName);
	sprintf(getTile.imgName, "%s", setTile.imgName);
	getTile.frameX     = setTile.frameX;
	getTile.frameY     = setTile.frameY;
	getTile.x		   = setTile.x;
	getTile.y		   = setTile.y;
	getTile.rc		   = setTile.rc;
	getTile.scale      = setTile.scale;
	getTile.gapX	   = setTile.gapX;
	getTile.gapY	   = setTile.gapY;
	getTile.moveX	   = setTile.moveX;
	getTile.moveY	   = setTile.moveY;
	getTile.centerX    = setTile.centerX;
	getTile.centerY    = setTile.centerY;
}

void mapTool::saveVectorTileData(tagTile* getTile, vSaveTile& vSaveTile, int tileSize)
{
	//수정사항: 벡터의 크기를 타일 사이즈에 따라서 생성
	tagTile tmpTile;
	ZeroMemory(&tmpTile, sizeof(tagTile));

	for (int i = 0; i < tileSize; ++i)
	{
		vSaveTile.push_back(tmpTile);
	}


	for (int i = 0; i < tileSize; ++i)
	{
		if (getTile[i].img == NULL) continue;

		vSaveTile[i].id		    = getTile[i].id;
		vSaveTile[i].index      = getTile[i].index;
		vSaveTile[i].attribute  = getTile[i].attribute;
		vSaveTile[i].tileType   = getTile[i].tileType;
		vSaveTile[i].anchorType = getTile[i].anchorType;
		vSaveTile[i].overPos    = getTile[i].overPos;
		vSaveTile[i].img	    = IMAGEMANAGER->findImage(getTile[i].imgName);
		sprintf(vSaveTile[i].imgName, "%s", getTile[i].imgName);
		vSaveTile[i].frameX     = getTile[i].frameX;
		vSaveTile[i].frameY     = getTile[i].frameY;
		vSaveTile[i].x		    = getTile[i].x;
		vSaveTile[i].y		    = getTile[i].y;
		vSaveTile[i].rc		    = getTile[i].rc;
		vSaveTile[i].scale      = getTile[i].scale;
		vSaveTile[i].gapX	    = getTile[i].gapX;
		vSaveTile[i].gapY	    = getTile[i].gapY;
		vSaveTile[i].moveX	    = getTile[i].moveX;
		vSaveTile[i].moveY	    = getTile[i].moveY;
		vSaveTile[i].centerX    = getTile[i].centerX;
		vSaveTile[i].centerY    = getTile[i].centerY;
	}
}


