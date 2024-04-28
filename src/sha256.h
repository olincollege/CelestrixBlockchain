#ifndef CELESTRIXBLOCKCHAIN_SHA256_H
#define CELESTRIXBLOCKCHAIN_SHA256_H

#include <cstdint>
#include <string>
#include <vector>

class sha256 {
private:
  static const uint32_t K[];
  static const uint32_t initialHashValues[];

  /**
   * @brief Right rotates a 32-bit value by n bits.
   * @param value The value to rotate.
   * @param n The number of bits to rotate.
   * @return The result of the rotation.
   */
  static uint32_t rightRotate(uint32_t value, uint32_t n);

  /**
   * @brief Performs the sigma0 function on a 32-bit value.
   * @param value The value to process.
   * @return The result of the sigma0 function.
   */
  static uint32_t sigma0(uint32_t value);

  /**
   * @brief Performs the sigma1 function on a 32-bit value.
   * @param value The value to process.
   * @return The result of the sigma1 function.
   */
  static uint32_t sigma1(uint32_t value);

  /**
   * @brief Performs the Sigma0 function on a 32-bit value.
   * @param value The value to process.
   * @return The result of the Sigma0 function.
   */
  static uint32_t Sigma0(uint32_t value);

  /**
   * @brief Performs the Sigma1 function on a 32-bit value.
   * @param value The value to process.
   * @return The result of the Sigma1 function.
   */
  static uint32_t Sigma1(uint32_t value);

  /**
   * @brief Computes the message schedule for a block.
   * @param block The block for which to compute the message schedule.
   * @return The computed message schedule.
   */
  static std::vector<uint32_t>
  computeMessageSchedule(const std::vector<uint8_t> &block);

public:
  /**
   * @brief Computes the SHA-256 hash of a message.
   * @param message The message to hash.
   * @return The SHA-256 hash of the message.
   */
  static std::vector<std::byte> hash(const std::vector<std::byte> &message);
};

#endif // CELESTRIXBLOCKCHAIN_SHA256_H
