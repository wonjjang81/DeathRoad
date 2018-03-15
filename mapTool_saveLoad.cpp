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
	//Ÿ�� ������ ����
	char tmpBuff[16];
	INIDATA->addData("mapData", "tileX", itoa(_tileX, tmpBuff, 10));
	INIDATA->addData("mapData", "tileY", itoa(_tileY, tmpBuff, 10));
	INIDATA->iniSave("deathRoad");

	//���� ������ ���� ��������
	const int terrainSize = _tileX * _tileY;
	tagTile* ptSaveTileTr = new tagTile[terrainSize];

	//���� ������ ���� �Űܴ��(����ȯ)
	for (int i = 0; i < _vSaveTr.size(); ++i)
	{
		 loadVectorTileData(_vSaveTr[i], ptSaveTileTr[i]);
	}

	//��������
	DWORD numOfByteWritten = 0;
	WriteFile(hFile, ptSaveTileTr, sizeof(tagTile) * terrainSize, &numOfByteWritten, NULL);
	//-------------------------------------- �������� ���Ϳ��� �������� --------------------------------------
	//���� ������ ����
	INIDATA->addData("mapData", "vBdSize", itoa(_vSaveBd.size(), tmpBuff, 10));
	INIDATA->iniSave("deathRoad");

	//���� ������ ���� ��������
	tagTile* ptSaveTileBd = new tagTile[_vSaveBd.size()];

	//���� ������ ���� �Űܴ��(����ȯ)
	for (int i = 0; i < _vSaveBd.size(); ++i)
	{
		loadVectorTileData(_vSaveBd[i], ptSaveTileBd[i]);
	}

	//��������
	WriteFile(hFile, ptSaveTileBd, sizeof(tagTile) * terrainSize, &numOfByteWritten, NULL);
	//========================================================================================================


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
	SCENEMANAGER->changeScene("����");

	string tempName;
	tempName.append(ofn.lpstrFile);

	HANDLE hFile;
	hFile = CreateFile(tempName.c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBoxA(0, "CreateFile Error", "", 0);
	}


	//========================================= �ε��� ���� �����ϱ� =========================================
	//----------------------------------------- �������� ���Ϳ� �Է� -----------------------------------------
	//����ũ�� �ε�
	int tmpTileX = INIDATA->loadDataInterger("deathRoad", "mapData", "tileX");
	int tmpTileY = INIDATA->loadDataInterger("deathRoad", "mapData", "tileY");
	const int terrainSize = tmpTileX * tmpTileY;
	tagTile* ptTmpTileTr = new tagTile[terrainSize];

	//���Ϸε�
	DWORD numOfByteWritten = 0;
	ReadFile(hFile, ptTmpTileTr, sizeof(tagTile) * terrainSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileTr, _vSaveTr, terrainSize);

	//----------------------------------------- �������� ���Ϳ� �Է� -----------------------------------------
	//����ũ�� �ε�
	const int buildingSize = INIDATA->loadDataInterger("deathRoad", "mapData", "vBdSize");
	tagTile* ptTmpTileBd = new tagTile[buildingSize];

	//���Ϸε�
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
	//��������: ������ ũ�⸦ Ÿ�� ����� ���� ����

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

