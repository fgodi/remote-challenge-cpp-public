# C++ Remote Challenge

This repository contains the basic set up for the C++ remote challenge. It contains necessary boilerplate code and needs at least C++11 to compile. You are nonetheless encouraged to use the latest C++ standard. The challenge itself and the test cases are not included and will be given separately. You are free to use any IDE and compiler, although the latter should support at least C++11. In the following, it is explained how to run the code with g++ and make.

## Prerequisites

* GIT: [Download](https://git-scm.com/downloads)
* g++/make: [Instructions for different OS](https://www.cs.odu.edu/~zeil/cs250PreTest/latest/Public/installingACompiler/)

## Build

Firstly, clone this repository and then move into its folder. A makefile is provided, supporting both ```make debug``` and ```make release```. Before going on to the next step, do ```make debug```.

## Run

This step verifies whether everything is ready for the challenge. Call the program with the arguments ```./input/test_case_0-0.json``` and ```./first_test.json``` in this order, e.g. if  you followed the instructions above, your command would be ```./bin/challenge-debug ./input/test_case_0-0.json ./first_test.json```. This should create a file *first_test.json*, which is identical to *test_case_0-0.json*. You can use [this diffchecker](https://www.diffchecker.com/) to verify that.

## Visualisation

This chapter is not necessary, but might be helpful. In the repository, you can additionally find a small python script which you can use to visualize all JSONs involved in the challenge. For this to work, you need [Python 3](https://www.python.org/downloads/). You can then call the script with ```python3 mini_viz.py ./input/test_case_0-0.json```. It creates a picture in the same folder where the original file was.

## Final notes

If something failed along the way und you cannot fix it on your own, reach out to us. If everything worked out, good luck solving the challenge which was provided to you!
