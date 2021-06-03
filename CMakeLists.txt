cmake_minimum_required(VERSION 3.2)

project(graphicalEditor VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_library(graphicalEditor main.cpp)

target_include_directories(graphicalEditor
    PRIVATE "${CMAKE_BINARY_DIR}"
)

if (MSVC)
    target_compile_options(graphicalEditor PRIVATE
        /W4
    )
else ()
    target_compile_options(graphicalEditor PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()


