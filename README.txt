% io_bds: binary data stream tools

* overview ... und warnung
* license
* download
* requirements
* compilation
* usage
* todo
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
with ill-defined, poorly documented and useless file formats used for
every new image processing project.

io_bds is just a set of routines to transfer some simple data between
processes without encoding/decoding overhead, because the
(de)compression cost of PNG or TIFF files is significant when a
program is only doing a quick image transformation.

Using io_bds this to read and write image files *will* end with some
portability and maintenance problems. There *will* be problems with
byte-endianness and type width. I won't fix anything and I will let
you and your software die a horrible death.

The format may (will) change, and no care will be taken to maintain
compatibility or to be able to read old data version. The only safety
measure will be to detect (and refuse) data format mismatch. io_bds
data should not be stored a sinble second between write() and read(),
and the write() and read() routines should come from the same
implementation, i.e. io_bds.c.

Be kind with your computer, be responsible with your code, use safe
and clean image *file* formats like PNG or TIFF for your image *file*
needs.

On the other hand, if you *only* need to send some data to stdout and
receive it from stdin, io_bds should be just fine. In that case,
io_bds is automagically and by design immune to byte-endianness and
type portability problems.

... ZO RELAXEN UND STREAMEN DER BLINKENBYTES.

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

## READ

TODO: REWRITE

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

* io_bds_read_flt(fname, &nx, &ny, &nc)
  read a float array
  - fname: file name; the standard input stream is used if fname is "-"
  - nx, ny, nc: variables to fill with the image size.

## WRITE

TODO: REWRITE

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

# REFERENCES

Blinkenlights. http://www.catb.org/~esr/jargon/html/B/blinkenlights.html

# COPYRIGHT

Copyright 2011 Nicolas Limare <nicolas.limare@cmla.ens-cachan.fr>

Copying and distribution of this README file, with or without
modification, are permitted in any medium without royalty provided
the copyright notice and this notice are preserved.  This file is
offered as-is, without any warranty.
