#ifndef ADVANCED_CPP_BHCC_CATEGORY_H
#define ADVANCED_CPP_BHCC_CATEGORY_H

#include <QString>

/**
 * @brief Category entity.
 */
class Category {
public:
    /**
     * @brief Creates a category.
     * @param id The ID of this category.
     * @param name The name of this category.
     */
    Category(unsigned int id, unsigned int userId, const QString& name);

    /**
     * @brief Returns the ID of this category.
     */
    [[nodiscard]] unsigned int getId() const;

    /**
     * @brief Returns the ID of the user who creates this category.
     */
    [[nodiscard]] unsigned int getUserId() const;

    /**
     * @brief Returns the name of this category.
     * @return The name of this category.
     */
    [[nodiscard]] QString getName() const;

private:
    unsigned int id;
    unsigned int userId;
    QString name;
};

#endif
