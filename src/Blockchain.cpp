#include "Blockchain.h"
#include <iostream>

Blockchain::Blockchain(int difficulty) : difficulty(difficulty) {
    // create a genesis block
  Block genesisBlock(std::vector<std::byte>(), std::time(nullptr), std::vector<Transaction>());
  genesisBlock.mineBlock(difficulty);
  chain.push_back(genesisBlock);
}

void Blockchain::addBlock(const Block &block) { chain.push_back(block); }

Block Blockchain::getBlock() const { return chain.back(); }

bool Blockchain::isChainValid() const {
  for (size_t i = 1; i < chain.size(); ++i) {
    const Block &currentBlock = chain[i];
    const Block &previousBlock = chain[i - 1];

    if (currentBlock.getBlockHash() != currentBlock.calculateBlockHash()) {
      return false;
    }

    if (currentBlock.getPreviousHash() != previousBlock.getBlockHash()) {
      return false;
    }
  }
  return true;
}

void Blockchain::mineTransactions() const {}

void Blockchain::printBlockchain() const {
    for (const auto &block : chain) {
        std::cout << "Block Hash: ";
        for (const auto &byte : block.getBlockHash()) {
            std::cout << std::hex << static_cast<int>(byte);
        }
        std::cout << std::endl;
        std::cout << "Previous Hash: ";
        for (const auto &byte : block.getPreviousHash()) {
            std::cout << std::hex << static_cast<int>(byte);
        }
        std::cout << std::endl;
        std::cout << "Timestamp: " << block.getTimestamp() << std::endl;
        std::cout << "Transactions: " << std::endl;
        for (const Transaction &transaction : block.getTransactions()) {
            std::cout << "Type: " << transaction.getType() << std::endl;
            std::cout << "Length: " << transaction.getLength() << std::endl;
        }
        std::cout << std::endl;
    }
}