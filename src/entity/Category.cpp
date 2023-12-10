#include "Category.h"

Category::Category(unsigned int id, unsigned int userId, const QString& name) :
    id(id),
    userId(userId),
    name(name) {
}

unsigned int Category::getId() const {
    return id;
}

unsigned int Category::getUserId() const {
    return userId;
}

QString Category::getName() const {
    return name;
}
