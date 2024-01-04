#!/bin/bash

a=100
b=200

echo a=$a b=$b

temp=$a
a=$b;
b=$temp

echo a=$a b=$b
