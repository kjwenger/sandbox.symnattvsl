cmake_minimum_required(VERSION 3.7)
if (NOT DEFINED CMAKE_PREFIX_PATH)
    set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../staging)
endif (NOT DEFINED CMAKE_PREFIX_PATH)
enable_testing()
find_package(Threads REQUIRED)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})
file(GLOB_RECURSE SRC
        ./pjsip/*.cpp
)
add_executable(test.pjsip
        ${SRC}
)
target_link_libraries(test.pjsip
        ${CMAKE_THREAD_LIBS_INIT}
        ${GTEST_LIBRARY}
        ${GTEST_MAIN_LIBRARY}
)
add_test(
        NAME cppcheck.pjsip
        COMMAND cppcheck ${SRC}
)
add_test(
        NAME test.pjsip
        COMMAND test.pjsip
)
