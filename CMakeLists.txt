cmake_minimum_required(VERSION 3.10)

project(stdlike LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_TESTING "Enable unit testing." OFF)

include_directories(3rdparty)

add_subdirectory(src)

if(${ENABLE_TESTING})
    enable_testing()
    add_subdirectory(test)
endif()