:: THIS FILE IS PART OF NEOWISE GAME ENGINE PROJECT 

@ECHO OFF

IF NOT EXIST "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\Common7\\IDE\\devenv.exe" (
    @ECHO +[INFO]: Visual Studio 2022 IDE was not found! Installing one...
    CD "..\..\"
    START "/d . .\\Tools\\Windows\\VisualStudio2022_Setup.exe"
) ELSE (
    @ECHO +[INFO]: Visual Studio 2022 IDE successfully found!
)

@ECHO ON
