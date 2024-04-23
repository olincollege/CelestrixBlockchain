#include "../src/Blockchain.h"
#include <criterion/criterion.h>

// Test basic block adding and getting from blockchain
Test(blockchain, add_block) {
  Blockchain blockchain(3);

  std::vector<std::byte> previousHash;
  std::time_t timestamp = std::time(nullptr);
  std::vector<Transaction> transactions;
  Block block(previousHash, timestamp, transactions);

  blockchain.addBlock(block);

  Block lastBlock = blockchain.getBlock();
  cr_assert(block.getPreviousHash() == lastBlock.getPreviousHash() &&
                block.getTimestamp() == lastBlock.getTimestamp(), // &&
            // block.getTransactions() == lastBlock.getTransactions(),
            "Block not added correctly to the chain");
}

// Test blockchain validity checking
Test(blockchain, chain_validity) {
  Blockchain blockchain(3);

  std::vector<std::byte> previousHash;
  std::time_t timestamp = std::time(nullptr);
  std::vector<Transaction> transactions;

  Block block1(previousHash, timestamp, transactions);
  Block block2(previousHash, timestamp, transactions);

  blockchain.addBlock(block1);
  blockchain.addBlock(block2);

  cr_assert(blockchain.isChainValid(), "Chain validity failed.");
}

// Test blockchain printing
Test(blockchain, print_blockchain1) {
  Blockchain blockchain(3);

  std::vector<std::byte> data(
      {std::byte{0x01}, std::byte{0x02}, std::byte{0x03}});
  Transaction transaction1(1, data);
  Transaction transaction2(2, data);
  Block block1(std::vector<std::byte>(), std::time(nullptr),
               std::vector<Transaction>());

  block1.addTransaction(transaction1);
  block1.addTransaction(transaction2);

  blockchain.addBlock(block1);

  std::stringstream expected_output;
  expected_output << "Block Hash: ";
  for (const auto &byte : block1.getBlockHash()) {
    expected_output << std::hex << static_cast<int>(byte);
  }

  expected_output << std::endl;
  expected_output << "Previous Hash: ";
  for (const auto &byte : block1.getPreviousHash()) {
    expected_output << std::hex << static_cast<int>(byte);
  }

  expected_output << std::endl;
  expected_output << "Timestamp: " << block1.getTimestamp() << std::endl;
  expected_output << "Transactions: " << std::endl;
  for (const Transaction &transaction : block1.getTransactions()) {
    expected_output << "Type: " << transaction.getType() << std::endl;
    expected_output << "Length: " << transaction.getLength() << std::endl;
  }

  expected_output << std::endl;

  std::stringstream actual_output;
  std::streambuf *cout_buffer = std::cout.rdbuf();
  std::cout.rdbuf(actual_output.rdbuf());

  blockchain.printBlockchain();

  std::cout.rdbuf(cout_buffer);

  cr_assert_str_eq(expected_output.str().c_str(), actual_output.str().c_str(),
                   "Printed blockchain output doesn't match expected output");
}
