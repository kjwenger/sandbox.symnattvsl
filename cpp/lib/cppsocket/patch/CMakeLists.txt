cmake_minimum_required(VERSION 3.9)
project(cppsocket)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
if (NOT DEFINED CMAKE_PREFIX_PATH)
    set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/staging)
endif (NOT DEFINED CMAKE_PREFIX_PATH)
file(GLOB INC LIST_DIRECTORIES false
        ./*.hpp
)
file(GLOB SRC LIST_DIRECTORIES false
        ./*.cpp
)
add_library(cppsocket SHARED
        ${INC}
        ${SRC}
)
target_include_directories(cppsocket PUBLIC
        ./
)
install(TARGETS cppsocket
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static
)
install(FILES
        ${INC}
        DESTINATION include
)