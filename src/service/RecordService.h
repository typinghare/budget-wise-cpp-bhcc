#ifndef RECORDSERVICE_H
#define RECORDSERVICE_H

#include <QList>
#include <QSharedPointer>

#include "src/repository/RecordRepository.h"

class RecordService {
public:
    RecordService();

    /**
     * @brief Returns a user's records.
     * @param userId The ID of a specific user.
     */
    QList<Record*> getAllRecords(unsigned int userId, bool desc = true);

    /**
     * @brief Creates a record.
     * @param userId The ID of a specific user.
     * @param subcategoryId The ID of the subcategory.
     * @param amount The amount.
     */
    QSharedPointer<Record> createRecord(
        unsigned int userId,
        unsigned int categoryId,
        unsigned int subcategoryId,
        float amount);

    /**
     * @brief Deletes a user's last record.
     * @param userId The ID of the user.
     * @return true if deleted successfully.
     */
    bool deleteLastRecord(unsigned int userId);
};

#endif // RECORDSERVICE_H
