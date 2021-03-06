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

// In many most cases, when a system call fails all we can do is print an 
// error and die. This macro turns what was once a 4-5 line statement into a 
// one liner. If the given expression is true, print an error and die.
#define perror_die_on_true(expr) { \
    if (expr) {                    \
        perror (exec_name);        \
        exit(1);                   \
    }                              \
}

extern char **get_line();
extern void lex_cleanup();

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
    // If malloc fails, perror and die
    perror_die_on_true (new_cmd == NULL);
    new_cmd->argv = argv;
    new_cmd->following_special = 0;
    new_cmd->next = NULL;
    return new_cmd;
}

// Free memory associated with a command_s, including argv
void free_command_s (command_s *root)
{
    if (root == NULL) return;
    for (int i = 0; root->argv[i]; i++)
    {
        free (root->argv[i]);
    }
    command_s *next = root->next;
    free (root);
    free_command_s (next);
}

// Checks for built in commands and performs them
// Returns 0 on success, -1 on failure
int check_commands (char **args) 
{
    if (args[0] && strcmp (args[0], "exit") == 0)
    {
        for (int i = 0; args[i]; i++) free (args[i]);
        lex_cleanup();
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
    // If fork failed, perror and die
    perror_die_on_true (pid < 0);
    // If we're child
    if (pid == 0)
    {
        // If readfd or writefd is other than default, dup it
        if (readfd != STDIN_FILENO)
        {
            perror_die_on_true (close (STDIN_FILENO));
            perror_die_on_true (dup (readfd) < 0);
        }
        if (writefd != STDOUT_FILENO)
        {
            perror_die_on_true (close (STDOUT_FILENO));
            perror_die_on_true (dup (writefd) < 0);
        }
        // If execvp returns, something horrible has happened
        perror_die_on_true (execvp (path, argv));
    }
    // If we're the parent
    return pid;
}

// Given a command_s, exectures the chain of commands represented by command_s.
int execute_commands (int readfd, command_s *root)
{
    // May be null if line ends in a ;
    if (root == NULL) return 0;

    int pid = 0;
    // No IO redirects
    if (root->following_special == 0)
    {
        pid = fork_and_exec(readfd, STDOUT_FILENO, root->argv[0], root->argv);
    }
    // Redirect to file
    else if (root->following_special == '>')
    {
        // Check that root->next is valid
        if (!(root->next) && !(root->next->argv[0]))
        {
            fprintf (stderr, "%s: No output file specified\n", exec_name);
            return 0;
        }
        // Open file (create it as user read and writable if it doesn't exist)
        char *filename = root->next->argv[0];
        int out_fd = open (filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
        // If we can't write to file, print an error and die
        perror_die_on_true (out_fd < 0);

        pid = fork_and_exec (readfd, out_fd, root->argv[0], root->argv);
        perror_die_on_true (close (out_fd));
        // Move root forward to next so we can check for semicolons
        root = root->next;
    }
    // Get input from file
    else if (root->following_special == '<')
    {
        // Check that root->next is valid
        if (!(root->next) || !(root->next->argv[0]))
        {
            fprintf (stderr, "%s: No input file specified\n", exec_name);
            return 0;
        }
        // Open file to read
        char *filename = root->next->argv[0];
        int in_fd = open (filename, O_RDONLY);
        // If we can't open the file, print an error and abort command
        if (in_fd < 0)
        {
        	perror (filename);
        	return -1;
        }
        if (root->next->following_special == '|')
        {
            int pipefd[2];
            int status = pipe(pipefd);
            perror_die_on_true (status < 0);

            int read_pipe = pipefd[0];
            int write_pipe = pipefd[1];

            pid = fork_and_exec(in_fd, write_pipe, root->argv[0], root->argv);
            perror_die_on_true (close (write_pipe));

            if (readfd != STDIN_FILENO) 
            {
                perror_die_on_true (close (readfd));
            }

            return execute_commands (read_pipe, root->next->next);
        }
        int out_fd = STDOUT_FILENO;
        if (root->next->following_special == '>')
        {
            if (!(root->next->next) || (!root->next->next->argv[0]))
            {
                fprintf (stderr, "%s: No output file specified\n", exec_name);
                return 0;
            }
            char *out_filename = root->next->next->argv[0];
            out_fd = open (out_filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
            perror_die_on_true (out_fd < 0);
        }
        pid = fork_and_exec (in_fd, out_fd, root->argv[0], root->argv);
        perror_die_on_true (close (in_fd));
        if (out_fd != STDOUT_FILENO)
        {
            perror_die_on_true (close (out_fd));
            // In this case, we need to move root forward twice to check for semicolons
            root = root->next;
        }
        // Move root forward to next so we can check for semicolons
        root = root->next;
    }
    // Pipe
    else if (root->following_special == '|')
    {
        // Check that root->next is valid
        if (!(root->next) && !(root->next->argv[0]))
        {
            fprintf (stderr, "%s: No command to pipe to\n", exec_name);
            return 0;
        }
        // Create pipe
        int pipefd[2];
        int status = pipe(pipefd);
        perror_die_on_true (status < 0);

        int read_pipe = pipefd[0];
        int write_pipe = pipefd[1];

        // Fork first process
        pid = fork_and_exec(readfd, write_pipe, root->argv[0], root->argv);
        // Close write_pipe as parent
        perror_die_on_true (close (write_pipe));

        // If readfd is from a pipe, close it
        if (readfd != STDIN_FILENO)
        {
            perror_die_on_true (close (readfd));
        }
        // Recursively execute the commands after the pipe, giving the read end of the pipe
        // as the fd to read from
        return execute_commands (read_pipe, root->next);
    }
    // If we got our input from a pipe, close that input
    if (readfd != STDIN_FILENO)
    {
        perror_die_on_true (close (readfd));
    }
    // If we executed a command, wait for it
    int status = 0;
    if (pid)
    {
        int status = 0;
        perror_die_on_true (waitpid (pid, &status, 0) < 0);
    }
    // If there is a semicolon, execute the command(s) following the semicolon
    if (root->following_special == ';')
        return execute_commands(STDIN_FILENO, root->next);
    return status;
}

// Parses the line of arguments to execute the desired command
int parse_args (char **args) 
{
    // Check for built-in commands, and exit if found
    int command_status = check_commands(args);
    switch (command_status) 
    {
        case 1: return 0;
        case -1: return -1;
    }
    // Create datastructure to hold command list
    command_s *root = new_command_s (args);
    command_s *curr = root;
    // Run through args and build command list
    for(int i = 0; args[i] != NULL; i++) 
    {
        // Special characters will be nulled and act as delimeters between
        // the argument vectors of each individual command
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
    free_command_s(root);
    return 0;
}

int main(int argc, char **argv) 
{
    exec_name = argv[0];
    char **args;
    // Repeatedly print a $ then read and execute a line
    printf ("$ ");
    while((args = get_line())) 
    {
        parse_args (args);
        printf ("$ ");
    }
    // Clean up scanner memory
    lex_cleanup();
}
