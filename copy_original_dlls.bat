@echo off

if exist %systemroot%\SysWOW64 (
	rem 64 bit system
	if exist %systemroot%\SysWOW64\ddraw.dll (
		copy %systemroot%\SysWOW64\ddraw.dll .\ddraw_original.dll
	) else (
		goto error
	)
	
	if exist %systemroot%\SysWOW64\user32.dll (
		copy %systemroot%\SysWOW64\user32.dll .\user32.dll
	) else (
		goto error
	)

) else (
	rem 32 bit system
	if exist %systemroot%\System32\ddraw.dll (
		copy %systemroot%\System32\ddraw.dll .\ddraw_original.dll
	) else (
		goto error
	)
	
	if exist %systemroot%\System32\user32.dll (
		copy %systemroot%\System32\user32.dll .\user32.dll
	) else (
		goto error
	)
)

echo Done!
exit

:error
echo Could not find ddraw.dll :-(

