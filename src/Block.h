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

/**
 * @brief Class representing a block in the blockchain.
 */
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
  /**
   * @brief Constructor for Block class.
   * @param index Index of the block.
   * @param version Version of the block.
   * @param previousHash Hash of the previous block.
   * @param timestamp Timestamp of when the block was created.
   * @param transactions List of transactions in the block.
   * @param nonce Nonce used in mining the block.
   * @param difficultyTarget Difficulty target for mining.
   */
  Block(int index, int version, std::vector<std::byte> previousHash,
        std::time_t timestamp, std::vector<Transaction> transactions, int nonce,
        int difficultyTarget);

  /**
   * @brief Gets the hash of the block.
   * @return The hash of the block.
   */
  [[nodiscard]] std::vector<std::byte> getBlockHash() const;

  /**
   * @brief Gets the hash of the previous block.
   * @return The hash of the previous block.
   */
  [[nodiscard]] std::vector<std::byte> getPreviousHash() const;

  /**
   * @brief Gets the list of transactions in the block.
   * @return The list of transactions in the block.
   */
  [[nodiscard]] std::vector<Transaction> getTransactions() const;

  /**
   * @brief Calculates the timestamp of the current time.
   * @return Timestamp of the current time.
   */
  static std::time_t getTimestamp();

  /**
   * @brief Gets the index of the block.
   * @return The index of the block.
   */
  [[nodiscard]] int getIndex() const;

  /**
   * @brief Gets the version of the block.
   * @return The version of the block.
   */
  [[nodiscard]] int getVersion() const;

  /**
   * @brief Gets the difficulty target for mining.
   * @return The difficulty target for mining.
   */
  [[nodiscard]] int getDifficulty() const;

  /**
   * @brief Gets the size of the block.
   * @return The size of the block.
   */
  [[maybe_unused]] [[nodiscard]] int getBlockSize() const;

  /**
   * @brief Gets the nonce used in mining the block.
   * @return The nonce used in mining the block.
   */
  [[nodiscard]] int getNonce() const;

  /**
   * @brief Calculates the hash of the block.
   * @return The calculated hash of the block.
   */
  [[nodiscard]] std::vector<std::byte> calculateBlockHash() const;

  /**
   * @brief Mines the block with a given difficulty target.
   * @param difficulty Difficulty target for mining.
   */
  void mineBlock(int difficulty);

  /**
   * @brief Adds a transaction to the block.
   * @param transaction The transaction to be added.
   */
  void addTransaction(const Transaction &transaction);

  /**
   * @brief Signs the block using the provided private key.
   * @param privateKey The private key used for signing.
   * @return True if signing is successful, false otherwise.
   */
  bool signBlock(EVP_PKEY *privateKey);

  /**
   * @brief Verifies the signature of the block using the provided public key.
   * @param publicKey The public key used for signature verification.
   * @return True if signature verification is successful, false otherwise.
   */
  [[nodiscard]] bool verifyBlockSignature(EVP_PKEY *publicKey) const;

  /**
   * @brief Generates a pair of EVP key (private and public key).
   * @return A pair of EVP key (private and public key).
   */
  static std::pair<EVP_PKEY *, EVP_PKEY *> generateEVPKeyPair();
};

#endif // CELESTRIXBLOCKCHAIN_BLOCK_H
