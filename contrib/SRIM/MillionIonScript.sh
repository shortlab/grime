#!/bin/bash

## This script runs SRIM many, many, many times (according to the user's wishes).
## This will generate many ions and distributions to be averaged. The reason this script
## was written is that SRIM does not automatically reseed random numbers. The goal of this
## script is to run SRIM many times, each with 10000 ions (and saving at that point), but
## with different random number seeds between 1 and 999,999,999. It then saves each file
## with its own unique identifier, averages their results, and saves them as one master
## output file.

function usage
{
    echo "usage: ./Million-Ion-Script <options>"
    echo "    -n #     --numsim #      Number of separate 10,000 ion simulations to run"
    echo "    -h       --help          Show this usage statement"
}


## First, define a file counter, which will be used to both track the number of simulations
## and to name each file.

FileCounter=1

## Take in the user's first argument as the number of simulations to run.

NumberOfSimulations=

while [ "$1" != "" ]; do
    case $1 in
        -n | --numsim )         shift
                                NumberOfSimulations=$1
                                ;;
        -h | --help )           usage
                                exit
                                ;;
        * )                     usage
                                exit 1
    esac
    shift
done

RandomSeed=

echo $NumberOfSimulations" simulations will be run."

## Set up a while loop. Each time, the code will create a new input file from TRIM-PROTO.IN,
## save it as TRIM-<#>.IN in InputFiles,
## also save it as TRIM.IN in this directory, run TRIM, and copy the output files VACANCY.TXT and RANGE.TXT
## to VACANCY-<#>.TXT and RANGE-<#>.txt in the OutputFilesForAveraging folder.

## Use 'i' as a counter to see when we've run enough simulations

i=1
while [ "$i" -le "$NumberOfSimulations" ]; do

    echo "Running simulation number "$NumberOfSimulations

## Generate a new random number seed for SRIM from /dev/urandom

    RandomSeed=$(od -vAn -N3 -tu4 < /dev/urandom)
    echo $RandomSeed
    RandomSeed=${RandomSeed// } #remove leading spaces

## Make input files named accordingly

    cp InputFiles/TRIM-PROTO.IN "TRIM-$RandomSeed.IN"

## Replace the <RAND> tag in that file with this random seed

    sed 's/<RAND>/'$RandomSeed'/' "TRIM-$RandomSeed.IN" > TRIM.IN
    rm "TRIM-"$RandomSeed".IN"

## Archive this input file

    cp TRIM.IN "InputFiles/TRIM-$RandomSeed.IN"

## Run TRIM using this input file

    wine TRIM.EXE

## Rename the output files accordingly

    cp VACANCY.txt "OutputFilesForAveraging/VACANCY-$RandomSeed.TXT"
    cp RANGE.txt "OutputFilesForAveraging/RANGE-$RandomSeed.TXT"
    rm *.txt

## Don't forget to increment the counter!

    i=$(($i + 1))

## End the while loop

done
