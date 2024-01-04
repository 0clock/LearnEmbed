#!/bin/bash

str=www.lingjun.life

a=${str:4}
b=${str:4:7}
c=${str:0-4}
d=${str:0-12:7}

echo $a
echo $b
echo $c
echo $d

a=${str#*.}
b=${str##*.}
c=${str%.*}
d=${str%%.*}


echo $a
echo $b
echo $c
echo $d

