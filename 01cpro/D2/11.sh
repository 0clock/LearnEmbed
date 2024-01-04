#!/bin/bash

read a

fir=$(( a/100 ))

sec=$((a/10%10))

las=$((a%10))

isShuixianhua=$(((fir**3+sec**3+las**3)==a))

echo $isShuixianhua

#1h=60min
#1min=60s

read sec

hour=$((sec/3600))
min=$(((sec-hour*3600)/60))
sec=$((sec-hour*3600-min*60))

echo $hour小时$min分钟$sec秒


