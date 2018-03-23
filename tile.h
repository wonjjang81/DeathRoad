#pragma once
#include "gameNode.h"
#include "tileInfo.h"

#include "dataSave.h"
#include "tileDataInfo.h"

#include <vector>
#include <map>

//Ÿ�Ϲ���
enum TILE_DIRECTION
{
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_NONE
};

//��ĿŸ��
enum ANCHOR_TYPE
{
	ANCHOR_NONE,
	ANCHOR_LEFTTOP,
	ANCHOR_CENTER,
	ANCHOR_BOTTOMCENTER
};

struct tagTile
{
	RECT      rc;
	image*    img;
	TILE_TYPE tileType;       //Ÿ��
	ATTRIBUTE attribute;      //�Ӽ�
	TYPE_ATTRIBUTE typeAtt;   //Ÿ�Ժ� �Ӽ�
	TYPE_ATTRIBUTE typeAtt2;  //Ÿ�Ժ� �Ӽ�
	ANCHOR_TYPE anchorType;   //��ĿŸ��
	OVERLAPPOSITION overPos;  //�ߺ���ġ ����
	TCHAR imgName[64];
	int index;
	float x, y;
	float gapX, gapY;
	float scale;
	int frameX;
	int frameY;
	float moveX;
	float moveY;
	float centerX, centerY;   //��Ʈ �߽���ǥ
	float reWidth, reHeight;  //��Ʈ ������ �缳��(16 X 16)
	int id;                   //tile ID
};

struct tagSampleTile
{
	RECT rc;
	int index;
	int frameX;
	int frameY;
};

struct tagCurrentTile
{
	int index;
	float x;
	float y;
};

class tile : public gameNode
{
private:
	typedef vector<tagTile>				 vTile;
	typedef vector<tagTile>::iterator	 viTile;

	typedef map<string, vTile>           mTile;
	typedef map<string, vTile>::iterator iterTile;
private:
	mTile _mTile;

	//DataInfo
	dataSave* _tileData;


public:
	void tileSetup(string tileName, float x, float y, ATTRIBUTE attribute, TILE_TYPE tileType, TYPE_ATTRIBUTE typeAttr, ANCHOR_TYPE anchor, OVERLAPPOSITION overPosition, float scale);
	void tileRender(string tileName, float moveX = 0, float moveY = 0);
	tagTile tileSelect(string tileName, float moveX = 0, float moveY = 0);
	void tileDrawFillRc(tagTile selectTile, COLORREF color, float opacity, float moveX = 0, float moveY = 0);
	void setTileAttribute(tagTile selectTile, ATTRIBUTE attribute);
	void setTileType(tagTile selectTile, TILE_TYPE tileType);

	void setTileAnchor(tagTile& tile, ANCHOR_TYPE anchor);  //��ĿŸ�Ժ� �̹��� Render ������ ����

	TYPE_ATTRIBUTE loadTileTypeAttribute(TILE_TYPE tileType, int index, int typeNum = 1);

	tile();
	~tile();
};

