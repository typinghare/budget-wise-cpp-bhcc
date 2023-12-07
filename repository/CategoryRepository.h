#ifndef CATEGORYREPOSITORY_H
#define CATEGORYREPOSITORY_H

#include <QList>

#include "entity/Category.h"

class CategoryRepository {
public:
    CategoryRepository();

    /**
     * @brief Retrieves a category.
     * @param id The ID of the category.
     * @return A category entity pointer; nullptr if the category does not exist.
     */
    Category* getCategory(unsigned int id);

    /**
     * @brief Creates a new category.
     * @param userId The ID of the user who creates the category.
     * @param name The name of this category.
     * @return A category entity pointer; nullptr if it fails to create a new category.
     */
    Category* createCategory(unsigned int userId, const QString& name);

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
    QList<Category *> getAll(unsigned int userId);

    /**
     * @brief Deletes a category.
     * @param userId The ID of the user who creates the category.
     * @param name The name of this category.
     * @return true if a category is deleted; false otherwise.
     */
    bool remove(unsigned int userId, const QString& name);
};

#endif // CATEGORYREPOSITORY_H
