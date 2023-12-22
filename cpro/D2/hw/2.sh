#!/bin/bash

read -p "请输入一个字符串："  a

echo 最后一个字符是：${a:0-1}
