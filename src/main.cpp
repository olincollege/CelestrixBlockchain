#include "Blockchain.h"

int main() {
  Blockchain blockchain(3);

  std::vector<std::byte> data(
      {std::byte{0x01}, std::byte{0x02}, std::byte{0x03}});
  Transaction transaction1(1, data);
  Transaction transaction2(2, data);

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

  block1.addTransaction(transaction1);
  block1.addTransaction(transaction2);

  blockchain.addBlock(block1);

  blockchain.printBlockchain();

  return 0;
}
