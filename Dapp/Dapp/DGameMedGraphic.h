#pragma once

#include <gdiplus.h>
using namespace Gdiplus;

struct SMatrixList
{
	Matrix *pMatrix;
	SMatrixList *next;
};


class DGameMedGraphic
{
public:
	DGameMedGraphic();
	virtual ~DGameMedGraphic();


	/*Camera System */
	int GetCameraX(void);
	int GetCameraY(void);
	int GetCameraW(void);
	int GetCameraH(void);
	void SetCamera(int x, int y, int w, int h);
public:
	int m_cameraX;
	int m_cameraY;
	int m_cameraW;
	int m_cameraH;
	/*Camera System */


	/*Abstract GDI interface */
	void LoadBMPfile(HBITMAP &hbitmap_s, LPWSTR filename); // for example, LoadBMPfile(GameIndex0, "res\\start\\starting.bmp");
	void FreeBMPHandle(HBITMAP hbitmap_s);
	int GetBMPWidth(HBITMAP hbitmap);
	int GetBMPHeight(HBITMAP hbitmap);
	void DrawBMP(HBITMAP hbitmap_source, int x, int y, COLORREF trans_color, int turnWSign = 0, int turnHSign = 0);
	void DrawBMP(HBITMAP hbitmap_source, int x, int y, int turnWSign = 0, int turnHSign = 0); // 没有透明色 not have transparent color
	void DrawLine(int nXBegin, int nYBegin, int nXEnd, int nYEnd, int nWidth = 2, COLORREF crColor = RGB(100, 100, 100), int nPenStyle = PS_SOLID);
	void DrawTextWM(int nPointSize, LPCTSTR lpszFaceName, COLORREF color, int x, int y, CString text); // for example, DrawText(100, "宋体", RGB(255, 255, 255), 320, 0, "Hello world!");
	void DrawRect(int nX, int nY, int nW, int nH, COLORREF color);
	void DrawPolygon(const POINT* lpPoints, int nCount, COLORREF color);
	void DrawEllipse(int nX, int nY, int nW, int nH, COLORREF color);
	/*Abstract GDI interface */


	/*Abstract GDI+ interface */
	Image* LoadImageWM(LPCWSTR filename); // for example, m_pImgTest = m_pGraphic->LoadImageWM(L"res//Bkgnd.png");
	static ARGB GetColorAlpha(DWORD r, DWORD g, DWORD b, DWORD a);
	void FreeImageWM(Image* image);
	void DrawImageWM(Image* image, float x, float y);
	void DrawImageWM(Image* image, float x, float y, float w, float h);
	void PushMatrixWM(void);
	void PopMatrixWM(void);
	void TranslateMatrixWM(float dx, float dy);
	void RotateMatrixWM(float degrees);
	void ScaleMatrixWM(float sx, float sy);
	void ResetMatrixWM(void);
	Graphics* GetGDIPlusWM(void); // if you want to transform something, please call GDIPlus function.
	void SetGDIPlusWM(Graphics *pGraphics);
	void SetNullGDIPlusWM(void);
	void FreeMartixList(void);
public:
	GdiplusStartupInput m_Gdiplus;	// 定义 GDI+ 初始化变量
	ULONG_PTR m_pGdiToken;			// 定义 GID+ 标识
	Graphics *m_pGDIPlusWM;
	SMatrixList m_SMatrixList;
	/*Abstract GDI+ interface */


	void SetMemDc(CDC * pMemDc);
	CDC* GetCDC(void);
	void SetNullMemDC(void);
public:
	CDC *m_pMemDC;

};

