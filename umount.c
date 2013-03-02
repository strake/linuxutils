#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>
#include <sys/mount.h>

int main (int argc, char *argu[]) {
	unsigned long flags = 0;

	for (int c = 0; c >= 0; c = getopt (argc, argu, "fl")) switch (c) {
	case 0:	break;
	case 'f':
		flags |= MNT_FORCE;
		break;
	case 'l':
		flags |= MNT_DETACH;
		break;
	}
	
	argu[--optind] = argu[0];
	argc -= optind;
	argu += optind;
	
	if (argc < 2) {
		fprintf (stderr, "%s: target not given\n", argu[0]);
		return 1;
	}
	
	if (umount2 (argu[1], flags) < 0) {
		fprintf (stderr, "%s: %s\n", argu[0], strerror (errno));
		return 1;
	}
	
	return 0;
}
