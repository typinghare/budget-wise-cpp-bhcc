#include "Record.h"

Record::Record(
    const unsigned int id,
    const Date date,
    Category&category,
    Subcategory&subcategory,
    const double amount
) : id(id), date(date), category(category), subcategory(subcategory), amount(amount) {
}

unsigned int Record::getId() const {
    return id;
}

Date Record::getDate() const {
    return date;
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
