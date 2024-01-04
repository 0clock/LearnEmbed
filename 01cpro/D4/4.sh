#!/bin/bash

read -p "请输入成绩：" a

if [ $a -ge 90 -a $a -le 100 ];then
	echo A
elif [ $a -ge 60 -a $a -le 89 ];then
	echo B
elif [ $a -ge 0 -a $a -le 59 ];then
	echo C
fi

read -p "请输入年份：" b

if [ $((b/4)) -a $((b%100)) -eq 0 ] || [ $((b%400==0)) ];then
	echo 是闰年
else
	echo 不是闰年
fi
