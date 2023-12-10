#include "Subcategory.h"

Subcategory::Subcategory(
    unsigned int id,
    unsigned int userId,
    unsigned int categoryId,
    const QString& name) :
    id(id),
    name(name),
    userId(userId),
    categoryId(categoryId) {
}

unsigned int Subcategory::getId() const {
    return id;
}

unsigned int Subcategory::getUserId() const {
    return userId;
}

unsigned int Subcategory::getCategoryId() const {
    return categoryId;
}

QString Subcategory::getName() const {
    return name;
}
