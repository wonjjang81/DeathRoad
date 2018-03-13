#include "stdafx.h"
#include "playGround.h"


void playGround::resourceAdd()
{
	//버튼
	IMAGEMANAGER->addFrameImage("맵툴버튼", L".//source//image//mapTool//mapTool_button.png", 44, 64, 1, 4);
	IMAGEMANAGER->addFrameImage("맵툴버튼타이틀탭", L".//source//image//mapTool//mapTool_btn_titleTab.png", 40, 180, 2, 9);
	IMAGEMANAGER->addFrameImage("맵툴버튼화살", L".//source//image//mapTool//mapTool_menu_arrow.png", 28, 20, 2, 2);

	//메뉴
	IMAGEMANAGER->addImage("맵툴창", L".//source//image//mapTool//mapTool_editor_window.png", 280, 720);
	IMAGEMANAGER->addImage("맵툴메뉴창지형", L".//source//image//mapTool//mapTool_menu_window_terrain.png", 270, 670);
	IMAGEMANAGER->addImage("맵툴메뉴창빌딩", L".//source//image//mapTool//mapTool_menu_window_builiding.png", 270, 670);
	IMAGEMANAGER->addImage("맵툴메뉴창아이템", L".//source//image//mapTool//mapTool_menu_window_item.png", 270, 670);
	IMAGEMANAGER->addImage("맵툴메뉴창적", L".//source//image//mapTool//mapTool_menu_window_enemy.png", 270, 670);
	IMAGEMANAGER->addImage("맵툴메뉴창무기", L".//source//image//mapTool//mapTool_menu_window_weapon.png", 270, 670);
	IMAGEMANAGER->addImage("맵툴메뉴창셋팅", L".//source//image//mapTool//mapTool_menu_window_setting.png", 270, 670);

	//타일
	IMAGEMANAGER->addFrameImage("맵툴타일바닥", L".//source//image//mapTool//tile//floors.png", 64, 368, dFrame(64, 16), dFrame(368, 16));
	IMAGEMANAGER->addFrameImage("맵툴타일거리", L".//source//image//mapTool//tile//street.png", 256, 512, 16, 32);
	IMAGEMANAGER->addFrameImage("맵툴타일빌딩1", L".//source//image//mapTool//tile//buildings.png", 224, 448, dFrame(224, 112), dFrame(512, 112));
	IMAGEMANAGER->addFrameImage("맵툴타일빌딩2", L".//source//image//mapTool//tile//city_florida.png", 224, 768, dFrame(224, 112), dFrame(768, 128));
	IMAGEMANAGER->addFrameImage("맵툴타일가구1", L".//source//image//mapTool//tile//dr2c_housefurniture_32px.png", 256, 960, dFrame(256, 32), dFrame(960, 32));
}


//총 프레임 넘버       이미지길이  프레임픽셀
int playGround::dFrame(int length, int pixel)
{
	int divisionFrame = length / pixel;
	return divisionFrame;
}