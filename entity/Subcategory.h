#ifndef ADVANCED_CPP_BHCC_SUBCATEGORY_H
#define ADVANCED_CPP_BHCC_SUBCATEGORY_H

#include <iostream>
#include "Category.h"

class Subcategory {
public:
    /**
     * Creates a subcategory.
     * @param id The ID of this subcategory.
     * @param name The name of this subcategory.
     * @param category The category this subcategory belongs to.
     */
    Subcategory(unsigned int id, const QString& name, Category&category);

    /**
     * Returns the ID of this subcategory.
     * @return the ID of this subcategory.
     */
    [[nodiscard]] unsigned int getId() const;

    /**
     * Returns the name of this subcategory.
     * @return the name of this subcategory.
     */
    [[nodiscard]] QString getName() const;

    /**
     * Returns the category this subcategory belongs to.
     * @return the category this subcategory belongs to.
     */
    [[nodiscard]] Category& getCategory() const;

private:
    unsigned int id;
    QString name;
    Category&category;
};

#endif
