#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main (int argc, char **argv) {
	char *exec_name = argv[0];
	for (int i = 1; i < argc; ++i) {
		int fd = open (argv[i], O_RDONLY);
		if (fd < 0) {
			perror(argv[i]);
			return EXIT_FAILURE;
		}

		if(close (fd)) {
			perror(exec_name);
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}