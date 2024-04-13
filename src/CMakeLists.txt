# Project config for src/

add_executable(main main.cpp)

add_library(Blockchain
        Block.cpp Block.h
        Transaction.cpp Transaction.h
        Blockchain.cpp Blockchain.h
        sha256.cpp sha256.h)

target_link_libraries(main PRIVATE Blockchain)