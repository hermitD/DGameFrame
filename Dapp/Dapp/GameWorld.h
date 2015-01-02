#pragma once
#include "DGameMedGraphic.h"
#include "DGameMedSound.h"

class GameWorld
{
public:
	GameWorld();
	~GameWorld();

	GameWorld *m_pGameworld;

	DGameMedGraphic *m_pMedGraphic;
	DGameMedSound *m_pMedsound;
};

