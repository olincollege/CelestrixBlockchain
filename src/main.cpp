#include "Blockchain.h"
#include "sha256.h"

int main() {
  std::cout << "==============================================================="
               "==========="
            << std::endl;
  std::cout << "==============================================================="
               "==========="
            << std::endl;
  std::cout << "                          Celestrix Blockchain "
               "           "
            << std::endl;
  std::cout << "==============================================================="
               "==========="
            << std::endl;
  std::cout << "==============================================================="
               "==========="
            << std::endl;

  // Initialize blockchain with the desired difficulty for mining
  int difficulty = 4;
  Blockchain blockchain(difficulty);

  // Generate EVP key pair for signature verification
  std::pair<EVP_PKEY *, EVP_PKEY *> keyPair = Block::generateEVPKeyPair();
  EVP_PKEY *privateKey = keyPair.first;
  EVP_PKEY *publicKey = keyPair.second;

  // Create data for transactions
  std::vector<std::byte> data1 = {std::byte{0x01}, std::byte{0x02},
                                  std::byte{0x03}};
  std::vector<std::byte> data2 = {std::byte{0x04}, std::byte{0x05},
                                  std::byte{0x06}};
  std::vector<std::byte> data3 = {std::byte{0x10}, std::byte{0x11},
                                  std::byte{0x12}};

  // Create transactions
  Transaction transaction1(1, data1);
  Transaction transaction2(1, data2);
  Transaction transaction3(1, data3);

  // signature verification
  std::cout << "                       Block Signature Verification "
               "           "
            << std::endl;

  // create and mine the genesis block
  Block genesisBlock(0, 1, std::vector<std::byte>(), std::time(nullptr),
                     std::vector<Transaction>(), 1, difficulty);
  genesisBlock.mineBlock(difficulty);
  genesisBlock.signBlock(privateKey);
  blockchain.addBlock(genesisBlock);

  // Create and mine block 1
  Block block1(1, 1, genesisBlock.getBlockHash(), std::time(nullptr),
               std::vector<Transaction>(), 10, difficulty);
  block1.addTransaction(transaction1);
  block1.mineBlock(difficulty);
  block1.signBlock(privateKey);
  blockchain.addBlock(block1);

  // Create and mine block 2
  Block block2(2, 1, block1.getBlockHash(), std::time(nullptr),
               std::vector<Transaction>(), 23, difficulty);
  block2.addTransaction(transaction2);
  block2.addTransaction(transaction3);
  block2.mineBlock(difficulty);
  block2.signBlock(privateKey);
  blockchain.addBlock(block2);

  // Verify signatures of the blocks
  if (genesisBlock.verifyBlockSignature(publicKey)) {
    std::cout << "Signature of genesis block is valid." << std::endl;
  } else {
    std::cout << "Signature of genesis block is invalid." << std::endl;
  }
  if (block1.verifyBlockSignature(publicKey)) {
    std::cout << "Signature of block 1 is valid." << std::endl;
  } else {
    std::cout << "Signature of block 1 is invalid." << std::endl;
  }
  if (block2.verifyBlockSignature(publicKey)) {
    std::cout << "Signature of block 2 is valid." << std::endl;
  } else {
    std::cout << "Signature of block 2 is invalid." << std::endl;
  }
  std::cout << "==============================================================="
               "==========="
            << std::endl;

  // Print the blockchain
  blockchain.printBlockchain();

  // Verify the blockchain
  std::cout << "==============================================================="
               "==========="
            << std::endl;
  if (blockchain.isChainValid()) {
    std::cout << "Blockchain is valid." << std::endl;
  } else {
    std::cout << "Blockchain is invalid." << std::endl;
  }

  std::cout << "==============================================================="
               "==========="
            << std::endl;

  // std::vector<std::byte> message = {std::byte(0x61), std::byte(0x62),
  //                                   std::byte(0x63)};
  // std::vector<std::byte> expectedHash = {
  //     std::byte(0xBA), std::byte(0x78), std::byte(0x16), std::byte(0xBF),
  //     std::byte(0x8F), std::byte(0x01), std::byte(0xCF), std::byte(0xEA),
  //     std::byte(0x41), std::byte(0x41), std::byte(0x40), std::byte(0xDE),
  //     std::byte(0x5D), std::byte(0xAE), std::byte(0x22), std::byte(0x23),
  //     std::byte(0xB0), std::byte(0x03), std::byte(0x61), std::byte(0xA3),
  //     std::byte(0x96), std::byte(0x17), std::byte(0x7A), std::byte(0x9C),
  //     std::byte(0xB4), std::byte(0x10), std::byte(0xFF), std::byte(0x61),
  //     std::byte(0xF2), std::byte(0x00), std::byte(0x15), std::byte(0xAD)};
  // std::vector<std::byte> hash = sha256::hash(message);

  // std::cout << "Actual Hash:" << std::endl;
  // for (const auto &byte : hash) {
  //   std::cout << std::hex << static_cast<int>(byte);
  // }
  // std::cout << std::endl;

  // std::cout << "Expected Hash:" << std::endl;

  // for (auto &byte : expectedHash) {
  //   std::cout << std::hex << static_cast<int>(byte);
  // }
  // std::cout << std::endl;

  // std::cout << "Hash from Online Source:" << std::endl;
  // std::cout
  //     << "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad"
  //     << std::endl;

  return 0;
}
