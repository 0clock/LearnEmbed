#!/bin/bash

var=hello

echo $var world
echo '$var world'
echo "$var world"

read a
read -p "a \ b \ c" a b c
echo $a $b $c 
#read -n 3 d
read -s e
echo $e
read -t 10 f
echo $f


