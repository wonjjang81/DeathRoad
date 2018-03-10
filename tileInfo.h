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

enum TILE_TYPE
{
	TYPE_TERRAIN,
	TYPE_BULIDING,
	TYPE_ITEM,
	TYPE_WEAPON,
	TYPE_ENEMY,
	TYPE_NONE
};

//�����Ӽ�
enum TERRAIN
{
	TR_LAND,
	TR_STREET,
	TR_GRASS,
	TR_WALL,
	TR_HILL,
	TR_NONE
};

//������ ��ü (Ÿ�� �Ұ���)
enum FIX_OBJECT
{
	FOBJ_TREE, 
	FOBJ_HOUSE_BOTTOM, FOBJ_HOUSE_TOP, FOBJ_HOUSE_DOOR,
	FOBJ_TREE_BOTTOM, FOBJ_TREE_TOP,
	FOBJ_OBSTACLE,
	FOBJ_CAR,
	FOBJ_SHELVES,
	FOBJ_FENCE,
	FOBJ_FURNITURE,
	FOBJ_TRASH,
	FOBJ_NONE
};

//������ �� �ִ� ��ü (Ÿ�� ����)
enum MOVE_OBJECT
{
	MOBJ_OBSTACLE,
	MOBJ_CAR,
	MOBJ_FURNITURE,
	MOBJ_NONE
};

//������
enum ITEM
{
	ITEM_HEAL,    //��ǰ��
	ITEM_FOOD,    //���ķ�
	ITEM_OIL,     //�⸧��
	ITEM_BULLET,  //�Ѿ˷�
	ITEM_NONE
};

//����
enum WEAPON
{
	WP_GUN,		//�ѷ�
	WP_BOMB,	//��ź��
	WP_SWORD,	//Į��
	WP_ROD,		//â�� (�ֵθ��� �ִ°�)
	WP_AXE,		//������
	WP_BOW,		//Ȱ��
	WP_MACHINE,	//���� (�⸧�Һ�)
	WP_NONE
};

//��Ÿ�Ӽ�
enum ATTRIBUTE
{
	ATTR_MOVE,
	ATTR_UNMOVE,
	ATTR_AFTER_RENDER,
	ATTR_NONE
};

//������
enum POSITION
{
	POS_START,
	POS_END,
	POS_NONE
};