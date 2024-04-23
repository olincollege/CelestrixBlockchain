#include "Block.h"

#include "sha256.h"
#include <utility>

Block::Block(int index, std::vector<std::byte> previousHash,
             std::time_t timestamp, std::vector<Transaction> transactions)
    : index(index), previousHash(std::move(previousHash)), timestamp(timestamp),
      transactions(std::move(transactions)) {
  version = 1;
  nonce = 0;
  merkleRoot = calculateMerkleRoot();
  blockHash = calculateBlockHash();
}

std::time_t Block::getTimestamp() { return std::time(nullptr); }

std::vector<std::byte> Block::getBlockHash() const { return blockHash; }

std::vector<std::byte> Block::calculateBlockHash() const {
  std::stringstream ss;
  ss << index;
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
    std::vector<std::byte> dataBytes;
    for (char c : data) {
        dataBytes.push_back(static_cast<std::byte>(c));
    }

    return sha256::hash(dataBytes);
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

int Block::getIndex() const { return index; }

bool Block::validateBlock() const {
    // TODO: not implemented yet
    return false;
}

int Block::getBlockSize() const {
    u_long size = sizeof(index) + sizeof(version) + sizeof(timestamp) + sizeof(nonce) + sizeof(difficultyTarget);
    size += previousHash.size() * sizeof(std::byte);
    size += blockHash.size() * sizeof(std::byte);
    size += merkleRoot.size() * sizeof(std::byte);
    size += blockSignature.size() * sizeof(std::byte);
    for (const auto &transaction : transactions) {
        size += sizeof(int); // Size of type
        size += sizeof(int); // Size of length
        size += transaction.getData().size() * sizeof(std::byte); // Size of data
    }
    return (int)size;
}

std::vector<std::byte> Block::getBlockSignature() const {
  return blockSignature;
}

std::vector<std::byte> Block::serialize() const {
    // TODO: not implemented yet
    return {};
}

Block Block::deserialize(const std::vector<std::byte> &serializedData) {
    // TODO: not implemented yet
    return {0, {}, 0, {}};
}

std::vector<std::byte> Block::calculateMerkleRoot() const {
    // extract transaction hashes
    std::vector<std::vector<std::byte>> transactionHashes;
    transactionHashes.reserve(transactions.size());
for (const auto &transaction : transactions) {
        transactionHashes.push_back(sha256::hash(transaction.encodeData()));
    }

    // handle odd number of transactions
    if (transactionHashes.size() % 2 != 0) {
        transactionHashes.push_back(transactionHashes.back());
    }

    // merkle root calculation logic
    while (transactionHashes.size() > 1) {
        std::vector<std::vector<std::byte>> nextHashes;
        for (size_t i = 0; i < transactionHashes.size(); i += 2) {
            std::vector<std::byte> combinedHashes;
            combinedHashes.insert(combinedHashes.end(), transactionHashes[i].begin(), transactionHashes[i].end());
            combinedHashes.insert(combinedHashes.end(), transactionHashes[i + 1].begin(), transactionHashes[i + 1].end());
            nextHashes.push_back(sha256::hash(combinedHashes));
        }
        transactionHashes = nextHashes;
    }

    return transactionHashes[0];
}

std::vector<std::byte> Block::getMerkleRoot() const {
    return merkleRoot;
}

int Block::getNonce() const { return nonce; }

void Block::setDifficulty(int difficulty) { difficultyTarget = difficulty; }

void Block::addTransaction(const Transaction &transaction) {
  transactions.push_back(transaction);
}
