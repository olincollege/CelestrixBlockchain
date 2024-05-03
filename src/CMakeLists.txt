# Project config for src/

add_executable(main main.cpp)

add_library(Blockchain
        Block.cpp Block.h
        Transaction.cpp Transaction.h
        Blockchain.cpp Blockchain.h
        sha256.cpp sha256.h)

# Link external libraries
find_package(OpenSSL REQUIRED)
target_link_libraries(Blockchain PRIVATE OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(main PRIVATE Blockchain OpenSSL::SSL OpenSSL::Crypto)

# Suppress OpenSSL deprecated warnings
target_compile_options(Blockchain PRIVATE "-Wno-deprecated-declarations")