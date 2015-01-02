#pragma once
#include "DGameTheGame.h"
class DGameTest :
	public DGameTheGame
{
public:
	DGameTest();
	~DGameTest();


	virtual void OnInit(void);
	virtual void Draw(int dt);
	virtual void OnLPointUp(int nX, int nY);
};

