#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <pwd.h>
#include <sys/resource.h>

static struct {
	const char *opt;
	int idtype;
} idtypes[] = {
	{ "-p", PRIO_PROCESS },
	{ "-u", PRIO_USER },
	{ "-g", PRIO_PGRP },
	{ 0, -1 }
};

static void usage (const char *prog) {
	fprintf (stderr,
	         "usage: %s -n priority -p pid ... -u user ... -g pgrp ...\n", prog);
	exit (1);
}

int main (int argc, char *argu []) {
	struct passwd *pwd;
	const char *prog;
	char *endptr = NULL;
	int idtype, who, prio;
	int i;
	int ret = 0;

	prog = argu[0];

	if (argc < 2)
		usage (prog);
	argc--;
	argu++;

	if (strcmp (argu[0], "-n"))
		usage (prog);
	argc--;
	argu++;

	prio = strtol (argu[0], &endptr, 10);
	if (*endptr)
		usage (prog);
	argc--;
	argu++;

	/* Default to process id */
	idtype = PRIO_PROCESS;
	for (; argc > 0; argc--, argu++) {
		for (i = 0; idtypes[i].opt; i++) {
			if (strcmp (idtypes[i].opt, argu[0]) == 0) {
				idtype = idtypes[i].idtype;
				break;
			}
		}
		if (idtypes[i].opt)
			continue;

		switch (idtype) {
		case PRIO_USER:
			pwd = getpwnam (argu[0]);
			if (!pwd) {
				fprintf (stderr, "user %s not found, skipping\n", argu[0]);
				continue;
			}
			who = pwd -> pw_uid;
			break;
		default:
			who = strtol (argu[0], &endptr, 10);
			if (*endptr || who < 0) {
				fprintf (stderr, "invalid value %s\n", argu[0]);
				continue;
			}
			break;
		}

		if (setpriority (idtype, who, prio) == -1) {
			fprintf (stderr, "failed to set priority for %d: %s\n",
			         who, strerror(errno));
			ret = 1;
		}
	}

	return ret;
}
