#ifndef CELESTRIXBLOCKCHAIN_BLOCKCHAIN_H
#define CELESTRIXBLOCKCHAIN_BLOCKCHAIN_H

#include "Block.h"

/**
 * @brief Class representing a blockchain.
 */
class Blockchain {
private:
  std::vector<Block> chain;
  int difficulty;

public:
  /**
   * @brief Constructs a new Blockchain object with the specified difficulty.
   * @param difficulty The difficulty level for mining blocks in the blockchain.
   */
  explicit Blockchain(int difficulty);

  /**
   * @brief Adds a block to the blockchain after mining it.
   * @param block The block to be added to the blockchain.
   */
  void addBlock(const Block &block);

  /**
   * @brief Retrieves a block from the blockchain by its index.
   * @param index The index of the block to retrieve.
   * @return The block at the specified index.
   * @throws std::out_of_range if the index is out of bounds.
   */
  Block getBlock(int index) const;

  /**
   * @brief Checks if the blockchain is valid by verifying the integrity of each
   * block.
   * @return true if the blockchain is valid, false otherwise.
   */
  bool isChainValid() const;

  /**
   * @brief Prints the entire blockchain to the standard output.
   */
  void printBlockchain() const;
};

#endif // CELESTRIXBLOCKCHAIN_BLOCKCHAIN_H
