#ifndef LOCALUSER_H
#define LOCALUSER_H

#include "entity/User.h"

class LocalUser {
private:
    static LocalUser* INSTANCE;
public:
    LocalUser();

    /**
     * @brief Sets the local user.
     * @param user The local user to set.
     */
    static void set(User* user);

    /**
     * @brief Gets the local user.
     * @return Null pointer if the local user does not exist.
     */
    static User* get();

private:
    User* user = nullptr;
};

#endif // LOCALUSER_H
