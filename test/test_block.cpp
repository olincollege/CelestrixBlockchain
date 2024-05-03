#include "../src/Block.h"
#include <criterion/criterion.h>

// Test getting block hash from a block
Test(block, get_block_hash) {
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
  expectedHash = block.calculateBlockHash();
  std::vector<std::byte> actualHash = block.getBlockHash();

  cr_assert(expectedHash == actualHash,
            "Block hash doesn't match expected hash");
}

// Test for mining a block
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

// Test for adding transactions to a block
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

// Test for getting a previous blocks hash from a block
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

// Test for getting nonce value from a block
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

// Test for getting difficulty from a block
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

// Test for getting the index of a block
Test(block, get_index) {
  std::vector<std::byte> previousHash(
      {std::byte{0x11}, std::byte{0x22}, std::byte{0x33}});
  std::time_t timestamp = std::time(nullptr);
  std::vector<Transaction> transactions;

  int index = 123;
  int version = 1;
  int nonce = 0;
  int difficultyTarget = 5;

  Block block(index, version, previousHash, timestamp, transactions, nonce,
              difficultyTarget);

  cr_assert_eq(block.getIndex(), index, "Index mismatch.");
}

// Test for getting the version of a block
Test(block, get_version) {
  std::vector<std::byte> previousHash(
      {std::byte{0x11}, std::byte{0x22}, std::byte{0x33}});
  std::time_t timestamp = std::time(nullptr);
  std::vector<Transaction> transactions;

  int index = 0;
  int version = 5;
  int nonce = 0;
  int difficultyTarget = 5;

  Block block(index, version, previousHash, timestamp, transactions, nonce,
              difficultyTarget);

  cr_assert_eq(block.getVersion(), version, "Version mismatch.");
}

// Test block signing and verification
Test(block, sign_and_verify_block) {
  auto keyPair = Block::generateEVPKeyPair();
  EVP_PKEY *privateKey = keyPair.first;
  EVP_PKEY *publicKey = keyPair.second;

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

  bool signatureResult = block.signBlock(privateKey);
  cr_assert(signatureResult, "Failed to sign the block.");

  bool verificationResult = block.verifyBlockSignature(publicKey);
  cr_assert(verificationResult, "Failed to verify the block signature.");

  EVP_PKEY_free(privateKey);
  EVP_PKEY_free(publicKey);
}
