/* Q1) The child process is a copy of the parent process, so when the child
 * makes changes to the stack variable 'x', those changes will NOT be visible
 * to the parent process.
 *
 * Author: Adam Podlosky <podloskya@mymacewan.ca>
 * Course: CMPT-360 Fall 2018 at MacEwan University
 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	int rc, x;

	x = 100;
	printf("init: x=%d, pid=%d\n", x, getpid());

	rc = fork();
	if (rc < 0) {
		fprintf(stderr, "fork() failed with %d\n", errno);
		exit(-1);
	} else if (rc == 0) {
		printf("child: x=%d, pid=%d\n", x, getpid());
		x += 33;
		printf("child: x=%d, pid=%d\n", x, getpid());
	} else {
		wait(NULL);

		printf("parent: x=%d, pid=%d\n", x, getpid());
		x += 66;
		printf("parent: x=%d, pid=%d\n", x, getpid());
	}

	return 0;
}
