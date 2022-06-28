#!/bin/bash

RED="\033[31;1m"
YELLOW="\033[93;1m"
GREEN="\033[32;1m"
BLUE="\033[34;1m"
END="\033[0m"

# Create variables
cppdir="tests"
objdir="obj"
outdir="tests/output"
diffdir="tests/diff"
logdir="tests/log"
incdir="includes/"
errlog="error.log"
flags='-Wall -Werror -Wextra -std=c++98 -Iincludes/ -Iincludes/RBTRee/ -Iincludes/Iterator/'
container="$PWD/$1"

# Remove the old dir
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

print_output()
{
    b=$(echo $b | tr 'a-z' 'A-Z')
    if [ -f "$outdir/ft_$b.out" ]; then
        if [ -s "$diffdir/ft_$b.diff" ]; then
            printf "$RED======TEST FAILED======= $b$END\n"
            printf "(Check tests/output/diff.out for more info)\n";
        else
            printf "$GREEN======TEST SUCCESS====== $b$END\n";
        fi
    else
        printf "$RED=========ERROR========== $b$END\n"
        printf "(Check err.log for more info)\n";
    fi
}

# Compile 2 binaries and compare the output
compare_output()
{
    b=$(basename "${f%.cpp}")
    printf '%s\n' "$b" >> "$errlog"
    clang++ "$f" $flags -DNAMESPACE=ft -o "$outdir/ft_$b.out" 2>> "$errlog"
    clang++ "$f" $flags -DNAMESPACE=std -o "$outdir/std_$b.out" 2>> "$errlog"
    ./"$outdir/ft_$b.out" > "$logdir/ft_$b" 2>> "$errlog"
    ./"$outdir/std_$b.out" > "$logdir/std_$b" 2>> "$errlog"
    diff -u "$logdir/ft_$b" "$logdir/std_$b" > "$diffdir/ft_$b.diff"
}

printf "\n"
if [ "$#" -ne 1 ]; then
    for f in "$cppdir"/*.cpp; do
        compare_output
        print_output
    done
else
    f="$cppdir"/"$(basename $container)".cpp
    compare_output
    print_output
fi
printf "\n"
