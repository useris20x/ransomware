/*
�Q�[���p�̃E�B���h�E���N���X����������
*/
#pragma once
#include<Windows.h>
#include<tchar.h>
#include"Input.h"

namespace Inferno
{
class SimpleWindow
{
public:
	//�萔
	enum WindowPostion
	{
		Center,
		Left,
		Right,
	};

public:
	SimpleWindow();
	~SimpleWindow();
	virtual bool Initialize();
	void Resize(const int width, const int height);
	void Show() const; //���݂̈ʒu�ƃT�C�Y�ŃE�B���h�E���A�N�e�B�u�ɂ���
	void SetTitleText(LPCTSTR str) const;
	void SetPos(const WindowPostion x, const WindowPostion y);

	HWND GetHWND() const;
	int GetWindowWidth() const;
	int GetWindowHeight() const;
	int GetClientWidth() const;
	int GetClientHeight() const;

	virtual bool Terminate();

private:
	WNDCLASSEX m_wc;
	HWND m_hWnd; //���g���w���E�B���h�E�n���h��

	//�E�B���h�E�g���܂߂��̈�i�E�B���h�E�̈�j
	int m_windowWidth;
	int m_windowHeight;

	//�E�B���h�E�g���������̈�(�N���C�A���g�̈�)
	int m_clientWidth;
	int m_clientHeight;
	


private:
	SimpleWindow(SimpleWindow& w) = delete;
	SimpleWindow operator=(SimpleWindow& w) = delete;
};
}