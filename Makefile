app: 
	gcc -o app main.c wildcard_globbing_handler.c parsing_handler.c
	
 
clean: 
	rm app