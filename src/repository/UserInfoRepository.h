#ifndef USERINFOREPOSITORY_H
#define USERINFOREPOSITORY_H

#include "src/entity/UserInfo.h"

class UserInfoRepository {
public:
    /**
     * @brief Retrieves and returns a user info.
     * @param userId The ID of the specific user.
     */
    UserInfo* getByUserId(unsigned int userId);

    /**
     * @brief Creates a user info; the balance is 0 by default.
     * @param userId The ID of the user.
     * @return A user info entity; null pointer if it fails to create.
     */
    UserInfo* create(unsigned int userId);

    /**
     * @brief Sets balance for an user.
     * @param userId The ID of the user.
     * @param balance The balance to update of the user.
     */
    bool updateBalance(unsigned int userId, float balance);
};

#endif // USERINFOREPOSITORY_H
