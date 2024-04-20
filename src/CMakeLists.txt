# Project config for src/

#add_executable(main main.cpp)

add_library(Block Block.h Block.cpp)
add_library(Blockchain Blockchain.h Blockchain.cpp)
add_library(Transaction Transaction.h Transaction.cpp)
add_library(sha256 sha256.h sha256.cpp)

#target_link_libraries(main PRIVATE )
