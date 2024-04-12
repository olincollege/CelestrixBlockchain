#include "Blockchain.h"

#include <iostream>

Blockchain::Blockchain(int difficulty) : difficulty(difficulty) {}

void Blockchain::addBlock(const Block &block) {}

Block Blockchain::getBlock() const {}

bool Blockchain::isChainValid() const {}

void Blockchain::mineTransactions() const {}

void Blockchain::printBlockchain() const {}
