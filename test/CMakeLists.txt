project(ClassTests)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(ClassTests
        SharedPtrTest.cpp
        UniquePtrTest.cpp)

target_link_libraries(ClassTests PRIVATE
        GTest::gtest_main
        GTest::gmock_main)

target_include_directories(ClassTests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../src)

include(GoogleTest)
gtest_discover_tests(ClassTests)

add_test(NAME ClassTests
        COMMAND ClassTests
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/test)
