#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef DEBUG
#include <ctype.h>
#endif

#include "hex2bin.h"

#ifdef NOSCANF
unsigned int toInt(char c)
{
	if (c >= '0' && c <= '9') { return      c - '0'; }
	if (c >= 'A' && c <= 'F') { return 10 + c - 'A'; }
	if (c >= 'a' && c <= 'f') { return 10 + c - 'a'; }
	return -1;
}
#endif

bin_pkg_t* hex2bin(char *hex)
{
	ssize_t hlen, h;
	bin_pkg_t *bp = NULL;

	hlen = strlen(hex);
	if(hlen < 2) { return bp; }
	if(hlen % 2 != 0) { return bp; }

#ifdef DEBUG
	// Check to make sure we have only hex digits in incoming hex array
	for(int i=0; i<hlen; i++) {
		if(!isxdigit(hex[i])) { return bp; }
	}
#endif

	h = 0;
	bp = calloc(1, sizeof(bin_pkg_t));
	bp->data = malloc(hlen/2);
	while(hlen > 1) {
#ifdef NOSCANF
		bp->data[bp->size++] = 16 * toInt(hex[h]) + toInt(hex[h+1]);
#else
		sscanf(hex+h, "%02hhx", (bp->data)+(bp->size++));
#endif
		hlen -= 2; h += 2;
	}
	return bp;
}

bin_pkg_t* dupe_pkg(bin_pkg_t *src, ssize_t skip)
{
	ssize_t newsize = src->size - skip;
	if(newsize < 1) { return NULL; }
	bin_pkg_t *clone = malloc(sizeof(bin_pkg_t));
	clone->data = calloc(1, newsize);
	if(skip < 0) {
		// Add empty space to the front of the buffer
		memcpy(clone->data - skip, src->data, src->size);
	} else {
		// Create a new package, based on a subset of the incoming package
		memcpy(clone->data, src->data + skip, newsize);
	}
	clone->size = newsize;
	return clone;
}

void destroy_binpkg(bin_pkg_t *bp)
{
	if(bp) {
		if(bp->data) { free(bp->data); }
		free(bp);
	}
}
