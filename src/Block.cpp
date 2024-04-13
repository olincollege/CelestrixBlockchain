#include "Block.h"
#include "sha256.h"

Block::Block(std::string previousHash, std::time_t timestamp, std::vector<Transaction> transactions)
    : previousHash(previousHash), timestamp(timestamp), transactions(transactions) {
    version = 1;
    nonce = 0;
    merkleRoot = calculateMerkleRoot();
    blockHash = calculateBlockHash();
}

std::time_t Block::getTimestamp() const {
    return std::time(nullptr);
}

std::string Block::getBlockHash() const {
    return blockHash;
}

std::string Block::calculateBlockHash() const {
    std::stringstream ss;
    ss << version << previousHash << timestamp << merkleRoot << blockSignature << nonce << difficultyTarget;
    std::string data = ss.str();
    return sha256::hash(data);
}

void Block::mineBlock(int difficulty) {
    merkleRoot = calculateMerkleRoot();
    // Proof of Work - Mining
    do {
        nonce++;
        blockHash = calculateBlockHash();
    } while (blockHash.substr(0, static_cast<unsigned long>(difficulty)) != std::string(
            static_cast<unsigned long>(difficulty), '0'));
}

std::string Block::getPreviousHash() const {
    return previousHash;
}

std::vector<Transaction> Block::getTransactions() const {
    return transactions;
}

int Block::getBlockHeight() const {
    return 0;
}

bool Block::validateBlock() const {
    return false;
}

int Block::getBlockSize() const {
    return 0;
}

std::string Block::getBlockSignature() const {
    return blockSignature;
}

std::vector<uint8_t> Block::serialize() const {
    return std::vector<uint8_t>();
}

Block Block::deserialize(const std::vector<uint8_t> &serializedData) {
}

std::string Block::calculateMerkleRoot() const {
    return "";
}

std::string Block::getMerkleRoot() const {
    return merkleRoot;
}

int Block::getNonce() const {
    return nonce;
}

void Block::setDifficulty(int difficulty) {
    difficultyTarget = difficulty;
}

void Block::addTransaction(const Transaction &transaction) {
    transactions.push_back(transaction);
}

