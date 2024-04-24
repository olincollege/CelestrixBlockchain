#include "Blockchain.h"

int main() {
  int index = 0;
  int version = 1;
  std::vector<std::byte> previousHash(
      {std::byte{0x11}, std::byte{0x22}, std::byte{0x33}});
  std::time_t timestamp = std::time(nullptr);
  std::vector<Transaction> transactions;
  int nonce = 0;
  int difficultyTarget = 4;

  Block block(index, version, previousHash, timestamp, transactions, nonce,
              difficultyTarget);

  std::vector<std::byte> data = {std::byte{0x01}, std::byte{0x02},
                                 std::byte{0x03}};

  Transaction transaction(1, data);
  Transaction transaction1(1, data);
  Transaction transaction2(1, data);
  block.addTransaction(transaction1);
  block.addTransaction(transaction2);

  block.mineBlock(difficultyTarget);

  std::cout << "Block Hash: ";
  for (const auto &byte : block.getBlockHash()) {
    std::cout << std::hex << static_cast<int>(byte);
  }
  std::cout << std::endl;
  std::cout << "Nonce: " << block.getNonce() << std::endl;
  std::cout << "Difficulty Target: " << block.getDifficulty() << std::endl;

  return 0;
}
