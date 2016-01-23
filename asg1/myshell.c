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
	if (new_cmd == NULL)
	{
		perror(exec_name);
		exit(1);
	}
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
		for (int i = 0; args[i]; i++) free (args[i]);
		yylex_destroy();
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

int fork_and_exec (int readfd, int writefd, char *path, char **argv)
{
	int pid = fork();
	// If fork failed
	if (pid < 0)
	{
		perror (exec_name);
		exit (1);
	}
	// If we're child
	else if (pid == 0)
	{
		if (readfd != STDIN_FILENO)
		{
			close (STDIN_FILENO);
			dup (readfd);
		}
		if (writefd != STDOUT_FILENO)
		{
			close (STDOUT_FILENO);
			dup (writefd);
		}
		// If execvp returns, something horrible happened
		if (execvp (path, argv))
		{
			perror (exec_name);
			exit (1);
		}
	}
	// If we're the parent
	return pid;
}

// Given a command_s, exectures the chain of commands represented by command_s.
int execute_commands (int readfd, command_s *root)
{
	if (root == NULL) return 0;
	int pid = 0;
	if (root->following_special == 0)
	{
		pid = fork_and_exec(readfd, STDOUT_FILENO, root->argv[0], root->argv);
	}
	else if (root->following_special == '>')
	{
		if (!(root->next) && !(root->next->argv[0]))
		{
			fprintf (stderr, "%s: No output file specified\n", exec_name);
			return 0;
		}
		char *filename = root->next->argv[0];
		int out_fd = open (filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
		pid = fork_and_exec (readfd, out_fd, root->argv[0], root->argv);
		close (out_fd);
		root = root->next;
	}
	else if (root->following_special == '<')
	{
		if (!(root->next) && !(root->next->argv[0]))
		{
			fprintf (stderr, "%s: No input file specified\n", exec_name);
			return 0;
		}
		char *filename = root->next->argv[0];
		int in_fd = open (filename, O_RDONLY);
		pid = fork_and_exec (in_fd, STDOUT_FILENO, root->argv[0], root->argv);
		close (in_fd);
		root = root->next;
	}
	else if (root->following_special == '|')
	{
		if (!(root->next) && !(root->next->argv[0]))
		{
			fprintf (stderr, "%s: No command to pipe to\n", exec_name);
			return 0;
		}
		int pipefd[2];
		int status = pipe(pipefd);
		int read_pipe = pipefd[0];
		int write_pipe = pipefd[1];

		pid = fork_and_exec(readfd, write_pipe, root->argv[0], root->argv);
		close (write_pipe);
		if (readfd != STDIN_FILENO)
		{
			if (close (readfd))
			{
				perror (exec_name);
				exit(1);
			}
		}
		return execute_commands (read_pipe, root->next);
	}
	if (readfd != STDIN_FILENO)
	{
		if (close (readfd))
		{
			perror (exec_name);
			exit(1);
		}
	}
	int status = 0;
	if (pid)
	{
		int status = 0;
		waitpid (pid, &status, 0);
	}
	if (root->following_special == ';')
		return execute_commands(STDIN_FILENO, root->next);
	return status;
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
			curr = curr->next;
		}
 	}
 	execute_commands(STDIN_FILENO, root);
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
