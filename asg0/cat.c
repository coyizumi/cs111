#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#define BUF_SIZE 1024

char *exec_name;

int dump_file (int fd) {
	int num_read;
	char buf[BUF_SIZE];
	while ((num_read = read(fd, buf, BUF_SIZE)) > 0) {
		int tot_written = 0;
		while (tot_written < num_read) {
			int num_written = write(STDOUT_FILENO, buf + tot_written, num_read - tot_written);
			if (num_written < 0) {
				perror("dump_file write");
				return -1;
			}
			tot_written += num_written;
		}
	}
	if (num_read < 0) {
		perror ("dump_file read");
		return -1;
	}
	return 0;
}

int main (int argc, char **argv) {
	exec_name = argv[0];
	for (int i = 1; i < argc; ++i) {
		int fd = open (argv[i], O_RDONLY);
		if (fd < 0) {
			perror (argv[i]);
			return EXIT_FAILURE;
		}

		if (dump_file(fd)) {
			return EXIT_FAILURE;
		}

		if(close (fd)) {
			perror (exec_name);
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}
