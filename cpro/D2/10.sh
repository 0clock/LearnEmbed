#!/bin/bash

read -a arr

echo len=${#arr[*]}

a=(`ls ./`)
echo lscount=${#a[*]}

c=($*)
echo inputslen=${#c[*]}
