#ifndef SUBCATEGORYREPOSITORY_H
#define SUBCATEGORYREPOSITORY_H

#include "entity/Subcategory.h"

class SubcategoryRepository {
public:
    SubcategoryRepository();

    /**
     * @brief Retrieves a subcategory.
     * @param id The ID of the category.
     * @return A category entity pointer; nullptr if the category does not exist.
     */
    Subcategory* getSubcategory(unsigned int id);
};

#endif // SUBCATEGORYREPOSITORY_H
