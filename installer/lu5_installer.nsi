# Name of the installer
OutFile "../bin/win64/lu5-x86_64-win-0.1.6.exe"

# Name of the application
Name "lu5"

# Default installation directory
InstallDir $PROGRAMFILES\lu5

# Request application privileges for the installer
RequestExecutionLevel admin

# Define installer and uninstaller icons
Icon "logo.ico"
UninstallIcon "logo.ico"

# Include Modern UI
!include "MUI2.nsh"

!define MUI_ICON "logo.ico"

# Define Welcome
!define MUI_WELCOMEFINISHPAGE
!define MUI_WELCOMEFINISHPAGE_LEFT
!define MUI_WELCOMEFINISHPAGE_BITMAP "logo_164x314.bmp"
!define MUI_WELCOMEFINISHPAGE_UNBITMAP "logo_164x314.bmp"

# Define Header Image
!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_LEFT
!define MUI_HEADERIMAGE_BITMAP "logo_150x57.bmp"
!define MUI_HEADERIMAGE_UNBITMAP "logo_150x57.bmp"

# Pages
!define MUI_WELCOMEPAGE_TEXT "Welcome to the lu5 installer."
!define MUI_WELCOMEPAGE_TITLE "Welcome"
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "..\LICENSE"
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES

# Define Finish Page Text
!define MUI_FINISHPAGE_TITLE "Installation Complete"
!define MUI_FINISHPAGE_TEXT "lu5 has been installed successfully. You can close and delete this installer."
!insertmacro MUI_PAGE_FINISH

# Uninstaller Pages
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH

!insertmacro MUI_LANGUAGE "English"

Section "Install"

  # Output directory
  SetOutPath "$INSTDIR"

  # Add files
  File "..\bin\win64\lu5.exe"
  File "..\bin\win64\zlib1.dll"
  File "..\bin\win64\libssp-0.dll"
  File "..\bin\win64\libbrotlicommon.dll"
  File "..\bin\win64\libbrotlidec.dll"
  File "..\bin\win64\libbz2-1.dll"
  File "..\bin\win64\libbrotlidec.dll"
  File "..\bin\win64\lua54.dll"
  File "..\bin\win64\libfreetype-6.dll"
  File "..\bin\win64\libwinpthread-1.dll"

  # Check if the path entry already exists
  nsExec::ExecToStack 'cmd.exe /C echo %PATH% | find "$INSTDIR"'
  Pop $0

  ${If} $0 == 0
    DetailPrint "Path already exists in PATH variable."
  ${Else}
    # Add the installation directory to the PATH environment variable
    nsExec::ExecToLog 'cmd.exe /C setx PATH "%PATH%;$INSTDIR"'
    DetailPrint "Added $INSTDIR to PATH variable."
  ${EndIf}
SectionEnd

Section "Uninstall"

  Delete "$INSTDIR\lu5.exe"
  Delete "$INSTDIR\zlib1.dll"
  Delete "$INSTDIR\libssp-0.dll"
  Delete "$INSTDIR\libbrotlicommon.dll"
  Delete "$INSTDIR\libbrotlidec.dll"
  Delete "$INSTDIR\libbz2-1.dll"
  Delete "$INSTDIR\libbrotlidec.dll"
  Delete "$INSTDIR\lua54.dll"
  Delete "$INSTDIR\libfreetype-6.dll"
  Delete "$INSTDIR\libwinpthread-1.dll"

  RMDir "$INSTDIR"

SectionEnd
