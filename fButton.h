#pragma once
#include "gameNode.h"
#include <vector>


//버튼 상태에 대한 정의
enum BUTTONSTATE
{
	BUTTONSTATE_NULL,		//초기화 상태
	BUTTONSTATE_UP,			//버튼이 올라올 때
	BUTTONSTATE_DOWN		//버튼이 눌러질 때
};

struct tagButton
{
	image* img;					//버튼 이미지
	float x, y;					//버튼 위치
	float centerX, centerY;		//버튼 중심점
	LPCWSTR titleText;          //버튼 제목 
	float textSize;				//버튼 제목 크기    
	BUTTONSTATE direction;		//버튼 상태
	RECT rc;                    //버튼 렉트
	POINT btnDownFrame;         //버튼 다운 이미지 프레임
	POINT btnUPFrame;           //버튼 업   이미지 프레임
	float scale;                //버튼 스케일
	bool isOn;                  //버튼 On/Off
	bool ptIn;                  //버튼안에 커서가 있나요?
};


class fButton : public gameNode
{
private:
	tagButton _button;


public:
	//================================ button ===============================
	HRESULT init(const char* imageName , LPCWSTR titleText, float textSize, float x, float y, POINT downFrame, POINT upFrame, float scale);
	void release();
	void update();
	void render();
	//================================ button ===============================

	//================================ getter ===============================
	inline bool getBtnOn() { return _button.isOn; }
	inline void setBtnOff(bool btnoff) { _button.isOn = btnoff; }
	inline bool getPtIn() { return _button.ptIn; }

	fButton();
	~fButton();
};
