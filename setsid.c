#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main (int argc, char *argu[]) {
	if (argc < 2) {
		fprintf (stderr, "%s: no arguments\n", argu[0]);
		return 1;
	}
	
	if (setsid () < 0 || execvp (argu[1], argu + 1) < 0) {
		fprintf (stderr, "%s: %s\n", argu[0], strerror (errno));
		return 1;
	}
}
