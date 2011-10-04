#!/bin/sh
#
# Test the code compilation and execution.

# Test the code correctness by computing the min/max/mean/std of a
# known image, lena. The expected output is in the data folder.
_test_run() {
    TEMPFILE=$(tempfile)
    example/make_bin 7 5 3 - | example/show_bin - >> $TEMPFILE
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
for CC in cc c++ gcc g++ tcc nwcc clang icc pathcc suncc; do
    which $CC || continue
    echo "* $CC compiler"
    _log make distclean
    case $CC in
	"gcc"|"g++")
	    _log make CC=$CC ;;
	*)
	    _log make CC=$CC CFLAGS= ;;
    esac
    _log _test_run
done

_log make distclean

_log_clean
