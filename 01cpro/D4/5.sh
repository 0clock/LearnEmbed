#!/bin/bash

read -p "请输入两个字符串：" a b

echo a=$a,b=$b

if [ -z "$a" -o -z "$b" ]
then
	echo NULL
else
	if [ $a = $b ]
	then
		echo "="
	elif [ "$a" > "$b" ]
		echo ">"
	elif [ "$a" < "$b" ]
		echo "<"
	fi
fi
