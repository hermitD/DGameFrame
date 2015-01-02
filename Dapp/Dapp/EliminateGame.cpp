#include "stdafx.h"
#include "EliminateGame.h"


EliminateGame::EliminateGame()
{
}


EliminateGame::~EliminateGame()
{
}


void EliminateGame::OnInit(void)
{
	//m_pGameMedia init is force to set before
	m_pMedgraphic	= m_pGameMedia->m_pGameMedGraphic;
	m_pMedSound		= m_pGameMedia->m_pGameMedSound;

}

void EliminateGame::OnExit(void)
{
	m_pMedgraphic = nullptr;
	m_pMedSound = nullptr;

}

void EliminateGame::OnLPointDown(int nX, int nY)
{
	//need to make a switch to set whether to output the debug things
	//printf("void EliminateGame::OnLPointDown( int nX, int nY )\n");
}

void EliminateGame::OnRPointDown(int nX, int nY)
{

}

void EliminateGame::OnLPointDrag(int nX, int nY)
{

}

void EliminateGame::OnRPointDrag(int nX, int nY)
{

}

void EliminateGame::OnLPointUp(int nX, int nY)
{

}

void EliminateGame::OnRPointUp(int nX, int nY)
{

}

void EliminateGame::OnKeyUp(WPARAM key)
{

}

void EliminateGame::OnKeyDown(WPARAM key)
{

}