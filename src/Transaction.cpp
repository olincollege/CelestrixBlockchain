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
  return {type, data};
}

std::string Transaction::serialize() const {
  nlohmann::json jsonObj;
  jsonObj["type"] = type;
  jsonObj["length"] = length;
  std::vector<int> dataInt;
  dataInt.reserve(data.size());
  for (const auto &byte : data) {
    dataInt.push_back(static_cast<int>(byte));
  }
  jsonObj["data"] = dataInt;

  return jsonObj.dump();
}

Transaction Transaction::deserialize(const std::string &serializedData) {
  nlohmann::json jsonObj = nlohmann::json::parse(serializedData);
  int type = jsonObj["type"];
  std::vector<std::byte> data;
  const auto &dataInt = jsonObj["data"];
  data.reserve(dataInt.size());
  for (const auto &intValue : dataInt) {
    data.push_back(static_cast<std::byte>(intValue));
  }

  return {type, data};
}
