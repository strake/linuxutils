#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <getopt.h>
#include <linux/sched.h>

int main (int argc, char *argu[]) {
	int flags = 0;
	
	for (int c = 0; c >= 0; c = getopt (argc, argu, "imnu")) switch (c) {
	case 0:	break;
	case 'i':
		flags |= CLONE_NEWIPC;
		break;
	case 'm':
		flags |= CLONE_NEWNS;
		break;
	case 'n':
		flags |= CLONE_NEWNET;
		break;
	case 'u':
		flags |= CLONE_NEWUTS;
		break;
	}
	
	argu[--optind] = argu[0];
	argc -= optind;
	argu += optind;
	
	if (argc < 2) {
		fprintf (stderr, "%s: no arguments given\n", argu[0]);
		return 1;
	}
	
	if (unshare (flags) < 0 || execvp (argu[1], argu + 1) < 0) {
		fprintf (stderr, "%s: %s\n", argu[0], strerror (errno));
		return 1;
	}
}
