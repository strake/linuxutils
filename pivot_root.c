#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/syscall.h>

int main (int argc, char *argu[]) {
	if (argc < 3) {
		fprintf (stderr, "%s: old, new root not both given", argu[0]);
		return 1;
	}
	
	if (syscall (SYS_pivot_root, argu[1], argu[2]) < 0) {
		fprintf (stderr, "%s: %s\n", argu[0], strerror (errno));
		return 1;
	}
	
	return 0;
}
