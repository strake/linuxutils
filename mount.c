#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/mount.h>

struct {
	char *kp, *kn;
	unsigned long v;
} optnames[] = {
	{ "remount",	0,		MS_REMOUNT },
	{ "ro",		"rw",		MS_RDONLY },
	{ "sync",	"async",	MS_SYNCHRONOUS },
	{ "dirsync",	0,		MS_DIRSYNC },
	{ "nodev",	"dev",		MS_NODEV },
	{ "noatime",	"atime",	MS_NOATIME },
	{ "nodiratime",	"diratime",	MS_NODIRATIME },
	{ "noexec",	"exec",		MS_NOEXEC },
	{ "nosuid",	"suid",		MS_NOSUID },
	{ "mand",	"nomand",	MS_MANDLOCK },
	{ "relatime",	"norelatime",	MS_RELATIME },
	{ 0,		0,		0 }
};

int main (int argc, char *argu[]) {
	int ii;
	unsigned long flags = 0;
	char *types;
	void *data;
	
	types = 0;
	data  = 0;
	for (int c = 0; c >= 0; c = getopt (argc, argu, "BMRd:o:t:")) switch (c) {
	case 0:	break;
	case 'B':
		flags |= MS_BIND;
		break;
	case 'M':
		flags |= MS_MOVE;
		break;
	case 'R':
		flags |= MS_REC;
		break;
	case 'd':
		data = optarg;
		break;
	case 'o':
		for (ii = 0; optnames[ii].v; ii++) {
			if (strcmp (optarg, optnames[ii].kp) == 0) {
				flags |= optnames[ii].v;
				break;
			}
			if (strcmp (optarg, optnames[ii].kn) == 0) {
				flags &= ~optnames[ii].v;
				break;
			}
		}
		if (optnames[ii].v) break;
		fprintf (stderr, "%s: Unknown option: %s\n", argu[0], optarg);
		return 1;
	case 't':
		types = optarg;
		break;
	}
	
	argu[--optind] = argu[0];
	argc -= optind;
	argu += optind;
	
	if (argc < 3) {
		fprintf (stderr, "%s: source, target not both given\n", argu[0]);
		return 1;
	}
	
	if (mount (argu[1], argu[2], types, flags, data) < 0) {
		fprintf (stderr, "%s: %s\n", argu[0], strerror (errno));
		return 1;
	}
	
	return 0;
}
