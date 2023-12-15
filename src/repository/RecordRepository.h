#ifndef RECORDREPOSITORY_H
#define RECORDREPOSITORY_H

#include <QList>

#include "src/entity/Record.h"

class RecordRepository {
public:
    /**
     * @brief Retrieves and returns a record.
     * @param id The ID of the record.
     */
    Record* get(unsigned int id);

    /**
     * @brief Retrives all records of a specific user.
     * @param userId The ID of the user.
     * @return A list of record entity pointers.
     */
    QList<Record*> getAllByUser(unsigned int userId, bool desc);

    /**
     * @brief Retrives all records of a specific category.
     * @param categoryId The ID of the category.
     * @return A list of record entity pointers.
     */
    QList<Record*> getAllByCategory(unsigned int categoryId, bool desc);

    /**
     * @brief Retrives all records of a specific subcategory.
     * @param subcategoryId The ID of the subcategory.
     * @return A list of record entity pointers.
     */
    QList<Record*> getAllBySubcategory(unsigned int subcategoryId, bool desc);

    /**
     * @brief Creates a record.
     * @param userId The ID of the user who creates this record.
     * @param subcategoryId The ID of the subcategory that this record belongs to.
     * @param createdAt The creating time.
     * @param amount The amount of money received (negative numbers represents payments).
     * @return A record entity pointer the record is successfully created; a null pointer otherwise.
     */
    Record* create(
        unsigned int userId,
        unsigned int categoryId,
        unsigned int subcategoryId,
        QDateTime createdAt,
        double amount);

    /**
     * @brief Gets the balance of a certain record.
     * @param id The ID of a record.
     */
    Record* getWithBalance(unsigned int id);

    /**
     * @brief Retrieves and returns a user's last record ID.
     * @param userId The ID of the user.
     * @return 0 if not found.
     */
    unsigned int getLastId(unsigned int userId);

    /**
     * @brief Deletes a record repository.
     * @param id The ID of the record to delete.
     */
    bool remove(unsigned int id);

    /**
     * @brief Removes all records of a specific category.
     * @param categoryId The ID of the category.
     */
    bool removeByCategoryId(unsigned int categoryId);

    /**
     * @brief Removes all records of a specific subcategory.
     * @param categoryId The ID of the category.
     */
    bool removeBySubcategoryId(unsigned int subcategoryId);
};

#endif // RECORDREPOSITORY_H
