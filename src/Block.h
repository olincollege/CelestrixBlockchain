#ifndef CELESTRIXBLOCKCHAIN_BLOCK_H
#define CELESTRIXBLOCKCHAIN_BLOCK_H

#include "Transaction.h"
#include <ctime>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

class Block {
private:
  // Block header
  int version;
  std::string previousHash;
  std::string blockHash;
  std::time_t timestamp;
  std::vector<Transaction> transactions;
  // Proof of Work members
  std::string merkleRoot;
  std::string blockSignature;
  int nonce;
  int difficultyTarget;

public:
  Block(std::string previousHash, std::time_t timestamp,
        std::vector<Transaction> transactions);
  std::string getBlockHash() const;
  std::string calculateBlockHash() const;
  std::string getPreviousHash() const;
  std::vector<Transaction> getTransactions() const;
  std::time_t getTimestamp() const;
  void mineBlock(int difficulty);
  int getBlockHeight() const;
  int getBlockSize() const;
  bool validateBlock() const;
  std::string getBlockSignature() const;
  std::vector<uint8_t> serialize() const;
  static Block deserialize(const std::vector<uint8_t>& serializedData);
  std::string calculateMerkleRoot() const;
  std::string getMerkleRoot() const;
  int getNonce() const;
  void setDifficulty(int difficulty);
  void addTransaction(const Transaction &transaction);
};

#endif // CELESTRIXBLOCKCHAIN_BLOCK_H
