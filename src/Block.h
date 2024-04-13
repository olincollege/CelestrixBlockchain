#ifndef CELESTRIXBLOCKCHAIN_BLOCK_H
#define CELESTRIXBLOCKCHAIN_BLOCK_H

#include "Transaction.h"
#include <ctime>
#include <string>
#include <vector>

class Block {
private:
  std::string previousHash;
  std::string blockHash;
  std::time_t timeStamp;
  std::vector<Transaction> transactions;
  // Block specifications
  int version;
  int height;
  int size;
  int weight;
  // Proof of Work members
  std::string merkleRoot;
  std::string blockSignature;
  std::string nonce;
  int difficultyTarget;

public:
  Block(std::string previousHash, std::time_t timestamp,
        std::vector<Transaction> transactions);
  std::string getBlockHash() const;
  std::string calculateBlockHash() const;
  void mineBlock(int difficulty);
  std::string getPreviousHash() const;
  std::vector<Transaction> getTransactions() const;
  std::time_t getTimestamp() const;

  // TODO: Add other methods and members
};

#endif // CELESTRIXBLOCKCHAIN_BLOCK_H
