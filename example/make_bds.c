/*
 * This file shows how to use io_bds.c. It is released in the public
 * domain and as such comes with no copyright requirement.
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

/* include the io_bds prototypes */
#include "io_bds.h"

int main(int argc, char **argv)
{
    /*
     * number of columns, lines and channels of the image
     * the image size is used as an array size and index, and int may
     * be a 32bit type on 64bit machines, so the correct type is size_t
     */
    size_t nx, ny, nc;
    /* float array to store an image */
    float *img;
    /* loop counter */
    size_t i;

    /* the image size is read from the command-line */
    if (5 > argc) {
        fprintf(stderr, "syntax: %s nx ny nc out.bds\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* read the image size */
    nx = (size_t) atoi(argv[1]);
    ny = (size_t) atoi(argv[2]);
    nc = (size_t) atoi(argv[3]);

    /* make a float array */
    img = (float *) malloc(nx * ny * nc * sizeof(float));
    if (NULL == img) {
        fprintf(stderr, "not enough memory\n");
        abort();
    }

    /* fill the array */
    for (i = 0; i < nx * ny * nc; i++)
        img[i] = (float) i *(float) i;

    /* write the float array */
    io_bds_write_flt(argv[4], img, nx, ny, nc);

    free(img);

    return EXIT_SUCCESS;
}
