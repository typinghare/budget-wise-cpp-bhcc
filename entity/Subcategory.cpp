#include "Subcategory.h"


Subcategory::Subcategory(
    const unsigned int id,
    const QString& name,
    Category& category
) :
    id(id),
    name(name),
    category(category) {
}

unsigned int Subcategory::getId() const {
    return id;
}

QString Subcategory::getName() const {
    return name;
}

Category& Subcategory::getCategory() const {
    return category;
}
