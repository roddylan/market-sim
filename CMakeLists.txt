cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(MARKET_SIM VERSION 0.1
        DESCRIPTION "Order book simulation"
        LANGUAGES CXX)


file(GLOB_RECURSE SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
list(REMOVE_ITEM SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
file(GLOB_RECURSE TEST_SRC "test/*.cpp")

add_executable(sim ${SRC})
add_executable(test ${TEST_SRC} ${SRC})


target_include_directories(sim PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(test PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

