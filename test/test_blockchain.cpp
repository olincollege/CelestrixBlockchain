#include "../src/Blockchain.h"
#include <criterion/criterion.h>

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

  int index = 0;
  int version = 1;
  int nonce = 123; // Some arbitrary value for testing purposes
  int difficultyTarget = 5;

  Block block(index, version, previousHash, timestamp, transactions, nonce,
              difficultyTarget);

  cr_assert_eq(block.getNonce(), nonce);
}

// // Test blockchain printing
// Test(blockchain, print_blockchain1) {
//   Blockchain blockchain(3);

//   std::vector<std::byte> data(
//       {std::byte{0x01}, std::byte{0x02}, std::byte{0x03}});
//   Transaction transaction1(1, data);
//   Transaction transaction2(2, data);

//   int index = 0;

//   Block block1(index, std::vector<std::byte>(), std::time(nullptr),
//                std::vector<Transaction>());

//   block1.addTransaction(transaction1);
//   block1.addTransaction(transaction2);

//   blockchain.addBlock(block1);

//   std::stringstream expected_output;
//   expected_output << "Block Hash: ";
//   for (const auto &byte : block1.getBlockHash()) {
//     expected_output << std::hex << static_cast<int>(byte);
//   }

//   expected_output << std::endl;
//   expected_output << "Previous Hash: ";
//   for (const auto &byte : block1.getPreviousHash()) {
//     expected_output << std::hex << static_cast<int>(byte);
//   }

//   expected_output << std::endl;
//   expected_output << "Timestamp: " << block1.getTimestamp() << std::endl;
//   expected_output << "Transactions: " << std::endl;
//   for (const Transaction &transaction : block1.getTransactions()) {
//     expected_output << "Type: " << transaction.getType() << std::endl;
//     expected_output << "Length: " << transaction.getLength() << std::endl;
//   }

//   expected_output << std::endl;

//   std::stringstream actual_output;
//   std::streambuf *cout_buffer = std::cout.rdbuf();
//   std::cout.rdbuf(actual_output.rdbuf());

//   blockchain.printBlockchain();

//   std::cout.rdbuf(cout_buffer);

//   cr_assert_str_eq(expected_output.str().c_str(),
//   actual_output.str().c_str(),
//                    "Printed blockchain output doesn't match expected
//                    output");
// }
