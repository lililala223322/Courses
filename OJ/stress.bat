@echo off
rem stress.bat —— 每轮输出测试串与结果
setlocal enabledelayedexpansion
set TOTAL=0
set PASS=0

echo [stress] 每轮显示测试串与结果，按 Ctrl-C 停止...
:loop
    set /a TOTAL+=1
    rem 生成并验证
    36test.exe > tmp.txt
    set RET=!errorlevel!
    rem 把测试串和结果读出来
    set "TEST_STR="
    set "GOT_STR="
    for /f "tokens=1,* delims=:" %%a in ('findstr /b "Test  :" tmp.txt') do set "TEST_STR=%%b"
    for /f "tokens=1,* delims=:" %%a in ('findstr /b "Got   :" tmp.txt') do set "GOT_STR=%%b"
    rem 去掉前导空格
    if defined TEST_STR set "TEST_STR=!TEST_STR:~1!"
    if defined GOT_STR set "GOT_STR=!GOT_STR:~1!"

    if !RET! equ 0 (
        set /a PASS+=1
        echo Round !TOTAL!  PASS  [!TEST_STR!]  -^>  [!GOT_STR!]
        del tmp.txt
    ) else (
        echo Round !TOTAL!  FAIL  [!TEST_STR!]  -^>  [!GOT_STR!]
        copy /y tmp.txt wa_case.txt >nul
    )
goto loop