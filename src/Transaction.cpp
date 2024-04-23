#include "Transaction.h"

Transaction::Transaction(int type, const std::vector<std::byte> &data)
    : type(type), data(data) {
  length = static_cast<int>(data.size());
}

int Transaction::getType() const { return type; }

int Transaction::getLength() const { return length; }

const std::vector<std::byte> &Transaction::getData() const { return data; }

std::vector<std::byte> Transaction::encodeData() const {
  std::vector<std::byte> encoded;
  // Encode type
  encoded.push_back(static_cast<std::byte>(type));
  // Encode length
  encoded.push_back(static_cast<std::byte>(length));
  // Encode data
  encoded.insert(encoded.end(), data.begin(), data.end());
  return encoded;
}

Transaction Transaction::decode(const std::vector<std::byte> &encodedData) {
  int type = static_cast<int>(encodedData[0]);
  int length = static_cast<int>(encodedData[1]);
  std::vector<std::byte> data(encodedData.begin() + 2,
                              encodedData.begin() + 2 + length);
  return Transaction(type, data);
}
