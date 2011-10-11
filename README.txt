% io_bds: binary data stream tools

* overview ... und warnung
* license
* download
* requirements
* compilation
* usage
* todo
* references
* copyright

# OVERVIEW ... UND WARNUNG

io_bds.c contains simple routines to read and write binary data via
unix pipes or similar transports. It focuses on simplicity and low
computational overhead, but is not portable across systems and
machines and doesn't try to minimize the memory usage. The first
incarnation only supports 1D, 2D and 3D float arrays.

ACHTUNG!!
DAS IST NICHT EIN FILE FORMAT ...

This is not yet-another-image-file-format! Image processing is plagued
with ill-defined, poorly documented and useless file formats
introduced for every new image processing project.

io_bds is just a set of routines to transfer some simple data between
processes without encoding/decoding overhead, because the
(de)compression cost of PNG or TIFF files or ASCII text formatting are
very significant when a program is only doing a quick image
transformation.

Using io_bds to read and write image files *will* end with some
portability and maintenance problems. There *will* be problems with
byte-endianness and type width. I won't fix anything and I will let
you and your software die a horrible death.

The format may (will) change, and no care will be taken to maintain
compatibility or to be able to read old data version. The only safety
measure will be to detect (and refuse) format mismatch. io_bds data
should not be stored a sinble second between write() and read(), and
the write() and read() routines should come from the same
implementation, i.e. io_bds.c.

Be kind with your computer, be responsible with your code, use sane
image *file* formats like PNG or TIFF for your image *file* needs.

... ZO RELAXEN UND STREAMEN DER BLINKENBYTES.

If you *only* need to send some data to stdout and receive it from
stdin, io_bds should be just fine, a no-brainer automagically immune
to byte order and type portability headaches.

# LICENSE

io_bds.c is distributed under a GPL3+ or BSD license, at your
option. See the included copyright notice, conditions and disclaimer
for details.

# DOWNLOAD

The latst version of this code is available at
  http://dev.ipol.im/git/?p=nil/io_bds.git
with a mirror at
  https://github.com/nilx/io_bds

# REQUIREMENTS

io_bds.c is ANSI C, and should compile on any system with any ANSI C
compiler.

# COMPILATION

Compile io_bds.c with the same compiler used for the other source files
of your project. C and C++ compilers are possible. io_bds has been
tested with gcc, icc, suncc, pathcc, tcc and nwcc.

You can compile the example codes located in the example folder using
the provided makefile, with the `make` command.

# USAGE

Compile io_bds.c with your program, and include io_bds.h to get the
function declarations. You can use io_bds.c with C or C++ code.

## WRITE

Write a float array with
  io_bds_write_flt(fname, data, nx, ny, nc)
  - fname: the file name, '-' for standard output (use it!)
  - data: float array
  - nx, ny, nc: array size

data is a unidimensional C array and nx, ny and nc are just indications
about how to interpret this array in a 3D context. For example, you
can transmit the same data array of 49152 floats as ...
  io_bds_write_flt('-', data, 128, 128, 4);
  io_bds_write_flt('-', data, 256, 256, 1);
  io_bds_write_flt('-', data, 1024, 48, 1);
... and the same data will be received on the other side, but probably
not processed the same way.

## READ

The data is read into a single float array with
  data = io_bds_read_flt(fname, &nx, &ny, &nc)
  - data: float array on freshly allocated memory
  - fname: the file name, '-' for standard output (use it!)
  - nx, ny, nc: size_t variables to fill with the image size

The float array is unidimentional, with nx*ny*nc elements. ny, ny and
nc are an indication about the 3D interpretation of this array.

## EXAMPLE

See the example folder.

# TODO

* cmake support
* C++ wrappers (vector output, merged functions)

# REFERENCES

Blinkenlights, if you didn't get it
-> http://www.catb.org/~esr/jargon/html/B/blinkenlights.html

# COPYRIGHT

Copyright 2011 Nicolas Limare <nicolas.limare@cmla.ens-cachan.fr>

Copying and distribution of this README file, with or without
modification, are permitted in any medium without royalty provided
the copyright notice and this notice are preserved.  This file is
offered as-is, without any warranty.
