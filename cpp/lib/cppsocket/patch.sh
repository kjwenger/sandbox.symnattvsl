#!/usr/bin/env bash

set -x

find ${1} -name '*.cpp' -exec sed -i 's/std::cout/std::cerr/g' {} \;

# | \
#xargs | \
#echo