#!/bin/bash 
a=("oneko bass frozen-bubble")
select varname in ${a[*]}
var=$varname
do
    case $varname in
    oneko )
        if [ -e $var ]
        then
            echo 存在文件，执行
            `$var`
        else
            echo 运行失败，进行下载
          sudo apt install $var
          `$var`
        fi  
        ;;  
    bass )
        if [ -e $var ]
        then                                    
            echo 存在文件，执行
            `$var`
        else
            echo 运行失败，进行下载
          sudo apt install $var
          `$var`
        fi
        ;;
    frozen-bubble )
		if [ -e $var ]
        then
            echo 存在文件，执行
            `$var`
        else
            echo 运行失败，进行下载
          sudo apt install $var
          `$var`
        fi
        ;;
    *)
        ;;
esac
done
