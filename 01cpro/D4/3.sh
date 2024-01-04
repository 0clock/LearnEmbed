#!/bin/bash 

read a b

if [ $a -gt $b ];then
	echo $a
else
	echo $b
fi

read c

if [ $((n%2)) -eq 0 ];then
	echo 是偶数
else
	echo 不是偶数
fi

read d

if [ $(((d/100)**3 + (d/10%10)**3 +(d%10)**3)) -eq $d ]
then 
	echo 是水仙花数
else
	echo 不是水仙花数
fi

