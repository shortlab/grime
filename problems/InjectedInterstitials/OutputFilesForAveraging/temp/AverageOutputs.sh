#!/bin/bash

## This script reads in SRIM output files, and averages their
##output values. It is used when many, many SRIM simulations are desired,
## and each only runs a few ions, but with a different random seed.

function usage
{
    echo "usage: ./AverageOutputs <options>"
    echo "    -p (string)     --prefix (string)      Output filename prefix"
    echo "    -h       --help          Show this usage statement"
}

## Get the filename prefix from the user

FilePrefix=""

while [ "$1" != "" ]; do
    case $1 in
        -p | --prefix )         shift
                                FilePrefix=$1
                                ;;
        -h | --help )           usage
                                exit
                                ;;
        * )                     usage
                                exit 1
    esac
    shift
done

## Go through each .TXT file that matches the user's specified prefix.
## Trim it to the last 100 lines (the actual output). Then read in each
## line, split it into space-separated terms, and keep a running
## average. This effectively keeps a 100xN matrix in memory,
## containing averaged output values aat each distance. Only read the first
## column once, as all files contain identical depth information.

Filename=

## Define variables Data1 through Data100, to hold running totals of
## whatever we are averaging

    for i in {1..100}
    do
      declare Data$i=0
    done

FileNumber=0

for Filename in "$FilePrefix"*.TXT; do

    echo "Opening "$Filename" for averaging"

## Use 'tail' to trim each file to the last 100 lines

    tail -n 102 $Filename > temp.txt

## Trim the last three lines if this is a VACANCY file

    if [ "$FilePrefix" == "VACANCY" ]; then
        head -n 100 temp.txt > data.txt
    elif [ "$FilePrefix" == "RANGE" ]; then
        tail -n 100 temp.txt > data.txt
    fi

## Open each file line-by-line

    i=1

    while read line; do
        IFS='  ' read -a splitline <<< "$line"
#        split(line, splitline, " ")
#        echo ${splitline[2]}


## Replce the 'E' in all numbers with a (*10**) for bc -le
        D1=$(echo "${splitline[1]})" | sed -r 's/E/*10\^\(/g' | sed -r 's/\+//g')
        D2=$(echo "${splitline[2]})" | sed -r 's/E/*10\^\(/g' | sed -r 's/\+//g')
        var="Data$i"
            if [ "$FilePrefix" == "VACANCY" ]; then
#                echo "(("${!var}" * "$FileNumber" + "$D1" + "$D2") / ($FileNumber + 1))"
#                echo "(("${!var}" * "$FileNumber" + "$D1" + "$D2") / ($FileNumber + 1))" | bc -l
                declare "Data$i"="$(echo "(${!var} * $FileNumber + $D1 + $D2) / ($FileNumber + 1)" | bc -l)"
            elif [ "$FilePrefix" == "RANGE" ]; then
                ${!var}=$((echo "("${!var}"' * "$FileNumber" + "${splitline[1]}"/10000000)")) # Convert from cm to nm
            fi
       i=$((i+1))

    done < data.txt

## End the for loop

    FileNumber=$((FileNumber+1))

done

## Finally, write out the distance vs. quantity information as a comma separated file.
## Read the distance data (in Angstroms) from the original data.txt file.

rm $FilePrefix-Averaged.csv
i=1
    while read line; do
        IFS='  ' read -a splitline <<< "$line"
        var="Data$i"
        Distance=$(echo "${splitline[0]})" | sed -r 's/E/*10\^\(/g' | sed -r 's/\+//g')
        Distance="$(echo "${Distance} / 10" | bc -l)"
        echo "$Distance ${!var}" >> $FilePrefix-Averaged.csv
        i=$((i+1))
    done < data.txt
