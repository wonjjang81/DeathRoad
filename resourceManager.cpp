#include "stdafx.h"
#include "playGround.h"


void playGround::resourceAdd()
{
	IMAGEMANAGER->addImage("Ÿ��Ʋ", L".//source//image//Ui//dr2c_title_small.png", WINSIZEX / 2, WINSIZEY / 2, 144, 48);

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

	//==================================================================== Ÿ�� ===================================================================
	//����
	IMAGEMANAGER->addFrameImage("����Ÿ�Ϻ���1", L".//source//image//mapTool//tile//building//buildings.png", 224, 448, dFrame(224, 112), dFrame(512, 112));
	IMAGEMANAGER->addFrameImage("����Ÿ�Ϻ���2", L".//source//image//mapTool//tile//building//city_florida.png", 224, 768, dFrame(224, 112), dFrame(768, 128));
	IMAGEMANAGER->addFrameImage("����Ÿ�Ϲ�", L".//source//image//mapTool//tile//building//doors.png", 256, 96, dFrame(256, 16), dFrame(96, 16));
	IMAGEMANAGER->addFrameImage("����Ÿ�ϱ��", L".//source//image//mapTool//tile//building//special32.png", 256, 768, dFrame(256, 16), dFrame(768, 16));
	IMAGEMANAGER->addFrameImage("����Ÿ�Ϻ�", L".//source//image//mapTool//tile//building//walls.png", 256, 256, dFrame(256, 16), dFrame(256, 16));
	//����
	IMAGEMANAGER->addFrameImage("����Ÿ�ϰ���1", L".//source//image//mapTool//tile//furniture//dr2c_housefurniture_32px.png", 256, 960, dFrame(256, 32), dFrame(960, 32));
	IMAGEMANAGER->addFrameImage("����Ÿ��å��", L".//source//image//mapTool//tile//furniture//shelves.png", 256, 128, dFrame(256, 16), dFrame(128, 16));
	//������
	IMAGEMANAGER->addFrameImage("����Ÿ�Ͼ�����", L".//source//image//mapTool//tile//item//dr2c_loot16.png", 128, 48, dFrame(128, 16), dFrame(48, 16));
	//��
	IMAGEMANAGER->addFrameImage("����Ÿ�ϰŸ�", L".//source//image//mapTool//tile//road//street.png", 256, 512, dFrame(256, 16), dFrame(512, 16));
	IMAGEMANAGER->addFrameImage("����Ÿ�ϳ���", L".//source//image//mapTool//tile//road//trees_96px.png", 480, 480, dFrame(480, 96), dFrame(480, 96));
	//����
	IMAGEMANAGER->addFrameImage("����Ÿ�Ϲٴ�", L".//source//image//mapTool//tile//terrain//floors.png", 128, 352, dFrame(128, 16), dFrame(352, 16));
	//����
	IMAGEMANAGER->addFrameImage("����Ÿ�Ϲ���", L".//source//image//mapTool//tile//weapon//dr2c_weapons.png", 128, 448, dFrame(128, 8), dFrame(448, 32));

	//==================================================================== ĳ���� ==================================================================
	//����
	IMAGEMANAGER->addFrameImage("femaleHead", L".//source//image//char//dr2c_female_heads.png", 192, 144, dFrame(192, 24), dFrame(144, 24));
	IMAGEMANAGER->addFrameImage("femaleBody", L".//source//image//char//dr2c_female_bodies.png", 480, 408, dFrame(480, 24), dFrame(408, 24));
	IMAGEMANAGER->addFrameImage("femaleGlass", L".//source//image//char//dr2c_female_glasses.png", 96, 336, dFrame(96, 24), dFrame(336, 24));
	IMAGEMANAGER->addFrameImage("femaleHair", L".//source//image//char//dr2c_female_hair.png", 240, 144, dFrame(240, 24), dFrame(144, 24));
	IMAGEMANAGER->addFrameImage("femaleHats", L".//source//image//char//dr2c_female_hats.png", 144, 216, dFrame(144, 24), dFrame(216, 24));

	//==================================================================== ��ƼŬ ==================================================================
	IMAGEMANAGER->addFrameImage("��ƼŬ", L".//source//image//mapTool//tile//particle//dr2c_particles.png", 256, 192, dFrame(256, 16), dFrame(192, 16));

}


//�� ������ �ѹ�       �̹�������  �������ȼ�
int playGround::dFrame(int length, int pixel)
{
	int divisionFrame = length / pixel;
	return divisionFrame;
}