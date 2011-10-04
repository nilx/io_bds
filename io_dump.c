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
 * @file io_dump.c
 * @brief raw memory dunmp read/write routines
 *
 * @author Nicolas Limare <nicolas.limare@cmla.ens-cachan.fr>
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* ensure consistency */
#include "io_dump.h"

/*
 * INFO
 */

/** @brief string tag inserted into the binary */
static char _io_dump_tag[] = "using io_png " IO_DUMP_VERSION;
/** @brief helps tracking versions with the string tag */
char *io_dump_info(void)
{
    return _io_dump_tag;
}

/** @brief abort() wrapper macro with an error message */
#define _IO_DUMP_ABORT(MSG) do {                                 \
    fprintf(stderr, "%s:%04u : %s\n", __FILE__, __LINE__, MSG); \
    fflush(stderr);                                             \
    abort();                                                    \
    } while (0);

/** @brief safe malloc wrapper */
static void *_io_dump_safe_malloc(size_t size)
{
    void *memptr;

    if (NULL == (memptr = malloc(size)))
        _IO_DUMP_ABORT("not enough memory");
    return memptr;
}

/** @brief safe malloc wrapper macro with safe casting */
#define _IO_DUMP_SAFE_MALLOC(NB, TYPE)                                   \
    ((TYPE *) _io_dump_safe_malloc((size_t) (NB) * sizeof(TYPE)))

/*
 * READ
 */

/**
 * @brief read an image into a float array
 *
 * The image is read into an array with the deinterlaced channels,
 * with values in [0,1].
 *
 * @param fname PNG file name
 * @param nxp, nyp, ncp pointers to variables to be filled with the number of
 *        columns, lines and channels of the image
 * @return pointer to an array of pixels, abort() on error
 */
float *io_dump_read_flt(const char *fname,
                       size_t * nxp, size_t * nyp, size_t * ncp)
{
    float *data;
    FILE * fp;
    size_t nx, ny, nc;
    size_t size;

    if (0 == strcmp(fname, "-"))
        fp = stdin;
    else if (NULL == (fp = fopen(fname, "rb")))
        _IO_DUMP_ABORT("failed to open file");
    /* get nx, ny, nc */
    if (1 != fread(&nx, sizeof(size_t), 1, fp)
	|| 1 != fread(&ny, sizeof(size_t), 1, fp)
	|| 1 != fread(&nc, sizeof(size_t), 1, fp))
	_IO_DUMP_ABORT("read error");
    size = nx * ny * nc;
    /* allocate the memory */
    data = _IO_DUMP_SAFE_MALLOC(size, float);
    /* read the data */
    if (size != fread(data, sizeof(float), size, fp))
	_IO_DUMP_ABORT("read error");

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
 * @brief write a float array into a file
 *
 * @param fname file name
 * @param data deinterlaced (RRR.GGG.BBB.AAA.) array to write 
 * @param nx, ny, nc number of columns, lines and channels of the image
 * @return void, abort() on error
 */
void io_dump_write_flt(const char *fname, const float* data,
                       size_t nx, size_t ny, size_t nc)
{
    FILE * fp;
    size_t size;

    if (0 == strcmp(fname, "-"))
        fp = stdout;
    else if (NULL == (fp = fopen(fname, "wb")))
        _IO_DUMP_ABORT("failed to open file");
    /* put nx, ny, nc */
    if (1 != fwrite(&nx, sizeof(size_t), 1, fp)
	|| fwrite(&ny, sizeof(size_t), 1, fp)
	|| fwrite(&nc, sizeof(size_t), 1, fp))
	_IO_DUMP_ABORT("write error");
    size = nx * ny * nc;
    /* read the data */
    if (size != fwrite(data, sizeof(float), size, fp))
	_IO_DUMP_ABORT("write error");

    if (stdout != fp)
        (void) fclose(fp);
    return;
}

