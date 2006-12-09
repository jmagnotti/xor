#!/bin/bash

# generates the main include file for XOR

# NOTE: currently does not account for exceptions such as demos (which
# shouldn't be included) and transitions or SDL textures (which don't work)
# -- such lines must be manually removed from the resulting file

# destination filename
H_FILE=xor.h

# delete old file
rm -f $H_FILE

echo "#ifndef XOR_H" > $H_FILE
echo "#define XOR_H" >> $H_FILE

# find all .h files
for i in `find . -name "*.h" | sed -e 's/\.\///'`
do
	# don't add a recursive include
	if [ $i != $H_FILE ]; then
		echo "#include \"$i\"" >> $H_FILE
	fi
done

echo "#endif" >> $H_FILE

