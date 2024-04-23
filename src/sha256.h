#ifndef CELESTRIXBLOCKCHAIN_SHA256_H
#define CELESTRIXBLOCKCHAIN_SHA256_H

#include <cstdint>
#include <string>
#include <vector>

class sha256 {
private:
  static const uint32_t K[];
  static const uint32_t initialHashValues[];

  static uint32_t rightRotate(uint32_t value, uint32_t n);
  static uint32_t sigma0(uint32_t value);
  static uint32_t sigma1(uint32_t value);
  static uint32_t Sigma0(uint32_t value);
  static uint32_t Sigma1(uint32_t value);
  static std::vector<uint32_t>
  computeMessageSchedule(const std::vector<uint8_t> &block);

public:
    static std::vector<std::byte> hash(const std::vector<std::byte>& message);
};

#endif // CELESTRIXBLOCKCHAIN_SHA256_H
