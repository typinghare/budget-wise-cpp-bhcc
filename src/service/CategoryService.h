#ifndef CATEGORYSERVICE_H
#define CATEGORYSERVICE_H

class CategoryService {
public:
    /**
     * @brief Deletes a category
     * @param categoryId The ID of the category.
     */
    bool deleteCategory(unsigned int categoryId);
};

#endif // CATEGORYSERVICE_H
