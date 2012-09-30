src/magic-file:src/main.c
	gcc -Wall -g src/main.c -o src/magic-file -l magic 
clean: 
	rm src/magic-file
	
