Readme File for 2015 JNM Injected Interstitials Paper by M. P. Short et al.
 <a href="http://dx.doi.org/10.5281/zenodo.31640"><img src="https://zenodo.org/badge/doi/10.5281/zenodo.31640.svg" alt="10.5281/zenodo.31640"></a>
==============================================

A note to those who want to reproduce our results:

You will have to install MOOSE to compile this code directly. Follow the instructions at www.mooseframework.org before proceeding.

To run the cases exactly as done in the paper, use a simple shell script to vary one parameter at once, and automatically
rename the output file accordingly. Follow this example to, for instance, change the temperature of the simulation in Kelvin by increments of 25K:

## Go to the project directory
cd ~/grime/problems/InjectedInterstitials/200nA

## Generate a sequence of numbers from 573-823K in increments of 25, and feed them into the simulation, AND name the output files accordingly
seq 573 25 823 | awk '{print "../.././grime-dev-opt -i grime.i Materials/PureIron/ConstantTemperature="$1" Outputs/file-base=grime-II-"$1"K"}' | sh

## Do the same thing, but this time use the input file with injected interstitials turned off:
seq 573 25 823 | awk '{print "../.././grime-dev-opt -i grime-noII.i Materials/PureIron/ConstantTemperature="$1" Outputs/file-base=grime-noII-"$1"K"}' | sh

If you want to reproduce the vacancy activation energy study, just slightly modify the above scripts to replace instead the vacancy activation energy:

## Generate a sequence of numbers from 80-92, and feed them into the simulation after the decimal point for E_A_vacancy, AND name the output files accordingly
seq 80 92 | awk '{print "../.././grime-dev-opt -i grime.i Materials/PureIron/ConstantTemperature=0."$1" Outputs/file-base=grime-II-"$1"0meV}' | sh

## Generate a sequence of numbers from 80-92, and feed them into the simulation after the decimal point for E_A_vacancy, AND name the output files accordingly
seq 80 92 | awk '{print "../.././grime-dev-opt -i grime-noII.i Materials/PureIron/ConstantTemperature=0."$1" Outputs/file-base=grime-noII-"$1"0meV}' | sh

The only difference between the input files is a single line removing the secondary source of injected interstitials, artificially turning it off.
To confirm this, type:

diff grime.i grime-noII.i

Your output should look like this:

181d180
<     SecondarySource = InjectedInterstitials

The single line shows that the first file contains the secondary source of interstitials, while the second file does not. Nothing else varies, so you're running the same simulation with and without injected interstitials.

All intermediate files, in .csv and .gnumeric form, are included so readers can verify our intermediate data and graphs. They are untouched since creating the figures in the paper.
Finally, please note that the input files are set to automatically output the .csv files in the papers/ directory for easier post processing. The .e (Exodus) files contain this information too. The csv files were created by adding postprocessors to aid in data extraction.
