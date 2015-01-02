#include "stdafx.h"
#include "resource.h"
#include "DMainFrame.h"
#include "DGameMedia.h"
#include "DGameDefine.h"
#include "DGameFrame.h"
#include "DGameTest.h"

DMainFrame::DMainFrame()
{
}


DMainFrame::~DMainFrame()
{
	SAFE_DELETE(m_pDGameMedia);
	SAFE_DELETE(m_pDGameFrame);
#ifdef ENABLE_CONSOLE
	FreeConsole();
#endif

}

// msg 
LRESULT DMainFrame::OnClose(WPARAM wParam, LPARAM lParam)	
{
	//return DWnd::OnClose(wParam, lParam);
	return DestroyWindow();
}

LRESULT DMainFrame::OnDestroy(WPARAM wParam, LPARAM lParam)
{
	//return DWnd::OnDestroy(wParam, lParam);
	PostQuitMessage(0);
	return TRUE;
}

void CALLBACK TimerProc(
	HWND hWnd,
	UINT uMsg,
	UINT idEvent,
	DWORD dwTime
	)
{
	assert(hWnd);
	DMainFrame* pDMainFrame = (DMainFrame*)DWnd::FromHandle(hWnd);

	pDMainFrame->OnTimer(idEvent, (LPARAM)pDMainFrame->m_hWnd);
	if (idEvent == ID_TIMER)
	{
		

		SYSTEMTIME st;
		GetLocalTime(&st);
		printf("%d\n",st.wSecond);
		InvalidateRect(hWnd, NULL, TRUE);
	}
}



LRESULT DMainFrame::OnCreate(WPARAM wParam, LPARAM lParam)
{
	////居中窗体
	//int scrWidth, scrHeight;
	//RECT rect;
	////获得屏幕尺寸
	//scrWidth = GetSystemMetrics(SM_CXSCREEN);
	//scrHeight = GetSystemMetrics(SM_CYSCREEN);
	////获取窗体尺寸
	//GetWindowRect(m_hWnd, &rect);
	//rect.left = (scrWidth - rect.right) / 2;
	//rect.top = (scrHeight - rect.bottom) / 2;
	////设置窗体位置
	//SetWindowPos(m_hWnd, HWND_TOP, rect.left, rect.top, rect.right, rect.bottom, SWP_SHOWWINDOW);

	//全屏代码
	//int scrWidth, scrHeight;
	//scrWidth = GetSystemMetrics(SM_CXSCREEN);
	//scrHeight = GetSystemMetrics(SM_CYSCREEN);

	//::SetWindowPos(m_hWnd, HWND_BOTTOM, 0, 0, (int)(scrWidth * 1.0f), (int)(scrHeight * 1.0f), SWP_NOZORDER);

	//_CrtSetBreakAlloc(139);

#ifdef ENABLE_CONSOLE
	::AllocConsole(); // open console resource
	//  直接关掉控制台窗口会出错，需要禁用掉
	{
		TCHAR buf[100];
		GetConsoleTitle(buf, 100);
		HWND hwnd = ::FindWindow(NULL, buf);
		HMENU hmenu = ::GetSystemMenu(hwnd, FALSE);
		::RemoveMenu(hmenu, SC_CLOSE, MF_BYCOMMAND);
	}
	freopen("CONOUT$", "w+t", stdout);
		
	PRINTLOG("Hello World!\n"); // for tests
#endif

	m_pDGameMedia = SAFE_NEW DGameMedia;
	if (m_pDGameMedia == NULL)
	{
		MessageBox(0,_T("could not new DGameMedia"),_T("ERROR"),0);
		exit(0);
	}

	m_pDGameFrame = SAFE_NEW DGameFrame(this, m_pDGameMedia);
	if (m_pDGameMedia == NULL)
	{
		MessageBox(0, _T("could not new DGameMedia"), _T("ERROR"), 0);
		exit(0);
	}
	m_pDGameFrame->OnInit();




	DGameTest *pGameTest = SAFE_NEW DGameTest;
	m_pDGameFrame->RunLayer(pGameTest);
	pGameTest = NULL;

	SetTimer(m_hWnd, TIMERID_GAME, 500, TimerProc);

	return TRUE;
}


LRESULT DMainFrame::OnTimer(WPARAM wParam, LPARAM lParam)
{
	//wParam[in]
	//	The timer identifier.
	//lParam[in]
	//	A pointer to an application - defined callback function that was passed to the SetTimer function when the timer was installed.
	if (wParam == TIMERID_GAME)
	{
		::KillTimer(m_hWnd,TIMERID_GAME);

		// 记录帧间隔
		DWORD dwCurTime = ::GetTickCount();
		DWORD dt = 0;
		dt = dwCurTime - m_dwLastTime;
		if (dt > MAX_MOMENT_TIME)
		{
			dt = MOMENT_TIME;
		}
		m_dwLastTime = dwCurTime;


		m_pDGameFrame->Update(dt);//帧间隔

		{ // 获取客户区域大小
			CRect rc;
			GetClientRect(&rc);
			m_nWideClient = rc.Width();
			m_nHightClient = rc.Height();
			DeleteObject(rc);
		}
		CDC dc;
		dc.Attach(::GetDC(m_hWnd));
		CDC *pDC = &dc;
		
		
		// 双缓冲
		CDC MemDC;
		CBitmap MemBitmap;
		MemDC.CreateCompatibleDC(NULL);
		MemBitmap.CreateCompatibleBitmap(pDC,m_pDGameMedia->m_pGameMedGraphic->GetCameraW(),
			m_pDGameMedia->m_pGameMedGraphic->GetCameraH());
		CBitmap   *pOldBit = MemDC.SelectObject(&MemBitmap);
		MemDC.FillSolidRect(m_pDGameMedia->m_pGameMedGraphic->GetCameraX(), m_pDGameMedia->m_pGameMedGraphic->GetCameraY(),
			m_pDGameMedia->m_pGameMedGraphic->GetCameraW(), m_pDGameMedia->m_pGameMedGraphic->GetCameraH(), RGB(148, 37, 158)); 
		m_pDGameMedia->m_pGameMedGraphic->SetMemDc(&MemDC);

		Graphics gh(MemDC.m_hDC);
		m_pDGameMedia->m_pGameMedGraphic->SetGDIPlusWM(&gh);


		m_pDGameFrame->Draw(dt);



#ifdef DEBUG_INFOS

		{ // Debugs
			CString str;
			CPoint point;
			int x = 0;
			int y = 0;

			GetCursorPos(&point);
			ScreenToClient(m_hWnd,&point);
			m_pDGameFrame->ChangeClientToGameCoor(x, y, m_pDGameMedia->m_pGameMedGraphic->GetCameraW(), m_pDGameMedia->m_pGameMedGraphic->GetCameraH(),
				(int)point.x, (int)point.y, m_nWideClient, m_nHightClient);
			x += m_pDGameMedia->m_pGameMedGraphic->GetCameraX();
			y += m_pDGameMedia->m_pGameMedGraphic->GetCameraY();


			str.Format(_T("窗口大小(%3d, %3d)"), m_nWideClient, m_nHightClient);
			m_pDGameMedia->m_pGameMedGraphic->DrawTextWM(100, _T("宋体"), RGB(250, 250, 250), 0, 0, str);

			str.Format(_T("游戏区域(%3d, %3d)"), GAME_SCREEN_W, GAME_SCREEN_H);
			m_pDGameMedia->m_pGameMedGraphic->DrawTextWM(100, _T("宋体"), RGB(250, 250, 250), 0, 14, str);
			str.Format(_T("客户坐标(%3d, %3d)"), (int)point.x, (int)point.y);
			m_pDGameMedia->m_pGameMedGraphic->DrawTextWM(100, _T("宋体"), RGB(250, 250, 250), 0, 28, str);
			str.Format(_T("游戏坐标(%3d, %3d)"), x, y);
			m_pDGameMedia->m_pGameMedGraphic->DrawTextWM(100, _T("宋体"), RGB(250, 250, 250), 0, 42, str);
			str.Format(_T("游戏间隔 %3d"), dt);
			m_pDGameMedia->m_pGameMedGraphic->DrawTextWM(100, _T("宋体"), RGB(250, 250, 250), 0, 56, str);
		}
#endif			

		m_pDGameMedia->m_pGameMedGraphic->SetNullMemDC();
		pDC->StretchBlt(0, 0, m_nWideClient, m_nHightClient,
			&MemDC,
			m_pDGameMedia->m_pGameMedGraphic->GetCameraX(), m_pDGameMedia->m_pGameMedGraphic->GetCameraY(),
			m_pDGameMedia->m_pGameMedGraphic->GetCameraW(), m_pDGameMedia->m_pGameMedGraphic->GetCameraH(),
			SRCCOPY); 
		MemDC.SelectObject(pOldBit);
		MemBitmap.DeleteObject();
		MemDC.DeleteDC();
		pOldBit->DeleteObject(); 
		pDC = NULL;
		SetTimer(m_hWnd,TIMERID_GAME, MOMENT_TIME, NULL);
	}
	DWnd::OnTimer(wParam, lParam);

	return TRUE;
}



//LRESULT DMainFrame::OnLButtonDown(WPARAM wParam, LPARAM lParam)
//{
//	/*WCHAR szWParam[MAX_PATH];
//	WCHAR szLParam[MAX_PATH];
//	_stprintf_s(szWParam, MAX_PATH, _T("%d"), wParam);
//	_stprintf_s(szLParam, MAX_PATH, _T("%d"), lParam);
//
//	MessageBox(0, szWParam, szLParam, 0);*/
//	//MessageBox(0, (LPCWSTR)wParam, (LPCWSTR)lParam, 0);
//	return TRUE;
//}



LRESULT DMainFrame::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	if (m_pDGameFrame->m_bLPointDownSign)
	{
		CPoint point;
		int x = 0;
		int y = 0;

		GetCursorPos(&point);
		ScreenToClient(m_hWnd,&point);
		m_pDGameFrame->ChangeClientToGameCoor(x, y, m_pDGameMedia->m_pGameMedGraphic->GetCameraW(), m_pDGameMedia->m_pGameMedGraphic->GetCameraH(),
			(int)point.x, (int)point.y, m_nWideClient, m_nHightClient);
		x += m_pDGameMedia->m_pGameMedGraphic->GetCameraX();
		y += m_pDGameMedia->m_pGameMedGraphic->GetCameraY();
		m_pDGameFrame->OnLPointDrag(x, y);
	}

	return TRUE;
}
LRESULT DMainFrame::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	CPoint point;
	int x = 0;
	int y = 0;

	GetCursorPos(&point);
	ScreenToClient(m_hWnd,&point);
	m_pDGameFrame->ChangeClientToGameCoor(x, y, m_pDGameMedia->m_pGameMedGraphic->GetCameraW(), m_pDGameMedia->m_pGameMedGraphic->GetCameraH(),
		(int)point.x, (int)point.y, m_nWideClient, m_nHightClient);
	x += m_pDGameMedia->m_pGameMedGraphic->GetCameraX();
	y += m_pDGameMedia->m_pGameMedGraphic->GetCameraY();
	m_pDGameFrame->OnLPointUp(x, y);

	return TRUE;

}
LRESULT DMainFrame::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	CPoint point;
	int x = 0;
	int y = 0;

	GetCursorPos(&point);
	ScreenToClient(m_hWnd, &point);
	m_pDGameFrame->ChangeClientToGameCoor(x, y, m_pDGameMedia->m_pGameMedGraphic->GetCameraW(), m_pDGameMedia->m_pGameMedGraphic->GetCameraH(),
		(int)point.x, (int)point.y, m_nWideClient, m_nHightClient);
	x += m_pDGameMedia->m_pGameMedGraphic->GetCameraX();
	y += m_pDGameMedia->m_pGameMedGraphic->GetCameraY();

	m_pDGameFrame->OnLPointDown(x, y);

	return TRUE;
}
LRESULT DMainFrame::OnRButtonUp(WPARAM wParam, LPARAM lParam)
{
	CPoint point;
	int x = 0;
	int y = 0;

	GetCursorPos(&point);
	ScreenToClient(m_hWnd, &point);
	m_pDGameFrame->ChangeClientToGameCoor(x, y, m_pDGameMedia->m_pGameMedGraphic->GetCameraW(), m_pDGameMedia->m_pGameMedGraphic->GetCameraH(),
		(int)point.x, (int)point.y, m_nWideClient, m_nHightClient);
	x += m_pDGameMedia->m_pGameMedGraphic->GetCameraX();
	y += m_pDGameMedia->m_pGameMedGraphic->GetCameraY();
	m_pDGameFrame->OnRPointUp(x, y);

	return TRUE;
}
LRESULT DMainFrame::OnRButtonDown(WPARAM wParam, LPARAM lParam)
{
	CPoint point;
	int x = 0;
	int y = 0;

	GetCursorPos(&point);
	ScreenToClient(m_hWnd, &point);
	m_pDGameFrame->ChangeClientToGameCoor(x, y, m_pDGameMedia->m_pGameMedGraphic->GetCameraW(), m_pDGameMedia->m_pGameMedGraphic->GetCameraH(),
		(int)point.x, (int)point.y, m_nWideClient, m_nHightClient);
	x += m_pDGameMedia->m_pGameMedGraphic->GetCameraX();
	y += m_pDGameMedia->m_pGameMedGraphic->GetCameraY();
	m_pDGameFrame->OnRPointDown(x, y);

	return TRUE;
}
LRESULT DMainFrame::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	m_pDGameFrame->OnKeyDown(wParam);

	return TRUE;
}
LRESULT DMainFrame::OnKeyUp(WPARAM wParam, LPARAM lParam)
{
	m_pDGameFrame->OnKeyUp(wParam);

	return TRUE;
}