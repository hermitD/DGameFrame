#include "stdafx.h"
#include "DWnd.h"


DWnd::DWnd(void)
{
	m_hWnd = NULL;
	m_lpfnOldWndProc = NULL;
}

DWnd::~DWnd(void)
{

}

BOOL DWnd::SubClassWindow(HWND hWnd)
{
	assert(hWnd);
	if (m_hWnd == hWnd) return TRUE;

	m_lpfnOldWndProc = (WNDPROC)GetWindowLongPtr(hWnd, GWL_WNDPROC);
	if (m_lpfnOldWndProc != DWnd::WndProc)
	{
		m_hWnd = hWnd;
		SetWindowLongPtr(m_hWnd, GWL_USERDATA, (LONG)this);
		SetWindowLongPtr(m_hWnd, GWL_WNDPROC, (LONG)DWnd::WndProc);
		return TRUE;
	}
	return FALSE;
}

DWnd* DWnd::FromHandle(HWND hWnd)
{
	assert(hWnd);

	DWnd* pWnd = (DWnd*)GetWindowLong(hWnd, GWL_USERDATA);
	return pWnd;
}

BOOL DWnd::PreCreateWindow(
	CREATESTRUCT& cs
	)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	BOOL bRet = ::GetClassInfoEx(cs.hInstance, cs.lpszClass, &wcex);
	if (bRet)
	{
		return TRUE;
	}

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = cs.hInstance;
	wcex.hIcon = (HICON)::LoadIcon(NULL, IDI_QUESTION);
	wcex.hIconSm = (HICON)::LoadIcon(NULL, IDI_QUESTION);
	wcex.hbrBackground = (HBRUSH)::GetStockObject(WHITE_BRUSH);
	wcex.hCursor = (HCURSOR)::LoadCursor(NULL, IDC_ARROW);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = cs.lpszClass;
	bRet = ::RegisterClassEx(&wcex);
	if (!bRet)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL DWnd::CreateEx(
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
	LPVOID lpParam
	)
{
	HINSTANCE hInstance = (HINSTANCE)::GetModuleHandle(NULL);
	assert(hInstance);

	CREATESTRUCT cs;
	cs.cx = nWidth;
	cs.cy = nHeight;
	cs.dwExStyle = dwExStyle;
	cs.hInstance = hInstance;
	cs.hMenu = nIDorHMenu;
	cs.hwndParent = hWndParent;
	cs.lpCreateParams = lpParam;
	cs.lpszClass = lpszClassName;
	cs.lpszName = lpszWindowName;
	cs.style = dwStyle;
	cs.x = x;
	cs.y = y;
	BOOL bRet = PreCreateWindow(cs);
	if (!bRet)
	{
		MessageBox(NULL, _T("failed reg wnd class"), _T(""), 0);
		return FALSE;
	}

	HWND hWnd = CreateWindowEx(cs.dwExStyle, cs.lpszClass, cs.lpszName, cs.style, cs.x, cs.y,
		cs.cx, cs.cy, cs.hwndParent, cs.hMenu, cs.hInstance, this);
	if (NULL == hWnd)
	{
		return FALSE;
	}
	m_hWnd = hWnd;

	SetWindowLongPtr(m_hWnd, GWL_USERDATA, (LONG)this);

	m_lpfnOldWndProc = (WNDPROC)GetWindowLongPtr(m_hWnd, GWL_WNDPROC);
	if (m_lpfnOldWndProc != DWnd::WndProc)
	{
		// 子类化
		SetWindowLongPtr(m_hWnd, GWL_WNDPROC, (LONG)DWnd::WndProc);
		// 补上这个过程中错失的事件
		WindowProc(WM_CREATE, 0, 0);
		WindowProc(WM_NCCREATE, 0, 0);
	}
	return TRUE;
}

// API Functions
BOOL DWnd::ShowWindow(int nCmdShow)
{
	assert(m_hWnd);
	return ::ShowWindow(m_hWnd, nCmdShow);
}

BOOL DWnd::UpdateWindow()
{
	assert(m_hWnd);
	return ::UpdateWindow(m_hWnd);
}

BOOL DWnd::DestroyWindow()
{
	assert(m_hWnd);
	return ::DestroyWindow(m_hWnd);
}

BOOL DWnd::GetClientRect(LPRECT lpRect)
{
	assert(m_hWnd);
	return ::GetClientRect(m_hWnd, lpRect);
}


LRESULT DWnd::Default(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (m_lpfnOldWndProc == DWnd::WndProc)
	{
		return ::DefWindowProc(m_hWnd, uMsg, wParam, lParam);
	}

	return m_lpfnOldWndProc(m_hWnd, uMsg, wParam, lParam);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// Windows message handler
//////////////////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK DWnd::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_CREATE || uMsg == WM_NCCREATE)
	{
		LPCREATESTRUCT pCs = (LPCREATESTRUCT)lParam;
		if (pCs)
		{
			DWnd* pWnd = (DWnd*)pCs->lpCreateParams;
			if (pWnd)
			{
				//为了WindowProc正常执行作准备工作
				pWnd->m_hWnd = hWnd;				
				pWnd->m_lpfnOldWndProc = (WNDPROC)GetWindowLongPtr(hWnd, GWL_WNDPROC);
			
				return pWnd->WindowProc(uMsg, wParam, lParam);
			}
		}
	}

	DWnd* pWnd = (DWnd*)GetWindowLongPtr(hWnd, GWL_USERDATA);
	if (pWnd)
	{
		return pWnd->WindowProc(uMsg, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT DWnd::WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_ACTIVATE:
		return OnActivate(wParam, lParam);
	case WM_ACTIVATEAPP:
		return OnActivateApp(wParam, lParam);
	case WM_ASKCBFORMATNAME:
		return OnAskCbFormatName(wParam, lParam);
	case WM_CANCELMODE:
		return OnCancelMode(wParam, lParam);
	case WM_CAPTURECHANGED:
		return OnCaptureChanged(wParam, lParam);
	case WM_CHANGECBCHAIN:
		return OnChangeCbChain(wParam, lParam);
	case WM_CHAR:
		return OnChar(wParam, lParam);
	case WM_CHARTOITEM:
		return OnCharToItem(wParam, lParam);
	case WM_CHILDACTIVATE:
		return OnChildActivate(wParam, lParam);
	case WM_CLOSE:
		return OnClose(wParam, lParam);
	case WM_COMPACTING:
		return OnCompacting(wParam, lParam);
	case WM_COMPAREITEM:
		return OnCompareItem(wParam, lParam);
	case WM_CONTEXTMENU:
		return OnContextMenu(wParam, lParam);
	case WM_COPYDATA:
		return OnCopyData(wParam, lParam);
	case WM_CREATE:
		return OnCreate(wParam, lParam);

	case WM_DEADCHAR:
		return OnDeadChar(wParam, lParam);
	case WM_DELETEITEM:
		return OnDeleteItem(wParam, lParam);
	case WM_DESTROY:
		return OnDestroy(wParam, lParam);
	case WM_DESTROYCLIPBOARD:
		return OnDestroyClipboard(wParam, lParam);
	case WM_DEVICECHANGE:
		return OnDeviceChange(wParam, lParam);
	case WM_DEVMODECHANGE:
		return OnDevModeChange(wParam, lParam);
	case WM_DRAWCLIPBOARD:
		return OnDrawClipboard(wParam, lParam);
	case WM_DRAWITEM:
		return OnDrawItem(wParam, lParam);
	case WM_DROPFILES:
		return OnDropFiles(wParam, lParam);
	case WM_ENABLE:
		return OnEnable(wParam, lParam);
	case WM_ENDSESSION:
		return OnEndSession(wParam, lParam);
	case WM_ENTERIDLE:
		return OnEnterIdle(wParam, lParam);
	case WM_ERASEBKGND:
		return OnEraseBkgnd(wParam, lParam);

	case WM_FONTCHANGE:
		return OnFontChange(wParam, lParam);
	case WM_GETDLGCODE:
		return OnGetDlgCode(wParam, lParam);
	case WM_GETMINMAXINFO:
		return OnGetMinMaxInfo(wParam, lParam);
	case WM_HELP:
		return OnHelpInfo(wParam, lParam);
	case WM_HSCROLL:
		return OnHScroll(wParam, lParam);
	case WM_HSCROLLCLIPBOARD:
		return OnHScrollClipboard(wParam, lParam);
	case WM_ICONERASEBKGND:
		return OnIconEraseBkgnd(wParam, lParam);
	case WM_INITMENU:
		return OnInitMenu(wParam, lParam);
	case WM_INITMENUPOPUP:
		return OnInitMenuPopup(wParam, lParam);
	case WM_KEYDOWN:
		return OnKeyDown(wParam, lParam);
	case WM_KEYUP:
		return OnKeyUp(wParam, lParam);
	case WM_KILLFOCUS:
		return OnKillFocus(wParam, lParam);

	case WM_LBUTTONDBLCLK:
		return OnLButtonDblClk(wParam, lParam);
	case WM_LBUTTONDOWN:
		return OnLButtonDown(wParam, lParam);
	case WM_LBUTTONUP:
		return OnLButtonUp(wParam, lParam);
	case WM_MBUTTONDBLCLK:
		return OnMButtonDblClk(wParam, lParam);
	case WM_MBUTTONDOWN:
		return OnMButtonDown(wParam, lParam);
	case WM_MBUTTONUP:
		return OnMButtonUp(wParam, lParam);
	case WM_MDIACTIVATE:
		return OnMDIActivate(wParam, lParam);
	case WM_MEASUREITEM:
		return OnMeasureItem(wParam, lParam);
	case WM_MENUCHAR:
		return OnMenuChar(wParam, lParam);
	case WM_MENUSELECT:
		return OnMenuSelect(wParam, lParam);
	case WM_MOUSEACTIVATE:
		return OnMouseActivate(wParam, lParam);
	case WM_MOUSEMOVE:
		return OnMouseMove(wParam, lParam);
	case WM_MOUSEWHEEL:
		return OnMouseWheel(wParam, lParam);
	case WM_MOVE:
		return OnMove(wParam, lParam);
	case WM_MOVING:
		return OnMoving(wParam, lParam);

	case WM_NCACTIVATE:
		return OnNcActivate(wParam, lParam);
	case WM_NCCALCSIZE:
		return OnNcCalcSize(wParam, lParam);
	case WM_NCCREATE:
		return OnNcCreate(wParam, lParam);
	case WM_NCDESTROY:
		return OnNcDestroy(wParam, lParam);
	case WM_NCHITTEST:
		return OnNcHitTest(wParam, lParam);
	case WM_NCLBUTTONDBLCLK:
		return OnNcLButtonDblClk(wParam, lParam);
	case WM_NCLBUTTONDOWN:
		return OnNcLButtonDown(wParam, lParam);
	case WM_NCLBUTTONUP:
		return OnNcLButtonUp(wParam, lParam);
	case WM_NCMBUTTONDBLCLK:
		return OnNcMButtonDblClk(wParam, lParam);
	case WM_NCMBUTTONDOWN:
		return OnNcMButtonDown(wParam, lParam);
	case WM_NCMBUTTONUP:
		return OnNcMButtonUp(wParam, lParam);
	case WM_NCMOUSEMOVE:
		return OnNcMouseMove(wParam, lParam);
	case WM_NCPAINT:
		return OnNcPaint(wParam, lParam);
	case WM_NCRBUTTONDBLCLK:
		return OnNcRButtonDblClk(wParam, lParam);
	case WM_NCRBUTTONDOWN:
		return OnNcRButtonDown(wParam, lParam);
	case WM_NCRBUTTONUP:
		return OnNcRButtonUp(wParam, lParam);

	case WM_PAINT:
		return OnPaint(wParam, lParam);
	case WM_PAINTCLIPBOARD:
		return OnPaintClipboard(wParam, lParam);
	case WM_PALETTECHANGED:
		return OnPaletteChanged(wParam, lParam);
	case WM_PALETTEISCHANGING:
		return OnPaletteIsChanging(wParam, lParam);
	case WM_PARENTNOTIFY:
		return OnParentNotify(wParam, lParam);
	case WM_QUERYDRAGICON:
		return OnQueryDragIcon(wParam, lParam);
	case WM_QUERYENDSESSION:
		return OnQueryEndSession(wParam, lParam);
	case WM_QUERYNEWPALETTE:
		return OnQueryNewPalette(wParam, lParam);
	case WM_QUERYOPEN:
		return OnQueryOpen(wParam, lParam);
	case WM_RBUTTONDBLCLK:
		return OnNcRButtonDblClk(wParam, lParam);
	case WM_RBUTTONDOWN:
		return OnRButtonDown(wParam, lParam);
	case WM_RBUTTONUP:
		return OnRButtonUp(wParam, lParam);
	case WM_RENDERALLFORMATS:
		return OnRenderAllFormats(wParam, lParam);
	case WM_RENDERFORMAT:
		return OnRenderFormat(wParam, lParam);

	case WM_SETCURSOR:
		return OnSetCursor(wParam, lParam);
	case WM_SETFOCUS:
		return OnSetFocus(wParam, lParam);
	case WM_SHOWWINDOW:
		return OnShowWindow(wParam, lParam);
	case WM_SIZE:
		return OnSize(wParam, lParam);
	case WM_SIZECLIPBOARD:
		return OnSizeClipboard(wParam, lParam);
	case WM_SIZING:
		return OnSizing(wParam, lParam);
	case WM_SPOOLERSTATUS:
		return OnSpoolerStatus(wParam, lParam);
	case WM_STYLECHANGED:
		return OnStyleChanged(wParam, lParam);
	case WM_STYLECHANGING:
		return OnStyleChanging(wParam, lParam);
	case WM_SYSCHAR:
		return OnSysChar(wParam, lParam);
	case WM_SYSCOLORCHANGE:
		return OnSysColorChange(wParam, lParam);
	case WM_SYSCOMMAND:
		return OnSysCommand(wParam, lParam);
	case WM_SYSDEADCHAR:
		return OnSysDeadChar(wParam, lParam);
	case WM_SYSKEYDOWN:
		return OnSysKeyDown(wParam, lParam);
	case WM_SYSKEYUP:
		return OnSysKeyUp(wParam, lParam);

	case WM_TCARD:
		return OnTCard(wParam, lParam);
	case WM_TIMECHANGE:
		return OnTimeChange(wParam, lParam);
	case WM_TIMER:
		return OnTimer(wParam, lParam);
	case WM_VKEYTOITEM:
		return OnVKeyToItem(wParam, lParam);
	case WM_VSCROLL:
		return OnVScroll(wParam, lParam);
	case WM_VSCROLLCLIPBOARD:
		return OnVScrollClipboard(wParam, lParam);
	case WM_WINDOWPOSCHANGED:
		return OnWindowPosChanged(wParam, lParam);
	case WM_WINDOWPOSCHANGING:
		return OnWindowPosChanging(wParam, lParam);
	case WM_WININICHANGE:
		return OnWinIniChange(wParam, lParam);

	default:
		break;
	}
	return Default(uMsg, wParam, lParam);
}

// WM_ Message Handlers: A - C 
LRESULT DWnd::OnActivate(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_ACTIVATE, wParam, lParam);
}

LRESULT DWnd::OnActivateApp(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_ACTIVATEAPP, wParam, lParam);
}

LRESULT DWnd::OnAskCbFormatName(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_ASKCBFORMATNAME, wParam, lParam);
}

LRESULT DWnd::OnCancelMode(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_CANCELMODE, wParam, lParam);
}

LRESULT DWnd::OnCaptureChanged(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_CAPTURECHANGED, wParam, lParam);
}

LRESULT DWnd::OnChangeCbChain(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_CHANGECBCHAIN, wParam, lParam);
}

LRESULT DWnd::OnChar(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_CHAR, wParam, lParam);
}

LRESULT DWnd::OnCharToItem(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_CHARTOITEM, wParam, lParam);
}

LRESULT DWnd::OnChildActivate(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_CHILDACTIVATE, wParam, lParam);
}

LRESULT DWnd::OnClose(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_CLOSE, wParam, lParam);
}

LRESULT DWnd::OnCompacting(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_COMPACTING, wParam, lParam);
}

LRESULT DWnd::OnCompareItem(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_COMPAREITEM, wParam, lParam);
}

LRESULT DWnd::OnContextMenu(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_CONTEXTMENU, wParam, lParam);
}

LRESULT DWnd::OnCopyData(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_COPYDATA, wParam, lParam);
}

LRESULT DWnd::OnCreate(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_CREATE, wParam, lParam);
}

// WM_ Message Handlers: D - E 
LRESULT DWnd::OnDeadChar(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_DEADCHAR, wParam, lParam);
}

LRESULT DWnd::OnDeleteItem(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_DELETEITEM, wParam, lParam);
}

LRESULT DWnd::OnDestroy(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_DESTROY, wParam, lParam);
}

LRESULT DWnd::OnDestroyClipboard(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_DESTROYCLIPBOARD, wParam, lParam);
}

LRESULT DWnd::OnDeviceChange(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_DEVICECHANGE, wParam, lParam);
}

LRESULT DWnd::OnDevModeChange(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_DEVMODECHANGE, wParam, lParam);
}

LRESULT DWnd::OnDrawClipboard(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_DRAWCLIPBOARD, wParam, lParam);
}

LRESULT DWnd::OnDrawItem(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_DRAWITEM, wParam, lParam);
}

LRESULT DWnd::OnDropFiles(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_DROPFILES, wParam, lParam);
}

LRESULT DWnd::OnEnable(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_ENABLE, wParam, lParam);
}

LRESULT DWnd::OnEndSession(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_ENDSESSION, wParam, lParam);
}

LRESULT DWnd::OnEnterIdle(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_ENTERIDLE, wParam, lParam);
}

LRESULT DWnd::OnEraseBkgnd(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_ERASEBKGND, wParam, lParam);
}

// WM_ Message Handlers: F - K
LRESULT DWnd::OnFontChange(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_FONTCHANGE, wParam, lParam);
}

LRESULT DWnd::OnGetDlgCode(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_GETDLGCODE, wParam, lParam);
}

LRESULT DWnd::OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_GETMINMAXINFO, wParam, lParam);
}

LRESULT DWnd::OnHelpInfo(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_HELP, wParam, lParam);
}

LRESULT DWnd::OnHScroll(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_HSCROLL, wParam, lParam);
}

LRESULT DWnd::OnHScrollClipboard(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_HSCROLLCLIPBOARD, wParam, lParam);
}

LRESULT DWnd::OnIconEraseBkgnd(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_ICONERASEBKGND, wParam, lParam);
}

LRESULT DWnd::OnInitMenu(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_INITMENU, wParam, lParam);
}

LRESULT DWnd::OnInitMenuPopup(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_INITMENUPOPUP, wParam, lParam);
}

LRESULT DWnd::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_KEYDOWN, wParam, lParam);
}

LRESULT DWnd::OnKeyUp(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_KEYUP, wParam, lParam);
}

LRESULT DWnd::OnKillFocus(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_KILLFOCUS, wParam, lParam);
}

//WM_ Message Handlers: L - M 
LRESULT DWnd::OnLButtonDblClk(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_LBUTTONDBLCLK, wParam, lParam);
}

LRESULT DWnd::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_LBUTTONDOWN, wParam, lParam);
}

LRESULT DWnd::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_LBUTTONUP, wParam, lParam);
}

LRESULT DWnd::OnMButtonDblClk(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_MBUTTONDBLCLK, wParam, lParam);
}

LRESULT DWnd::OnMButtonDown(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_MBUTTONDOWN, wParam, lParam);
}

LRESULT DWnd::OnMButtonUp(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_MBUTTONUP, wParam, lParam);
}

LRESULT DWnd::OnMDIActivate(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_MDIACTIVATE, wParam, lParam);
}

LRESULT DWnd::OnMeasureItem(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_MEASUREITEM, wParam, lParam);
}

LRESULT DWnd::OnMenuChar(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_MENUCHAR, wParam, lParam);
}

LRESULT DWnd::OnMenuSelect(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_MENUSELECT, wParam, lParam);
}

LRESULT DWnd::OnMouseActivate(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_MOUSEACTIVATE, wParam, lParam);
}

LRESULT DWnd::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_MOUSEMOVE, wParam, lParam);
}

LRESULT DWnd::OnMouseWheel(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_MOUSEWHEEL, wParam, lParam);
}

LRESULT DWnd::OnMove(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_MOVE, wParam, lParam);
}

LRESULT DWnd::OnMoving(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_MOVING, wParam, lParam);
}

//WM_ Message Handlers: N - O 
LRESULT DWnd::OnNcActivate(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCACTIVATE, wParam, lParam);
}

LRESULT DWnd::OnNcCalcSize(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCCALCSIZE, wParam, lParam);
}

LRESULT DWnd::OnNcCreate(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCCREATE, wParam, lParam);
}

LRESULT DWnd::OnNcDestroy(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCDESTROY, wParam, lParam);
}

LRESULT DWnd::OnNcHitTest(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCHITTEST, wParam, lParam);
}

LRESULT DWnd::OnNcLButtonDblClk(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCLBUTTONDBLCLK, wParam, lParam);
}

LRESULT DWnd::OnNcLButtonDown(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCLBUTTONDOWN, wParam, lParam);
}

LRESULT DWnd::OnNcLButtonUp(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCLBUTTONUP, wParam, lParam);
}

LRESULT DWnd::OnNcMButtonDblClk(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCRBUTTONDBLCLK, wParam, lParam);
}

LRESULT DWnd::OnNcMButtonDown(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCMBUTTONDOWN, wParam, lParam);
}

LRESULT DWnd::OnNcMButtonUp(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCMBUTTONUP, wParam, lParam);
}

LRESULT DWnd::OnNcMouseMove(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCMOUSEMOVE, wParam, lParam);
}

LRESULT DWnd::OnNcPaint(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCPAINT, wParam, lParam);
}

LRESULT DWnd::OnNcRButtonDblClk(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCRBUTTONDBLCLK, wParam, lParam);
}

LRESULT DWnd::OnNcRButtonDown(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCRBUTTONDOWN, wParam, lParam);
}

LRESULT DWnd::OnNcRButtonUp(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_NCRBUTTONUP, wParam, lParam);
}

// WM_ Messages: P - R 
LRESULT DWnd::OnPaint(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_PAINT, wParam, lParam);
}

LRESULT DWnd::OnPaintClipboard(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_PAINTCLIPBOARD, wParam, lParam);
}

LRESULT DWnd::OnPaletteChanged(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_PALETTECHANGED, wParam, lParam);
}

LRESULT DWnd::OnPaletteIsChanging(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_PALETTEISCHANGING, wParam, lParam);
}

LRESULT DWnd::OnParentNotify(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_PARENTNOTIFY, wParam, lParam);
}

LRESULT DWnd::OnQueryDragIcon(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_QUERYDRAGICON, wParam, lParam);
}

LRESULT DWnd::OnQueryEndSession(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_QUERYENDSESSION, wParam, lParam);
}

LRESULT DWnd::OnQueryNewPalette(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_QUERYNEWPALETTE, wParam, lParam);
}

LRESULT DWnd::OnQueryOpen(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_QUERYOPEN, wParam, lParam);
}

LRESULT DWnd::OnRButtonDblClk(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_RBUTTONDBLCLK, wParam, lParam);
}

LRESULT DWnd::OnRButtonDown(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_RBUTTONDOWN, wParam, lParam);
}

LRESULT DWnd::OnRButtonUp(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_RBUTTONUP, wParam, lParam);
}

LRESULT DWnd::OnRenderAllFormats(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_RENDERALLFORMATS, wParam, lParam);
}

LRESULT DWnd::OnRenderFormat(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_RENDERFORMAT, wParam, lParam);
}


// WM_ Messages: S 
LRESULT DWnd::OnSetCursor(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_SETCURSOR, wParam, lParam);
}

LRESULT DWnd::OnSetFocus(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_SETFOCUS, wParam, lParam);
}

LRESULT DWnd::OnShowWindow(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_SHOWWINDOW, wParam, lParam);
}

LRESULT DWnd::OnSize(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_SIZE, wParam, lParam);
}

LRESULT DWnd::OnSizeClipboard(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_SIZECLIPBOARD, wParam, lParam);
}

LRESULT DWnd::OnSizing(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_SIZING, wParam, lParam);
}

LRESULT DWnd::OnSpoolerStatus(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_SPOOLERSTATUS, wParam, lParam);
}

LRESULT DWnd::OnStyleChanged(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_STYLECHANGED, wParam, lParam);
}

LRESULT DWnd::OnStyleChanging(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_STYLECHANGING, wParam, lParam);
}

LRESULT DWnd::OnSysChar(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_SYSCHAR, wParam, lParam);
}

LRESULT DWnd::OnSysColorChange(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_SYSCOLORCHANGE, wParam, lParam);
}

LRESULT DWnd::OnSysCommand(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_SYSCOMMAND, wParam, lParam);
}

LRESULT DWnd::OnSysDeadChar(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_DEADCHAR, wParam, lParam);
}

LRESULT DWnd::OnSysKeyDown(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_SYSKEYDOWN, wParam, lParam);
}

LRESULT DWnd::OnSysKeyUp(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_SYSKEYUP, wParam, lParam);
}

//WM_ Messages: T - Z 
LRESULT DWnd::OnTCard(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_TCARD, wParam, lParam);
}

LRESULT DWnd::OnTimeChange(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_TIMECHANGE, wParam, lParam);
}

LRESULT DWnd::OnTimer(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_TIMECHANGE, wParam, lParam);
}

LRESULT DWnd::OnVKeyToItem(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_VKEYTOITEM, wParam, lParam);
}

LRESULT DWnd::OnVScroll(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_VSCROLL, wParam, lParam);
}

LRESULT DWnd::OnVScrollClipboard(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_VSCROLLCLIPBOARD, wParam, lParam);
}

LRESULT DWnd::OnWindowPosChanged(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_WINDOWPOSCHANGED, wParam, lParam);
}

LRESULT DWnd::OnWindowPosChanging(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_WINDOWPOSCHANGING, wParam, lParam);
}

LRESULT DWnd::OnWinIniChange(WPARAM wParam, LPARAM lParam)
{
	return Default(WM_WININICHANGE, wParam, lParam);
}