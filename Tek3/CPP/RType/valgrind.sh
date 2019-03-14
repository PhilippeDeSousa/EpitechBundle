#! /bin/sh

valgrind --suppressions=ValgrindFilter.txt $*
