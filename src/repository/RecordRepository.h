#ifndef RECORDREPOSITORY_H
#define RECORDREPOSITORY_H

#include <QList>

#include "src/entity/Record.h"

class RecordRepository {
public:
    RecordRepository();

    /**
     * @brief Retrives all records of a specific user.
     * @param userId The ID of the user.
     * @return A list of record entity pointers.
     */
    QList<Record *> getAll(unsigned int userId);

    /**
     * @brief Creates a record.
     * @param userId The ID of the user who creates this record.
     * @param subcategoryId The ID of the subcategory that this record belongs to.
     * @param createdAt The creating time.
     * @param amount The amount of money received (negative numbers represents payments).
     * @param balance The balance.
     * @return A record entity pointer the record is successfully created; a null pointer otherwise.
     */
    Record* create(
        unsigned int userId,
        unsigned int subcategoryId,
        QDateTime createdAt,
        double amount,
        double balance);
};

#endif // RECORDREPOSITORY_H
