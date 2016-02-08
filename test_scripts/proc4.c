#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int main(){
	
	long i;
	int j, k;
	pid_t pid; 
	int sum = 0;
	for(j = 0; j < 10; j++){
		for(i = 0; i < 4800000000; i++){
			;
		}
	pid = getpid();
	printf("Proc4.c pid:%d; Iteration %d\n", pid, j);
	}
}