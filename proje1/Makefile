all:mainProgram	run

mainProgram: main.o matrixLib.o
	gcc main.o matrixLib.o -o mainProgram
main.o:main.c
	gcc -c main.c
matrixLab.o: matrixLib.c matrixLib.h
	gcc -c matrixLib.c
clean:
	del *.o mainProgram.exe
run:
	mainProgram.exe 400