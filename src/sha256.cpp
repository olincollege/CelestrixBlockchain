#include "sha256.h"


const uint32_t sha256::K[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

const uint32_t sha256::initialHashValues[8] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};

uint32_t sha256::rightRotate(uint32_t value, uint32_t n) {
    return (value >> n ) | (value << (32 - n));
}

uint32_t sha256::sigma0(uint32_t value) {
    return rightRotate(value, 7) ^ rightRotate(value, 18) ^ (value >> 3);
}

uint32_t sha256::sigma1(uint32_t value) {
    return rightRotate(value, 17) ^ rightRotate(value, 19) ^ (value >> 10);
}

uint32_t sha256::Sigma0(uint32_t value) {
    return rightRotate(value, 2) ^ rightRotate(value, 13) ^ rightRotate(value, 22);
}

uint32_t sha256::Sigma1(uint32_t value) {
    return rightRotate(value, 6) ^ rightRotate(value, 11) ^ rightRotate(value, 25);
}

std::vector<uint32_t> sha256::computeMessageSchedule(const std::vector<uint8_t> &block) {
    std::vector<uint32_t> messageSchedule(64);
    for (int i = 0; i < 16; ++i) {
        messageSchedule[i] = (block[i * 4] << 24) | (block[i * 4 + 1] << 16) | (block[i * 4 + 2] << 8) | block[i * 4 + 3];
    }
    for (int i = 16; i < 64; ++i) {
        messageSchedule[i] = sigma1(messageSchedule[i - 2]) + messageSchedule[i - 7] + sigma0(messageSchedule[i - 15]) + messageSchedule[i - 16];
    }
    return messageSchedule;
}

std::string sha256::hash(std::basic_string<char, std::char_traits<char>, std::allocator<char>> message) {
    std::vector<uint8_t> paddedMessage;
    // Pad the message
    paddedMessage.push_back(0x80);
    // Append zeros such that message length is 448 bits modulo 512
    while ((paddedMessage.size() * 8) % 512 != 448) {
        paddedMessage.push_back(0x00);
    }
    // Append original message bit-length
    uint64_t messageLength = message.size() * 8;
    for (int i = 0; i < 8; ++i) {
        paddedMessage.push_back((messageLength >> (56 -i * 8)) & 0xFF);
    }

    // Process blocks
    std::vector<uint32_t> hashValues(initialHashValues, initialHashValues + 8);

    for (size_t i = 0; i < paddedMessage.size(); i += 64) {
        std::vector<uint8_t> block(paddedMessage.begin() + i, paddedMessage.begin() + i + 64);
        std::vector<uint32_t> messageSchedule = computeMessageSchedule(block);

        // Initialize working variables to current hash value
        uint32_t a = hashValues[0];
        uint32_t b = hashValues[1];
        uint32_t c = hashValues[2];
        uint32_t d = hashValues[3];
        uint32_t e = hashValues[4];
        uint32_t f = hashValues[5];
        uint32_t g = hashValues[6];
        uint32_t h = hashValues[7];

        // Compression function main loop
        for (int j = 0; j < 64; ++j) {
            uint32_t ch = (e & f) ^ ((~e) & g);
            uint32_t temp1 = h + Sigma1(e) + ch + K[j] + messageSchedule[j];
            uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
            uint32_t temp2 = Sigma0(e) + maj;

            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        // Add the compressed chunk to the current hash value
        hashValues[0] += a;
        hashValues[1] += b;
        hashValues[2] += c;
        hashValues[3] += d;
        hashValues[4] += e;
        hashValues[5] += f;
        hashValues[6] += g;
        hashValues[7] += h;
    }

    // Construct the final hash string
    std::string hashString;
    for (size_t i = 0; i < hashValues.size(); ++i) {
        for (int j = 0; j < 4; ++j) {
            hashString += ((hashValues[i] >> (24 - j * 8)) & 0xFF);
        }
    }

    return hashString;
}


