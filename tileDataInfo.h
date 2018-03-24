#pragma once

#define ITEMSIZE 8 * 3
#define WALLSIZE 16 * 16

enum TYPE_ATTRIBUTE
{
	TYPE_A_NONE,

	TYPE_A_TR_START,		//������

	TYPE_A_FT_ITEM,			//������ ����

	TYPE_A_IT_DRUG,			//��ǰ��
	TYPE_A_IT_FOOD,			//���ķ�
	TYPE_A_IT_OIL,			//�⸧��
	TYPE_A_IT_BULLET,		//�Ѿ˷�

	TYPE_A_WL_EMPTY,		//��׸�
	TYPE_A_WL_CENTER,		//�߾Ӻ�
	TYPE_A_WL_ORIGINAL,		//��
	TYPE_A_WL_ARENDER,		//After������

	TYPE_A_WP_GUN,			//�ѷ� (�Ѿ�/ȭ�� �߻�)
	TYPE_A_WP_BOMB,			//��ź��
	TYPE_A_WP_SWORD,		//Į�� (�ֵθ��� ��)
	TYPE_A_WP_MACHINE 		//���� (�⸧�Һ�)
};

enum TXTDATAINFO
{
	INFO_INDEX,
	INFO_TYPE,
	INFO_TYPE2,
	INFO_VALUE
};

struct tagDataInfo
{
	int index;
	int type;
	int type2;
	int value;
};


