#ifndef CELESTRIXBLOCKCHAIN_BLOCK_H
#define CELESTRIXBLOCKCHAIN_BLOCK_H

#include "Transaction.h"
#include <cstdint>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>

class Block {
private:
  // Block header
  int index;
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
  Block(int index, std::vector<std::byte> previousHash,
        std::time_t timestamp, std::vector<Transaction> transactions);
  [[nodiscard]] std::vector<std::byte> getBlockHash() const;
  [[nodiscard]] std::vector<std::byte> calculateBlockHash() const;
  [[nodiscard]] std::vector<std::byte> getPreviousHash() const;
  [[nodiscard]] std::vector<Transaction> getTransactions() const;
  static std::time_t getTimestamp() ;
  void mineBlock(int difficulty);
  [[nodiscard]] int getIndex() const;
  [[nodiscard]] int getBlockSize() const;
  [[nodiscard]] std::vector<std::byte> serialize() const;
  static Block deserialize(const std::vector<std::byte> &serializedData);
  [[nodiscard]] std::vector<std::byte> calculateMerkleRoot() const;
  [[nodiscard]] std::vector<std::byte> getMerkleRoot() const;
  [[nodiscard]] int getNonce() const;
  void setDifficulty(int difficulty);
  void addTransaction(const Transaction &transaction);
  bool signBlock(const EVP_PKEY* privateKey);
  bool verifyBlockSignature(const EVP_PKEY* publicKey) const;
  std::vector<std::byte> getBlockSignature() const;
};

#endif // CELESTRIXBLOCKCHAIN_BLOCK_H
