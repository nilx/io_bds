#ifndef _IO_BIN_H
#define _IO_BIN_H

#ifdef __cplusplus
extern "C" {
#endif

#define IO_BIN_VERSION "0.20111004"

#include <stddef.h>

/* io_bin.c */
char *io_bin_info(void);
float *io_bin_read_flt(const char *fname, size_t *nxp, size_t *nyp, size_t *ncp);
void io_bin_write_flt(const char *fname, const float *data, size_t nx, size_t ny, size_t nc);

#ifdef __cplusplus
}
#endif

#endif /* !_IO_BIN_H */
