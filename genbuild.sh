#!/usr/bin/env bash

# generate build.h

[ -n "$CC" ] && [ -n "$CFLAGS" ] || exit 1

branch=`git status | grep '^On branch' | sed -e 's/On branch //'`
hash=`git rev-parse --short HEAD`
date=`date +"%b %e %Y"`
compiler=`$CC --version | head -1`

# Find out actual compile flags used
# Don't use `` backquotes here or there'll be surprises.
cc1=$( $CC $CFLAGS -E -v - </dev/null 2>&1 | grep cc1 | head -1 | tr -d '\\"' )

# Target: try -march first
if echo "$cc1" | grep -q "march="; then
    target=`echo "$cc1" | sed -e 's/.*-march=\([^ ]*\).*/\1/' `
else        # -mcpu then ?
    target=`echo "$cc1" | grep 'mcpu=' | sed -e 's/.*-mcpu=\([^ ]*\).*/\1/' `
fi
# XXX clang

CFLAGS=$( echo "$CFLAGS" | tr -d '\\"' )

echo "#define CINKGO_GIT_BRANCH   \"$branch\""
echo "#define CINKGO_GIT_HASH     \"$hash\""
echo "#define CINKGO_BUILD_DATE   \"$date\""
echo "#define CINKGO_BUILD_TARGET \"$target\""
echo "#define CINKGO_CFLAGS       \"$CFLAGS\""
echo "#define CINKGO_COMPILER     \"$compiler\""
echo "#define CINKGO_CC1          \"$cc1\""