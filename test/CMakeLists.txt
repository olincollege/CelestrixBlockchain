set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-conversion")

list(APPEND CMAKE_CTEST_ARGUMENTS --verbose)

# Homebrew on Apple Silicon puts headers and libraries into /opt/homebrew
# instead of /usr, so make sure that the Criterion libraries can be found on
# those machines.
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin"
        AND CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "arm64")
    include_directories(BEFORE SYSTEM "/opt/homebrew/include")
    link_directories(BEFORE "/opt/homebrew/lib")
endif()


# Tests

add_executable(test_transaction test_transaction.cpp)
target_link_libraries(test_transaction
    PRIVATE Transaction
    PUBLIC ${CRITERION}
)
add_test(
    NAME test_transaction
    COMMAND test_transaction ${CRITERION_FLAGS}
)
