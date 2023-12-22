#!/bin/bash

 grep "^linus" /etc/group | cut -d ':' -f 3
