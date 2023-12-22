#!/bin/bash

a=hello
b1=$a world
echo b1=$b1
b2=$aworld
echo b2=$b2
b3=${a}world
echo b3=$b3
b4=world$a
echo b4=$b4
c='$a world'
echo c=$c
d="$a world"
echo d=$d
