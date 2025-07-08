cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()

project(MARKET_SIM VERSION 0.1
        DESCRIPTION "Order book simulation"
        LANGUAGES CXX)

# googletest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


file(GLOB_RECURSE SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
list(REMOVE_ITEM SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
file(GLOB_RECURSE TEST_SRC "test/*.cpp")
set(MAIN "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
set(BENCH_ORDER_BOOK "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/benchmark_order_book.cpp")

add_executable(sim ${MAIN} ${SRC})
add_executable(run_test ${TEST_SRC} ${SRC})
add_executable(benchmark_order_book ${BENCH_ORDER_BOOK} ${SRC})


target_include_directories(sim PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(run_test PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include" "${gtest_SOURCE_DIR}/googletest/include")
target_include_directories(benchmark_order_book PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(run_test PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(run_test)