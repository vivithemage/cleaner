src/magic-file:src/main.c
	gcc -Wall -g src/main.c -o src/magic-file -l magic `pkg-config --cflags gtk+-2.0 --libs gtk+-2.0`
clean: 
	rm src/magic-file
	
