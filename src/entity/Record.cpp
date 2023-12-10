#include "Record.h"

Record::Record(
    unsigned int id,
    Date createdAt,
    unsigned int userId,
    unsigned int subcategoryId,
    double amount,
    double balance
) :
    id(id),
    createdAt(createdAt),
    userId(userId),
    subcategoryId(subcategoryId),
    amount(amount),
    balance(balance){
}

unsigned int Record::getId() const {
    return id;
}

Date Record::getCreatedAt() const {
    return createdAt;
}

unsigned int Record::getUserId() const {
    return userId;
}

unsigned int Record::getSubcategoryId() const {
    return subcategoryId;
}

double Record::getAmount() const {
    return amount;
}

double Record::getBalance() const {
    return balance;
}
