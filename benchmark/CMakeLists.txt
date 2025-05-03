cmake_minimum_required(VERSION 3.24)
project(phfbench)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(${PROJECT_NAME} ${SRC_FILES})

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU") # TODO: add MSVC support
    target_compile_options(${PROJECT_NAME} PRIVATE -fconstexpr-ops-limit=2000000000)
endif()

# phf
target_include_directories(${PROJECT_NAME} PRIVATE ../phf/include)

# google benchmark
add_subdirectory(thirdparty/benchmark)
target_link_libraries(${PROJECT_NAME} benchmark::benchmark_main)
target_include_directories(${PROJECT_NAME} PRIVATE thirdparty/benchmark/include)

# frozen
target_include_directories(${PROJECT_NAME} PRIVATE thirdparty/frozen/include)