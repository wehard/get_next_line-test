#!/bin/bash

BLACK="\033[30m"
GRAY="\033[1;30m"
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
	printf "$NORMAL%s $CYAN%s,$NORMAL %s!\n" "Hello" $(cat $GNLDIR/author) "good luck"
else
	printf "$RED%s\n" "Error: no author file"
fi

sleep 2

printf "$GRAY"

cp ./main.c $GNLDIR/.
cp ./compile.sh $GNLDIR/.
cd $GNLDIR
bash compile.sh

printf "\n$BLUE"

cd $TESTDIR
cp $GNLDIR/test_gnl .

# cleanup
rm -f $GNLDIR/test_gnl
rm -f $GNLDIR/main.c
rm -f $GNLDIR/main.o
rm -f $GNLDIR/get_next_line.o
rm -f $GNLDIR/compile.sh

# run test
./test_gnl test_null_cases.txt
LINES=$(./test_gnl test_null_cases.txt | grep "Lines" | cut -d ' ' -f 2)

printf "\nExpected: 16\n"

if [ $LINES -eq 16 ]; then
	printf "$GREEN%s\n" "[OK]"
else
	printf "$RED%s\n" "[FAIL]"
fi
