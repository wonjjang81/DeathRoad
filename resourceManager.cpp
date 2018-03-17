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

	//==================================================================== 타일 ===================================================================
	//빌딩
	IMAGEMANAGER->addFrameImage("맵툴타일빌딩1", L".//source//image//mapTool//tile//building//buildings.png", 224, 448, dFrame(224, 112), dFrame(512, 112));
	IMAGEMANAGER->addFrameImage("맵툴타일빌딩2", L".//source//image//mapTool//tile//building//city_florida.png", 224, 768, dFrame(224, 112), dFrame(768, 128));
	IMAGEMANAGER->addFrameImage("맵툴타일문", L".//source//image//mapTool//tile//building//doors.png", 256, 96, dFrame(256, 16), dFrame(96, 16));
	IMAGEMANAGER->addFrameImage("맵툴타일기계", L".//source//image//mapTool//tile//building//special32.png", 256, 768, dFrame(256, 16), dFrame(768, 16));
	IMAGEMANAGER->addFrameImage("맵툴타일벽", L".//source//image//mapTool//tile//building//walls.png", 256, 256, dFrame(256, 16), dFrame(256, 16));
	//가구
	IMAGEMANAGER->addFrameImage("맵툴타일가구1", L".//source//image//mapTool//tile//furniture//dr2c_housefurniture_32px.png", 256, 960, dFrame(256, 32), dFrame(960, 32));
	IMAGEMANAGER->addFrameImage("맵툴타일책장", L".//source//image//mapTool//tile//furniture//shelves.png", 256, 128, dFrame(256, 16), dFrame(128, 16));
	//아이템
	IMAGEMANAGER->addFrameImage("맵툴타일아이템", L".//source//image//mapTool//tile//item//dr2c_loot16.png", 128, 48, dFrame(128, 16), dFrame(48, 16));
	//길
	IMAGEMANAGER->addFrameImage("맵툴타일거리", L".//source//image//mapTool//tile//road//street.png", 256, 512, dFrame(256, 16), dFrame(512, 16));
	IMAGEMANAGER->addFrameImage("맵툴타일나무", L".//source//image//mapTool//tile//road//trees_96px.png", 480, 480, dFrame(480, 96), dFrame(480, 96));
	//지형
	IMAGEMANAGER->addFrameImage("맵툴타일바닥", L".//source//image//mapTool//tile//terrain//floors.png", 128, 352, dFrame(128, 16), dFrame(352, 16));
	//무기
	IMAGEMANAGER->addFrameImage("맵툴타일무기", L".//source//image//mapTool//tile//weapon//dr2c_weapons.png", 128, 448, dFrame(128, 8), dFrame(448, 32));

}


//총 프레임 넘버       이미지길이  프레임픽셀
int playGround::dFrame(int length, int pixel)
{
	int divisionFrame = length / pixel;
	return divisionFrame;
}