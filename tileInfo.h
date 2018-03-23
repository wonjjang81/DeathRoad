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
};

//�ߺ���ġ ����
enum OVERLAPPOSITION
{
	OVERPO_NO,
	OVERPO_YES
};

//������
enum TYPE_ATTRIBUTE
{
	TYPE_A_NONE,

	TYPE_A_TR_START,		//������

	TYPE_A_IT_HEAL,			//��ǰ��
	TYPE_A_IT_FOOD,			//���ķ�
	TYPE_A_IT_OIL,			//�⸧��
	TYPE_A_IT_BULLET,		//�Ѿ˷�

	TYPE_A_WP_GUN,			//�ѷ�
	TYPE_A_WP_BOMB,			//��ź��
	TYPE_A_WP_SWORD,		//Į��
	TYPE_A_WP_ROD,			//â�� (�ֵθ��� �ִ°�)
	TYPE_A_WP_AXE,			//������
	TYPE_A_WP_BOW,			//Ȱ��
	TYPE_A_WP_MACHINE 		//���� (�⸧�Һ�)
};

