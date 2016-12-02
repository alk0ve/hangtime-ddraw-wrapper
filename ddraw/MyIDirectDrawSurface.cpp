#include "MyIDirectDrawSurface.h"
#include "common.h"
#include "LogStructs.h"



MyIDirectDrawSurface::MyIDirectDrawSurface(LPDIRECTDRAWSURFACE directDrawSurfacePtr)
	: m_iDirectDrawSurface(directDrawSurfacePtr)
{}


MyIDirectDrawSurface::~MyIDirectDrawSurface()
{}

IMPL_STDMETHOD(MyIDirectDrawSurface::QueryInterface) (THIS_ REFIID riid, LPVOID FAR * ppvObj) { LOG_THIS_FUNC(); return m_iDirectDrawSurface->QueryInterface(riid, ppvObj);  }

IMPL_STDMETHOD_(ULONG, MyIDirectDrawSurface::AddRef) (THIS) { LOG_THIS_FUNC(); return m_iDirectDrawSurface->AddRef(); }

IMPL_STDMETHOD_(ULONG, MyIDirectDrawSurface::Release) (THIS) { LOG_THIS_FUNC(); return m_iDirectDrawSurface->Release(); }

IMPL_STDMETHOD(MyIDirectDrawSurface::AddAttachedSurface)(THIS_ LPDIRECTDRAWSURFACE a) { LOG_THIS_FUNC(); return m_iDirectDrawSurface->AddAttachedSurface(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::AddOverlayDirtyRect)(THIS_ LPRECT a) { LOG_THIS_FUNC(); return m_iDirectDrawSurface->AddOverlayDirtyRect(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::Blt)(THIS_ LPRECT lpDestRect, LPDIRECTDRAWSURFACE lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwFlags, LPDDBLTFX lpDDBltFx)
{
	// TODO: intercept @@@@@@@@@@@@@@@
	LOG_THIS_FUNC();

	Log("\tlpDestRect:");
	LogRect(lpDestRect);

	LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": lpDDSrcSurface = " << HEX(lpDDSrcSurface));

	Log("\tlpSrcRect:");
	LogRect(lpSrcRect);

	LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": dwFlags = " << HEX(dwFlags));

	return m_iDirectDrawSurface->Blt(lpDestRect, lpDDSrcSurface, lpSrcRect, dwFlags, lpDDBltFx);
}

IMPL_STDMETHOD(MyIDirectDrawSurface::BltBatch)(THIS_ LPDDBLTBATCH a, DWORD b, DWORD c) { LOG_THIS_FUNC(); return m_iDirectDrawSurface->BltBatch(a, b, c); }

IMPL_STDMETHOD(MyIDirectDrawSurface::BltFast)(THIS_ DWORD a, DWORD b, LPDIRECTDRAWSURFACE c, LPRECT d, DWORD e) { LOG_THIS_FUNC(); return m_iDirectDrawSurface->BltFast(a, b, c, d, e); }

IMPL_STDMETHOD(MyIDirectDrawSurface::DeleteAttachedSurface)(THIS_ DWORD a, LPDIRECTDRAWSURFACE b) { LOG_THIS_FUNC(); return m_iDirectDrawSurface->DeleteAttachedSurface(a, b); }

IMPL_STDMETHOD(MyIDirectDrawSurface::EnumAttachedSurfaces)(THIS_ LPVOID a, LPDDENUMSURFACESCALLBACK b) { LOG_THIS_FUNC(); return m_iDirectDrawSurface->EnumAttachedSurfaces(a, b); }

IMPL_STDMETHOD(MyIDirectDrawSurface::EnumOverlayZOrders)(THIS_ DWORD a, LPVOID b, LPDDENUMSURFACESCALLBACK c) { LOG_THIS_FUNC(); return m_iDirectDrawSurface->EnumOverlayZOrders(a, b, c); }

IMPL_STDMETHOD(MyIDirectDrawSurface::Flip)(THIS_ LPDIRECTDRAWSURFACE lpDDSurfaceTargetOverride, DWORD dwFlags)
{
	// TODO: INTERCEPT @@@@@@@@@@@@@@@@@@@@@@@@@
	LOG_FORMAT(__FILE__ << ":" << __func__ << "(lpDDSurfaceTargetOverride = " << HEX(lpDDSurfaceTargetOverride) << ", dwFlags = " << HEX(dwFlags) << ")");
	return m_iDirectDrawSurface->Flip(lpDDSurfaceTargetOverride, dwFlags);
}

IMPL_STDMETHOD(MyIDirectDrawSurface::GetAttachedSurface)(THIS_ LPDDSCAPS lpDDSCaps, LPDIRECTDRAWSURFACE FAR * lplpDDAttachedSurface)
{
	// TODO: INTERCEPT @@@@@@@@@@@@@@@@@@@@@@
	LOG_THIS_FUNC();
	LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": lpDDSCaps->dwCaps = " << HEX(lpDDSCaps->dwCaps));
	LPDIRECTDRAWSURFACE returnedAttachedSurface = NULL;
	HRESULT result =  m_iDirectDrawSurface->GetAttachedSurface(lpDDSCaps, &returnedAttachedSurface);

	LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": *lplpDDAttachedSurface [return value] = " << HEX(returnedAttachedSurface) << ", hResult =" << HEX(result));

	*lplpDDAttachedSurface = returnedAttachedSurface;
	return result;
}

IMPL_STDMETHOD(MyIDirectDrawSurface::GetBltStatus)(THIS_ DWORD a) { LOG_THIS_FUNC(); return m_iDirectDrawSurface->GetBltStatus(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::GetCaps)(THIS_ LPDDSCAPS a) { LOG_THIS_FUNC(); return m_iDirectDrawSurface->GetCaps(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::GetClipper)(THIS_ LPDIRECTDRAWCLIPPER FAR* a) { LOG_THIS_FUNC(); return m_iDirectDrawSurface->GetClipper(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::GetColorKey)(THIS_ DWORD a, LPDDCOLORKEY b) { LOG_THIS_FUNC(); return m_iDirectDrawSurface->GetColorKey(a, b); }

IMPL_STDMETHOD(MyIDirectDrawSurface::GetDC)(THIS_ HDC FAR * a) { LOG_THIS_FUNC(); return m_iDirectDrawSurface->GetDC(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::GetFlipStatus)(THIS_ DWORD a) { LOG_THIS_FUNC(); return m_iDirectDrawSurface->GetFlipStatus(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::GetOverlayPosition)(THIS_ LPLONG a, LPLONG b) { LOG_THIS_FUNC(); return m_iDirectDrawSurface->GetOverlayPosition(a, b); }

IMPL_STDMETHOD(MyIDirectDrawSurface::GetPalette)(THIS_ LPDIRECTDRAWPALETTE FAR* a) { LOG_THIS_FUNC(); return m_iDirectDrawSurface->GetPalette(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::GetPixelFormat)(THIS_ LPDDPIXELFORMAT a) { LOG_THIS_FUNC(); return m_iDirectDrawSurface->GetPixelFormat(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::GetSurfaceDesc)(THIS_ LPDDSURFACEDESC a) { LOG_THIS_FUNC(); return m_iDirectDrawSurface->GetSurfaceDesc(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::Initialize)(THIS_ LPDIRECTDRAW a, LPDDSURFACEDESC b) { LOG_THIS_FUNC(); return m_iDirectDrawSurface->Initialize(a, b); }

IMPL_STDMETHOD(MyIDirectDrawSurface::IsLost)(THIS) { LOG_THIS_FUNC(); return m_iDirectDrawSurface->IsLost(); }

IMPL_STDMETHOD(MyIDirectDrawSurface::Lock)(THIS_ LPRECT lpDestRect, LPDDSURFACEDESC lpDDSurfaceDesc, DWORD dwFlags, HANDLE hEvent)
{
	// TODO: INTERCEPT @@@@@@@@@@@@@@@@@@@@@@@@
	LOG_THIS_FUNC();

	Log("\tlpDestRect:");
	LogRect(lpDestRect);

	Log("\tlpDDSurfaceDesc BEFORE LOCK:");
	LogSurfaceDescriptionStruct(lpDDSurfaceDesc);

	LOG_FORMAT("\tdwFlags = " << HEX(dwFlags));

	HRESULT result = m_iDirectDrawSurface->Lock(lpDestRect, lpDDSurfaceDesc, dwFlags, hEvent);

	LOG_FORMAT("\tlpDDSurfaceDesc AFTER LOCK [hResult = " << HEX(result) << "]:");
	LogSurfaceDescriptionStruct(lpDDSurfaceDesc);

	return result;
}

IMPL_STDMETHOD(MyIDirectDrawSurface::ReleaseDC)(THIS_ HDC a) { LOG_THIS_FUNC(); return m_iDirectDrawSurface->ReleaseDC(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::Restore)(THIS) { LOG_THIS_FUNC(); return m_iDirectDrawSurface->Restore(); }

IMPL_STDMETHOD(MyIDirectDrawSurface::SetClipper)(THIS_ LPDIRECTDRAWCLIPPER a) { LOG_THIS_FUNC(); return m_iDirectDrawSurface->SetClipper(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::SetColorKey)(THIS_ DWORD a, LPDDCOLORKEY b) { LOG_THIS_FUNC(); return m_iDirectDrawSurface->SetColorKey(a, b); }

IMPL_STDMETHOD(MyIDirectDrawSurface::SetOverlayPosition)(THIS_ LONG a, LONG b) { LOG_THIS_FUNC(); return m_iDirectDrawSurface->SetOverlayPosition(a, b); }

IMPL_STDMETHOD(MyIDirectDrawSurface::SetPalette)(THIS_ LPDIRECTDRAWPALETTE a) { LOG_THIS_FUNC(); return m_iDirectDrawSurface->SetPalette(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::Unlock)(THIS_ LPVOID lpRectMaybe)
{
	// TODO: INTERCEPT @@@@@@@@@@@@@@@@@@@@@@@@
	LOG_THIS_FUNC();
	return m_iDirectDrawSurface->Unlock(lpRectMaybe);
}

IMPL_STDMETHOD(MyIDirectDrawSurface::UpdateOverlay)(THIS_ LPRECT a, LPDIRECTDRAWSURFACE b, LPRECT c, DWORD d, LPDDOVERLAYFX e) { LOG_THIS_FUNC(); return m_iDirectDrawSurface->UpdateOverlay(a, b, c, d, e); }

IMPL_STDMETHOD(MyIDirectDrawSurface::UpdateOverlayDisplay)(THIS_ DWORD a) { LOG_THIS_FUNC(); return m_iDirectDrawSurface->UpdateOverlayDisplay(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::UpdateOverlayZOrder)(THIS_ DWORD a, LPDIRECTDRAWSURFACE b) { LOG_THIS_FUNC(); return m_iDirectDrawSurface->UpdateOverlayZOrder(a, b); }

