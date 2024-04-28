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

Test(block, mine_block) {
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

  block.mineBlock(difficultyTarget);

  std::vector<std::byte> minedBlockHash = block.getBlockHash();

  cr_assert(!minedBlockHash.empty(), "Mined block hash is empty");

  cr_assert(minedBlockHash.size() == 32, "Invalid mined block hash size");
}

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

  cr_assert_eq(updatedTransactions.size(), 1, "Transaction size mismatch.");
  cr_assert_eq(updatedTransactions[0].getType(), 1,
               "Transaction type mismatch.");
  cr_assert_eq(updatedTransactions[0].getData(), data,
               "Transaction data mismatch.");
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

  cr_assert(block.getPreviousHash() == previousHash, "Previous hash mismatch.");
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

  cr_assert_eq(block.getNonce(), nonce, "Nonce mismatch.");
}

Test(block, get_difficulty) {
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
