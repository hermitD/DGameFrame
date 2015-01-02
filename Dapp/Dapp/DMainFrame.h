#pragma once
#include "DWnd.h"
#include "DGameMedia.h"
#include "DGameFrame.h"

class DMainFrame :
	public DWnd
{
public:
	DMainFrame();
	~DMainFrame();

	DGameMedia		*m_pDGameMedia;
	DGameFrame		*m_pDGameFrame;

	DWORD			m_dwLastTime;
	DWORD			m_nWideClient;
	DWORD			m_nHightClient;

public:
	//message handle
	virtual LRESULT OnClose(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnDestroy(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnCreate(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnTimer(WPARAM wParam, LPARAM lParam);


	virtual LRESULT OnMouseMove(WPARAM wParam, LPARAM lParam);

	virtual LRESULT OnLButtonUp(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnLButtonDown(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnRButtonUp(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnRButtonDown(WPARAM wParam, LPARAM lParam);

	virtual LRESULT OnKeyDown(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnKeyUp(WPARAM wParam, LPARAM lParam);

};

