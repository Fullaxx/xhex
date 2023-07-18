#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "hex2bin.h"

#define BIN (0x0)
#define HEX (0x1)
#define CSV (0x2)

void print_output(bin_pkg_t *bp, unsigned int flags);

#ifdef __cplusplus
}
#endif

#endif /* __OUTPUT_H__ */
