cmake_minimum_required(VERSION 3.7)
enable_testing()
find_package(Threads REQUIRED)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})
add_executable(test.pjsip
        src/test.pjsip.cpp
)
target_link_libraries(test.pjsip
        ${CMAKE_THREAD_LIBS_INIT}
        ${GTEST_LIBRARY}
        ${GTEST_MAIN_LIBRARY}
)
add_test(
        NAME test.pjsip
        COMMAND test.pjsip
)
