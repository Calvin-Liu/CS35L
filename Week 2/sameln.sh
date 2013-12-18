#!/bin/bash

declare -a ARRAY
dir=$1
RESULT=`ls -a $dir | sort`
let count=0
let firstAdd=0
let onlyonce=0
let i=0

if [ $firstAdd == 0 ]				#purpose is to add the first file into the array
then
	for FILE in $RESULT
	do
		if [ -f "$dir/$FILE" ]
		then
			if [ $count == 0 ]
			then
				ARRAY[$count]="$dir/$FILE"
				let firstAdd=firstAdd+1
				let count=count+1
			fi
		fi
	done
fi

#set -x
for FILE in $RESULT
do
	if [ $onlyonce == 1 ] 
	then
		if [ -f "$dir/$FILE" ]    
		then
			echo "$dir/$FILE"
			for ((i=0; i!=$count; i++))     #loops through the array			
			do
				cmp "$dir/$FILE" "${ARRAY[$i]}"
				if [ $? == 0 ] 				  #if it is the same
				then
					rm "$dir/$FILE"
					ln ${ARRAY[$i]}	"$dir/$FILE"  #make hard link
					break 		#move to next input file
				fi
			done
			if [ $i == $count ]
			then
				ARRAY[$count]="$dir/$FILE"
				let count=count+1
			fi
		fi
	else
		if [ -f "$dir/$FILE" ]
		then
			let onlyonce=onlyonce+1
		fi
	fi
done
#set +x:
