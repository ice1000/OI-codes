#!/bin/bash
time=`echo $1 | cut -d "." -f1`
echo `expr $time / 2`

