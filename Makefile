all:
	gcc -Iinclude -o ez8 main.c -lSDL2main -lSDL2
clean:
	del ez8.exe
run:
	gcc -Iinclude -o ez8 main.c -lSDL2main -lSDL2
	ez8 test_opcode.ch8
