#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

extern char **get_line();

// Keep track of all special characters
char *specials[] = {"(", ")", "<", ">", "|", "&", ";", NULL};
// Keep track of all internal commands
char *commands[] = {"exit", NULL};
// Enumerate all internal commands
enum {EXIT} command;

int check_commands (char **args) {
	// Check if args[0] is an internal command
	for (int i = 0; commands[i] != NULL; i++) {
		// If it is, reference the enum to see which it is and perform appropriate action
		if (args[0] && strcmp(args[0], commands[i]) == 0) {
			switch (i) {
				case EXIT: exit(0);
			}
			return 1;
		}
	}
	return 0;
}

int parse_args (char **args) {
	int command_status = check_commands(args);
	switch (command_status) {
		case 1: return 0;
		case -1: return -1;
	}
	for(int i = 0; args[i] != NULL; i++) {
 		printf("Argument %d: %s\n", i, args[i]);
 		free (args[i]);
 	}
 	return 0;
}

int main() {
 	char **args; 
 	while((args = get_line())) {
 		parse_args (args);
 	}
}