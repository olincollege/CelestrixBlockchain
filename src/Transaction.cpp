#include "Transaction.h"

Transaction::Transaction(int type, const std::vector <uint8_t> &data) : type(type), data(data) {
    length = data.size();
}

int Transaction::getType() const {
    return type;
}

int Transaction::getLength() const {
    return length;
}

const std::vector<u_int8_t>& Transaction::getData() const {
    return data;
}

std::vector<u_int8_t> Transaction::encodeData() const {
    std::vector<u_int8_t> encoded;
    // Encode type
    encoded.push_back(static_cast<u_int8_t>(type));
    // Encode length
    encoded.push_back(static_cast<u_int8_t>(length));
    // Encode data
    encoded.insert(encoded.end(), data.begin(), data.end());
    return encoded;
}

Transaction Transaction::decode(const std::vector <u_int8_t> &encodedData) {
    int type = encodedData[0];
    int length = encodedData[1];
    std::vector<u_int8_t> data(encodedData.begin() + 2, encodedData.begin() + 2 + length);
    return Transaction(type, data);
}