cmake_minimum_required(VERSION 3.18)

project(pikiwidb-folly
        DESCRIPTION "Part of folly library which pikiwidb depends on"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

aux_source_directory(. FOLLY_SRC)
add_compile_definitions(FOLLY_NO_CONFIG)

add_library(pikiwidb-folly ${FOLLY_SRC})
