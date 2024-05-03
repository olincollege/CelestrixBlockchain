#include "Blockchain.h"

Blockchain::Blockchain(int mineDifficulty) : difficulty(mineDifficulty) {}

void Blockchain::addBlock(const Block &block) {
  // calculate the index for adding the new block
  int newIndex = chain.empty() ? 0 : chain.back().getIndex() + 1;

  // get the previous block's hash
  std::vector<std::byte> previousHash;
  if (!chain.empty()) {
    previousHash = chain.back().getBlockHash();
  }

  // initialize a new block, mine it, and then add it to the blockchain
  Block newBlock(newIndex, block.getVersion(), previousHash,
                 Block::getTimestamp(), block.getTransactions(),
                 block.getNonce(), block.getDifficulty());
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
  // iterate through all blocks in the chain
  for (size_t i = 1; i < chain.size(); ++i) {
    const Block &currentBlock = chain[i];
    const Block &previousBlock = chain[i - 1];

    // check whether the current block's hash is equal to its calculated block
    // hash
    if (currentBlock.getBlockHash() != currentBlock.calculateBlockHash()) {
      return false;
    }

    // check whether the previous hash stored in the current block is equal to
    // the previous block's hash
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
      std::cout << "\t Type: " << transaction.getType() << std::endl;
      std::cout << "\t Length: " << transaction.getLength() << std::endl;
      std::cout << "\t Data: ";
      for (std::byte dataByte : transaction.getData()) {
        std::cout << static_cast<unsigned>(dataByte) << "";
      }
      std::cout << std::endl;
      std::cout << "\t-------" << std::endl;
    }
    std::cout << std::endl;
  }
}
