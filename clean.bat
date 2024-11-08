@echo off

rd root /s /q
cd image
cmd /c clean.bat
cd ..
cd kernel 
cmd /c clean.bat
cd ..