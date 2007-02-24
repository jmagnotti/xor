#!/bin/bash

# simulates a video wall by starting multiple instances of the program
# with different position parameters

rows=3
cols=3
width=200
height=200

let "max_x = cols/2"
let "max_y = rows/2"

let "x=0"
for i in `seq -$max_x 1 $max_x`; do
	let "y=($cols-1)*height"
	for j in `seq -$max_y 1 $max_y`; do
		./WallDemo $i $j $width $height $x $y >/dev/null &
		sleep 1
		let "y=$y-$height"
	done
	let "x=$x+$width"
done

