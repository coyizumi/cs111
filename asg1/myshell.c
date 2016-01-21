#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdbool.h>

extern char **get_line();

// Keep track of all special characters
char *specials[] = {"(", ")", "<", ">", "|", "&", ";", NULL};
// Keep track of all internal commands
char *commands[] = {"exit", NULL};
// Enumerate all internal commands
enum {EXIT} command;

typedef struct command_s 
{
	char **argv;
	char following_special;
	struct command_s* next;
} command_s;

void print_command_s (command_s *cmd)
{
	if (cmd == NULL) return;
	printf ("argv: ");
	for (int i = 0; cmd->argv[i] != NULL; i++)
	{
		printf ("%s ", cmd->argv[i]);
	}
	printf ("\nfollowing special: %c\n", cmd->following_special);
	print_command_s (cmd->next);
}

command_s *new_command_s (char **argv)
{
	command_s *new_cmd = malloc (sizeof (*new_cmd));
	new_cmd->argv = argv;
	new_cmd->following_special = 0;
	new_cmd->next = NULL;
	return new_cmd;
}

int check_commands (char **args) 
{
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

int check_special (char *str) 
{
	for (int i = 0; specials[i] != NULL; i++) 
	{
		if (str && strcmp(str, specials[i]) == 0) 
		{
			return str[0];
		}
	}
	return 0;
}

int parse_args (char **args) 
{
	int command_status = check_commands(args);
	switch (command_status) 
	{
		case 1: return 0;
		case -1: return -1;
	}
	command_s *root = new_command_s (args);
	command_s *curr = root;
	for(int i = 0; args[i] != NULL; i++) 
	{
		int special = check_special (args[i]);
		if (special)
		{
			curr->following_special = special;
			args[i] = NULL;
			curr->next = new_command_s (args + i + 1);
		}
 	}
 	print_command_s (root);
 	return 0;
}

int main() 
{
 	char **args; 
 	while((args = get_line())) 
 	{
 		parse_args (args);
 	}
}