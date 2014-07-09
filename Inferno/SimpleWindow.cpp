#include"SimpleWindow.h"
#include"Input.h"
#include<Windows.h>
#include<tchar.h>
#include"MyException.h"
#include"..\TString.h"
#include"MyTypes.h"
#include"..\resource.h"

extern Inferno::Input* g_GlobalInput; //�Ƃ肠����

namespace
{
LRESULT WINAPI SimpleWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
}
LPCTSTR className = TEXT("SimpleWindow");

namespace Inferno
{
SimpleWindow::SimpleWindow()
{
}

SimpleWindow::~SimpleWindow()
{
	UnregisterClass(className, m_wc.hInstance);
}

bool SimpleWindow::Initialize()
{
	//WindowClass�ݒ�
	m_wc.cbSize = sizeof(WNDCLASSEX);
	m_wc.style = CS_CLASSDC | CS_HREDRAW | CS_VREDRAW; //CS_CLASSDC:�S�ẴE�B���h�E�������f�o�C�X�R���e�L�X�g�����L����
	m_wc.lpfnWndProc = SimpleWindowProc;
	m_wc.cbClsExtra = 0L;
	m_wc.cbWndExtra = 0L;
	m_wc.hInstance = GetModuleHandle(NULL);
	m_wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	m_wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	m_wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	m_wc.lpszMenuName = NULL;
	m_wc.lpszClassName = className;
	m_wc.hIconSm = NULL;
	//WindowClass�o�^
	if (!RegisterClassEx(&m_wc))
	{
		throw Inferno::CreationFailed(TEXT("�E�B���h�E�N���X"));
	}

	//�E�B���h�E�𐶐�
	m_hWnd = CreateWindow(className, TEXT("SimpleWindow"),
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX, //|WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, //�E�B���h�E�ʒu
		CW_USEDEFAULT, CW_USEDEFAULT, //�E�B���h�E�T�C�Y
		GetDesktopWindow(), //�����͒���
		NULL, m_wc.hInstance, NULL);
	if (m_hWnd == NULL)
	{
		throw Inferno::CreationFailed(TEXT("�E�B���h�E"));
	}

	this->Resize(800, 600);

	//::SetProcessDPIAware();

	return true;
}

void SimpleWindow::Resize(const int width, const int height)
{
	// �E�B���h�E�T�C�Y���Đݒ肷��
	RECT rect;
	int ww, wh;
	int cw, ch;
	// �N���C�A���g�̈�̊O�̕����v�Z
	GetClientRect(m_hWnd, &rect);		// �N���C�A���g�����̃T�C�Y�̎擾
	cw = rect.right - rect.left;	// �N���C�A���g�̈�O�̉������v�Z
	ch = rect.bottom - rect.top;	// �N���C�A���g�̈�O�̏c�����v�Z

	// �E�C���h�E�S�̂̉����̕����v�Z
	GetWindowRect(m_hWnd, &rect);		// �E�C���h�E�S�̂̃T�C�Y�擾
	ww = rect.right - rect.left;	// �E�C���h�E�S�̂̕��̉������v�Z
	wh = rect.bottom - rect.top;	// �E�C���h�E�S�̂̕��̏c�����v�Z
	ww = ww - cw;					// �N���C�A���g�̈�ȊO�ɕK�v�ȕ�
	wh = wh - ch;					// �N���C�A���g�̈�ȊO�ɕK�v�ȍ���

	// �E�B���h�E�T�C�Y�̍Čv�Z
	ww = width + ww;			// �K�v�ȃE�C���h�E�̕�
	wh = height + wh;		// �K�v�ȃE�C���h�E�̍���

	// �E�C���h�E�T�C�Y�̍Đݒ�
	SetWindowPos(m_hWnd, HWND_TOP, 0, 0, ww, wh, SWP_NOMOVE);

	m_windowHeight = wh;
	m_windowWidth = ww;
	m_clientHeight = height;
	m_clientWidth = width;
}

void SimpleWindow::SetPos(const WindowPostion x, const WindowPostion y)
{
	// �E�C���h�E�S�̂̉����̕����v�Z
	RECT rect;
	GetWindowRect(m_hWnd, &rect);		// �E�C���h�E�S�̂̃T�C�Y�擾
	const int ww = rect.right - rect.left;	// �E�C���h�E�S�̂̕��̉������v�Z
	const int wh = rect.bottom - rect.top;	// �E�C���h�E�S�̂̕��̏c�����v�Z

	//result
	int rx = 0;
	int ry = 0;

	//�ʒu�����W�ɒ���
	switch (x)
	{
	case Center:
		rx = (GetSystemMetrics(SM_CXSCREEN) - ww) / 2;
		if (rx < 0) rx=0; //��ʂ������������ꍇ
		break;
	default:
		break;
	}

	switch (y)
	{
	case Center:
		ry = (GetSystemMetrics(SM_CYSCREEN) - wh) / 2;
		if (ry < 0) ry = 0; //��ʂ������������ꍇ
		break;
	default:
		break;
	}

	//adjust (offset)
	int ax = 0;
	int ay = 0;

	//�^�X�N�o�[���������ꍇ��������
	//�^�X�N�o�[�̈ʒu����`�œ���
	APPBARDATA sBarInfo;
	ZeroMemory(&sBarInfo, sizeof(APPBARDATA));
	sBarInfo.cbSize = sizeof(APPBARDATA);
	sBarInfo.hWnd = m_hWnd;
	SHAppBarMessage(ABM_GETTASKBARPOS, &sBarInfo);
	RECT r = sBarInfo.rc;
	//�^�X�N�o�[�����ɂ��������̑Ώ�
	if (r.left <= 0 && r.top <= 0 &&//�^�X�N�o�[�̍��[�Ə�[��0�ȉ���
		r.right <= r.bottom //�E�ӂ�艺�ӂ������ꍇ
		)
	{
		ax = r.right; //�^�X�N�o�[�������̈�����炷
	}
	//�����f�X�N�g�b�v���I�[�o�[�����ꍇ��
	if (rx + ax + ww > GetSystemMetrics(SM_CXSCREEN))
	{
		//�^�X�N�o�[�A�������̓f�X�N�g�b�v�[�ɃW���X�g�����悤�ɂ���
		rx = ax - (ww - m_clientWidth)/2;  //���̒l�̓E�B���h�E�g�����Y�����Ă���
		ax = 0;
	}

	//�^�X�N�o�[����ɂ��������̑Ώ�
	if (r.left <= 0 && r.top <= 0 &&//�^�X�N�o�[�̍��[�Ə�[��0�ȉ���
		r.bottom <= r.right //���ӂ��E�ӂ������ꍇ
		)
	{
		ay = r.bottom;//�^�X�N�o�[�������̈�����炷
	}
	//�����f�X�N�g�b�v���I�[�o�[�����ꍇ��
	if (ry + ay + wh > GetSystemMetrics(SM_CYSCREEN))
	{
		ry = ay - (wh - m_clientHeight)/2; //�^�X�N�o�[�A�������̓f�X�N�g�b�v�[�ɃW���X�g�����悤�ɂ���
		ay = 0;
	}
	

	::SetWindowPos(m_hWnd, HWND_TOP, rx+ax, ry+ay, 0, 0, SWP_NOSIZE);
}

void SimpleWindow::Show() const
{
	::ValidateRect(m_hWnd, 0);
	::ShowWindow(m_hWnd, SW_SHOW);
	::UpdateWindow(m_hWnd); //WM_PAINT���b�Z�[�W���o���āA�̈���X�V
}

void SimpleWindow::SetTitleText(LPCTSTR str) const
{
	::SetWindowText(m_hWnd, str);
}


HWND SimpleWindow::GetHWND() const
{
	return m_hWnd;
}

int SimpleWindow::GetWindowWidth() const
{
	return m_windowWidth;
}

int SimpleWindow::GetWindowHeight() const
{
	return m_windowHeight;
}

int SimpleWindow::GetClientWidth() const
{
	return m_clientWidth;
}

int SimpleWindow::GetClientHeight() const
{
	return m_clientHeight;
}

bool SimpleWindow::Terminate()
{
	DestroyWindow(m_hWnd);
	return true;
}

}

namespace
{
LRESULT WINAPI SimpleWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc, hBuffer;
	PAINTSTRUCT ps;
	static HBITMAP hBitmap;

	switch (msg) {
	case WM_DESTROY:
		DeleteObject(hBitmap);
		PostQuitMessage(0);
		return 0;
	case WM_CREATE:
		hBitmap = LoadBitmap(
			((LPCREATESTRUCT)lParam)->hInstance,
			(LPCWSTR)IDB_BITMAP1
			);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hBuffer = CreateCompatibleDC(hdc);
		SelectObject(hBuffer, hBitmap);
		
		BITMAP bmp;
		::GetObject(hBitmap, sizeof(BITMAP), &bmp);

		BitBlt(hdc, 0, 0, bmp.bmWidth, bmp.bmHeight, hBuffer, 0, 0, SRCCOPY);

		DeleteDC(hBuffer);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return (DefWindowProc(hWnd, msg, wParam, lParam));
}
}

