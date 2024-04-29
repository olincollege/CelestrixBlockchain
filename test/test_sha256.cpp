#include "../src/sha256.h"
#include <criterion/criterion.h>
#include <iostream>

Test(sha256, hash_function) {
  std::vector<std::byte> message = {std::byte(0x61), std::byte(0x62),
                                    std::byte(0x63)};
  std::vector<std::byte> expectedHash = {
      std::byte(0xBA), std::byte(0x78), std::byte(0x16), std::byte(0xBF),
      std::byte(0x8F), std::byte(0x01), std::byte(0xCF), std::byte(0xEA),
      std::byte(0x41), std::byte(0x41), std::byte(0x40), std::byte(0xDE),
      std::byte(0x5D), std::byte(0xAE), std::byte(0x22), std::byte(0x23),
      std::byte(0xB0), std::byte(0x03), std::byte(0x61), std::byte(0xA3),
      std::byte(0x96), std::byte(0x17), std::byte(0x7A), std::byte(0x9C),
      std::byte(0xB4), std::byte(0x10), std::byte(0xFF), std::byte(0x61),
      std::byte(0xF2), std::byte(0x00), std::byte(0x15), std::byte(0xAD)};
  std::vector<std::byte> hash = sha256::hash(message);

  std::cout << "\n" << std::endl;
  std::cout << "Actual Hash:" << std::endl;
  for (const auto &byte : hash) {
    std::cout << std::hex << static_cast<int>(byte);
  }
  std::cout << "\n" << std::endl;

  std::cout << std::endl;

  std::cout << "Expected Hash:" << std::endl;

  for (auto &byte : expectedHash) {
    std::cout << std::hex << static_cast<int>(byte);
  }
  std::cout << "\n" << std::endl;

  std::cout << std::endl;

  std::cout << "Hash from Online Source:" << std::endl;
  std::cout
      << "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad"
      << std::endl;
  std::cout << "\n" << std::endl;

  cr_assert(false);
  //   cr_assert_arr_eq(reinterpret_cast<uint8_t *>(hash.data()),
  //                    reinterpret_cast<uint8_t *>(expectedHash.data()),
  //                    hash.size());
}
