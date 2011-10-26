#!/bin/sh
#
# Test the code compilation and execution.

# Test the code correctness by computing the min/max/mean/std of a
# known image, lena. The expected output is in the data folder.
_test_run() {
    TEMPFILE=$(tempfile)
    ./example/make_bds 7 5 3 - | ./example/show_bds - > $TEMPFILE
    dos2unix $TEMPFILE #when compiled with mingw
    test "6ce1aceadc9ac31e8e1a472750d766b2  $TEMPFILE" \
	= "$(md5sum $TEMPFILE)"
    rm -f $TEMPFILE
}

################################################

_log_init

echo "* default build, test, clean, rebuild"
_log make -B debug
_log _test_run
_log make -B
_log _test_run
_log make
_log make clean
_log make

echo "* compiler support"
for CC in cc c++ c89 c99 gcc g++ tcc nwcc clang icc pathcc suncc \
    i586-mingw32msvc-cc; do
    which $CC || continue
    echo "* $CC compiler"
    _log make distclean
    case $CC in
	"dmc") # inter-processs pipes are broken when running via wine
	    _log make -f makefile.dmc
	    _log make -f makefile.dmc clean
	    ;;
	*)
	    _log make CC=$CC
	    ;;
    esac
    _log _test_run
done

_log make distclean

_log_clean
