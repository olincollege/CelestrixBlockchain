#include "Blockchain.h"
#include "Block.h"

int main() {
    // Initialize blockchain with the desired difficulty for mining
    int difficulty = 4;
    Blockchain blockchain(difficulty);

    // Create data for transactions
    std::vector<std::byte> data1 = {std::byte{0x01}, std::byte{0x02}, std::byte{0x03}};
    std::vector<std::byte> data2 = {std::byte{0x04}, std::byte{0x05}, std::byte{0x06}};
    std::vector<std::byte> data3 = {std::byte{0x10}, std::byte{0x11}, std::byte{0x12}};

    // Create transactions
    Transaction transaction1(1, data1);
    Transaction transaction2(1, data2);
    Transaction transaction3(1, data3);

    // create and mine the genesis block
    Block genesisBlock(0, 1, std::vector<std::byte>(), std::time(nullptr), std::vector<Transaction>(), 1, difficulty);
    genesisBlock.mineBlock(difficulty);
    blockchain.addBlock(genesisBlock);

    // Create and mine the second block
    Block block1(1, 1, genesisBlock.getBlockHash(), std::time(nullptr), std::vector<Transaction>(), 10, difficulty);
    block1.addTransaction(transaction1);
    block1.mineBlock(difficulty);
    blockchain.addBlock(block1);

    // Create and mine the third block
    Block block2(2, 1, block1.getBlockHash(), std::time(nullptr), std::vector<Transaction>(), 23, difficulty);
    block2.addTransaction(transaction2);
    block2.addTransaction(transaction3);
    block2.mineBlock(difficulty);
    blockchain.addBlock(block2);

    // Print the blockchain
    std::cout << "====================" << std::endl;
    std::cout << "Celestrix Blockchain" << std::endl;
    std::cout << "====================" << std::endl;
    blockchain.printBlockchain();

    // Verify the blockchain
    if (blockchain.isChainValid()) {
        std::cout << "Blockchain is valid." << std::endl;
    } else {
        std::cout << "Blockchain is invalid." << std::endl;
    }

    return 0;
}
