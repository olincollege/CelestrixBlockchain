#ifndef CELESTRIXBLOCKCHAIN_TRANSACTION_H
#define CELESTRIXBLOCKCHAIN_TRANSACTION_H

#include <cstdint>
#include <vector>

class Transaction {
private:
  int type;
  int length;
  std::vector<uint8_t> data;

public:
  Transaction(int type, const std::vector<uint8_t> &data);
  int getType() const;
  int getLength() const;
  const std::vector<uint8_t> &getData() const;
  std::vector<uint8_t> encodeData() const;
  static Transaction decode(const std::vector<uint8_t> &encodedData);
};

#endif // CELESTRIXBLOCKCHAIN_TRANSACTION_H
