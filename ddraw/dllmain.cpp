#include <windows.h>

#pragma comment (linker, "/export:AcquireDDThreadLock=ddraw_original.AcquireDDThreadLock,@1")
#pragma comment (linker, "/export:CompleteCreateSysmemSurface=ddraw_original.CompleteCreateSysmemSurface,@2")
#pragma comment (linker, "/export:D3DParseUnknownCommand=ddraw_original.D3DParseUnknownCommand,@3")
#pragma comment (linker, "/export:DDGetAttachedSurfaceLcl=ddraw_original.DDGetAttachedSurfaceLcl,@4")
#pragma comment (linker, "/export:DDInternalLock=ddraw_original.DDInternalLock,@5")
#pragma comment (linker, "/export:DDInternalUnlock=ddraw_original.DDInternalUnlock,@6")
#pragma comment (linker, "/export:DSoundHelp=ddraw_original.DSoundHelp,@7")
//#pragma comment (linker, "/export:DirectDrawCreate=ddraw_original.DirectDrawCreate,@8")
#pragma comment (linker, "/export:DirectDrawCreateClipper=ddraw_original.DirectDrawCreateClipper,@9")
#pragma comment (linker, "/export:DirectDrawCreateEx=ddraw_original.DirectDrawCreateEx,@10")
#pragma comment (linker, "/export:DirectDrawEnumerateA=ddraw_original.DirectDrawEnumerateA,@11")
#pragma comment (linker, "/export:DirectDrawEnumerateExA=ddraw_original.DirectDrawEnumerateExA,@12")
#pragma comment (linker, "/export:DirectDrawEnumerateExW=ddraw_original.DirectDrawEnumerateExW,@13")
#pragma comment (linker, "/export:DirectDrawEnumerateW=ddraw_original.DirectDrawEnumerateW,@14")
#pragma comment (linker, "/export:DllCanUnloadNow=ddraw_original.DllCanUnloadNow,@15")
#pragma comment (linker, "/export:DllGetClassObject=ddraw_original.DllGetClassObject,@16")
#pragma comment (linker, "/export:GetDDSurfaceLocal=ddraw_original.GetDDSurfaceLocal,@17")
#pragma comment (linker, "/export:GetOLEThunkData=ddraw_original.GetOLEThunkData,@18")
#pragma comment (linker, "/export:GetSurfaceFromDC=ddraw_original.GetSurfaceFromDC,@19")
#pragma comment (linker, "/export:RegisterSpecialCase=ddraw_original.RegisterSpecialCase,@20")
#pragma comment (linker, "/export:ReleaseDDThreadLock=ddraw_original.ReleaseDDThreadLock,@21")
#pragma comment (linker, "/export:SetAppCompatData=ddraw_original.SetAppCompatData,@22")

BOOL WINAPI DllMain(HINSTANCE hInst,DWORD reason,LPVOID)
{
	return TRUE;
}