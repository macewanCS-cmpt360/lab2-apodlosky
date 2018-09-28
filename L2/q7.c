/* Q7) There is no output from the child process because puts() is writing to a
 * standard file descriptor that has been closed prior.

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
		close(STDOUT_FILENO);
		rc = puts("hello from child");
		if (rc < 0)
			fprintf(stderr, "puts() failed with %d\n", errno);
	} else {
		wait(NULL);
		puts("hello from parent");
	}

	return 0;
}
