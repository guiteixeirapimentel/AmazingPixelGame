#!/bin/bash
clear
echo "Build Started"

compilingFlags="-lSDL"

defines=""

readarray -td '' list < <(find . -type f -name "*.cpp" -print0)

echo "${list[@]}"

all_files=''
i="0"
for ((; $i<${#list[@]}; i++)); do
    all_files+="${list[$i]} "
done


# emscripten pathing
# emscDir='/./home/guilherme/emscripten/emsdk/upstream/emscripten/em++'

# cpp files
cppFiles=$all_files

# output file
outputFile="game"

# command construction
cmd="g++ $cppFiles -g -o $outputFile $compilingFlags $defines" 

# command calling
$cmd

echo "Build finished!"

./game
