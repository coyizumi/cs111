#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#define BUF_SIZE 1024

char *exec_name;

// Reads from the given file descriptor and dumps contents to stdout
// Returns 0 on success, -1 on failure
int dump_file (int fd) {
    int num_read;
    char buf[BUF_SIZE];
    // While we haven't encountered and error or EOF, read contents into buf
    while ((num_read = read(fd, buf, BUF_SIZE)) > 0) {
        // While the number of bytes written is less than the number read
        int tot_written = 0;
        while (tot_written < num_read) {
            // Write remaining bytes in buf to stdout, print error and return on failure
            int num_written = write(STDOUT_FILENO, buf + tot_written, num_read - tot_written);
            if (num_written < 0) {
                perror("dump_file write");
                return -1;
            }
            tot_written += num_written;
        }
    }
    // Print error and return on read failure
    if (num_read < 0) {
        perror ("dump_file read");
        return -1;
    }
    return 0;
}

int main (int argc, char **argv) {
    exec_name = argv[0];
    // For each entry in argv
    for (int i = 1; i < argc; ++i) {
        // Try to open the file, print error and quit on failure
        int fd = open (argv[i], O_RDONLY);
        if (fd < 0) {
            perror (argv[i]);
            return EXIT_FAILURE;
        }

        // Dump the file to stdout, exit on failure
        if (dump_file(fd)) {
            return EXIT_FAILURE;
        }

        // Close the opened file, print error and quit on failure
        if(close (fd)) {
            perror (exec_name);
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}
