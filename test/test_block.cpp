#include "../src/Block.h"
#include <criterion/criterion.h>

Test(BlockTest, get_block_hash) {
  std::vector<std::byte> previousHash(
      {std::byte{0x11}, std::byte{0x22}, std::byte{0x33}});
  std::time_t timestamp = std::time(nullptr);
  std::vector<Transaction> transactions;

  int index = 0;
  int version = 1;
  int nonce = 0;
  int difficultyTarget = 5;

  Block block(index, version, previousHash, timestamp, transactions, nonce,
              difficultyTarget);

  std::vector<std::byte> expectedHash = block.calculateBlockHash();

  block.mineBlock(difficultyTarget);

  std::vector<std::byte> actualHash = block.getBlockHash();

  cr_assert(expectedHash == actualHash,
            "Block hash doesn't match expected hash");
}
Test(block, mine_block) {}

Test(block, serialize_block) {}

Test(block, deserialize_block) {}

// Test(block, calculate_merkle_root) {}

Test(block, add_transaction) {
  std::vector<std::byte> previousHash(
      {std::byte{0x11}, std::byte{0x22}, std::byte{0x33}});
  std::time_t timestamp = std::time(nullptr);
  std::vector<Transaction> transactions;

  int index = 0;
  int version = 1;
  int nonce = 0;
  int difficultyTarget = 5;

  Block block(index, version, previousHash, timestamp, transactions, nonce,
              difficultyTarget);

  std::vector<std::byte> data = {std::byte{0x01}, std::byte{0x02},
                                 std::byte{0x03}};
  Transaction transaction(1, data);

  block.addTransaction(transaction);

  std::vector<Transaction> updatedTransactions = block.getTransactions();

  cr_assert_eq(updatedTransactions.size(), 1);
  cr_assert_eq(updatedTransactions[0].getType(), 1);
  cr_assert_eq(updatedTransactions[0].getData(), data);
}

Test(block, get_previous_hash) {
  std::vector<std::byte> previousHash(
      {std::byte{0x11}, std::byte{0x22}, std::byte{0x33}});
  std::time_t timestamp = std::time(nullptr);
  std::vector<Transaction> transactions;

  int index = 0;
  int version = 1;
  int nonce = 0;
  int difficultyTarget = 5;

  Block block(index, version, previousHash, timestamp, transactions, nonce,
              difficultyTarget);

  cr_assert(block.getPreviousHash() == previousHash);
}

Test(block, get_nonce) {
  std::vector<std::byte> previousHash(
      {std::byte{0x11}, std::byte{0x22}, std::byte{0x33}});
  std::time_t timestamp = std::time(nullptr);
  std::vector<Transaction> transactions;

  std::vector<std::byte> data(
      {std::byte{0x01}, std::byte{0x02}, std::byte{0x03}});
  Transaction transaction(1, data);

  int index = 0;
  int version = 1;
  int nonce = 0;
  int difficultyTarget = 5;

  Block block(index, version, previousHash, timestamp, transactions, nonce,
              difficultyTarget);

  block.addTransaction(transaction);

  cr_assert_eq(block.getNonce(), nonce);
}

Test(block, get_block_signature) {

  std::vector<std::byte> previousHash(
      {std::byte{0x11}, std::byte{0x22}, std::byte{0x33}});
  std::time_t timestamp = std::time(nullptr);
  std::vector<Transaction> transactions;

  std::vector<std::byte> data(
      {std::byte{0x01}, std::byte{0x02}, std::byte{0x03}});
  Transaction transaction(1, data);

  int index = 0;
  int version = 1;
  int nonce = 0;
  int difficultyTarget = 5;

  Block block(index, version, previousHash, timestamp, transactions, nonce,
              difficultyTarget);

  block.addTransaction(transaction);

  // cr_assert_eq(block.getBlockSignature(), );
}

Test(block, get_merkle_root) {}

Test(block, get_difficult) {
  std::vector<std::byte> previousHash(
      {std::byte{0x11}, std::byte{0x22}, std::byte{0x33}});
  std::time_t timestamp = std::time(nullptr);
  std::vector<Transaction> transactions;

  int index = 0;
  int version = 1;
  int nonce = 0;
  int difficultyTarget = 5;

  Block block(index, version, previousHash, timestamp, transactions, nonce,
              difficultyTarget);

  std::vector<std::byte> data(
      {std::byte{0x01}, std::byte{0x02}, std::byte{0x03}});
  Transaction transaction(1, data);

  block.addTransaction(transaction);

  cr_assert(block.getDifficulty() == difficultyTarget, "Difficulty mismatch");
}
