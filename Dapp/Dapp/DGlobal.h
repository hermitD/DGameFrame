#pragma once
#include "stdafx.h"
#include "DWinApp.h"

extern DWinApp* g_pWinApp;
extern DWinApp* GGetApp();

/*
	useful MACRO :)
*/
#define SAFE_NEW new
#define SAFE_DELETE(ptr) {if (ptr != NULL) {delete ptr; ptr = NULL;}}
#define SAFE_DELETEARRAY(ptr) {if (ptr != NULL) {delete[] ptr; ptr = NULL;}}


#define  ID_TIMER 1