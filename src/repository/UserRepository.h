#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include <QString>

#include "src/entity/User.h"

/**
 * @brief User repository.
 */
class UserRepository {
public:
    /**
     * @brief Retrieves a user by its ID.
     * @param id The ID of the user.
     * @return A user entity pointer; nullptr if the user does not exist.
     */
    User* get(unsigned int id);

    /**
     * @brief Retrieves a user by its username.
     * @return A user entity pointer; nullptr if the user does not exist.
     */
    User* getByUsername(const QString& username);

    /**
     * @brief Creates a new user.
     * @param username The username of the new user.
     * @param authString The authentication string of the new user.
     * @param email The email of the new user.
     * @return A user entity pointer; nullptr if it fails to create a new user.
     */
    User* create(const QString& username, const QString& authString, const QString& email);

    /**
     * @brief Updates user's authentication string.
     * @param id The ID of the user.
     * @param authString The new authentication string.
     */
    bool updateAuthString(unsigned int id, const QString& authString);
};

#endif // USERREPOSITORY_H
