#!/usr/bin/env bash

gcc -c ./src/countword.c 
gcc -o ./countword ./src/countword.c


gcc -c ./src/median.c 
gcc -o ./median ./src/median.c


./countword

./median

