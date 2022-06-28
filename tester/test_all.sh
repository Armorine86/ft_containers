#!/bin/bash

RED="\033[31;1m"
GREEN="\033[32;1m"
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
    printf "$RED-----> $b: 🚫$END\n"
    printf "(Check tests/output/diff.out for more info)\n";
}

test_success()
{
    printf "$GREEN-----> $b: ✅$END\n";
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
    ./"$outdir/ft_$b.out" > "$logdir/ft_$b" 2>> "$errlog"
    ./"$outdir/std_$b.out" > "$logdir/std_$b" 2>> "$errlog"
    diff -u "$logdir/ft_$b" "$logdir/std_$b" > "$diffdir/ft_$b.diff"
}

printf "\n"
if [ "$#" -ne 1 ]; then
    for f in "$cppdir"/*.cpp; do
        compile_tests
        compare_output
        print_output
    done
else
    f="$cppdir"/"$(basename $container)".cpp
    compile_tests
    compare_output
    print_output
fi
printf "\n"
