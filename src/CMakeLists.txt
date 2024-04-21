# Project config for src/

#add_executable(main main.cpp)

# add_library(Block Block.h Block.cpp)
# add_library(Blockchain Blockchain.h Blockchain.cpp)
# add_library(Transaction Transaction.h Transaction.cpp)
# add_library(sha256 sha256.h sha256.cpp)

add_library(Blockchain
        Block.cpp Block.h
        Transaction.cpp Transaction.h
        Blockchain.cpp Blockchain.h
        sha256.cpp sha256.h)


#target_link_libraries(main PRIVATE )
