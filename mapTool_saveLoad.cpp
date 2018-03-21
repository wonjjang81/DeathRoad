#include "stdafx.h"
#include "mapTool.h"


//Ÿ�� ����
void mapTool::save()
{
	// ���� ������ ���� �������ϳ���
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


	//=============================================== ���� ���� ===============================================
	//-------------------------------------- ���� ���� ���Ϳ��� �������� --------------------------------------
	//��������� ��������
	string tmpStrFileName;
	tmpStrFileName.append(ofn.lpstrFileTitle);

	TCHAR tmpFileName[128];
	ZeroMemory(&tmpFileName, sizeof(tmpFileName));
	sprintf(tmpFileName, "%s", tmpStrFileName.c_str());

	
	//Ÿ�� ������ ����
	char tmpTsizeX[32];
	char tmpTsizeY[32];
	sprintf(tmpTsizeX, "%d", _tileX);
	sprintf(tmpTsizeY, "%d", _tileY);
	INIDATA->addData("mapData", "tileX", tmpTsizeX);
	INIDATA->addData("mapData", "tileY", tmpTsizeY);
	INIDATA->iniSave(tmpFileName);  //map ���ϸ�� �����ϰ� ����


	//���� ������ ����
	char tmpVsize[32];
	sprintf(tmpVsize, "%d", _vSaveTr.size());
	INIDATA->addData("mapData", "vTrSize", tmpVsize);
	INIDATA->iniSave(tmpFileName);

	//���� ������ ���� ��������
	tagTile* ptSaveTileTr = new tagTile[_vSaveTr.size()];

	//���� ������ ���� �Űܴ��(����ȯ)
	for (int i = 0; i < _vSaveTr.size(); ++i)
	{
		 loadVectorTileData(_vSaveTr[i], ptSaveTileTr[i]);
	}

	//��������
	DWORD numOfByteWritten = 0;
	WriteFile(hFile, ptSaveTileTr, sizeof(tagTile) * _vSaveTr.size(), &numOfByteWritten, NULL);

	//-------------------------------------- ���� ���� ���Ϳ��� �������� --------------------------------------
	//���� ������ ����
	ZeroMemory(&tmpVsize, sizeof(tmpVsize));
	sprintf(tmpVsize, "%d", _vSaveBd.size());
	INIDATA->addData("mapData", "vBdSize", tmpVsize);
	INIDATA->iniSave(tmpFileName);

	//���� ������ ���� ��������
	tagTile* ptSaveTileBd = new tagTile[_vSaveBd.size()];

	//���� ������ ���� �Űܴ��(����ȯ)
	for (int i = 0; i < _vSaveBd.size(); ++i)
	{
		loadVectorTileData(_vSaveBd[i], ptSaveTileBd[i]);
	}

	//��������
	WriteFile(hFile, ptSaveTileBd, sizeof(tagTile) * _vSaveBd.size(), &numOfByteWritten, NULL);

	//-------------------------------------- ���� ���� ���Ϳ��� �������� -------------------------------------
	//���� ������ ����
	ZeroMemory(&tmpVsize, sizeof(tmpVsize));
	sprintf(tmpVsize, "%d", _vSaveRd.size());
	INIDATA->addData("mapData", "vRdSize", tmpVsize);
	INIDATA->iniSave(tmpFileName);

	//���� ������ ���� ��������
	tagTile* ptSaveTileRd = new tagTile[_vSaveRd.size()];

	//���� ������ ���� �Űܴ��(����ȯ)
	for (int i = 0; i < _vSaveRd.size(); ++i)
	{
		loadVectorTileData(_vSaveRd[i], ptSaveTileRd[i]);
	}

	//��������
	WriteFile(hFile, ptSaveTileRd, sizeof(tagTile) * _vSaveRd.size(), &numOfByteWritten, NULL);

	//-------------------------------------- ���� ���� ���Ϳ��� �������� -------------------------------------
	//���� ������ ����
	ZeroMemory(&tmpVsize, sizeof(tmpVsize));
	sprintf(tmpVsize, "%d", _vSaveFt.size());
	INIDATA->addData("mapData", "vFtSize", tmpVsize);
	INIDATA->iniSave(tmpFileName);

	//���� ������ ���� ��������
	tagTile* ptSaveTileFt = new tagTile[_vSaveFt.size()];

	//���� ������ ���� �Űܴ��(����ȯ)
	for (int i = 0; i < _vSaveFt.size(); ++i)
	{
		loadVectorTileData(_vSaveFt[i], ptSaveTileFt[i]);
	}

	//��������
	WriteFile(hFile, ptSaveTileFt, sizeof(tagTile) * _vSaveFt.size(), &numOfByteWritten, NULL);


	//------------------------------------- ������ ���� ���Ϳ��� �������� -------------------------------------
	//���� ������ ����
	ZeroMemory(&tmpVsize, sizeof(tmpVsize));
	sprintf(tmpVsize, "%d", _vSaveIt.size());
	INIDATA->addData("mapData", "vItSize", tmpVsize);
	INIDATA->iniSave(tmpFileName);

	//���� ������ ���� ��������
	tagTile* ptSaveTileIt = new tagTile[_vSaveIt.size()];

	//���� ������ ���� �Űܴ��(����ȯ)
	for (int i = 0; i < _vSaveIt.size(); ++i)
	{
		loadVectorTileData(_vSaveIt[i], ptSaveTileIt[i]);
	}

	//��������
	WriteFile(hFile, ptSaveTileIt, sizeof(tagTile) * _vSaveIt.size(), &numOfByteWritten, NULL);

	//------------------------------------- ���� ���� ���Ϳ��� �������� --------------------------------------
	//���� ������ ����
	ZeroMemory(&tmpVsize, sizeof(tmpVsize));
	sprintf(tmpVsize, "%d", _vSaveWp.size());
	INIDATA->addData("mapData", "vWpSize", tmpVsize);
	INIDATA->iniSave(tmpFileName);

	//���� ������ ���� ��������
	tagTile* ptSaveTileWp = new tagTile[_vSaveWp.size()];

	//���� ������ ���� �Űܴ��(����ȯ)
	for (int i = 0; i < _vSaveWp.size(); ++i)
	{
		loadVectorTileData(_vSaveWp[i], ptSaveTileWp[i]);
	}

	//��������
	WriteFile(hFile, ptSaveTileWp, sizeof(tagTile) * _vSaveWp.size(), &numOfByteWritten, NULL);

	//-------------------------------------- �� ���� ���Ϳ��� �������� --------------------------------------
	//���� ������ ����
	ZeroMemory(&tmpVsize, sizeof(tmpVsize));
	sprintf(tmpVsize, "%d", _vSaveEm.size());
	INIDATA->addData("mapData", "vEmSize", tmpVsize);
	INIDATA->iniSave(tmpFileName);

	//���� ������ ���� ��������
	tagTile* ptSaveTileEm = new tagTile[_vSaveEm.size()];

	//���� ������ ���� �Űܴ��(����ȯ)
	for (int i = 0; i < _vSaveEm.size(); ++i)
	{
		loadVectorTileData(_vSaveEm[i], ptSaveTileEm[i]);
	}

	//��������
	WriteFile(hFile, ptSaveTileEm, sizeof(tagTile) * _vSaveEm.size(), &numOfByteWritten, NULL);

	//-------------------------------------- �� ���� ���Ϳ��� �������� --------------------------------------
	//���� ������ ����
	ZeroMemory(&tmpVsize, sizeof(tmpVsize));
	sprintf(tmpVsize, "%d", _vSaveWl.size());
	INIDATA->addData("mapData", "vWlSize", tmpVsize);
	INIDATA->iniSave(tmpFileName);

	//���� ������ ���� ��������
	tagTile* ptSaveTileWl = new tagTile[_vSaveWl.size()];

	//���� ������ ���� �Űܴ��(����ȯ)
	for (int i = 0; i < _vSaveWl.size(); ++i)
	{
		loadVectorTileData(_vSaveWl[i], ptSaveTileWl[i]);
	}

	//��������
	WriteFile(hFile, ptSaveTileWl, sizeof(tagTile) * _vSaveWl.size(), &numOfByteWritten, NULL);

	//-------------------------------------- �� ���� ���Ϳ��� �������� --------------------------------------
	//���� ������ ����
	ZeroMemory(&tmpVsize, sizeof(tmpVsize));
	sprintf(tmpVsize, "%d", _vSaveDr.size());
	INIDATA->addData("mapData", "vDrSize", tmpVsize);
	INIDATA->iniSave(tmpFileName);

	//���� ������ ���� ��������
	tagTile* ptSaveTileDr = new tagTile[_vSaveDr.size()];

	//���� ������ ���� �Űܴ��(����ȯ)
	for (int i = 0; i < _vSaveDr.size(); ++i)
	{
		loadVectorTileData(_vSaveDr[i], ptSaveTileDr[i]);
	}

	//��������
	WriteFile(hFile, ptSaveTileDr, sizeof(tagTile) * _vSaveDr.size(), &numOfByteWritten, NULL);

	//========================================================================================================


	CloseHandle(hFile);
}

//Ÿ�� �ε�
void mapTool::load()
{
	// ���� ������ ���� �������ϳ���
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
	//----------------- ��������� �������� -----------------
	string tmpStrFileName;
	tmpStrFileName.append(ofn.lpstrFileTitle);
	//���ϸ��� Ȯ���� �����
	int tmpStringLength = tmpStrFileName.length();
	int tmpStringIndex = tmpStrFileName.find(".map");
	tmpStrFileName.erase(tmpStringIndex, (tmpStringLength - tmpStringIndex));
	//String -> char
	TCHAR tmpFileName[128];
	ZeroMemory(&tmpFileName, sizeof(tmpFileName));
	sprintf(tmpFileName, "%s", tmpStrFileName.c_str());
	//-------------------------------------------------------


	//���� �ʱ�ȭ
	vTileClear();

	//����ũ�� �ε�
	_tileX = INIDATA->loadDataInterger(tmpFileName, "mapData", "tileX");
	_tileY = INIDATA->loadDataInterger(tmpFileName, "mapData", "tileY");

	//grid ���Ϳ� ���
	gridVectorDraw(_tileX, _tileY);

	const int terrainSize = INIDATA->loadDataInterger(tmpFileName, "mapData", "vTrSize");
	tagTile* ptTmpTileTr = new tagTile[terrainSize];

	//���Ϸε�
	DWORD numOfByteWritten = 0;
	ReadFile(hFile, ptTmpTileTr, sizeof(tagTile) * terrainSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileTr, _vSaveTr, terrainSize);

	//----------------------------------------- �������� ���Ϳ� �Է� -----------------------------------------
	//����ũ�� �ε�
	const int bdSize = INIDATA->loadDataInterger(tmpFileName, "mapData", "vBdSize");
	tagTile* ptTmpTileBd = new tagTile[bdSize];

	//���Ϸε�
	ReadFile(hFile, ptTmpTileBd, sizeof(tagTile) * bdSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileBd, _vSaveBd, bdSize);

	//----------------------------------------- �������� ���Ϳ� �Է� -----------------------------------------
	//����ũ�� �ε�
	const int rdSize = INIDATA->loadDataInterger(tmpFileName, "mapData", "vRdSize");
	tagTile* ptTmpTileRd = new tagTile[rdSize];

	//���Ϸε�
	ReadFile(hFile, ptTmpTileBd, sizeof(tagTile) * rdSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileRd, _vSaveRd, rdSize);

	//----------------------------------------- �������� ���Ϳ� �Է� -----------------------------------------
	//����ũ�� �ε�
	const int ftSize = INIDATA->loadDataInterger(tmpFileName, "mapData", "vFtSize");
	tagTile* ptTmpTileFt = new tagTile[ftSize];

	//���Ϸε�
	ReadFile(hFile, ptTmpTileFt, sizeof(tagTile) * ftSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileFt, _vSaveFt, ftSize);

	//---------------------------------------- ���������� ���Ϳ� �Է� ----------------------------------------
	//����ũ�� �ε�
	const int itSize = INIDATA->loadDataInterger(tmpFileName, "mapData", "vItSize");
	tagTile* ptTmpTileIt = new tagTile[itSize];

	//���Ϸε�
	ReadFile(hFile, ptTmpTileIt, sizeof(tagTile) * itSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileIt, _vSaveIt, itSize);

	//----------------------------------------- �������� ���Ϳ� �Է� ----------------------------------------
	//����ũ�� �ε�
	const int wpSize = INIDATA->loadDataInterger(tmpFileName, "mapData", "vWpSize");
	tagTile* ptTmpTileWp = new tagTile[wpSize];

	//���Ϸε�
	ReadFile(hFile, ptTmpTileWp, sizeof(tagTile) * wpSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileWp, _vSaveWp, wpSize);

	//------------------------------------------ ������ ���Ϳ� �Է� -----------------------------------------
	//����ũ�� �ε�
	const int emSize = INIDATA->loadDataInterger(tmpFileName, "mapData", "vEmSize");
	tagTile* ptTmpTileEm = new tagTile[emSize];

	//���Ϸε�
	ReadFile(hFile, ptTmpTileEm, sizeof(tagTile) * emSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileEm, _vSaveEm, emSize);

	//------------------------------------------ ������ ���Ϳ� �Է� -----------------------------------------
	//����ũ�� �ε�
	const int wlSize = INIDATA->loadDataInterger(tmpFileName, "mapData", "vWlSize");
	tagTile* ptTmpTileWl = new tagTile[wlSize];

	//���Ϸε�
	ReadFile(hFile, ptTmpTileWl, sizeof(tagTile) * wlSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileWl, _vSaveWl, wlSize);

	//------------------------------------------ ������ ���Ϳ� �Է� -----------------------------------------
	//����ũ�� �ε�
	const int drSize = INIDATA->loadDataInterger(tmpFileName, "mapData", "vDrSize");
	tagTile* ptTmpTileDr = new tagTile[drSize];

	//���Ϸε�
	ReadFile(hFile, ptTmpTileDr, sizeof(tagTile) * drSize, &numOfByteWritten, NULL);
	saveVectorTileData(ptTmpTileDr, _vSaveDr, drSize);

	//------------------------------------------- �׸��� ���� �Է� ------------------------------------------


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


