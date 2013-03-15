#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main (int argc, char **argu) {
	struct stat ttysb;
	char *tty;
	int ret;
	int mask;

	tty = ttyname (STDERR_FILENO);
	if (!tty) {
		fprintf (stderr, "%s: %s\n", argu[0], strerror (errno));
		return 1;
	}

	ret = stat (tty, &ttysb);
	if (ret < 0) {
		fprintf (stderr, "%s: %s\n", argu[0], strerror (errno));
		return 1;
	}

	mask = S_IWGRP | S_IWOTH;
	if (argc < 2) {
		if (ttysb.st_mode & mask) {
			puts ("is y");
			return 0;
		}
		puts ("is n");
		return 0;
	}

	switch (argu[1][0]) {
	case 'y':
		ret = chmod (tty, ttysb.st_mode | mask);
		if (ret < 0) {
			fprintf (stderr, "%s: %s\n", argu[0],
				 strerror (errno));
			return 1;
		}
		break;
	case 'n':
		ret = chmod (tty, ttysb.st_mode & ~mask);
		if (ret < 0) {
			fprintf (stderr, "%s: %s\n", argu[0],
				 strerror (errno));
			return 1;
		}
		break;
	default:
		fprintf (stderr, "%s: invalid argument\n", argu[0]);
		return 1;
	}

	return 0;
}
