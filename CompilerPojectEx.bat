ScannerProject.l ParProject.y
bison -d ParProject.y
flex ScannerProject.l
gcc -o Projectex ParProject.tab.c lex.yy.c -lfl