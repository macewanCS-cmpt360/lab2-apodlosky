/* Q3) Yes, this can be done without using wait(), by having the parent sleep
 * for a second, this should give the child process enough time to write first.
 * You could also use waitpid() on the child's PID.
 *
 * Author: Adam Podlosky <podloskya@mymacewan.ca>
 * Course: CMPT-360 Fall 2018 at MacEwan University
 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	int rc;

	rc = fork();
	if (rc < 0) {
		fprintf(stderr, "fork() failed with %d\n", errno);
		exit(-1);
	} else if (rc == 0) {
		puts("hello");
		fflush(stdout);
	} else {
		//wait(NULL);
		sleep(1);

		puts("goodbye");
		fflush(stdout);
	}

	return 0;
}
