#!/bin/bash

read -p "请输入天数："  day

week=$[day/7]
day=$[day%7]

echo $week周$day天

echo