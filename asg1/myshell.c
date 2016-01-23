#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>

extern char **get_line();
extern int yylex_destroy();

char *exec_name;

// Keep track of all special characters
char *specials[] = {"(", ")", "<", ">", "|", "&", ";", NULL};

// Keeps track of an argv for a command, a trailing special character, and
// acts as a linked list for chains of commands.
typedef struct command_s 
{
	char **argv;
	char following_special;
	struct command_s* next;
} command_s;

// Prints the contents of the given command_s
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

// Create and return a new command_s with argv as its argument vector
command_s *new_command_s (char **argv)
{
	command_s *new_cmd = malloc (sizeof (*new_cmd));
	new_cmd->argv = argv;
	new_cmd->following_special = 0;
	new_cmd->next = NULL;
	return new_cmd;
}

// Free memory associated with a command_s, including argv
void free_commands (command_s *root)
{
	if (root == NULL) return;
	for (int i = 0; root->argv[i]; i++)
	{
		free (root->argv[i]);
	}
	command_s *next = root->next;
	free (root);
	free_commands(next);
}

// Checks for built in commands and performs them
// Returns 0 on success, -1 on failure
int check_commands (char **args) 
{
	if (args[0] && strcmp (args[0], "exit") == 0)
	{
		exit(0);
	}
	return 0;
}

// Checks to see if the given string is a special character
// If it is, returns an integer representing that character
// Else, returns 0
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

// Given a command_s, exectures the chain of commands represented by command_s.
int execute_commands (command_s *root)
{
	if (root->following_special == 0)
	{
		int pid;
		if ((pid = fork()))
		{
			int status;
			waitpid (-1, &status, 0);
		}
		else
		{
			execvp (root->argv[0], root->argv);
		}
	}
	else if (root->following_special == '>')
	{
		char *filename = root->next->argv[0];
		int pid;
		if ((pid = fork()))
		{
			int status;
			waitpid (-1, &status, 0);
		}
		else
		{
			// Open filename. Create if not already created, open for writing only.
			// If creating the file, give the user read and write permissions
			int out_fd = open (filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
			close (STDOUT_FILENO);
			dup (out_fd);
			execvp (root->argv[0], root->argv);
		}
	}
	else if (root->following_special == '<')
	{
		char *filename = root->next->argv[0];
		int pid;
		if ((pid = fork()))
		{
			int status;
			waitpid (-1, &status, 0);
		}
		else
		{
			int in_fd = open (filename, O_RDONLY);
			close (STDIN_FILENO);
			dup (in_fd);
			execvp (root->argv[0], root->argv);
		}
	}
	else if (root->following_special == '|')
	{
		int pid;
		int pipefd[2];
		int status = pipe(pipefd);
		int readfd = pipefd[0];
		int writefd = pipefd[1];
		if ((pid = fork()))
		{
			if ((pid = fork()))
			{
				close (readfd); close (writefd);
				int status;
				waitpid (pid, &status, 0);
			}
			else
			{
				if (root->next)
				{
					close (STDIN_FILENO);
					close (writefd);
					dup (readfd);
					execvp (root->next->argv[0], root->next->argv);
				}
			}
		}
		else
		{
			close (STDOUT_FILENO);
			close (readfd);
			dup (writefd);
			execvp (root->argv[0], root->argv);
		}
	}
	return 0;
}

// Parses the line of arguments to execute the desired command
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
			free (args[i]);
			args[i] = NULL;
			curr->next = new_command_s (args + i + 1);
		}
 	}
 	print_command_s (root);
 	execute_commands(root);
 	free_commands(root);
 	return 0;
}

int main(int argc, char **argv) 
{
	exec_name = argv[0];
 	char **args; 
 	printf ("$ ");
 	while((args = get_line())) 
 	{
 		parse_args (args);
 		printf ("$ ");
 	}
 	// Clean up scanner memory
 	yylex_destroy();
}
