@ECHO OFF
cd "%~dp0"
ECHO  -------------------------------------------------------------------------
ECHO  - This SRIM SETUP program will install Windows programs that are missing.
ECHO  - After each step, the result will be shown. Press ENTER to continue.
ECHO  - First, it must identify whether your PC is a 32-bit or a 64-bit system.
ECHO  ------------------------------------------------------------------------- 
IF EXIST C:\Windows\SysWOW64  (ECHO Your computer is a 64-bit Windows System) ELSE (ECHO Your computer is a 32-bit Windows System)
ECHO  ------------------------------------------------------------------------- 
pause
cd SRIM-Setup
ECHO  ------------------------------------------------------------------------- 
ECHO  - Next, the Microsoft Visual Basic System will be installed.
ECHO  ------------------------------------------------------------------------- 
pause
MSVBvm50.exe
CLS
ECHO  ------------------------------------------------------------------------- 
ECHO  - Next, five missing Microsoft system files will be installed.
ECHO  - If you get an ERROR MESSAGE, it means the file is already on you computer.
ECHO  - Just click OK and continue.
ECHO  ------------------------------------------------------------------------- 
pause
IF EXIST C:\Windows\SysWOW64 (C:\Windows\SysWOW64\regsvr32.exe  COMCTL32.OCX) ELSE (C:\Windows\System32\regsvr32.exe  COMCTL32.OCX)
IF EXIST C:\Windows\SysWOW64 (C:\Windows\SysWOW64\regsvr32.exe  COMDLG32.OCX) ELSE (C:\Windows\System32\regsvr32.exe  COMDLG32.OCX)
IF EXIST C:\Windows\SysWOW64 (C:\Windows\SysWOW64\regsvr32.exe  MSFLXGRD.OCX) ELSE (C:\Windows\System32\regsvr32.exe  MSFLXGRD.OCX)
IF EXIST C:\Windows\SysWOW64 (C:\Windows\SysWOW64\regsvr32.exe  TABCTL32.OCX) ELSE (C:\Windows\System32\regsvr32.exe  TABCTL32.OCX)
IF EXIST C:\Windows\SysWOW64 (C:\Windows\SysWOW64\regsvr32.exe  RICHTX32.OCX) ELSE (C:\Windows\System32\regsvr32.exe  RICHTX32.OCX)
CLS
ECHO  ------------------------------------------------------------------------- 
ECHO  ------------------------------------------------------------------------- 
ECHO   - Finally, the Microsoft font "Linedraw.ttf" will be installed.  
ECHO  ------------------------------------------------------------------------- 
ECHO  - It will be necessary for you to give the INSTALL command.
ECHO  - A new window will open, showing the font. Press INSTALL at the top.
ECHO  ------------------------------------------------------------------------- 
pause
c:\Windows\System32\fontview.exe linedraw.ttf
cd ..\
ECHO  -------------------------------------------------- 
ECHO  ------  END of SRIM setup file loading.  ---------
ECHO  -------------------------------------------------- 
pause

