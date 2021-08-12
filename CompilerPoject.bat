ScannerProject.l ParserProject.y
bison -d ParserProject.y
flex ScannerProject.l
gcc -o Project ParserProject.tab.c lex.yy.c -lfl