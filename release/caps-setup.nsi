; Caps Windows Installer Script
; NSIS 3.x

!include "MUI2.nsh"
!include "x64.nsh"

; General
Name "Caps"
OutFile "caps-1.0.0-win64-setup.exe"
InstallDir "$PROGRAMFILES64\Caps"
InstallDirRegKey HKLM "Software\Caps" "InstallDir"
RequestExecutionLevel admin
SetCompressor /SOLID lzma
Unicode true

; Version Info
VIProductVersion "1.0.0.0"
VIAddVersionKey "ProductName" "Caps"
VIAddVersionKey "CompanyName" "Caps Project"
VIAddVersionKey "FileDescription" "Caps Installer"
VIAddVersionKey "FileVersion" "1.0.0"
VIAddVersionKey "ProductVersion" "1.0.0"
VIAddVersionKey "LegalCopyright" "MIT License"

; Interface Settings
!define MUI_ABORTWARNING
!define MUI_ICON "caps.ico"
!define MUI_UNICON "caps.ico"

; Pages
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "LICENSE.txt"
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

; Languages
!insertmacro MUI_LANGUAGE "English"

; Installer Section
Section "Caps Core" SecCore
    SetOutPath "$INSTDIR"

    ; Main executables
    File "caps-1.0.0-win64\capsd.exe"
    File "caps-1.0.0-win64\caps-cli.exe"
    File "caps-1.0.0-win64\caps-qt.exe"

    ; Documentation
    File "caps-1.0.0-win64\RELEASE_NOTES.txt"
    File "caps-1.0.0-win64\caps.conf.example"
    File "caps-1.0.0-win64\README.md"
    File "LICENSE.txt"

    ; Create data directory
    CreateDirectory "$APPDATA\Caps"

    ; Write registry keys
    WriteRegStr HKLM "Software\Caps" "InstallDir" "$INSTDIR"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Caps" "DisplayName" "Caps"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Caps" "UninstallString" '"$INSTDIR\uninstall.exe"'
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Caps" "DisplayIcon" '"$INSTDIR\caps-qt.exe"'
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Caps" "Publisher" "Caps Project"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Caps" "DisplayVersion" "1.0.0"
    WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Caps" "NoModify" 1
    WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Caps" "NoRepair" 1

    ; Create uninstaller
    WriteUninstaller "$INSTDIR\uninstall.exe"

    ; Start Menu shortcuts
    CreateDirectory "$SMPROGRAMS\Caps"
    CreateShortcut "$SMPROGRAMS\Caps\Caps.lnk" "$INSTDIR\caps-qt.exe"
    CreateShortcut "$SMPROGRAMS\Caps\Uninstall Caps.lnk" "$INSTDIR\uninstall.exe"

    ; Desktop shortcut
    CreateShortcut "$DESKTOP\Caps.lnk" "$INSTDIR\caps-qt.exe"
SectionEnd

; Uninstaller Section
Section "Uninstall"
    ; Remove files
    Delete "$INSTDIR\capsd.exe"
    Delete "$INSTDIR\caps-cli.exe"
    Delete "$INSTDIR\caps-qt.exe"
    Delete "$INSTDIR\RELEASE_NOTES.txt"
    Delete "$INSTDIR\caps.conf.example"
    Delete "$INSTDIR\README.md"
    Delete "$INSTDIR\LICENSE.txt"
    Delete "$INSTDIR\uninstall.exe"

    ; Remove shortcuts
    Delete "$SMPROGRAMS\Caps\Caps.lnk"
    Delete "$SMPROGRAMS\Caps\Uninstall Caps.lnk"
    RMDir "$SMPROGRAMS\Caps"
    Delete "$DESKTOP\Caps.lnk"

    ; Remove install directory
    RMDir "$INSTDIR"

    ; Remove registry keys
    DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Caps"
    DeleteRegKey HKLM "Software\Caps"
SectionEnd
