#!/bin/bash

i=0
for file in srcs/*.c
do
	d_prev[i]=$(stat -f %m $file)
	let "i+=1"
done

while [ 1 ]
do
	for file in srcs/*.c
	do
		i=0
		d[i]=$(stat -f %m $file)
		if [ "${d[i]}" -gt "${d_prev[i]}" ]
		then
			printf "compile\n"
			./compile.sh
			d_prev[i]=${d[i]}
		fi
		let "i+=1"
	done
	sleep 2
done
