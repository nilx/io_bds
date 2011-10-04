#ifndef _IO_DUMP_H
#define _IO_DUMP_H

#ifdef __cplusplus
extern "C" {
#endif

#define IO_DUMP_VERSION "0.20111004"

#include <stddef.h>

/* io_dump.c */
char *io_dump_info(void);
float *io_dump_read_flt(const char *fname, size_t *nxp, size_t *nyp, size_t *ncp);
void io_dump_write_flt(const char *fname, const float *data, size_t nx, size_t ny, size_t nc);

#ifdef __cplusplus
}
#endif

#endif /* !_IO_DUMP_H */
