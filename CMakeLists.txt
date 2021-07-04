cmake_minimum_required(VERSION 3.2)

IF(DEFINED ENV{GITHUB_RUN_NUMBER})
    project(bulk VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})
ELSE()
    project(bulk)
ENDIF()

add_executable(bulk_cli main.cpp)

set_target_properties(bulk_cli PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(bulk_cli
    PRIVATE "${CMAKE_BINARY_DIR}"
)

if (MSVC)
    target_compile_options(bulk_cli PRIVATE
        /W4
    )
else ()
    target_compile_options(bulk_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()


install(TARGETS bulk_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
