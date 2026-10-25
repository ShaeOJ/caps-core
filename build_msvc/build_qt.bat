@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
if errorlevel 1 (
    echo Failed to set up VS environment
    exit /b 1
)
set QTBASEDIR=C:\Qt_static
cd /d C:\Users\ShaeOJ\Documents\GitHub\Caps-new\build_msvc
"C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" caps-qt\caps-qt.vcxproj -property:Configuration=Release -property:Platform=x64 -verbosity:normal
