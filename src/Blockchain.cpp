#include "Blockchain.h"

Blockchain::Blockchain(int difficulty) : difficulty(difficulty) {

}

void Blockchain::addBlock(const Block &block) {
    chain.push_back(block);
}

Block Blockchain::getBlock() const {}

bool Blockchain::isChainValid() const {}

void Blockchain::mineTransactions() const {}
