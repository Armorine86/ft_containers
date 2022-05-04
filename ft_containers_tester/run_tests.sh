#!/bin/sh

# Project location
FT_CONTAINERS="../includes/Vector/"

# Tests location
TEST_DIR="tests"

# Containers to test
CONTAINERS="vector stack map set"

# Check for leaks
LEAK_CHECK=1

if [[ $LEAK_CHECK == 1 ]]; then
    LEAK_FLAG="-DLEAK_CHECK"
else
    LEAK_FLAG=""
fi

# check OS for echo -e flag (MAC or Linux)
if [[ "$OSTYPE" == "darwin"* ]]; then
    ECHO_FLAG=""
else
    ECHO_FLAG="-e"
fi

# Objects dir
OBJ="obj"

# Create objects dir
mkdir -p $OBJ

# Diff log dir
LOGS="logs"

# Create logs dir
mkdir -p $LOGS

LOG_FT="ft.log.txt"
LOG_STD="std.log.txt"

DIFFS="diffs"

mkdir -p $DIFFS

# ANSI Colors
RED="\033[31;1m"
GREEN="\033[32;1m"
RST="\033[0m"

# Compiler
CC="clang++"

# Compiler flags
FLAGS="-Wall -Werror -Wextra -std=c++98 -stdlib=libc++ -I$FT_CONTAINERS -I$TEST_DIR"

# Print success
test_success() {
    echo $ECHO_FLAG $1:$GREEN OK! $RST
}

# Print failure
test_fail() {
    echo $ECHO_FLAG $1:$RED KO! $RST
}

# Print red text
print_err() {
    echo $ECHO_FLAG $RED$1$RST
}

test_suite() {
    mkdir -p $LOGS/$1
    mkdir -p $DIFFS/$1

    for t in $2 ; do
        LOG1=$LOGS/$1/"$t"_"$LOG_FT"
        LOG2=$LOGS/$1/"$t"_"$LOG_STD"

        if $CC $FLAGS $LEAK_FLAG $TEST_DIR/$1/$t.cpp ; then
            ./a.out > $LOG1
        else
            print_err "Error compiling"
            test_fail "$1 $t"
            continue
        fi

        if $CC $FLAGS $LEAK_FLAG -DUSE_STD $TEST_DIR/$1/$t.cpp ; then
            ./a.out > $LOG2
        else
            print_err "Error compiling"
            test_fail "$1 $t"
            continue
        fi

        DIFF_FILE="$DIFFS/$1/"$t"_diff.txt"
        diff -u $LOG1 $LOG2 > $DIFF_FILE
        RESULT=$(cat $DIFF_FILE)

        if [[ ${#RESULT} > 0 ]] ; then
            test_fail "$1 $t"
            print_err "Check $DIFF_FILE for $t diffs with std"
        else
            test_success "$1 $t"
            rm -rf $DIFF_FILE
        fi
    done
}

test_typedefs() {
    mkdir -p $OBJ/$1

    if $CC $FLAGS $LEAK_FLAG -c $TEST_DIR/$1/typedefs.cpp -o $OBJ/$1/typedefs.o; then
        test_success "$1 typedefs"
    else
        print_err "Error compiling"
        test_fail "$1 typedefs"
        continue
    fi
}

test_vector() {
    test_typedefs "vector"
    test_suite "vector" "types ctor ctor_copy ctor_size ctor_range assignment assign assign_range at index_op front back push_back reserve resize swap pop_back max_size empty get_allocator data iterator insert insert_size insert_range clear erase erase_range comparisons"
}

test_stack() {
    test_typedefs "stack"
    test_suite "stack" "types misc comparisons"
}

test_provided() {
    NAME="provided"
    mkdir -p $LOGS/$NAME
    mkdir -p $DIFFS/$NAME

    LOG1=$LOGS/$NAME/"$NAME"_"$LOG_FT"
    LOG2=$LOGS/$NAME/"$NAME"_"$LOG_STD"

    if $CC $FLAGS $LEAK_FLAG $TEST_DIR/$NAME.cpp ; then
        ./a.out > $LOG1
    else
        print_err "Error compiling"
        test_fail "$NAME"
        continue
    fi

    if $CC $FLAGS $LEAK_FLAG -DUSE_STD $TEST_DIR/$NAME.cpp ; then
        ./a.out > $LOG2
    else
        print_err "Error compiling"
        test_fail "$NAME"
        continue
    fi

    DIFF_FILE="$DIFFS/$NAME/"$NAME"_diff.txt"
    diff -u $LOG1 $LOG2 > $DIFF_FILE
    RESULT=$(cat $DIFF_FILE)

    if [[ ${#RESULT} > 0 ]] ; then
        test_fail "$NAME"
        print_err "Check $DIFF_FILE for $NAME diffs with std"
    else
        test_success "$NAME"
        rm -rf $DIFF_FILE
    fi
}

test_vector
rm -rf a.out
