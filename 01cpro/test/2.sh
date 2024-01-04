#!/bin/bash

read a b
if [ $a -eq $b ]
then
	echo =
elif [ $a -lt $b ]
then
	echo \<
elif [ $a -gt $b ]
then
	echo \>
fi

