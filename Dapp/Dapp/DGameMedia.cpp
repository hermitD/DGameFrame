#include "stdafx.h"
#include "DGameDefine.h"
#include "DGameMedia.h"


DGameMedia::DGameMedia()
{
	m_pGameMedGraphic = nullptr;
	m_pGameMedSound = nullptr;
	m_pGameMedGraphic = SAFE_NEW DGameMedGraphic;
	if (m_pGameMedGraphic == nullptr)
	{
		MessageBox(NULL, _T("failed to new DGameMedGraphic"), _T("Error"), MB_OK | MB_ICONASTERISK);
		exit(0);
	}
	m_pGameMedSound = SAFE_NEW DGameMedSound;
	if (m_pGameMedSound == NULL)
	{
		MessageBox(NULL, _T("failed to new m_pGameMedSound!"), TEXT("Error!"), MB_OK | MB_ICONASTERISK);
		exit(0);
	}
}


DGameMedia::~DGameMedia()
{
	SAFE_DELETE(m_pGameMedGraphic);
	SAFE_DELETE(m_pGameMedSound);
}
