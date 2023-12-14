#include "CategoryService.h"

#include "src/Database.h"

bool CategoryService::deleteCategory(unsigned int categoryId) {
    auto categoryRepository = Database::getInstance()->getCategoryRepository();
    bool removeCategoryResult = categoryRepository.remove(categoryId);
    if (!removeCategoryResult) {
        return false;
    }

    // Delete all subcategories
    auto subcategoryRepository = Database::getInstance()->getSubcategoryRepository();
    auto removeSubcategoriesResult = subcategoryRepository.removeByCategoryId(categoryId);
    if (!removeSubcategoriesResult) {
        return false;
    }

    // Delete all records
    auto recordRepository = Database::getInstance()->getRecordRepository();
    auto removeRecordsResult = recordRepository.removeByCategoryId(categoryId);
    if (!removeRecordsResult) {
        return false;
    }

    return true;
}
