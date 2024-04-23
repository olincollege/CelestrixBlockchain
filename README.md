# Celestrix Blockchain

A blockchain implementation in C++ - Software Systems Spring 2024 Final
Project - Olin College of Engineering

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
sudo apt-get update
sudo apt-get install nlohmann-json3-dev
```

### nlohmann json

This library is used for serializing and deserializing data in the JSON format when communicating using a P2P network.

**Linux** - run the below commands in a terminal
```commandline
sudo apt-get update
sudo apt-get install libssl-dev
```

**macOS** - run the below commands in a terminal (using homebrew)
```commandline
brew install nlohmann-json
```