#ifndef CELESTRIXBLOCKCHAIN_BLOCK_H
#define CELESTRIXBLOCKCHAIN_BLOCK_H

#include "Transaction.h"
#include <cstdint>
#include <ctime>
#include <iostream>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

class Block {
private:
  // Block header
  int index;
  int version{};
  std::vector<std::byte> previousHash;
  std::vector<std::byte> blockHash;
  std::time_t timestamp;
  std::vector<Transaction> transactions;
  // Proof of Work members
  std::vector<std::byte> blockSignature;
  int nonce{};
  int difficultyTarget{};

public:
  Block(int index, int version, std::vector<std::byte> previousHash,
        std::time_t timestamp, std::vector<Transaction> transactions, int nonce,
        int difficultyTarget);
  [[nodiscard]] std::vector<std::byte> getBlockHash() const;
  [[nodiscard]] std::vector<std::byte> getPreviousHash() const;
  [[nodiscard]] std::vector<Transaction> getTransactions() const;
  static std::time_t getTimestamp();
  [[nodiscard]] int getIndex() const;
  [[nodiscard]] int getVersion() const;
  [[nodiscard]] int getDifficulty() const;
  [[maybe_unused]] [[nodiscard]] int getBlockSize() const;
  [[nodiscard]] int getNonce() const;
  [[nodiscard]] std::vector<std::byte> calculateBlockHash() const;
  void mineBlock(int difficulty);
  void addTransaction(const Transaction &transaction);
  bool signBlock(EVP_PKEY *privateKey);
  [[nodiscard]] bool verifyBlockSignature(EVP_PKEY *publicKey) const;
  static std::pair<EVP_PKEY *, EVP_PKEY *> generateEVPKeyPair();
};

#endif // CELESTRIXBLOCKCHAIN_BLOCK_H
