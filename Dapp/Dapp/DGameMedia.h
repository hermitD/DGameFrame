#pragma once
#include "DGameMedGraphic.h"
#include "DGameMedSound.h"


class DGameMedia
{
public:
	DGameMedia();
	virtual ~DGameMedia();

	DGameMedGraphic *m_pGameMedGraphic;
	DGameMedSound *m_pGameMedSound;
};

