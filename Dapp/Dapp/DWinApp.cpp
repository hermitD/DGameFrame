#include "stdafx.h"
#include "DWinApp.h"
#include "DGlobal.h"


DWinApp::DWinApp()
{
	m_pMainWnd = nullptr;
	g_pWinApp = this;
}


DWinApp::~DWinApp()
{
}


BOOL DWinApp::InitInstance()
{
	return TRUE;
}
BOOL DWinApp::ExitInstance()
{
	return TRUE;

}
void DWinApp::run()
{
	MSG msg;
	while (::GetMessage(&msg, NULL, NULL, NULL))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
}