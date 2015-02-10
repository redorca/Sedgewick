
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/time.h>
#include <unistd.h>

static uint64_t
get_seed()
{
	int fd, rv;
	uint64_t seed;
	struct timeval tv;

	gettimeofday(&tv, NULL);
	seed = tv.tv_usec;

	fd = open("/dev/urandom", O_RDONLY);
	if (!(fd < 0)) {
		read(fd, &seed, 8);
		close(fd);
	}

	return seed;
}

int
random_init()
{
	srandom(get_seed());
}

