#!/bin/bash

RED="\033[31;1m"
YELLOW="\033[93;1m"
GREEN="\033[32;1m"
BLUE="\033[34;1m"
END="\033[0m"

cppdir="tests"
objdir="obj"
outdir="tests/output"
diffdir="tests/diff"
logdir="tests/log"
incdir="includes/"
errlog="error.log"
flags='-Wall -Werror -Wextra -std=c++98'
container="$PWD/$1"

if [ -d "$outdir" ]; then
    rm -rf $outdir
fi
if [ -d "$diffdir" ]; then
    rm -rf $diffdir
fi
if [ -d "$logdir" ]; then
    rm -rf $logdir
fi
if [ -f "$errlog" ]; then
    rm $errlog
fi

mkdir -p "$outdir"
mkdir -p "$diffdir"
mkdir -p "$logdir"

test_fail()
{
    printf "$RED======TEST FAILED======= $b$END\n"
    printf "(Check tests/output/diff.out for more info)\n";
}

test_success()
{
    printf "$GREEN======TEST SUCCESS====== $b$END\n";
}

print_output()
{
    RESULT=$(cat "$diffdir/ft_$b.diff")

    if [[ ${#RESULT} > 0 ]] ; then
        test_fail
    else
        test_success
    fi
}

compile_tests()
{
    b=$(basename "${f%.cpp}")
    printf '%s\n' "$b" >> "$errlog"
    clang++ "$f" $flags -DNAMESPACE=ft -o "$outdir/ft_$b.out" 2>> "$errlog"
    clang++ "$f" $flags -DNAMESPACE=std -o "$outdir/std_$b.out" 2>> "$errlog"
}


compare_output()
{
	printf "$BLUE********   FT_$b BENCHMARK   ********$END\n"
    time -p bash -c "for ((i = 0; i < 2000; ++i)); do ./"$outdir/ft_$b.out" > "$logdir/ft_$b"; done;"
	printf "$YELLOW********   STD_$b BENCHMARK   ********$END\n"
    time -p bash -c "for ((i = 0; i < 2000; ++i)); do ./"$outdir/std_$b.out" > "$logdir/ft_$b"; done;"
}

printf "\n"
if [ "$#" -ne 1 ]; then
    for f in "$cppdir"/*.cpp; do
        compile_tests
        compare_output
    done
else
    f="$cppdir"/"$(basename $container)".cpp
    compile_tests
    compare_output
fi
