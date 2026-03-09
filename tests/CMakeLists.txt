include(FetchContent)

FetchContent_Declare(
    gtest 
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG v1.17.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

enable_testing()

add_executable(tests 
    test_core.cpp
)
target_link_libraries(tests
    PRIVATE 
        ${PROJECT_NAME}_interface 
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)