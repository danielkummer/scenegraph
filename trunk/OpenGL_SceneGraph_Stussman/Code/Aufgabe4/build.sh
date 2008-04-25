#!/bin/sh
touch ChangeLog
svn2cl
aclocal && autoconf && automake --add-missing && ./configure && make


