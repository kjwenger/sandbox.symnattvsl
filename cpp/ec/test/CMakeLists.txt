cmake_minimum_required(VERSION 3.7)
if (NOT DEFINED CMAKE_PREFIX_PATH)
    set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../staging)
endif (NOT DEFINED CMAKE_PREFIX_PATH)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})
file(GLOB_RECURSE SRC
        ./*.cpp
)
add_executable(test.ec
        ${SRC}
)
target_link_libraries(test.ec
        ${CMAKE_THREAD_LIBS_INIT}
        ${GTEST_LIBRARY}
        ${GTEST_MAIN_LIBRARY}
)
add_test(
        NAME cppcheck.ec
        COMMAND cppcheck ${SRC}
)
add_test(
        NAME test.ec
        COMMAND test.ec
)
