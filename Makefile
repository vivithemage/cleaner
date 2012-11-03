src/magic-file:src/main.c
	gcc -o src/magic-file `xml2-config --cflags` src/main.c  -g -l magic `xml2-config --libs`
clean: 
	rm src/magic-file
	
