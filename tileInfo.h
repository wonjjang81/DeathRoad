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
	TYPE_NONE,
	TYPE_TERRAIN,
	TYPE_BUILDING,
	TYPE_ROAD,
	TYPE_FURNITURE,
	TYPE_ITEM,
	TYPE_WEAPON,
	TYPE_ENEMY
};

//�����Ӽ�
enum TERRAIN
{
	TR_NONE,
	TR_LAND,
	TR_STREET,
	TR_GRASS,
	TR_WALL,
	TR_HILL
};

//������ ��ü (Ÿ�� �Ұ���)
enum FIX_OBJECT
{
	FOBJ_NONE,
	FOBJ_TREE, 
	FOBJ_HOUSE_BOTTOM, FOBJ_HOUSE_TOP, FOBJ_HOUSE_DOOR,
	FOBJ_TREE_BOTTOM, FOBJ_TREE_TOP,
	FOBJ_OBSTACLE,
	FOBJ_CAR,
	FOBJ_SHELVES,
	FOBJ_FENCE,
	FOBJ_FURNITURE,
	FOBJ_TRASH
};

//������ �� �ִ� ��ü (Ÿ�� ����)
enum MOVE_OBJECT
{
	MOBJ_NONE,
	MOBJ_OBSTACLE,
	MOBJ_CAR,
	MOBJ_FURNITURE
};

//������
enum ITEM
{
	ITEM_NONE,
	ITEM_HEAL,    //��ǰ��
	ITEM_FOOD,    //���ķ�
	ITEM_OIL,     //�⸧��
	ITEM_BULLET   //�Ѿ˷�
};

//����
enum WEAPON
{
	WP_NONE,
	WP_GUN,		//�ѷ�
	WP_BOMB,	//��ź��
	WP_SWORD,	//Į��
	WP_ROD,		//â�� (�ֵθ��� �ִ°�)
	WP_AXE,		//������
	WP_BOW,		//Ȱ��
	WP_MACHINE 	//���� (�⸧�Һ�)
};

//��Ÿ�Ӽ�
enum ATTRIBUTE
{
	ATTR_NONE,
	ATTR_MOVE,
	ATTR_UNMOVE,
	ATTR_AFTER_RENDER,

	//�浹 ��Ʈ ������
	ATTR_WALL_NONE,   
	ATTR_WALL_LEFT,
	ATTR_WALL_TOP,
	ATTR_WALL_RIGHT,
	ATTR_WALL_BOTTOM,
	ATTR_DOOR
};

//������
enum POSITION
{
	POS_NONE,
	POS_START,
	POS_END
};

//�ߺ���ġ ����
enum OVERLAPPOSITION
{
	OVERPO_NO,
	OVERPO_YES
};