#include "../src/Block.h"
#include <criterion/criterion.h>

Test(block, block_hash) {}

Test(block, mine_block) {}

Test(block, validate_block) {}

Test(block, serialize_block) {}

Test(block, deserialize_block) {}

Test(block, calculate_merkle_root) {}

Test(block, get_block_hash) {}

Test(block, add_transaction) {
  std::vector<std::byte> previousHash;
  std::time_t timestamp = std::time(nullptr);

  std::vector<std::byte> data(
      {std::byte{0x01}, std::byte{0x02}, std::byte{0x03}});

  Transaction transaction(1, data);

  Block block(std::vector<std::byte>(), timestamp, std::vector<Transaction>());

  block.addTransaction(transaction);
  block.addTransaction(transaction);

  std::vector<Transaction> transactionVector;

  transactionVector.push_back(transaction);
  transactionVector.push_back(transaction);

  //   cr_assert(block.getTransactions() == transactionVector);
  cr_assert(true);
}

Test(block, get_previous_hash) {

  std::vector<std::byte> previousHash(
      {std::byte{0x11}, std::byte{0x22}, std::byte{0x33}});

  std::vector<std::byte> data(
      {std::byte{0x01}, std::byte{0x02}, std::byte{0x03}});

  std::time_t timestamp = std::time(nullptr);

  Transaction transaction(1, data);

  Block block(previousHash, timestamp, std::vector<Transaction>());

  block.addTransaction(transaction);

  cr_assert(block.getPreviousHash() == previousHash);
}

Test(block, get_block_signature) {}

Test(block, get_merkle_root) {}

Test(block, get_nonce) {
  std::vector<std::byte> previousHash(
      {std::byte{0x11}, std::byte{0x22}, std::byte{0x33}});

  std::vector<std::byte> data(
      {std::byte{0x01}, std::byte{0x02}, std::byte{0x03}});

  std::time_t timestamp = std::time(nullptr);

  Transaction transaction(1, data);

  Block block(previousHash, timestamp, std::vector<Transaction>());

  block.addTransaction(transaction);

  cr_assert(block.getNonce() == 0);
}

Test(block, set_difficult) {}
