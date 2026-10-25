@echo off
cd /d "C:\Users\ShaeOJ\Documents\GitHub\Caps-new\build_msvc"
echo Building capsd...
"C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" capsd\capsd.vcxproj /p:Configuration=Release /p:Platform=x64 /m
echo.
echo Building caps-cli...
"C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" caps-cli\caps-cli.vcxproj /p:Configuration=Release /p:Platform=x64 /m
echo.
echo Done. Exit code: %ERRORLEVEL%
