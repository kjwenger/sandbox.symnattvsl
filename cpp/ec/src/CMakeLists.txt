cmake_minimum_required(VERSION 3.9)
if (NOT DEFINED CMAKE_PREFIX_PATH)
    set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../staging)
endif (NOT DEFINED CMAKE_PREFIX_PATH)
if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif(UNIX)
file(GLOB_RECURSE INC
        ../../inc/*.hpp
        ../inc/*.hpp
)
file(GLOB_RECURSE SRC
        ../../src/*.cpp
        ./*.cpp
)
add_executable(ec
        ${INC}
        ${SRC}
)
target_include_directories(ec PUBLIC
        ../../inc
        ../inc
        ${CMAKE_PREFIX_PATH}/include
)
target_link_libraries(ec
        ${CMAKE_PREFIX_PATH}/lib/libcppsocket.so
)
find_package(Doxygen
        REQUIRED dot
        OPTIONAL_COMPONENTS mscgen dia
)
doxygen_add_docs(doxygen.ec
        ./
        ./inc
)
