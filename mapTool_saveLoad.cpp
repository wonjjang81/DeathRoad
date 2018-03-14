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
	const int terrainSize = TILEX * TILEY;
	tagTile tmpTile[terrainSize];
	ZeroMemory(&tmpTile, sizeof(tagTile) * terrainSize);

	for (int i = 0; i < _vSaveTr.size(); ++i)
	{
		 loadVectorTileData(_vSaveTr[i], tmpTile[i]);
	}
	//-------------------------------------- 빌딩정보 벡터에서 가져오기 --------------------------------------


	//========================================================================================================

	DWORD numOfByteWritten = 0;
	WriteFile(hFile, &tmpTile, sizeof(tagTile) * terrainSize, &numOfByteWritten, NULL);




	//HANDLE hMapFile = CreateFileMapping(hFile,  //파일을 매핑할 파일의 핸들
	//	NULL,                                   //파일 보안 속성
	//	PAGE_READWRITE,                         //접근권한
	//	0,                                      //매핑할 파일의 크기 지정
	//	0,                                      //매핑할 파일의 크기 지정 
	//	NULL);                                  //파일매핑 이름 / 메모리 공유에 사용되는 식별자 문자열
	//if (hMapFile == NULL)
	//{
	//	MessageBoxA(0, "CreateFileMapping Error", "", 0);
	//}


	//CHAR *pWrite = (CHAR *)MapViewOfFile(hMapFile,  //파일맵 핸들
	//	FILE_MAP_WRITE,                             //파일뷰의 접근권한
	//	0,                                          //매핑할 파일의 시작위치
	//	0,                                          //매핑할 파일의 시작위치
	//	0);                                         //매핑할 크기 / 0이면 파일 전체를 매핑
	//if (pWrite == NULL)
	//{
	//	MessageBoxA(0, "MapViewOfFile Error", "", 0);
	//}


	//UnmapViewOfFile(pWrite);   //매핑된 데이터 영역 해제
	//CloseHandle(hMapFile);     //핸들 반환
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
	this->init();

	string tempName;
	tempName.append(ofn.lpstrFile);

	HANDLE hFile;
	hFile = CreateFile(tempName.c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBoxA(0, "CreateFile Error", "", 0);
	}

	//HANDLE hMapFile = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
	//if (hMapFile == NULL)
	//{
	//	MessageBoxA(0, "CreateFileMapping Error", "", 0);
	//}

	//CHAR *pWrite = (CHAR *)MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);
	//if (pWrite == NULL)
	//{
	//	MessageBoxA(0, "MapViewOfFile Error", "", 0);
	//}

	const int terrainSize = TILEX * TILEY;
	tagTile tmpTile[terrainSize];
	ZeroMemory(&tmpTile, sizeof(tagTile) * terrainSize);



	DWORD numOfByteWritten = 0;
	ReadFile(hFile, &tmpTile, sizeof(tagTile) * terrainSize, &numOfByteWritten, NULL);

	//========================================= 로드한 파일 저장하기 =========================================
	//----------------------------------------- 지형정보 벡터에 입력 -----------------------------------------
	saveVectorTileData(tmpTile, _vSaveTr, terrainSize);
	//========================================================================================================


	//UnmapViewOfFile(pWrite);
	//CloseHandle(hMapFile);
	CloseHandle(hFile);
}


void mapTool::loadVectorTileData(tagTile setTile, tagTile& getTile)
{
	//if (setTile.img == NULL) return;

	getTile.attribute = setTile.attribute;
	getTile.tileType  = setTile.tileType;
	getTile.index	  = setTile.index;
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

		vSaveTile[i].attribute = getTile[i].attribute;
		vSaveTile[i].tileType  = getTile[i].tileType;
		vSaveTile[i].index	   = getTile[i].index;
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