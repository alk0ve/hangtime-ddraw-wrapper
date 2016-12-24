#include "LogStructs.h"
#include "common.h"

void LogSurfaceDescriptionStruct(LPDDSURFACEDESC surface)
{
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
}

void LogRect(LPRECT lpRectangle)
{
	if (lpRectangle == NULL)
	{
		LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": LPRECT is NULL");
		return;
	}

	LOG_FORMAT("\t" << __FILE__ << ":" << __func__ << ": left = " << DEC(lpRectangle->left) << ", top = " << DEC(lpRectangle->top) << ", right = " << DEC(lpRectangle->right) << ", bottom = " << DEC(lpRectangle->bottom));
}