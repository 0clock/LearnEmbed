#!/bin/bash

#逻辑或
a=0
b=hello
value=`expr $a \| $b`
echo value=$value

a=0
b=0
value=`expr $a \| $b`
echo value=$value

a=hello
b=world
value=`expr $a \| $b`
echo value=$value

a=hello
b=0
value=`expr $a \| $b`
echo value=$value

#逻辑与
a=0
b=hello
value=`expr $a \& $b`
echo value=$value

a=0
b=0
value=`expr $a \& $b`
echo value=$value

a=hello
b=world
value=`expr $a \& $b`
echo value=$value

a=hello
b=0
value=`expr $a \& $b`
echo value=$value

