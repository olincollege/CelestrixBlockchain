#ifndef CELESTRIXBLOCKCHAIN_TRANSACTION_H
#define CELESTRIXBLOCKCHAIN_TRANSACTION_H

#include <cstdint>
#include <vector>

/**
 * @brief Class representing a transaction in a block.
 */
class Transaction {
private:
  int type;
  int length;
  std::vector<std::byte> data;

public:
  /**
   * @brief Constructor for Transaction class.
   * @param type Type of the transaction.
   * @param data Data of the transaction.
   */
  Transaction(int type, const std::vector<std::byte> &data);

  /**
   * @brief Gets the type of the transaction.
   * @return The type of the transaction.
   */
  [[nodiscard]] int getType() const;

  /**
   * @brief Gets the length of the transaction data.
   * @return The length of the transaction data.
   */
  [[nodiscard]] int getLength() const;

  /**
   * @brief Gets the data of the transaction.
   * @return The data of the transaction.
   */
  [[nodiscard]] const std::vector<std::byte> &getData() const;

  /**
   * @brief Encodes the transaction data.
   * @return The encoded transaction data.
   */
  [[nodiscard]] std::vector<std::byte> encodeData() const;

  /**
   * @brief Decodes the encoded transaction data.
   * @param encodedData The encoded transaction data.
   * @return The decoded transaction.
   */
  static Transaction decode(const std::vector<std::byte> &encodedData);
};

#endif // CELESTRIXBLOCKCHAIN_TRANSACTION_H
