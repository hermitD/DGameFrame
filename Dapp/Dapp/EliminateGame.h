#pragma once
#include "DGameTheGame.h"
#include "GameWorld.h"


class EliminateGame :
	public DGameTheGame
{
public:
	EliminateGame();
	~EliminateGame();

	virtual void OnInit(void);
	virtual void OnExit(void);
	virtual void OnLPointDown(int nX, int nY);
	virtual void OnRPointDown(int nX, int nY);
	virtual void OnLPointDrag(int nX, int nY);
	virtual void OnRPointDrag(int nX, int nY);
	virtual void OnLPointUp(int nX, int nY);
	virtual void OnRPointUp(int nX, int nY);
	virtual void OnKeyUp(WPARAM key);
	virtual void OnKeyDown(WPARAM key);


public:
	//define to easy use
	DGameMedGraphic *m_pMedgraphic;
	DGameMedSound	*m_pMedSound;
	GameWorld		*m_pGameWorld;
};

