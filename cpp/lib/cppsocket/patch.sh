#!/usr/bin/env bash

#set -x

case "$(uname -s)" in
   Darwin)
     find ${1} -name '*.cpp' -print | xargs sed -i '' 's/std::cout/std::cerr/g'
     ;;
   *)
     find ${1} -name '*.cpp' -exec sed -i 's/std::cout/std::cerr/g' {} \;
     ;;
esac