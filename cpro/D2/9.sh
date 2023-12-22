#!/bin/bash

a=(aa bb cc dd)
a[4]=eee

echo ${a[*]}
echo ${a[4]}



echo ${#a[*]}
echo ${#a[4]}
echo ${#a[@]}
