#include "sha256.h"

std::vector<std::byte> sha256::hash(const std::vector<std::byte> &message) {
  // hash the sha256 digest length
  std::vector<std::byte> hash(SHA256_DIGEST_LENGTH);
  SHA256_CTX sha256;

  // hash the data
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, message.data(), message.size());
  SHA256_Final(reinterpret_cast<unsigned char *>(hash.data()), &sha256);

  return hash;
}
