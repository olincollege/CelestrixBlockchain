#ifndef CELESTRIXBLOCKCHAIN_BLOCKCHAIN_H
#define CELESTRIXBLOCKCHAIN_BLOCKCHAIN_H

#include "Block.h"

class Blockchain {
private:
  std::vector<Block> chain;
  int difficulty;
  mutable std::vector<Transaction> pendingTransactions;

public:
  explicit Blockchain(int difficulty);
  void addBlock(const Block &block);
  Block getBlock() const;
  bool isChainValid() const;
  void mineTransactions() const;
  void printBlockchain() const;
};

#endif // CELESTRIXBLOCKCHAIN_BLOCKCHAIN_H
