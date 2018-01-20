cmake_minimum_required(VERSION 3.7)
if (NOT DEFINED CMAKE_PREFIX_PATH)
    set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../staging)
endif (NOT DEFINED CMAKE_PREFIX_PATH)
set(CMAKE_INSTALL_PREFIX ${CMAKE_PREFIX_PATH})
set(CONFIGURE_ARGS
        --prefix=${CMAKE_PREFIX_PATH}
)
include(ExternalProject)
ExternalProject_Add(
        pjsip
        SVN_REPOSITORY http://svn.pjsip.org/repos/pjproject/trunk
        CONFIGURE_COMMAND ./configure ${CONFIGURE_ARGS}
        INSTALL_DIR ${CMAKE_INSTALL_PREFIX}
        BUILD_IN_SOURCE 1
        BUILD_COMMAND make dep && make clean && make -j
)
