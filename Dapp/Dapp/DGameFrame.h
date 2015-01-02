#pragma once
#include "DGameMedia.h"
#include "DGameTheGame.h"
#include "DGameDefine.h"

class DGameFrame
{
public:
	DGameFrame(void);
	DGameFrame(void *pObserve, DGameMedia *pDGameMedia);
	virtual ~DGameFrame();

	void OnInit(void);
	void OnExit(void);
	void OnLPointUp(int nX, int nY);
	void OnRPointUp(int nX, int nY);
	void OnLPointDrag(int nX, int nY);
	void OnRPointDrag(int nX, int nY);
	void OnLPointDown(int nX, int nY);
	void OnRPointDown(int nX, int nY);
	void OnKeyUp(WPARAM key);
	void OnKeyDown(WPARAM key);


	void Update(int dt);
	void Draw(int dt); //?


	void ChangeClientToGameCoor(int &gameX, int &gameY, int gameW, int gameH, int clientX, int clientY, int clientW, int clientH);
	DGameTheGame* RunLayer(DGameTheGame *pDTheGame);


	bool m_bLPointDownSign;
	bool m_bRPointDownSign;
	bool m_bKeyArray[ASCII_NUM];


	void *m_pObserve;
	DGameMedia		*m_pGameMedia;
	DGameTheGame	*m_pTheGame;

};

