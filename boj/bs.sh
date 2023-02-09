#!/bin/bash

template="../t.cpp"
name=${1/.xpp}.xpp
funcs=${1/.xpp}.fpp
file="${name/.xpp}_xpp.cpp"
echo "compiling $name"
sed "18 r $name" $template > $file
sed -i "14 r $funcs" $file
compile $file
