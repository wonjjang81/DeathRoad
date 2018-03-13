#include "stdafx.h"
#include "playGround.h"


void playGround::resourceAdd()
{
	//��ư
	IMAGEMANAGER->addFrameImage("������ư", L".//source//image//mapTool//mapTool_button.png", 44, 64, 1, 4);
	IMAGEMANAGER->addFrameImage("������ưŸ��Ʋ��", L".//source//image//mapTool//mapTool_btn_titleTab.png", 40, 180, 2, 9);
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
	IMAGEMANAGER->addFrameImage("����Ÿ�Ϲٴ�", L".//source//image//mapTool//tile//floors.png", 64, 368, dFrame(64, 16), dFrame(368, 16));
	IMAGEMANAGER->addFrameImage("����Ÿ�ϰŸ�", L".//source//image//mapTool//tile//street.png", 256, 512, 16, 32);
	IMAGEMANAGER->addFrameImage("����Ÿ�Ϻ���1", L".//source//image//mapTool//tile//buildings.png", 224, 448, dFrame(224, 112), dFrame(512, 112));
	IMAGEMANAGER->addFrameImage("����Ÿ�Ϻ���2", L".//source//image//mapTool//tile//city_florida.png", 224, 768, dFrame(224, 112), dFrame(768, 128));
	IMAGEMANAGER->addFrameImage("����Ÿ�ϰ���1", L".//source//image//mapTool//tile//dr2c_housefurniture_32px.png", 256, 960, dFrame(256, 32), dFrame(960, 32));
}


//�� ������ �ѹ�       �̹�������  �������ȼ�
int playGround::dFrame(int length, int pixel)
{
	int divisionFrame = length / pixel;
	return divisionFrame;
}