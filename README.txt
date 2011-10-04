% io_dump: simplest image io interface

* overview
* license
* download
* requirements
* compilation
* usage
* todo
* copyright

# OVERVIEW

io_dump.c contains simple routines to read and write binary image data.
This data format is only a simplistic format for local exchange via
unix pipes or similar transports. Is has the lowest possible overhead,
but may be unsafe.

# LICENSE

io_dump.c is distributed under a GPL3+ or BSD license, at your
option. See the included copyright notice, conditions and disclaimer
for details.

# DOWNLOAD

The latst version of this code is available at
  http://dev.ipol.im/git/?p=nil/io_dump.git
with a mirror at
  https://github.com/nilx/io_dump

# REQUIREMENTS

io_dump.c is ANSI C, and should compile on any system with any ANSI C
compiler.

# COMPILATION

Compile io_dump.c with the same compiler used for the other source files
of your project. C and C++ compilers are possible. io_png has been
tested with gcc, icc, suncc, pathcc, tcc and nwcc.

You can compile the example codes located in the example folder using
the provided makefile, with the `make` command.

# USAGE

Compile io_dump.c with your program, and include io_dump.h to get the
function declarations. You can use io_dump.c with C or C++ code.

## READ

The image is read into a single array. For multiple channel images,
the output array successively contains each channel. For example, a
color image with 30 rows and 40 columns is read into a single array of
3600 cells, with:

* the first 1200 cells (30 x 40) containing the red channel
* the next 1200 cells containing the green channel
* the last 1200 cells containing the blue channel

In each channel, the image is stored row after row.

No image structure is needed, and the image size information is
collected via pointer parameters.

The read function is:

* io_dump_read_flt(fname, &nx, &ny, &nc)
  read an image into a [0,1] float array
  - fname: file name; the standard input stream is used if fname is "-"
  - nx, ny, nc: variables to fill with the image size; NULL pointer
    can also be used to ignore a size

## WRITE

The image is written from a single array, with the same layout as
the one received from the read functions.

The write function is:

* io_png_write_flt(fname, data, nx, ny, nc)
  write an image from a [0,1] float array
  - fname: file name, the standard output stream is used if fname is "-"
  - data: image array
  - nx, ny, nc: image size

## EXAMPLE

See the example folder.

# TODO

* cmake support
* C++ wrappers (vector output, merged functions)

# COPYRIGHT

Copyright 2011 Nicolas Limare <nicolas.limare@cmla.ens-cachan.fr>

Copying and distribution of this README file, with or without
modification, are permitted in any medium without royalty provided
the copyright notice and this notice are preserved.  This file is
offered as-is, without any warranty.
