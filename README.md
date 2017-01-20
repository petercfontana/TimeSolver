# pes.timed

June 19, 2009

Written by Peter Fontana (pfontana@cs.umd.edu).

## Contents

* [Brief Program Description][]
* [Installing/Compiling][]
* [Running the Program][]
* [Generating Examples][]
* [Notes][]

## Brief Program Description

This program is a Model Checker for timed automata that uses pes (predicate equation systems).

## Installing/Compiling

To install, simply run "make".

Running make clean will remove the files generated by compiling.

### Needed Libraries

No additional libraries are needed.

## Running the Program

The executable program is named "demo" 

To run, use ./demo <exampleFile>

Example files are included in the "example" directory (most are also inside another directory in the "example" directory.

To make the examples, see the section "Generating Examples"

Running "./build_all.sh" will compile the program and the example-generating programs.

## Generating Examples

Most examples are already there.  Some are program-generated.  To compile the programs to generate examples, either run "make" in each directory (with the desired makefile), or in the regular directory run "./build_all.sh"  This will compile the original program and the example-generating programs.

Then, run each program and provide as a parameter the number of processes.  This will then write to standard output the generated example.  It is recommended to redirect the output to a file.

Some folders will have various examples.

## Notes

No additional Notes.