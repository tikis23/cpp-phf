cmake_minimum_required(VERSION 3.24)
project(phftest)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(${PROJECT_NAME} ${SRC_FILES})

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU") # TODO: add MSVC support
    target_compile_options(${PROJECT_NAME} PRIVATE -fconstexpr-ops-limit=2000000000)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ../phf/include)

add_subdirectory(thirdparty/googletest)
target_link_libraries(${PROJECT_NAME} GTest::gtest_main)
target_include_directories(${PROJECT_NAME} PRIVATE thirdparty/googletest/googlemock/include)
target_include_directories(${PROJECT_NAME} PRIVATE thirdparty/googletest/googletest/include)