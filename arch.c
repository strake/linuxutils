#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/utsname.h>

int main(int argc, char **argu)
{
	struct utsname utsname;

	if (uname(&utsname)) {
		fprintf(stderr, "%s :%s\n", *argu, strerror(errno));
		return 1;
	}

	printf("%s\n", utsname.machine);

	return 0;
}
