all: tp.exe run

tp.exe: tp.o
	gcc tp.o -o tp.exe -std=c18

run: tp.exe
	tp.exe

tp.o: tp.c
	gcc -c tp.c -o tp.o -std=c18
