#include "../src/Blockchain.h"
#include <criterion/criterion.h>

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
