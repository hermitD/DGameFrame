#include "stdafx.h"
#include "DGameTest.h"


DGameTest::DGameTest()
{
}


DGameTest::~DGameTest()
{


}
void DGameTest::OnInit(void)
{

}

void DGameTest::Draw(int dt)
{
	
	HBITMAP HBk;
	m_pGameMedia->m_pGameMedGraphic->LoadBMPfile(HBk, _T("Materials\\bk.bmp"));
	m_pGameMedia->m_pGameMedGraphic->DrawBMP(HBk, 0, 75);


	//m_pGameMedia->m_pGameMedGraphic->DrawRect(300, 300, 100, 100, RGB(255, 255, 0));
	m_pGameMedia->m_pGameMedGraphic->DrawRect(0, 550, 949, 100, RGB(255, 255, 0));
	//m_pGameMedia->m_pGameMedGraphic->DrawEllipse
}

void DGameTest::OnLPointUp(int nX, int nY)
{
	printf("Left Button Down %d  ,  %d\n", nX, nY);
}
