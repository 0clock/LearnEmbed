#!/bin/bash

read -p "请输入三个数：" a b c
max=$a
if (( max<b ))
then
	max=$b
fi

if (( max<c ))
then
	max=$c
fi

echo max=$max
