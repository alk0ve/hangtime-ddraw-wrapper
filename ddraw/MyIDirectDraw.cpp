#include "MyIDirectDraw.h"
#include "MyIDirectDrawSurface.h"
#include "LogStructs.h"

EmulatedDisplayMode g_emulatedDisplayMode = { 0 };

HWND MyIDirectDraw::g_topLevelWindowHandle = NULL;
DWORD MyIDirectDraw::g_emulatedCooperativeLevelFlags = 0;


MyIDirectDraw::MyIDirectDraw(LPDIRECTDRAW iDirectDraw)
	: m_iDirectDraw(iDirectDraw)
{}


MyIDirectDraw::~MyIDirectDraw()
{
	// nothing
}


IMPL_STDMETHOD(MyIDirectDraw::QueryInterface) (THIS_ REFIID riid, LPVOID FAR * ppvObj)
{
	LOG_THIS_FUNC();
	return m_iDirectDraw->QueryInterface(riid, ppvObj);
}

IMPL_STDMETHOD_(ULONG, MyIDirectDraw::AddRef) (THIS) 
{
	LOG_THIS_FUNC();
	return m_iDirectDraw->AddRef();
}

IMPL_STDMETHOD_(ULONG, MyIDirectDraw::Release) (THIS)
{
	LOG_THIS_FUNC();
	return m_iDirectDraw->Release();
}

/*** IDirectDraw methods ***/
IMPL_STDMETHOD(MyIDirectDraw::Compact)(THIS)
{
	LOG_THIS_FUNC();
	return m_iDirectDraw->Compact();
}

IMPL_STDMETHOD(MyIDirectDraw::CreateClipper)(THIS_ DWORD a, LPDIRECTDRAWCLIPPER FAR* b, IUnknown FAR * c)
{
	LOG_THIS_FUNC();
	return m_iDirectDraw->CreateClipper(a, b, c);
}

IMPL_STDMETHOD(MyIDirectDraw::CreatePalette)(THIS_ DWORD a, LPPALETTEENTRY b, LPDIRECTDRAWPALETTE FAR* c, IUnknown FAR * d)
{
	LOG_THIS_FUNC();
	return m_iDirectDraw->CreatePalette(a, b, c, d);
}

IMPL_STDMETHOD(MyIDirectDraw::CreateSurface)(THIS_ LPDDSURFACEDESC lpDDSurfaceDesc, LPDIRECTDRAWSURFACE FAR * lplpDDSurface, IUnknown FAR * pUnkOuter)
{
	LOG_THIS_FUNC();
	return MyIDirectDrawSurface::Create(m_iDirectDraw, lpDDSurfaceDesc, lplpDDSurface, pUnkOuter);
}

IMPL_STDMETHOD(MyIDirectDraw::DuplicateSurface)(THIS_ LPDIRECTDRAWSURFACE a, LPDIRECTDRAWSURFACE FAR * b)
{
	LOG_THIS_FUNC();
	return m_iDirectDraw->DuplicateSurface(a, b);
}

IMPL_STDMETHOD(MyIDirectDraw::EnumDisplayModes)(THIS_ DWORD a, LPDDSURFACEDESC b, LPVOID c, LPDDENUMMODESCALLBACK d)
{
	LOG_THIS_FUNC();
	return m_iDirectDraw->EnumDisplayModes(a, b, c, d);
}

IMPL_STDMETHOD(MyIDirectDraw::EnumSurfaces)(THIS_ DWORD a, LPDDSURFACEDESC b, LPVOID c, LPDDENUMSURFACESCALLBACK d)
{
	LOG_THIS_FUNC();
	return m_iDirectDraw->EnumSurfaces(a, b, c, d);
}

IMPL_STDMETHOD(MyIDirectDraw::FlipToGDISurface)(THIS)
{
	LOG_THIS_FUNC();
	return m_iDirectDraw->FlipToGDISurface();
}


IMPL_STDMETHOD(MyIDirectDraw::GetCaps)(THIS_ LPDDCAPS a, LPDDCAPS b)
{
	LOG_THIS_FUNC();
	return m_iDirectDraw->GetCaps(a, b);
}

IMPL_STDMETHOD(MyIDirectDraw::GetDisplayMode)(THIS_ LPDDSURFACEDESC a)
{
	// in theory we should intercept this, but
	// it seems that Hangtime never calls it
	LOG_THIS_FUNC();
	return m_iDirectDraw->GetDisplayMode(a);
}

IMPL_STDMETHOD(MyIDirectDraw::GetFourCCCodes)(THIS_  LPDWORD a, LPDWORD b)
{
	LOG_THIS_FUNC();
	return m_iDirectDraw->GetFourCCCodes(a, b);
}

IMPL_STDMETHOD(MyIDirectDraw::GetGDISurface)(THIS_ LPDIRECTDRAWSURFACE FAR * a)
{
	LOG_THIS_FUNC();
	return m_iDirectDraw->GetGDISurface(a);
}

IMPL_STDMETHOD(MyIDirectDraw::GetMonitorFrequency)(THIS_ LPDWORD a)
{
	LOG_THIS_FUNC();
	return m_iDirectDraw->GetMonitorFrequency(a);
}

IMPL_STDMETHOD(MyIDirectDraw::GetScanLine)(THIS_ LPDWORD a)
{
	LOG_THIS_FUNC();
	return m_iDirectDraw->GetScanLine(a);
}

IMPL_STDMETHOD(MyIDirectDraw::GetVerticalBlankStatus)(THIS_ LPBOOL a)
{
	LOG_THIS_FUNC();
	return m_iDirectDraw->GetVerticalBlankStatus(a);
}

IMPL_STDMETHOD(MyIDirectDraw::Initialize)(THIS_ GUID FAR * a)
{
	LOG_THIS_FUNC();
	return m_iDirectDraw->Initialize(a);
}

IMPL_STDMETHOD(MyIDirectDraw::RestoreDisplayMode)(THIS)
{
	LOG_THIS_FUNC();
	// return m_iDirectDraw->RestoreDisplayMode();
	return DD_OK;
}

IMPL_STDMETHOD(MyIDirectDraw::SetCooperativeLevel)(THIS_ HWND hWnd, DWORD dwFlags)
{
	// TODO: intercept
	LOG_THIS_FUNC();
	LOG_FORMAT("\thWnd = " << HEX(hWnd) << ", dwFlags = " << HEX(dwFlags));
	g_emulatedCooperativeLevelFlags = dwFlags;
	g_topLevelWindowHandle = hWnd;

	// return m_iDirectDraw->SetCooperativeLevel(hWnd, dwFlags);
	return m_iDirectDraw->SetCooperativeLevel(hWnd, DDSCL_NORMAL);
}

IMPL_STDMETHOD(MyIDirectDraw::SetDisplayMode)(THIS_ DWORD dwWidth, DWORD dwHeight, DWORD dwBPP)
{
	LOG_THIS_FUNC();
	//return m_iDirectDraw->SetDisplayMode(dwWidth, dwHeight, dwBPP);
	g_emulatedDisplayMode.dwWidth = dwWidth;
	g_emulatedDisplayMode.dwHeight = dwHeight;
	g_emulatedDisplayMode.dwBPP = dwBPP;

	return DD_OK;
}

IMPL_STDMETHOD(MyIDirectDraw::WaitForVerticalBlank)(THIS_ DWORD a, HANDLE b)
{
	LOG_THIS_FUNC();
	return m_iDirectDraw->WaitForVerticalBlank(a, b);
}

