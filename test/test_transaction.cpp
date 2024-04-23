#include "../src/Transaction.h"
#include <criterion/criterion.h>

// Test to verify encoding and decoding of transactions
Test(transaction, encode_decode) {
  std::vector<std::byte> data(
      {std::byte{0x01}, std::byte{0x02}, std::byte{0x03}});
  Transaction tx(1, data);

  std::vector<std::byte> encoded = tx.encodeData();
  Transaction decodedTx = Transaction::decode(encoded);

  cr_assert_eq(decodedTx.getType(), tx.getType(), "Type mismatch");
  cr_assert_eq(decodedTx.getLength(), tx.getLength(), "Length mismatch");
  cr_assert_eq(decodedTx.getData(), tx.getData(), "Data mismatch");
}

// Test basic class construction
Test(transaction, constructor) {
  std::vector<std::byte> data(
      {std::byte{0x01}, std::byte{0x02}, std::byte{0x03}});
  Transaction transaction(1, data);
  cr_assert_eq(transaction.getType(), 1);
  cr_assert_eq(transaction.getLength(), 3);
  cr_assert_eq(transaction.getData(), data);
}

// Test with empty data
Test(transaction, no_data) {
  std::vector<std::byte> emptyData({});
  Transaction emptyTransaction(1, emptyData);
  cr_assert_eq(emptyTransaction.getLength(), 0);
  cr_assert_eq(emptyTransaction.getData(), emptyData);
}

// Test with data with one entry
Test(transaction, OneData) {
  std::vector<std::byte> oneData({std::byte{0x01}});
  Transaction oneTransaction(1, oneData);
  cr_assert_eq(oneTransaction.getLength(), 1);
  cr_assert_eq(oneTransaction.getData(), oneData);
}
