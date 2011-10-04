/*
 * Copyright (c) 2010-2011, Nicolas Limare <nicolas.limare@cmla.ens-cachan.fr>
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under, at your option, the terms of the GNU General Public
 * License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version, or
 * the terms of the simplified BSD license.
 *
 * You should have received a copy of these licenses along this
 * program. If not, see <http://www.gnu.org/licenses/> and
 * <http://www.opensource.org/licenses/bsd-license.html>.
 */

/**
 * @file io_bin.c
 * @brief raw memory image read/write routines
 *
 * @author Nicolas Limare <nicolas.limare@cmla.ens-cachan.fr>
 */

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

/* ensure consistency */
#include "io_bin.h"

/*
 * INFO
 */

/** @brief string tag inserted into the binary */
static char _io_bin_tag[] = "using io_bin " IO_BIN_VERSION;
/** @brief helps tracking versions with the string tag */
char *io_bin_info(void)
{
    return _io_bin_tag;
}

/** @brief abort() wrapper macro with an error message */
#define _IO_BIN_ABORT(MSG) do {                                 \
    fprintf(stderr, "%s:%04u : %s\n", __FILE__, __LINE__, MSG); \
    fflush(stderr);                                             \
    abort();                                                    \
    } while (0);

/** @brief abort() wrapper macro plus the system error */
#define _IO_BIN_ABORT_ERR(MSG) do {                             \
    fprintf(stderr, "%s:%04u : %s : %s\n",                      \
            __FILE__, __LINE__, MSG, strerror(errno));          \
    fflush(stderr);                                             \
    abort();                                                    \
    } while (0);

/** @brief safe malloc wrapper */
static void *_io_bin_safe_malloc(size_t size)
{
    void *memptr;

    if (NULL == (memptr = malloc(size)))
        _IO_BIN_ABORT("not enough memory");
    return memptr;
}

/** @brief safe malloc wrapper macro with safe casting */
#define _IO_BIN_SAFE_MALLOC(NB, TYPE)                                   \
    ((TYPE *) _io_bin_safe_malloc((size_t) (NB) * sizeof(TYPE)))

/*
 * READ
 */

/**
 * @brief read a float array
 *
 * The array size (3 x size_t) is read first, then the array data.
 *
 * @param fname file name, "-" for stdin
 * @param nxp, nyp, ncp pointers to variables to be filled with the number of
 *        columns, lines and channels of the image
 * @return pointer to an array of pixels, abort() on error
 */
float *io_bin_read_flt(const char *fname,
                       size_t * nxp, size_t * nyp, size_t * ncp)
{
    float *data;
    FILE *fp;
    size_t nx, ny, nc;
    size_t size;

    if (0 == strcmp(fname, "-"))
        fp = stdin;
    else {
        fprintf(stderr,
                "Warning: binary format is not safe for file storage.\n");
        if (NULL == (fp = fopen(fname, "rb")))
            _IO_BIN_ABORT_ERR("failed to open file");
    }
    /* get nx, ny, nc */
    if (1 != fread(&nx, sizeof(size_t), 1, fp)
        || 1 != fread(&ny, sizeof(size_t), 1, fp)
        || 1 != fread(&nc, sizeof(size_t), 1, fp))
        _IO_BIN_ABORT("read error");

    size = nx * ny * nc;
    /* allocate the memory */
    data = _IO_BIN_SAFE_MALLOC(size, float);
    /* read the data */
    if (size != fread(data, sizeof(float), size, fp))
        _IO_BIN_ABORT_ERR("read error");

    if (stdin != fp)
        (void) fclose(fp);
    *nxp = nx;
    *nyp = ny;
    *ncp = nc;
    return data;
}

/*
 * WRITE
 */

/**
 * @brief write a float array
 *
 * The array size (3 x size_t) is written first, then the array data.
 *
 * @param fname file name, "-" for stdout
 * @param data array to write
 * @param nx, ny, nc dimensions of the array
 * @return void, abort() on error
 */
void io_bin_write_flt(const char *fname, const float *data,
                      size_t nx, size_t ny, size_t nc)
{
    FILE *fp;
    size_t size;

    if (0 == strcmp(fname, "-"))
        fp = stdout;
    else {
        fprintf(stderr,
                "Warning: binary format is not safe for file storage.\n");
        if (NULL == (fp = fopen(fname, "wb")))
            _IO_BIN_ABORT_ERR("failed to open file");
    }
    /* put nx, ny, nc */
    if (1 != fwrite((void *) &nx, sizeof(size_t), 1, fp)
        || 1 != fwrite((void *) &ny, sizeof(size_t), 1, fp)
        || 1 != fwrite((void *) &nc, sizeof(size_t), 1, fp))
        _IO_BIN_ABORT_ERR("write error");

    size = nx * ny * nc;
    /* write the data */
    if (size != fwrite(data, sizeof(float), size, fp))
        _IO_BIN_ABORT_ERR("write error");

    if (stdout != fp)
        (void) fclose(fp);
    return;
}
