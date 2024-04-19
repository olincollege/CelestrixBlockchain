#ifndef CELESTRIXBLOCKCHAIN_TRANSACTION_H
#define CELESTRIXBLOCKCHAIN_TRANSACTION_H

#include <cstdint>
#include <vector>

class Transaction {
private:
  int type;
  int length;
  std::vector<std::byte> data;

public:
  Transaction(int type, const std::vector<std::byte> &data);
  int getType() const;
  int getLength() const;
  const std::vector<std::byte> &getData() const;
  std::vector<std::byte> encodeData() const;
  static Transaction decode(const std::vector<std::byte> &encodedData);
};

#endif // CELESTRIXBLOCKCHAIN_TRANSACTION_H
