#include "stdafx.h"
#include "mapTool.h"


//Ÿ�� ����
void mapTool::save()
{
	// ���� ������ ���� �������ϳ���
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

	//����ó��
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


	//========================================= ������ ���� �ҷ����� =========================================
	//-------------------------------------- �������� ���Ϳ��� �������� --------------------------------------
	const int terrainSize = TILEX * TILEY;
	tagTile tmpTile[terrainSize];
	ZeroMemory(&tmpTile, sizeof(tagTile) * terrainSize);

	for (int i = 0; i < _vSaveTr.size(); ++i)
	{
		 loadVectorTileData(_vSaveTr[i], tmpTile[i]);
	}
	//-------------------------------------- �������� ���Ϳ��� �������� --------------------------------------


	//========================================================================================================

	DWORD numOfByteWritten = 0;
	WriteFile(hFile, &tmpTile, sizeof(tagTile) * terrainSize, &numOfByteWritten, NULL);




	//HANDLE hMapFile = CreateFileMapping(hFile,  //������ ������ ������ �ڵ�
	//	NULL,                                   //���� ���� �Ӽ�
	//	PAGE_READWRITE,                         //���ٱ���
	//	0,                                      //������ ������ ũ�� ����
	//	0,                                      //������ ������ ũ�� ���� 
	//	NULL);                                  //���ϸ��� �̸� / �޸� ������ ���Ǵ� �ĺ��� ���ڿ�
	//if (hMapFile == NULL)
	//{
	//	MessageBoxA(0, "CreateFileMapping Error", "", 0);
	//}


	//CHAR *pWrite = (CHAR *)MapViewOfFile(hMapFile,  //���ϸ� �ڵ�
	//	FILE_MAP_WRITE,                             //���Ϻ��� ���ٱ���
	//	0,                                          //������ ������ ������ġ
	//	0,                                          //������ ������ ������ġ
	//	0);                                         //������ ũ�� / 0�̸� ���� ��ü�� ����
	//if (pWrite == NULL)
	//{
	//	MessageBoxA(0, "MapViewOfFile Error", "", 0);
	//}


	//UnmapViewOfFile(pWrite);   //���ε� ������ ���� ����
	//CloseHandle(hMapFile);     //�ڵ� ��ȯ
	CloseHandle(hFile);

}

//Ÿ�� �ε�
void mapTool::load()
{
	// ���� ������ ���� �������ϳ���
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

	//����ó��
	if (GetSaveFileName(&ofn) == FALSE) return;

	//�ʱ�ȭ
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

	//========================================= �ε��� ���� �����ϱ� =========================================
	//----------------------------------------- �������� ���Ϳ� �Է� -----------------------------------------
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
	//��������: ������ ũ�⸦ Ÿ�� ����� ���� ����

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