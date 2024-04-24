# Project config for src/

add_executable(main main.cpp)

add_library(Blockchain
        Block.cpp Block.h
        Transaction.cpp Transaction.h
        Blockchain.cpp Blockchain.h
        sha256.cpp sha256.h)

# External libraries
find_package(OpenSSL REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

target_link_libraries(Blockchain PRIVATE OpenSSL::SSL OpenSSL::Crypto ${nlohmann_json_INCLUDE_DIRS})

target_link_libraries(main PRIVATE Blockchain)
