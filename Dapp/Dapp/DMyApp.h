#pragma once
#include "DWinApp.h"


class DMyApp :public DWinApp
{
public:
	DMyApp();
	virtual ~DMyApp();

public:
	virtual BOOL InitInstance();
	virtual BOOL ExitInstance();
};

extern DMyApp theApp;