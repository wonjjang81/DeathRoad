#include "stdafx.h"
#include "mapLoad.h"


mapLoad::mapLoad()
{
}
mapLoad::~mapLoad()
{
}


void mapLoad::loadMap(string fileName)
{
	//========================================= �ε��� ���� �����ϱ� =========================================
	//----------------------------------------- �������� ���Ϳ� �Է� -----------------------------------------
	//----------------- ��������� �������� -----------------


	char str[256];
	GetCurrentDirectory(256, str);   //���� ���丮 ���
	string tmpFileName;
	tmpFileName.append(str);         //���ϰ��
	tmpFileName.append("\\map\\");   //���ϰ��
	tmpFileName.append(fileName);    //���ϸ�
	tmpFileName.append(".map");      //Ȯ����
	
	HANDLE hFile;
	hFile = CreateFile(tmpFileName.c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBoxA(0, "CreateFile Error", "", 0);
	}

	//���� �ʱ�ȭ
	//vTileClear();

	tmpFileName.clear();
	tmpFileName.append("map//");
	tmpFileName.append(fileName);


	//����ũ�� �ε�
	const int trSize = INIDATA->loadDataInterger(tmpFileName.c_str(), "mapData", "vTrSize");

	tagTile* ptTmpTileTr = new tagTile[trSize];

	//���Ϸε�
	DWORD numOfByteWritten = 0;
	ReadFile(hFile, ptTmpTileTr, sizeof(tagTile) * trSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileTr, _vSaveTr, trSize);

	//----------------------------------------- �������� ���Ϳ� �Է� -----------------------------------------
	//����ũ�� �ε�
	const int bdSize = INIDATA->loadDataInterger(tmpFileName.c_str(), "mapData", "vBdSize");
	tagTile* ptTmpTileBd = new tagTile[bdSize];

	//���Ϸε�
	ReadFile(hFile, ptTmpTileBd, sizeof(tagTile) * bdSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileBd, _vSaveBd, bdSize);

	//----------------------------------------- �������� ���Ϳ� �Է� -----------------------------------------
	//����ũ�� �ε�
	const int rdSize = INIDATA->loadDataInterger(tmpFileName.c_str(), "mapData", "vRdSize");
	tagTile* ptTmpTileRd = new tagTile[rdSize];

	//���Ϸε�
	ReadFile(hFile, ptTmpTileBd, sizeof(tagTile) * rdSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileRd, _vSaveRd, rdSize);

	//----------------------------------------- �������� ���Ϳ� �Է� -----------------------------------------
	//����ũ�� �ε�
	const int ftSize = INIDATA->loadDataInterger(tmpFileName.c_str(), "mapData", "vFtSize");
	tagTile* ptTmpTileFt = new tagTile[ftSize];

	//���Ϸε�
	ReadFile(hFile, ptTmpTileFt, sizeof(tagTile) * ftSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileFt, _vSaveFt, ftSize);

	//---------------------------------------- ���������� ���Ϳ� �Է� ----------------------------------------
	//����ũ�� �ε�
	const int itSize = INIDATA->loadDataInterger(tmpFileName.c_str(), "mapData", "vItSize");
	tagTile* ptTmpTileIt = new tagTile[itSize];

	//���Ϸε�
	ReadFile(hFile, ptTmpTileIt, sizeof(tagTile) * itSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileIt, _vSaveIt, itSize);

	//----------------------------------------- �������� ���Ϳ� �Է� ----------------------------------------
	//����ũ�� �ε�
	const int wpSize = INIDATA->loadDataInterger(tmpFileName.c_str(), "mapData", "vWpSize");
	tagTile* ptTmpTileWp = new tagTile[wpSize];

	//���Ϸε�
	ReadFile(hFile, ptTmpTileWp, sizeof(tagTile) * wpSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileWp, _vSaveWp, wpSize);

	//------------------------------------------ ������ ���Ϳ� �Է� -----------------------------------------
	//����ũ�� �ε�
	const int emSize = INIDATA->loadDataInterger(tmpFileName.c_str(), "mapData", "vEmSize");
	tagTile* ptTmpTileEm = new tagTile[emSize];

	//���Ϸε�
	ReadFile(hFile, ptTmpTileEm, sizeof(tagTile) * emSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileEm, _vSaveEm, emSize);

	//------------------------------------------ ������ ���Ϳ� �Է� -----------------------------------------
	//����ũ�� �ε�
	const int wlSize = INIDATA->loadDataInterger(tmpFileName.c_str(), "mapData", "vWlSize");
	tagTile* ptTmpTileWl = new tagTile[wlSize];

	//���Ϸε�
	ReadFile(hFile, ptTmpTileWl, sizeof(tagTile) * wlSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileWl, _vSaveWl, wlSize);

	//------------------------------------------ ������ ���Ϳ� �Է� -----------------------------------------
	//����ũ�� �ε�
	const int drSize = INIDATA->loadDataInterger(tmpFileName.c_str(), "mapData", "vDrSize");
	tagTile* ptTmpTileDr = new tagTile[drSize];

	//���Ϸε�
	ReadFile(hFile, ptTmpTileDr, sizeof(tagTile) * drSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileDr, _vSaveDr, drSize);
	//========================================================================================================


	CloseHandle(hFile);
}


void mapLoad::saveVectorTileData(tagTile* getTile, vSaveTile& vSaveTile, int tileSize)
{
	//��������: ������ ũ�⸦ Ÿ�� ����� ���� ����
	tagTile tmpTile;
	ZeroMemory(&tmpTile, sizeof(tagTile));

	for (int i = 0; i < tileSize; ++i)
	{
		vSaveTile.push_back(tmpTile);
	}


	for (int i = 0; i < tileSize; ++i)
	{
		if (getTile[i].img == NULL) continue;

		vSaveTile[i].id = getTile[i].id;
		vSaveTile[i].index = getTile[i].index;
		vSaveTile[i].attribute = getTile[i].attribute;
		vSaveTile[i].tileType = getTile[i].tileType;
		vSaveTile[i].anchorType = getTile[i].anchorType;
		vSaveTile[i].overPos = getTile[i].overPos;
		vSaveTile[i].img = IMAGEMANAGER->findImage(getTile[i].imgName);
		sprintf(vSaveTile[i].imgName, "%s", getTile[i].imgName);
		vSaveTile[i].frameX = getTile[i].frameX;
		vSaveTile[i].frameY = getTile[i].frameY;
		vSaveTile[i].x = getTile[i].rc.left;
		vSaveTile[i].y = getTile[i].rc.top;

		vSaveTile[i].rc = getTile[i].rc;
		revisonRect(vSaveTile[i].attribute, vSaveTile[i].rc);

		vSaveTile[i].scale = getTile[i].scale;
		vSaveTile[i].gapX = getTile[i].gapX;
		vSaveTile[i].gapY = getTile[i].gapY;
		vSaveTile[i].moveX = getTile[i].moveX;
		vSaveTile[i].moveY = getTile[i].moveY;
		vSaveTile[i].centerX = getTile[i].centerX;
		vSaveTile[i].centerY = getTile[i].centerY;
	}
}


void mapLoad::revisonRect(ATTRIBUTE att, RECT& rc)
{
	switch (att)
	{
		case ATTR_NONE:
			ZeroMemory(&rc, sizeof(RECT));
		break;
		case ATTR_MOVE:
			ZeroMemory(&rc, sizeof(RECT));
		break;
		case ATTR_UNMOVE:

		break;
		case ATTR_AFTER_RENDER:
			ZeroMemory(&rc, sizeof(RECT));
		break;
		case ATTR_WALL_CENTER:
	
		break;
		case ATTR_WALL_UNMOVE:
	
		break;
		case ATTR_DOOR:

		break;
		case ATTR_STARTPOINT:
	
		break;
	}
}