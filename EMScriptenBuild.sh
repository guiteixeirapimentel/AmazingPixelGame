#!/bin/bash
echo "Build Started"

readarray -td '' list < <(find . -type f -name "*.cpp" -print0)

# disables assert
defines="-DNDEBUG=1"

echo "${list[@]}"

all_files=''
i="0"
for ((; $i<${#list[@]}; i++)); do
    all_files+="${list[$i]} "
done


# emscripten pathing
emscDir='/./home/guilherme/emscripten/emsdk/upstream/emscripten/em++'

# cpp files
cppFiles=$all_files #"./main.cpp ./Character.cpp"

# output file
outputFile="index.html"

# command construction
cmd="$emscDir -O3 $cppFiles -o $outputFile -s ASYNCIFY $defines" 

# command calling
$cmd

echo "Build finished!"
