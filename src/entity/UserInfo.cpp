#include "UserInfo.h"

UserInfo::UserInfo() = default;

UserInfo::UserInfo(unsigned int id)
    : id (id) {
}

unsigned int UserInfo::getId() const {
    return id;
}
