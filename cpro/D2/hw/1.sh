#!/bin/bash

user=`whoami`
passwd=`grep ^$user /etc/passwd `
uid=${passwd:8:4}
gid=${passwd:13:4}

a=([0]=$user [1]=$SHELL [2]=$uid [3]=$gid)

echo ${a[*]}

