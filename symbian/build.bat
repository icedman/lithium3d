@echo off

set project=minimal

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
if "%1"=="s60"     goto serie60
if "%1"=="serie60" goto serie60
if "%1"=="S60"     goto serie60
if "%1"=="SERIE60" goto serie60
if "%1"=="uiq"     goto uiq
if "%1"=="UIQ"     goto uiq

goto help


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
:serie60

echo Building for Serie 60

copy bld_s60.inf bld.inf /y
call bldmake bldfiles
call abld build armi urel
makesis %project%_s60.pkg

goto end


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
:uiq

echo Building for UIQ

copy bld_uiq.inf bld.inf /y
call bldmake bldfiles
call abld build armi urel
makesis %project%_uiq.pkg

goto end


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
:help

echo.
echo Build syntax: build [s60,serie60,uiq]
echo.


:end

del bld.inf
del abld.bat
