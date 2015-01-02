#include "stdafx.h"
#include "DGameFrame.h"


DGameFrame::DGameFrame()
{
}


DGameFrame::DGameFrame(void *pObserve, DGameMedia *pDGameMedia)
{
	m_pTheGame = nullptr;
	m_pGameMedia = pDGameMedia;
	m_pObserve = pObserve;


	m_bLPointDownSign = false;
	m_bRPointDownSign = false; 

	for (int i = 0; i < ASCII_NUM; i++)
	{
		m_bKeyArray[i] = false;
	}

}


DGameFrame::~DGameFrame()
{
	OnExit();
	m_pGameMedia = nullptr;
	m_pObserve = nullptr;
	SafeDelete(m_pTheGame);

}


void DGameFrame::OnInit(void) //像这种类似的函数就是在主程序中接受消息 然后给调用其成员来响应
{
	if (m_pTheGame != NULL)
	{
		m_pTheGame->OnInit();
	}

}

void DGameFrame::OnExit(void)
{
	if (m_pTheGame != NULL)
	{
		m_pTheGame->OnExit();
	}
}

void DGameFrame::Update(int dt)
{
	if (m_pTheGame != NULL)
	{
		m_pTheGame->Update(dt);
	}
}

void DGameFrame::Draw(int dt)
{
	if (m_pTheGame != NULL)
	{
		m_pTheGame->Draw(dt);
	}
}

void DGameFrame::OnLPointDrag(int nX, int nY)
{
	if (m_pTheGame != NULL)
	{
		m_pTheGame->OnLPointDrag(nX, nY);
	}
}

void DGameFrame::OnRPointDrag(int nX, int nY)
{
	if (m_pTheGame != NULL)
	{
		m_pTheGame->OnRPointDrag(nX, nY);
	}
}

void DGameFrame::OnLPointUp(int nX, int nY)
{
	m_bLPointDownSign = false;
	if (m_pTheGame != NULL)
	{
		m_pTheGame->m_bLPointDownSign = false;
		m_pTheGame->OnLPointUp(nX, nY);
	}
}

void DGameFrame::OnRPointUp(int nX, int nY)
{
	m_bRPointDownSign = false;
	if (m_pTheGame != NULL)
	{
		m_pTheGame->m_bRPointDownSign = false;
		m_pTheGame->OnRPointUp(nX, nY);
	}
}

void DGameFrame::OnLPointDown(int nX, int nY)
{
	m_bLPointDownSign = true;
	if (m_pTheGame != NULL)
	{
		m_pTheGame->m_bLPointDownSign = true;
		m_pTheGame->OnLPointDown(nX, nY);
	}
}

void DGameFrame::OnRPointDown(int nX, int nY)
{
	m_bRPointDownSign = true;
	if (m_pTheGame != NULL)
	{
		m_pTheGame->m_bRPointDownSign = true;
		m_pTheGame->OnRPointDown(nX, nY);
	}
}

void DGameFrame::OnKeyUp(WPARAM key)
{
	if (key >= 0 && key < ASCII_NUM)
	{
		m_bKeyArray[key] = false;
	}
	if (m_pTheGame != NULL)
	{
		if (key >= 0 && key < ASCII_NUM)
		{
			m_pTheGame->m_bKeyArray[key] = false;
		}
		m_pTheGame->OnKeyUp(key);
	}
}

void DGameFrame::OnKeyDown(WPARAM key)
{
	if (key >= 0 && key < ASCII_NUM)
	{
		m_bKeyArray[key] = true;
	}
	if (m_pTheGame != NULL)
	{
		if (key >= 0 && key < ASCII_NUM)
		{
			m_pTheGame->m_bKeyArray[key] = true;
		}
		m_pTheGame->OnKeyDown(key);
	}
}




//ChangeClientToGameCoor 未知
void DGameFrame::ChangeClientToGameCoor(int &gameX, int &gameY, int gameW, int gameH, int clientX, int clientY, int clientW, int clientH)
{
	if (clientW == 0)
	{
		clientW = 1;
	}
	if (clientH == 0)
	{
		clientH = 1;
	}
	gameX = (int)(gameW * clientX / (1.0f * clientW));
	gameY = (int)(gameH * clientY / (1.0f * clientH));
}



DGameTheGame*  DGameFrame::RunLayer(DGameTheGame *pDTheGame)
{
	DGameTheGame* pLastGamePlay = m_pTheGame;
	if (pLastGamePlay != NULL)	//如果不为空就退出
	{
		pLastGamePlay->OnExit();
	}
	m_pTheGame = pDTheGame;	//把成员变量给本身然后进行初始化 进行新的游戏
	if (m_pTheGame != NULL)
	{
		m_pTheGame->m_pObserve = this;
		m_pTheGame->m_pGameMedia = m_pGameMedia;
		m_pTheGame->OnInit();
	}

	return pLastGamePlay;
}