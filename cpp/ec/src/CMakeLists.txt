cmake_minimum_required(VERSION 3.7)
if (NOT DEFINED CMAKE_PREFIX_PATH)
    set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../staging)
endif (NOT DEFINED CMAKE_PREFIX_PATH)
file(GLOB_RECURSE SRC
        ./*.cpp
)
add_executable(ec
        ${SRC}
)
