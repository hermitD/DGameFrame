#include "stdafx.h"
#include "DMyApp.h"
#include "DMainFrame.h"


DMyApp theApp;

DMyApp::DMyApp()
{

}


DMyApp::~DMyApp()
{

}



BOOL DMyApp::InitInstance()
{
	DMainFrame* pMainWnd = SAFE_NEW DMainFrame();
	assert(pMainWnd);

	m_pMainWnd = pMainWnd;

	//BOOL bRet = pMainWnd->CreateEx(0, _T("Doye"), _T("Hello Doye"), WS_OVERLAPPEDWINDOW,
	//	CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL);

	BOOL bRet = pMainWnd->CreateEx(0, _T("Doye"), _T("Hello Doye"), WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME,
		CW_USEDEFAULT, CW_USEDEFAULT, 949, 685, NULL, NULL);
	if (!bRet)
	{
		MessageBox(NULL, _T("创建窗口失败！"), _T("创建窗口！"), 0);
		return FALSE;
	}





	pMainWnd->ShowWindow(SW_SHOW);
	pMainWnd->UpdateWindow();

	return TRUE;
}


BOOL DMyApp::ExitInstance()
{
	SAFE_DELETE(m_pMainWnd);
	return TRUE;
}