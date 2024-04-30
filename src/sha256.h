#ifndef CELESTRIXBLOCKCHAIN_SHA256_H
#define CELESTRIXBLOCKCHAIN_SHA256_H

#include <cstdint>
#include <openssl/sha.h>
#include <string>
#include <vector>

class sha256 {
public:
  /**
   * @brief Computes the SHA-256 hash of a message.
   * @param message The message to hash.
   * @return The SHA-256 hash of the message.
   */
  static std::vector<std::byte> hash(const std::vector<std::byte> &message);
};

#endif // CELESTRIXBLOCKCHAIN_SHA256_H
