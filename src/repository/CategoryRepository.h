#ifndef CATEGORYREPOSITORY_H
#define CATEGORYREPOSITORY_H

#include <QList>

#include "src/entity/Category.h"

class CategoryRepository {
public:
    CategoryRepository();

    /**
     * @brief Retrieves a category.
     * @param id The ID of the category.
     * @return A category entity pointer; nullptr if the category does not exist.
     */
    Category* get(unsigned int id);

    /**
     * @brief Creates a new category.
     * @param userId The ID of the user who creates the category.
     * @param name The name of this category.
     * @return A category entity pointer; nullptr if it fails to create a new category.
     */
    Category* create(unsigned int userId, const QString& name);

    /**
     * @brief Retrieves a category by creator's ID and name.
     * @param userId The ID of the user who creates the category.
     * @param name The name of this category.
     * @return A category entity pointer; nullptr if the category does not exist.
     */
    Category* getByUserIdAndName(unsigned int userId, const QString& name);

    /**
     * @brief Retrieves all categories of a specifid user from the database.
     * @param userId The ID of the user.
     * @return A list of categories.
     */
    QList<Category*> getAll(unsigned int userId);

    /**
     * @brief Deletes a category.
     * @param id The ID of the category to delete.
     * @return true if a category is deleted; false otherwise.
     */
    bool remove(unsigned int id);

    /**
     * @brief Updates the name of the category.
     * @param id The ID of the category to update.
     * @param newName The new name of the category.
     * @return true if it is updated successfully; false otherwise.
     */
    bool update(unsigned int id, const QString& newName);
};

#endif // CATEGORYREPOSITORY_H
