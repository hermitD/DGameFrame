
#include "stdafx.h"
#include "Dapp.h"
#include "DGlobal.h"


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	//1. find the App
	DWinApp* pWinApp = GGetApp();

	//2. do the loop about the app
	pWinApp->InitInstance();
	pWinApp->run();
	pWinApp->ExitInstance();

	return TRUE;


}
