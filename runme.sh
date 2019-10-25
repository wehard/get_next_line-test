#!/bin/bash

BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
PINK="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"
NORMAL="\033[0;39m"

if [[ $# -eq 0 ]] ; then
    printf "$RED%s$WHITE%s\n" "Error: " "Enter target directoy as argument"
    exit 1
fi

GNLDIR=$1
TESTDIR=$(pwd)

# Check author
if test -f "$GNLDIR/author"; then
	printf "$NORMAL%s $CYAN%s!\n$NORMAL" "Hello" $(cat $GNLDIR/author)
else
	printf "$RED%s\n" "Error: no author file"
fi

cp ./main.c $GNLDIR/.
cp ./compile.sh $GNLDIR/.
cd $GNLDIR
bash compile.sh
cd $TESTDIR
cp $GNLDIR/test_gnl .
./test_gnl test_null_cases.txt
