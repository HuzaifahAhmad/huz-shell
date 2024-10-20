app: 
	gcc -o app main.c wildcard_globbing_handler.c parsing_handler.c piping_handler.c external_commands.c built_in_commands.c history_of_commands.c
	
 

executable:
	clang -g -o a.out main.c wildcard_globbing_handler.c parsing_handler.c piping_handler.c external_commands.c built_in_commands.c history_of_commands.c

	

clean: 
	rm app