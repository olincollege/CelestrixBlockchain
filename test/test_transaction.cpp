#include "../src/Transaction.h"
#include <criterion/criterion.h>

// Test to verify encoding and decoding of transactions
Test(transaction, encode_decode) {
  std::vector<uint8_t> data = {0x01, 0x02, 0x03};
  Transaction tx(1, data);

  std::vector<uint8_t> encoded = tx.encodeData();
  Transaction decodedTx = Transaction::decode(encoded);

  cr_assert_eq(decodedTx.getType(), tx.getType(), "Type mismatch");
  cr_assert_eq(decodedTx.getLength(), tx.getLength(), "Length mismatch");
  cr_assert_eq(decodedTx.getData(), tx.getData(), "Data mismatch");
}
