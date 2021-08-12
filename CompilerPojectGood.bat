ScannerProject.l good.y
bison -d good.y
flex ScannerProject.l
gcc -o goo good.tab.c lex.yy.c -lfl
cd C:\Users\Moflawer\Desktop\final
goo
pause