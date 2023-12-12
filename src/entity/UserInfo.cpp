#include "UserInfo.h"

UserInfo::UserInfo() = default;

UserInfo::UserInfo(unsigned int id, unsigned int userId, double balance):
    id(id),
    userId(userId),
    balance(balance) {
}

unsigned int UserInfo::getId() const {
    return id;
}

unsigned int UserInfo::getUserId() const {
    return userId;
}

double UserInfo::getBalance() const {
    return balance;
}
