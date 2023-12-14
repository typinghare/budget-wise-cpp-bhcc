#ifndef SUBCATEGORYREPOSITORY_H
#define SUBCATEGORYREPOSITORY_H

#include <QList>
#include <QSharedPointer>

#include "src/entity/Subcategory.h"

class SubcategoryRepository {
public:
    /**
     * @brief Retrieves and returns a subcateogry.
     * @param id The ID of the subcategory.
     */
    Subcategory* get(unsigned int id);

    /**
     * @brief Creates a subcategory.
     * @param name The name of the subcategory.
     * @param userId The ID of the user who created this subcategory.
     * @param cateogryId The ID of the category this subcategory belongs to.
     * @return A subcategory entity pointer; nullptr if the category fails to be created.
     */
    Subcategory* create(unsigned int userId, unsigned int cateogryId, const QString& name);

    /**
     * @brief Retrieves all subcategories.
     * @param userId The ID of the user who created this subcategory.
     * @return A list of subcategory entity pointers;
     */
    QList<Subcategory*> getAllByUserId(unsigned int userId);

    /**
     * @brief Retrieves all subcategories.
     * @param userId The ID of the user who created this subcategory.
     * @param categoryId The ID of the category this subcategory belongs to.
     * @return A list of subcategory entity pointers;
     */
    QList<Subcategory*> getAllByCategoryId(unsigned int categoryId);

    /**
     * @brief Retrieves category.
     * @param userId The ID of the user who created this subcategory.
     * @param categoryId The ID of the category this subcategory belongs to.
     * @param name The name of this subcategory.
     * @return A category entity pointer; nullptr if the category does not exist.
     */
    Subcategory* getByUserIdAndCategoryIdAndName(
        unsigned int userId,
        unsigned int categoryId,
        const QString& name);

    /**
     * @brief Deletes all subcategories.
     * @param categoryId The ID of the category this subcategory belongs to.
     * @return True if deleted successfully; false otherwise.
     */
    bool removeByCategoryId(unsigned int categoryId);

    /**
     * @brief Deletes a subcategory.
     * @param id The ID of the subcategory to delete.
     * @return True if deleted successfully; false otherwise.
     */
    bool remove(unsigned int id);

    /**
     * @brief Updates a subcategory.
     * @param id The ID of the subcategory to update.
     * @param userId The ID of the user who created this subcategory.
     * @param name The new subcategory name.
     * @return A subcategory entity pointer; nullptr if the category fails to be updated.
     */
    bool update(unsigned int id, unsigned int categoryId, const QString &name);
};

#endif // SUBCATEGORYREPOSITORY_H
