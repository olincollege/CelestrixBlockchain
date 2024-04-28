#include "Block.h"
#include "sha256.h"

Block::Block(int index, int version, std::vector<std::byte> previousHash,
             std::time_t timestamp, std::vector<Transaction> transactions,
             int nonce, int difficultyTarget)
    : index(index), version(version), previousHash(std::move(previousHash)),
      blockHash(), timestamp(timestamp), transactions(std::move(transactions)),
      nonce(nonce), difficultyTarget(difficultyTarget) {}

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
  ss << difficultyTarget;

  std::string data = ss.str();
  std::vector<std::byte> dataBytes;
  for (char c : data) {
    dataBytes.push_back(static_cast<std::byte>(c));
  }

  return sha256::hash(dataBytes);
}

void Block::mineBlock(int difficulty) {
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

[[maybe_unused]] int Block::getBlockSize() const {
  u_long size = sizeof(index) + sizeof(version) + sizeof(timestamp) +
                sizeof(nonce) + sizeof(difficultyTarget);
  size += previousHash.size() * sizeof(std::byte);
  size += blockHash.size() * sizeof(std::byte);
  size += blockSignature.size() * sizeof(std::byte);
  for (const auto &transaction : transactions) {
    size += sizeof(int);                                      // Size of type
    size += sizeof(int);                                      // Size of length
    size += transaction.getData().size() * sizeof(std::byte); // Size of data
  }
  return (int)size;
}

int Block::getNonce() const { return nonce; }

int Block::getDifficulty() const { return difficultyTarget; }

void Block::addTransaction(const Transaction &transaction) {
  transactions.push_back(transaction);
}

int Block::getVersion() const { return version; }

bool Block::signBlock() {
    EVP_PKEY* privateKey = EVP_PKEY_new();
    RSA *rsa = EVP_PKEY_get1_RSA(privateKey);
    EVP_PKEY_assign_RSA(privateKey, rsa);
    EVP_MD_CTX *mdCtx = EVP_MD_CTX_new();

    //std::cout << privateKey << std::endl;
    //std::cout << mdCtx << std::endl;

    if (EVP_DigestSignInit(mdCtx, nullptr, EVP_sha256(), nullptr,
                           privateKey) <= 0) {
        std::cerr << "Error initializing message digest context" << std::endl;
        return false;
    }

    std::vector<std::byte> hash = calculateBlockHash();

    if (EVP_DigestSignUpdate(mdCtx,
                             reinterpret_cast<const unsigned char *>(hash.data()),
                             hash.size()) <= 0) {
        std::cerr << "Error signing the hash" << std::endl;
        return false;
    }

    size_t lenSignature;
    if (EVP_DigestSignFinal(mdCtx, nullptr, &lenSignature) <= 0) {
        std::cerr << "Error allocating memory for the signature" << std::endl;
        return false;
    }
    blockSignature.resize(lenSignature);

    if (EVP_DigestSignFinal(
            mdCtx, reinterpret_cast<unsigned char *>(blockSignature.data()),
            &lenSignature) <= 0) {
        std::cerr << "Error storing the signature" << std::endl;
        return false;
    }

    EVP_MD_CTX_free(mdCtx);
    EVP_PKEY_free(privateKey);
    return true;
}

bool Block::verifyBlockSignature() const {
    EVP_PKEY* publicKey  = EVP_PKEY_new();
    RSA *rsa = EVP_PKEY_get1_RSA(publicKey);
    EVP_PKEY_assign_RSA(publicKey, rsa);
    EVP_MD_CTX *mdCtx = EVP_MD_CTX_new();

    //std::cout << publicKey << std::endl;
    //std::cout << mdCtx << std::endl;

    if (EVP_DigestVerifyInit(mdCtx, nullptr, EVP_sha256(), nullptr,
                             publicKey) <= 0) {
        std::cerr << "Error verifying init message digest context" << std::endl;
        return false;
    }

    std::vector<std::byte> hash = calculateBlockHash();

    if (EVP_DigestVerify(
            mdCtx, reinterpret_cast<const unsigned char *>(blockSignature.data()),
            blockSignature.size(),
            reinterpret_cast<const unsigned char *>(hash.data()),
            hash.size()) <= 0) {
        std::cerr << "Error verifying message" << std::endl;
        return false;
    }

    EVP_MD_CTX_free(mdCtx);
    EVP_PKEY_free(publicKey);
    return true;
}
