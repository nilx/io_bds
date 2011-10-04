/*
 * This file shows how to use io_bin.c. It is released in the public
 * domain and as such comes with no copyright requirement.
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

/* include the io_bin prototypes */
#include "io_bin.h"

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

    /* the file to read is given as the first command-line argument */
    if (2 > argc) {
        fprintf(stderr, "syntax: %s in.bin\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* read the image info a float array */
    img = io_bin_read_flt(argv[1], &nx, &ny, &nc);

    /* nx, ny and nc hold the image sizes */
    printf("image file: %s\n", argv[1]);
    printf("image size: %i x %i, %i channels\n",
           (int) nx, (int) ny, (int) nc);

    /*
     * img contains the float pixels values.
     * display the pixels
     */
    printf("   x    y    c : value\n");
    for (i = 0; i < nx * ny * nc; i++)
        printf("%04lu %04lu %04lu : %f\n",
               i % nx, i / nx % ny, i / nx / ny, img[i]);

    free(img);

    return EXIT_SUCCESS;
}
