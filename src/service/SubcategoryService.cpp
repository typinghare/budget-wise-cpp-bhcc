#include "SubcategoryService.h"

#include "src/Database.h"

bool SubcategoryService::removeSubcategory(unsigned int subcategoryId) {
    // Delete all subcategories
    auto subcategoryRepository = Database::getInstance()->getSubcategoryRepository();
    auto removeSubcategoryResult = subcategoryRepository.remove(subcategoryId);
    if (!removeSubcategoryResult) {
        return false;
    }

    // Delete all records
    auto recordRepository = Database::getInstance()->getRecordRepository();
    auto removeRecordsResult = recordRepository.removeBySubcategoryId(subcategoryId);
    if (!removeRecordsResult) {
        return false;
    }

    return true;
}
