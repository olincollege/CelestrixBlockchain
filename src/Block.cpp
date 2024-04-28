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

bool Block::signBlock(EVP_PKEY *privateKey) {
  EVP_MD_CTX *mdCtx = EVP_MD_CTX_new();

  if (EVP_DigestSignInit(mdCtx, nullptr, EVP_sha256(), nullptr, privateKey) <=
      0) {
    std::cerr << "Error initializing message digest context" << std::endl;
    EVP_MD_CTX_free(mdCtx);
    return false;
  }

  std::vector<std::byte> hash = calculateBlockHash();

  if (EVP_DigestSignUpdate(mdCtx,
                           reinterpret_cast<const unsigned char *>(hash.data()),
                           hash.size()) <= 0) {
    std::cerr << "Error signing the hash" << std::endl;
    EVP_MD_CTX_free(mdCtx);
    return false;
  }

  size_t lenSignature;
  if (EVP_DigestSignFinal(mdCtx, nullptr, &lenSignature) <= 0) {
    std::cerr << "Error allocating memory for the signature" << std::endl;
    EVP_MD_CTX_free(mdCtx);
    return false;
  }

  blockSignature.resize(lenSignature);

  if (EVP_DigestSignFinal(
          mdCtx, reinterpret_cast<unsigned char *>(blockSignature.data()),
          &lenSignature) <= 0) {
    std::cerr << "Error storing the signature" << std::endl;
    EVP_MD_CTX_free(mdCtx);
    return false;
  }

  EVP_MD_CTX_free(mdCtx);
  return true;
}

bool Block::verifyBlockSignature(EVP_PKEY *publicKey) const {
  EVP_MD_CTX *mdCtx = EVP_MD_CTX_new();

  if (EVP_DigestVerifyInit(mdCtx, nullptr, EVP_sha256(), nullptr, publicKey) <=
      0) {
    std::cerr << "Error verifying init message digest context" << std::endl;
    EVP_MD_CTX_free(mdCtx);
    return false;
  }

  std::vector<std::byte> hash = calculateBlockHash();

  if (EVP_DigestVerify(
          mdCtx, reinterpret_cast<const unsigned char *>(blockSignature.data()),
          blockSignature.size(),
          reinterpret_cast<const unsigned char *>(hash.data()),
          hash.size()) <= 0) {
    std::cerr << "Error verifying message" << std::endl;
    EVP_MD_CTX_free(mdCtx);
    return false;
  }

  EVP_MD_CTX_free(mdCtx);
  return true;
}

std::pair<EVP_PKEY *, EVP_PKEY *> Block::generateEVPKeyPair() {
  EVP_PKEY_CTX *ctx;
  EVP_PKEY *pkey = nullptr;
  EVP_PKEY *pubkey = nullptr;

  // create a new context for key generation
  if (!(ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, nullptr))) {
    std::cerr << "Error creating EVP_PKEY_CTX" << std::endl;
    return std::make_pair(nullptr, nullptr);
  }

  // initialize the context for key generation
  if (EVP_PKEY_keygen_init(ctx) <= 0) {
    std::cerr << "Error initializing EVP_PKEY_CTX for key generation"
              << std::endl;
    EVP_PKEY_CTX_free(ctx);
    return std::make_pair(nullptr, nullptr);
  }

  // Set RSA key length (2048 bits)
  if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048) <= 0) {
    std::cerr << "Error setting RSA key length" << std::endl;
    EVP_PKEY_CTX_free(ctx);
    return std::make_pair(nullptr, nullptr);
  }

  // generate the key pair
  if (EVP_PKEY_keygen(ctx, &pkey) <= 0) {
    std::cerr << "Error generating EVP private key" << std::endl;
    EVP_PKEY_CTX_free(ctx);
    return std::make_pair(nullptr, nullptr);
  }

  // Extract public key from private key
  pubkey = EVP_PKEY_new();
  if (!pubkey) {
    std::cerr << "Error creating EVP public key" << std::endl;
    EVP_PKEY_free(pkey);
    EVP_PKEY_CTX_free(ctx);
    return std::make_pair(nullptr, nullptr);
  }

  // Serialize private key to create public key
  BIO *bio = BIO_new(BIO_s_mem());
  if (!bio) {
    std::cerr << "Error creating BIO" << std::endl;
    EVP_PKEY_free(pkey);
    return std::make_pair(nullptr, nullptr);
  }

  if (PEM_write_bio_PUBKEY(bio, pkey) != 1) {
    std::cerr << "Error writing public key data to BIO" << std::endl;
    BIO_free(bio);
    EVP_PKEY_free(pkey);
    return std::make_pair(nullptr, nullptr);
  }

  // Read public key from BIO
  pubkey = PEM_read_bio_PUBKEY(bio, nullptr, nullptr, nullptr);
  if (!pubkey) {
    std::cerr << "Error creating EVP public key from BIO" << std::endl;
    BIO_free(bio);
    EVP_PKEY_free(pkey);
    return std::make_pair(nullptr, nullptr);
  }

  BIO_free(bio);

  EVP_PKEY_CTX_free(ctx);

  return std::make_pair(pkey, pubkey);
}
