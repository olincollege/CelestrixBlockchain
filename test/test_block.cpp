#include "../src/Block.h"
#include <criterion/criterion.h>

Test(block, block_hash) {}

Test(block, mine_block) {}

Test(block, validate_block) {}

Test(block, serialize_block) {}

Test(block, deserialize_block) {}

Test(block, calculate_merkle_root) {}

Test(block, get_block_hash) {}

// Test for adding a transaction to a block
Test(block, add_transaction) {
  std::vector<std::byte> previousHash(
      {std::byte{0x11}, std::byte{0x22}, std::byte{0x33}});
  std::vector<std::byte> data = {std::byte{0x01}, std::byte{0x02},
                                 std::byte{0x03}};
  Transaction transaction(1, data);

  int index = 0;
  int version = 1; // Set a version number
  std::time_t timestamp = std::time(nullptr);
  int nonce = 0;            // Set a default nonce
  int difficultyTarget = 4; // Set a difficulty target

  Block block(index, version, previousHash, timestamp,
              std::vector<Transaction>(), nonce, difficultyTarget);

  block.addTransaction(transaction);

  std::vector<Transaction> transactions = block.getTransactions();

  cr_assert_eq(transactions.size(), 1);
  cr_assert_eq(transactions[0].getType(), 1);
  cr_assert_eq(transactions[0].getData(), data);
}

Test(block, get_previous_hash) {

  std::vector<std::byte> previousHash(
      {std::byte{0x11}, std::byte{0x22}, std::byte{0x33}});

  std::vector<std::byte> data(
      {std::byte{0x01}, std::byte{0x02}, std::byte{0x03}});

  std::time_t timestamp = std::time(nullptr);

  Transaction transaction(1, data);

  int index = 0;

  Block block(index, 1, previousHash, timestamp, std::vector<Transaction>(), 0,
              0);

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

  int index = 0;

  Block block(index, 1, previousHash, timestamp, std::vector<Transaction>(), 0,
              0);

  // Mine the block to generate the nonce
  block.mineBlock(4); // Assuming difficulty level 4 for mining

  cr_assert_eq(block.getNonce(), block.getNonce());
}

Test(block, set_difficult) {}
