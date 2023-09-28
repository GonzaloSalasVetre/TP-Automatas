tp-p1.exe tp-p3.exe: tp-p1.o tp-p3.o
	gcc tp-p1.o -o tp-p1.exe -std=c18
	gcc tp-p3.o -o tp-p3.exe -std=c18


tp-p1.o tp-p3.o: tp-p1.c tp-p3.c
	gcc -c tp-p1.c -o tp-p1.o -std=c18
	gcc -c tp-p3.c -o tp-p3.o -std=c18