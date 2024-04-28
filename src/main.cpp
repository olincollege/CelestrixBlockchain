#include "Block.h"
#include "Blockchain.h"

int main() {
  std::cout << "==============================================================="
               "==========="
            << std::endl;
  std::cout << "==============================================================="
               "==========="
            << std::endl;
  std::cout << "                          Celestrix Blockchain                 "
               "           "
            << std::endl;
  std::cout << "==============================================================="
               "==========="
            << std::endl;
  std::cout << "==============================================================="
               "==========="
            << std::endl;

  // Initialize blockchain with the desired difficulty for mining
  int difficulty = 4;
  Blockchain blockchain(difficulty);

  // Create data for transactions
  std::vector<std::byte> data1 = {std::byte{0x01}, std::byte{0x02},
                                  std::byte{0x03}};
  std::vector<std::byte> data2 = {std::byte{0x04}, std::byte{0x05},
                                  std::byte{0x06}};
  std::vector<std::byte> data3 = {std::byte{0x10}, std::byte{0x11},
                                  std::byte{0x12}};

  // Create transactions
  Transaction transaction1(1, data1);
  Transaction transaction2(1, data2);
  Transaction transaction3(1, data3);

  // signature verification
  std::cout << "                       Block Signature Verification            "
               "           "
               << std::endl;

  // create and mine the genesis block
  Block genesisBlock(0, 1, std::vector<std::byte>(), std::time(nullptr),
                     std::vector<Transaction>(), 1, difficulty);
  genesisBlock.mineBlock(difficulty);
  genesisBlock.signBlock();
  blockchain.addBlock(genesisBlock);

  // Create and mine block 1
  Block block1(1, 1, genesisBlock.getBlockHash(), std::time(nullptr),
               std::vector<Transaction>(), 10, difficulty);
  block1.addTransaction(transaction1);
  block1.mineBlock(difficulty);
  block1.signBlock();
  blockchain.addBlock(block1);

  // Create and mine block 2
  Block block2(2, 1, block1.getBlockHash(), std::time(nullptr),
               std::vector<Transaction>(), 23, difficulty);
  block2.addTransaction(transaction2);
  block2.addTransaction(transaction3);
  block2.mineBlock(difficulty);
  block2.signBlock();
  blockchain.addBlock(block2);

  // Verify signatures of the blocks
  if (genesisBlock.verifyBlockSignature()) {
    std::cout << "Signature of genesis block is valid." << std::endl;
  } else {
    std::cout << "Signature of genesis block is invalid." << std::endl;
  }
  if (block1.verifyBlockSignature()) {
    std::cout << "Signature of block 1 is valid." << std::endl;
  } else {
    std::cout << "Signature of block 1 is invalid." << std::endl;
  }
  if (block2.verifyBlockSignature()) {
    std::cout << "Signature of block 2 is valid." << std::endl;
  } else {
    std::cout << "Signature of block 2 is invalid." << std::endl;
  }
  std::cout << "==============================================================="
               "==========="
            << std::endl;

  // Print the blockchain
  blockchain.printBlockchain();

  std::cout << "==============================================================="
               "==========="
            << std::endl;
  // Verify the blockchain
  if (blockchain.isChainValid()) {
    std::cout << "Blockchain is valid." << std::endl;
  } else {
    std::cout << "Blockchain is invalid." << std::endl;
  }

  std::cout << "==============================================================="
               "==========="
            << std::endl;
  return 0;
}
