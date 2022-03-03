#!/bin/bash

fileOne=${1}
fileTwo=${2}
numLines=${3:-"1"}

diff <(xxd ${fileOne} | head -n ${numLines}) <(xxd ${fileTwo} | head -n ${numLines})
