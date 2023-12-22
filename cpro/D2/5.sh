#!/bin/bash

#1.使用readonly修饰
readonly var=hello
echo $var

a=123
unset a
echo a=$a
unset var
echo var=$var

function one(){
	b=100
	local c=200
}

one
echo b=$b
echo c=$c


