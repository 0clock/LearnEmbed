#!/bin/bash

a=hello
b=hello
c=Hel
d=hel
e=heL

value=`expr match $a $b`
echo value=$value

value=`expr match $a $c`
echo value=$value

value=`expr match $a $d`
echo value=$value

value=`expr match $a $e`
echo value=$value

#字符串截取
a=www.lingjun.life
value=`expr substr $a 5 7`
echo value=$value

#字符匹配

value=`expr index $a "l"`
echo value=$value

str="hello world"
len=${#str}
echo len=$len

len1=`expr length "$str"`
echo len1=$len1

