cmake_minimum_required(VERSION 3.18)

project(pikiwidb-folly
        DESCRIPTION "Part of folly library which pikiwidb depends on"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE FOLLY_SRC ${PROJECT_SOURCE_DIR}/folly/*.cpp)
add_compile_definitions(FOLLY_NO_CONFIG)

add_library(pikiwidb-folly OBJECT ${FOLLY_SRC})
target_include_directories(pikiwidb-folly INTERFACE .)

find_package(glog)
find_package(double-conversion)
find_package(fmt)

if(NOT glog_FOUND OR NOT double-conversion_FOUND OR NOT fmt_FOUND)
  message(FATAL_ERROR "dependencies not meet")
endif()

target_link_libraries (pikiwidb-folly glog double-conversion fmt)
