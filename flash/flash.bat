@echo off
echo AGENCE LESS IS MORE
echo TORPILLE 1.1 Flasher
echo 2018 Tous droits reserves.
echo.
SET /P PORT=Quel port ?
esptool.exe -vv -cd nodemcu -cb 115200 -cp %PORT% -ca 0x00000 -cf torpille1.ino.adafruit.bin
pause