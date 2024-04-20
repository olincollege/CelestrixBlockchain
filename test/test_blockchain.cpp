#include "../src/Blockchain.h"
#include <criterion/criterion.h>

Test(Blockchain, Constructor) {

  int difficulty = 1;

  std::vector<std::byte> previousHash{std::byte{0x02}};

  std::time_t timestamp = 1;

  std::vector<std::byte> data(
      {std::byte{0x01}, std::byte{0x02}, std::byte{0x03}});
  Transaction transaction(1, data);
  std::vector<Transaction> transaction_vector{transaction};

  Block block(previousHash, timestamp, transaction_vector);

  Blockchain blockchain(difficulty);
  blockchain.addBlock(block);
  Block addedBlock = blockchain.getBlock();
  cr_assert_eq(addedBlock.getTimestamp(), 1);
}
