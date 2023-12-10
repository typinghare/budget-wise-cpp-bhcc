#include "LocalUser.h"

LocalUser* LocalUser::INSTANCE = new LocalUser();

LocalUser::LocalUser() = default;

void LocalUser::set(User* user) {
    LocalUser::INSTANCE->user = user;
}

User*  LocalUser::get() {
    return LocalUser::INSTANCE->user;
}
