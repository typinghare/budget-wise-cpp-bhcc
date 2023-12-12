#ifndef USERINFOREPOSITORY_H
#define USERINFOREPOSITORY_H

#include "src/entity/UserInfo.h"

class UserInfoRepository {
public:
    UserInfoRepository();

    /**
     * @brief Creates a user info; the balance is 0 by default.
     * @param userId The ID of the user.
     * @return A user info entity; null pointer if it fails to create.
     */
    UserInfo* create(unsigned int userId);

    /**
     * @brief Retrieves and returns the balance of a user.
     * @param userId The ID of the user.
     */
    float getBalance(unsigned int userId);

    /**
     * @brief Sets balance for an user.
     * @param userId The ID of the user.
     * @param balance The balance to update of the user.
     */
    bool updateBalance(unsigned int userId, float balance);
};

class FailToGetUserInfoException: public std::exception {
};

#endif // USERINFOREPOSITORY_H
