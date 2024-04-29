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
    PRIVATE Blockchain
    PUBLIC ${CRITERION}
)
add_test(
    NAME test_transaction
    COMMAND test_transaction ${CRITERION_FLAGS}
)

add_executable(test_blockchain test_blockchain.cpp)
target_link_libraries(test_blockchain
    PRIVATE Blockchain
    PUBLIC ${CRITERION}
)
add_test(
    NAME test_blockchain
    COMMAND test_blockchain ${CRITERION_FLAGS}
)


add_executable(test_block test_block.cpp)
target_link_libraries(test_block
    PRIVATE Blockchain
    PUBLIC ${CRITERION}
)
add_test(
    NAME test_block
    COMMAND test_block ${CRITERION_FLAGS}
_)

add_executable(test_sha256 test_sha256.cpp)
target_link_libraries(test_sha256
    PRIVATE Blockchain
    PUBLIC ${CRITERION}
)
add_test(
    NAME test_sha256
    COMMAND test_sha256 ${CRITERION_FLAGS}
_)
