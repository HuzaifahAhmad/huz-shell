char* wildcard_globbing(char input_string[]);

char** parsing_handler(char input_string[]);

void piping_handler(char **tokenized_array);

void executing_command(char **tokenized_array_for_execution);

void execute_external_command(char **external_command_execution);

void execute_built_in_command(char **built_in_command_execution); 

void print_command_history(char input_string[]);

char *trim_whitespace(char *str);