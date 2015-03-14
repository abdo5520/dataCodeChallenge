#!/usr/bin/env bash

gcc -c countword.c 
gcc -o countword countword.c


gcc -c median.c 
gcc -o median median.c


./countword

./median

