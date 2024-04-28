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