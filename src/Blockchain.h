#ifndef CELESTRIXBLOCKCHAIN_BLOCKCHAIN_H
#define CELESTRIXBLOCKCHAIN_BLOCKCHAIN_H

#include "Block.h"
#include <iostream>

class Blockchain {
private:
  std::vector<Block> chain;
  int difficulty;
  mutable std::vector<Transaction> pendingTransactions;

public:
  explicit Blockchain(int difficulty);
  void addBlock(const Block &block);
  Block getBlock(int index) const;
  bool isChainValid() const;
  void printBlockchain() const;
};

#endif // CELESTRIXBLOCKCHAIN_BLOCKCHAIN_H
