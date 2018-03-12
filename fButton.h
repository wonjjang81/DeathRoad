#pragma once
#include "gameNode.h"
#include <vector>


//��ư ���¿� ���� ����
enum BUTTONSTATE
{
	BUTTONSTATE_NULL,		//�ʱ�ȭ ����
	BUTTONSTATE_UP,			//��ư�� �ö�� ��
	BUTTONSTATE_DOWN		//��ư�� ������ ��
};

struct tagButton
{
	image* img;					//��ư �̹���
	float x, y;					//��ư ��ġ
	float centerX, centerY;		//��ư �߽���
	LPCWSTR titleText;          //��ư ���� 
	float textSize;				//��ư ���� ũ��    
	BUTTONSTATE direction;		//��ư ����
	RECT rc;                    //��ư ��Ʈ
	POINT btnDownFrame;         //��ư �ٿ� �̹��� ������
	POINT btnUPFrame;           //��ư ��   �̹��� ������
	float scale;                //��ư ������
	bool isOn;                  //��ư On/Off
	bool ptIn;                  //��ư�ȿ� Ŀ���� �ֳ���?
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
