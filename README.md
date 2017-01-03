GOAL: add windowed mode to NBA Hangtime via a wrapper for ddraw.dll.


How to use:
========================================
1. build ddraw and user32 in VS
2. copy ddraw.dll, ussr32.dll (yes, that's not a typo), copy_original_dlls.bat and patch_hangtime_user32.py from hangtime python repo to NBA Hangtime's folder
3. run patch_hangtime_user32.py (it patches the executable to allow setting up a proxy for user32.dll)
3. run copy_original_dlls.bat
	3.1. if that didn't work - find your own ddraw.dll (in \Windows\SysWOW64 if you're running a 64-bit OS or \Windows\System32 otherwise), copy it to the game folder and rename to ddraw_original.dll, then find user32.dll and copy it as user32.dll (yes, without changing the name) )
4. profit :-)



DLL Proxy on user32.dll
========================================
Windows has a mechanism called Known DLLs that makes sure that certain DLLs (user32.dll among them) are always loaded from system32/SysWOW64; to bypass this I patched HANGTIME.exe to load ussr32.dll instead; I did this for both the import and the call to LoadLibrary.

As it turns out you can't load user32.dll twice under different names, so I made sure that ussr32.dll loaded user32.dll (and not user32_original.dll or something) so that when other dlls also loaded user32.dll they'd all end up with only one instance of user32.dll loaded in the process.

