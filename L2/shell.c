/* Simple shell.
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

/* Size of buffer for parsing command-line arguments */
#define CMDLINE_BUFFER	1024

/* Maximum number of command-line arguments (including the NULL entry) */
#define MAX_ARGS	10

int main(void)
{
	char *args[MAX_ARGS];
	char *cmdline;
	char *token;
	int background, i, rc;

	cmdline = calloc(1, CMDLINE_BUFFER);
	if (cmdline == NULL) {
		fprintf(stderr, "calloc() failed with %d\n", errno);
		exit(1);
	}

	while (1) {
		printf("prompt> ");
		fflush(stdout);
		fgets(cmdline, CMDLINE_BUFFER, stdin);
		//fprintf(stderr, "[debug] cmdline = *%s*\n", cmdline);

		background = 0;
		i = 0;
		token = strtok(cmdline, "\n ");
		while (token != NULL && i < MAX_ARGS) {
			//fprintf(stderr, "[debug] args[%d] = '%s'\n", i, token);
			args[i++] = strdup(token);
			token = strtok(NULL, "\n ");
		}
		args[i] = NULL;

		if (i > 1 && strcmp(args[i - 1], "&") == 0) {
			/* run in background */
			i--;
			free(args[i]);
			args[i] = NULL;
			background = 1;
		}

		rc = fork();
		if (rc < 0) {
			fprintf(stderr, "fork() failed with %d\n", errno);
			exit(1);
		} else if (rc == 0) {
			/* child: exec the argument array */
			execvp(args[0], args);
		} else {
			/* parent: wait for child if running in foreground */
			if (!background)
				wait(NULL);
		}

		while (i > 0) {
			i--;
			if (args[i] != NULL) {
				free(args[i]);
				args[i] = NULL;
			}
		}
	}

	free(cmdline);
	return 0;
}
