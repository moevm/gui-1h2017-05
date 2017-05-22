; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "KeKnaizer"
#define MyAppVersion "1.0"
#define MyAppPublisher "LoL KeK Jakuk-Uzbek, Inc."
#define MyAppURL "http://www.gotohell.com/"
#define MyAppExeName "new_GUIGUIGUI.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{42BBB44E-A31B-4786-9D7C-659F25EBD8B4}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
AllowNoIcons=yes
OutputDir=C:\Users\������\Desktop\kekstallator
OutputBaseFilename=kekSetup
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "D:\QT\build-new_GUIGUIGUI-Desktop_Qt_5_8_0_MSVC2013_64bit-Release\release\new_GUIGUIGUI.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\QT\build-new_GUIGUIGUI-Desktop_Qt_5_8_0_MSVC2013_64bit-Release\release\Qt5Core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\QT\build-new_GUIGUIGUI-Desktop_Qt_5_8_0_MSVC2013_64bit-Release\release\Qt5Gui.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\QT\build-new_GUIGUIGUI-Desktop_Qt_5_8_0_MSVC2013_64bit-Release\release\Qt5Sql.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\QT\build-new_GUIGUIGUI-Desktop_Qt_5_8_0_MSVC2013_64bit-Release\release\Qt5Widgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\QT\build-new_GUIGUIGUI-Desktop_Qt_5_8_0_MSVC2013_64bit-Release\release\kekbase\*"; DestDir: "{app}\kekbase"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\QT\build-new_GUIGUIGUI-Desktop_Qt_5_8_0_MSVC2013_64bit-Release\release\platforms\*"; DestDir: "{app}\platforms"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\QT\build-new_GUIGUIGUI-Desktop_Qt_5_8_0_MSVC2013_64bit-Release\release\sqldrivers\*"; DestDir: "{app}\sqldrivers"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

