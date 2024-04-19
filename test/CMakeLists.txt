set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-conversion")

list(APPEND CMAKE_CTEST_ARGUMENTS --verbose)

add_executable(test_transaction test_transaction.cpp)
target_link_libraries(test_transaction
    PRIVATE Transaction
    PUBLIC ${CRITERION}

)
add_test(
    NAME test_transaction
    COMMAND test_transaction ${CRITERION_FLAGS}
)
