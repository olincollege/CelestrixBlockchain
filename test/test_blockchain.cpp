#include "../src/Blockchain.h"
#include <criterion/criterion.h>

// // Test basic block adding and getting from blockchain
// Test(blockchain, add_block) {
//   Blockchain blockchain(3);

//   std::vector<std::byte> previousHash(
//       {std::byte{0x11}, std::byte{0x22}, std::byte{0x33}});
//   std::time_t timestamp = std::time(nullptr);
//   std::vector<Transaction> transactions;

//   int index = 0;
//   int version = 1;
//   int nonce = 0;
//   int difficultyTarget = 5;

//   Block block(index, version, previousHash, timestamp, transactions, nonce,
//               difficultyTarget);

//   blockchain.addBlock(block);

//   Block lastBlock = blockchain.getBlock(block.getIndex());
//   cr_assert(block.getPreviousHash() == lastBlock.getPreviousHash() &&
//                 block.getTimestamp() == lastBlock.getTimestamp(), // &&
//             // block.getTransactions() == lastBlock.getTransactions(),
//             "Block not added correctly to the chain");
// }

// Test blockchain validity checking
Test(blockchain, chain_validity) {
  Blockchain blockchain(3);

  std::vector<std::byte> previousHash(
      {std::byte{0x11}, std::byte{0x22}, std::byte{0x33}});
  std::time_t timestamp = std::time(nullptr);
  std::vector<Transaction> transactions;

  int index = 0;
  int version = 1;
  int nonce = 0;
  int difficultyTarget = 5;

  Block block1(index, version, previousHash, timestamp, transactions, nonce,
               difficultyTarget);
  Block block2(index, version, previousHash, timestamp, transactions, nonce,
               difficultyTarget);

  blockchain.addBlock(block1);
  blockchain.addBlock(block2);

  cr_assert(blockchain.isChainValid(), "Chain validity failed.");
}

// Test blockchain printing
