#ifndef ADVANCED_CPP_BHCC_CATEGORY_H
#define ADVANCED_CPP_BHCC_CATEGORY_H

#include <iostream>

/**
 * @brief Category entity.
 */
class Category {
public:
    /**
     * Creates a category.
     * @param id The ID of this category.
     * @param name The name of this category.
     */
    Category(unsigned int id, std::string_view name);

    /**
     * Returns the ID of this category.
     * @return the ID of this category.
     */
    [[nodiscard]] unsigned int getId() const;

    /**
     * @brief Returns the name of this category.
     * @return The name of this category.
     */
    [[nodiscard]] std::string_view getName() const;

private:
    unsigned int id;
    std::string name;
};

#endif
