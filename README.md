GOAL: add windowed mode to NBA Hangtime via a wrapper for ddraw.dll.


How to use:
1. build ddraw.dll in VS
2. copy ddraw.dll and copy_ddraw.bat to NBA Hangtime's folder
3. run copy_ddraw.bat
	3.1. if it doesn't create ddraw_original.dll in your folder copy the one in "3rd party" folder
	3.2. if none of the above work - find your own ddraw.dll (in \Windows\SysWOW64 if you're running a 64-bit OS or \Windows\System32 otherwise), copy it to the game folder and rename to ddraw_original.dll.
4. profit :-)
