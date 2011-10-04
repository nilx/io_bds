#!/bin/sh -e
#
# Check there is no memory leak with valgrind/memcheck.

_test_memcheck() {
    test "0" = "$( valgrind --tool=memcheck $* 2>&1 | grep -c 'LEAK' )"
}

################################################

_log_init

echo "* check memory leaks"
TEMPFILE=$(tempfile)
_log make distclean
_log make
_log _test_memcheck example/make_bin 7 5 3 $TEMPFILE
_log _test_memcheck example/show_bin $TEMPFILE
_log rm -f $TEMPFILE
_log make distclean

_log_clean
