#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hex2bin.h"
#include "xform.h"
#include "output.h"

void reverse(bin_pkg_t *bp)
{
	int i;
	unsigned char rev;
	for(i = 0; i < bp->size; i++) {
		rev = (bp->data[i] & 0x01) ? 1 : 0;
		rev = (bp->data[i] & 0x02) ? (rev<<1 | 1) : (rev<<1 | 0);
		rev = (bp->data[i] & 0x04) ? (rev<<1 | 1) : (rev<<1 | 0);
		rev = (bp->data[i] & 0x08) ? (rev<<1 | 1) : (rev<<1 | 0);
		rev = (bp->data[i] & 0x10) ? (rev<<1 | 1) : (rev<<1 | 0);
		rev = (bp->data[i] & 0x20) ? (rev<<1 | 1) : (rev<<1 | 0);
		rev = (bp->data[i] & 0x40) ? (rev<<1 | 1) : (rev<<1 | 0);
		rev = (bp->data[i] & 0x80) ? (rev<<1 | 1) : (rev<<1 | 0);
		bp->data[i] = rev;
	}
}

void xor(bin_pkg_t *bp, unsigned char x)
{
	int i;
	for(i = 0; i < bp->size; i++) {
		bp->data[i] = (bp->data[i] ^ x);
	}
}

void invert(bin_pkg_t *bp)
{
	xor(bp, 0xFF);
}

void shorten(bin_pkg_t *bp, ssize_t newlen)
{
	if((newlen >= 0) && (newlen <= bp->size)) { bp->size = newlen; }
}

void process_line(char *buf, unsigned int line_num)
{
	int i;
	char *op;
	char key[1024];
	bin_pkg_t *tmp, *bp;

	bp = hex2bin(buf);
	if(!bp) {
		fprintf(stderr, "hex2bin(%s) error!\n", buf);
		exit(1);
	}

	for(i=0; i<100; i++) {
		snprintf(key, sizeof(key), "XOP%02d", i);
		op = getenv(key);
		if(op) {
			if(strcmp(op, "reverse") == 0) { reverse(bp); }
			if(strcmp(op, "invert") == 0) { invert(bp); }
			if(strncmp(op, "cut=", 4) == 0) { shorten(bp, atoi(op+4)); }
			if(strncmp(op, "skip=", 5) == 0) {
				tmp = dupe_pkg(bp, atoi(op+5));
				destroy_binpkg(bp);
				bp = tmp;
			}
		}
	}

	int flags = HEX;
	char *output = getenv("OUTPUT");
	if(output) {
		if(strcmp(output, "CSV") == 0) { flags = HEX|CSV; }
		if(strcmp(output, "BIN") == 0) { flags = BIN; }
	}

	print_output(bp, flags);

	destroy_binpkg(bp);
}
