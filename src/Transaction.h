#ifndef CELESTRIXBLOCKCHAIN_TRANSACTION_H
#define CELESTRIXBLOCKCHAIN_TRANSACTION_H

#include "nlohmann/json.hpp"
#include <cstdint>
#include <vector>

class Transaction {
private:
  int type;
  int length;
  std::vector<std::byte> data;

public:
  Transaction(int type, const std::vector<std::byte> &data);
  [[nodiscard]] int getType() const;
  [[nodiscard]] int getLength() const;
  [[nodiscard]] const std::vector<std::byte> &getData() const;
  [[nodiscard]] std::vector<std::byte> encodeData() const;
  static Transaction decode(const std::vector<std::byte> &encodedData);
  [[nodiscard]] std::string serialize() const;
  static Transaction deserialize(const std::string &serializedData);
};

#endif // CELESTRIXBLOCKCHAIN_TRANSACTION_H
