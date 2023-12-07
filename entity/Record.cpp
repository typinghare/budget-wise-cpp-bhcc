#include "Record.h"

Record::Record(
    const unsigned int id,
    const Date createdAt,
    Category&category,
    Subcategory&subcategory,
    const double amount
) :
    id(id),
    createdAt(createdAt),
    category(category),
    subcategory(subcategory),
    amount(amount) {
}

unsigned int Record::getId() const {
    return id;
}

Date Record::getCreatedAt() const {
    return createdAt;
}

Category& Record::getCategory() const {
    return category;
}

Subcategory& Record::getSubcategory() const {
    return subcategory;
}

double Record::getAmount() const {
    return amount;
}
