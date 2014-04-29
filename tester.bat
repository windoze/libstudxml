@echo off
rem file      : tester.bat
rem copyright : Copyright (c) 2013-2014 Code Synthesis Tools CC
rem license   : MIT; see accompanying LICENSE file

rem
rem Run test or example. The test/example directory is the current directory.
rem
rem %1     "test" or "example"
rem %2     configuration, for example, Debug or Release
rem %3     platform, for example Win32 or x64
rem topdir variable containing the path to top project directory
rem

setlocal

set "PATH=%topdir%\bin64;%topdir%\bin;%PATH%"

if "_%DIFF%_" == "__" set DIFF=fc

if "_%3_" == "_Win32_" (
  set "dir=%2"
) else (
  set "dir=%3\%2"
)

rem Globbing returns files in alphabetic order.
rem
if exist *.xml (
  for %%f in (*.xml) do (

    if "_%1_" == "_example_" (
      %dir%\driver.exe %%f
    ) else (
      %dir%\driver.exe %%f >test.out
    )

    if errorlevel 1 (
      del /f test.out
      goto error
    )

    if "_%1_" == "_test_" (

      %DIFF% %%f test.out

      if errorlevel 1 (
        del /f test.out
        goto error
      )

      del /f test.out
    )
  )
) else (

  %dir%\driver.exe
  if errorlevel 1 goto error
)

goto end

:error
endlocal
exit /b 1

:end
endlocal
