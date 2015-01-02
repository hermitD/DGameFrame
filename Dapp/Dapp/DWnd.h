#pragma once
#include "stdafx.h"


class DWnd
{
public:
	DWnd();
	~DWnd();
public:
	virtual BOOL PreCreateWindow(
		CREATESTRUCT& cs
		);
	virtual BOOL CreateEx(
		DWORD dwExStyle,
		LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName,
		DWORD dwStyle,
		int x,
		int y,
		int nWidth,
		int nHeight,
		HWND hWndParent,
		HMENU nIDorHMenu,
		LPVOID lpParam = nullptr
		);

public:
	BOOL ShowWindow(int nCmdShow);
	BOOL UpdateWindow();
	BOOL DestroyWindow();

	BOOL GetClientRect(LPRECT lpRect);

public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT Default(UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	BOOL SubClassWindow(HWND hWnd);
	static DWnd* FromHandle(HWND hWnd);

public:
	HWND m_hWnd;
	WNDPROC m_lpfnOldWndProc;

	//////////////////////////////////////////////////////////////////////////////////////////////
public:// virtual message handler

	// WM_ Message Handlers: A - C 
	virtual LRESULT OnActivate(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnActivateApp(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnAskCbFormatName(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnCancelMode(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnCaptureChanged(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnChangeCbChain(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnChar(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnCharToItem(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnChildActivate(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnClose(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnCompacting(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnCompareItem(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnContextMenu(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnCopyData(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnCreate(WPARAM wParam, LPARAM lParam);

	// WM_ Message Handlers: D - E 
	virtual LRESULT OnDeadChar(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnDeleteItem(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnDestroy(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnDestroyClipboard(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnDeviceChange(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnDevModeChange(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnDrawClipboard(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnDrawItem(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnDropFiles(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnEnable(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnEndSession(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnEnterIdle(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnEraseBkgnd(WPARAM wParam, LPARAM lParam);

	// WM_ Message Handlers: F - K
	virtual LRESULT OnFontChange(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnGetDlgCode(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnHelpInfo(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnHScroll(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnHScrollClipboard(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnIconEraseBkgnd(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnInitMenu(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnInitMenuPopup(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnKeyDown(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnKeyUp(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnKillFocus(WPARAM wParam, LPARAM lParam);

	//WM_ Message Handlers: L - M 
	virtual LRESULT OnLButtonDblClk(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnLButtonDown(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnLButtonUp(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMButtonDblClk(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMButtonDown(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMButtonUp(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMDIActivate(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMeasureItem(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMenuChar(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMenuSelect(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMouseActivate(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMouseMove(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMouseWheel(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMove(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMoving(WPARAM wParam, LPARAM lParam);

	//WM_ Message Handlers: N - O 
	virtual LRESULT OnNcActivate(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnNcCalcSize(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnNcCreate(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnNcDestroy(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnNcHitTest(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnNcLButtonDblClk(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnNcLButtonDown(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnNcLButtonUp(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnNcMButtonDblClk(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnNcMButtonDown(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnNcMButtonUp(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnNcMouseMove(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnNcPaint(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnNcRButtonDblClk(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnNcRButtonDown(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnNcRButtonUp(WPARAM wParam, LPARAM lParam);

	// WM_ Messages: P - R 
	virtual LRESULT OnPaint(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnPaintClipboard(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnPaletteChanged(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnPaletteIsChanging(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnParentNotify(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnQueryDragIcon(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnQueryEndSession(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnQueryNewPalette(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnQueryOpen(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnRButtonDblClk(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnRButtonDown(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnRButtonUp(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnRenderAllFormats(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnRenderFormat(WPARAM wParam, LPARAM lParam);

	// WM_ Messages: S 
	virtual LRESULT OnSetCursor(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnSetFocus(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnShowWindow(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnSize(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnSizeClipboard(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnSizing(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnSpoolerStatus(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnStyleChanged(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnStyleChanging(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnSysChar(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnSysColorChange(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnSysCommand(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnSysDeadChar(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnSysKeyDown(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnSysKeyUp(WPARAM wParam, LPARAM lParam);

	//WM_ Messages: T - Z 
	virtual LRESULT OnTCard(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnTimeChange(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnTimer(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnVKeyToItem(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnVScroll(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnVScrollClipboard(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnWindowPosChanged(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnWindowPosChanging(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnWinIniChange(WPARAM wParam, LPARAM lParam);

};

