#pragma once

//Ÿ�� �԰�
#define TILE_SIZEX 16
#define TILE_SIZEY 16

//Ÿ�ϰ���
#define TILEX 50
#define TILEY 50

//Ÿ�� �� ������
#define TILE_TOTAL_SIZEX TILE_SIZEX * TILEX
#define TILE_TOTAL_SIZEY TILE_SIZEY * TILEY

//Ÿ�ϼ���
#define SAMPLETILEX 15
#define SAMPLETILEY 15

//RGB
#define WHITE	 RGB(255,255,255)
#define BLACK	 RGB(0  ,0  ,0)
#define BLUE	 RGB(255,0  ,0)
#define GREEN	 RGB(0  ,255,0)
#define RED		 RGB(0  ,0  ,255)
#define CYAN	 RGB(255,255,0)
#define MAGENTA  RGB(255,0  ,255)
#define YELLOW   RGB(0  ,255,255)

enum TILE_TYPE
{
	TYPE_NONE,
	TYPE_TERRAIN,
	TYPE_BUILDING,
	TYPE_ROAD,
	TYPE_FURNITURE,
	TYPE_ITEM,
	TYPE_WEAPON,
	TYPE_ENEMY,
	TYPE_WALL,
	TYPE_DOOR
};

//��Ÿ�Ӽ�
enum ATTRIBUTE
{
	ATTR_CRECT_NONE,      //�浹��Ʈ ����
	ATTR_CRECT_CENTER,    //�浹��Ʈ �����簢��
	ATTR_CRECT_ORIGINAL,  //�浹��Ʈ Ÿ�ϻ�����
	ATTR_CRECT_RESIZE,    //�浹��Ʈ ����

	ATTR_AFTERRENDER      //Z-order
};

//�ߺ���ġ ����
enum OVERLAPPOSITION
{
	OVERPO_NO,
	OVERPO_YES
};




