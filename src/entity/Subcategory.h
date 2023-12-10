#ifndef ADVANCED_CPP_BHCC_SUBCATEGORY_H
#define ADVANCED_CPP_BHCC_SUBCATEGORY_H

#include <QString>

// Forward declaration
class Category;

class Subcategory {
public:
    /**
     * @brief Creates a subcategory.
     * @param id The ID of this subcategory.
     * @param name The name of this subcategory.
     * @param userId The ID of the user who created this subcategory.
     * @param categoryId The ID of category this subcategory belongs to.
     */
    Subcategory(
        const unsigned int id,
        unsigned int userId,
        unsigned int categoryId,
        const QString& name);

    /**
     * Returns the ID of this subcategory.
     */
    [[nodiscard]] unsigned int getId() const;

    /**
     * Returns the ID of the user who created this subcategory.
     */
    [[nodiscard]] unsigned int getUserId() const;

    /**
     * Returns the ID of category this subcategory belongs to.
     */
    [[nodiscard]] unsigned int getCategoryId() const;

    /**
     * Returns the name of this subcategory.
     */
    [[nodiscard]] QString getName() const;

private:
    unsigned int id;
    unsigned int userId;
    unsigned int categoryId;
    QString name;
};

#endif
