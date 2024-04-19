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
  std::vector<std::byte> previousHash;
  std::vector<std::byte> blockHash;
  std::time_t timestamp;
  std::vector<Transaction> transactions;
  // Proof of Work members
  std::vector<std::byte> merkleRoot;
  std::vector<std::byte> blockSignature;
  int nonce;
  int difficultyTarget{};

public:
  Block(std::vector<std::byte> previousHash, std::time_t timestamp,
        std::vector<Transaction> transactions);
  std::vector<std::byte> getBlockHash() const;
  std::vector<std::byte> calculateBlockHash() const;
  std::vector<std::byte> getPreviousHash() const;
  std::vector<Transaction> getTransactions() const;
  std::time_t getTimestamp() const;
  void mineBlock(int difficulty);
  int getBlockHeight() const;
  int getBlockSize() const;
  bool validateBlock() const;
  std::vector<std::byte> getBlockSignature() const;
  std::vector<std::byte> serialize() const;
  static Block deserialize(const std::vector<std::byte>& serializedData);
  std::vector<std::byte> calculateMerkleRoot() const;
  std::vector<std::byte> getMerkleRoot() const;
  int getNonce() const;
  void setDifficulty(int difficulty);
  void addTransaction(const Transaction &transaction);
};

#endif // CELESTRIXBLOCKCHAIN_BLOCK_H
