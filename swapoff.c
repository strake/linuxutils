#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/swap.h>

int main (int argc, char *argu[]) {
	int failed = 0;
	
	for (int c = 0; c >= 0; c = getopt (argc, argu, "")) switch (c) {
	}
	
	argu[--optind] = argu[0];
	argc -= optind;
	argu += optind;
	
	for (int ii = 1; ii < argc; ii++) if (swapoff (argu[ii]) < 0) {
		fprintf (stderr, "%s: %s\n", argu[0], strerror (errno));
		failed++;
	}
	
	return failed;
}
