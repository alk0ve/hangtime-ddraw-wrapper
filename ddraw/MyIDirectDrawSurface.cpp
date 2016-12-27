#include "MyIDirectDrawSurface.h"
#include "common.h"
#include "LogStructs.h"
#include "MyIDirectDraw.h"


MyIDirectDrawSurface * g_wrappedSurfaces[MyIDirectDrawSurface::MAX_NUM_WRAPPED_SURFACES] = { 0 };
unsigned int g_numWrappedSurfaces = 0;


HRESULT MyIDirectDrawSurface::Create(LPDIRECTDRAW lpDirectDraw, LPDDSURFACEDESC lpDDSurfaceDesc, LPDIRECTDRAWSURFACE FAR * lplpDDSurface, IUnknown FAR * pUnkOuter)
{
	LOG_STATIC_FUNC();
	LogSurfaceDescriptionStruct(lpDDSurfaceDesc);

	LPDIRECTDRAWSURFACE frontSurfacePtr = NULL;
	HRESULT result;

	if ((lpDDSurfaceDesc->dwFlags & DDSD_CAPS) && (lpDDSurfaceDesc->ddsCaps.dwCaps & DDSCAPS_PRIMARYSURFACE))
	{
		if ((MAX_NUM_WRAPPED_SURFACES - 1) <= g_numWrappedSurfaces)
		{
			LOG_FORMAT("\tERROR: creating a primary surface with back buffer failed - too many wrapped surfaces");
			return DDERR_GENERIC;
		}

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
		surfaceDescription.dwWidth = SURFACE_WIDTH;
		surfaceDescription.dwHeight = SURFACE_HEIGHT;

		result = lpDirectDraw->CreateSurface(&surfaceDescription, &backSurfacePtr, pUnkOuter);
		if (result != DD_OK)
		{
			LOG_FORMAT("\tCreating an emulated secondary surface failed with error code " << HEX(result));
			frontSurfacePtr->Release();
			return DDERR_GENERIC;
		}

		MyIDirectDrawSurface * backingSurfaceWrapperPtr = new MyIDirectDrawSurface(backSurfacePtr, NULL, false);
		MyIDirectDrawSurface * surfacePtr = new MyIDirectDrawSurface(frontSurfacePtr, backingSurfaceWrapperPtr, true);
		*lplpDDSurface = surfacePtr;

		g_wrappedSurfaces[g_numWrappedSurfaces] = backingSurfaceWrapperPtr;
		++g_numWrappedSurfaces;

		g_wrappedSurfaces[g_numWrappedSurfaces] = surfacePtr;
		++g_numWrappedSurfaces;

		LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": returning " << HEX(surfacePtr) << " with backing buffer at " << HEX(backingSurfaceWrapperPtr));

		return DD_OK;
	}
	else
	{
		if (MAX_NUM_WRAPPED_SURFACES <= g_numWrappedSurfaces)
		{
			LOG_FORMAT("\tERRROR: creating a secondary surface failed - too many wrapped surfaces");
			return DDERR_GENERIC;
		}

		LOG_FORMAT("\tCreating a secondary surface");
		result = lpDirectDraw->CreateSurface(lpDDSurfaceDesc, &frontSurfacePtr, pUnkOuter);

		if (DD_OK != result)
		{
			LOG_FORMAT(__FILE__ << ":" << __func__ << ": call to CreateSurface failed with error " << HEX(result));
			return result;
		}

		MyIDirectDrawSurface * myIDirectDrawSurface = new MyIDirectDrawSurface(frontSurfacePtr, NULL, false);

		g_wrappedSurfaces[g_numWrappedSurfaces] = myIDirectDrawSurface;
		++g_numWrappedSurfaces;

		*lplpDDSurface = myIDirectDrawSurface;
		LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": returning MyIDirectDrawSurface at " << HEX(myIDirectDrawSurface));

		return result;
	}
}


LPDIRECTDRAWSURFACE MyIDirectDrawSurface::GetRawSurface(LPDIRECTDRAWSURFACE surfacePtr)
{
	LOG_STATIC_FUNC();
	LOG_FORMAT("\tsurfacePtr = " << HEX(surfacePtr));

	if (surfacePtr == NULL)
	{
		return surfacePtr;
	}

	for (unsigned int i = 0; i < g_numWrappedSurfaces; ++i)
	{
		if ((LPDIRECTDRAWSURFACE)g_wrappedSurfaces[i] == surfacePtr)
		{
			LPDIRECTDRAWSURFACE rawSurfacePtr = g_wrappedSurfaces[i]->m_rawSurfacePtr;
			LOG_FORMAT("\tFound raw surface " << HEX(rawSurfacePtr) << " for wrapped surface " << HEX(surfacePtr));
			return rawSurfacePtr;
		}
	}

	LOG_FORMAT("\tERROR: found no raw surface for wrapped surface " << HEX(surfacePtr));
	return surfacePtr;
}


MyIDirectDrawSurface::MyIDirectDrawSurface(LPDIRECTDRAWSURFACE surfacePtr, MyIDirectDrawSurface * nextSurfacePtr, bool hasBackingBuffers)
	: m_rawSurfacePtr(surfacePtr), m_nextSurfacePtr(nextSurfacePtr), m_hasBackingBuffers(hasBackingBuffers)
{}


MyIDirectDrawSurface::~MyIDirectDrawSurface()
{}

IMPL_STDMETHOD(MyIDirectDrawSurface::QueryInterface) (THIS_ REFIID riid, LPVOID FAR * ppvObj) { LOG_THIS_FUNC(); return m_rawSurfacePtr->QueryInterface(riid, ppvObj);  }

IMPL_STDMETHOD_(ULONG, MyIDirectDrawSurface::AddRef) (THIS) {
	LOG_THIS_FUNC();
	if (m_hasBackingBuffers)
	{
		m_nextSurfacePtr->AddRef();
	}
	return m_rawSurfacePtr->AddRef();
}

IMPL_STDMETHOD_(ULONG, MyIDirectDrawSurface::Release) (THIS) {
	LOG_THIS_FUNC();
	if (m_hasBackingBuffers)
	{
		m_nextSurfacePtr->Release();
	}
	return m_rawSurfacePtr->Release();
}

IMPL_STDMETHOD(MyIDirectDrawSurface::AddAttachedSurface)(THIS_ LPDIRECTDRAWSURFACE a) { LOG_THIS_FUNC(); return m_rawSurfacePtr->AddAttachedSurface(GetRawSurface(a)); }

IMPL_STDMETHOD(MyIDirectDrawSurface::AddOverlayDirtyRect)(THIS_ LPRECT a) { LOG_THIS_FUNC(); return m_rawSurfacePtr->AddOverlayDirtyRect(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::Blt)(THIS_ LPRECT lpDestRect, LPDIRECTDRAWSURFACE lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwFlags, LPDDBLTFX lpDDBltFx)
{
	// TODO: intercept - or not?
	LOG_THIS_FUNC();

	Log("\tlpDestRect:");
	LogRect(lpDestRect);

	LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": lpDDSrcSurface = " << HEX(lpDDSrcSurface));

	Log("\tlpSrcRect:");
	LogRect(lpSrcRect);

	Log("\tlpDDBltFx:");
	LogDDBLTFX(lpDDBltFx, dwFlags);

	LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": dwFlags = " << HEX(dwFlags));

	return m_rawSurfacePtr->Blt(lpDestRect, GetRawSurface(lpDDSrcSurface), lpSrcRect, dwFlags, lpDDBltFx);
}

IMPL_STDMETHOD(MyIDirectDrawSurface::BltBatch)(THIS_ LPDDBLTBATCH a, DWORD b, DWORD c) { LOG_THIS_FUNC(); return m_rawSurfacePtr->BltBatch(a, b, c); }

IMPL_STDMETHOD(MyIDirectDrawSurface::BltFast)(THIS_ DWORD dwX, DWORD dwY, LPDIRECTDRAWSURFACE lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwFlags)
{
	LOG_THIS_FUNC();
	LOG_FORMAT("\tdwX = " << DEC(dwX) << ", dwY = " << DEC(dwY) << ", lpDDSrcSurface = " << HEX(lpDDSrcSurface) << ", dwFlags = " << HEX(dwFlags));
	LOG_FORMAT("\tlpSrcRect:");
	LogRect(lpSrcRect);

	return m_rawSurfacePtr->BltFast(dwX, dwY, GetRawSurface(lpDDSrcSurface), lpSrcRect, dwFlags);
}

IMPL_STDMETHOD(MyIDirectDrawSurface::DeleteAttachedSurface)(THIS_ DWORD a, LPDIRECTDRAWSURFACE b) { LOG_THIS_FUNC(); return m_rawSurfacePtr->DeleteAttachedSurface(a, GetRawSurface(b)); }

IMPL_STDMETHOD(MyIDirectDrawSurface::EnumAttachedSurfaces)(THIS_ LPVOID a, LPDDENUMSURFACESCALLBACK b) { LOG_THIS_FUNC(); return m_rawSurfacePtr->EnumAttachedSurfaces(a, b); }

IMPL_STDMETHOD(MyIDirectDrawSurface::EnumOverlayZOrders)(THIS_ DWORD a, LPVOID b, LPDDENUMSURFACESCALLBACK c) { LOG_THIS_FUNC(); return m_rawSurfacePtr->EnumOverlayZOrders(a, b, c); }

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
	SetRect(&sourceRectangle, 0, 0, SURFACE_WIDTH, SURFACE_HEIGHT);

	LOG_FORMAT("\tsourceRectangle:");
	LogRect(&sourceRectangle);

	LOG_FORMAT("\tdestinationRectangle:");
	LogRect(&destinationRectangle);

	result = m_rawSurfacePtr->Blt(&destinationRectangle, m_nextSurfacePtr->m_rawSurfacePtr, &sourceRectangle, DDBLT_WAIT, NULL);

	return result;
}

IMPL_STDMETHOD(MyIDirectDrawSurface::GetAttachedSurface)(THIS_ LPDDSCAPS lpDDSCaps, LPDIRECTDRAWSURFACE FAR * lplpDDAttachedSurface)
{
	LOG_THIS_FUNC();
	LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": lpDDSCaps->dwCaps = " << HEX(lpDDSCaps->dwCaps));

	if ((lpDDSCaps->dwCaps & DDSCAPS_BACKBUFFER) && m_hasBackingBuffers)
	{
		LOG_FORMAT("\tReturning emulated back-buffer at " << HEX(m_nextSurfacePtr));
		m_nextSurfacePtr->AddRef(); // as per MSDN entry for GetAttachedSurface
		*lplpDDAttachedSurface = m_nextSurfacePtr;
		return DD_OK;
	}
	else
	{
		LOG_FORMAT("\tReturning raw buffer");
		LOG_FORMAT("\tTHIS SHOULD NOT HAPPEN, SOMETHING IS WRONG");
		LPDIRECTDRAWSURFACE returnedAttachedSurface = NULL;
		HRESULT result = m_rawSurfacePtr->GetAttachedSurface(lpDDSCaps, &returnedAttachedSurface);

		LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": *lplpDDAttachedSurface [return value] = " << HEX(returnedAttachedSurface) << ", hResult = " << HEX(result));

		*lplpDDAttachedSurface = returnedAttachedSurface;

		return result;
	}
}

IMPL_STDMETHOD(MyIDirectDrawSurface::GetBltStatus)(THIS_ DWORD a) { LOG_THIS_FUNC(); return m_rawSurfacePtr->GetBltStatus(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::GetCaps)(THIS_ LPDDSCAPS a) { LOG_THIS_FUNC(); return m_rawSurfacePtr->GetCaps(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::GetClipper)(THIS_ LPDIRECTDRAWCLIPPER FAR* a) { LOG_THIS_FUNC(); return m_rawSurfacePtr->GetClipper(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::GetColorKey)(THIS_ DWORD a, LPDDCOLORKEY b) { LOG_THIS_FUNC(); return m_rawSurfacePtr->GetColorKey(a, b); }

IMPL_STDMETHOD(MyIDirectDrawSurface::GetDC)(THIS_ HDC FAR * a) { LOG_THIS_FUNC(); return m_rawSurfacePtr->GetDC(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::GetFlipStatus)(THIS_ DWORD a) { LOG_THIS_FUNC(); return m_rawSurfacePtr->GetFlipStatus(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::GetOverlayPosition)(THIS_ LPLONG a, LPLONG b) { LOG_THIS_FUNC(); return m_rawSurfacePtr->GetOverlayPosition(a, b); }

IMPL_STDMETHOD(MyIDirectDrawSurface::GetPalette)(THIS_ LPDIRECTDRAWPALETTE FAR* a) { LOG_THIS_FUNC(); return m_rawSurfacePtr->GetPalette(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::GetPixelFormat)(THIS_ LPDDPIXELFORMAT a) { LOG_THIS_FUNC(); return m_rawSurfacePtr->GetPixelFormat(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::GetSurfaceDesc)(THIS_ LPDDSURFACEDESC a) { LOG_THIS_FUNC(); return m_rawSurfacePtr->GetSurfaceDesc(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::Initialize)(THIS_ LPDIRECTDRAW a, LPDDSURFACEDESC b) { LOG_THIS_FUNC(); return m_rawSurfacePtr->Initialize(a, b); }

IMPL_STDMETHOD(MyIDirectDrawSurface::IsLost)(THIS) { LOG_THIS_FUNC(); return m_rawSurfacePtr->IsLost(); }

IMPL_STDMETHOD(MyIDirectDrawSurface::Lock)(THIS_ LPRECT lpDestRect, LPDDSURFACEDESC lpDDSurfaceDesc, DWORD dwFlags, HANDLE hEvent)
{
	// TODO: INTERCEPT - or not?
	LOG_THIS_FUNC();

	Log("\tlpDestRect:");
	LogRect(lpDestRect);

	Log("\tlpDDSurfaceDesc BEFORE LOCK:");
	LogSurfaceDescriptionStruct(lpDDSurfaceDesc);

	LOG_FORMAT("\tdwFlags = " << HEX(dwFlags));

	HRESULT result = m_rawSurfacePtr->Lock(lpDestRect, lpDDSurfaceDesc, dwFlags, hEvent);

	LOG_FORMAT("\tlpDDSurfaceDesc AFTER LOCK [hResult = " << HEX(result) << "]:");
	LogSurfaceDescriptionStruct(lpDDSurfaceDesc);

	return result;
}

IMPL_STDMETHOD(MyIDirectDrawSurface::ReleaseDC)(THIS_ HDC a) { LOG_THIS_FUNC(); return m_rawSurfacePtr->ReleaseDC(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::Restore)(THIS) { LOG_THIS_FUNC(); return m_rawSurfacePtr->Restore(); }

IMPL_STDMETHOD(MyIDirectDrawSurface::SetClipper)(THIS_ LPDIRECTDRAWCLIPPER a) { LOG_THIS_FUNC(); return m_rawSurfacePtr->SetClipper(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::SetColorKey)(THIS_ DWORD a, LPDDCOLORKEY b) { LOG_THIS_FUNC(); return m_rawSurfacePtr->SetColorKey(a, b); }

IMPL_STDMETHOD(MyIDirectDrawSurface::SetOverlayPosition)(THIS_ LONG a, LONG b) { LOG_THIS_FUNC(); return m_rawSurfacePtr->SetOverlayPosition(a, b); }

IMPL_STDMETHOD(MyIDirectDrawSurface::SetPalette)(THIS_ LPDIRECTDRAWPALETTE a) { LOG_THIS_FUNC(); return m_rawSurfacePtr->SetPalette(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::Unlock)(THIS_ LPVOID lpRectMaybe)
{
	// TODO: INTERCEPT - or not?
	LOG_THIS_FUNC();
	return m_rawSurfacePtr->Unlock(lpRectMaybe);
}

IMPL_STDMETHOD(MyIDirectDrawSurface::UpdateOverlay)(THIS_ LPRECT a, LPDIRECTDRAWSURFACE b, LPRECT c, DWORD d, LPDDOVERLAYFX e) { LOG_THIS_FUNC(); return m_rawSurfacePtr->UpdateOverlay(a, GetRawSurface(b), c, d, e); }

IMPL_STDMETHOD(MyIDirectDrawSurface::UpdateOverlayDisplay)(THIS_ DWORD a) { LOG_THIS_FUNC(); return m_rawSurfacePtr->UpdateOverlayDisplay(a); }

IMPL_STDMETHOD(MyIDirectDrawSurface::UpdateOverlayZOrder)(THIS_ DWORD a, LPDIRECTDRAWSURFACE b) { LOG_THIS_FUNC(); return m_rawSurfacePtr->UpdateOverlayZOrder(a, GetRawSurface(b)); }

