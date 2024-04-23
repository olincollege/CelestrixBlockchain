#include "Blockchain.h"
#include <iostream>

Blockchain::Blockchain(int difficulty) : difficulty(difficulty) {
  // create a genesis block
  Block genesisBlock(0,
                     1,
                     std::vector<std::byte>(),
                     std::time(nullptr),
                     std::vector<Transaction>(),
                     1,
                     difficulty);
  genesisBlock.mineBlock(difficulty);
  chain.push_back(genesisBlock);
}

void Blockchain::addBlock(const Block &block) {
    int newIndex = chain.empty() ? 0 : chain.back().getIndex() + 1;
    Block newBlock(newIndex,
                   block.getVersion(),
                   block.getPreviousHash(),
                   Block::getTimestamp(),
                   block.getTransactions(),
                   block.getNonce(),
                   block.getDifficulty());
    newBlock.mineBlock(difficulty);
    chain.push_back(newBlock);
}

Block Blockchain::getBlock(int index) const {
    if (index >= 0 && index < static_cast<int>(chain.size())) {
        return chain[static_cast<unsigned long>(index)];
    } else {
        throw std::out_of_range("Index out of bounds");
    }
}

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

void Blockchain::printBlockchain() const {
  for (const auto &block : chain) {
      std::cout << "Block Index: " << block.getIndex() << std::endl;
      std::cout << "Block Version: " << block.getVersion() << std::endl;
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
    std::cout << "Timestamp: " << Block::getTimestamp() << std::endl;
    std::cout << "Transactions: " << std::endl;
    for (const Transaction &transaction : block.getTransactions()) {
      std::cout << "Type: " << transaction.getType() << std::endl;
      std::cout << "Length: " << transaction.getLength() << std::endl;
    }
    std::cout << std::endl;
  }
}
