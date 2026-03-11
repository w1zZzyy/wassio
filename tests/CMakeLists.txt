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

option(ENABLE_SANITIZERS "Enable ASan + UBSan" ON)
if(ENABLE_SANITIZERS)
    target_compile_options(tests PRIVATE
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
        -g
    )
    target_link_options(tests PRIVATE
        -fsanitize=address,undefined
    )
endif()

include(GoogleTest)
gtest_discover_tests(tests)