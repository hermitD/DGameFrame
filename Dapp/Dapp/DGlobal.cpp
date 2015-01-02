#include "stdafx.h"
#include "DGlobal.h"

DWinApp* g_pWinApp = nullptr;
DWinApp* GGetApp()
{
	return g_pWinApp;
}