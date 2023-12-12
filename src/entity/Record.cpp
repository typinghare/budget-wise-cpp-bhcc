#include "Record.h"

Record::Record(
    unsigned int id,
    unsigned int userId,
    unsigned int subcategoryId,
    QDateTime createdAt,
    double amount,
    double balance
    ) :
    id(id),
    userId(userId),
    subcategoryId(subcategoryId),
    createdAt(createdAt),
    amount(amount),
    balance(balance){
}

unsigned int Record::getId() const {
    return id;
}

unsigned int Record::getUserId() const {
    return userId;
}

unsigned int Record::getSubcategoryId() const {
    return subcategoryId;
}

QDateTime Record::getCreatedAt() const {
    return createdAt;
}

double Record::getAmount() const {
    return amount;
}

double Record::getBalance() const {
    return balance;
}
