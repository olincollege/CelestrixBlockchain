#include "Block.h"

#include "sha256.h"

Block::Block(int index,
             int version,
             std::vector<std::byte> previousHash,
             std::time_t timestamp,
             std::vector<Transaction> transactions,
             int nonce,
             int difficultyTarget) :
             index(index),
             version(version),
             previousHash(std::move(previousHash)),
             timestamp(timestamp),
             transactions(std::move(transactions)),
             nonce(nonce),
             difficultyTarget(difficultyTarget)
             {
    merkleRoot = calculateMerkleRoot();
    blockHash = calculateBlockHash();
    // Generate random nonce
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, INT_MAX);
    nonce = dist(gen);
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

int Block::getBlockSize() const {
  u_long size = sizeof(index) + sizeof(version) + sizeof(timestamp) +
                sizeof(nonce) + sizeof(difficultyTarget);
  size += previousHash.size() * sizeof(std::byte);
  size += blockHash.size() * sizeof(std::byte);
  size += merkleRoot.size() * sizeof(std::byte);
  size += blockSignature.size() * sizeof(std::byte);
  for (const auto &transaction : transactions) {
    size += sizeof(int);                                      // Size of type
    size += sizeof(int);                                      // Size of length
    size += transaction.getData().size() * sizeof(std::byte); // Size of data
  }
  return (int)size;
}

bool Block::signBlock(const EVP_PKEY *privateKey) {
  // message digest context for signing
  EVP_MD_CTX *mdCtx = EVP_MD_CTX_new();
  if (!mdCtx) {
    return false;
  }

  // initialize it with SHA256
  if (EVP_DigestSignInit(mdCtx, nullptr, EVP_sha256(), nullptr,
                         const_cast<EVP_PKEY *>(privateKey)) != 1) {
    EVP_MD_CTX_free(mdCtx);
    return false;
  }

  // calculate the hash of the block
  std::vector<std::byte> hash = calculateBlockHash();

  // sign the hash
  if (EVP_DigestSign(mdCtx, nullptr, nullptr,
                     reinterpret_cast<const unsigned char *>(hash.data()),
                     hash.size()) != 1) {
    EVP_MD_CTX_free(mdCtx);
    return false;
  }

  // allocate memory for length of signature
  size_t lenSignature;
  if (EVP_DigestSign(mdCtx, nullptr, &lenSignature, nullptr, 0) != 1) {
    EVP_MD_CTX_free(mdCtx);
    return false;
  }
  blockSignature.resize(lenSignature);

  // sign the hash and store signature
  if (EVP_DigestSign(
          mdCtx, reinterpret_cast<unsigned char *>(blockSignature.data()),
          &lenSignature, reinterpret_cast<const unsigned char *>(hash.data()),
          hash.size()) != 1) {
    EVP_MD_CTX_free(mdCtx);
    return false;
  }

  EVP_MD_CTX_free(mdCtx);
  return true;
}

bool Block::verifyBlockSignature(const EVP_PKEY *publicKey) const {
  // message digest context for signing
  EVP_MD_CTX *mdCtx = EVP_MD_CTX_new();
  if (!mdCtx) {
    return false;
  }

  // initialize it with SHA256
  if (EVP_DigestSignInit(mdCtx, nullptr, EVP_sha256(), nullptr,
                         const_cast<EVP_PKEY *>(publicKey)) != 1) {
    EVP_MD_CTX_free(mdCtx);
    return false;
  }

  // calculate the hash of the block
  std::vector<std::byte> hash = calculateBlockHash();

  // verify the signature
  if (EVP_DigestVerify(
          mdCtx, reinterpret_cast<const unsigned char *>(blockSignature.data()),
          blockSignature.size(),
          reinterpret_cast<const unsigned char *>(hash.data()),
          hash.size()) != 1) {
    EVP_MD_CTX_free(mdCtx);
    return false;
  }

  EVP_MD_CTX_free(mdCtx);

  return true;
}

std::vector<std::byte> Block::getBlockSignature() const {
  return blockSignature;
}

std::string Block::serialize() const {
    nlohmann::json jsonObj;
    jsonObj["index"] = index;
    jsonObj["version"] = version;

    // Serialize previous hash
    std::vector<int> serializedPreviousHash;
    serializedPreviousHash.reserve(previousHash.size());
    for (const auto& byte : previousHash) {
        serializedPreviousHash.push_back(static_cast<int>(byte));
    }
    jsonObj["previous_hash"] = serializedPreviousHash;

    jsonObj["timestamp"] = static_cast<int64_t>(timestamp);

    // Serialize transactions
    std::vector<std::string> serializedTransactions;
    serializedTransactions.reserve(transactions.size());
    for (const auto& transaction : transactions) {
        serializedTransactions.push_back(transaction.serialize());
    }
    jsonObj["transactions"] = serializedTransactions;

    // Serialize merkle root
    std::vector<int> serializedMerkleRoot;
    serializedMerkleRoot.reserve(merkleRoot.size());
    for (const auto& byte : merkleRoot) {
        serializedMerkleRoot.push_back(static_cast<int>(byte));
    }
    jsonObj["merkle_root"] = serializedMerkleRoot;

    // Serialize block signature
    std::vector<int> serializedBlockSignature;
    serializedBlockSignature.reserve(blockSignature.size());
    for (const auto& byte : blockSignature) {
        serializedBlockSignature.push_back(static_cast<int>(byte));
    }
    jsonObj["block_signature"] = serializedBlockSignature;

    jsonObj["nonce"] = nonce;
    jsonObj["difficulty_target"] = difficultyTarget;

    return jsonObj.dump();
}

Block Block::deserialize(const std::string &serializedData) {
    nlohmann::json jsonObj = nlohmann::json::parse(serializedData);

    int index = jsonObj["index"];
    int version = jsonObj["version"];

    // Deserialize previous hash
    std::vector<std::byte> previousHash;
    for (const auto& intValue : jsonObj["previous_hash"]) {
        previousHash.push_back(static_cast<std::byte>(intValue));
    }

    auto timestamp = static_cast<std::time_t>(jsonObj["timestamp"]);

    // Deserialize transactions
    std::vector<Transaction> transactions;
    for (const auto& serializedTransaction : jsonObj["transactions"]) {
        transactions.push_back(Transaction::deserialize(serializedTransaction.dump()));
    }

    // Deserialize merkle root
    std::vector<std::byte> merkleRoot;
    for (const auto& intValue : jsonObj["merkle_root"]) {
        merkleRoot.push_back(static_cast<std::byte>(intValue));
    }

    // Deserialize block signature
    std::vector<std::byte> blockSignature;
    for (const auto& intValue : jsonObj["block_signature"]) {
        blockSignature.push_back(static_cast<std::byte>(intValue));
    }

    int nonce = jsonObj["nonce"];
    int difficultyTarget = jsonObj["difficulty_target"];

    return {index, version, previousHash, timestamp, transactions, nonce, difficultyTarget};
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
      combinedHashes.insert(combinedHashes.end(), transactionHashes[i].begin(),
                            transactionHashes[i].end());
      combinedHashes.insert(combinedHashes.end(),
                            transactionHashes[i + 1].begin(),
                            transactionHashes[i + 1].end());
      nextHashes.push_back(sha256::hash(combinedHashes));
    }
    transactionHashes = nextHashes;
  }

  return transactionHashes[0];
}

std::vector<std::byte> Block::getMerkleRoot() const { return merkleRoot; }

int Block::getNonce() const { return nonce; }

int Block::getDifficulty() const { return difficultyTarget; }

void Block::addTransaction(const Transaction &transaction) {
  transactions.push_back(transaction);
}

int Block::getVersion() const { return version; }
