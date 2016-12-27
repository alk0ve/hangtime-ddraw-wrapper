GOAL: add windowed mode to NBA Hangtime via a wrapper for ddraw.dll.


How to use:
1. build ddraw and user32 in VS
2. copy ddraw.dll, ussr32.dll (yes, that's not a typo), copy_original_dlls.bat and patch_hangtime_user32.py from hangtime python repo to NBA Hangtime's folder
3. run patch_hangtime_user32.py (it patches the executable to allow setting up a proxy for user32.dll)
3. run copy_original_dlls.bat
	3.1. if that didn't work - find your own ddraw.dll (in \Windows\SysWOW64 if you're running a 64-bit OS or \Windows\System32 otherwise), copy it to the game folder and rename to ddraw_original.dll, then do the same for user32.dll ( -> user32_original.dll)
4. profit :-)
