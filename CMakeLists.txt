cmake_minimum_required(VERSION 3.16)
project(codemasterspandas VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(codemasterspandas
    src/value.cpp
    src/series.cpp
    src/dataframe.cpp
    src/io.cpp
    src/statistics.cpp
    src/transform.cpp
)
target_include_directories(codemasterspandas PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_compile_features(codemasterspandas PUBLIC cxx_std_17)
install(TARGETS codemasterspandas
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
install(DIRECTORY include/ DESTINATION include)
if(MSVC)
    target_compile_options(codemasterspandas PRIVATE /W4)
else()
    target_compile_options(codemasterspandas PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_subdirectory(examples)

include(CTest)

if(BUILD_TESTING)

    # Test 1: Main library functionality
    add_executable(library_tests
        tests/test_library.cpp
    )

    target_link_libraries(library_tests
        PRIVATE codemasterspandas
    )

    add_test(
        NAME library_tests
        COMMAND library_tests
    )


    # Test 2: Edge cases
    add_executable(edge_case_tests
        tests/test_edge_cases.cpp
    )

    target_link_libraries(edge_case_tests
        PRIVATE codemasterspandas
    )

    add_test(
        NAME edge_case_tests
        COMMAND edge_case_tests
    )


    # Test 3: Data transformations
    add_executable(transform_tests
        tests/test_transform.cpp
    )

    target_link_libraries(transform_tests
        PRIVATE codemasterspandas
    )

    add_test(
        NAME transform_tests
        COMMAND transform_tests
    )

endif()