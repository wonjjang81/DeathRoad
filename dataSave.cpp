#include "stdafx.h"
#include "dataSave.h"


dataSave::dataSave()
{
}
dataSave::~dataSave()
{
}


HRESULT dataSave::init()
{


	return S_OK;
}


void dataSave::dataSet()
{
	itemSet();
	wallSet();
	furnitureSet();
	weaponSet();
}


//Furniture Info
void dataSave::furnitureSet()
{
	tagDataInfo tmpInfo;
	vItemInfo vItemInfo;

	int tileX = 8;
	int tileY = 30;

	for (int i = 0; i < tileY; ++i)
	{
		for (int j = 0; j < tileX; ++j)
		{
			if (i < tileY)
			{
				ZeroMemory(&tmpInfo, sizeof(tagDataInfo));

				if (i == 1 && j == 4)  continue;
				if (i == 2)			   continue;
				if (i == 3 && j == 4)  continue;
				if (i == 4 && j == 4)  continue;
				if (i == 6 && j == 4)  continue;
				if (i == 7)			   continue;
				if (i == 8 && j == 4)  continue;
				if (i == 9 && j == 4)  continue;
				if (i == 11 && j == 4) continue;
				if (i == 12)		   continue;
				if (i == 13 && j == 4) continue;
				if (i == 14 && j == 4) continue;
				if (i == 16 && j == 4) continue;
				if (i == 17)		   continue;
				if (i == 18 && j == 4) continue;
				if (i == 19 && j == 4) continue;
				if (i == 21 && j == 4) continue;
				if (i == 22)		   continue;
				if (i == 23 && j == 4) continue;
				if (i == 24 && j == 4) continue;
				if (i == 26 && j == 4) continue;
				if (i == 27)		   continue;
				if (i == 28 && j == 4) continue;
				if (i == 29 && j == 4) continue;


				if (j == 0 || j == 2 || j == 4)
				{
					tmpInfo.index = (i * tileX) + j;
					tmpInfo.type = TYPE_A_FT_ITEM;

					vItemInfo.push_back(tmpInfo);
				}
			}
		}
	}

	//Data Save
	str2IntSave(vItemInfo, "FurnitureData");
}



//Item Info
void dataSave::itemSet()
{
	tagDataInfo tmpInfo;
	vItemInfo vItemInfo;

	for (int i = 0; i < ITEMSIZE; ++i)
	{
		//food
		if (i < 8)
		{
			ZeroMemory(&tmpInfo, sizeof(tagDataInfo));

			tmpInfo.index = i;
			tmpInfo.type = TYPE_A_IT_FOOD;
			tmpInfo.value = RND->getFromIntTo(2, 5);

			vItemInfo.push_back(tmpInfo);
		}
		//drug
		if (i >= 8 && i < 11)
		{
			ZeroMemory(&tmpInfo, sizeof(tagDataInfo));

			tmpInfo.index = i;
			tmpInfo.type = TYPE_A_IT_DRUG;
			tmpInfo.value = RND->getFromIntTo(2, 5);

			vItemInfo.push_back(tmpInfo);
		}
		//oil
		if (i == 12)
		{
			ZeroMemory(&tmpInfo, sizeof(tagDataInfo));

			tmpInfo.index = i;
			tmpInfo.type = TYPE_A_IT_OIL;
			tmpInfo.value = RND->getFromIntTo(3, 7);

			vItemInfo.push_back(tmpInfo);
		}
		//bullets
		if (i == 11 || (i >= 16 && i < 20))
		{
			ZeroMemory(&tmpInfo, sizeof(tagDataInfo));

			tmpInfo.index = i;
			tmpInfo.type = TYPE_A_IT_BULLET;
			tmpInfo.value = RND->getFromIntTo(3, 10);

			vItemInfo.push_back(tmpInfo);
		}
	}

	//Data Save
	str2IntSave(vItemInfo, "itemData");
}


//Wall Info
void dataSave::wallSet()
{
	tagDataInfo tmpInfo;
	vItemInfo vItemInfo;

	int tileX = 16;
	int tileY = 16;

	for (int i = 0; i < tileY; ++i)
	{
		for (int j = 0; j < tileX; ++j)
		{
			if (i < 1)  //0번째 열
			{
				ZeroMemory(&tmpInfo, sizeof(tagDataInfo));

				if (j == 1 || j == 3 || j == 5 || j == 9)
				{
					tmpInfo.index = (i * tileX) + j;
					tmpInfo.type  = TYPE_A_WL_CENTER;
					tmpInfo.type2 = TYPE_A_WL_ARENDER;

					vItemInfo.push_back(tmpInfo);
				}
				else  
				{
					tmpInfo.index = (i * tileX) + j;
					tmpInfo.type  = TYPE_A_WL_EMPTY;
					tmpInfo.type2 = TYPE_A_WL_ARENDER;

					vItemInfo.push_back(tmpInfo);
				}
			}
			else if (i < 2)  //1번째 열
			{
				ZeroMemory(&tmpInfo, sizeof(tagDataInfo));

				if (j == 0)
				{
					tmpInfo.index = (i * tileX) + j;
					tmpInfo.type = TYPE_A_WL_CENTER;
					tmpInfo.type2 = TYPE_A_WL_ARENDER;

					vItemInfo.push_back(tmpInfo);
				}
				else if (j < 10)
				{
					tmpInfo.index = (i * tileX) + j;
					tmpInfo.type  = TYPE_A_WL_ORIGINAL;
					tmpInfo.type2 = TYPE_A_WL_ARENDER;

					vItemInfo.push_back(tmpInfo);
				}
				else
				{
					tmpInfo.index = (i * tileX) + j;
					tmpInfo.type = TYPE_A_WL_EMPTY;

					vItemInfo.push_back(tmpInfo);
				}
			}
			else if (i < 3)  //2번째 열
			{
				ZeroMemory(&tmpInfo, sizeof(tagDataInfo));

				if (j == 5 || j == 7 || j == 9 || j == 10 || j == 14)
				{
					tmpInfo.index = (i * tileX) + j;
					tmpInfo.type  = TYPE_A_NONE;
					tmpInfo.type2 = TYPE_A_WL_ARENDER;

					vItemInfo.push_back(tmpInfo);
				}
				else
				{
					tmpInfo.index = (i * tileX) + j;
					tmpInfo.type = TYPE_A_WL_EMPTY;

					vItemInfo.push_back(tmpInfo);
				}
			}
			else if (i < tileY)
			{
				if (j == 0 || j == 8)
				{
					tmpInfo.index = (i * tileX) + j;
					tmpInfo.type  = TYPE_A_WL_CENTER;

					vItemInfo.push_back(tmpInfo);
				}
				else if (j == 1 || j == 2 || j == 9 || j == 10)
				{
					tmpInfo.index = (i * tileX) + j;
					tmpInfo.type = TYPE_A_WL_EMPTY;

					vItemInfo.push_back(tmpInfo);
				}
			}
		}

	}

	//Data Save
	str2IntSave(vItemInfo, "wallData");
}


//Weapon Info
void dataSave::weaponSet()
{
	tagDataInfo tmpInfo;
	vItemInfo vItemInfo;

	int tileX = 17;
	int tileY = 14;

	for (int i = 0; i < tileY; ++i)
	{
		for (int j = 0; j < tileX; ++j)
		{
			if (i == 0)  //0번째 열
			{
				ZeroMemory(&tmpInfo, sizeof(tagDataInfo));

				if (j == 0 || j == 15 || j == 16)
				{
					tmpInfo.index = (i * tileX) + j;
					tmpInfo.type = TYPE_A_WP_BOMB;

					vItemInfo.push_back(tmpInfo);
				}
				else
				{
					tmpInfo.index = (i * tileX) + j;
					tmpInfo.type = TYPE_A_WP_GUN;

					vItemInfo.push_back(tmpInfo);
				}
			}
			else if (i == 11)  //11번째 열
			{
				ZeroMemory(&tmpInfo, sizeof(tagDataInfo));

				tmpInfo.index = (i * tileX) + j;
				tmpInfo.type = TYPE_A_WP_GUN;

				vItemInfo.push_back(tmpInfo);
			}

		}

	}

	//Data Save
	str2IntSave(vItemInfo, "weaponData");
}






//Save
void dataSave::txtSave(string saveFileName, vector<string> vStr)
{
	HANDLE file;

	int strSize = vStr.size() * 2 + 2;
	char buff[32];
	INIDATA->addData(saveFileName.c_str(), "vSize", itoa(strSize, buff, 10));
	INIDATA->iniSave("TileData");

	char* str = new char[strSize];
	DWORD write;

	//----------------------- 벡터정보 -----------------------
	ZeroMemory(str, sizeof(str));
	for (int i = 0; i < vStr.size(); i++)
	{
		strncat_s(str, strSize, vStr[i].c_str(), strSize - 2);
	}
	//--------------------------------------------------------


	//------------------------ 파일명 ------------------------
	char strFile[256];
	GetCurrentDirectory(256, strFile);   //현재 디렉토리 경로
	string tmpFileName;
	tmpFileName.append(strFile);		 //파일경로
	tmpFileName.append("\\map\\");		 //파일경로
	tmpFileName.append(saveFileName);    //파일명
	tmpFileName.append(".txt");			 //확장자
	//--------------------------------------------------------


	//----------------------- 파일저장 -----------------------
	file = CreateFile(tmpFileName.c_str(), GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, strSize, &write, NULL);
	//--------------------------------------------------------


	CloseHandle(file);
}


//Load Data
//                    파일명               인덱스넘버  DATA(1:TYPE | 2:TYPE2 | 3:VALUE)
int dataSave::txtLoad(string loadFileName, int index, int data)
{
	HANDLE file;
	
	int vSize = INIDATA->loadDataInterger("TileData", loadFileName.c_str(), "vSize");
	char* str = new char[vSize];
	DWORD read;

	//------------------------ 파일명 ------------------------
	char strFile[256];
	GetCurrentDirectory(256, strFile);   //현재 디렉토리 경로
	string tmpFileName;
	tmpFileName.append(strFile);		 //파일경로
	tmpFileName.append("\\map\\");		 //파일경로
	tmpFileName.append(loadFileName);    //파일명
	tmpFileName.append(".txt");			 //확장자
	//--------------------------------------------------------

	//----------------------- 파일로드 -----------------------
	file = CreateFile(tmpFileName.c_str(), GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, vSize, &read, NULL);

	CloseHandle(file);
	//--------------------------------------------------------

	//--------------------- 데이터 변환 ----------------------
	vString tmpVString;
	tmpVString = TXTDATA->charArraySeparation(str);

	tagDataInfo tempItemInfo;
	vItemInfo tmpVItemInfo;

	for (int i = 0; i < tmpVString.size(); ++i)
	{
		if (tmpVString[i] == "|")
		{
			//예외처리
			if (i + 1 >= tmpVString.size()) break;

			tempItemInfo.index = atoi(tmpVString[i + 1].c_str());
			tempItemInfo.type  = atoi(tmpVString[i + 2].c_str());
			tempItemInfo.type2 = atoi(tmpVString[i + 3].c_str());
			tempItemInfo.value = atoi(tmpVString[i + 4].c_str());

			tmpVItemInfo.push_back(tempItemInfo);
		}
	}
	//--------------------------------------------------------

	//데이터 로드후 임시벡터에 담기 -> 따로 분리 (임시벡터 -> 메모리상 저장해서 쓰기) || 멀티스레드

	//--------------------- 데이터 반환 ----------------------
	for (int i = 0; i < tmpVItemInfo.size(); ++i)
	{
		if (tmpVItemInfo[i].index == index)

		{
			switch (data)
			{
				case INFO_TYPE:
					return tmpVItemInfo[i].type;
				break;
				case INFO_TYPE2:
					return tmpVItemInfo[i].type2;
				break;
				case INFO_VALUE:
					return tmpVItemInfo[i].value;
				break;
			}
		}
	}
	//--------------------------------------------------------

	return -1;
}

void dataSave::str2IntSave(vItemInfo saveVector, string fileName)
{
	//int -> string
	char str[128];
	vString vString;

	for (int i = 0; i < saveVector.size(); ++i)
	{
		//칸막이
		if (i == 0) strcatAdd(vString, "|,");

		//index
		ZeroMemory(&str, sizeof(str));
		itoa(saveVector[i].index, str, 10);
		vString.push_back(str);
		strcatAdd(vString, ",");  //,

		//type
		ZeroMemory(&str, sizeof(str));
		itoa(saveVector[i].type, str, 10);
		vString.push_back(str);
		strcatAdd(vString, ",");  //,

		//type2
		ZeroMemory(&str, sizeof(str));
		itoa(saveVector[i].type2, str, 10);
		vString.push_back(str);
		strcatAdd(vString, ",");  //,

		//value
		ZeroMemory(&str, sizeof(str));
		itoa(saveVector[i].value, str, 10);
		vString.push_back(str);
		strcatAdd(vString, ",");  //,

		//칸막이
		strcatAdd(vString, "|,");
	}

	txtSave(fileName, vString);
}


void dataSave::strcatAdd(vString& vStr, string inStr)
{
	char catStr[128];
	ZeroMemory(&catStr, sizeof(catStr));
	strcat(catStr, inStr.c_str());

	vStr.push_back(catStr);
}

