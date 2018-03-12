#include "stdafx.h"
#include "playGround.h"


void playGround::resourceAdd()
{
	//��ư
	IMAGEMANAGER->addFrameImage("������ư", L".//source//image//mapTool//mapTool_button.png", 44, 64, 1, 4);
	IMAGEMANAGER->addFrameImage("������ưŸ��Ʋ��", L".//source//image//mapTool//mapTool_btn_titleTab.png", 40, 160, 2, 8);
	IMAGEMANAGER->addFrameImage("������ưȭ��", L".//source//image//mapTool//mapTool_menu_arrow.png", 28, 20, 2, 2);

	//�޴�
	IMAGEMANAGER->addImage("����â", L".//source//image//mapTool//mapTool_editor_window.png", 280, 720);
	IMAGEMANAGER->addImage("�����޴�â����", L".//source//image//mapTool//mapTool_menu_window_terrain.png", 270, 670);
	IMAGEMANAGER->addImage("�����޴�â����", L".//source//image//mapTool//mapTool_menu_window_builiding.png", 270, 670);
	IMAGEMANAGER->addImage("�����޴�â������", L".//source//image//mapTool//mapTool_menu_window_item.png", 270, 670);
	IMAGEMANAGER->addImage("�����޴�â��", L".//source//image//mapTool//mapTool_menu_window_enemy.png", 270, 670);
	IMAGEMANAGER->addImage("�����޴�â����", L".//source//image//mapTool//mapTool_menu_window_weapon.png", 270, 670);
	IMAGEMANAGER->addImage("�����޴�â����", L".//source//image//mapTool//mapTool_menu_window_setting.png", 270, 670);

	//Ÿ��
	IMAGEMANAGER->addFrameImage("����Ÿ�Ϲٴ�", L".//source//image//mapTool//tile//floors.png", 128, 352, 8, 22);
	IMAGEMANAGER->addFrameImage("����Ÿ�ϰŸ�", L".//source//image//mapTool//tile//street.png", 256, 512, 16, 32);
	IMAGEMANAGER->addFrameImage("����Ÿ�Ϻ���A", L".//source//image//mapTool//tile//buildings.png", 224, 512, dFrame(224, 16), dFrame(512, 16));
	IMAGEMANAGER->addFrameImage("����Ÿ�Ϻ���F", L".//source//image//mapTool//tile//city_florida.png", 224, 768, dFrame(224, 16), dFrame(768, 16));
}


//�� ������ �ѹ�       �̹�������  �������ȼ�
int playGround::dFrame(int length, int pixel)
{
	int divisionFrame = length / pixel;
	return divisionFrame;
}