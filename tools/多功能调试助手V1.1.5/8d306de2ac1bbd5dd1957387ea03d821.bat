@echo off
echo ��ӭʹ��ɽ��๦�ܵ������֣�����������...
taskkill /f /im "�๦�ܵ�������.exe"
:loop2
if exist "�๦�ܵ�������.exe" (del "�๦�ܵ�������.exe"  & goto loop2)
COPY /y "999" "�๦�ܵ�������.exe"
del "999"

CLS
echo ��ӭʹ��ɽ��๦�ܵ������֣�������ΪV1.1.6�汾.
timeout /t 1 >nul
del 4d0f87bf2b641a69170d8a4c45a383e1.vbs
del 8d306de2ac1bbd5dd1957387ea03d821.bat