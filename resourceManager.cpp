#include "stdafx.h"
#include "playGround.h"


void playGround::resourceAdd()
{
	IMAGEMANAGER->addFrameImage("������ư", L".//source//image//mapTool//mapTool_button.png", 44, 64, 1, 4);
	IMAGEMANAGER->addImage("����â", L".//source//image//mapTool//mapTool_editor_window.png", 280, 720);
	IMAGEMANAGER->addFrameImage("������ưŸ��Ʋ��", L".//source//image//mapTool//mapTool_btn_titleTab.png", 40, 160, 2, 8);
	IMAGEMANAGER->addImage("�����޴�â����", L".//source//image//mapTool//mapTool_menu_window_terrain.png", 270, 670);
	IMAGEMANAGER->addImage("�����޴�â����", L".//source//image//mapTool//mapTool_menu_window_builiding.png", 270, 670);
	IMAGEMANAGER->addImage("�����޴�â������", L".//source//image//mapTool//mapTool_menu_window_item.png", 270, 670);
	IMAGEMANAGER->addImage("�����޴�â��", L".//source//image//mapTool//mapTool_menu_window_enemy.png", 270, 670);
	IMAGEMANAGER->addImage("�����޴�â����", L".//source//image//mapTool//mapTool_menu_window_weapon.png", 270, 670);
	IMAGEMANAGER->addImage("�����޴�â����", L".//source//image//mapTool//mapTool_menu_window_setting.png", 270, 670);

	IMAGEMANAGER->addFrameImage("����Ÿ�Ϲٴ�", L".//source//image//mapTool//tile//floors.png", 128, 352, 8, 22);
}