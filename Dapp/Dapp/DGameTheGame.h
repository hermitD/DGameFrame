#pragma once
#include "DGameMedia.h"
#include "DGameDefine.h"

class DGameTheGame
{
public:
	DGameTheGame();
	~DGameTheGame();

	virtual void OnInit(void) = 0; 
	virtual void OnExit(void); 
	virtual void OnLPointDown(int nX, int nY); 
	virtual void OnRPointDown(int nX, int nY); 
	virtual void OnLPointDrag(int nX, int nY); 
	virtual void OnRPointDrag(int nX, int nY);
	virtual void OnLPointUp(int nX, int nY); 
	virtual void OnRPointUp(int nX, int nY); 
	virtual void OnKeyUp(WPARAM key);
	virtual void OnKeyDown(WPARAM key); 
	virtual void Update(int dt); 
	virtual void Draw(int dt); 
	void *m_pObserve;
	DGameMedia *m_pGameMedia;


	bool m_bLPointDownSign;
	bool m_bRPointDownSign;
	bool m_bKeyArray[ASCII_NUM];
};

