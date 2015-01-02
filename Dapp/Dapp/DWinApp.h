#pragma once
#include "stdafx.h"
#include "DMainFrame.h"

class DWinApp
{
public:
	DWinApp();
	virtual ~DWinApp();

public:
	virtual BOOL InitInstance();
	virtual BOOL ExitInstance();
	virtual void run();

public:
	DMainFrame *m_pMainWnd;
};

