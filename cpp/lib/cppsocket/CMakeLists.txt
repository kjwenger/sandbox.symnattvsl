cmake_minimum_required(VERSION 3.7)
if (NOT DEFINED CMAKE_PREFIX_PATH)
    set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../staging)
endif (NOT DEFINED CMAKE_PREFIX_PATH)
set(CMAKE_INSTALL_PREFIX ${CMAKE_PREFIX_PATH})
set(CMAKE_ARGS
        -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
        -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
)
include(ExternalProject)
ExternalProject_Add(
        cppsocket
        GIT_REPOSITORY https://github.com/elnormous/cppsocket.git
        PATCH_COMMAND cp -v ${CMAKE_CURRENT_SOURCE_DIR}/patch/CMakeLists.txt <SOURCE_DIR>
        CMAKE_ARGS ${CMAKE_ARGS}
        INSTALL_DIR ${CMAKE_INSTALL_PREFIX}
)
