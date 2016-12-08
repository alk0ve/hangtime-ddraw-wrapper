#include "MyIDirectDrawSurface.h"
#include "common.h"
#include "LogStructs.h"
#include "MyIDirectDraw.h"


HRESULT MyIDirectDrawSurface::Create(LPDIRECTDRAW lpDirectDraw, LPDDSURFACEDESC lpDDSurfaceDesc, LPDIRECTDRAWSURFACE FAR * lplpDDSurface, IUnknown FAR * pUnkOuter)
{
	LOG_STATIC_FUNC();
	LogSurfaceDescriptionStruct(lpDDSurfaceDesc);

	LPDIRECTDRAWSURFACE frontSurfacePtr = NULL;
	HRESULT result;

	if ((lpDDSurfaceDesc->dwFlags & DDSD_CAPS) && (lpDDSurfaceDesc->ddsCaps.dwCaps & DDSCAPS_PRIMARYSURFACE))
	{
		LOG_FORMAT("\tCreating a primary surface with back buffer");
		DDSURFACEDESC surfaceDescription = { 0 };
		LPDIRECTDRAWSURFACE backSurfacePtr = NULL;
		
		surfaceDescription.dwSize = sizeof(DDSURFACEDESC);
		surfaceDescription.dwFlags = DDSD_CAPS;
		surfaceDescription.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

		result = lpDirectDraw->CreateSurface(&surfaceDescription, &frontSurfacePtr, pUnkOuter);
		if (result != DD_OK)
		{
			LOG_FORMAT("\tCreating a primary surface failed with error code " << HEX(result));
			return DDERR_GENERIC;
		}

		ZeroMemory(&surfaceDescription, sizeof(DDSURFACEDESC));
		surfaceDescription.dwSize = sizeof(DDSURFACEDESC);
		surfaceDescription.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
		surfaceDescription.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
		surfaceDescription.dwWidth = 640;
		surfaceDescription.dwHeight = 480;

		result = lpDirectDraw->CreateSurface(&surfaceDescription, &backSurfacePtr, pUnkOuter);
		if (result != DD_OK)
		{
			LOG_FORMAT("\tCreating a primary surface failed with error code " << HEX(result));
			frontSurfacePtr->Release();
			return DDERR_GENERIC;
		}

		MyIDirectDrawSurface * myIDirectDrawSurface = new MyIDirectDrawSurface(frontSurfacePtr, backSurfacePtr, true);
		*lplpDDSurface = myIDirectDrawSurface;
		LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": returning MyIDirectDrawSurface at " << HEX(myIDirectDrawSurface));

		return DD_OK;
	}
	else
	{
		LOG_FORMAT("\tCreating a secondary surface");
		result = lpDirectDraw->CreateSurface(lpDDSurfaceDesc, &frontSurfacePtr, pUnkOuter);

		if (DD_OK != result)
		{
			LOG_FORMAT(__FILE__ << ":" << __func__ << ": call to CreateSurface failed with error " << HEX(result));
			return result;
		}

		MyIDirectDrawSurface * myIDirectDrawSurface = new MyIDirectDrawSurface(frontSurfacePtr, NULL, false);
		*lplpDDSurface = myIDirectDrawSurface;
		LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": returning MyIDirectDrawSurface at " << HEX(myIDirectDrawSurface));

		return result;
	}
}


MyIDirectDrawSurface::MyIDirectDrawSurface(LPDIRECTDRAWSURFACE frontSurfacePtr, LPDIRECTDRAWSURFACE backSurfacePtr, bool isSurfacePrimary)
	: m_frontSurfacePtr(frontSurfacePtr), m_backSurfacePtr(backSurfacePtr), m_isPrimary(isSurfacePrimary)
{}


MyIDirectDrawSurface::~MyIDirectDrawSurface()
{}

IMPL_STDMETHOD(MyIDirectDrawSurface::QueryInterface) (THIS_ REFIID riid, LPVOID FAR * ppvObj) { LOG_THIS_FUNC(); return m_frontSurfacePtr->QueryInterface(riid, ppvObj);  }

IMPL_STDMETHOD_(ULONG, MyIDirectDrawSurface::AddRef) (THIS) { LOG_THIS_FUNC(); return m_frontSurfacePtr->AddRef(); }

IMPL_STDMETHOD_(ULONG, MyIDirectDrawSurface::Release) (THIS) { LOG_THIS_FUNC(); return m_frontSurfacePtr->Release(); }

IMPL_STDMETHOD(MyIDirectDrawSurface::AddAttachedSurface)(THIS_ LPDIRECTDRAWSURFACE a) { LOG_THIS_FUNC(); return m_frontSurfacePtr->AddAttachedSurface(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::AddOverlayDirtyRect)(THIS_ LPRECT a) { LOG_THIS_FUNC(); return m_frontSurfacePtr->AddOverlayDirtyRect(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::Blt)(THIS_ LPRECT lpDestRect, LPDIRECTDRAWSURFACE lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwFlags, LPDDBLTFX lpDDBltFx)
{
	// TODO: intercept - or not?
	LOG_THIS_FUNC();

	Log("\tlpDestRect:");
	LogRect(lpDestRect);

	LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": lpDDSrcSurface = " << HEX(lpDDSrcSurface));

	Log("\tlpSrcRect:");
	LogRect(lpSrcRect);

	LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": dwFlags = " << HEX(dwFlags));

	return m_frontSurfacePtr->Blt(lpDestRect, lpDDSrcSurface, lpSrcRect, dwFlags, lpDDBltFx);
}

IMPL_STDMETHOD(MyIDirectDrawSurface::BltBatch)(THIS_ LPDDBLTBATCH a, DWORD b, DWORD c) { LOG_THIS_FUNC(); return m_frontSurfacePtr->BltBatch(a, b, c); }

IMPL_STDMETHOD(MyIDirectDrawSurface::BltFast)(THIS_ DWORD a, DWORD b, LPDIRECTDRAWSURFACE c, LPRECT d, DWORD e) { LOG_THIS_FUNC(); return m_frontSurfacePtr->BltFast(a, b, c, d, e); }

IMPL_STDMETHOD(MyIDirectDrawSurface::DeleteAttachedSurface)(THIS_ DWORD a, LPDIRECTDRAWSURFACE b) { LOG_THIS_FUNC(); return m_frontSurfacePtr->DeleteAttachedSurface(a, b); }

IMPL_STDMETHOD(MyIDirectDrawSurface::EnumAttachedSurfaces)(THIS_ LPVOID a, LPDDENUMSURFACESCALLBACK b) { LOG_THIS_FUNC(); return m_frontSurfacePtr->EnumAttachedSurfaces(a, b); }

IMPL_STDMETHOD(MyIDirectDrawSurface::EnumOverlayZOrders)(THIS_ DWORD a, LPVOID b, LPDDENUMSURFACESCALLBACK c) { LOG_THIS_FUNC(); return m_frontSurfacePtr->EnumOverlayZOrders(a, b, c); }

IMPL_STDMETHOD(MyIDirectDrawSurface::Flip)(THIS_ LPDIRECTDRAWSURFACE lpDDSurfaceTargetOverride, DWORD dwFlags)
{
	LOG_THIS_FUNC();
	LOG_FORMAT("\tlpDDSurfaceTargetOverride = " << HEX(lpDDSurfaceTargetOverride) << ", dwFlags = " << HEX(dwFlags));

	HRESULT result;
	RECT sourceRectangle;
	RECT destinationRectangle;
	POINT p;

	p.x = 0; p.y = 0;
	ClientToScreen(MyIDirectDraw::g_topLevelWindowHandle, &p);
	GetClientRect(MyIDirectDraw::g_topLevelWindowHandle, &destinationRectangle);
	OffsetRect(&destinationRectangle, p.x, p.y);
	SetRect(&sourceRectangle, 0, 0, 640, 480);
	result = m_frontSurfacePtr->Blt(&destinationRectangle, m_backSurfacePtr, &sourceRectangle, DDBLT_WAIT, NULL);

	return result;

	// return m_frontSurfacePtr->Flip(lpDDSurfaceTargetOverride, dwFlags);
}

IMPL_STDMETHOD(MyIDirectDrawSurface::GetAttachedSurface)(THIS_ LPDDSCAPS lpDDSCaps, LPDIRECTDRAWSURFACE FAR * lplpDDAttachedSurface)
{
	LOG_THIS_FUNC();
	LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": lpDDSCaps->dwCaps = " << HEX(lpDDSCaps->dwCaps));

	if ((lpDDSCaps->dwCaps & DDSCAPS_BACKBUFFER) && m_isPrimary)
	{
		LOG_FORMAT("\tReturning artificial back-buffer");
		*lplpDDAttachedSurface = m_backSurfacePtr;
		return DD_OK;
	}
	else
	{
		LOG_FORMAT("\tReturning natural buffer");
		LOG_FORMAT("\tIMPORTANT: THIS SHOULD NOT HAPPEN, SOMETHING IS WRONG");
		LPDIRECTDRAWSURFACE returnedAttachedSurface = NULL;
		HRESULT result = m_frontSurfacePtr->GetAttachedSurface(lpDDSCaps, &returnedAttachedSurface);

		LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": *lplpDDAttachedSurface [return value] = " << HEX(returnedAttachedSurface) << ", hResult = " << HEX(result));

		*lplpDDAttachedSurface = returnedAttachedSurface;

		return result;
	}
}

IMPL_STDMETHOD(MyIDirectDrawSurface::GetBltStatus)(THIS_ DWORD a) { LOG_THIS_FUNC(); return m_frontSurfacePtr->GetBltStatus(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::GetCaps)(THIS_ LPDDSCAPS a) { LOG_THIS_FUNC(); return m_frontSurfacePtr->GetCaps(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::GetClipper)(THIS_ LPDIRECTDRAWCLIPPER FAR* a) { LOG_THIS_FUNC(); return m_frontSurfacePtr->GetClipper(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::GetColorKey)(THIS_ DWORD a, LPDDCOLORKEY b) { LOG_THIS_FUNC(); return m_frontSurfacePtr->GetColorKey(a, b); }

IMPL_STDMETHOD(MyIDirectDrawSurface::GetDC)(THIS_ HDC FAR * a) { LOG_THIS_FUNC(); return m_frontSurfacePtr->GetDC(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::GetFlipStatus)(THIS_ DWORD a) { LOG_THIS_FUNC(); return m_frontSurfacePtr->GetFlipStatus(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::GetOverlayPosition)(THIS_ LPLONG a, LPLONG b) { LOG_THIS_FUNC(); return m_frontSurfacePtr->GetOverlayPosition(a, b); }

IMPL_STDMETHOD(MyIDirectDrawSurface::GetPalette)(THIS_ LPDIRECTDRAWPALETTE FAR* a) { LOG_THIS_FUNC(); return m_frontSurfacePtr->GetPalette(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::GetPixelFormat)(THIS_ LPDDPIXELFORMAT a) { LOG_THIS_FUNC(); return m_frontSurfacePtr->GetPixelFormat(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::GetSurfaceDesc)(THIS_ LPDDSURFACEDESC a) { LOG_THIS_FUNC(); return m_frontSurfacePtr->GetSurfaceDesc(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::Initialize)(THIS_ LPDIRECTDRAW a, LPDDSURFACEDESC b) { LOG_THIS_FUNC(); return m_frontSurfacePtr->Initialize(a, b); }

IMPL_STDMETHOD(MyIDirectDrawSurface::IsLost)(THIS) { LOG_THIS_FUNC(); return m_frontSurfacePtr->IsLost(); }

IMPL_STDMETHOD(MyIDirectDrawSurface::Lock)(THIS_ LPRECT lpDestRect, LPDDSURFACEDESC lpDDSurfaceDesc, DWORD dwFlags, HANDLE hEvent)
{
	// TODO: INTERCEPT - or not?
	LOG_THIS_FUNC();

	Log("\tlpDestRect:");
	LogRect(lpDestRect);

	Log("\tlpDDSurfaceDesc BEFORE LOCK:");
	LogSurfaceDescriptionStruct(lpDDSurfaceDesc);

	LOG_FORMAT("\tdwFlags = " << HEX(dwFlags));

	HRESULT result = m_frontSurfacePtr->Lock(lpDestRect, lpDDSurfaceDesc, dwFlags, hEvent);

	LOG_FORMAT("\tlpDDSurfaceDesc AFTER LOCK [hResult = " << HEX(result) << "]:");
	LogSurfaceDescriptionStruct(lpDDSurfaceDesc);

	return result;
}

IMPL_STDMETHOD(MyIDirectDrawSurface::ReleaseDC)(THIS_ HDC a) { LOG_THIS_FUNC(); return m_frontSurfacePtr->ReleaseDC(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::Restore)(THIS) { LOG_THIS_FUNC(); return m_frontSurfacePtr->Restore(); }

IMPL_STDMETHOD(MyIDirectDrawSurface::SetClipper)(THIS_ LPDIRECTDRAWCLIPPER a) { LOG_THIS_FUNC(); return m_frontSurfacePtr->SetClipper(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::SetColorKey)(THIS_ DWORD a, LPDDCOLORKEY b) { LOG_THIS_FUNC(); return m_frontSurfacePtr->SetColorKey(a, b); }

IMPL_STDMETHOD(MyIDirectDrawSurface::SetOverlayPosition)(THIS_ LONG a, LONG b) { LOG_THIS_FUNC(); return m_frontSurfacePtr->SetOverlayPosition(a, b); }

IMPL_STDMETHOD(MyIDirectDrawSurface::SetPalette)(THIS_ LPDIRECTDRAWPALETTE a) { LOG_THIS_FUNC(); return m_frontSurfacePtr->SetPalette(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::Unlock)(THIS_ LPVOID lpRectMaybe)
{
	// TODO: INTERCEPT - or not?
	LOG_THIS_FUNC();
	return m_frontSurfacePtr->Unlock(lpRectMaybe);
}

IMPL_STDMETHOD(MyIDirectDrawSurface::UpdateOverlay)(THIS_ LPRECT a, LPDIRECTDRAWSURFACE b, LPRECT c, DWORD d, LPDDOVERLAYFX e) { LOG_THIS_FUNC(); return m_frontSurfacePtr->UpdateOverlay(a, b, c, d, e); }

IMPL_STDMETHOD(MyIDirectDrawSurface::UpdateOverlayDisplay)(THIS_ DWORD a) { LOG_THIS_FUNC(); return m_frontSurfacePtr->UpdateOverlayDisplay(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::UpdateOverlayZOrder)(THIS_ DWORD a, LPDIRECTDRAWSURFACE b) { LOG_THIS_FUNC(); return m_frontSurfacePtr->UpdateOverlayZOrder(a, b); }

