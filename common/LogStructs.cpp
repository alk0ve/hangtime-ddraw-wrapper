#include "LogStructs.h"
#include "common.h"

void LogSurfaceDescriptionStruct(LPDDSURFACEDESC surface)
{
#ifndef DISABLE_LOG
	if (surface->dwSize != sizeof(DDSURFACEDESC))
	{
		LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": unexpected struct size");
		return;
	}

	LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": dwFlags = " << HEX(surface->dwFlags));

	if (surface->dwFlags & DDSD_BACKBUFFERCOUNT)
	{
		LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": dwBackBufferCount  = " << DEC(surface->dwBackBufferCount));
	}

	if (surface->dwFlags & DDSD_CAPS)
	{
		LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": ddsCaps.dwCaps = " << HEX(surface->ddsCaps.dwCaps));
	}

	if (surface->dwFlags & DDSD_HEIGHT)
	{
		LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": dwHeight  = " << DEC(surface->dwHeight));
	}

	if (surface->dwFlags & DDSD_LPSURFACE)
	{
		LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": lpSurface = " << HEX(surface->lpSurface));
	}

	if (surface->dwFlags & DDSD_REFRESHRATE)
	{
		LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": dwRefreshRate = " << HEX(surface->dwRefreshRate));
	}

	if (surface->dwFlags & DDSD_WIDTH)
	{
		LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": dwWidth = " << DEC(surface->dwWidth));
	}
	if (surface->dwFlags & DDSD_PITCH)
	{
		LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": lPitch = " << DEC(surface->lPitch));
	}

#endif
}

void LogRect(LPRECT lpRectangle)
{
#ifndef DISABLE_LOG
	if (lpRectangle == NULL)
	{
		LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": LPRECT is NULL");
		return;
	}

	LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": left = " << DEC(lpRectangle->left) << ", top = " << DEC(lpRectangle->top) << ", right = " << DEC(lpRectangle->right) << ", bottom = " << DEC(lpRectangle->bottom));
#endif
}


void LogDDBLTFX(LPDDBLTFX lpDDBltFx, DWORD dwFlags)
{
#ifndef DISABLE_LOG
	if (lpDDBltFx == NULL)
	{
		LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": LPDDBLTFX is NULL");
		return;
	}

	if (dwFlags & DDBLT_COLORFILL)
	{
		LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": lpDDBltFx->dwFillColor = " << HEX(lpDDBltFx->dwFillColor));
	}

	if (dwFlags & DDBLT_DDFX)
	{
		LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": lpDDBltFx->dwDDFX = " << HEX(lpDDBltFx->dwDDFX));
	}

	if (dwFlags & DDBLT_DDROPS)
	{
		LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": lpDDBltFx->dwDDROP = " << HEX(lpDDBltFx->dwDDROP));
	}

	if (dwFlags & DDBLT_DEPTHFILL)
	{
		LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": lpDDBltFx->dwFillDepth = " << HEX(lpDDBltFx->dwFillDepth));
	}

	if (dwFlags & DDBLT_KEYDESTOVERRIDE)
	{
		LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": lpDDBltFx->ddckDestColorkey = [" << HEX(lpDDBltFx->ddckDestColorkey.dwColorSpaceLowValue) << ", " << HEX(lpDDBltFx->ddckDestColorkey.dwColorSpaceHighValue) << "]");
	}

	if (dwFlags & DDBLT_KEYSRCOVERRIDE)
	{
		LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": lpDDBltFx->ddckSrcColorkey = [" << HEX(lpDDBltFx->ddckSrcColorkey.dwColorSpaceLowValue) << ", " << HEX(lpDDBltFx->ddckSrcColorkey.dwColorSpaceHighValue) << "]");
	}

	if (dwFlags & DDBLT_ROP)
	{
		LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": lpDDBltFx->dwROP = " << HEX(lpDDBltFx->dwROP));
	}

	if (dwFlags & DDBLT_ROTATIONANGLE)
	{
		LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": lpDDBltFx->dwRotationAngle = " << HEX(lpDDBltFx->dwRotationAngle));
	}
#endif
}