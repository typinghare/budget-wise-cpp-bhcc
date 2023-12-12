#ifndef ADVANCED_CPP_BHCC_RECORD_H
#define ADVANCED_CPP_BHCC_RECORD_H

#include <QDateTime>

#include "Category.h"
#include "Subcategory.h"

class Record {
public:
    /**
     * Creates a record.
     * @param id The ID of this record.
     * @param date The creation date.
     * @param category The category this record belongs to.
     * @param subcategory The subcategory this record belongs to.
     * @param amount The amount of this record (in US dollars).
     */
    Record(
        unsigned int id,
        unsigned int userId,
        unsigned int subcategoryId,
        QDateTime createdAt,
        double amount,
        double balance);

    /**
     * @brief Returns the ID of this record.
     */
    [[nodiscard]] unsigned int getId() const;

    /**
     * @brief Returns the ID of the user who created this record.
     */
    [[nodiscard]] unsigned int getUserId() const;

    /**
     * @brief Returns the subcategory this record belongs to.
     */
    [[nodiscard]] unsigned int getSubcategoryId() const;

    /**
     * @brief Returns the creation date.
     */
    [[nodiscard]] QDateTime getCreatedAt() const;

    /**
     * @brief Returns the amount of this record.
     */
    [[nodiscard]] double getAmount() const;

    /**
     * @brief Returns the balance of this record.
     */
    [[nodiscard]] double getBalance() const;

private:
    unsigned int id;
    unsigned int userId;
    unsigned int subcategoryId;
    QDateTime createdAt;
    double amount;
    double balance;
};

#endif
