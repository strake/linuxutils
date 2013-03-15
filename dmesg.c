#include <unistd.h>
#include <sys/klog.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>

enum {
	SYSLOG_ACTION_READ_ALL = 3,
	SYSLOG_ACTION_CLEAR = 5,
	SYSLOG_ACTION_SIZE_BUFFER = 10,
};

static void usage (const char *prog) {
	fprintf (stderr, "usage: %s [options]\n", prog);
	fprintf (stderr, " -C\tClear the ring buffer.\n");
}

int main (int argc, char **argu) {
	int n;
	int c;
	char *buf;
	const char *prog;

	prog = argu[0];

	for (c = 0; c >= 0; c = getopt (argc, argu, "C")) {
		switch (c) {
		case 'C':
			if (klogctl (SYSLOG_ACTION_CLEAR, NULL, 0) < 0) {
				fprintf (stderr, "%s: %s\n", argu[0],
					 strerror (errno));
				return 1;
			}
			return 0;
		case '?':
			usage (prog);
			return 1;
		}
	}

	n = klogctl (SYSLOG_ACTION_SIZE_BUFFER, NULL, 0);
	if (n < 0) {
		fprintf (stderr, "%s: %s\n", argu[0],
			 strerror (errno));
		return 1;
	}

	buf = malloc (n);
	if (!buf) {
	        fprintf (stderr, "%s: failed to allocate memory\n", argu[0]);
	        return 1;
        }
	n = klogctl (SYSLOG_ACTION_READ_ALL, buf, n);
	if (n < 0 || (write (STDOUT_FILENO, buf, n) != n)) {
		fprintf (stderr, "%s: %s\n", argu[0],
			 strerror (errno));
		free (buf);
		return 1;
	}
	free (buf);

	return 0;
}
