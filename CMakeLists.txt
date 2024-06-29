cmake_minimum_required(VERSION 3.10)

project("FibonacciHeap" LANGUAGES CXX)

file(GLOB SRC_FILES src/*.cpp)
add_executable(main ${SRC_FILES})

target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
