/* Q2) Yes, both the parent and child processes can access the file descriptor.
 * In my testing, I had to write over 50 lines of text before the parent and
 * child began overwriting written by other.
 *
 * Author: Adam Podlosky <podloskya@mymacewan.ca>
 * Course: CMPT-360 Fall 2018 at MacEwan University
 */
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

static const char msg_init[] = "hello world\n";
static const char msg_child[] = "child says hello\n";
static const char msg_parent[] = "parent says hello\n";

int main(void)
{
	int i, fd, rc;
	size_t length;

	fd = open("q2.txt", O_WRONLY|O_CREAT|O_TRUNC);
	if (fd == -1) {
		fprintf(stderr, "open() failed with %d\n", errno);
		exit(-1);
	}

	write(fd, msg_init, strlen(msg_init));

	rc = fork();
	if (rc < 0) {
		fprintf(stderr, "fork() failed with %d\n", errno);
		exit(-1);
	} else if (rc == 0) {
		length = strlen(msg_child);
		for (i = 0; i < 100; i++)
			write(fd, msg_child, length);
	} else {
		//wait(NULL);
		length = strlen(msg_parent);
		for (i = 0; i < 100; i++)
			write(fd, msg_parent, length);
	}

	close(fd);
	return 0;
}
