tp-p2y3.exe: tp-p2y3.o
	gcc tp-p2y3.o -o tp-p2y3.exe -std=c18


tp-p2y3.o: tp-p2y3.c
	gcc -c tp-p2y3.c -o tp-p2y3.o -std=c18

tp-p1.exe: tp-p1.o
	gcc tp-p1.o -o tp-p1.exe -std=c18


tp-p1.o: tp-p1.c
	gcc -c tp-p1.c -o tp-p1.o -std=c18