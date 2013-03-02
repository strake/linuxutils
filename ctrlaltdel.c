#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/reboot.h>

int main (int argc, char *argu[]) {
	if (argc < 2) {
		fprintf (stderr, "%s: no mode given\n", argu[0]);
		return 1;
	}
	
	if (strcmp (argu[1], "soft") == 0 && reboot (RB_DISABLE_CAD) >= 0 ||
	    strcmp (argu[1], "hard") == 0 && reboot (RB_ENABLE_CAD)  >= 0) return 0;
	
	fprintf (stderr, "%s: %s\n", argu[0], strerror (errno));
	return 1;
}
