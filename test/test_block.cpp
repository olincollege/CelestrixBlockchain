#include "../src/Block.h"
#include <criterion/criterion.h>

Test(block, block_hash) {}

Test(block, mine_block) {}

Test(block, validate_block) {}

Test(block, serialize_block) {}

Test(block, deserialize_block) {}

Test(block, calculate_merkle_root) {}

Test(block, get_block_hash) {}

// Test for adding a transaction to a block
Test(block, add_transaction) {
    std::vector<std::byte> previousHash(
            {std::byte{0x11}, std::byte{0x22}, std::byte{0x33}});
    std::vector<std::byte> data = {std::byte{0x01}, std::byte{0x02}, std::byte{0x03}};
    Transaction transaction(1, data);

    int index = 0;
    std::time_t timestamp = std::time(nullptr);
    std::vector<Transaction> transactions;

    Block block(index, 0, previousHash, timestamp, transactions, 0, 0);

    block.addTransaction(transaction);

    std::vector<Transaction> updatedTransactions = block.getTransactions();

    cr_assert_eq(updatedTransactions.size(), 1);

    cr_assert_eq(updatedTransactions[0].getType(), 1);
    cr_assert_eq(updatedTransactions[0].getData(), data);
}

Test(block, get_previous_hash) {
    std::vector<std::byte> previousHash(
            {std::byte{0x11}, std::byte{0x22}, std::byte{0x33}});
    std::vector<std::byte> data(
            {std::byte{0x01}, std::byte{0x02}, std::byte{0x03}});
    std::time_t timestamp = std::time(nullptr);

    Transaction transaction(1, data);

    int index = 0;
    std::vector<Transaction> transactions;

    Block block(index, 0, previousHash, timestamp, transactions, 0, 0);

    block.addTransaction(transaction);

    std::vector<std::byte> retrievedPreviousHash = block.getPreviousHash();

    cr_assert_eq(retrievedPreviousHash, previousHash);
}

Test(block, get_block_signature) {}

Test(block, get_merkle_root) {}

Test(block, get_nonce) {
    std::vector<std::byte> previousHash(
            {std::byte{0x11}, std::byte{0x22}, std::byte{0x33}});
    std::vector<std::byte> data(
            {std::byte{0x01}, std::byte{0x02}, std::byte{0x03}});
    std::time_t timestamp = std::time(nullptr);
    std::vector<Transaction> transactions;

    int index = 0;

    Block block(index, 0, previousHash, timestamp, transactions, 0, 0);

    cr_assert_eq(block.getNonce(), 0);
}

Test(block, set_difficult) {}
