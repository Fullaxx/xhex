#include <stdio.h>

#include "hex2bin.h"
#include "output.h"

void print_output(bin_pkg_t *bp, unsigned int flags)
{
	int i;

	for(i = 0; i < bp->size; i++) {
		if(flags & HEX) {
			if(flags & CSV) {
				printf("\"%02X\",", bp->data[i]);
			} else {
				printf("%02X", bp->data[i]);
			}
		} else {
			printf("%c", bp->data[i]);
		}
	}

	if(flags > 0) { printf("\n"); }
}
