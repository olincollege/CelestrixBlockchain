# Celestrix Blockchain

A blockchain implementation in C++ - Software Systems Spring 2024 Final
Project - Olin College of Engineering

## Overview of the Project
A blockchain is a decentralized and distributed digital ledger that records
transactions across multiple computers in a way that is immutable and transparent.
Celestrix Blockchain provides a simple implementation of this technology
in C++, demonstrating functionalities such as block creation, mining, and transaction management.

## Dependencies

The instructions to obtain the dependent libraries are below.

### OpenSSL

This library is used for verifying block signature in the blockchain.

**Linux** - run the below commands in a terminal
```commandline
sudo apt-get update
sudo apt-get install libssl-dev
```

**macOS** - run the below commands in a terminal (using homebrew)
If you do not have homebrew, the instructions to obtain that are here: https://brew.sh 
```commandline
brew install openssl
```

## Compilation and Execution

1. Clone the repository to your local machine.
2. Navigate to the project directory. (your pwd should be `CelestrixBlockchain/`)

### Using CMake - from CLI or IDE (recommended)

To compile and run Celestrix Blockchain using an IDE, you can 
simply build the project using the parent CMakeLists.txt,
and then run the `main` executable.

Alternatively, if you want to build from CMake using CLI:

```commandline
mkdir build
cd build
cmake ..
make
```

### Using CLI directly

To compile and run Celestrix Blockchain using CLI, 
you can compile the source code using a C++ compiler with C++20 support:

`g++ -std=c++20 -o blockchain main.cpp block.cpp blockchain.cpp -lssl -lcrypto`

Then, run the compiled executable: `./blockchain`


## Project Specifications

### Blockchain Example Output

<img width="416" alt="CelestrixBlockchain" src="https://github.com/sparshgup/CelestrixBlockchain/assets/19605629/9c76b588-cea6-4081-9c5a-f2fac77ea00c">

### Initializing a new Blockchain

Initializing a new Blockchain is very simple because you only have to pass the desired difficulty for mining as a parameter.

```cpp
int difficulty = 4;
Blockchain blockchain(difficulty);
```

### Initializing a new Block

The universal standard is that the first block to be initialized and added to a blockchain is called the genesis block. 

To add a block, you need to create transactions which can be done by, for example:

```cpp
// Create data for transaction
std::vector<std::byte> data = {std::byte{0x01}, std::byte{0x02}, std::byte{0x03}};

// Create transaction
Transaction transaction(1, data);
```

Once you have created the desired amount of transactions, you can initialize a new block with the following parameters. Once after it is initialized, we need to mine the block and then sign it using a private key before adding it to the blockchain. (more on that below)

```cpp
Block block(int index, int version, std::vector<std::byte> previousHash,
  std::time_t timestamp, std::vector<Transaction> transactions, int nonce, int difficultyTarget);
block.addTransaction(transaction);
block.mineBlock(difficulty);
block.signBlock(privateKey);
blockchain.addBlock(block);
```

### Block Signature & Verification

Signing a block is not necessary to add the block to a blockchain (in this project), but it is considered as the best-practice to maintain the integrity of a blockchain and keep the transaction data secure.

To do this, we need to first initialize a public key and private key pair that will be used for signing & verifying a block.

```cpp
std::pair<EVP_PKEY *, EVP_PKEY *> keyPair = Block::generateEVPKeyPair();
EVP_PKEY *privateKey = keyPair.first;
EVP_PKEY *publicKey = keyPair.second;
```

We can sign a block with the generated private key once after we have initialized a block.
```cpp
block.signBlock(privateKey);
```

Similarly, we can verify the block signature by using the generated public key and printing the verification result in the standard output.
```cpp
if (block.verifyBlockSignature(publicKey)) {
  std::cout << "Signature of block is valid." << std::endl;
} else {
  std::cout << "Signature of block is invalid." << std::endl;
}
```

### Printing the blockchain

For ease of use, one can print the entire blockchain by simply using:

```cpp
blockchain.printBlockchain();
```

### Verifying the blockchain 

One of the requirements once after we have manually created a blockchain is to actually verify if the blocks are connected properly by checking the linkage of the block hashes. In this project, one can verify the blockchain and print the verification result in the standard output using:

```cpp
if (blockchain.isChainValid()) {
  std::cout << "Blockchain is valid." << std::endl;
} else {
  std::cout << "Blockchain is invalid." << std::endl;
}
```
