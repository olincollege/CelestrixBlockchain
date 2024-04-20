#include "Block.h"

#include "sha256.h"
#include <utility>

Block::Block(std::vector<std::byte> previousHash, std::time_t timestamp,
             std::vector<Transaction> transactions)
    : previousHash(std::move(previousHash)), timestamp(timestamp),
      transactions(std::move(transactions)) {
  version = 1;
  nonce = 0;
  merkleRoot = calculateMerkleRoot();
  blockHash = calculateBlockHash();
}

std::time_t Block::getTimestamp() const { return std::time(nullptr); }

std::vector<std::byte> Block::getBlockHash() const { return blockHash; }

std::vector<std::byte> Block::calculateBlockHash() const {
  std::stringstream ss;
  ss << version;
  for (const auto &byte : previousHash) {
    ss << static_cast<int>(byte);
  }
  ss << timestamp;
  for (const auto &transaction : transactions) {
    ss << transaction.getType();
    ss << transaction.getLength();
    const std::vector<std::byte> &data = transaction.getData();
    for (const auto &byte : data) {
      ss << static_cast<int>(byte);
    }
  }
  ss << nonce;
  for (const auto &byte : blockSignature) {
    ss << static_cast<int>(byte);
  }
  ss << difficultyTarget;

  std::string data = ss.str();
  return sha256::hash(data);
}

void Block::mineBlock(int difficulty) {
  merkleRoot = calculateMerkleRoot();
  // Proof of Work - Mining
  std::vector<std::byte> target(static_cast<unsigned long>(difficulty / 8),
                                static_cast<std::byte>(0x00));
  target.push_back(
      static_cast<std::byte>(static_cast<int>(0xFF) << (8 - difficulty % 8)));

  do {
    nonce++;
    blockHash = calculateBlockHash();
  } while (!std::equal(blockHash.begin(), blockHash.begin() + difficulty / 8,
                       target.begin()));
}

std::vector<std::byte> Block::getPreviousHash() const { return previousHash; }

std::vector<Transaction> Block::getTransactions() const { return transactions; }

int Block::getBlockHeight() const { return 0; }

bool Block::validateBlock() const { return false; }

int Block::getBlockSize() const { return 0; }

std::vector<std::byte> Block::getBlockSignature() const {
  return blockSignature;
}

std::vector<std::byte> Block::serialize() const { return {}; }

Block Block::deserialize(const std::vector<std::byte> &serializedData) {}

std::vector<std::byte> Block::calculateMerkleRoot() const { return {}; }

std::vector<std::byte> Block::getMerkleRoot() const { return {}; }

int Block::getNonce() const { return nonce; }

void Block::setDifficulty(int difficulty) { difficultyTarget = difficulty; }

void Block::addTransaction(const Transaction &transaction) {
  transactions.push_back(transaction);
}
