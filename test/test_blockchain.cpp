#include "../src/Blockchain.h"
#include <criterion/criterion.h>

// Test basic block adding and getting from blockchain
Test(blockchain, add_block) {
  Blockchain blockchain(3);

  std::vector<std::byte> previousHash(
      {std::byte{0x11}, std::byte{0x22}, std::byte{0x33}});
  std::time_t timestamp = std::time(nullptr);
  std::vector<Transaction> transactions;

  int index = 0;
  int version = 1;
  int nonce = 0;
  int difficultyTarget = 5;

  std::vector<std::byte> data(
      {std::byte{0x01}, std::byte{0x02}, std::byte{0x03}});
  Transaction transaction1(1, data);
  Transaction transaction2(1, data);

  Block block(index, version, previousHash, timestamp, transactions, nonce,
              difficultyTarget);
  block.addTransaction(transaction1);
  block.addTransaction(transaction2);

  blockchain.addBlock(block);

  Block lastBlock = blockchain.getBlock(block.getIndex());

  cr_assert(block.getPreviousHash() == lastBlock.getPreviousHash() &&
                block.getTimestamp() == lastBlock.getTimestamp() &&
                block.getTransactions().size() ==
                    lastBlock.getTransactions().size(),
            "Block not added correctly to the chain");

  for (size_t i = 0; i < block.getTransactions().size(); ++i) {
    Transaction expectedTransaction = block.getTransactions()[i];
    Transaction actualTransaction = lastBlock.getTransactions()[i];

    cr_assert(expectedTransaction.getType() == actualTransaction.getType() &&
                  expectedTransaction.getLength() ==
                      actualTransaction.getLength() &&
                  expectedTransaction.getData() == actualTransaction.getData(),
              "Transaction %zu not added correctly to the block", i);
  }
}

// Test blockchain validity checking
Test(blockchain, chain_validity) {
  int difficulty = 4;
  Blockchain blockchain(difficulty);

  std::vector<std::byte> data1 = {std::byte{0x01}, std::byte{0x02},
                                  std::byte{0x03}};
  std::vector<std::byte> data2 = {std::byte{0x04}, std::byte{0x05},
                                  std::byte{0x06}};
  std::vector<std::byte> data3 = {std::byte{0x10}, std::byte{0x11},
                                  std::byte{0x12}};

  Transaction transaction1(1, data1);
  Transaction transaction2(1, data2);
  Transaction transaction3(1, data3);

  Block genesisBlock(0, 1, std::vector<std::byte>(), std::time(nullptr),
                     std::vector<Transaction>(), 1, difficulty);
  genesisBlock.mineBlock(difficulty);
  blockchain.addBlock(genesisBlock);
  genesisBlock.signBlock();

  Block block1(1, 1, genesisBlock.getBlockHash(), std::time(nullptr),
               std::vector<Transaction>(), 10, difficulty);
  block1.addTransaction(transaction1);
  block1.mineBlock(difficulty);
  blockchain.addBlock(block1);
  block1.signBlock();

  Block block2(2, 1, block1.getBlockHash(), std::time(nullptr),
               std::vector<Transaction>(), 23, difficulty);
  block2.addTransaction(transaction2);
  block2.addTransaction(transaction3);
  block2.mineBlock(difficulty);
  blockchain.addBlock(block2);
  block2.signBlock();
  cr_assert(blockchain.isChainValid(), "Chain validity failed.");
}

Test(blockchain, get_block) {
  int difficulty = 4;
  Blockchain blockchain(difficulty);

  std::vector<std::byte> data1 = {std::byte{0x01}, std::byte{0x02},
                                  std::byte{0x03}};
  std::vector<std::byte> data2 = {std::byte{0x04}, std::byte{0x05},
                                  std::byte{0x06}};
  std::vector<std::byte> data3 = {std::byte{0x10}, std::byte{0x11},
                                  std::byte{0x12}};

  Transaction transaction1(1, data1);
  Transaction transaction2(1, data2);
  Transaction transaction3(1, data3);

  Block genesisBlock(0, 1, std::vector<std::byte>(), std::time(nullptr),
                     std::vector<Transaction>(), 1, difficulty);
  genesisBlock.mineBlock(difficulty);
  blockchain.addBlock(genesisBlock);
  genesisBlock.signBlock();

  Block block1(1, 1, genesisBlock.getBlockHash(), std::time(nullptr),
               std::vector<Transaction>(), 10, difficulty);
  block1.addTransaction(transaction1);
  block1.mineBlock(difficulty);
  blockchain.addBlock(block1);
  block1.signBlock();

  Block block2(2, 1, block1.getBlockHash(), std::time(nullptr),
               std::vector<Transaction>(), 23, difficulty);
  block2.addTransaction(transaction2);
  block2.addTransaction(transaction3);
  block2.mineBlock(difficulty);
  blockchain.addBlock(block2);
  block2.signBlock();

  Block zeroithBlock = blockchain.getBlock(0);
  Block firstBlock = blockchain.getBlock(1);
  Block secondBlock = blockchain.getBlock(2);

  cr_assert(zeroithBlock.getBlockHash() == genesisBlock.getBlockHash() &&
            zeroithBlock.getPreviousHash() == genesisBlock.getPreviousHash() &&
            zeroithBlock.getTimestamp() == genesisBlock.getTimestamp()
            // &&
            // zeroithBlock.getTransactions() == genesisBlock.getTransactions()
            // && zeroithBlock.getBlockSize() == genesisBlock.getBlockSize()
  );

  cr_assert(firstBlock.getBlockHash() == block1.getBlockHash() &&
            firstBlock.getPreviousHash() == block1.getPreviousHash() &&
            firstBlock.getTimestamp() == block1.getTimestamp()
            //&& firstBlock.getTransactions() == block1.getTransactions() &&
            // firstBlock.getBlockSize() == block1.getBlockSize()

  );

  cr_assert(secondBlock.getBlockHash() == block2.getBlockHash() &&
            secondBlock.getPreviousHash() == block2.getPreviousHash() &&
            secondBlock.getTimestamp() == block2.getTimestamp()
            //&& secondBlock.getTransactions() == block2.getTransactions() &&
            // secondBlock.getBlockSize() == block2.getBlockSize()

  );
}
