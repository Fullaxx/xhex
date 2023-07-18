#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hex2bin.h"

int main(int argc, char *argv[])
{
	bin_pkg_t *aa = hex2bin("414100");
	printf("%s (%ld)\n", aa->data, aa->size);

	bin_pkg_t *err = dupe_pkg(aa, 99);
	if(err) {
		fprintf(stderr, "err should be NULL!\n");
		exit(1);
	}

	bin_pkg_t *a = dupe_pkg(aa, 1);
	printf("%s (%ld)\n", a->data, a->size);

	bin_pkg_t *baa = dupe_pkg(aa, -1);
	baa->data[0] = 'B';
	printf("%s (%ld)\n", baa->data, baa->size);

	bin_pkg_t *large = dupe_pkg(a, -99999);
	memset(large->data, 'X', 99999);
	printf("... %c%c%c (%ld)\n",
		large->data[99997],
		large->data[99998],
		large->data[99999],
		large->size);

	destroy_binpkg(a);
	destroy_binpkg(aa);
	destroy_binpkg(baa);
	destroy_binpkg(large);

	return 0;
}
