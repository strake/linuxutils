#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/swap.h>

int main (int argc, char *argu[]) {
	int flags = 0, failed = 0;
	
	for (int c = 0; c >= 0; c = getopt (argc, argu, "dp:")) switch (c) {
	case 0:	break;
	case 'd':
		flags |= SWAP_FLAG_DISCARD;
		break;
	case 'p':
		flags |= (strtoul (optarg, 0, 10) << SWAP_FLAG_PRIO_SHIFT) & SWAP_FLAG_PRIO_MASK;
		break;
	}
	
	argu[--optind] = argu[0];
	argc -= optind;
	argu += optind;
	
	for (int ii = 1; ii < argc; ii++) if (swapon (argu[ii], flags) < 0) {
		fprintf (stderr, "%s: %s\n", argu[0], strerror (errno));
		failed++;
	}
	
	return failed;
}
